#ifndef TagAndProbeTree_h
#define TagAndProbeTree_h

#include "tree_reader_V8.h"
#include "PhotonIdCuts.h"
#include "LeptonIdCuts.h"
#include "EnergyScaleCorrection.h"
#include "JetScaleSystematics.h"
#include "ElectronEffectiveArea.h"
#include "MassResolution.h"

#include "TLorentzVector.h"
#include "TVector3.h"

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

class TagAndProbeTree : public tree_reader_V8 {

public:
  
  TagAndProbeTree(TTree *tree=0, const TString& outname="redntp.root");
  //virtual ~TagAndProbeTree(){};
  virtual ~TagAndProbeTree();
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
  
  //photon selection
  //  bool photonIDCuts2012(int i, photonidcuts2012 const& pid, vector<bool*> vpass);
  bool photonIDCuts2012(int i, photonidcuts2012 const& pid, bool* vpass[]);

  // lepton tag
  bool leptonCutsEle2012(int i, electronidcuts2012 const& pid, vector<bool> *vpass);
  bool leptonCutsEleMva2012(int iEle, electronidcutsMva2012 const& pid, vector<bool> *vpass);
  bool leptonCutsMu2012(int iMu, muonidcuts2012 const& pid, vector<bool> *vpass);
  bool leptonCutsMuVL2012(int iMu, muonidcuts2012 const& pid, vector<bool> *vpass);
  double eleDzPV(int iele, int iPV);
  double eleDxyPV(int iele, int iPV);
  double muonDzPV(int imu, int iPV);
  double muonDxyPV(int imu, int iPV);
  double trackDzPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);
  double trackDxyPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom);
  void SetAllMVA();
  void ClusterShape(Int_t* i, Float_t* tmva_photonid_sieie, Float_t* tmva_photonid_etawidth, Float_t* tmva_photonid_phiwidth, Float_t* tmva_photonid_r9, Float_t* tmva_photonid_s4ratio);
  bool PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) ;
  Float_t PhotonIDMVA(Int_t i);

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

  void SetAllRecoVarToMinus999();

  virtual vector<int>    firstones(Float_t * vec, vector<bool> *asso, int number=2);
  bool mcID(int i); 
  void correctPhotons(bool energyRegression);
  TLorentzVector correctMet(TLorentzVector uncormet, bool smearing = 1, bool scale = 0, bool PUremoval = 0);
  TLorentzVector shiftMet(TLorentzVector uncormet);
  

//electrons
  /*Int_t           nEle;
   Float_t         electron_px[10];   //[nEle]
   Float_t         electron_py[10];   //[nEle]
   Float_t         electron_pz[10];   //[nEle]
   Float_t         electron_vx[10];   //[nEle]
   Float_t         electron_vy[10];   //[nEle]
   Float_t         electron_vz[10];   //[nEle]
   Float_t         electron_pt[10];   //[nEle]
   Float_t         electron_eta[10];   //[nEle]
   Float_t         electron_phi[10];   //[nEle]
   Float_t         electron_energy[10];   //[nEle]
   Float_t         electron_ecalEnergy[10];   //[nEle]
   Float_t         electron_trackPatVtx[10];   //[nEle]
   Float_t         electron_charge[10];   //[nEle]
   Float_t         electron_fBrem[10];   //[nEle]
   Float_t         electron_dist[10];   //[nEle]
   Float_t         electron_dcot[10];   //[nEle]
   Int_t           electron_misHits[10];   //[nEle]
   Int_t           electron_matchedConv[10];   //[nEle]
   Int_t           electron_seedType[10];   //[nEle]
   Float_t         electron_EoP[10];   //[nEle]
   Float_t         electron_OneOverEMinusOneOverP[10];   //[nEle]
   Float_t         electron_r9[10];   //[nEle]
   Int_t           electron_nSubClusters[10];   //[nEle]
   Float_t         electron_trkIso[10];   //[nEle]
   Float_t         electron_ecalIso[10];   //[nEle]
   Float_t         electron_hcalIso[10];   //[nEle]
   Float_t         electron_trkIso03[10];   //[nEle]
   Float_t         electron_ecalIso03[10];   //[nEle]
   Float_t         electron_hcalIso03[10];   //[nEle]
   Float_t         electron_SigmaIetaIeta[10];   //[nEle]
   Float_t         electron_SigmaIphiIphi[10];   //[nEle]
   Float_t         electron_dEtaIn[10];   //[nEle]
   Float_t         electron_dPhiIn[10];   //[nEle]
   Float_t         electron_HoE[10];   //[nEle]
   Float_t         electron_pFlowMVA[10];   //[nEle]
   Float_t         electron_sc_energy[10];   //[nEle]
   Float_t         electron_sc_eta[10];   //[nEle]
   Float_t         electron_sc_phi[10];   //[nEle]
   Float_t         electron_mvaNonTrig[10];   //[nEle]
   Float_t         electron_mvaTrig[10];   //[nEle]
   Float_t         electron_chHad03Iso[10];   //[nEle]
   Float_t         electron_nHad03Iso[10];   //[nEle]
   Float_t         electron_phot03Iso[10];   //[nEle]
   Float_t         electron_chHad04Iso[10];   //[nEle]
   Float_t         electron_nHad04Iso[10];   //[nEle]
   Float_t         electron_phot04Iso[10];   //[nEle]
   Float_t         electron_chHad05Iso[10];   //[nEle]
   Float_t         electron_nHad05Iso[10];   //[nEle]
   Float_t         electron_phot05Iso[10];   //[nEle]

   Int_t           isEleTag[10];
   Int_t           isEleProbe[10];
   Int_t           genEleMatched_index[10];
   Float_t         deltaR_EleGenReco[10];
   Float_t         invMassEle;
   */
   // List of branches
   TBranch        *b_genpt;   //!
   TBranch        *b_genProcessId;   //!
   TBranch        *b_genQScale;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_passEcalLaserFilter;   //!
   TBranch        *b_passHBHENoiseFilter;   //!
   TBranch        *b_passCSCTightHaloFilter;   //!
   TBranch        *b_passhcalLaserEventFilter;   //!
   TBranch        *b_passEcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_passtrackingFailureFilter;   //!
   TBranch        *b_passeeBadScFilter;   //!
   TBranch        *b_store;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_bx;   //!
   TBranch        *b_orbit;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_rhoPF;   //!
   TBranch        *b_rhoCalo;   //!
   TBranch        *b_rhoAllJets;   //!
   TBranch        *b_nMC;   //!
   TBranch        *b_pdgIdMC;   //!
   TBranch        *b_statusMC;   //!
   TBranch        *b_motherIDMC;   //!
   TBranch        *b_ptMC ;   //!
   TBranch        *b_eMC  ;   //!
   TBranch        *b_etaMC;   //!
   TBranch        *b_phiMC;   //!
   TBranch        *b_pu_n;   //!
   TBranch        *b_pu_true_n;   //!
   TBranch        *b_pu_zpos;   //!
   TBranch        *b_pu_sumpt_lowpt;   //!
   TBranch        *b_pu_sumpt_highpt;   //!
   TBranch        *b_pu_ntrks_lowpt;   //!
   TBranch        *b_pu_ntrks_highpt;   //!
   TBranch        *b_nPhot;   //!
   TBranch        *b_ptPhot ;   //!
   TBranch        *b_ePhot  ;   //!
   TBranch        *b_escPhot  ;   //!
   TBranch        *b_escRegrPhot  ;   //!
   TBranch        *b_escRegrPhotError  ;   //!
   TBranch        *b_escPhFixPhot  ;   //!
   TBranch        *b_escPhFixPhotError  ;   //!
   TBranch        *b_escRawPhot  ;   //!
   TBranch        *b_etascPhot  ;   //!
   TBranch        *b_phiscPhot  ;   //!
   TBranch        *b_xscPhot  ;   //!
   TBranch        *b_yscPhot  ;   //!
   TBranch        *b_zscPhot  ;   //!
   TBranch        *b_xcaloPhot  ;   //!
   TBranch        *b_ycaloPhot  ;   //!
   TBranch        *b_zcaloPhot  ;   //!
   TBranch        *b_eseedPhot  ;   //!
   TBranch        *b_etaPhot;   //!
   TBranch        *b_phiPhot;   //!
   TBranch        *b_timePhot;   //!
   TBranch        *b_e4SwissCrossPhot;   //!
   TBranch        *b_hasPixelSeedPhot;   //!
   TBranch        *b_hasMatchedPromptElePhot;   //!
   TBranch        *b_hasMatchedConvPhot;   //!
   TBranch        *b_isEBPhot;   //!
   TBranch        *b_isEEPhot;   //!
   TBranch        *b_isEBEEGapPhot;   //!
   TBranch        *b_ntracksConvPhot;   //!
   TBranch        *b_isValidVtxConvPhot;   //!
   TBranch        *b_pairInvmassConvPhot;   //!
   TBranch        *b_pairCotThetaSeperationConvPhot;   //!
   TBranch        *b_pairmomentumXConvPhot;   //!
   TBranch        *b_pairmomentumYConvPhot;   //!
   TBranch        *b_pairmomentumZConvPhot;   //!
   TBranch        *b_chi2ConvPhot;   //!
   TBranch        *b_nDofConvPhot;   //!
   TBranch        *b_eOverPConvPhot;   //!
   TBranch        *b_convVxConvPhot;   //!
   TBranch        *b_convVyConvPhot;   //!
   TBranch        *b_convVzConvPhot;   //!
   TBranch        *b_distOfMinimumApproachConvPhot;   //!
   TBranch        *b_dPhiTracksAtVtxConvPhot;   //!
   TBranch        *b_pid_isEM;   //!
   TBranch        *b_pid_isLoose;   //!
   TBranch        *b_pid_isTight;   //!
   TBranch        *b_pid_jurECAL;   //!
   TBranch        *b_pid_twrHCAL;   //!
   TBranch        *b_pid_HoverE;   //!
   TBranch        *b_pid_hlwTrack;   //!
   TBranch        *b_pid_hlwTrackNoDz;   //!
   TBranch        *b_pid_hlwTrackBestRank;   //!
   TBranch        *b_pid_etawid;   //!
   TBranch        *b_pid_jurECAL03;   //!
   TBranch        *b_pid_twrHCAL03;   //!
   TBranch        *b_pid_hlwTrack03;   //!
   TBranch        *b_pid_hlwTrack03NoDz;   //!
   TBranch        *b_pid_hlwTrack03ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged01ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged02ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged03ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged04ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged05ForCiC;   //!
   TBranch        *b_pid_pfIsoCharged06ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons01ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons02ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons03ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons04ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons05ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons06ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals01ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals02ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals03ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals04ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals05ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals06ForCiC;   //!
   TBranch        *b_ptiso004Phot;   //!
   TBranch        *b_ntrkiso004Phot;   //!
   TBranch        *b_ptiso035Phot;   //!
   TBranch        *b_ntrkiso035Phot;   //!
   TBranch        *b_ptiso04Phot;   //!
   TBranch        *b_ntrkiso04Phot;   //!
   TBranch        *b_hcalovecal04Phot;   //!
   TBranch        *b_ecaliso04Phot;   //!
   TBranch        *b_pid_scetawid;   //!
   TBranch        *b_pid_scphiwid;   //!
   TBranch        *b_pid_lambdaRatio;   //!
   TBranch        *b_pid_esXwidth;   //!
   TBranch        *b_pid_esYwidth;   //!
   TBranch        *b_sMajMajPhot;   //!
   TBranch        *b_sMinMinPhot;   //!
   TBranch        *b_alphaPhot;   //!
   TBranch        *b_sEtaEtaPhot;   //!
   TBranch        *b_sEtaPhiPhot;   //!
   TBranch        *b_sPhiPhiPhot;   //!
   TBranch        *b_E1Phot;   //!
   TBranch        *b_E2OverE9Phot;   //!
   TBranch        *b_E4Phot;   //!
   TBranch        *b_E9Phot;   //!
   TBranch        *b_E25Phot;   //!
   TBranch        *b_ieleassocPhot;   //!
   TBranch        *b_pid_deltaRToTrackPhot;   //!
   TBranch        *b_nElePhot;   //!
   TBranch        *b_pid_jurECALElePhot ;   //!
   TBranch        *b_pid_twrHCALElePhot ;   //!
   TBranch        *b_pid_HoverEElePhot ;   //!
   TBranch        *b_pid_hlwTrackElePhot ;   //!
   TBranch        *b_pid_etawidElePhot ;   //!
   TBranch        *b_pid_dphivtxElePhot ;   //!
   TBranch        *b_pid_detavtxElePhot ;   //!
   TBranch        *b_pid_mishitsElePhot ;   //!
   TBranch        *b_pid_distElePhot ;   //!
   TBranch        *b_pid_dcotElePhot ;   //!
   TBranch        *b_pid_ptElePhot ;   //!
   TBranch        *b_nJet_akt5;   //!
   TBranch        *b_ptJet_akt5 ;   //!
   TBranch        *b_ptCorrJet_akt5 ;   //!
   TBranch        *b_eJet_akt5  ;   //!
   TBranch        *b_etaJet_akt5;   //!
   TBranch        *b_phiJet_akt5;   //!
   TBranch        *b_emfJet_akt5;   //!
   TBranch        *b_n90Jet_akt5;   //!
   TBranch        *b_n90HitsJet_akt5;   //!
   TBranch        *b_fHPDJet_akt5;   //!
   TBranch        *b_fRBXJet_akt5;   //!
   TBranch        *b_nJet_akt7;   //!
   TBranch        *b_ptJet_akt7 ;   //!
   TBranch        *b_ptCorrJet_akt7 ;   //!
   TBranch        *b_eJet_akt7  ;   //!
   TBranch        *b_etaJet_akt7;   //!
   TBranch        *b_phiJet_akt7;   //!
   TBranch        *b_emfJet_akt7;   //!
   TBranch        *b_n90Jet_akt7;   //!
   TBranch        *b_n90HitsJet_akt7;   //!
   TBranch        *b_fHPDJet_akt7;   //!
   TBranch        *b_fRBXJet_akt7;   //!
   TBranch        *b_nJet_pfakt5;   //!
   TBranch        *b_ptJet_pfakt5 ;   //!
   TBranch        *b_ptCorrJet_pfakt5 ;   //!
   TBranch        *b_eJet_pfakt5  ;   //!
   TBranch        *b_etaJet_pfakt5;   //!
   TBranch        *b_phiJet_pfakt5;   //!
   TBranch        *b_ptDJet_pfakt5;   //!
   TBranch        *b_rmsCandJet_pfakt5;   //!
   TBranch        *b_rmsCandTrueJet_pfakt5;   //!
   TBranch        *b_rmsCandTrue_QCJet_pfakt5;   //!
   TBranch        *b_axis1Jet_pfakt5;   //!
   TBranch        *b_axis2Jet_pfakt5;   //!
   TBranch        *b_pullJet_pfakt5;   //!
   TBranch        *b_tanaJet_pfakt5;   //!
   TBranch        *b_ptD_QCJet_pfakt5;   //!

   TBranch        *b_axis1_QCJet_pfakt5;   //!
   TBranch        *b_axis2_QCJet_pfakt5;   //!
   TBranch        *b_pull_QCJet_pfakt5;   //!
   TBranch        *b_tana_QCJet_pfakt5;   //!
   TBranch        *b_RchgJet_pfakt5;   //!
   TBranch        *b_RneutralJet_pfakt5;   //!
   TBranch        *b_RJet_pfakt5;   //!
   TBranch        *b_Rchg_QCJet_pfakt5;   //!
   TBranch        *b_nChg_ptCutJet_pfakt5;   //!
   TBranch        *b_nChg_QCJet_pfakt5;   //!
   TBranch        *b_nChg_ptCut_QCJet_pfakt5;   //!
   TBranch        *b_nNeutral_ptCutJet_pfakt5;   //!
   TBranch        *b_pTMaxJet_pfakt5;   //!
   TBranch        *b_pTMaxChgJet_pfakt5;   //!
   TBranch        *b_pTMaxNeutralJet_pfakt5;   //!
   TBranch        *b_pTMaxChg_QCJet_pfakt5;   //!
   TBranch        *b_jetId_dRMean_pfakt5;   //!
   TBranch        *b_jetId_frac01_pfakt5;   //!
   TBranch        *b_jetId_frac02_pfakt5;   //!
   TBranch        *b_jetId_frac03_pfakt5;   //!
   TBranch        *b_jetId_frac04_pfakt5;   //!
   TBranch        *b_jetId_frac05_pfakt5;   //!
   TBranch        *b_jetId_nNeutrals_pfakt5;   //!
   TBranch        *b_jetId_beta_pfakt5;   //!
   TBranch        *b_jetId_betaStar_pfakt5;   //!
   TBranch        *b_jetId_dZ_pfakt5;   //!
   TBranch        *b_jetId_nCharged_pfakt5;   //!
   TBranch        *b_jetId_dR2Mean_pfakt5;   //!
   TBranch        *b_jetId_betaStarClassic_pfakt5;   //!
   TBranch        *b_jetIdSimple_mva_pfakt5;   //!
   TBranch        *b_jetIdSimple_wp_pfakt5;   //!
   TBranch        *b_jetIdFull_mva_pfakt5;   //!
   TBranch        *b_jetIdFull_wp_pfakt5;   //!
   TBranch        *b_jetIdCutBased_mva_pfakt5;   //!
   TBranch        *b_jetIdCutBased_wp_pfakt5;   //!
   TBranch        *b_beta_pfakt5;   //!
   TBranch        *b_betaStar_pfakt5;   //!
   TBranch        *b_combinedSecondaryVertexBJetTags;   //!
   TBranch        *b_combinedSecondaryVertexMVABJetTags;   //!
   TBranch        *b_jetBProbabilityBJetTags;   //!
   TBranch        *b_jetProbabilityBJetTags;   //!
   TBranch        *b_simpleSecondaryVertexHighEffBJetTags;   //!
   TBranch        *b_simpleSecondaryVertexHighPurBJetTags;   //!
   TBranch        *b_softMuonBJetTags;   //!
   TBranch        *b_softMuonByIP3dBJetTags;   //!
   TBranch        *b_softMuonByPtBJetTags;   //!
   TBranch        *b_softElectronByIP3dBJetTags;   //!
   TBranch        *b_softElectronByPtBJetTags;   //!
   TBranch        *b_trackCountingHighPurBJetTags;   //!
   TBranch        *b_trackCountingHighEffBJetTags;   //!
   TBranch        *b_npfcand_all;   //!
   TBranch        *b_nChargedHadrons_uncl;   //!
   TBranch        *b_nChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_nChargedHadronsothervtx_uncl;   //!
   TBranch        *b_nPhotons_uncl;   //!
   TBranch        *b_nMuons_uncl;   //!
   TBranch        *b_nElectrons_uncl;   //!
   TBranch        *b_nNeutralHadrons_uncl;   //!
   TBranch        *b_nHFHadrons_uncl;   //!
   TBranch        *b_nHFEM_uncl;   //!
   TBranch        *b_epfcand_all;   //!
   TBranch        *b_eChargedHadrons_uncl;   //!
   TBranch        *b_eChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_eChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_ePhotons_uncl;   //!
   TBranch        *b_eMuons_uncl;   //!
   TBranch        *b_eElectrons_uncl;   //!
   TBranch        *b_eNeutralHadrons_uncl;   //!
   TBranch        *b_eHFHadrons_uncl;   //!
   TBranch        *b_eHFEM_uncl;   //!

   TBranch        *b_ptChargedHadrons_uncl;   //!
   TBranch        *b_ptChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_ptChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_ptPhotons_uncl;   //!
   TBranch        *b_ptMuons_uncl;   //!
   TBranch        *b_ptElectrons_uncl;   //!
   TBranch        *b_ptNeutralHadrons_uncl;   //!
   TBranch        *b_ptHFHadrons_uncl;   //!
   TBranch        *b_ptHFEM_uncl;   //!

   TBranch        *b_etaChargedHadrons_uncl;   //!
   TBranch        *b_etaChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_etaChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_etaPhotons_uncl;   //!
   TBranch        *b_etaMuons_uncl;   //!
   TBranch        *b_etaElectrons_uncl;   //!
   TBranch        *b_etaNeutralHadrons_uncl;   //!
   TBranch        *b_etaHFHadrons_uncl;   //!
   TBranch        *b_etaHFEM_uncl;   //!
   TBranch        *b_ptpfcand_all;   //!
   TBranch        *b_phiChargedHadrons_uncl;   //!
   TBranch        *b_phiChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_phiChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_phiPhotons_uncl;   //!
   TBranch        *b_phiMuons_uncl;   //!
   TBranch        *b_phiElectrons_uncl;   //!
   TBranch        *b_phiNeutralHadrons_uncl;   //!
   TBranch        *b_phiHFHadrons_uncl;   //!
   TBranch        *b_phiHFEM_uncl;   //!

   TBranch        *b_sumptChargedHadrons_uncl;   //!
   TBranch        *b_sumptChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_sumptChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_sumptPhotons_uncl;   //!
   TBranch        *b_sumptMuons_uncl;   //!
   TBranch        *b_sumptElectrons_uncl;   //!
   TBranch        *b_sumptNeutralHadrons_uncl;   //!
   TBranch        *b_sumptHFHadrons_uncl;   //!
   TBranch        *b_sumptHFEM_uncl;   //!
   TBranch        *b_sumptpfcand_all;   //!
   TBranch        *b_nChargedHadrons_pfakt5;   //!
   TBranch        *b_nChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_nChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_nPhotons_pfakt5;   //!
   TBranch        *b_nMuons_pfakt5;   //!
   TBranch        *b_nElectrons_pfakt5;   //!
   TBranch        *b_nNeutralHadrons_pfakt5;   //!
   TBranch        *b_nHFHadrons_pfakt5;   //!
   TBranch        *b_nHFEM_pfakt5;   //!
   TBranch        *b_eChargedHadrons_pfakt5;   //!
   TBranch        *b_eChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_eChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_ePhotons_pfakt5;   //!
   TBranch        *b_eMuons_pfakt5;   //!
   TBranch        *b_eElectrons_pfakt5;   //!
   TBranch        *b_eNeutralHadrons_pfakt5;   //!
   TBranch        *b_eHFHadrons_pfakt5;   //!
   TBranch        *b_eHFEM_pfakt5;   //!
   TBranch        *b_ptChargedHadrons_pfakt5;   //!
   TBranch        *b_ptChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_ptChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_ptPhotons_pfakt5;   //!
   TBranch        *b_ptMuons_pfakt5;   //!
   TBranch        *b_ptElectrons_pfakt5;   //!
   TBranch        *b_ptNeutralHadrons_pfakt5;   //!
   TBranch        *b_ptHFHadrons_pfakt5;   //!
   TBranch        *b_ptHFEM_pfakt5;   //!
   TBranch        *b_etaChargedHadrons_pfakt5;   //!
   TBranch        *b_etaChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_etaChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_etaPhotons_pfakt5;   //!
   TBranch        *b_etaMuons_pfakt5;   //!
   TBranch        *b_etaElectrons_pfakt5;   //!
   TBranch        *b_etaNeutralHadrons_pfakt5;   //!
   TBranch        *b_etaHFHadrons_pfakt5;   //!
   TBranch        *b_etaHFEM_pfakt5;   //!
   TBranch        *b_phiChargedHadrons_pfakt5;   //!
   TBranch        *b_phiChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_phiChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_phiPhotons_pfakt5;   //!
   TBranch        *b_phiMuons_pfakt5;   //!
   TBranch        *b_phiElectrons_pfakt5;   //!
   TBranch        *b_phiNeutralHadrons_pfakt5;   //!
   TBranch        *b_phiHFHadrons_pfakt5;   //!
   TBranch        *b_phiHFEM_pfakt5;   //!
   TBranch        *b_sumptChargedHadrons_pfakt5;   //!
   TBranch        *b_sumptChargedHadronsgoodvtx_pfakt5;   //!
   TBranch        *b_sumptChargedHadronsnoothervtx_pfakt5;   //!
   TBranch        *b_sumptPhotons_pfakt5;   //!
   TBranch        *b_sumptMuons_pfakt5;   //!
   TBranch        *b_sumptElectrons_pfakt5;   //!
   TBranch        *b_sumptNeutralHadrons_pfakt5;   //!
   TBranch        *b_sumptHFHadrons_pfakt5;   //!
   TBranch        *b_sumptHFEM_pfakt5;   //!
   TBranch        *b_nJet_pfakt7;   //!
   TBranch        *b_ptJet_pfakt7 ;   //!
   TBranch        *b_ptCorrJet_pfakt7 ;   //!
   TBranch        *b_eJet_pfakt7  ;   //!
   TBranch        *b_etaJet_pfakt7;   //!
   TBranch        *b_phiJet_pfakt7;   //!
   TBranch        *b_nJetGen_akt5;   //!
   TBranch        *b_ptJetGen_akt5 ;   //!
   TBranch        *b_eJetGen_akt5  ;   //!
   TBranch        *b_etaJetGen_akt5;   //!
   TBranch        *b_phiJetGen_akt5;   //!
   TBranch        *b_nMuonsGen_akt5;   //!
   TBranch        *b_nElectronsGen_akt5;   //!
   TBranch        *b_nPhotonsGen_akt5;   //!
   TBranch        *b_nTracksGen_akt5;   //!
   TBranch        *b_nNeutralHadronsGen_akt5;   //!
   TBranch        *b_nHFHadronsGen_akt5;   //!
   TBranch        *b_nHFEMGen_akt5;   //!
   TBranch        *b_nNeutronsGen_akt5;   //!
   TBranch        *b_nK0LGen_akt5;   //!
   TBranch        *b_nK0SGen_akt5;   //!
   TBranch        *b_nLambdasGen_akt5;   //!
   TBranch        *b_nCsiGen_akt5;   //!
   TBranch        *b_nOtherNeutralHadronsGen_akt5;   //!
   TBranch        *b_eMuonsGen_akt5;   //!
   TBranch        *b_eElectronsGen_akt5;   //!
   TBranch        *b_ePhotonsGen_akt5;   //!
   TBranch        *b_eTracksGen_akt5;   //!
   TBranch        *b_eNeutralHadronsGen_akt5;   //!
   TBranch        *b_eHFHadronsGen_akt5;   //!
   TBranch        *b_eHFEMGen_akt5;   //!
   TBranch        *b_eNeutronsGen_akt5;   //!
   TBranch        *b_eK0LGen_akt5;   //!
   TBranch        *b_eK0SGen_akt5;   //!
   TBranch        *b_eLambdasGen_akt5;   //!
   TBranch        *b_eCsiGen_akt5;   //!
   TBranch        *b_eOtherNeutralHadronsGen_akt5;   //!
   TBranch        *b_nJetGen_akt7;   //!
   TBranch        *b_ptJetGen_akt7 ;   //!
   TBranch        *b_eJetGen_akt7  ;   //!
   TBranch        *b_etaJetGen_akt7;   //!
   TBranch        *b_phiJetGen_akt7;   //!
   TBranch        *b_nvertex;   //!
   TBranch        *b_sMet;   //!
   TBranch        *b_eMet;   //!
   TBranch        *b_phiMet;   //!
   TBranch        *b_signifMet;   //!
   TBranch        *b_sCorrMet;   //!
   TBranch        *b_eCorrMet;   //!
   TBranch        *b_phiCorrMet;   //!
   TBranch        *b_signifCorrMet;   //!
   TBranch        *b_sNoHFMet;   //!
   TBranch        *b_eNoHFMet;   //!
   TBranch        *b_phiNoHFMet;   //!
   TBranch        *b_signifNoHFMet;   //!
   TBranch        *b_stcMet;   //!
   TBranch        *b_etcMet;   //!
   TBranch        *b_phitcMet;   //!
   TBranch        *b_signiftcMet;   //!
   TBranch        *b_sglobalPfMet;   //!
   TBranch        *b_eglobalPfMet;   //!
   TBranch        *b_phiglobalPfMet;   //!
   TBranch        *b_signifglobalPfMet;   //!
   TBranch        *b_scentralPfMet;   //!
   TBranch        *b_ecentralPfMet;   //!
   TBranch        *b_phicentralPfMet;   //!
   TBranch        *b_signifcentralPfMet;   //!
   TBranch        *b_eassocPfMet;   //!
   TBranch        *b_phiassocPfMet;   //!
   TBranch        *b_signifassocPfMet;   //!
   TBranch        *b_eassocOtherVtxPfMet;   //!
   TBranch        *b_phiassocOtherVtxPfMet;   //!
   TBranch        *b_signifassocOtherVtxPfMet;   //!
   TBranch        *b_etrkPfMet;   //!
   TBranch        *b_phitrkPfMet;   //!
   TBranch        *b_signiftrkPfMet;   //!
   TBranch        *b_ecleanPfMet;   //!
   TBranch        *b_phicleanPfMet;   //!
   TBranch        *b_signifcleanPfMet;   //!
   TBranch        *b_globalPfSums;   //!
   TBranch        *b_spfMet;   //!
   TBranch        *b_epfMet;   //!
   TBranch        *b_phipfMet;   //!
   TBranch        *b_signifpfMet;   //!
   TBranch        *b_spfMetType1;   //!
   TBranch        *b_epfMetType1;   //!
   TBranch        *b_phipfMetType1;   //!
   TBranch        *b_signifpfMetType1;   //!
   TBranch        *b_sMetGen;   //!
   TBranch        *b_eMetGen;   //!
   TBranch        *b_phiMetGen;   //!
   TBranch        *b_signifMetGen;   //!
   TBranch        *b_sMetGen2;   //!
   TBranch        *b_eMetGen2;   //!
   TBranch        *b_phiMetGen2;   //!
   TBranch        *b_vxMC;   //!
   TBranch        *b_vyMC;   //!
   TBranch        *b_vzMC;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_vntracks;   //!
   TBranch        *b_vchi2;   //!
   TBranch        *b_vndof;   //!
   TBranch        *b_vlogsumpt2;   //!
   TBranch        *b_nPreselPhotonPairs;   //!
   TBranch        *b_indexPreselPhot1;   //!
   TBranch        *b_indexPreselPhot2;   //!
   TBranch        *b_vrankPhotonPairs;   //!
   TBranch        *b_vevtMvaPhotonPairs;   //!
   TBranch        *b_vevtProbPhotonPairs;   //!
   TBranch        *b_vptbalPhotonPairs;   //!
   TBranch        *b_vptasymPhotonPairs;   //!
   TBranch        *b_nHLT;   //!
   TBranch        *b_hltNamesLen;   //!
   TBranch        *b_HLTNames;   //!
   TBranch        *b_HLTResults;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_electron_px;   //!
   TBranch        *b_electron_py;   //!
   TBranch        *b_electron_pz;   //!
   TBranch        *b_electron_vx;   //!
   TBranch        *b_electron_vy;   //!
   TBranch        *b_electron_vz;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_energy;   //!
   TBranch        *b_electron_ecalEnergy;   //!
   TBranch        *b_electron_trackPatVtx;   //!
   TBranch        *b_electron_charge;   //!
   TBranch        *b_electron_fBrem;   //!
   TBranch        *b_electron_dist;   //!
   TBranch        *b_electron_dcot;   //!
   TBranch        *b_electron_misHits;   //!
   TBranch        *b_electron_matchedConv;   //!
   TBranch        *b_electron_seedType;   //!
   TBranch        *b_electron_EoP;   //!
   TBranch        *b_electron_OneOverEMinusOneOverP;   //!
   TBranch        *b_electron_r9;   //!
   TBranch        *b_electron_nSubClusters;   //!
   TBranch        *b_electron_trkIso;   //!
   TBranch        *b_electron_ecalIso;   //!
   TBranch        *b_electron_hcalIso;   //!
   TBranch        *b_electron_trkIso03;   //!
   TBranch        *b_electron_ecalIso03;   //!
   TBranch        *b_electron_hcalIso03;   //!
   TBranch        *b_electron_SigmaIetaIeta;   //!
   TBranch        *b_electron_SigmaIphiIphi;   //!
   TBranch        *b_electron_dEtaIn;   //!
   TBranch        *b_electron_dPhiIn;   //!
   TBranch        *b_electron_HoE;   //!
   TBranch        *b_electron_pFlowMVA;   //!
   TBranch        *b_electron_sc_energy;   //!
   TBranch        *b_electron_sc_eta;   //!
   TBranch        *b_electron_sc_phi;   //!
   TBranch        *b_electron_mvaNonTrig;   //!
   TBranch        *b_electron_mvaTrig;   //!
   TBranch        *b_electron_chHad03Iso;   //!
   TBranch        *b_electron_nHad03Iso;   //!
   TBranch        *b_electron_phot03Iso;   //!
   TBranch        *b_electron_chHad04Iso;   //!
   TBranch        *b_electron_nHad04Iso;   //!
   TBranch        *b_electron_phot04Iso;   //!
   TBranch        *b_electron_chHad05Iso;   //!
   TBranch        *b_electron_nHad05Iso;   //!
   TBranch        *b_electron_phot05Iso;   //!
   TBranch        *b_isBeamHaloGlobalLoosePass;   //!
   TBranch        *b_isBeamHaloGloablTightPass;   //!
   TBranch        *b_isBeamHaloHcalLoosePass;   //!
   TBranch        *b_isBeamHaloHcalTightPass;   //!
   TBranch        *b_isBeamHaloCSCLoosePass;   //!
   TBranch        *b_isBeamHaloCSCTightPass;   //!
   TBranch        *b_isBeamHaloEcalLoosePass;   //!
   TBranch        *b_isBeamHaloEcalTightPass;   //!
   TBranch        *b_isBeamHaloIDTightPass;   //!
   TBranch        *b_isBeamHaloIDLoosePass;   //!
   TBranch        *b_isSmellsLikeHalo_Tag;   //!
   TBranch        *b_isLooseHalo_Tag;   //!
   TBranch        *b_isTightHalo_Tag;   //!
   TBranch        *b_isExtremeTightHalo_Tag;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_Muon_px;   //!
   TBranch        *b_Muon_py;   //!
   TBranch        *b_Muon_pz;   //!
   TBranch        *b_Muon_vx;   //!
   TBranch        *b_Muon_vy;   //!
   TBranch        *b_Muon_vz;   //!
   TBranch        *b_Muon_pt;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_energy;   //!
   TBranch        *b_Muon_charge;   //!
   TBranch        *b_Muon_isGlobalMuon;   //!
   TBranch        *b_Muon_isTrackerMuon;   //!
   TBranch        *b_Muon_isStandAloneMuon;   //!
   TBranch        *b_Muon_trkLayerWithMeas;   //!
   TBranch        *b_Muon_InnerTrack_isNonnull;   //!
   TBranch        *b_Muon_OuterTrack_isNonnull;   //!
   TBranch        *b_Muon_OuterPoint_x;   //!
   TBranch        *b_Muon_OuterPoint_y;   //!
   TBranch        *b_Muon_OuterPoint_z;   //!
   TBranch        *b_Muon_isPFMuon;   //!
   TBranch        *b_Muon_pfiso04_chHad;   //!
   TBranch        *b_Muon_pfiso04_chPar;   //!
   TBranch        *b_Muon_pfiso04_nHad;   //!
   TBranch        *b_Muon_pfiso04_Phot;   //!
   TBranch        *b_Muon_pfiso04_PUPt;   //!
   TBranch        *b_Muon_pfiso03_chHad;   //!
   TBranch        *b_Muon_pfiso03_chPar;   //!
   TBranch        *b_Muon_pfiso03_nHad;   //!
   TBranch        *b_Muon_pfiso03_Phot;   //!
   TBranch        *b_Muon_pfiso03_PUPt;   //!
   TBranch        *b_Muon_InnerPoint_x;   //!
   TBranch        *b_Muon_InnerPoint_y;   //!
   TBranch        *b_Muon_InnerPoint_z;   //!
   TBranch        *b_Muon_trackIso;   //!
   TBranch        *b_Muon_ecalIso;   //!
   TBranch        *b_Muon_hcalIso;   //!
   TBranch        *b_Muon_relIso;   //!
   TBranch        *b_Muon_normChi2;   //!
   TBranch        *b_Muon_validHits;   //!
   TBranch        *b_Muon_tkHits;   //!
   TBranch        *b_Muon_pixHits;   //!
   TBranch        *b_Muon_numberOfMatches;   //!
   TBranch        *b_nCosmicMuons;   //!
   TBranch        *b_CosmicMuon_px;   //!
   TBranch        *b_CosmicMuon_py;   //!
   TBranch        *b_CosmicMuon_pz;   //!
   TBranch        *b_CosmicMuon_pt;   //!
   TBranch        *b_CosmicMuon_eta;   //!
   TBranch        *b_CosmicMuon_phi;   //!
   TBranch        *b_CosmicMuon_energy;   //!
   TBranch        *b_CosmicMuon_charge;   //!
   TBranch        *b_CosmicMuon_isGlobalMuon;   //!
   TBranch        *b_CosmicMuon_isTrackerMuon;   //!
   TBranch        *b_CosmicMuon_isStandAloneMuon;   //!
   TBranch        *b_CosmicMuon_InnerTrack_isNonnull;   //!
   TBranch        *b_CosmicMuon_OuterTrack_isNonnull;   //!
   TBranch        *b_CosmicMuon_OuterPoint_x;   //!
   TBranch        *b_CosmicMuon_OuterPoint_y;   //!
   TBranch        *b_CosmicMuon_OuterPoint_z;   //!
   TBranch        *b_Xsec;   //!
   

   /*
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
   */ 
   
   
   TMVA::Reader *tmvaReaderID_Single_Barrel, *tmvaReaderID_Single_Endcap;
   Float_t tmva_photonid_pt;
   Float_t tmva_photonid_nPhot;       
   Float_t tmva_photonid_isMatchedPhot;
   Float_t tmva_photonid_ptWeight; 
   Float_t tmva_photonid_rr;     
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
   
  

private:

  
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
  
  
   //int nEle;
  float electron_pt_tag;    
  float electron_energy_tag;
  float electron_phi_tag;   
  float electron_eta_tag;   
  int   isMatched_ele_tag;  
  //shower shape tag 
  float electron_EoP_tag;		    
  float electron_OneOverEMinusOneOverP_tag; 
  float electron_r9_tag;		    
  float electron_SigmaIetaIeta_tag;	    
  float electron_dEtaIn_tag;		    
  float electron_dPhiIn_tag;		    
  float electron_HoE_tag;		    
  float electron_sc_eta_tag;                
  //iso tag
  float electron_trkIso_tag;
  float electron_ecalIso_tag;
  float electron_hcalIso_tag;
  float electron_trkIso03_tag;
  float electron_ecalIso03_tag;
  float electron_hcalIso03_tag;
  float electron_chHad03Iso_tag;
  float electron_nHad03Iso_tag;
  float electron_phot03Iso_tag;
  float electron_chHad04Iso_tag;
  float electron_nHad04Iso_tag;
  float electron_phot04Iso_tag;
  float electron_chHad05Iso_tag;
  float electron_nHad05Iso_tag;
  float electron_phot05Iso_tag;
  //s4Ratio e sIetaIphi ?

  float electron_pt_probe;
  float electron_energy_probe;
  float electron_phi_probe;
  float electron_eta_probe;
  int isMatched_ele_probe;
  //shower shape probe 
  float electron_EoP_probe;
  float electron_OneOverEMinusOneOverP_probe;
  float electron_r9_probe;
  float electron_SigmaIetaIeta_probe;
  float electron_dEtaIn_probe;
  float electron_dPhiIn_probe;
  float electron_HoE_probe;
  float electron_sc_eta_probe;
  //iso probe
  float electron_trkIso_probe;	  
  float electron_ecalIso_probe;	  
  float electron_hcalIso_probe;	  
  float electron_trkIso03_probe;  
  float electron_ecalIso03_probe; 
  float electron_hcalIso03_probe; 
  float electron_chHad03Iso_probe;
  float electron_nHad03Iso_probe; 
  float electron_phot03Iso_probe; 
  float electron_chHad04Iso_probe;
  float electron_nHad04Iso_probe; 
  float electron_phot04Iso_probe; 
  float electron_chHad05Iso_probe;
  float electron_nHad05Iso_probe; 
  float electron_phot05Iso_probe; 
  //s4Ratio e sIetaIphi ?

   std::vector<std::string>* aHLTNames;

   float weight;


};
#endif
