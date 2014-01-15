#ifndef SingleGammaTree_giulia_h
#define SingleGammaTree_giulia_h

#include "tree_reader_V9.h"
//#include "PhotonIdCuts.h"
#include "LeptonIdCuts.h"
#include "EnergyScaleCorrection.h"
#include "JetScaleSystematics.h"
//#include "ElectronEffectiveArea.h"
//#include "MassResolution.h"

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

#define NGENJETS 200
#define NMC 150

class SingleGammaTree_giulia : public tree_reader_V9 {

public:
  
  SingleGammaTree_giulia(TTree *tree=0, const TString& outname="redntp.root");
  //virtual ~SingleGammaTree_giulia(){};
  virtual ~SingleGammaTree_giulia();
  virtual void     Loop();
  void SetJsonFile(const char* json) { jsonFile = json; };
  void SetPuWeights(std::string puWeightFile);
  void SetPuWeightsHLT(std::string puWeightFileHLT, int hltThresh);
  double ErrEt(double Et, double Eta);
  void SetNtotXsection(int ntot, float xsec) {      
    NtotEvents = ntot;
    xsection = xsec;
    EquivLumi = ntot/xsec;
  }
  void setEnergyScaleCorrections(TString correctionFile, TString correctionType)
  {
    std::cout << "Constructing new Scale Corrections Of Type " << correctionType<< std::endl;
    std::cout << "Constructing new Scale Corrections from file " << correctionFile << std::endl;
    scaleCorrections_=new EnergyScaleCorrection(correctionFile,correctionType);
  }
  
  std::string photonLevelNewIDMVA_EB;
  std::string photonLevelNewIDMVA_EE;
  std::string cicVersion;
  
private:
  TFile* hOutputFile ;
  TTree * ana_tree ;
  
  TRandom3* gen_;
  
  vector<bool> jetnoisophot;
  
  const char* jsonFile;
  
  Int_t SampleID;
  Int_t  NtotEvents;
  float xsection;
  float EquivLumi;
  bool doPDFweight;

  /*
  //SingleGammaTree giulia
  const int nPhot_presel;
  float ptPhot_presel[nPhot_presel];
  float ePhot_presel[nPhot_presel];
  float etaPhot_presel[nPhot_presel];
  float phiPhot_presel[nPhot_presel];
  */


  void SetAllRecoVarToMinus999();

  virtual vector<int>    firstones(Float_t * vec, vector<bool> *asso, int number=4);
  bool mcID(int i); 
  void correctPhotons(bool energyRegression);
  TLorentzVector correctMet(TLorentzVector uncormet, bool smearing = 1, bool scale = 0, bool PUremoval = 0);
  TLorentzVector shiftMet(TLorentzVector uncormet);
  
  // defines photon CiC ID cuts for all cut levels
  enum phoCiCIDLevel { phoNOCUTS=0, phoLOOSE, phoMEDIUM, phoTIGHT, phoSUPERTIGHT, phoHYPERTIGHT1, phoHYPERTIGHT2, phoHYPERTIGHT3, phoHYPERTIGHT4, phoHYPERTIGHT5, phoHYPERTIGHT6, phoHYPERTIGHT7, phoHYPERTIGHT8, phoHYPERTIGHT9, phoNCUTLEVELS };
  enum phoCiCCuts { phoISOSUMOET=0,  phoISOSUMOETBAD,   phoTRKISOOETOM,   phoSIEIE,   phoHOVERE,   phoR9,   phoDRTOTK_25_99,   phoPIXEL, phoNCUTS };
  enum phoCiC6Categories { phoCiC6EBhighR9=0, phoCiC6EBmidR9, phoCiC6EBlowR9, phoCiC6EEhighR9, phoCiC6EEmidR9, phoCiC6EElowR9, phoCiC6NCATEGORIES };
  enum phoCiC4Categories { phoCiC4EBhighR9=0, phoCiC4EBlowR9, phoCiC4EEhighR9, phoCiC4EElowR9, phoCiC4NCATEGORIES };

  void SetPhotonCutsInCategories(phoCiCIDLevel cutlevel, float * cic6_cuts_lead, float * cic6_cuts_sublead, float * cic4_cuts_lead, float * cic4_cuts_sublead, float*, float*);
  void FillPhotonCiCSelectionVariable(int photon_index, int vtx_index);

  float cic6_cut_lead_isosumoet[phoNCUTLEVELS][6];
  float cic6_cut_lead_isosumoetbad[phoNCUTLEVELS][6];
  float cic6_cut_lead_trkisooet[phoNCUTLEVELS][6];
  float cic6_cut_lead_sieie[phoNCUTLEVELS][6];
  float cic6_cut_lead_hovere[phoNCUTLEVELS][6];
  float cic6_cut_lead_r9[phoNCUTLEVELS][6];
  float cic6_cut_lead_drtotk_25_99[phoNCUTLEVELS][6];
  float cic6_cut_lead_pixel[phoNCUTLEVELS][6];
  float cic6_cut_sublead_isosumoet[phoNCUTLEVELS][6];
  float cic6_cut_sublead_isosumoetbad[phoNCUTLEVELS][6];
  float cic6_cut_sublead_trkisooet[phoNCUTLEVELS][6];
  float cic6_cut_sublead_sieie[phoNCUTLEVELS][6];
  float cic6_cut_sublead_hovere[phoNCUTLEVELS][6];
  float cic6_cut_sublead_r9[phoNCUTLEVELS][6];
  float cic6_cut_sublead_drtotk_25_99[phoNCUTLEVELS][6];
  float cic6_cut_sublead_pixel[phoNCUTLEVELS][6];
  
  float cic4_cut_lead_isosumoet[phoNCUTLEVELS][4];
  float cic4_cut_lead_isosumoetbad[phoNCUTLEVELS][4];
  float cic4_cut_lead_trkisooet[phoNCUTLEVELS][4];
  float cic4_cut_lead_sieie[phoNCUTLEVELS][4];
  float cic4_cut_lead_hovere[phoNCUTLEVELS][4];
  float cic4_cut_lead_r9[phoNCUTLEVELS][4];
  float cic4_cut_lead_drtotk_25_99[phoNCUTLEVELS][4];
  float cic4_cut_lead_pixel[phoNCUTLEVELS][4];
  float cic4_cut_sublead_isosumoet[phoNCUTLEVELS][4];
  float cic4_cut_sublead_isosumoetbad[phoNCUTLEVELS][4];
  float cic4_cut_sublead_trkisooet[phoNCUTLEVELS][4];
  float cic4_cut_sublead_sieie[phoNCUTLEVELS][4];
  float cic4_cut_sublead_hovere[phoNCUTLEVELS][4];
  float cic4_cut_sublead_r9[phoNCUTLEVELS][4];
  float cic4_cut_sublead_drtotk_25_99[phoNCUTLEVELS][4];
  float cic4_cut_sublead_pixel[phoNCUTLEVELS][4];
  
  float cic4pf_cut_lead_isosumoet[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_isosumoetbad[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_trkisooet[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_sieie[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_hovere[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_r9[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_drtotk_25_99[phoNCUTLEVELS][4];
  float cic4pf_cut_lead_pixel[phoNCUTLEVELS][4];
  
  float cic4pf_cut_sublead_isosumoet[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_isosumoetbad[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_trkisooet[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_sieie[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_hovere[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_r9[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_drtotk_25_99[phoNCUTLEVELS][4];
  float cic4pf_cut_sublead_pixel[phoNCUTLEVELS][4];
  
  TH1F* cic4_cut_isosumoet[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_isosumoetbad[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_trkisooet[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_sieie[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_hovere[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_r9[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_drtotk_25_99[phoCiC4NCATEGORIES];
  TH1F* cic4_cut_pixel[phoCiC4NCATEGORIES];
  
  void SetAllMVA(); 
  int   PhotonCiCSelectionLevel( int photon_index, bool electronVeto, int vertex_index, bool usePF);
  bool  PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) ;

  TMVA::Reader *tmvaReaderID_Single_Barrel, *tmvaReaderID_Single_Endcap;
  Float_t tmva_photonid_pfchargedisogood03;
  Float_t tmva_photonid_pfchargedisobad03;
  Float_t tmva_photonid_pfphotoniso03;
  Float_t tmva_photonid_pfneutraliso03;
  Float_t tmva_photonid_sieie;
  Float_t tmva_photonid_sieip;
  Float_t tmva_photonid_etawidth;
  Float_t tmva_photonid_phiwidth;
  Float_t tmva_photonid_r9;
  Float_t tmva_photonid_s4ratio;
  Float_t tmva_photonid_lambdaratio;
  Float_t tmva_photonid_sceta;
  Float_t tmva_photonid_eventrho;
  Float_t tmva_photonid_ESEffSigmaRR;
  Float_t PhotonIDMVANew(Int_t iPhoton, Int_t vtx);  
  
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
    int etacat = (Int_t)(TMath::Abs(etascPhot[photonindex])>1.479);   // 0, 1 (barrel --> endcap)
    return  etacat;
  }
  
   // lepton tag
  bool leptonCutsEle2012(int iEle, electronidcuts2012 const& pid, vector<bool> *vpass);
  bool leptonCutsEleMva2012(int iEle, electronidcutsMva2012 const& pid, vector<bool> *vpass);
  bool leptonCutsMu2012(int iMu, muonidcuts2012 const& pid, vector<bool> *vpass);
  bool leptonCutsMuVL2012(int iMu, muonidcuts2012 const& pid, vector<bool> *vpass);
  double eleDzPV(int iele, int iPV);
  double eleDxyPV(int iele, int iPV);
  double muonDzPV(int imu, int iPV);
  double muonDxyPV(int imu, int iPV);
  double trackDzPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);
  double trackDxyPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);
  
  // gen level info
  int countLOGenGamma();
  int countISRGenGamma();
  int countFSRGenGamma();

  // vector of pu weights
  std::vector<Double_t> puweights_;
  std::vector<Double_t> puweights30_;
  std::vector<Double_t> puweights50_;
  std::vector<Double_t> puweights75_;
  std::vector<Double_t> puweights90_;
  std::vector<Double_t> puweights135_;
  std::vector<Double_t> puweights150_;

  EnergyScaleCorrection* scaleCorrections_;
 
  Int_t runRN;
  Int_t eventRN;
  Int_t lumi;
  Float_t nvtx;
  Float_t rhoPFRN;
  Int_t npu;
  Float_t pu_weight;
  Float_t pu_weight30;
  Float_t pu_weight50;
  Float_t pu_weight75;
  Float_t pu_weight90;
  Float_t pu_weight135;
  Float_t pu_weight150;
  Int_t promptGamma;
  Int_t LOGamma;
  Int_t ISRGamma;
  Int_t FSRGamma;
  Bool_t H_event;
  Bool_t Z_event;
  Bool_t W_event;
  Bool_t Vqq_event;

  Float_t gen_pt_gamma1;
  Float_t gen_pt_gamma2;
  Float_t gen_eta_gamma1;
  Float_t gen_eta_gamma2;
  Float_t gen_phi_gamma1;
  Float_t gen_phi_gamma2;

  Float_t gen_pt_lep1,  gen_pt_lep2;
  Float_t gen_eta_lep1, gen_eta_lep2;
  Float_t gen_phi_lep1, gen_phi_lep2;
  Int_t gen_pid_lep1, gen_pid_lep2;

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
  Float_t ptphot2;
  Float_t deltaRToTrackphot1;
  Float_t deltaRToTrackphot2;
  Float_t etaphot1;
  Float_t etaphot2;
  Float_t phiphot1;
  Float_t phiphot2;
  Float_t etascphot1;
  Float_t etascphot2;
  Float_t E1phot1;
  Float_t E1phot2;
  Float_t E9phot1;
  Float_t E9phot2;
  Float_t energyErrphot1;
  Float_t energyErrphot2;
  Float_t energySmearingphot1;
  Float_t energySmearingphot2;
  Float_t r9phot1;
  Float_t r9phot2;
  Float_t idmvaphot1;
  Float_t idmvaphot2;
  Int_t idcicpfphot1;
  Int_t idcicpfphot2;
  Int_t idcicpfnoelvetophot1;
  Int_t idcicpfnoelvetophot2;
  Int_t   pid_haspixelseedphot1; 
  Int_t   pid_haspixelseedphot2; 
  Float_t pid_HoverEphot1;
  Float_t pid_HoverEphot2;
  Int_t   pid_hasMatchedConvphot1;
  Int_t   pid_hasMatchedConvphot2;
  Int_t   pid_hasMatchedPromptElephot1;
  Int_t   pid_hasMatchedPromptElephot2;

  Float_t massgg;
  Float_t ptgg;
  Float_t phigg;
  Float_t etagg;
  Float_t massggnewvtx;
  Float_t ptggnewvtx;

  Float_t eSmearedMet_;   
  Float_t phiSmearedMet_;
  Float_t eShiftedMet_;   
  Float_t phiShiftedMet_;
  Float_t eShiftedScaledMet_;   
  Float_t phiShiftedScaledMet_;
  Float_t eSmearedShiftedMet_;   
  Float_t phiSmearedShiftedMet_;
  Float_t eShiftedScaledMetPUcorr_;   
  Float_t phiShiftedScaledMetPUcorr_;
  Float_t eSmearedShiftedMetPUcorr_;   
  Float_t phiSmearedShiftedMetPUcorr_;
  Float_t spfMet_;
  Float_t epfMet_;
  Float_t phipfMet_;
  Float_t signifpfMet_;
  Float_t spfMetType1_;
  Float_t epfMetType1_;
  Float_t phipfMetType1_;
  Float_t signifpfMetType1_;
  Float_t sMetGen_;
  Float_t eMetGen_;
  Float_t phiMetGen_;
  Float_t signifMetGen_;
  Float_t sMetGen2_;
  Float_t eMetGen2_;
  Float_t phiMetGen2_;

  Int_t vtxId;
  Float_t vtxPos_x;
  Float_t vtxPos_y;
  Float_t vtxPos_z;

   Float_t ptele1, ptele2;
   Float_t etaele1, etaele2;
   Float_t phiele1, phiele2;
   Float_t eneele1, eneele2;
   Float_t sIeIeele1, sIeIeele2;
   Float_t dphiele1, dphiele2;
   Float_t detaele1, detaele2;
   Float_t hoeele1, hoeele2;
   Int_t mhitsele1, mhitsele2;
   Float_t d0ele1, d0ele2;
   Float_t dzele1, dzele2;
   Float_t oEmoPele1, mvanotrigele1, mvatrigele1; 
   Int_t matchconvele1;
   Float_t chHadIso03ele1, nHadIso03ele1, photIso03ele1;
   Float_t oEmoPele2, mvanotrigele2, mvatrigele2; 
   Int_t matchconvele2;
   Float_t chHadIso03ele2, nHadIso03ele2, photIso03ele2;
   Float_t ecalIso03ele1, hcalIso03ele1, trackerIso03ele1; 
   Float_t ecalIso03ele2, hcalIso03ele2, trackerIso03ele2; 

   Float_t pteleloose1, pteleloose2;
   Float_t etaeleloose1, etaeleloose2;
   Float_t phieleloose1, phieleloose2;
   Float_t eneeleloose1, eneeleloose2;

   Float_t ptelenontr901, ptelenontr902;
   Float_t etaelenontr901, etaelenontr902;
   Float_t phielenontr901, phielenontr902;
   Float_t eneelenontr901, eneelenontr902;

   Float_t ptrecomu1, ptrecomu2;
   Float_t etarecomu1, etarecomu2;
   Float_t phirecomu1, phirecomu2;
   Float_t enerecomu1, enerecomu2;
   Int_t pixhitsrecomu1, pixhitsrecomu2;
   Int_t trkhitsrecomu1, trkhitsrecomu2;
   Int_t hitsrecomu1, hitsrecomu2;
   Float_t chi2recomu1, chi2recomu2;
   Int_t matchrecomu1, matchrecomu2;
   Float_t d0recomu1, d0recomu2;
   Float_t dzrecomu1, dzrecomu2;
   Float_t isorecomu1,isorecomu2;
   Float_t chHadrecomu1, nHadrecomu1, photrecomu1, puptrecomu1;
   Float_t chHadrecomu2, nHadrecomu2, photrecomu2, puptrecomu2;

   Float_t ptmuloose1, ptmuloose2;
   Float_t etamuloose1, etamuloose2;
   Float_t phimuloose1, phimuloose2;
   Float_t enemuloose1, enemuloose2;

   Float_t ptmuvloose1, ptmuvloose2;
   Float_t etamuvloose1, etamuvloose2;
   Float_t phimuvloose1, phimuvloose2;
   Float_t enemuvloose1, enemuvloose2;

   std::vector<std::string>* aHLTNames;

   float weight;

   void ClusterShape(Int_t* iPhoton ,Float_t* tmva_photonid_sieie,  Float_t* tmva_photonid_etawidth, Float_t* tmva_photonid_phiwidth, Float_t* tmva_photonid_r9, Float_t* tmva_photonid_s4ratio );

};
#endif
