enum PlotVariable{
	ETA,
    ETA_EXT,
    ETA_EB,
    ETA_EE,
	PU_EB,
	PU_EE,
	ET_EB,
	ET_EE,
	ET_ETA
};
enum PlotObject{
    COMPARE_EXT_ETA,
	ELE_STEP3,
    ELE_STEP4,
	PHO,
	SC,
	ELE_500To1000,
	ELE_1000To1500,
	ELE_1500To3000,
	PHO_1000To1500,
	PHO_1500To3000,
	PHO_3000To4000,
	QCD_30To50,
	QCD_300ToInf,
	ELE_ALL_ENERGY,
	PHO_ALL_ENERGY
};
void plot(bool dcbFit,PlotVariable plotVar,PlotObject plotObj);

void Plotter()
{
	gSystem->Exec("gmake RegressionTrainerExe -j 8");
	gSystem->Exec("gmake RegressionApplierExe -j 8");

	gROOT->ProcessLine("gROOT->SetBatch(true)");
	gROOT->ProcessLine(".x rootScripts/setupResPlotter.c");
	gROOT->ProcessLine("ResPlotter res");

	// list of physics objects to plot
	vector<PlotObject> plotObj = {
        COMPARE_EXT_ETA,
//		ELE_STEP3,
//		ELE_STEP4,
//		PHO,
//		SC,
//		ELE_500To1000,
//		ELE_1000To1500,
//		ELE_1500To3000,
//		PHO_1000To1500,
//		PHO_1500To3000,
//		PHO_3000To4000,
//		QCD_30To50,
//		QCD_300ToInf,
//		ELE_ALL_ENERGY,
//		PHO_ALL_ENERGY
	};
	int nObjects = plotObj.size();

	// list of variables to plot
	vector<PlotVariable> plotVar = {
//		ETA,
//		ETA_EXT,
//      ETA_EB,
        ETA_EE,
//		PU_EB,
//		PU_EE,
//		ET_EB,
//		ET_EE,
//		ET_ETA
	};
	int nVariables = plotVar.size();

	for(int i=0;i<nObjects;i++){
		for(int j=0;j<nVariables;j++){
			plot(false,plotVar.at(j),plotObj.at(i));
			plot(true,plotVar.at(j),plotObj.at(i));
		}
	}
}

void plot(bool dcbFit,PlotVariable plotVar,PlotObject plotObj)
{
	TString var1,var2,binning1,binning2,saveTag;
	TString fitType;

	if(dcbFit){ 
		gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");
		fitType = "DCB";
	}
	else{
		gROOT->ProcessLine("res.setFitType(ResFitter::FitType::Cruijff)");
		fitType = "CRUIJF";
	} 

	TString baseCuts = "mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && evt.eventnr%5>2";
	TString treeName1;
	TString treeName2 = "nullptr";
	TString puBinning,etBinning,etaBinning,oneBinRange,saveLoc,fitsArg;

	// Object settings
	if(plotObj == ELE_STEP3){
		treeName1 = "treeEleStep3";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/EtaExtEle/Step3_";
		fitsArg = "0,2";
		etaBinning = "absEtaExt";
		puBinning = "puBins";
	}
	else if(plotObj == ELE_STEP4){
		treeName1 = "treeEleStep4";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/EtaExtEle/Step4_";
		fitsArg = "1,2";
		etaBinning = "absEtaExt";
		puBinning = "puBins";
	}
	else if(plotObj == COMPARE_EXT_ETA){
		treeName1 = "treeStep4_1";
		treeName2 = "treeStep4_2";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/ExtendedEta/diffBinning/LE/Step4_";
		fitsArg = "2,5";
	}
        
	// Variable settings
	else if(plotVar==ETA_EE){
		var1 	 = "mc.pt";
		binning1 = etBinning;
		var2 	 = "abs(sc.seedEta)";
		binning2 = "absEtaEE2";
		saveTag  = "EtaExtEE";
	}
	else if(plotVar==PU_EB){
		var1 	 = "mc.pt";
		binning1 = etBinning;
		var2 	 = "nrVert";
		binning2 = puBinning;
		saveTag  = "PU_EB";
		baseCuts += " && abs(sc.seedEta)<1.442";
	}
	else if(plotVar==PU_EE){
		var1 	 = "mc.pt";
		binning1 = etBinning;
		var2 	 = "nrVert";
		binning2 = puBinning;
		saveTag  = "PU_EE";
		baseCuts += " && abs(sc.seedEta)>1.566";
	}
	else if(plotVar==ET_EB){
		var1 	 = "mc.pt";
		binning1 = oneBinRange;
		var2 	 = "mc.pt";
		binning2 = etBinning;
		saveTag  = "PU_EE";
		baseCuts += " && abs(sc.seedEta)<1.442";
	}
	else if(plotVar==ET_EE){
		var1 	 = "mc.pt";
		binning1 = oneBinRange;
		var2 	 = "mc.pt";
		binning2 = etBinning;
		saveTag  = "PU_EE";
		baseCuts += " && abs(sc.seedEta)>1.566";
	}
	else if(plotVar==ET_ETA){
		var1 	 = "sc.seedEta";
		binning1 = "etaBins";
		var2 	 = "mc.pt";
		binning2 = "etBinsHEEle";
		saveTag  = "EtEta";
	}
	else{
		cout << "PLOTTING ERROR: plotVar not correctly chosen" << endl;	
		return;
	}

	TString printFits = "res.printFits({"+fitsArg+"},\"plots/Run3"+saveLoc+"_"+fitType+"_"+saveTag+"_\")";
	TString makeHists = "res.makeHists({"+treeName1+","+treeName2+"},\"\",\""+baseCuts+"\",\""+var1+"\",\""+var2+"\","+binning1+","+binning2+")";
	gROOT->ProcessLine(makeHists);
	gROOT->ProcessLine(printFits);

}
