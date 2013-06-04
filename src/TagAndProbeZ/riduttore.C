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
  TFile *outFile[1];
  outFile[0] = new TFile("outFile.root","RECREATE");

  // output trees declaration
  TTree *myTree[1];
  for (int ii=0; ii<1; ii++) {
    myTree[ii] = new TTree();
    myTree[ii] -> SetName("myTree");
  }

  float mass;
  float probe_eta, probe_abseta, probe_phi, probe_pt;
  float probe_bdt;
  float numvtx;
  float puW;
  int okLooseEleID, okMediumEleID, okTightEleID;  
  int okMVA_005, okMVA_01, okMVA_02;

  for (int ii=0; ii<1; ii++) {
    myTree[ii] -> Branch("mass",&mass,"mass/F");
    myTree[ii] -> Branch("probe_eta",&probe_eta,"probe_eta/F");
    myTree[ii] -> Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
    myTree[ii] -> Branch("probe_phi",&probe_phi,"probe_phi/F");
    myTree[ii] -> Branch("probe_pt",&probe_pt,"probe_pt/F");
    myTree[ii] -> Branch("probe_bdt",&probe_bdt,"probe_bdt/F");
    myTree[ii] -> Branch("numvtx",&numvtx,"numvtx/F");
    myTree[ii] -> Branch("puW",  &puW,  "puW/F");
    myTree[ii] -> Branch("okLooseEleID",&okLooseEleID,"okLooseEleID/I");
    myTree[ii] -> Branch("okMediumEleID",&okMediumEleID,"okMediumEleID/I");
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
  // for (Long64_t jentry=0; jentry<nentries;jentry++) {
  for (Long64_t jentry=0; jentry<1700000;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry%5000==0) cout << "entry " << ientry << endl;
    
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    for (int iEle=0; iEle<nEle; iEle++) {  // Tight => Medium
      if ( runOnMC && (!isGenMatchEle[iEle] || !isTagTightEle[iEle]) ) continue;
      if (!runOnMC && !isTagTightEle[iEle]) continue;  
      TLorentzVector theEle;
      theEle.SetPtEtaPhiM(electron_pt[iEle], electron_eta[iEle], electron_phi[iEle], 0.);

      for (int iPho=0; iPho<nPhot; iPho++) {
	if ( runOnMC &&( !isGenMatchPhot[iPho] || !isProbePreselPhot[iPho])) continue;
	if (!runOnMC && !isProbePreselPhot[iPho]) continue;

	// if (r9Phot[iPho]<0.94) continue;  // high R9 only
	// if (r9Phot[iPho]>0.94) continue;  // low R9 only

	TLorentzVector thePho;
	thePho.SetPtEtaPhiM(ptPhot[iPho], etaPhot[iPho], phiPhot[iPho], 0.);
      
	TLorentzVector theTaP = theEle + thePho;
	float theMass = theTaP.M();
	if (theMass<120 && theMass>60) {

	  // filling the tree
	  mass = theMass;

	  probe_eta    = etaPhot[iPho];
	  probe_abseta = fabs(etaPhot[iPho]);
	  probe_phi    = phiPhot[iPho];
	  probe_pt     = ptPhot[iPho];
	  probe_bdt    = mvaIDPhot[iPho];

	  numvtx = nvtx;

	  if(runOnMC) puW = pu_weight;
	  else puW = 1.;
	  
	  okLooseEleID  = isProbeLoosePhot[iPho];
	  okMediumEleID = isProbeMediumPhot[iPho];
	  okTightEleID  = isProbeTightPhot[iPho];

	  // MVA WPs
	  okMVA_005 = 0;
	  okMVA_01  = 0;
	  okMVA_02  = 0;
	  if (fabs(etaPhot[iPho])<1.5) {
	    if ( mvaIDPhot[iPho]>0.711099 ) okMVA_005 = 1;
	    if ( mvaIDPhot[iPho]>0.812948 ) okMVA_01  = 1;
	    if ( mvaIDPhot[iPho]>0.878893 ) okMVA_02  = 1;
	  } else {
	    if ( mvaIDPhot[iPho]>0.581733 ) okMVA_005 = 1;
	    if ( mvaIDPhot[iPho]>0.73721  ) okMVA_01  = 1;
	    if ( mvaIDPhot[iPho]>0.850808 ) okMVA_02  = 1;
	  }

	  // check HLT and pT range
	  if (!runOnMC) {
	    if ( isHLT_TandP() ) myTree[0]->Fill();
	  } else {
	    myTree[0]->Fill();
	  }

	}  // ok mass
      } // loop over photons
    }   // loop over electrons
  }  // entries

  for (int ii=0; ii<1; ii++) {
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

