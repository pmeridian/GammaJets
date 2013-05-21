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
  bool runOnMC = true;

  // output file
  TFile outFile("outFile.root","RECREATE");

  // output tree declaration
  TTree *myTree = new TTree();
  myTree->SetName("myTree");

  float mass;
  float probe_eta, probe_abseta, probe_phi, probe_pt;
  float numvtx;
  float puW30, puW50, puW75, puW90;  
  int okLooseElePtEta; 
  int okLooseEleID;
  int okMediumElePtEta; 
  int okMediumEleID; 
  int okTightElePtEta; 
  int okTightEleID; 

  myTree->Branch("mass",&mass,"mass/F");
  myTree->Branch("probe_eta",&probe_eta,"probe_eta/F");
  myTree->Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
  myTree->Branch("probe_phi",&probe_phi,"probe_phi/F");
  myTree->Branch("probe_pt",&probe_pt,"probe_pt/F");
  myTree->Branch("numvtx",&numvtx,"numvtx/F");
  myTree->Branch("puW30",&puW30,"puW30/F");
  myTree->Branch("puW50",&puW50,"puW50/F");
  myTree->Branch("puW75",&puW75,"puW75/F");
  myTree->Branch("puW90",&puW90,"puW90/F");
  myTree->Branch("okLooseElePtEta",&okLooseElePtEta,"okLooseElePtEta/I");
  myTree->Branch("okLooseEleID",&okLooseEleID,"okLooseEleID/I");
  myTree->Branch("okMediumElePtEta",&okMediumElePtEta,"okMediumElePtEta/I");
  myTree->Branch("okMediumEleID",&okMediumEleID,"okMediumEleID/I");
  myTree->Branch("okTightElePtEta",&okTightElePtEta,"okTightElePtEta/I");
  myTree->Branch("okTightEleID",&okTightEleID,"okTightEleID/I");


  // Loop over events
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Going to loop over " << nentries << " events" << endl;
  cout << endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // for (Long64_t jentry=0; jentry<200000;jentry++) {   
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

	  numvtx       = nvtx;

	  puW30        = pu_weight30;
	  puW50        = pu_weight50;
	  puW75        = pu_weight75;
	  puW90        = pu_weight90;

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

	  myTree->Fill();
	}  // ok mass
      } // loop over photons
    }   // loop over electrons
  }  // entries

  outFile.cd();
  TDirectory* outputDirectory = outFile.mkdir("myTaPDir");
  outputDirectory->cd();
  myTree->Write();
  outFile.Close();
}
