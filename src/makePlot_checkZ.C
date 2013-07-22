{
  gROOT->ProcessLine(".L fillPlot2012_gammaJets.C++");
  gROOT->ProcessLine(".L finalize2012_gammaJets_checkZ.C++");

  // luminosita' 2012 per HLT - ID + iso
  float lumi2012_HLT30 = 2.97236;   
  float lumi2012_HLT50 = 60.0473;
  float lumi2012_HLT75 = 124.176;
  float lumi2012_HLT90 = 377.529;

  // tagli   
  float ptlead30min = 40.;
  float ptlead50min = 65.;
  float ptlead75min = 90.;
  float ptlead90min = 105.;
  // 
  float ptlead30max = 65.;
  float ptlead50max = 90.;
  float ptlead75max = 105.;
  float ptlead90max = 200000.;
  
  // nominale 
  finalize2012_gammaJets_checkZ(lumi2012_HLT30,lumi2012_HLT50,lumi2012_HLT75,lumi2012_HLT90,ptlead30min,ptlead50min,ptlead75min,ptlead90min,ptlead30max,ptlead50max,ptlead75max,ptlead90max,0,0,"nvtx","nvtx",20,0.,40.,"# vtx"); 
  finalize2012_gammaJets_checkZ(lumi2012_HLT30,lumi2012_HLT50,lumi2012_HLT75,lumi2012_HLT90,ptlead30min,ptlead50min,ptlead75min,ptlead90min,ptlead30max,ptlead50max,ptlead75max,ptlead90max,0,0,"ptL","ptL",12,0.,120.,"p_{T} leading photon [GeV]"); 
  // finalize2012_gammaJets_checkZ(lumi2012_HLT30,lumi2012_HLT50,lumi2012_HLT75,lumi2012_HLT90,ptlead30min,ptlead50min,ptlead75min,ptlead90min,ptlead30max,ptlead50max,ptlead75max,ptlead90max,0,0,"etaL","etaL",15,-3.,3.,"#eta_{T} leading photon [GeV]"); 
  // finalize2012_gammaJets_checkZ(lumi2012_HLT30,lumi2012_HLT50,lumi2012_HLT75,lumi2012_HLT90,ptlead30min,ptlead50min,ptlead75min,ptlead90min,ptlead30max,ptlead50max,ptlead75max,ptlead90max,0,0,"ngamma","ngamma",10,0.,10.,"# photons"); 
}
