#ifndef GammaJetsSelection_h
#define GammaJetsSelection_h

#include "tree_reader.h"

#include "TLorentzVector.h"
#include <TFile.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TString.h>
#include<vector>
#include<string>
#include <TChain.h>

#include "TMVA/Reader.h"

using std::string;
using std::vector;

class GammaJetsSelection : public tree_reader {

public:
  
  GammaJetsSelection(TTree *tree=0, const TString& outname="redntp.root");
  virtual ~GammaJetsSelection();
  virtual void     Loop();
  void SetJsonFile(const char* json) { jsonFile = json; };
  void SetPuWeights(std::string puWeightFile);
  
private:
  TFile* hOutputFile ;
  TTree * ana_tree ;
  
  vector<bool> jetnoisophot;
  
  const char* jsonFile;
  
  void SetAllRecoVarToMinus999();

  virtual vector<int> firstones(Float_t * vec, vector<bool> *asso, int number=4);

  bool  PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) ;

  //photon category functions (r9 and eta)
  int PhotonCategory(int photonindex) { 
    return PhotonR9Category(photonindex) + 2*PhotonEtaCategory(photonindex);
  }

  Int_t PhotonR9Category(int photonindex) { 
    if(photonindex < 0) return -1;
    int r9cat = (Int_t)(E9Phot[photonindex]/escRawPhot[photonindex]<0.94);// 0, 1(high r9 --> low r9)
    return r9cat;
  }

  int PhotonEtaCategory(int photonindex) {
    if(photonindex < 0) return -1;
    //int etacat = (Int_t)(!isEBPhot[photonindex]);   // 0, 1 (barrel --> endcap)
    int etacat = (Int_t)(TMath::Abs(etascPhot[photonindex])>1.479);   // 0, 1 (barrel --> endcap)
    return  etacat;
  }

  // vector of pu weights
  std::vector<Double_t> puweights_;

  Int_t runRN;
  Int_t eventRN;
  Float_t nvtx;
  Float_t rhoPFRN;
  Float_t rhoAllJetsRN;
  Int_t npu;
  Float_t pu_weight;

  Float_t gen_pt_gamma1;
  Float_t gen_eta_gamma1;
  Float_t gen_phi_gamma1;

  Int_t njets;
  Float_t ptjet[10];
  Float_t ptcorrjet[10];
  Float_t ecorrjet[10];
  Float_t etajet[10];
  Float_t phijet[10];
  Float_t betajet[10];
  Float_t betastarjet[10];
  Float_t rmsjet[10];

  Float_t ptphot1;
  Float_t deltaRToTrackphot1;
  Float_t etaphot1;
  Float_t phiphot1;
  Float_t etascphot1;
  Float_t E1phot1;
  Float_t E9phot1;
  Float_t r9phot1;
  Int_t   pid_haspixelseedphot1; 
  Float_t pid_HoverEphot1;
  Float_t pid_sigmaIeIephot1;
  Float_t pid_hlwTrack04phot1;
  Float_t pid_jurECAL04phot1;
  Float_t pid_twrHCAL04phot1;
  Float_t pid_pfIsoCharged03phot1;
  Float_t pid_pfIsoPhotons03phot1;
  Float_t pid_pfIsoNeutrals03phot1;
  Float_t pid_pfIsoCharged04phot1;
  Float_t pid_pfIsoPhotons04phot1;
  Float_t pid_pfIsoNeutrals04phot1;
  Int_t   pid_hasMatchedConvphot1;
  Int_t   pid_hasMatchedPromptElephot1;

  Int_t vtxId;
  Float_t vtxPos_x;
  Float_t vtxPos_y;
  Float_t vtxPos_z;

   // int nFiredHLT;
   std::vector<std::string>*  aHLTNames;
   std::vector<bool>*  aHLTResults;

   float weight;
};
#endif
