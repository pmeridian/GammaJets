#define addWeightToTree_cxx
#include "addWeightToTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void addWeightToTree::Loop()
{
  if (fChain == 0) return;
  
  // isolation weight files
  TFile* fileWeights  = TFile::Open("histo_v6/genIso/isoWeight/WP95/isoWeights.root");
  
  // loading histos with weights
  TH1F* h1_isoW_EB          = (TH1F*)fileWeights->Get("h_isoWeight_EB");
  TH1F* h1_isoW_EE          = (TH1F*)fileWeights->Get("h_isoWeight_EE");
  TH1F* h1_isoW_EB_pt40_65  = (TH1F*)fileWeights->Get("h_isoWeight_EB_pt40_65");
  TH1F* h1_isoW_EE_pt40_65  = (TH1F*)fileWeights->Get("h_isoWeight_EE_pt40_65");
  TH1F* h1_isoW_EB_pt65_90  = (TH1F*)fileWeights->Get("h_isoWeight_EB_pt65_90");
  TH1F* h1_isoW_EE_pt65_90  = (TH1F*)fileWeights->Get("h_isoWeight_EE_pt65_90");
  TH1F* h1_isoW_EB_pt90_105 = (TH1F*)fileWeights->Get("h_isoWeight_EB_pt90_105");
  TH1F* h1_isoW_EE_pt90_105 = (TH1F*)fileWeights->Get("h_isoWeight_EE_pt90_105");
  TH1F* h1_isoW_EB_pt105    = (TH1F*)fileWeights->Get("h_isoWeight_EB_pt105");
  TH1F* h1_isoW_EE_pt105    = (TH1F*)fileWeights->Get("h_isoWeight_EE_pt105");
  
  // output tree, with modified weight
  TFile* outFile=TFile::Open("outputWithWeight.root","recreate");
  TTree* treeWithWeights= new TTree();
  treeWithWeights->SetName("myTrees_withWeight");
  createBranches(treeWithWeights);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if(jentry%50000==0) cout<<jentry<<endl;
    
    // remove events not to be analyzed
    if (weight==0) continue;
    
    // computing the isolation weight according eta/pT of the photon
    float isWeb,       isWee;
    float isWeb40_65,  isWee40_65;
    float isWeb65_90,  isWee65_90;
    float isWeb90_105, isWee90_105;
    float isWeb105,    isWee105;
    
    isWeb = h1_isoW_EB->GetBinContent(h1_isoW_EB->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    isWee = h1_isoW_EE->GetBinContent(h1_isoW_EE->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    
    if (ptPhot>=40 && ptPhot<65) {
      isWeb40_65 = h1_isoW_EB_pt40_65->GetBinContent(h1_isoW_EB_pt40_65->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
      isWee40_65 = h1_isoW_EE_pt40_65->GetBinContent(h1_isoW_EE_pt40_65->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    } else {
      isWeb40_65 = -1000.;
      isWee40_65 = -1000.;
    }
    
    if (ptPhot>=65 && ptPhot<90) {
      isWeb65_90 = h1_isoW_EB_pt65_90->GetBinContent(h1_isoW_EB_pt65_90->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
      isWee65_90 = h1_isoW_EE_pt65_90->GetBinContent(h1_isoW_EE_pt65_90->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    } else {
      isWeb65_90 = -1000.;
      isWee65_90 = -1000.;
    }
    
    if (ptPhot>=90 && ptPhot<105) {
      isWeb90_105 = h1_isoW_EB_pt90_105->GetBinContent(h1_isoW_EB_pt90_105->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
      isWee90_105 = h1_isoW_EE_pt90_105->GetBinContent(h1_isoW_EE_pt90_105->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    } else {
      isWeb90_105 = -1000.;
      isWee90_105 = -1000.;
    }

    if (ptPhot>=105) {
      isWeb105 = h1_isoW_EB_pt105->GetBinContent(h1_isoW_EB_pt105->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
      isWee105 = h1_isoW_EE_pt105->GetBinContent(h1_isoW_EE_pt105->GetXaxis()->FindBin(combinedPfIsoFPR03Phot));
    } else {
      isWeb105 = -1000.;
      isWee105 = -1000.;
    }
    
    // saving in the tree
    bool isEB = true;
    if ( fabs(etaPhot)>1.4442 ) isEB = false;      
    
    if (isEB) {
      isoW_EB_t          = isWeb;
      isoW_EB_pt40_65_t  = isWeb40_65;
      isoW_EB_pt65_90_t  = isWeb65_90;
      isoW_EB_pt90_105_t = isWeb90_105;
      isoW_EB_pt105_t    = isWeb105;
    } else {
      isoW_EB_t          = -1000.;
      isoW_EB_pt40_65_t  = -1000.; 
      isoW_EB_pt65_90_t  = -1000.; 
      isoW_EB_pt90_105_t = -1000.; 
      isoW_EB_pt105_t    = -1000.;
    }
    
    if (!isEB) {
      isoW_EE_t          = isWee;
      isoW_EE_pt40_65_t  = isWee40_65;
      isoW_EE_pt65_90_t  = isWee65_90;
      isoW_EE_pt90_105_t = isWee90_105;
      isoW_EE_pt105_t    = isWee105;
    } else {
      isoW_EE_t          = -1000.;
      isoW_EE_pt40_65_t  = -1000.; 
      isoW_EE_pt65_90_t  = -1000.; 
      isoW_EE_pt90_105_t = -1000.; 
      isoW_EE_pt105_t    = -1000.;
    }

    treeWithWeights->Fill();
  }
  
  cout << "done with the loop. Ready to write" << endl;
  treeWithWeights->Write();
  cout << "done with the writing" << endl;
  outFile->Write();
  outFile->Close();
}
