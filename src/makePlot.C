{
  gROOT->ProcessLine(".L fillPlot2012_gammaJets.C++");
  gROOT->ProcessLine(".L finalize2012_gammaJets.C++");
  
  // luminosita' 2012
  float lumi2012=9300.;  

  // tagli
  float ptlead = 30.;

  // nominale 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"nvtx","nvtx",40,0.,40.,"# vtx"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"sigmaIeIe", "sigmaIeIe", 50,0.,0.1,"#sigma I#eta I#eta"); 
  finalize2012_gammaJets(lumi2012,ptlead,0,0,"trackerIso","trackerIso",22,0.,11.,"tracker isolation"); 
  finalize2012_gammaJets(lumi2012,ptlead,0,0,"ecalIso",   "ecalIso",   22,0.,11.,"ECAL isolation"); 
  finalize2012_gammaJets(lumi2012,ptlead,0,0,"hcalIso",   "hcalIso",   22,0.,11.,"HCAL isolation"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"chargedIso","chargedIso",22,0.,11.,"charged PF isolation"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"neutralIso","neutralIso",22,0.,11.,"neutral PF isolation"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"gammaIso",  "gammaIso",  22,0.,11.,"photons PF isolation"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"pfIso",     "pfIso",     22,0.,11.,"PF isolation"); 
  finalize2012_gammaJets(lumi2012,ptlead,0,0,"HoE",       "HoE",       50,0.,0.2,"H/E"); 
}
