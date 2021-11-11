
void plot(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);

void plotRun3Pho()
{
 //-----parameters-----//
 //Which plots to plot
 bool etaPlot = true;
 bool puPlot  = true;
 bool ePlot   = true;

 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = false;

// gSystem->Exec("gmake RegressionTrainerExe -j 8");
// gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupResPlotter.c");

 plot(etaPlot,puPlot,ePlot,dcbFit);
}

void plot(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::CRUIJF)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res.makeHists({treePhoStep3,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>2\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins3)");
  gROOT->ProcessLine("res.printFits({0,2},\"../plots/Run3/Photons/CRUIJF_Eta_\")");
 }
 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res.makeHists({treePhoStep3,nullptr},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>2\",\"mc.pt\",\"nrVert\",etBins,puBins)");
  gROOT->ProcessLine("res.printFits({0,2},\"../plots/Run3/Photons/CRUIJF_PU_EB_\")");

  gROOT->ProcessLine("res.makeHists({treePhoStep3,nullptr},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>2\",\"mc.pt\",\"nrVert\",etBins,puBins)");
  gROOT->ProcessLine("res.printFits({0,2},\"../plots/Run3/Photons/CRUIJF_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res.makeHists({treePhoStep3,nullptr},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>2\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({0,2},\"../plots/Run3/Photons/CRUIJF_Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treePhoStep3,nullptr},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>2\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({0,2},\"../plots/Run3/Photons/CRUIJF_Et_EE_\")");
 }
}
