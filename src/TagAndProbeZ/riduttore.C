#define riduttore_cxx
#include "riduttore.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

void riduttore::Loop()
{
  if (fChain == 0) return;

  // hardcoded
  bool runOnMC = false;

  // output file
  TFile *outFile[5];
  outFile[0] = new TFile("outFile.root","RECREATE");
  outFile[1] = new TFile("outFile30.root","RECREATE");
  outFile[2] = new TFile("outFile50.root","RECREATE");
  outFile[3] = new TFile("outFile75.root","RECREATE");
  outFile[4] = new TFile("outFile90.root","RECREATE");

  // output trees declaration
  TTree *myTree[5];
  for (int ii=0; ii<5; ii++) {
    myTree[ii] = new TTree();
    myTree[ii] -> SetName("myTree");
  }

  float mass;
  float probe_eta, probe_abseta, probe_phi, probe_pt;
  float numvtx;
  float puW;
  float puW30, puW50, puW75, puW90;  
  int okLooseElePtEta,  okLooseEleID;
  int okMediumElePtEta, okMediumEleID; 
  int okTightElePtEta,  okTightEleID; 
  int okMVA_005, okMVA_01, okMVA_02;

  for (int ii=0; ii<5; ii++) {
    myTree[ii] -> Branch("mass",&mass,"mass/F");
    myTree[ii] -> Branch("probe_eta",&probe_eta,"probe_eta/F");
    myTree[ii] -> Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
    myTree[ii] -> Branch("probe_phi",&probe_phi,"probe_phi/F");
    myTree[ii] -> Branch("probe_pt",&probe_pt,"probe_pt/F");
    myTree[ii] -> Branch("numvtx",&numvtx,"numvtx/F");
    myTree[ii] -> Branch("puW",  &puW,  "puW/F");
    myTree[ii] -> Branch("puW30",&puW30,"puW30/F");
    myTree[ii] -> Branch("puW50",&puW50,"puW50/F");
    myTree[ii] -> Branch("puW75",&puW75,"puW75/F");
    myTree[ii] -> Branch("puW90",&puW90,"puW90/F");
    myTree[ii] -> Branch("okLooseElePtEta",&okLooseElePtEta,"okLooseElePtEta/I");
    myTree[ii] -> Branch("okLooseEleID",&okLooseEleID,"okLooseEleID/I");
    myTree[ii] -> Branch("okMediumElePtEta",&okMediumElePtEta,"okMediumElePtEta/I");
    myTree[ii] -> Branch("okMediumEleID",&okMediumEleID,"okMediumEleID/I");
    myTree[ii] -> Branch("okTightElePtEta",&okTightElePtEta,"okTightElePtEta/I");
    myTree[ii] -> Branch("okTightEleID",&okTightEleID,"okTightEleID/I");
    myTree[ii] -> Branch("okMVA_005",&okMVA_005,"okMVA_005/I");
    myTree[ii] -> Branch("okMVA_01",&okMVA_01,"okMVA_01/I");
    myTree[ii] -> Branch("okMVA_02",&okMVA_02,"okMVA_02/I");
  }

  // Loop over events
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Going to loop over " << nentries << " events" << endl;
  cout << endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry%5000==0) cout << "entry " << ientry << endl;
    
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    for (int iEle=0; iEle<nEle; iEle++) {
      if ( runOnMC && !isEleTag_match[iEle]) continue;
      if (!runOnMC && !isEleTag[iEle]) continue;
      TLorentzVector theEle;
      theEle.SetPtEtaPhiE(electron_pt[iEle], electron_eta[iEle], electron_phi[iEle], electron_energy[iEle]);

      for (int iPho=0; iPho<nPhot; iPho++) {
	if ( runOnMC && !isEleProbe_match[iPho]) continue;
	if (!runOnMC && !isEleProbe[iPho]) continue;
	TLorentzVector thePho;
	thePho.SetPtEtaPhiE(ptPhot[iPho], etaPhot[iPho], phiPhot[iPho], ePhot[iPho]);
      
	TLorentzVector theTaP = theEle + thePho;
	float theMass = theTaP.M();
      
	if (theMass<120 && theMass>60) {

	  // filling the tree
	  mass = theMass;

	  probe_eta    = etaPhot[iPho];
	  probe_abseta = fabs(etaPhot[iPho]);
	  probe_phi    = phiPhot[iPho];
	  probe_pt     = ptPhot[iPho];

	  numvtx = nvtx;

	  if(runOnMC) {
	    puW   = pu_weight;
	    puW30 = pu_weight30;
	    puW50 = pu_weight50;
	    puW75 = pu_weight75;
	    puW90 = pu_weight90;
	  } else {
	    puW   = 1.;
	    puW30 = 1.;
	    puW50 = 1.;
	    puW75 = 1.;
	    puW90 = 1.;
	  }

	  if(runOnMC) {
	    okLooseElePtEta  = passLooseElePtEta_match[iPho];
	    okLooseEleID     = passLooseEleID_match[iPho];
	    okMediumElePtEta = passMediumElePtEta_match[iPho];
	    okMediumEleID    = passMediumEleID_match[iPho];
	    okTightElePtEta  = passTightElePtEta_match[iPho];
	    okTightEleID     = passTightEleID_match[iPho];
	  } else {
	    okLooseElePtEta  = passLooseElePtEta[iPho];
	    okLooseEleID     = passLooseEleID[iPho];
	    okMediumElePtEta = passMediumElePtEta[iPho];
	    okMediumEleID    = passMediumEleID[iPho];
	    okTightElePtEta  = passTightElePtEta[iPho];
	    okTightEleID     = passTightEleID[iPho];
	  }

	  // MVA WPs
	  okMVA_005 = 0;
	  okMVA_01  = 0;
	  okMVA_02  = 0;
	  if (fabs(etaPhot[iPho])<1.5) {
	    if ( BDT_output[iPho]>0.711099 ) okMVA_005 = 1;
	    if ( BDT_output[iPho]>0.812948 ) okMVA_01  = 1;
	    if ( BDT_output[iPho]>0.878893 ) okMVA_02  = 1;
	  } else {
	    if ( BDT_output[iPho]>0.581733 ) okMVA_005 = 1;
	    if ( BDT_output[iPho]>0.73721  ) okMVA_01  = 1;
	    if ( BDT_output[iPho]>0.850808 ) okMVA_02  = 1;
	  }

	  // check HLT and pT range
	  if (!runOnMC) {
	    if ( isHLT_TandP() )                                           myTree[0]->Fill();
	    if ( isHLT_30() && ptPhot[iPho]>=40 && ptPhot[iPho]<65 )       myTree[1]->Fill();
	    if ( isHLT_50() && ptPhot[iPho]>=65 && ptPhot[iPho]<90 )       myTree[2]->Fill();
	    if ( isHLT_75() && ptPhot[iPho]>=90 && ptPhot[iPho]<105 )      myTree[3]->Fill();
	    if ( isHLT_90() && ptPhot[iPho]>=105 && ptPhot[iPho]<200000 )  myTree[4]->Fill();
	    }
	  if (runOnMC) {
	    myTree[0]->Fill();
	    if ( ptPhot[iPho]>=40 && ptPhot[iPho]<65 )       myTree[1]->Fill();
	    if ( ptPhot[iPho]>=65 && ptPhot[iPho]<90 )       myTree[2]->Fill();
	    if ( ptPhot[iPho]>=90 && ptPhot[iPho]<105 )      myTree[3]->Fill();
	    if ( ptPhot[iPho]>=105 && ptPhot[iPho]<200000 )  myTree[4]->Fill();
	  }

	}  // ok mass
      } // loop over photons
    }   // loop over electrons
  }  // entries

  for (int ii=0; ii<5; ii++) {
    outFile[ii]->cd();
    TDirectory* outputDirectory = outFile[ii]->mkdir("myTaPDir");
    outputDirectory->cd();
    myTree[ii]->Write();
    outFile[ii]->Close();
  }
}

bool riduttore::isHLT_TandP() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v3") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v4") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v5") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v6") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v7") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v3")   isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v4")   isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v5")   isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v6")   isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_Mass50_v7")   isok=true;
  }
  return isok;
}

bool riduttore::isHLT_30() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v18") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v19") isok=true;
  }
  return isok;
}

bool riduttore::isHLT_50() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v17") isok=true;
  }
  return isok;
}

bool riduttore::isHLT_75() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v18") isok=true;
  }
  return isok;
}

bool riduttore::isHLT_90() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v13") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v15") isok=true;
  }
  return isok;
}
