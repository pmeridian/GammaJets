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
  // muons
  ana_tree->Branch("oneLooseIsoMu",  &oneLooseIsoMu,  "oneLooseIsoMu/I");
  ana_tree->Branch("oneTightIsoMu",  &oneTightIsoMu,  "oneTightIsoMu/I");
  // electrons
  ana_tree->Branch("oneWP80Ele",     &oneWP80Ele,     "oneWP80Ele/I");
  ana_tree->Branch("oneWP90Ele",     &oneWP90Ele,     "oneWP90Ele/I");
  ana_tree->Branch("oneHwwEle",      &oneHwwEle,      "oneHwwEle/I");
  ana_tree->Branch("oneHzzEle",      &oneHzzEle,      "oneHzzEle/I");
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
  ana_tree->Branch("matchingMu",  matchingMu,  "matchingMu[njets]/I");
  ana_tree->Branch("matchingEle", matchingEle, "matchingEle[njets]/I");
  // gammas
  ana_tree->Branch("dRGenphot1",&dRGenphot1,"dRGenphot1/F");
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
  ana_tree->Branch("pid_deltaRToTrackphot1",&pid_deltaRToTrackphot1,"pid_deltaRToTrackphot1/F");
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
          
      // preselection 
      bool preselection = true;  
      if (ptPhot[i]<30) preselection = false;
      if (fabs(etascPhot[i])>1.4442 && fabs(etascPhot[i])<1.566) preselection = false;
      if (fabs(etascPhot[i])>2.5) preselection = false;
      // ID as in 2012 CaloIdVL for HLT
      bool iseb=1;
      if ((fabs(etascPhot[i]))>1.4442) iseb=0;
      if(iseb) {
	if(pid_etawid[i]>0.024) preselection = false;
	if(pid_HoverE[i]>0.15)  preselection = false;
      }
      if(!iseb) {
	if(pid_etawid[i]>0.040) preselection = false;
	if(pid_HoverE[i]>0.10)  preselection = false;
      }
      // quite loose tracker based isolation
      if(pid_twrHCAL[i]>4) preselection = false;
      // electron veto
      if (hasMatchedPromptElePhot[i]) preselection = false; 
      // if (hasPixelSeedPhot[i]) preselection = false;   
      if (preselection) isophot.push_back(1); 
      else isophot.push_back(0);  
    }
    vector<int> firstfourassphot = firstones(ptPhot,&assophot,4);
    vector<int> firstfourisophot = firstones(ptPhot,&isophot,4);      


    // 4) muons: to veto events with muons (save tightID + loose and tight isolation WPs)
    //           to clean up jets based on loose isolation
    std::vector<int> _looseIsolMu;
    _looseIsolMu.clear();
    oneLooseIsoMu=0;
    oneTightIsoMu=0;
    for(int iMu=0; iMu<nMuons; iMu++){
      if (Muon_pt[iMu] < 20.)        continue;  
      if (fabs(Muon_eta[iMu]) > 2.4) continue;
      if (!muTightId(iMu))           continue;
      float absMuIso = Muon_pfiso04_chHad[iMu] + max(0.,Muon_pfiso04_nHad[iMu]+Muon_pfiso04_Phot[iMu]-0.5*Muon_pfiso04_PUPt[iMu]);
      float relMuIso = absMuIso/Muon_pt[iMu];
      if (relMuIso<0.20) {
	_looseIsolMu.push_back(iMu);  
	oneLooseIsoMu++;
      }
      if (relMuIso<0.12) oneTightIsoMu++;
    }
    _looseIsolMu = sortMuonsByPt(_looseIsolMu);  
    int minLooseIsolMuSize = _looseIsolMu.size();
    if (minLooseIsolMuSize>4) minLooseIsolMuSize = 4;

    // 5) electrons: to veto events with electrons (save WP80, WP90, HWW BDT, HZZ BDT)
    //               to clean up jets based on HZZ BDT isolation
    std::vector<int> _hzzEle;
    _hzzEle.clear();
    oneWP80Ele=0;     
    oneWP90Ele=0;     
    oneHzzEle=0;      
    oneHwwEle=0;      
    for(int iEle=0; iEle<nEle; iEle++){
      if (electron_pt[iEle] < 20.)            continue;
      if (fabs(electron_sc_eta[iEle]) > 2.5 ) continue;
      if (fabs(electron_sc_eta[iEle]) > 1.4442 && fabs(electron_sc_eta[iEle]) < 1.566) continue;
      bool isWP90 = (eleCutId2012(iEle)).first;
      bool isWP80 = (eleCutId2012(iEle)).second;
      bool isHWW  = eleMvaId2012_Hww(iEle);
      bool isHZZ  = eleMvaId2012_Hzz(iEle);
      if (isWP90) oneWP90Ele++;
      if (isWP80) oneWP80Ele++;
      if (isHWW)  oneHwwEle++;
      if (isHZZ) {
	_hzzEle.push_back(iEle);
	oneHzzEle++;
      }
    }
    _hzzEle = sortElectronsByPt(_hzzEle);    
    int minHzzEleSize = _hzzEle.size();
    if (minHzzEleSize>4) minHzzEleSize = 4;

    // 6) reco jets and cleaning from photons
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
      matchingMu[ijet]  = -999;
      matchingEle[ijet] = -999;
    }
	
    njets=0;
    for( unsigned ijet=0; ijet<firsttennoisojet.size(); ++ijet ) {
      if( firsttennoisojet.at(ijet)>=0 ) {
	
	if( ptCorrJet_pfakt5[firsttennoisojet.at(ijet)] < 20. ) continue;
	if( njets >=10 ) continue;
	
	// match jets / muons (considering only the first 4 selected loose muons)
	int assmu = 0;
	for (int iMu=0; iMu<minLooseIsolMuSize; iMu++) {
	  int myMu = _looseIsolMu[iMu];
	  float DR = sqrt(delta_eta(etaJet_pfakt5[firsttennoisojet.at(ijet)],Muon_eta[myMu])*delta_eta(etaJet_pfakt5[firsttennoisojet.at(ijet)],Muon_eta[myMu]) + 
			  delta_phi(phiJet_pfakt5[firsttennoisojet.at(ijet)],Muon_phi[myMu])*delta_phi(phiJet_pfakt5[firsttennoisojet.at(ijet)],Muon_phi[myMu]));
	  if( DR < .5 ) assmu = 1;   
	}
      
	// match jets / electrons (considering only the first 4 selected loose electrons)
	int assele = 0;
	for (int iEle=0; iEle<minHzzEleSize; iEle++) {
	  int myEle = _hzzEle[iEle];
	  float DR = sqrt(delta_eta(etaJet_pfakt5[firsttennoisojet.at(ijet)],electron_eta[myEle])*delta_eta(etaJet_pfakt5[firsttennoisojet.at(ijet)],electron_eta[myEle]) + 
			  delta_phi(phiJet_pfakt5[firsttennoisojet.at(ijet)],electron_phi[myEle])*delta_phi(phiJet_pfakt5[firsttennoisojet.at(ijet)],electron_phi[myEle]));
	  if( DR < .5 ) assele = 1;   
	}
	
	ptjet[njets]       = ptJet_pfakt5[firsttennoisojet.at(ijet)];
	ptcorrjet[njets]   = ptCorrJet_pfakt5[firsttennoisojet.at(ijet)];	  
	ecorrjet[njets]    = ptcorrjet[njets]/ptjet[njets]*eJet_pfakt5[firsttennoisojet.at(ijet)];
	etajet[njets]      = etaJet_pfakt5[firsttennoisojet.at(ijet)];
	phijet[njets]      = phiJet_pfakt5[firsttennoisojet.at(ijet)];
	betajet[njets]     = beta_pfakt5[firsttennoisojet.at(ijet)][vrankPhotonPairs[0]];
	betastarjet[njets] = betaStar_pfakt5[firsttennoisojet.at(ijet)][vrankPhotonPairs[0]];
	rmsjet[njets]      = rmsCandJet_pfakt5[firsttennoisojet.at(ijet)];
	matchingMu[njets]  = assmu; 
	matchingEle[njets] = assele; 
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
      pid_deltaRToTrackphot1   = pid_deltaRToTrackPhot[firstfourisophot.at(0)];
      // matching with gen gammas
      float theDRminLO=999;
      for(int i=0; i<nMC; i++) {
	if(pdgIdMC[i]==22 && statusMC[i]==3){
	  int myMoth   = motherIDMC[i];
	  int myMothId = abs(pdgIdMC[myMoth]);
	  if (myMothId<25) {
	    float theDR = sqrt(delta_eta(etaphot1,etaMC[i])*delta_eta(etaphot1,etaMC[i]) +
			       delta_phi(phiphot1,phiMC[i])*delta_phi(phiphot1,phiMC[i]) );
	    if (theDR<theDRminLO) theDRminLO = theDR;
	  }
	}
      }
      dRGenphot1 = theDRminLO; 

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

  dRGenphot1 = -999.;  
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
  pid_deltaRToTrackphot1 = -999.;
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
    matchingMu[i]  = -999;
    matchingEle[i] = -999;
  }
 vtxId = -999;
 vtxPos_x = -999;
 vtxPos_y = -999;
 vtxPos_z = -999;
 npu = -999;
 etascphot1 = -999;
 pu_weight = -999;
 weight = -999;
 oneLooseIsoMu = -999;
 oneTightIsoMu = -999;
 oneWP80Ele=-999;
 oneWP90Ele=-999;
 oneHwwEle=-999;
 oneHzzEle=-999;
}

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

// muon selection - tight ID as defined in 
// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
bool GammaJetsSelection::muTightId(int iMu) {

  bool globalmu, pfmu;
  bool pixhits, globalhits, chi2, match, withm;
  bool d0, dz;

  // ID
  globalmu   = Muon_isGlobalMuon[iMu];       
  pfmu       = Muon_isPFMuon[iMu];           
  chi2       = Muon_normChi2[iMu] < 10;
  globalhits = Muon_validHits[iMu] > 0;
  match      = Muon_numberOfMatches[iMu] > 1;
  pixhits    = Muon_pixHits[iMu] > 0;
  withm      = Muon_trkLayerWithMeas[iMu] > 5;   

  // impact parameter
  float d0Muon = muonDxyPV(iMu,0);
  float dzMuon = muonDzPV(iMu,0);
  d0 = fabs(d0Muon) < 0.2;
  dz = fabs(dzMuon) < 0.5;

  return (globalmu && pfmu && chi2 && globalhits && match && pixhits && withm && d0 && dz);
}

std::vector<int> GammaJetsSelection::sortMuonsByPt(std::vector<int> muons) {
  int tmp;
  int max;
  for(int i=0;i<(int)muons.size();i++) {
    max = i;
    float maxmuPt = Muon_pt[i];
    for(int x=i; x<(int)muons.size(); x++) {
      float xmuPt = Muon_pt[x];
      if(xmuPt > maxmuPt) {
	max = x;
      }
    }
    tmp = muons[i];
    muons[i] = muons[max];
    muons[max] = tmp;
  }
  return muons;
}

// electron selection - 2012 Loose WP (~WP90) and Medium WP (~WP80)
std::pair<bool,bool> GammaJetsSelection::eleCutId2012(int iEle) {

  bool setaeta, deta, dphi, hoe, oeMop;
  bool minhits, matchconv;
  bool d0, dz;
  bool isol;

  // impact parameters                                                                                                                     
  float d0Ele = eleDxyPV(iEle,0);  
  float dzEle = eleDzPV(iEle,0);   

  // isolation and effective areas (updated 2012 HCP numbers)
  float abseta       = fabs(electron_sc_eta[iEle]);
  float eff_area_sum = get03EleEffectiveAreas(abseta);
  float theIsolation = electron_chHad03Iso[iEle];
  theIsolation += max<float>(0.,electron_nHad03Iso[iEle]+electron_phot03Iso[iEle]-eff_area_sum*rhoAllJets);  // chiara: rho?

  // common to EB, EE and the two WPs
  d0        = fabs(d0Ele) < 0.02;
  minhits   = electron_misHits[iEle] <= 1;
  matchconv = electron_matchedConv[iEle]==0;
  isol      = theIsolation < electron_pt[iEle]* 0.15;

  // WP90                                                                                                                        
  if (abseta<1.4442) {
    setaeta   = electron_SigmaIetaIeta[iEle] < 0.01;
    deta      = fabs(electron_dEtaIn[iEle])  < 0.007;
    dphi      = fabs(electron_dPhiIn[iEle])  < 0.15;
    hoe       = electron_HoE[iEle] < 0.12;
    oeMop     = fabs(1./electron_ecalEnergy[iEle] - 1./electron_trackPatVtx[iEle]) < 0.05;
    dz        = fabs(dzEle) < 0.2;
  } else {
    setaeta = electron_SigmaIetaIeta[iEle] < 0.03;
    deta    = fabs(electron_dEtaIn[iEle]) < 0.009;
    dphi    = fabs(electron_dPhiIn[iEle]) < 0.1;
    hoe     = electron_HoE[iEle] < 0.10;
    oeMop   = fabs(1./electron_ecalEnergy[iEle] - 1./electron_trackPatVtx[iEle]) < 0.05;
    dz      = fabs(dzEle) < 0.2;
  }
  bool isWP90 = setaeta && deta && dphi && hoe && oeMop && d0 && dz && minhits && matchconv && isol;

  // WP80                                                                                                                        
  if (abseta<1.4442) {
    deta = fabs(electron_dEtaIn[iEle])  < 0.004;
    dphi = fabs(electron_dPhiIn[iEle])  < 0.06;
    dz   = fabs(dzEle) < 0.1;
  } else {
    deta = fabs(electron_dEtaIn[iEle]) < 0.007;
    dphi = fabs(electron_dPhiIn[iEle]) < 0.03;
    dz   = fabs(dzEle) < 0.1;
  }
  bool isWP80 = isWP90 && deta && dphi && dz;

  return make_pair(isWP90,isWP80);
}

// electron selection based on ID MVA - tight, same as for H->WW
bool GammaJetsSelection::eleMvaId2012_Hww(int iEle) {

  bool minhits, matchconv;
  bool isol, isID;

  // preselection used at HLT (for BDT training)
  bool isHLT = trainTrigPresel(iEle);

  // isolation and effective areas (updated 2012 HCP numbers)
  float abseta       = fabs(electron_sc_eta[iEle]);
  float eff_area_sum = get03EleEffectiveAreas(abseta);
  float theIsolation = electron_chHad03Iso[iEle];
  theIsolation += max<float>(0.,electron_nHad03Iso[iEle]+electron_phot03Iso[iEle]-eff_area_sum*rhoAllJets);  // chiara: rho?
  isol = theIsolation < electron_pt[iEle]* 0.15;  

  // ID
  float bdt = electron_mvaTrig[iEle];
  isID = (
	  ( ptphot1 <= 20 && abseta >= 0.000 && abseta < 0.800 && bdt > 0.00 ) ||
	  ( ptphot1 <= 20 && abseta >= 0.800 && abseta < 1.479 && bdt > 0.10 ) ||
	  ( ptphot1 <= 20 && abseta >= 1.479 && abseta < 2.500 && bdt > 0.62 ) ||
	  ( ptphot1 >  20 && abseta >= 0.000 && abseta < 0.800 && bdt > 0.94 ) ||
	  ( ptphot1 >  20 && abseta >= 0.800 && abseta < 1.479 && bdt > 0.85 ) ||
	  ( ptphot1 >  20 && abseta >= 1.479 && abseta < 2.500 && bdt > 0.92 )
	  );

  // conv.rej
  minhits   = electron_misHits[iEle] == 0;
  matchconv = electron_matchedConv[iEle]==0;

  bool isHWW = isHLT && minhits && matchconv && isol && isID;
  return isHWW;
}

// electron selection based on ID MVA - loose, same as for H->ZZ 
bool GammaJetsSelection::eleMvaId2012_Hzz(int iEle) {

  bool minhits;
  bool d0;
  bool isol, isID;
  
  // impact parameters
  float d0Ele = eleDxyPV(iEle,0);

  // isolation and effective areas (updated 2012 HCP numbers)
  float abseta       = fabs(electron_sc_eta[iEle]);
  float eff_area_sum = get03EleEffectiveAreas(abseta);
  float theIsolation = electron_chHad03Iso[iEle];
  theIsolation += max<float>(0.,electron_nHad03Iso[iEle]+electron_phot03Iso[iEle]-eff_area_sum*rhoAllJets);  // chiara: rho?
  isol = theIsolation < electron_pt[iEle]* 0.40;  

  // ID
  float bdt = electron_mvaNonTrig[iEle];
  isID = (
	  ( ptphot1 <= 10 && abseta >= 0.000 && abseta < 0.800 && bdt > 0.470 ) ||
	  ( ptphot1 <= 10 && abseta >= 0.800 && abseta < 1.479 && bdt > 0.004 ) ||
	  ( ptphot1 <= 10 && abseta >= 1.479 && abseta < 2.500 && bdt > 0.295 ) ||
	  ( ptphot1 >  10 && abseta >= 0.000 && abseta < 0.800 && bdt > 0.500 ) ||
	  ( ptphot1 >  10 && abseta >= 0.800 && abseta < 1.479 && bdt > 0.120 ) ||
	  ( ptphot1 >  10 && abseta >= 1.479 && abseta < 2.500 && bdt > 0.600 )
	  );
  
  // conv.rej
  minhits = electron_misHits[iEle] <= 1;
  
  // IP cut
  // chiara: the real Hzz uses |SIP|<4, but we don't have the track error...
  d0 = fabs(d0Ele) < 0.05;

  bool isHZZ = minhits && d0 && isol && isID;
  return isHZZ;
}

bool GammaJetsSelection::trainTrigPresel(int iEle) {

  bool myTrigPresel = false;

  float abseta  = fabs(electron_sc_eta[iEle]);
  float thept   = electron_pt[iEle];

  int minhits   = electron_misHits[iEle];
  float setaeta = electron_SigmaIetaIeta[iEle];
  float hoe     = electron_HoE[iEle];
  float trkIso  = electron_trkIso03[iEle];
  float ecalIso = electron_ecalIso03[iEle];
  float hcalIso = electron_hcalIso03[iEle];

  if(abseta < 1.479) {
    if(setaeta < 0.014 &&
       hoe < 0.15 &&
       trkIso/thept < 0.2 &&  
       ecalIso/thept < 0.2 && 
       hcalIso/thept < 0.2 && 
       minhits == 0)
      myTrigPresel = true;
  }
  else {
    if(setaeta < 0.035 &&
       hoe < 0.10 &&
       trkIso/thept < 0.2 &&  
       ecalIso/thept < 0.2 && 
       hcalIso/thept < 0.2 && 
       minhits == 0)
      myTrigPresel = true;
  }
  return myTrigPresel;
}

double GammaJetsSelection::eleDzPV(int iele, int iPV) {

  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(electron_vx[iele],electron_vy[iele],electron_vz[iele]);  
  TVector3 lepMom(electron_px[iele],electron_py[iele],electron_pz[iele]);
  return trackDzPV(PVPos,lepVPos,lepMom);
}

double GammaJetsSelection::eleDxyPV(int iele, int iPV) {

  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(electron_vx[iele],electron_vy[iele],electron_vz[iele]);
  TVector3 lepMom(electron_px[iele],electron_py[iele],electron_pz[iele]);
  return trackDxyPV(PVPos,lepVPos,lepMom);
}

double GammaJetsSelection::muonDzPV(int imu, int iPV) {

  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(Muon_vx[imu],Muon_vy[imu],Muon_vz[imu]);
  TVector3 lepMom(Muon_px[imu],Muon_py[imu],Muon_pz[imu]);
  return trackDzPV(PVPos,lepVPos,lepMom);
}

double GammaJetsSelection::muonDxyPV(int imu, int iPV) {

  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(Muon_vx[imu],Muon_vy[imu],Muon_vz[imu]);
  TVector3 lepMom(Muon_px[imu],Muon_py[imu],Muon_pz[imu]);
  return trackDxyPV(PVPos,lepVPos,lepMom);
}

double GammaJetsSelection::trackDzPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom) {

  float trackPt = trackMom.Pt();
  return (trackVPos.Z()-PVPos.Z()) - ((trackVPos.X()-PVPos.X())*trackMom.X()+(trackVPos.Y()-PVPos.Y())*trackMom.Y())/trackPt *trackMom.Pz()/trackPt;
}

double GammaJetsSelection::trackDxyPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom) {

  return ( - (trackVPos.X()-PVPos.X())*trackMom.Y() + (trackVPos.Y()-PVPos.Y())*trackMom.X() ) / trackMom.Pt();
}

// values for cone dR=0.3
double GammaJetsSelection::get03EleEffectiveAreas(float eta) {

  float abseta = fabs(eta);

  if(abseta <= 1.)                            return 0.13;
  else if(abseta > 1.    && abseta <= 1.479)  return 0.14;
  else if(abseta > 1.479 && abseta <= 2.0)    return 0.07;
  else if(abseta > 2.    && abseta <= 2.2)    return 0.09;
  else if(abseta > 2.2   && abseta <=  2.3)   return 0.11;
  else if(abseta > 2.3   && abseta <= 2.4)    return 0.11;
  else if(abseta > 2.4)                       return 0.14;
  else                                        return 9999;
}

std::vector<int> GammaJetsSelection::sortElectronsByPt(std::vector<int> electrons) {
  int tmp;
  int max;
  for(int i=0;i<(int)electrons.size();i++) {
    max = i;
    float maxelePt = electron_pt[i];
    for(int x=i; x<(int)electrons.size(); x++) {
      float xelePt = electron_pt[x];
      if(xelePt > maxelePt) {
	max = x;
      }
    }
    tmp = electrons[i];
    electrons[i] = electrons[max];
    electrons[max] = tmp;
  }
  return electrons;
}

