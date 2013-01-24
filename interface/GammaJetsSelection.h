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

  bool muTightId(int iMu);
  std::vector<int> sortMuonsByPt(std::vector<int> muons);

  std::pair<bool,bool> eleCutId2012(int iEle);
  double get03EleEffectiveAreas(float eta);
  bool eleMvaId2012_Hww(int iEle);
  bool eleMvaId2012_Hzz(int iEle);
  bool trainTrigPresel(int iEle);
  std::vector<int> sortElectronsByPt(std::vector<int> electrons);

  double eleDzPV(int iele, int iPV);
  double eleDxyPV(int iele, int iPV);
  double muonDzPV(int imu, int iPV);
  double muonDxyPV(int imu, int iPV);
  double trackDzPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);
  double trackDxyPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);  

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
  Int_t oneGenMuon;
  Int_t oneGenEle;

  Int_t njets;
  Float_t ptjet[10];
  Float_t ptcorrjet[10];
  Float_t ecorrjet[10];
  Float_t etajet[10];
  Float_t phijet[10];
  Float_t betajet[10];
  Float_t betastarjet[10];
  Float_t rmsjet[10];
  Int_t matchingMu[10];
  Int_t matchingEle[10];

  Int_t ngammas;
  Float_t dRGenphot[10];
  Float_t ptphot[10];
  Float_t deltaRToTrackphot[10];
  Float_t etaphot[10];
  Float_t phiphot[10];
  Float_t etascphot[10];
  Float_t E1phot[10];
  Float_t E9phot[10];
  Float_t r9phot[10];
  Int_t   pid_haspixelseedphot[10]; 
  Float_t pid_HoverEphot[10];
  Float_t pid_sigmaIeIephot[10];
  Float_t pid_hlwTrack04phot[10];
  Float_t pid_jurECAL04phot[10];
  Float_t pid_twrHCAL04phot[10];
  Float_t pid_pfIsoCharged03phot[10];
  Float_t pid_pfIsoPhotons03phot[10];
  Float_t pid_pfIsoNeutrals03phot[10];
  Float_t pid_pfIsoCharged04phot[10];
  Float_t pid_pfIsoPhotons04phot[10];
  Float_t pid_pfIsoNeutrals04phot[10];
  Int_t   pid_hasMatchedConvphot[10];
  Int_t   pid_hasMatchedPromptElephot[10];
  Float_t pid_deltaRToTrackphot[10];

  Int_t vtxId;
  Float_t vtxPos_x;
  Float_t vtxPos_y;
  Float_t vtxPos_z;

  Int_t oneLooseIsoMu;
  Int_t oneTightIsoMu;
  Int_t oneWP80Ele;
  Int_t oneWP90Ele;
  Int_t oneHwwEle;
  Int_t oneHzzEle;

   // int nFiredHLT;
   std::vector<std::string>*  aHLTNames;
   std::vector<bool>*  aHLTResults;

   float weight;
};
#endif
