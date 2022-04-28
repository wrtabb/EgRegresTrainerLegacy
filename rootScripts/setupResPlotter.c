 {
    //binning
    std::vector<double> puBins = {0,10,20,30,40,50,60,70};
    std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
    std::vector<double> etaBins2p5 = {-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5};
    std::vector<double> etaBins3 = {-3.0,-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
    std::vector<double> absEtaBins = {0.0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
    std::vector<double> absEtaEB = {0.0,0.5,1.0,1.4442};
    std::vector<double> absEtaEE = {1.566,2.0,2.5,3.0};
    std::vector<double> absEtaEE2 = {1.566,1.75,2.0,2.25,2.5,2.75,3.0};
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
    std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/Run3_2021/EtaExtendedEle/";
    std::string inputName = "etaExtendedEle.root";

    // Run3_2021 Extended Eta Electrons 
    std::string results1 = resultsDirectory + "Run3ExtendedEtaEle/";
    std::string step3Name  = "regEleEcalRun3_EtaExtendedElectrons_RealIC_RealTraining_stdVar_stdCuts_ntrees1500_applied.root";
    std::string step4Name  = "regEleEcalTrkRun3_EtaExtendedElectrons_RealIC_stdVar_stdCuts_ntrees1500_applied.root";
    TTree*treeStep4_1 = HistFuncs::makeChain("egRegTree",inputDirectory+inputName,1,1,1);
    TTree*treeStep4Friend_1 = HistFuncs::makeChain("egRegTreeFriend",results1+step4Name,1,1,1);
    treeStep4_1->AddFriend(treeStep4Friend_1);

    TTree*treeStep3_1 = HistFuncs::makeChain("egRegTree",results1+step3Name,1,1,1);
    TTree*treeStep3Friend_1 = HistFuncs::makeChain("egRegTreeFriend",results1+step3Name,1,1,1);
    treeStep3_1->AddFriend(treeStep3Friend_1);

    // Run3_2021 Extended Eta Electrons with Run3 Applied
    std::string results2 = resultsDirectory + "Run3Ele_AppliedTo_ExtEtaEle/";
    std::string step4Name2  = "run3_AppliedTo_ExtEta.root";
    TTree*treeStep4_2 = HistFuncs::makeChain("egRegTree",results2+step4Name2,1,1,1);
    TTree*treeStep4Friend_2 = HistFuncs::makeChain("egRegTreeFriend",results2+step4Name2,1,1,1);
    treeStep4_2->AddFriend(treeStep4Friend_2);

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
