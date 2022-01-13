 {
   //binning
   std::vector<double> puBins = {0,10,20,30,40,50,60,70};
   std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
   std::vector<double> etaBins2p5 = {-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5};//,2.75,3.0}
   std::vector<double> etaBins3 = {0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.,2.25,2.5,2.75,3.0};
   std::vector<double> etaBins = {0,0.5,1.0,1.4442,1.566,2.0,2.5};
   std::vector<double> ptOneBinLow = {1,500}; 
   std::vector<double> ptOneBinMedium = {500,1000}; 
   std::vector<double> ptOneBinHigh = {1000,1500}; 
   std::vector<double> ptOneBinUltra = {1500,3000}; 
   std::vector<double> ptOneBinSuper = {3000,4000};

   std::vector<double> etaBinsFine = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4442,1.566,1.8,2.0,2.2,2.4,2.6};
   // binning for different energy ranges
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
   std::vector<double> etBins500To5000  = {500,2000,3000,4000,5000};

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
   std::string regresDirectory = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/";
   std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/Run3_2021/";

   // High Energy Photons 500To5000 trained on all high energy
   std::string results500To5000Pho = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/Run3Pho_Pt500to5000/";
   std::string outputName500To5000Pho = "regPhoEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*tree500To5000Pho = HistFuncs::makeChain("egRegTree",results500To5000Pho+outputName500To5000Pho,1,1,1);
   TTree*tree500To5000PhoFriend = HistFuncs::makeChain("egRegTreeFriend",results500To5000Pho+outputName500To5000Pho,1,1,1);
   tree500To5000Pho->AddFriend(tree500To5000PhoFriend);

   // High Energy Photons Trained on Saturated Crystals 
   std::string resultsSatCrysPho = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/Run3Pho_Pt500to5000_Saturated/";
   std::string outputNameSatCrysPho = "regPhoEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeSatCrysPho = HistFuncs::makeChain("egRegTree",resultsSatCrysPho+outputNameSatCrysPho,1,1,1);
   TTree*treeSatCrysPhoFriend = HistFuncs::makeChain("egRegTreeFriend",resultsSatCrysPho+outputNameSatCrysPho,1,1,1);
   treeSatCrysPho->AddFriend(treeSatCrysPhoFriend);

   // High Energy Electrons 500To5000 trained on all high energy
   std::string results500To5000Ele = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/Run3Ele_Pt500to5000/";
   std::string outputName500To5000Ele = "regEleEcalHighEnergy_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*tree500To5000Ele = HistFuncs::makeChain("egRegTree",results500To5000Ele+outputName500To5000Ele,1,1,1);
   TTree*tree500To5000EleFriend = HistFuncs::makeChain("egRegTreeFriend",results500To5000Ele+outputName500To5000Ele,1,1,1);
   tree500To5000Ele->AddFriend(tree500To5000EleFriend);

   // High Energy Electrons Trained on Saturated Crystals 
   std::string resultsSatCrysEle = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/Run3Ele_Pt500to5000_Saturated/";
   std::string outputNameSatCrysEle = "regEleEcalHighEnergy_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeSatCrysEle = HistFuncs::makeChain("egRegTree",resultsSatCrysEle+outputNameSatCrysEle,1,1,1);
   TTree*treeSatCrysEleFriend = HistFuncs::makeChain("egRegTreeFriend",resultsSatCrysEle+outputNameSatCrysEle,1,1,1);
   treeSatCrysEle->AddFriend(treeSatCrysEleFriend);

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
