enum PlotVariable{
	ETA,
	PU_EB,
	PU_EE,
	ET_EB,
	ET_EE,
	ET_ETA
};
enum PlotObject{
	ELE,
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
//		ELE,
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
		ELE_ALL_ENERGY,
//		PHO_ALL_ENERGY
	};
	int nObjects = plotObj.size();

	// list of variables to plot
	vector<PlotVariable> plotVar = {
//		ETA,
//		PU_EB,
//		PU_EE,
//		ET_EB,
//		ET_EE,
		ET_ETA
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

	TString baseCuts = "mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0";
	TString treeName1;
	TString treeName2 = "nullptr";
	TString puBinning,etBinning,etaBinning,oneBinRange,saveLoc,fitsArg;

	// Object settings
	if(plotObj == ELE){
		treeName1 = "treeEleStep4";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/Electrons/Ele";
		fitsArg = "0,1";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == PHO){
		treeName1 = "treePhoStep3";
		baseCuts += " && pho.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/Photons/Pho";
		fitsArg = "0,2";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == SC){
		treeName1 = "treeSCStep3";
		baseCuts += " && sc.et>0";	
		etBinning = "etBinsLow";
		oneBinRange = "ptOneBinLow";
		saveLoc = "/Superclusters/SC";
		fitsArg = "0,3";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == QCD_30To50){
		treeName1 = "treeQCD30To50";
		baseCuts += " && ele.et>0";	
		etBinning = "ptOneBinQCDLow";
		oneBinRange = "ptOneBinQCDLow";
		saveLoc = "/QCD/QCD_30To50";
		fitsArg = "0,1";
		etaBinning = "etaBinsEBEE";
		puBinning = "puBinsQCD";
	}
	else if(plotObj == QCD_300ToInf){
		treeName1 = "treeQCD300ToInf";
		baseCuts += " && ele.et>0";	
		etBinning = "ptOneBinQCDHigh";
		oneBinRange = "ptOneBinQCDHigh";
		saveLoc = "/QCD/QCD_300ToInf";
		fitsArg = "0,1";
		etaBinning = "etaBinsEBEE";
		puBinning = "puBinsQCD";
	}
	else if(plotObj == ELE_500To1000){
		treeName1 = "tree500To1000Ele";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsMedium";
		oneBinRange = "ptOneBinMedium";
		saveLoc = "/Electrons_HighEnergy/Pt500to1000";
		fitsArg = "0,1";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == ELE_1000To1500){
		treeName1 = "tree1000To1500Ele";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsHigh";
		oneBinRange = "ptOneBinHigh";
		saveLoc = "/Electrons_HighEnergy/Pt1000to1500";
		fitsArg = "0,1";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == ELE_1500To3000){
		treeName1 = "tree1500To3000Ele";
		baseCuts += " && ele.et>0";	
		etBinning = "etBinsUltra";
		oneBinRange = "ptOneBinUltra";
		saveLoc = "/Electrons_HighEnergy/Pt1500to3000";
		fitsArg = "0,1";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == PHO_1000To1500){
		treeName1 = "tree1000To1500Pho";
		baseCuts += " && pho.et>0";	
		etBinning = "etBinsHigh";
		oneBinRange = "ptOneBinHigh";
		saveLoc = "/Photons_HighEnergy/Pt1000to1500";
		fitsArg = "0,2";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == PHO_1500To3000){
		treeName1 = "tree1500To3000Pho";
		baseCuts += " && pho.et>0";	
		etBinning = "etBinsUltra";
		oneBinRange = "ptOneBinUltra";
		saveLoc = "/Photons_HighEnergy/Pt1500to3000";
		fitsArg = "0,2";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == PHO_3000To4000){
		treeName1 = "tree3000To4000Pho";
		baseCuts += " && pho.et>0";	
		etBinning = "etBinsSuper";
		oneBinRange = "ptOneBinSuper";
		saveLoc = "/Photons_HighEnergy/Pt3000to4000";
		fitsArg = "0,2";
		etaBinning = "etaBins";
		puBinning = "puBins";
	}
	else if(plotObj == ELE_ALL_ENERGY){
		treeName1 = "treeAllEle";
		baseCuts += " && ele.et>0";	
		saveLoc = "/Electrons_HighEnergy_NoECALTrk/Electrons_";
		fitsArg = "0,1";
	}
	else if(plotObj == PHO_ALL_ENERGY){
		treeName1 = "treeAllPho";
		baseCuts += " && ele.et>0";	
		saveLoc = "/Photons_AllEnergy/Photons";
		fitsArg = "0,2";
	}
        
	// Variable settings
	if(plotVar==ETA){
		var1 	 = "mc.pt";
		binning1 = etBinning;
		var2 	 = "sc.seedEta";
		binning2 = etaBinning;
		saveTag  = "Eta";
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
