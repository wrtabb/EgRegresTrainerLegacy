 {
   //binning
   std::vector<double> puBins = {0,10,20,30,40,50,60,70};
   std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
   std::vector<double> etaBins = {0,0.5,1.0,1.4442,1.566,2.0,2.5};
   std::vector<double> etaBins3 = {0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
   std::vector<double> ptOneBinVeryLow = {1,100}; 
   std::vector<double> ptOneBinLow = {1,500}; 
   std::vector<double> ptOneBinMedium = {500,1000}; 
   std::vector<double> ptOneBinHigh = {1000,1500}; 
   std::vector<double> ptOneBinUltra = {1500,3000}; 
   std::vector<double> ptOneBinSuper = {3000,4000};

   std::vector<double> etaBinsFine = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,
                                      1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.0,2.25,2.5};
   std::vector<double> etaBinsFine3= {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,
                                      1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.0,2.25,2.5,2.75,3.0};
   // binning for different energy ranges
   std::vector<double> etBinsVeryLow    = {1,10,40,60,80,100};
   std::vector<double> etBinsLow3   = {25,40,50,60};
   std::vector<double> etBinsLow    = {1,100,200,300,400,500};
   std::vector<double> etBinsMedium = {500,600,700,800,900,1000};
   std::vector<double> etBinsHigh   = {1000,1100,1200,1300,1400,1500};
   std::vector<double> etBinsUltra  = {1500,1750,2000,2250,2500,2750,3000};
   std::vector<double> etBinsSuper  = {3000,3200,3400,3800,4000};
   std::vector<double> etBinsAllEle = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,
				       1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,
				       2300,2400,2500,2600,2700,2800,2900,3000};
   std::vector<double> etBinsHEEle  = {500,600,700,800,900,1000,1100,1200,
				       1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,
				       2300,2400,2500,2600,2700,2800,2900,3000};
   std::vector<double> etBinsAllPho = {5,100,200,300,400,500,1000,1100,1200,
				       1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,
				       2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
				       3300,3400,3500,3600,3700,3800,3900,4000};

   // binning for QCD samples
   std::vector<double> ptOneBinQCDLow  = {0,80}; 
   std::vector<double> ptOneBinQCDHigh = {0,1000}; 
   std::vector<double> etBinsQCDLow    = {0,20,40,80};
   std::vector<double> etBinsQCDHigh   = {0,200,400,600,1000};
   std::vector<double> etaBinsEBEE     = {0,1.4442,1.566,2.5};
   std::vector<double> puBinsQCD       = {0,30,60,90};


   std::vector<double> etBinsPhoHigh = {1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000};
   std::vector<double> etaBinsSimple = {0.,0.7,1.1,1.4442,1.566,2.,2.25,2.5};
   
   //suppressing noisy fits
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
   RooMsgService::instance().setSilentMode(true);
   gErrorIgnoreLevel = kError;
  
   //-----trees-----//
 
   //Directories for making trees
   std::string resultsDirectory = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/results/";
   std::string inputDirectoryRun3 = "/home/hep/wrtabb/Egamma/input_trees/Run3/2021/";
   std::string inputDirectory2018 = "/home/hep/wrtabb/Egamma/input_trees/2018UL/";

   // Run3_2021 Electrons 
   std::string resultsELE = resultsDirectory + "resultsEle/";
   std::string nameELE  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeEle = HistFuncs::makeChain("egRegTree",inputDirectoryRun3+"DoubleElectron_FlatPt-1To500_FlatPU0to70_120X_mcRun3_2021_realistic_v6-v1_AODSIM.root",1,1,1);
   TTree*treeEleFriend = HistFuncs::makeChain("egRegTreeFriend",resultsELE+nameELE,1,1,1);
   treeEle->AddFriend(treeEleFriend);

   // Run2_2018UL Electrons 
   std::string resultsELE2018 = resultsDirectory + "resultsEleV5/";
   std::string nameELE2018  = "eleReg2018UL_applied.root";
   TTree*treeEle2018 = HistFuncs::makeChain("egRegTree",inputDirectory2018+"DoubleElectron_FlatPt-1To300_2018ConditionsFlatPU0to70RAW_105X_upgrade2018_realistic_v4-v1_AODSIM_EgRegTreeV5Refined.root",1,1,1);
   TTree*treeEle2018Friend = HistFuncs::makeChain("egRegTreeFriend",resultsELE2018+nameELE2018,1,1,1);
   treeEle2018->AddFriend(treeEle2018Friend);
   
   // Run3_2021 Photons 
   std::string resultsPHO = resultsDirectory + "resultsPho/";
   std::string namePHO  = "regPhoEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treePho = HistFuncs::makeChain("egRegTree",inputDirectoryRun3+"DoublePhoton_FlatPt-5To500_FlatPU0to70_120X_mcRun3_2021_realistic_v6-v1_AODSIM.root",1,1,1);
   TTree*treePhoFriend = HistFuncs::makeChain("egRegTreeFriend",resultsPHO+namePHO,1,1,1);
   treePho->AddFriend(treePhoFriend);

   // Run2_2018UL Photons 
   std::string resultsPHO2018 = resultsDirectory + "resultsPhoV5/";
   std::string namePHO2018  = "phoReg2018UL_applied.root";
   TTree*treePho2018 = HistFuncs::makeChain("egRegTree",inputDirectory2018+"DoublePhoton_FlatPt-5To300_2018ConditionsFlatPU0to70RAW_105X_upgrade2018_realistic_v4-v1_AODSIM_EgRegTreeV5Refined.root",1,1,1);
   TTree*treePho2018Friend = HistFuncs::makeChain("egRegTreeFriend",resultsPHO2018+namePHO2018,1,1,1);
   treePho2018->AddFriend(treePho2018Friend);

   /*************************************
   #now as an example do the following, 
   #note the second tree argument is for when I was comparing to a different sample, 
   #ie 102X 2018, now we just set it to null

   ResPlotter resPlotter
   resPlotter.makeHists({regTreeEleReal2018V52018Reg,nullptr},"Real IC, 1.566< |#eta|<2.5","mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3","mc.pt","sc.seedEta",etBins,etaBins)
   resPlotter.printFits({3,5,6},"plots/regresFitsThreeComp")

   #or compare two variables 
   resPlotter.printFits({3,6},"plots/regresFitsTwoComp")
  
   ************************************/
}
