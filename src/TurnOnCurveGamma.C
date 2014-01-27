#define TurnOnCurveGamma_cxx
#include "TurnOnCurveGamma.h"

#include <TH1.h>
#include <TMath.h>
#include <iostream>
#include "TVector3.h"

using namespace std;

void TurnOnCurveGamma::Loop() {
  
  if (fChain == 0) return;
  
  int nentries = fChain->GetEntries();
  // cout << "chiara: nentries = " << nentries << endl;
  
  // Initialization
  SetAllMVA();
  BookFinalTreeTurnOn();   

  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if (jentry%50000==0) std::cout << "Analyzing event " << jentry << "/" << nentries << " (" <<  setprecision(4) << jentry*100./nentries << "%)" << std::endl;

    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    // json file already applied at reduction time, not needed here
    
    // patological events removal
    if (npu>=60) continue;    
    
    // first vertex must be good
    if (vtxId<0) continue;
    
    // check if the event fired the wanted HLT path (wo isolation applied) 
    isHLT30  = isHLT_30();
    isHLT50  = isHLT_50();
    isHLT75  = isHLT_75();
    isHLT90  = isHLT_90();
    isHLT135 = isHLT_135();   
    isHLT150 = isHLT_150();   
    
    /*
    // check if there is a Z in the event, to have a pure enough sample 
    isAZ       = true;   
    isAZ_tight = true;   
    if (nEle<2) {
      isAZ       = false;
      isAZ_tight = false;
    }

    // b) best tag-probe pair => mee closest to Z mass                                                               
    mass    = 1000.;
    ptEle1  = 999.;
    ptEle2  = 999.;
    etaEle1 = 999.;
    etaEle2 = 999.;
    float minpull = 100000.;
    float okmass  = 1000.;
    int theEle1   = -1;
    int theEle2   = -1;

    for(int iele1=0; iele1<nEle; iele1++) {
      TLorentzVector electron1(electron_px[iele1],electron_py[iele1],electron_pz[iele1],electron_energy[iele1]);

      // eta and pT cuts for ele1
      if ( fabs(electron_sc_eta[iele1])>1.4442 && fabs(electron_sc_eta[iele1])<1.566 ) continue;
      if ( fabs(electron_sc_eta[iele1])>2.5 ) continue;
      if ( electron_pt[iele1]<20. ) continue;
      
      for(int iele2=iele1+1; iele2<nEle; iele2++) {
	TLorentzVector electron2(electron_px[iele2],electron_py[iele2],electron_pz[iele2],electron_energy[iele2]);

        // eta and pT cuts for ele2
	if ( fabs(electron_sc_eta[iele2])>1.4442 && fabs(electron_sc_eta[iele2])<1.566 ) continue;
        if ( fabs(electron_sc_eta[iele2])>2.5 ) continue;
        if ( electron_pt[iele2]<20. ) continue;

	// best invariant mass
        mass = (electron1+electron2).M();
        float pull=fabs(mass-91.1876);
        if( fabs(pull) < minpull ) {
          okmass  = mass;
          minpull = fabs(pull);
          theEle1 = iele1;
          theEle2 = iele2;
          ptEle1  = electron_pt[iele1];
          ptEle2  = electron_pt[iele2];
          etaEle1 = electron_sc_eta[iele1];
          etaEle2 = electron_sc_eta[iele2];
        }
      }
    }
    if ( okmass>120 || okmass<60 ) {
      isAZ       = false;
      isAZ_tight = false;
    }

    // c) one of the two electrons should be tight enough (a sort of tag) 
    if ( isAZ ) {  
      if ( isTagTightEle[theEle1] || isTagTightEle[theEle2] ) isAZ_tight = true;  
    }
    */

    // at least 1 reconstructed photon candidate passing the full selection
    std::vector<int> photons=sortedPtPhotons();
    if (photons.size()<1) continue;
      
    std::vector<int> preselectPhotons=preselectedPhotons(photons);
    if (preselectPhotons.size()<1) continue;
    
    if ( photons.size() != preselectPhotons.size() ) {
      cout << "chiara: secondo me c'e' un problema. I fotoni in photons devono essere gia' preselezionati" << endl;
      continue;
    }

    std::vector<int> selectPhotons=selectedPhotons(preselectPhotons);
    if (selectPhotons.size()<1) continue;
      

    // now check the match with HLT candidates and keep the kinematics of the highest pT photon selected and matching 
    // here having 135 as well would be better, but the info is missing in our ntuples. Use 90 for both 135 and 150
    match20=false;
    match30=false;
    match50=false;
    match75=false;
    match90=false;     

    eta_match20=-999.;
    eta_match30=-999.;
    eta_match50=-999.;
    eta_match75=-999.;
    eta_match90=-999.;   

    pt_match20=-999.;
    pt_match30=-999.;
    pt_match50=-999.;
    pt_match75=-999.;
    pt_match90=-999.;   

    pt_online_match20=-999.;
    pt_online_match30=-999.;
    pt_online_match50=-999.;
    pt_online_match75=-999.;
    pt_online_match90=-999.;   

    // match between HLT candidates and good selected photons 
    for (int iSel=0; iSel<(int)selectPhotons.size(); iSel++) {
      
      int thePhot = selectPhotons[iSel];

      if (!match20) {
	if (isTrig20CaloVLMatchedPhot[thePhot]) {   // chiara: questo non va bene perche' il path e' spento...
	  match20 = true;
	  eta_match20       = etaPhot_presel[thePhot];
	  pt_match20        = ptPhot_presel[thePhot];
	  pt_online_match20 = hltCandPt20CaloVLPhot[thePhot];   
	}
      }

      if (!match30) {
	if (isTrig30CaloVLMatchedPhot[thePhot]) {
	  match30 = true;
	  eta_match30       = etaPhot_presel[thePhot];
	  pt_match30        = ptPhot_presel[thePhot];
	  pt_online_match30 = hltCandPt30CaloVLPhot[thePhot]; 
	}
      }

      if (!match50) {
	if (isTrig50CaloVLMatchedPhot[thePhot]) {   
	  match50 = true;
	  eta_match50       = etaPhot_presel[thePhot];
	  pt_match50        = ptPhot_presel[thePhot];
	  pt_online_match50 = hltCandPt50CaloVLPhot[thePhot]; 
	}
      }

      if (!match75) {
	if (isTrig75CaloVLMatchedPhot[thePhot]) {   
	  match75 = true;
	  eta_match75       = etaPhot_presel[thePhot];
	  pt_match75        = ptPhot_presel[thePhot];
	  pt_online_match75 = hltCandPt75CaloVLPhot[thePhot]; 
	}
      }

      if (!match90) {
	if (isTrig90CaloVLMatchedPhot[thePhot]) {   
	  match90 = true;
	  eta_match90       = etaPhot_presel[thePhot];
	  pt_match90        = ptPhot_presel[thePhot];
	  pt_online_match90 = hltCandPt90CaloVLPhot[thePhot]; 
	}
      }
    }
    
    // Filling the output tree
    FillTreeEvent();              
    finalTreeTurnOn->Fill();       
  }

  // Write output tree
  finalTreeTurnOn->Write();
  outFile->Write();
  outFile->Close();
}

bool TurnOnCurveGamma::isHLT_30() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v11") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v13") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v14") isok=true;
  }
  return isok;
}

bool TurnOnCurveGamma::isHLT_50() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v7")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v8")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v9")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v10") isok=true;
  }
  return isok;
}

bool TurnOnCurveGamma::isHLT_75() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v10") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v11") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v13") isok=true;
  }
  return isok;
}

bool TurnOnCurveGamma::isHLT_90() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v7")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v8")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v9")  isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v10") isok=true;
  }
  return isok;
}

bool TurnOnCurveGamma::isHLT_135() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon135_v4") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon135_v5") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon135_v6") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon135_v7") isok=true;
  }
  return isok;
}

bool TurnOnCurveGamma::isHLT_150() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v1") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v2") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v3") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v4") isok=true;
  }
  return isok;
}

std::vector<int> TurnOnCurveGamma::sortedPtPhotons() {

  std::vector<int> sortedPhotons;
  int sorted_index[nPhot_presel];
  TMath::Sort(nPhot_presel,ptPhot_presel,sorted_index);
  for (int ipho=0;ipho<nPhot_presel;++ipho)
    sortedPhotons.push_back(sorted_index[ipho]);

  return sortedPhotons;
}

int TurnOnCurveGamma::effectiveAreaRegion(float theEta) {

  int theEAregion = 999;
  if (fabs(theEta)<1.) theEAregion = 0;
  if (fabs(theEta)<1.479 && fabs(theEta)>1.)    theEAregion = 1;
  if (fabs(theEta)<2.    && fabs(theEta)>1.479) theEAregion = 2;
  if (fabs(theEta)<2.2   && fabs(theEta)>2.0)   theEAregion = 3;
  if (fabs(theEta)<2.3   && fabs(theEta)>2.2)   theEAregion = 4;
  if (fabs(theEta)<2.4   && fabs(theEta)>2.3)   theEAregion = 5;
  if (fabs(theEta)>2.4) theEAregion = 6;

  return theEAregion;
}

std::vector<int> TurnOnCurveGamma::preselectedPhotons(const std::vector<int>& photons) {
 
  std::vector<int> selPhotons;

  for (int ipho=0;ipho<(int)photons.size();++ipho) {

    int theEAregion = effectiveAreaRegion(etaPhot_presel[photons[ipho]]);   
    if (theEAregion>6) continue;
      
    float preselECAL    = pid_jurECAL03_presel[photons[ipho]]  - 0.012*ptPhot_presel[photons[ipho]];  
    float preselHCAL    = pid_twrHCAL03_presel[photons[ipho]]  - 0.005*ptPhot_presel[photons[ipho]]; 
    float preselTracker = pid_hlwTrack03_presel[photons[ipho]] - 0.002*ptPhot_presel[photons[ipho]]; 
    if ( preselECAL > 50.)    continue;
    if ( preselHCAL > 50.)    continue;
    if ( preselTracker > 50)  continue;

    if ( theEAregion<2) {  // EB
      if ( pid_HoverE_presel[photons[ipho]]>0.075 )  continue;
      if ( sEtaEtaPhot_presel[photons[ipho]]>0.014 ) continue;
    } else {               // EE
      if(pid_HoverE_presel[photons[ipho]]>0.075)   continue;
      if (sEtaEtaPhot_presel[photons[ipho]]>0.034) continue;
    }
    selPhotons.push_back(photons[ipho]);
  }

  return selPhotons;
}

std::vector<int> TurnOnCurveGamma::selectedPhotons(const std::vector<int>& photons) {
  
  std::vector<int> selPhotons;
  double mva_cut_EB[4] = {0.892656, 0.844931, 0.766479, -1.};//corresponding to sig eff 0.80, 0.90, 0.95, 1.          
  double mva_cut_EE[4] = {0.871778, 0.778579, 0.601807, -1.};//corresponding to sig eff 0.80, 0.90, 0.95, 1.  

  for (int ipho=0;ipho<(int)photons.size();++ipho) {

    int theEAregion = effectiveAreaRegion(etaPhot_presel[photons[ipho]]); 
    if (theEAregion>6) continue;

    // photon ID MVA
    float theIdMva = PhotonIDMVA(photons[ipho]);

    // cuts on photon ID mva for fixed signal eff
    // chiara: per il momento uso eff=95%
    if(theEAregion<2){
      if ( theIdMva < mva_cut_EB[2]) continue;
    } else {
      if ( theIdMva < mva_cut_EE[2]) continue;
    }
    
    selPhotons.push_back(photons[ipho]);
  }

  return selPhotons;
}

void TurnOnCurveGamma::SetAllMVA() {

  if (isMVAinitialized) return;

  tmvaReaderID_Single_Barrel = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Barrel->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Barrel->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Barrel->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Barrel->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  tmvaReaderID_Single_Barrel->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Barrel->AddVariable("rhoAllJets",          &tmva_photonid_eventrho );
  tmvaReaderID_Single_Barrel->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );
  tmvaReaderID_Single_Barrel->AddSpectator("ptPhot_presel",      &tmva_photonid_pt );

  tmvaReaderID_Single_Endcap = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Endcap->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Endcap->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Endcap->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Endcap->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  tmvaReaderID_Single_Endcap->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Endcap->AddVariable("rhoAllJets",          &tmva_photonid_eventrho );
  tmvaReaderID_Single_Endcap->AddVariable("rr_presel",           &tmva_photonid_rr );
  tmvaReaderID_Single_Endcap->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );
  tmvaReaderID_Single_Endcap->AddSpectator("ptPhot_presel",      &tmva_photonid_pt );

  std::cout << "Booking PhotonID EB MVA with file " 
	    << "/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EB/TMVAClassification_BDTG.weights.xml" << std::endl;
  tmvaReaderID_Single_Barrel->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EB/TMVAClassification_BDTG.weights.xml");   
  std::cout << "Booking PhotonID EE MVA with file " 
	    << "/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EE/TMVAClassification_BDTG.weights.xml" << std::endl;
  tmvaReaderID_Single_Endcap->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EE/TMVAClassification_BDTG.weights.xml");   

  isMVAinitialized=true;
  return;
}

Float_t TurnOnCurveGamma::PhotonIDMVA(Int_t iPhoton) {

  Float_t mva = 999.;
  
  tmva_photonid_etawidth     = pid_scetawid_presel[iPhoton];
  tmva_photonid_phiwidth     = pid_scphiwid_presel[iPhoton];
  tmva_photonid_sieie        = sEtaEtaPhot_presel[iPhoton];
  tmva_photonid_sieip        = sEtaPhiPhot_presel[iPhoton];
  tmva_photonid_s4ratio      = s4RatioPhot_presel[iPhoton];
  tmva_photonid_r9           = r9Phot_presel[iPhoton];
  tmva_photonid_pt           = ptPhot_presel[iPhoton];
  tmva_photonid_sceta        = etascPhot_presel[iPhoton];
  tmva_photonid_eventrho     = rhoAllJets;   
  tmva_photonid_rr           = rr_presel[iPhoton];

  bool isEBphot = true;
  if (fabs(etascPhot_presel[iPhoton])>1.479) isEBphot = false;
  
  if (isEBphot)
    mva = tmvaReaderID_Single_Barrel->EvaluateMVA("BDT");   
  else
    mva = tmvaReaderID_Single_Endcap->EvaluateMVA("BDT");

  return mva;
}

void TurnOnCurveGamma::BookFinalTreeTurnOn() {

  outFile=TFile::Open("/tmp/crovelli/myTurnOnFile.root","recreate");
  outFile->cd();
  
  finalTreeTurnOn = new TTree("finalTreeTurnOn","finalTreeTurnOn");

  finalTreeTurnOn->Branch("ptGamma20",&finalTreeTurnOn_ptGamma20,"ptGamma20/F");
  finalTreeTurnOn->Branch("ptGamma30",&finalTreeTurnOn_ptGamma30,"ptGamma30/F");
  finalTreeTurnOn->Branch("ptGamma50",&finalTreeTurnOn_ptGamma50,"ptGamma50/F");
  finalTreeTurnOn->Branch("ptGamma75",&finalTreeTurnOn_ptGamma75,"ptGamma75/F");
  finalTreeTurnOn->Branch("ptGamma90",&finalTreeTurnOn_ptGamma90,"ptGamma90/F");
  // here we'd need 135 as well, but the info is missing in our ntuples. Use 90 for both 135 and 150

  finalTreeTurnOn->Branch("etaGamma20",&finalTreeTurnOn_etaGamma20,"etaGamma20/F");
  finalTreeTurnOn->Branch("etaGamma30",&finalTreeTurnOn_etaGamma30,"etaGamma30/F");
  finalTreeTurnOn->Branch("etaGamma50",&finalTreeTurnOn_etaGamma50,"etaGamma50/F");
  finalTreeTurnOn->Branch("etaGamma75",&finalTreeTurnOn_etaGamma75,"etaGamma75/F");
  finalTreeTurnOn->Branch("etaGamma90",&finalTreeTurnOn_etaGamma90,"etaGamma90/F");

  finalTreeTurnOn->Branch("ptOnlineGamma20",&finalTreeTurnOn_ptOnlineGamma20,"ptOnlineGamma20/F");
  finalTreeTurnOn->Branch("ptOnlineGamma30",&finalTreeTurnOn_ptOnlineGamma30,"ptOnlineGamma30/F");
  finalTreeTurnOn->Branch("ptOnlineGamma50",&finalTreeTurnOn_ptOnlineGamma50,"ptOnlineGamma50/F");
  finalTreeTurnOn->Branch("ptOnlineGamma75",&finalTreeTurnOn_ptOnlineGamma75,"ptOnlineGamma75/F");
  finalTreeTurnOn->Branch("ptOnlineGamma90",&finalTreeTurnOn_ptOnlineGamma90,"ptOnlineGamma90/F");

  finalTreeTurnOn->Branch("hltmatchGamma20",&finalTreeTurnOn_hltmatchGamma20,"hltmatchGamma20/i");
  finalTreeTurnOn->Branch("hltmatchGamma30",&finalTreeTurnOn_hltmatchGamma30,"hltmatchGamma30/i");
  finalTreeTurnOn->Branch("hltmatchGamma50",&finalTreeTurnOn_hltmatchGamma50,"hltmatchGamma50/i");
  finalTreeTurnOn->Branch("hltmatchGamma75",&finalTreeTurnOn_hltmatchGamma75,"hltmatchGamma75/i");
  finalTreeTurnOn->Branch("hltmatchGamma90",&finalTreeTurnOn_hltmatchGamma90,"hltmatchGamma90/i");

  /*
  finalTreeTurnOn->Branch("mass",       &finalTreeTurnOn_mass,       "mass/F");
  finalTreeTurnOn->Branch("ptEle1",     &finalTreeTurnOn_ptEle1,     "ptEle1/F");
  finalTreeTurnOn->Branch("ptEle2",     &finalTreeTurnOn_ptEle2,     "ptEle2/F");
  finalTreeTurnOn->Branch("etaEle1",    &finalTreeTurnOn_etaEle1,    "etaEle1/F");
  finalTreeTurnOn->Branch("etaEle2",    &finalTreeTurnOn_etaEle2,    "etaEle2/F");
  finalTreeTurnOn->Branch("tagEle1",    &finalTreeTurnOn_tagEle1,    "tagEle1/i");
  finalTreeTurnOn->Branch("tagEle2",    &finalTreeTurnOn_tagEle2,    "tagEle2/i");
  finalTreeTurnOn->Branch("isAZ",       &finalTreeTurnOn_isAZ,       "isAZ/i");  
  finalTreeTurnOn->Branch("isAZ_tight", &finalTreeTurnOn_isAZ_tight, "isAZ_tight/i");  
  */

  finalTreeTurnOn->Branch("passHLT30",  &finalTreeTurnOn_passHLT30,  "passHLT30/i");
  finalTreeTurnOn->Branch("passHLT50",  &finalTreeTurnOn_passHLT50,  "passHLT50/i");
  finalTreeTurnOn->Branch("passHLT75",  &finalTreeTurnOn_passHLT75,  "passHLT75/i");
  finalTreeTurnOn->Branch("passHLT90",  &finalTreeTurnOn_passHLT90,  "passHLT90/i");
  finalTreeTurnOn->Branch("passHLT135", &finalTreeTurnOn_passHLT135, "passHLT135/i");
  finalTreeTurnOn->Branch("passHLT150", &finalTreeTurnOn_passHLT150, "passHLT150/i");

  finalTreeTurnOn->Branch("run",  &finalTreeTurnOn_run,  "run/i");
  finalTreeTurnOn->Branch("lumi", &finalTreeTurnOn_lumi, "lumi/i");
  finalTreeTurnOn->Branch("event",&finalTreeTurnOn_event,"event/i");
  finalTreeTurnOn->Branch("nvtx", &finalTreeTurnOn_nvtx, "nvtx/i");
  finalTreeTurnOn->Branch("rho",  &finalTreeTurnOn_rho,  "rho/F");
}

void TurnOnCurveGamma::FillTreeEvent() {

  finalTreeTurnOn_ptGamma20=pt_match20;
  finalTreeTurnOn_ptGamma30=pt_match30;
  finalTreeTurnOn_ptGamma50=pt_match50;
  finalTreeTurnOn_ptGamma75=pt_match75;
  finalTreeTurnOn_ptGamma90=pt_match90;
  // here we'd need 135 as well, but the info is missing in our ntuples. Use 90 for both 135 and 150

  finalTreeTurnOn_etaGamma20=eta_match20;
  finalTreeTurnOn_etaGamma30=eta_match30;
  finalTreeTurnOn_etaGamma50=eta_match50;
  finalTreeTurnOn_etaGamma75=eta_match75;
  finalTreeTurnOn_etaGamma90=eta_match90;

  finalTreeTurnOn_ptOnlineGamma20=pt_online_match20;
  finalTreeTurnOn_ptOnlineGamma30=pt_online_match30;
  finalTreeTurnOn_ptOnlineGamma50=pt_online_match50;
  finalTreeTurnOn_ptOnlineGamma75=pt_online_match75;
  finalTreeTurnOn_ptOnlineGamma90=pt_online_match90;

  finalTreeTurnOn_hltmatchGamma20=match20;
  finalTreeTurnOn_hltmatchGamma30=match30;
  finalTreeTurnOn_hltmatchGamma50=match50;
  finalTreeTurnOn_hltmatchGamma75=match75;
  finalTreeTurnOn_hltmatchGamma90=match90;

  /*
  finalTreeTurnOn_mass=mass;
  finalTreeTurnOn_ptEle1=ptEle1;
  finalTreeTurnOn_ptEle2=ptEle2;
  finalTreeTurnOn_etaEle1=etaEle1;
  finalTreeTurnOn_etaEle2=etaEle2;
  finalTreeTurnOn_tagEle1=isTagTightEle[theEle1];
  finalTreeTurnOn_tagEle2=isTagTightEle[theEle2]; 
  finalTreeTurnOn_isAZ=isAZ;
  finalTreeTurnOn_isAZ_tight=isAZ_tight;
  */

  finalTreeTurnOn_passHLT30=isHLT30;
  finalTreeTurnOn_passHLT50=isHLT50;
  finalTreeTurnOn_passHLT75=isHLT75;
  finalTreeTurnOn_passHLT90=isHLT90;  
  finalTreeTurnOn_passHLT135=isHLT135;  
  finalTreeTurnOn_passHLT150=isHLT150;

  finalTreeTurnOn_run=run;
  finalTreeTurnOn_lumi=lumi;  
  finalTreeTurnOn_event=event;
  finalTreeTurnOn_nvtx=nvtx;
  finalTreeTurnOn_rho=rhoAllJets;

  return;
}
