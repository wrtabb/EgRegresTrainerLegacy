"""
regtools is a python module to collect various functions for running the regression
"""
import os
import subprocess

class RegArgs:
    def set_defaults(self):
        self.base_name = "reg_sc"
        self.cuts_name = "stdCuts"
        self.vars_name = "stdVar"  
        self.cfg_dir = "configs"
        self.out_dir = "results" 
        self.tree_name = "egHLTRun3Tree"
        self.write_full_tree = "0"
        self.reg_out_tag = ""
        self.min_events = 300
        self.shrinkage = 0.15
        self.min_significance = 5.0
        self.event_weight = 1.
        self.mean_min = 0.2
        self.mean_max = 2.0
        self.fix_mean = False
        self.input_testing = "test.root"
        self.input_training = "train.root"
        self.target = "eg_gen_energy/(eg_rawEnergy)"
        self.var_eb = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"
        self.var_ee = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"
        self.cuts_base = "(eg_gen_energy>0 && eg_sigmaIEtaIEta>0 && eventnr%2==0)"
        self.ntrees = 1500
        self.do_eb = True

    def __init__(self):
        self.set_defaults()

    def name(self):
        if self.do_eb: region = "EB"
        else: region = "EE"
        return "{args.base_name}_{args.vars_name}_{args.cuts_name}_{region}_ntrees{args.ntrees}".format(args=self,region=region)

    def applied_name(self):
        return "{args.out_dir}/{args.base_name}_{args.vars_name}_{args.cuts_name}_ntrees{args.ntrees}_applied.root".format(args=self)
    
    def cfg_name(self):
        return "{}/{}.config".format(self.cfg_dir,self.name())

    def output_name(self):
        return "{}/{}_results.root".format(self.out_dir,self.name())

    def set_sc_default(self):
        self.target = "eg_gen_energy/(eg_rawEnergy)"
#        self.var_eb = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"
#        self.var_ee = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"
        self.var_eb = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV"
        self.var_ee = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEE1GeV"
    
#    def set_ecal_default(self):
#        self.target = "eg_gen_energy/(eg_rawEnergy)"
#        self.var_eb = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"
#        self.var_ee = "eg_rawEnergy:eg_phiWidth:eg_eta:eg_rawEnergy:eg_clusterMaxDR:eg_r9Full:eg_nrClus:nrHitsEB1GeV+nrHitsEE1GeV"


    def make_cfg(self):
        base_cfg = """
Trainer: GBRLikelihoodTrain
NumberOfRegressions: 1
TMVAFactoryOptions: !V:!Silent:!Color:!DrawProgressBar
OutputDirectory: {args.out_dir}
Regression.1.Name: {name}
Regression.1.InputFiles: {args.input_training}
Regression.1.Tree: {args.tree_name}
Regression.1.trainingOptions: SplitMode=random:!V
Regression.1.Options: MinEvents={args.min_events}:Shrinkage={args.shrinkage}:NTrees={args.ntrees}:MinSignificance={args.min_significance}:EventWeight={args.event_weight}
Regression.1.DoCombine: False
Regression.1.DoEB: {args.do_eb}
Regression.1.VariablesEB: {args.var_eb}
Regression.1.VariablesEE: {args.var_ee}
Regression.1.Target: {args.target}
Regression.1.CutBase: {args.cuts_base} 
Regression.1.CutEB: eg_isEB
Regression.1.CutEE: !eg_isEB
Regression.1.MeanMin: {args.mean_min}
Regression.1.MeanMax: {args.mean_max}
Regression.1.FixMean: {args.fix_mean}

""".format(args=self,name=self.name())
        if not os.path.isdir(self.cfg_dir):
            os.mkdir(self.cfg_dir)
        with open(self.cfg_name(),"w") as f:
            f.write(base_cfg)

    def run_eb_and_ee(self):  

        if not os.path.isdir(self.out_dir):
            os.mkdir(self.out_dir)

        self.do_eb = True
        self.make_cfg()

	# Scram arch has to be set manually
	# This also must be done in the training script in scripts/
	arch = "slc7_amd64_gcc700"

        print "starting: {}".format(self.name())
        subprocess.Popen(["bin/"+arch+"/RegressionTrainerExe",self.cfg_name()]).communicate()
        forest_eb_file = self.output_name()
    
        self.do_eb = False
        self.make_cfg()
        print "starting: {}".format(self.name())
        subprocess.Popen(["bin/"+arch+"/RegressionTrainerExe",self.cfg_name()]).communicate()
        forest_ee_file = self.output_name()

        
        subprocess.Popen(["bin/"+arch+"/RegressionApplierExe",self.input_testing,self.applied_name(),"--gbrForestFileEE",forest_ee_file,"--gbrForestFileEB",forest_eb_file,"--nrThreads","4","--treeName",self.tree_name,"--writeFullTree",self.write_full_tree,"--regOutTag",self.reg_out_tag]).communicate()

        print "made ",self.applied_name()


    def forest_filenames(self):
        do_eb_org = self.do_eb
        self.do_eb = True
        forest_eb_file = self.output_name()
        self.do_eb = False
        forest_ee_file = self.output_name()
        self.do_eb = do_eb_org
        return forest_eb_file,forest_ee_file
