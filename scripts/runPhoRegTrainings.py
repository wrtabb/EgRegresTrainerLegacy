#!/usr/bin/env python

import subprocess
import os
import regtools
from regtools import RegArgs
import argparse   

def main():
    
    parser = argparse.ArgumentParser(description='runs the SC regression trainings')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/2016UL',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="results/2016UL_HE",help='output dir')
    args = parser.parse_args()

    #step 1, run calo only regression on the ideal IC to get the mean
    #step 2, apply the mean to the real IC sample and save the result in a tree
    #step 3, retrain the resolution for the real IC on the corrected energy

    #event split: ECAL Ideal IC train = eventnr%10=0
    #             ECAL Real IC train = eventnr%10=1
    run_step1 = True
    run_step2 = True
    run_step3 = True
    
    base_pho_cuts = "(pho.nrSatCrys>0 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && pho.et>0 && {extra_cuts})"

    era_name = "2016UL"
    input_ideal_ic  = "{}/DoublePhoton_FlatPt-5To5000.root".format(args.input_dir)
    input_real_ic = "{}/DoublePhoton_FlatPt-5To5000.root".format(args.input_dir)
    ideal_eventnr_cut = "evt.eventnr%3==0"
    real_eventnr_cut = "evt.eventnr%3==1"



    #step1 train the calo only regression using IDEAL intercalibration constants
    print "starting step1"
    regArgs = RegArgs()
    regArgs.input_training = str(input_ideal_ic)
    regArgs.input_testing = str(input_ideal_ic)  
    regArgs.set_phoecal_default() 
    regArgs.cuts_name = "stdCuts"
    regArgs.cuts_base = base_pho_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = "resultsPhoV5" 
    regArgs.ntrees = 1500  
    regArgs.base_name = "regPhoEcal{era_name}_IdealIC_IdealTraining".format(era_name=era_name)
    if run_step1: regArgs.run_eb_and_ee()
    
    #step2 now we run over the REAL intercalibration constant data and make a new tree with this regression included
    print "starting step2"
    regArgs.do_eb = True
    forest_eb_file = regArgs.output_name()
    regArgs.do_eb = False
    forest_ee_file = regArgs.output_name()

    regArgs.base_name = "regPhoEcal{era_name}_RealIC_IdealTraining".format(era_name=era_name)
    input_for_res_training = str(regArgs.applied_name()) #save the output name before we change it

    # Set scram arch
    arch = "slc7_amd64_gcc700"
    if run_step2: subprocess.Popen(["bin/"+arch+"/RegressionApplierExe",input_real_ic,input_for_res_training,"--gbrForestFileEE",forest_ee_file,"--gbrForestFileEB",forest_eb_file,"--nrThreads","4","--treeName",regArgs.tree_name,"--writeFullTree","1","--regOutTag","Ideal"]).communicate()
    
    #step3 we now run over re-train with the REAL sample for the sigma, changing the target to have the correction applied 
    print "starting step3"
    regArgs.base_name = "regPhoEcal{era_name}_RealIC_RealTraining".format(era_name=era_name)
    regArgs.input_training = input_for_res_training
    regArgs.input_testing = input_for_res_training
    regArgs.target = "mc.energy/((sc.rawEnergy+sc.rawESEnergy)*regIdealMean)"
    regArgs.fix_mean = True
    regArgs.write_full_tree = "1"
    regArgs.reg_out_tag = "Real"
    regArgs.cuts_base = base_pho_cuts.format(extra_cuts = real_eventnr_cut)
    if run_step3: regArgs.run_eb_and_ee()

    
          
    
if __name__ =='__main__':
    main()


