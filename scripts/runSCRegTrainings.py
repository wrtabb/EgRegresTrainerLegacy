#!/usr/bin/env python

import subprocess
import os
try:
    from regtools import RegArgs
except ImportError:
    raise ImportError('module regtools not found, please add "python" to PYTHON27PATH or PYTHONPATH as appropriate eg\n  export PYTHON27PATH=$PYTHON27PATH:python\nand try again')
import time
import argparse
def main():  

    parser = argparse.ArgumentParser(description='runs the SC regression trainings')
    parser.add_argument('--era',required=True,help='year to produce for, 2016, 2017, 2018 are the options')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/HLTRun3',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/HLTRun3Regression",help='output dir')
    args = parser.parse_args()

    #step 1, run calo only regression on the ideal IC to get the mean
    #step 2, apply the mean to the real IC sample and save the result in a tree
    #step 3, retrain the resolution for the real IC on the corrected energy
    run_step1 = True
    run_step2 = True
    run_step3 = True

    #setup the selection (event number cuts come later)
    cuts_name = "stdCuts" 
    base_ele_cuts = "(eg_energy>0 && eg_sigmaIEtaIEta>0 && eg_sigmaIPhiIPhi>0 && {extra_cuts})"
    
    #prefixes all the regressions produced
    if args.era=='2021':
        base_reg_name = "HLTReg2021"
        input_ideal_ic  = "{}/.root".format(args.input_dir)
        input_real_ic = "{}/.root".format(args.input_dir)
        ideal_eventnr_cut = "eventnr%5==0"  #4million electrons
        real_eventnr_cut = "eventnr%5==1" #4million electrons

    else:
        raise ValueError("era {} is invalid, only option is 2021".format(era))

    
    regArgs = RegArgs()
    regArgs.input_training =  str(input_ideal_ic)
    regArgs.input_testing = str(input_ideal_ic)
    regArgs.set_sc_default()
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = "{}/resultsSC".format(args.output_dir)
    regArgs.cuts_name = cuts_name
    regArgs.base_name = "{}_IdealIC_IdealTraining".format(base_reg_name)
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.ntrees = 1500
 
    print """about to run the supercluster regression with: 
    name: {name}
    ideal ic input: {ideal_ic}
    real ic input: {real_ic}
    output dir: {out_dir}
steps to be run:
    step 1: ideal training for mean       = {step1}
    step 2: apply ideal training to real  = {step2}
    step 3: real training for sigma       = {step3}""".format(name=base_reg_name,ideal_ic=input_ideal_ic,real_ic=input_real_ic,out_dir=args.output_dir,step1=run_step1,step2=run_step2,step3=run_step3)
    time.sleep(20)

    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    if run_step1: regArgs.run_eb_and_ee()
    
    regArgs.do_eb = True
    forest_eb_file = regArgs.output_name()
    regArgs.do_eb = False
    forest_ee_file = regArgs.output_name()

    regArgs.base_name = "{}_RealIC_IdealTraining".format(base_reg_name)
    input_for_res_training = str(regArgs.applied_name()) #save the output name before we change it
    input_for_input_for_res_training = str(input_real_ic)
    
    # Set scram arch
    arch = "slc7_amd64_gcc700"
    if run_step2: subprocess.Popen(["bin/"+arch+"/RegressionApplierExe",input_for_input_for_res_training,input_for_res_training,"--gbrForestFileEE",forest_ee_file,"--gbrForestFileEB",forest_eb_file,"--nrThreads","4","--treeName",regArgs.tree_name,"--writeFullTree","1","--regOutTag","Ideal"]).communicate()

    regArgs.base_name = "{}_RealIC_RealTraining".format(base_reg_name)
    regArgs.input_training = input_for_res_training
    regArgs.input_testing = input_for_res_training
    regArgs.target = "eg_gen_energy/(eg_rawEnergy*regIdealMean)"
    regArgs.fix_mean = True
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = real_eventnr_cut)
    if run_step3: regArgs.run_eb_and_ee()

if __name__ =='__main__':
    main()


