 {
   //binning
   std::vector<double> puBins = {0,10,20,30,40,50,60,70,80};
   std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
   std::vector<double> etaBins = {0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.,2.25,2.5};//,2.75,3.0}
   std::vector<double> etaBins2p5 = {-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5};//,2.75,3.0}
   std::vector<double> etaBinsPho = {0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.,2.25,2.5,2.75,3.0};
   std::vector<double> etBins = {5,15,30,50,100,150,300};
   std::vector<double> etBins100 = {5,15,30,50,100};
   std::vector<double> etBinsPho = {10,20,30,50,100,150,300};
   std::vector<double> etBinsSC = {25,40,50,60};
   std::vector<double> ptOneBin = {5,500}; 
   //std::vector<double> etBins = {10,20,30,50,75,100,125,150,200,250,300};
   std::vector<double> etBinsVs = {5,10,15,20,25,30,35,40,45,50,60,65,70,75,80,85,90,95,100,120,140,160,180,200,220,240,260,280,300};
   std::vector<double> etBinsVsPho = {5,50,100,150,200,250,300,350,400,450,500};
   
   std::vector<double> etBinsMedium = {300,400,500,600,700,800,900,1000};
   std::vector<double> etBinsEleHigh = {1000,1100,1200,1300,1400,1500};
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
   std::string step3Name  = "regPhoEcal2021Run3_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
   TTree*treePhoStep3 = HistFuncs::makeChain("egRegTree",resultsPho+step3Name,1,1,1);
   TTree*treePhoStep3Friend = HistFuncs::makeChain("egRegTreeFriend",resultsPho+step3Name,1,1,1);
   treePhoStep3->AddFriend(treePhoStep3Friend);

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
