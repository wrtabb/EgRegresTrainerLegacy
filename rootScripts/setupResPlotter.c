 {
    //binning
    std::vector<double> puBins = {0,10,20,30,40,50,60,70};
    std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
    std::vector<double> etaBins2p5 = {-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5};
    std::vector<double> etaBins3 = {-3.0,-2.5,-2.0,-1.5666,-1.4442,-1.0,-0.5,0.0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
    std::vector<double> absEtaBins = {0.0,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
    std::vector<double> absEtaEB = {0.0,0.5,1.0,1.4442};
    std::vector<double> absEtaEE = {1.566,2.0,2.5,3.0};
    std::vector<double> absEtaEEdiff = {1.566,1.75,2.0,2.4,2.65,3.0};
    std::vector<double> absEtaEE2 = {1.566,1.75,2.0,2.25,2.5,2.75,3.0};
    std::vector<double> absEtaExt = {2.5,2.6,2.7,2.8,2.9,3.0};
    std::vector<double> ptOneBin = {1,500}; 
    std::vector<double> ptOneBinHE = {1000,5000}; 

    std::vector<double> etaBinsFine 
        = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4442,1.566,1.8,2.0,2.2,2.4,2.6};
    std::vector<double> etBinsLow    = {1,100,200,300,400,500};
    std::vector<double> etBinsHigh    = {1000,3000,4000,5000};

    //suppressing noisy fits
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
    RooMsgService::instance().setSilentMode(true);
    gErrorIgnoreLevel = kError;

    //-----trees-----//

    //Directories for making trees
    std::string resultsDirectory = "/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/regressions/EtaExtended/";
    std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/Run3/2022/EtaExtendedEle/";
    std::string inputName = "DoubleElectron_FlatPt-500To5000_13p6TeV_Run3Winter22DR-FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2_AODSIM.root";

    std::string filename = "input.root";

    // 12_2_HE 
    std::string results1 = resultsDirectory + "12_2_HE/";
    TTree*tree1 = HistFuncs::makeChain("egRegTree",results1+filename,1,1,1);
    TTree*tree1Friend = HistFuncs::makeChain("egRegTreeFriend",results1+filename,1,1,1);
    tree1->AddFriend(tree1Friend);

    // 12_2_LE 
    std::string results2 = resultsDirectory + "12_2_LE/";
    TTree*tree2 = HistFuncs::makeChain("egRegTree",results2+filename,1,1,1);
    TTree*tree2Friend = HistFuncs::makeChain("egRegTreeFriend",results2+filename,1,1,1);
    tree2->AddFriend(tree2Friend);

    // 12_0_HE 
    std::string results3 = resultsDirectory + "12_0_HE/";
    TTree*tree3 = HistFuncs::makeChain("egRegTree",results3+filename,1,1,1);
    TTree*tree3Friend = HistFuncs::makeChain("egRegTreeFriend",results3+filename,1,1,1);
    tree3->AddFriend(tree3Friend);

    // 12_0_LE
    std::string results4 = resultsDirectory + "12_0_LE/";
    TTree*tree4 = HistFuncs::makeChain("egRegTree",results4+filename,1,1,1);
    TTree*tree4Friend = HistFuncs::makeChain("egRegTreeFriend",results4+filename,1,1,1);
    tree4->AddFriend(tree4Friend);

    // 12_2_LE ideal and real ICs
    std::string results5 = resultsDirectory + "12_2_LE_ideal_and_real/";
    TTree*tree5 = HistFuncs::makeChain("egRegTree",results5+filename,1,1,1);
    TTree*tree5Friend = HistFuncs::makeChain("egRegTreeFriend",results5+filename,1,1,1);
    tree5->AddFriend(tree5Friend);

    // 12_2_HE ideal and real ICs
    std::string results6 = resultsDirectory + "12_2_HE_ideal_and_real/";
    TTree*tree6 = HistFuncs::makeChain("egRegTree",results6+filename,1,1,1);
    TTree*tree6Friend = HistFuncs::makeChain("egRegTreeFriend",results6+filename,1,1,1);
    tree6->AddFriend(tree6Friend);

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
