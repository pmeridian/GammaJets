#define TagAndProbeAnalysis_cxx
#include "TagAndProbeAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <TLorentzVector.h>

using namespace std;

void TagAndProbeAnalysis::Loop()
{
  if (fChain == 0) return;

  readR9Weights();
  
  // output file
  TFile *outFile[5];
  outFile[0] = new TFile(outFileNamePrefix+"_tag"+tagTightnessLevel+(mcMatch==0 ? "" : "_mcMatch"+TString::Format("%d",mcMatch))+"_HLT"+".root","RECREATE");
  outFile[1] = new TFile(outFileNamePrefix+"_tag"+tagTightnessLevel+(mcMatch==0 ? "" : "_mcMatch"+TString::Format("%d",mcMatch))+"_HLT"+"30.root","RECREATE");
  outFile[2] = new TFile(outFileNamePrefix+"_tag"+tagTightnessLevel+(mcMatch==0 ? "" : "_mcMatch"+TString::Format("%d",mcMatch))+"_HLT"+"50.root","RECREATE");
  outFile[3] = new TFile(outFileNamePrefix+"_tag"+tagTightnessLevel+(mcMatch==0 ? "" : "_mcMatch"+TString::Format("%d",mcMatch))+"_HLT"+"75.root","RECREATE");
  outFile[4] = new TFile(outFileNamePrefix+"_tag"+tagTightnessLevel+(mcMatch==0 ? "" : "_mcMatch"+TString::Format("%d",mcMatch))+"_HLT"+"90.root","RECREATE");

  // output trees declaration
  TTree *myTree[5];
  for (int ii=0; ii<5; ii++) {
    outFile[ii]->cd();
    TDirectory* outputDirectory = outFile[ii]->mkdir("myTaPDir");
    outputDirectory->cd();
    myTree[ii] = new TTree();
    myTree[ii] -> SetName("myTree");
  }

  float mass;
  float probe_eta, probe_abseta, probe_phi, probe_pt, probe_r9;
  int numvtx;
  float rho;
  float r9weight_EB;
  float r9weight_EE;
  float puW;
  float puW30, puW50, puW75, puW90;  
  int okLooseElePtEta,  okLooseEleID;
  int okMediumElePtEta, okMediumEleID; 
  int okTightElePtEta,  okTightEleID; 
  int okMVA_005, okMVA_01, okMVA_02;
  int hasPromptElectronMatched;
  float probe_pid_scetawid, probe_pid_scphiwid;
  float probe_sEtaEta, probe_sEtaPhi;
  float probe_s4Ratio, probe_etasc;
  float probe_rr;
  float probe_mvaId;
  float probe_fprCharged03,   probe_fprNeutral03,   probe_fprPhoton03;
  float probe_fprRCCharged03, probe_fprRCNeutral03, probe_fprRCPhoton03;
  // float probe_fprCharged04,   probe_fprNeutral04,   probe_fprPhoton04;
  // float probe_fprRCCharged04, probe_fprRCNeutral04, probe_fprRCPhoton04;

  for (int ii=0; ii<5; ii++) {
    myTree[ii] -> Branch("mass",&mass,"mass/F");
    myTree[ii] -> Branch("probe_eta",&probe_eta,"probe_eta/F");
    myTree[ii] -> Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
    myTree[ii] -> Branch("probe_phi",&probe_phi,"probe_phi/F");
    myTree[ii] -> Branch("probe_pt",&probe_pt,"probe_pt/F");
    myTree[ii] -> Branch("probe_r9",&probe_r9,"probe_r9/F");
    myTree[ii] -> Branch("probe_pid_scetawid",&probe_pid_scetawid,"probe_pid_scetawid/F");
    myTree[ii] -> Branch("probe_pid_scphiwid",&probe_pid_scphiwid,"probe_pid_scphiwid/F");
    myTree[ii] -> Branch("probe_sEtaEta",&probe_sEtaEta,"probe_sEtaEta/F");
    myTree[ii] -> Branch("probe_sEtaPhi",&probe_sEtaPhi,"probe_sEtaPhi/F");
    myTree[ii] -> Branch("probe_s4Ratio",&probe_s4Ratio,"probe_s4Ratio/F");
    myTree[ii] -> Branch("probe_etasc",&probe_etasc,"probe_etasc/F");
    myTree[ii] -> Branch("probe_rr",&probe_rr,"probe_rr/F");
    myTree[ii] -> Branch("probe_mvaId",&probe_mvaId,"probe_mvaId/F"); 
    myTree[ii] -> Branch("probe_fprCharged03",&probe_fprCharged03,"probe_fprCharged03/F"); 
    myTree[ii] -> Branch("probe_fprNeutral03",&probe_fprNeutral03,"probe_fprNeutral03/F"); 
    myTree[ii] -> Branch("probe_fprPhoton03", &probe_fprPhoton03, "probe_fprPhoton03/F"); 
    myTree[ii] -> Branch("probe_fprRCCharged03",&probe_fprRCCharged03,"probe_fprRCCharged03/F"); 
    myTree[ii] -> Branch("probe_fprRCNeutral03",&probe_fprRCNeutral03,"probe_fprRCNeutral03/F"); 
    myTree[ii] -> Branch("probe_fprRCPhoton03", &probe_fprRCPhoton03, "probe_fprRCPhoton03/F"); 
    /*
    myTree[ii] -> Branch("probe_fprCharged04",&probe_fprCharged04,"probe_fprCharged04/F"); 
    myTree[ii] -> Branch("probe_fprNeutral04",&probe_fprNeutral04,"probe_fprNeutral04/F"); 
    myTree[ii] -> Branch("probe_fprPhoton04", &probe_fprPhoton04, "probe_fprPhoton04/F"); 
    myTree[ii] -> Branch("probe_fprRCCharged04",&probe_fprRCCharged04,"probe_fprRCCharged04/F"); 
    myTree[ii] -> Branch("probe_fprRCNeutral04",&probe_fprRCNeutral04,"probe_fprRCNeutral04/F"); 
    myTree[ii] -> Branch("probe_fprRCPhoton04", &probe_fprRCPhoton04, "probe_fprRCPhoton04/F"); 
    */
    myTree[ii] -> Branch("numvtx",&numvtx,"numvtx/I");
    myTree[ii] -> Branch("rho",&rho,"rho/F");
    myTree[ii] -> Branch("puW",  &puW,  "puW/F");
    myTree[ii] -> Branch("r9WeightEB",  &r9weight_EB,  "r9WeightEB/F");
    myTree[ii] -> Branch("r9WeightEE",  &r9weight_EE,  "r9WeightEE/F");
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
    myTree[ii] -> Branch("hasPromptElectronMatched",&hasPromptElectronMatched,"hasPromptElectronMatched/I");
  }

  // Loop over events
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Going to loop over " << nentries << " events" << endl;
  cout << endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (jentry%5000==0) cout << "Read entry " << jentry << endl;

    for (int iEle=0; iEle<nEle; iEle++) {
      
      if (isMC && mcMatch)
	if (!isGenMatchEle[iEle])
	  continue;

      if (tagTightnessLevel=="Tight")
	{
	  if (!isTagTightEle[iEle])
	    continue;
	}
      else if (tagTightnessLevel=="Medium")
	{
	  if (!isTagMediumEle[iEle])
	    continue;
	}
      else if (tagTightnessLevel=="Loose")
	{
	  if (!isTagLooseEle[iEle])
	    continue;
	}
      else
	{
	  std::cout << "Tag Selection undefined" << std::endl;
	  exit(-1);
	}


      // we ask:
      // the event to fire one of the two T&P HLT paths
      // the tag electron to match the hard leg of the fired HLT path 
      bool hltMatch = false;
      if (isHLT_TandP_Ele17() && isTrig17Mass50MatchedEle[iEle]) hltMatch = true;  
      if (isHLT_TandP_Ele20() && isTrig20Mass50MatchedEle[iEle]) hltMatch = true;  
      if (!hltMatch) continue;


      TLorentzVector theEle;
      theEle.SetPtEtaPhiM(electron_pt[iEle], electron_eta[iEle], electron_phi[iEle], 0.);

      for (int iPho=0; iPho<nPhot; iPho++) {
	if (isMC && mcMatch)
	  if (!isGenMatchPhot[iPho])
	    continue;

	//apply preselection as probe selection for photons (should be loosened to measure preselection SF)
	if (!isProbePreselPhot[iPho])
	  continue;

	TLorentzVector thePho;
	thePho.SetPtEtaPhiE(ptPhot[iPho], etaPhot[iPho], phiPhot[iPho], ePhot[iPho]);
      
	TLorentzVector theTaP = theEle + thePho;
	float theMass = theTaP.M();
      
	if (fabs(theMass-91.181)>DeltaMZ)
	  continue;

	// filling the tree
	mass = theMass;
	
	probe_eta    = etascPhot[iPho];
	probe_abseta = fabs(etascPhot[iPho]);
	probe_phi    = phiPhot[iPho];
	probe_pt     = ptPhot[iPho];
	probe_r9     = r9Phot[iPho];
	
	probe_pid_scetawid = pid_scetawid[iPho];
	probe_pid_scphiwid = pid_scphiwid[iPho];
	probe_sEtaEta      = sEtaEtaPhot[iPho];
	probe_sEtaPhi      = sEtaPhiPhot[iPho];
	probe_s4Ratio      = s4RatioPhot[iPho];
	probe_etasc        = etascPhot[iPho];
	probe_rr           = sigmaRRPhot[iPho]; 
	probe_mvaId        = mvaIDPhot[iPho]; 

	probe_fprCharged03   = pid_pfIsoFPRCharged03[iPho]; 
	probe_fprNeutral03   = pid_pfIsoFPRNeutral03[iPho]; 
	probe_fprPhoton03    = pid_pfIsoFPRPhoton03[iPho]; 
	probe_fprRCCharged03 = pid_pfIsoFPRRandomConeCharged03[iPho]; 
	probe_fprRCNeutral03 = pid_pfIsoFPRRandomConeNeutral03[iPho]; 
	probe_fprRCPhoton03  = pid_pfIsoFPRRandomConePhoton03[iPho]; 
	/*
	probe_fprCharged04   = pid_pfIsoFPRCharged04[iPho]; 
	probe_fprNeutral04   = pid_pfIsoFPRNeutral04[iPho]; 
	probe_fprPhoton04    = pid_pfIsoFPRPhoton04[iPho]; 
	probe_fprRCCharged04 = pid_pfIsoFPRRandomConeCharged04[iPho]; 
	probe_fprRCNeutral04 = pid_pfIsoFPRRandomConeNeutral04[iPho]; 
	probe_fprRCPhoton04  = pid_pfIsoFPRRandomConePhoton04[iPho]; 
	*/

	numvtx = nvtx;
	rho=rhoAllJets;

	if(isMC) {
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
	

	if (r9Reweight)
	  {
	    r9weight_EB=r9weights_EB->GetBinContent(r9weights_EB->FindBin(r9Phot[iPho]));
	    r9weight_EE=r9weights_EE->GetBinContent(r9weights_EE->FindBin(r9Phot[iPho]));
	  }
	else
	  {
	    r9weight_EB=1.;
	    r9weight_EE=1.;
	  }


	okLooseElePtEta  = 1;
	okLooseEleID     = isProbeLoosePhot[iPho];
	okMediumElePtEta = 1;
	okMediumEleID    = isProbeMediumPhot[iPho];
	okTightElePtEta  = 1;
	okTightEleID     = isProbeTightPhot[iPho];

	hasPromptElectronMatched = hasMatchedPromptElePhot[iPho];

	// MVA WPs
	okMVA_005 = 0;
	okMVA_01  = 0;
	okMVA_02  = 0;
	if (isEBPhot[iPho]) {
	  if ( mvaIDPhot[iPho]>0.711099 ) okMVA_005 = 1;
	  if ( mvaIDPhot[iPho]>0.812948 ) okMVA_01  = 1;
	  if ( mvaIDPhot[iPho]>0.878893 ) okMVA_02  = 1;
	} else {
	  if ( mvaIDPhot[iPho]>0.581733 ) okMVA_005 = 1;
	  if ( mvaIDPhot[iPho]>0.73721  ) okMVA_01  = 1;
	  if ( mvaIDPhot[iPho]>0.850808 ) okMVA_02  = 1;
	}
	
	// check HLT and pT range
	if (!isMC) {
	  myTree[0]->Fill();
	  if ( isHLT_30() && ptPhot[iPho]>=40 && ptPhot[iPho]<65 )       myTree[1]->Fill();
	  if ( isHLT_50() && ptPhot[iPho]>=65 && ptPhot[iPho]<90 )       myTree[2]->Fill();
	  if ( isHLT_75() && ptPhot[iPho]>=90 && ptPhot[iPho]<105 )      myTree[3]->Fill();
	  if ( isHLT_90() && ptPhot[iPho]>=105 && ptPhot[iPho]<200000 )  myTree[4]->Fill();
	}

	if (isMC) {
	  myTree[0]->Fill();
	  if ( ptPhot[iPho]>=40 && ptPhot[iPho]<65 )         myTree[1]->Fill();
	  if ( ptPhot[iPho]>=65 && ptPhot[iPho]<90 )         myTree[2]->Fill();
	  if ( ptPhot[iPho]>=90 && ptPhot[iPho]<105 )        myTree[3]->Fill();
	  if ( ptPhot[iPho]>=105 && ptPhot[iPho]<200000 )    myTree[4]->Fill();
	}
      
      } // loop over photons

    }   // loop over electrons
  }

  for (int ii=0; ii<5; ii++) {
    outFile[ii]->cd("myTaPDir");
    myTree[ii]->Write();
    outFile[ii]->Close();
  }
}

bool TagAndProbeAnalysis::isHLT_TandP_Ele20() {  

  bool isok = false;   


  for (int ii=0; ii<firedHLTNames->size(); ii++) {

    std::string input((*firedHLTNames)[ii]);
    int thestr = 0;
    for(thestr = input.find("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v", 0); 
	thestr != string::npos; 
	thestr = input.find("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v", thestr)) {
      // cout << "eccolo: " << (*firedHLTNames)[ii] << endl;
      return true;
    }
  }


  return isok;
}

bool TagAndProbeAnalysis::isHLT_TandP_Ele17() {  

  bool isok = false;   

  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    std::string input((*firedHLTNames)[ii]);
    int thestr = 0;
    for(thestr = input.find("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v", 0); 
	thestr != string::npos; 
	thestr = input.find("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v", thestr)) {
      // cout << "eccolo: " << (*firedHLTNames)[ii] << endl;
      return true;
    }
  }

  return isok;
}

bool TagAndProbeAnalysis::isHLT_30() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v18") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v19") isok=true;
  }
  return isok;
}

bool TagAndProbeAnalysis::isHLT_50() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v17") isok=true;
  }
  return isok;
}

bool TagAndProbeAnalysis::isHLT_75() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v18") isok=true;
  }
  return isok;
}

bool TagAndProbeAnalysis::isHLT_90() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v13") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v15") isok=true;
  }
  return isok;
}

void TagAndProbeAnalysis::readR9Weights()
{
  if (!r9Reweight)
    return;
  
  TFile *f=TFile::Open(r9WeightsFile);

  r9weights_EB=(TH1F*)f->Get("R9WeightEBAll");
  r9weights_EE=(TH1F*)f->Get("R9WeightEEAll");

  //Just do a smoothing of the weights
  r9weights_EB->Rebin(2);
  r9weights_EE->Rebin(2);

  r9weights_EB->Smooth(4);
  r9weights_EE->Smooth(4);
}
