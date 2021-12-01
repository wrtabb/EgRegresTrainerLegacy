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
   std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/Run3_2021/";

   // Run3_2021 Photons
   std::string resultsPho = resultsDirectory + "resultsPho/";
   std::string step3NamePho  = "regPhoEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treePhoStep3 = HistFuncs::makeChain("egRegTree",resultsPho+step3NamePho,1,1,1);
   TTree*treePhoStep3Friend = HistFuncs::makeChain("egRegTreeFriend",resultsPho+step3NamePho,1,1,1);
   treePhoStep3->AddFriend(treePhoStep3Friend);

   // Run3_2021 Mustache superclusters 
   std::string resultsSC = resultsDirectory + "resultsSC/";
   std::string step3NameSC  = "2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   std::string step2NameSC  = "2021Run3_RealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeSCStep3 = HistFuncs::makeChain("egRegTree",resultsSC+step2NameSC,1,1,1);
   TTree*treeSCStep3Friend = HistFuncs::makeChain("egRegTreeFriend",resultsSC+step3NameSC,1,1,1);
   treeSCStep3->AddFriend(treeSCStep3Friend);

   // Run3_2021 Electrons 
   std::string resultsEle = resultsDirectory + "resultsEle/";
   std::string step3NameEle  = "regEleEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   std::string step4NameEle  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeEleStep4 = HistFuncs::makeChain("egRegTree",resultsEle+step3NameEle,1,1,1);
   TTree*treeEleStep4Friend = HistFuncs::makeChain("egRegTreeFriend",resultsEle+step4NameEle,1,1,1);
   treeEleStep4->AddFriend(treeEleStep4Friend);

   // Run3_2021 High energy electrons
   std::string results500To1000Ele = resultsDirectory + "resultsPt500To1000Ele/";
   std::string outputName500To1000Ele  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*tree500To1000Ele = HistFuncs::makeChain("egRegTree",results500To1000Ele+outputName500To1000Ele,1,1,1);
   TTree*tree500To1000EleFriend = HistFuncs::makeChain("egRegTreeFriend",results500To1000Ele+outputName500To1000Ele,1,1,1);
   tree500To1000Ele->AddFriend(tree500To1000EleFriend);

   std::string results1000To1500Ele = resultsDirectory + "resultsPt1000To1500Ele/";
   std::string outputName1000To1500Ele  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*tree1000To1500Ele = HistFuncs::makeChain("egRegTree",results1000To1500Ele+outputName1000To1500Ele,1,1,1);
   TTree*tree1000To1500EleFriend = HistFuncs::makeChain("egRegTreeFriend",results1000To1500Ele+outputName1000To1500Ele,1,1,1);
   tree1000To1500Ele->AddFriend(tree1000To1500EleFriend);

   std::string results1500To3000Ele = resultsDirectory + "resultsPt1500To3000Ele/";
   std::string outputName1500To3000Ele  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*tree1500To3000Ele = HistFuncs::makeChain("egRegTree",results1500To3000Ele+outputName1500To3000Ele,1,1,1);
   TTree*tree1500To3000EleFriend = HistFuncs::makeChain("egRegTreeFriend",results1500To3000Ele+outputName1500To3000Ele,1,1,1);
   tree1500To3000Ele->AddFriend(tree1500To3000EleFriend);

   // Run3_2021 QCD Samples
   std::string resultsQCD30To50 = resultsDirectory + "resultsQCD/";
   std::string outputNameQCD30To50  = "regQCD30to50EcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeQCD30To50 = HistFuncs::makeChain("egRegTree",resultsQCD30To50+outputNameQCD30To50,1,1,1);
   TTree*treeQCD30To50Friend = HistFuncs::makeChain("egRegTreeFriend",resultsQCD30To50+outputNameQCD30To50,1,1,1);
   treeQCD30To50->AddFriend(treeQCD30To50Friend);

   std::string resultsQCD300ToInf = resultsDirectory + "resultsQCD/";
   std::string outputNameQCD300ToInf  = "regQCD300toInfEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treeQCD300ToInf = HistFuncs::makeChain("egRegTree",resultsQCD300ToInf+outputNameQCD300ToInf,1,1,1);
   TTree*treeQCD300ToInfFriend = HistFuncs::makeChain("egRegTreeFriend",resultsQCD300ToInf+outputNameQCD300ToInf,1,1,1);
   treeQCD300ToInf->AddFriend(treeQCD300ToInfFriend);

   std::string resultsAllEle = resultsDirectory + "resultsAllEnergiesEle/";
   std::string outputNameAllEle  = "regEleEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_results.root";
   TTree*treeAllEle = HistFuncs::makeChain("egRegTree",resultsAllEle+outputNameAllEle,1,1,1);
   TTree*treeAllEleFriend = HistFuncs::makeChain("egRegTreeFriend",resultsAllEle+outputNameAllEle,1,1,1);
   treeAllEle->AddFriend(treeAllEleFriend);

   // Run3_2021 High energy photons 
   std::string results1000To1500Pho = resultsDirectory + "resultsPt1000To1500Pho/";
   // root file misnamed, but leavin this for now
   std::string outputName1000To1500Pho  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_results.root";
   TTree*tree1000To1500Pho = HistFuncs::makeChain("egRegTree",results1000To1500Pho+outputName1000To1500Pho,1,1,1);
   TTree*tree1000To1500PhoFriend = HistFuncs::makeChain("egRegTreeFriend",results1000To1500Pho+outputName1000To1500Pho,1,1,1);
   tree1000To1500Pho->AddFriend(tree1000To1500PhoFriend);

   std::string results1500To3000Pho = resultsDirectory + "resultsPt1500To3000Pho/";
   std::string outputName1500To3000Pho  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_results.root";
   TTree*tree1500To3000Pho = HistFuncs::makeChain("egRegTree",results1500To3000Pho+outputName1500To3000Pho,1,1,1);
   TTree*tree1500To3000PhoFriend = HistFuncs::makeChain("egRegTreeFriend",results1500To3000Pho+outputName1500To3000Pho,1,1,1);
   tree1500To3000Pho->AddFriend(tree1500To3000PhoFriend);

   std::string results3000To4000Pho = resultsDirectory + "resultsPt3000To4000Pho/";
   std::string outputName3000To4000Pho  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_results.root";
   TTree*tree3000To4000Pho = HistFuncs::makeChain("egRegTree",results3000To4000Pho+outputName3000To4000Pho,1,1,1);
   TTree*tree3000To4000PhoFriend = HistFuncs::makeChain("egRegTreeFriend",results3000To4000Pho+outputName3000To4000Pho,1,1,1);
   tree3000To4000Pho->AddFriend(tree3000To4000PhoFriend);

   std::string resultsAllPho = resultsDirectory + "resultsAllEnergiesPho/";
   std::string outputNameAllPho  = "regEleEcalTrk2021Run3_RealIC_stdVar_stdCuts_ntrees1500_results.root";
   TTree*treeAllPho = HistFuncs::makeChain("egRegTree",resultsAllPho+outputNameAllPho,1,1,1);
   TTree*treeAllPhoFriend = HistFuncs::makeChain("egRegTreeFriend",resultsAllPho+outputNameAllPho,1,1,1);
   treeAllPho->AddFriend(treeAllPhoFriend);

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
