#include "interface/GammaJetsSelection.h"
#include "interface/JSON.h"
#include <TH2.h>
#include <TStyle.h>
#include <TString.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <TLorentzVector.h>

#define MAX_PU_REWEIGHT 60

using namespace std;

GammaJetsSelection::GammaJetsSelection(TTree *tree, const TString& outname) : tree_reader(tree), jsonFile(0) {

  hOutputFile = TFile::Open(outname, "RECREATE" ) ;
}

inline double delta_phi(double phi1, double phi2) {

  double dphi = TMath::Abs(phi1 - phi2);
  return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
}

inline double delta_eta(double eta1, double eta2) {
  
  return (eta2 >= 0 ? eta1 - eta2 : eta2 - eta1);
}

GammaJetsSelection::~GammaJetsSelection() {
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
}

vector<int> GammaJetsSelection::firstones(Float_t *vec, vector<bool> *asso, int number){
  
  vector<int> themax;
  
  for(int j=0; j<number; j++) {
    double maxtemp(-999); 
    int idmaxtemp(-999);
    
    for (int i=0; i<int(asso->size()); i++) {
      bool skip(0);
      for(int ss=0; ss<j; ss++) { 
	if ( i == themax.at(ss) )   
	  skip = 1;
      }
      if ( vec[i] > maxtemp && asso->at(i) && !skip) {
	maxtemp = vec[i];
	idmaxtemp = i;
      }
    }
    themax.push_back(idmaxtemp);
  }
  return themax;
}

void GammaJetsSelection::Loop() {

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  JSON* myjson=0;
  if (jsonFile) {
    std::cout << "Reading JSON" << jsonFile << std::endl;
    myjson=new JSON(jsonFile);
  }
  
  hOutputFile->cd();   
  TH1D ptphotgen1("ptphotgen1","ptphotgen1", 100, 0.,300.);
  

  // ------------------------------------------------------------
  // Output tree initialization
  ana_tree = new TTree ("AnaTree","Reduced tree for final analysis") ;
  // general
  ana_tree->Branch("run",&runRN,"run/I");
  ana_tree->Branch("event",&eventRN,"event/I");
  ana_tree->Branch("nvtx",&nvtx,"nvtx/F");
  ana_tree->Branch("rhoPF",&rhoPFRN,"rhoPF/F");
  ana_tree->Branch("rhoAllJets",&rhoAllJetsRN,"rhoAllJets/F");
  ana_tree->Branch("npu",&npu,"npu/I");
  ana_tree->Branch("pu_weight",&pu_weight,"pu_weight/F");
  // gen level
  ana_tree->Branch("gen_pt_gamma1",  &gen_pt_gamma1,  "gen_pt_gamma1/F");
  ana_tree->Branch("gen_eta_gamma1", &gen_eta_gamma1, "gen_eta_gamma1/F");
  ana_tree->Branch("gen_phi_gamma1", &gen_phi_gamma1, "gen_phi_gamma1/F");
  // jets
  ana_tree->Branch("njets",       &njets,      "njets/I");
  ana_tree->Branch("ecorrjet",    ecorrjet,    "ecorrjet[njets]/F");
  ana_tree->Branch("ptjet",       ptjet,       "ptjet[njets]/F");
  ana_tree->Branch("ptcorrjet",   ptcorrjet,   "ptcorrjet[njets]/F");
  ana_tree->Branch("etajet",      etajet,      "etajet[njets]/F");
  ana_tree->Branch("phijet",      phijet,      "phijet[njets]/F");
  ana_tree->Branch("betajet",     betajet,     "betajet[njets]/F");
  ana_tree->Branch("betastarjet", betastarjet, "betastarjet[njets]/F");
  ana_tree->Branch("rmsjet",      rmsjet,      "rmsjet[njets]/F");
  // gammas
  ana_tree->Branch("ptphot1",&ptphot1,"ptphot1/F");
  ana_tree->Branch("etaphot1",&etaphot1,"etaphot1/F");
  ana_tree->Branch("phiphot1",&phiphot1,"phiphot1/F");
  ana_tree->Branch("etascphot1",&etascphot1,"etascphot1/F");
  ana_tree->Branch("E1phot1",&E1phot1,"E1phot1/F");
  ana_tree->Branch("E9phot1",&E9phot1,"E9phot1/F");
  ana_tree->Branch("r9phot1",&r9phot1,"r9phot1/F");
  ana_tree->Branch("deltaRToTrackphot1",&deltaRToTrackphot1,"deltaRToTrackphot1/F");
  ana_tree->Branch("pid_haspixelseedphot1",&pid_haspixelseedphot1,"pid_haspixelseedphot1/I");
  ana_tree->Branch("pid_HoverEphot1",&pid_HoverEphot1,"pid_HoverEphot1/F");
  ana_tree->Branch("pid_sigmaIeIephot1",&pid_sigmaIeIephot1,"pid_sigmaIeIephot1/F");
  ana_tree->Branch("pid_hlwTrack04phot1",&pid_hlwTrack04phot1,"pid_hlwTrack04phot1/F");
  ana_tree->Branch("pid_jurECAL04phot1",&pid_jurECAL04phot1,"pid_jurECAL04phot1/F");
  ana_tree->Branch("pid_twrHCAL04phot1",&pid_twrHCAL04phot1,"pid_twrHCAL04phot1/F");
  ana_tree->Branch("pid_hasMatchedConvphot1",&pid_hasMatchedConvphot1,"pid_hasMatchedConvphot1/I");
  ana_tree->Branch("pid_hasMatchedPromptElephot1",&pid_hasMatchedPromptElephot1,"pid_hasMatchedPromptElephot1/I");
  ana_tree->Branch("pid_pfIsoCharged03phot1",&pid_pfIsoCharged03phot1,"pid_pfIsoCharged03phot1/F");  
  ana_tree->Branch("pid_pfIsoPhotons03phot1",&pid_pfIsoPhotons03phot1,"pid_pfIsoPhotons03phot1/F");  
  ana_tree->Branch("pid_pfIsoNeutrals03phot1",&pid_pfIsoNeutrals03phot1,"pid_pfIsoNeutrals03phot1/F"); 
  ana_tree->Branch("pid_pfIsoCharged04phot1",&pid_pfIsoCharged04phot1,"pid_pfIsoCharged04phot1/F");  
  ana_tree->Branch("pid_pfIsoPhotons04phot1",&pid_pfIsoPhotons04phot1,"pid_pfIsoPhotons04phot1/F");  
  ana_tree->Branch("pid_pfIsoNeutrals04phot1",&pid_pfIsoNeutrals04phot1,"pid_pfIsoNeutrals04phot1/F"); 
  // vtx
  ana_tree->Branch("vtxId",   &vtxId,   "vtxId/I");
  ana_tree->Branch("vtxPos_x",&vtxPos_x,"vtxPos_x/F");
  ana_tree->Branch("vtxPos_y",&vtxPos_y,"vtxPos_y/F");
  ana_tree->Branch("vtxPos_z",&vtxPos_z,"vtxPos_z/F");
  // triggering paths
  ana_tree->Branch("nHLT",           &nHLT,        "nHLT/I");
  ana_tree->Branch("allHLTNames",    &aHLTNames);
  ana_tree->Branch("allHLTResults",  &aHLTResults);


  // ------------------------------------------------------------  
  // Other initializations
  // temp varables to keep track of the file being processed
  TString foldname("");
  TString currfilename("");
  int ifile(0);
  int nfiles = ((TChain*)fChain)->GetListOfFiles()->GetEntries();
  
  
  // ------------------------------------------------------------  
  // Loop over entries
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   
    nbytes += nb;
    
    // good LSs only
    if (myjson && nMC<=0) 
      if (!myjson->isGoodLS(run,lbn)) continue;
    
    // print name of current file
    currfilename = TString(fChain->GetCurrentFile()->GetName());
    if(currfilename != foldname) {
      ifile++;
      cout << "Opening file " << ifile << " of "  << nfiles << "\n"
	   << currfilename  << "\n"
	   << "------------------------------"
	   << endl;
      foldname = currfilename;
    }

    // pu (and other) weights
    npu = pu_n;
    if(npu<MAX_PU_REWEIGHT && puweights_.size()>0 && nMC>0) 
      pu_weight = puweights_[npu];
    else
      pu_weight = 1;

    weight=pu_weight;
    
    // skip events where the number of jets, photons, and vertexes is above the maximum allowed value
    if (nPhot>30) {
      cout << "number of photons = " << nPhot << " and above threshold of 30; skipping" << endl;
      continue;
    }
    if (nJet_pfakt5 > 200) {
      cout << "number of nJet_pfakt5 = " << nJet_pfakt5 << " and above threshold of 200; skipping" << endl;
      continue;
    }
    if (nvertex > MAX_PU_REWEIGHT) {
      cout << "number of nvertex = " << nvertex << " and above threshold of " << MAX_PU_REWEIGHT << "; skipping" << endl;
      continue;
    }
    

    // ----------------------------------------------
    // gen level analysis

    // init of mc related variables
    vector<bool> photassocMC;
    for(int i=0; i<nMC; i++) {
      if(pdgIdMC[i] == 22 && statusMC[i] == 3){
	photassocMC.push_back(1);	
      }
      else
	photassocMC.push_back(0);
    }
   
    // gen level gammas 
    vector<int> firstfourgenphot = firstones(ptMC,&photassocMC,4);
    
    // filling the output tree with gen level info
    vector<int>* genPhotPtr = &firstfourgenphot;
    int index_phot1;
    if (firstfourgenphot.size()>=1) {
      index_phot1    = genPhotPtr->at(0);
      gen_pt_gamma1  = ptMC[index_phot1];
      gen_eta_gamma1 = etaMC[index_phot1];
      gen_phi_gamma1 = phiMC[index_phot1];
    }
    if (firstfourgenphot.size()==0) {
      gen_pt_gamma1  = -999.;
      gen_eta_gamma1 = -999.;
      gen_phi_gamma1 = -999.;
    }
    
    // to be used at analysis level
    ptphotgen1.Fill(ptMC[firstfourgenphot.at(0)],weight);    



    // ----------------------------------------------
    // reco level analysis

    // 1) vertex ==> we assume the correct one is vtx0 - chiara
    vtxId=0;
    vtxPos_x=vx[0];
    vtxPos_y=vy[0];
    vtxPos_z=vz[0];
    

    // 2) reco photons
    vector<bool> assophot;
    vector<bool> isophot;
    
    // montecarlo association with gen gammas 
    for(int i=0; i<nPhot; i++) {
      bool assp(0);
      for(int j=0; j<nMC; j++){
	double DR;
	if(photassocMC.at(j)){
	  DR = sqrt(delta_eta(etaPhot[i],etaMC[j])*delta_eta(etaPhot[i],etaMC[j]) + delta_phi(phiPhot[i],phiMC[j])*delta_phi(phiPhot[i],phiMC[j]) ) ;
	  if(DR < .01 ) assp = 1; 
	}
      }
      if(assp) assophot.push_back(1);   
      else assophot.push_back(0);  
          
      // preselection - chiara, ancora da vedere, per il momento metto solo pT ed eta cuts
      // + ele veto semplice del 2011. Da cambiare
      bool preselection = true;  
      if (ptPhot[i]<30) preselection = false;
      if (fabs(etascPhot[i])>1.4442 && fabs(etascPhot[i])<1.566) preselection = false;
      if (fabs(etascPhot[i])>2.5) preselection = false;
      if (hasPixelSeedPhot[i]) preselection = false;   // chiara: andra' cambiata in una piu' sensata dopo
      if (preselection) isophot.push_back(1); 
      else isophot.push_back(0);  
    }
    vector<int> firstfourassphot = firstones(ptPhot,&assophot,4);
    vector<int> firstfourisophot = firstones(ptPhot,&isophot,4);      


    // 3) reco jets and cleaning from photons
    vector<bool> jetnoassphot;            // jets passing PU Id and not matched with gen-level gammas
    vector<bool> jetgoodnoisophot;        // jets passing PU Id and not matched with reco gammas passing the preselection
    jetnoisophot.clear();                 // jets not matched with reco gammas passing the preselection
	
    for(int i=0; i<nJet_pfakt5; i++){
      bool assp(0);
      bool assi(0);
      
      // match jets / photons
      double DR;
      DR = sqrt(delta_eta(etaJet_pfakt5[i],etaPhot[firstfourassphot.at(0)])*delta_eta(etaJet_pfakt5[i],etaPhot[firstfourassphot.at(0)]) + 
		delta_phi(phiJet_pfakt5[i],phiPhot[firstfourassphot.at(0)])*delta_phi(phiJet_pfakt5[i],phiPhot[firstfourassphot.at(0)]) ) ;
      if( DR < .5 ) assp = 1;   // with gen gammas 
      
      DR = sqrt(delta_eta(etaJet_pfakt5[i],etaPhot[firstfourisophot.at(0)])*delta_eta(etaJet_pfakt5[i],etaPhot[firstfourisophot.at(0)]) + 
		delta_phi(phiJet_pfakt5[i],phiPhot[firstfourisophot.at(0)])*delta_phi(phiJet_pfakt5[i],phiPhot[firstfourisophot.at(0)]) ) ;
      if( DR < .5 ) assi = 1;   // with preselected gammas

      // good jets - passing cut based PU ID 
      bool goodetajet(1);
      if(TMath::Abs(etaJet_pfakt5[i]) > 4.7) goodetajet = 0;  
      if(TMath::Abs(etaJet_pfakt5[i]) < 2.5) {
	if(betaStar_pfakt5[i][0] > 0.2 * log( nvertex - 0.67 ) ) goodetajet = 0;   // chiara: vtx 0
	if(rmsCandJet_pfakt5[i] > 0.06) goodetajet = 0;
      } else if(TMath::Abs(etaJet_pfakt5[i]) < 3){
	if(rmsCandJet_pfakt5[i] > 0.05) goodetajet = 0;
      } else {
	if(rmsCandJet_pfakt5[i] > 0.055) goodetajet = 0;
      }
      
      if(!assp && goodetajet) jetnoassphot.push_back(1); 
      else jetnoassphot.push_back(0);  
          
      if(!assi && goodetajet) jetgoodnoisophot.push_back(1); 
      else jetgoodnoisophot.push_back(0);  
      
      if(!assi) jetnoisophot.push_back(1); 
      else jetnoisophot.push_back(0);  
    }
    vector<int> firsttennoisojet = firstones(ptCorrJet_pfakt5,&jetgoodnoisophot,10);      
  



    // saving jet related variables in the tree for the first 10 good jets not matching preselected gammas
    for( unsigned ijet=0; ijet<10; ++ijet ) {
      ptjet[ijet]       = -999.;
      ptcorrjet[ijet]   = -999.;
      ecorrjet[ijet]    = -999.;
      etajet[ijet]      = -999.;
      phijet[ijet]      = -999.;
      betajet[ijet]     = -999.;
      betastarjet[ijet] = -999.;
      rmsjet[ijet]      = -999.;
    }
	
    njets=0;
    for( unsigned ijet=0; ijet<firsttennoisojet.size(); ++ijet ) {
      if( firsttennoisojet.at(ijet)>=0 ) {
	
	if( ptCorrJet_pfakt5[firsttennoisojet.at(ijet)] < 20. ) continue;
	if( njets >=10 ) continue;
	
	ptjet[njets]       = ptJet_pfakt5[firsttennoisojet.at(ijet)];
	ptcorrjet[njets]   = ptCorrJet_pfakt5[firsttennoisojet.at(ijet)];	  
	ecorrjet[njets]    = ptcorrjet[njets]/ptjet[njets]*eJet_pfakt5[firsttennoisojet.at(ijet)];
	etajet[njets]      = etaJet_pfakt5[firsttennoisojet.at(ijet)];
	phijet[njets]      = phiJet_pfakt5[firsttennoisojet.at(ijet)];
	betajet[njets]     = beta_pfakt5[firsttennoisojet.at(ijet)][vrankPhotonPairs[0]];
	betastarjet[njets] = betaStar_pfakt5[firsttennoisojet.at(ijet)][vrankPhotonPairs[0]];
	rmsjet[njets]      = rmsCandJet_pfakt5[firsttennoisojet.at(ijet)];
	
	njets++;
      } // if good index 
    } // for firsttennoisojet


    // saving the fired HLT paths in the tree
    aHLTNames   = new std::vector<std::string>;
    aHLTResults = new std::vector<bool>;
    aHLTNames   -> clear();
    aHLTResults -> clear();
    for (int ii=0; ii<(HLTResults->size()); ii++) {
      if ((*HLTResults)[ii]) {
	aHLTNames->push_back((*HLTNames)[ii]);
	aHLTResults->push_back((*HLTResults)[ii]);
      }
    }


    // saving gamma related stuffs (and general ones) in the tree for events passing the reco preselection
    // reco preselection: at least 1 gamma with pT>30 and in acceptance
    bool recoPreselection = ( firstfourisophot.at(0)>-1 && ptPhot[firstfourisophot.at(0)]>30 && 
			      (! ((fabs(etascPhot[firstfourisophot.at(0)])>1.4442 && (fabs(etascPhot[firstfourisophot.at(0)])<1.566)) || (fabs(etascPhot[firstfourisophot.at(0)])>2.5) ) ) );
    
    if(!recoPreselection ) { 
      SetAllRecoVarToMinus999();  
    }
    else {
      
      ptphot1    = ptPhot[firstfourisophot.at(0)]; 
      etaphot1   = etaPhot[firstfourisophot.at(0)];
      phiphot1   = phiPhot[firstfourisophot.at(0)];
      etascphot1 = etascPhot[firstfourisophot.at(0)];
      deltaRToTrackphot1 = pid_deltaRToTrackPhot[firstfourisophot.at(0)];
      E1phot1 = E1Phot[firstfourisophot.at(0)];
      E9phot1 = E9Phot[firstfourisophot.at(0)];
      r9phot1 = E9Phot[firstfourisophot.at(0)]/escRawPhot[firstfourisophot.at(0)];
      pid_haspixelseedphot1 =  hasPixelSeedPhot[firstfourisophot.at(0)]; 
      pid_hasMatchedConvphot1 = hasMatchedConvPhot[firstfourisophot.at(0)]; 
      pid_hasMatchedPromptElephot1 = hasMatchedPromptElePhot[firstfourisophot.at(0)]; 
      pid_HoverEphot1 =  pid_HoverE[firstfourisophot.at(0)];
      pid_sigmaIeIephot1  = pid_etawid[firstfourisophot.at(0)];
      pid_hlwTrack04phot1 = pid_hlwTrack[firstfourisophot.at(0)];
      pid_jurECAL04phot1  = pid_jurECAL[firstfourisophot.at(0)];
      pid_twrHCAL04phot1  = pid_twrHCAL[firstfourisophot.at(0)];
      pid_pfIsoCharged03phot1  = pid_pfIsoCharged03ForCiC[firstfourisophot.at(0)][0];
      pid_pfIsoPhotons03phot1  = pid_pfIsoPhotons03ForCiC[firstfourisophot.at(0)];
      pid_pfIsoNeutrals03phot1 = pid_pfIsoNeutrals03ForCiC[firstfourisophot.at(0)];
      pid_pfIsoCharged04phot1  = pid_pfIsoCharged04ForCiC[firstfourisophot.at(0)][0];
      pid_pfIsoPhotons04phot1  = pid_pfIsoPhotons04ForCiC[firstfourisophot.at(0)];
      pid_pfIsoNeutrals04phot1 = pid_pfIsoNeutrals04ForCiC[firstfourisophot.at(0)];

      // others
      nvtx    = nvertex;
      runRN   = run;
      eventRN = event;
      rhoPFRN = rhoPF;
      rhoAllJetsRN = rhoAllJets;
    }
    
    if(recoPreselection) ana_tree->Fill();
    
    delete aHLTNames;  
    delete aHLTResults;

  } /// loop over events
    
  hOutputFile->Write() ;
  if (myjson) delete myjson;
}

void GammaJetsSelection::SetPuWeights(std::string puWeightFile)
{
  if (puWeightFile == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }
  
  std::cout << "PU REWEIGHTING:: Using file " << puWeightFile << std::endl;
  
  TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  f_pu->cd();
  
  TH1D *puweights = 0;
  TH1D *gen_pu = 0;
  
  gen_pu= (TH1D*) f_pu->Get("generated_pu");
  puweights= (TH1D*) f_pu->Get("weights");
  
  if (!puweights || !gen_pu) {
    std::cout << "weights histograms  not found in file " << puWeightFile << std::endl;
    return;
  }
  
  TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
  weightedPU->Multiply(puweights);
  //Rescaling weights in order to preserve same integral of events
  TH1D* weights= (TH1D*)puweights->Clone("rescaledWeights");
  weights->Scale( gen_pu->Integral(1,MAX_PU_REWEIGHT) / weightedPU->Integral(1,MAX_PU_REWEIGHT) );
  
  float sumPuWeights=0.;
  for (int i = 0; i<MAX_PU_REWEIGHT; i++) {
    float weight=1.;
    weight=weights->GetBinContent(i+1);
    sumPuWeights+=weight;
    puweights_.push_back(weight);
  }
}

void GammaJetsSelection::SetAllRecoVarToMinus999() {
  
  ptphot1    = -999.;
  deltaRToTrackphot1 = -999.;
  etaphot1   = -999.;
  phiphot1   = -999.;
  etascphot1 = -999.;
  E1phot1    = -999.;
  E9phot1    = -999.;
  r9phot1      = -999.;
  pid_haspixelseedphot1        = -999.;
  pid_HoverEphot1              = -999.;
  pid_sigmaIeIephot1  = -999.;
  pid_hlwTrack04phot1 = -999.;
  pid_jurECAL04phot1  = -999.;
  pid_twrHCAL04phot1  = -999.;
  pid_pfIsoCharged03phot1  = -999.;
  pid_pfIsoPhotons03phot1  = -999.;
  pid_pfIsoNeutrals03phot1 = -999.;
  pid_pfIsoCharged04phot1  = -999.;
  pid_pfIsoPhotons04phot1  = -999.;
  pid_pfIsoNeutrals04phot1 = -999.;
  pid_hasMatchedConvphot1      = -999.; 
  pid_hasMatchedPromptElephot1 = -999.; 
  nvtx    = -999;
  runRN   = -999;
  eventRN = -999;
  rhoPFRN = -999;
  rhoAllJetsRN = -999;
  for( unsigned i=0; i<10; ++i ) {
    ptjet[i]       = -999;
    ptcorrjet[i]   = -999;
    ecorrjet[i]    = -999;
    etajet[i]      = -999;
    phijet[i]      = -999;
    betajet[i]     = -999;
    betastarjet[i] = -999;
    rmsjet[i]      = -999;
  }
 vtxId = -999;
 vtxPos_x = -999;
 vtxPos_y = -999;
 vtxPos_z = -999;
 npu = -999;
 etascphot1 = -999;
 pu_weight = -999;
 weight = -999;
}

// chiara: da usare!
bool GammaJetsSelection::PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) {

  int photon_category = PhotonCategory(photon_index);

  float mitCuts_hoe[4]                 = {0.082,0.075,0.075,0.075};                                        
  float mitCuts_sieie[4]               = {0.014,0.014,0.034,0.034};                                        
  float mitCuts_ecaliso[4]             = {50,4,50,4};                                                      
  float mitCuts_hcaliso[4]             = {50,4,50,4};                                                      
  float mitCuts_trkiso[4]              = {50,4,50,4};                                                      
  float mitCuts_pfiso[4]               = {4,4,4,4};
  
  float val_hoe        = pid_HoverE[photon_index];
  float val_sieie      = pid_etawid[photon_index];                                                          
  float val_ecaliso = pid_jurECAL03[photon_index] - 0.012*ptPhot[photon_index];                              
  float val_hcaliso = pid_twrHCAL03[photon_index] - 0.005*ptPhot[photon_index]; 
  float val_trkiso  = pid_hlwTrack03[photon_index] - 0.002*ptPhot[photon_index]; 
  
  //float val_hcalecal   = (pho_ecalsumetconedr03[photon_index]+pho_hcalsumetconedr03[photon_index]-rho_algo1*rhofac);                                             
  int val_pho_isconv = !hasMatchedPromptElePhot[photon_index];
  float val_pfiso02 = pid_pfIsoCharged02ForCiC[photon_index][vertex_index];
  
  if (val_hoe             >= mitCuts_hoe[photon_category]         ) return false;                                           
  if (val_sieie           >= mitCuts_sieie[photon_category]       ) return false;
  if (val_ecaliso         >= mitCuts_ecaliso[photon_category]     ) return false;
  if (val_hcaliso         >= mitCuts_hcaliso[photon_category]     ) return false;                                           
  if (val_trkiso          >= mitCuts_trkiso[photon_category]      ) return false;
  if ((!val_pho_isconv && electronVeto) ) return false; // Electron Rejection based Conversion Safe Veto
  if (val_pfiso02 >= mitCuts_pfiso[photon_category]) return false;            
  
  return true;
}

