 {
    //binning
    std::vector<double> puBins = {0,10,20,30,40,50,60,70};
    std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
    std::vector<double> etaBins2p5 = {-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5};
    std::vector<double> etaBins3 = {-3.0,-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
    std::vector<double> absEtaExt = {2.5,2.6,2.7,2.8,2.9,3.0};
    std::vector<double> ptOneBin = {1,500}; 

    std::vector<double> etaBinsFine 
        = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4442,1.566,1.8,2.0,2.2,2.4,2.6};
    std::vector<double> etBinsLow    = {1,100,200,300,400,500};

    //suppressing noisy fits
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
    RooMsgService::instance().setSilentMode(true);
    gErrorIgnoreLevel = kError;

    //-----trees-----//

    //Directories for making trees
    std::string resultsDirectory = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/";
    std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/Run3_2021/EtaExtendedEle";

    // Run3_2021 Extended Eta Electrons 
    std::string resultsEle = resultsDirectory + "Run3ExtendedEtaEle/";
    std::string step3NameEle  = "regEleEcalRun3_EtaExtendedElectrons_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
    std::string step4NameEle  = "regEleEcalTrkRun3_EtaExtendedElectrons_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
    TTree*treeEleStep4 = HistFuncs::makeChain("egRegTree",resultsEle+step3NameEle,1,1,1);
    TTree*treeEleStep4Friend = HistFuncs::makeChain("egRegTreeFriend",resultsEle+step4NameEle,1,1,1);
    treeEleStep4->AddFriend(treeEleStep4Friend);

    TTree*treeEleStep3 = HistFuncs::makeChain("egRegTree",resultsEle+step3NameEle,1,1,1);
    TTree*treeEleStep3Friend = HistFuncs::makeChain("egRegTreeFriend",resultsEle+step3NameEle,1,1,1);
    treeEleStep3->AddFriend(treeEleStep3Friend);

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
