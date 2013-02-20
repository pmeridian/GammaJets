{
  gROOT->ProcessLine(".L fillPlot2012_gammaJets.C++");
  gROOT->ProcessLine(".L finalize2012_gammaJets.C++");
  
  // luminosita' 2012 in pb 
  float lumi2012=60.;               // 50 ID + ISO  
  // float lumi2012=124.176;        // 75 ID + ISO      
  // float lumi2012=5334.23;        // 150 

  // tagli   
  float ptlead = 60.;
  
  // nominale 
  finalize2012_gammaJets(lumi2012,ptlead,0,0,"nvtx","nvtx",20,0.,40.,"# vtx"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"mass","mass",40,0.,200.,"m(#gamma #gamma))"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"etaL","etaL",15,-3.,3.,"#eta leading #gamma"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"ptL","ptL",50,0.,300.,"pt leading #gamma"); 
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"ngamma",    "ngamma",    10,0.,10,  "# #gamma");  
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"sigmaIeIe", "sigmaIeIe", 50,0.,0.05,"#sigma I#eta I#eta");  
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"HoE",       "HoE",       50,0.,0.2,"H/E");       
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"chargedIso","chargedIso",22,0.,11.,"charged PF isolation");    
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"neutralIso","neutralIso",22,0.,11.,"neutral PF isolation");         
  // finalize2012_gammaJets(lumi2012,ptlead,0,0,"gammaIso",  "gammaIso",  22,0.,11.,"photons PF isolation");       
}
