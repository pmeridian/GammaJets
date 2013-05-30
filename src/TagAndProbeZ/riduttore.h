//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 29 18:40:11 2013 by ROOT version 5.32/00
// from TTree AnaTree/Reduced tree for final analysis
// found on file: /xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv3_data.cicpfloose..DrellYan_v1_BDTbug/redntp_DoubleElectron_Run2012A-13Jul2012-v1_00.root
//////////////////////////////////////////////////////////

#ifndef riduttore_h
#define riduttore_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class riduttore {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumi;
   Int_t           isMC;
   Float_t         nvtx;
   Int_t           vtxId;
   Int_t           npu;
   Int_t           NtotEvents;
   Float_t         xsection;
   Float_t         EquivLumi;
   Int_t           SampleID;
   Float_t         pu_weight;
   Float_t         pu_weight30;
   Float_t         pu_weight50;
   Float_t         pu_weight75;
   Float_t         pu_weight90;
   Int_t           LOGamma;
   Int_t           ISRGamma;
   Int_t           FSRGamma;
   Float_t         rhoAllJets;
   Float_t         rhoPF;
   Int_t           nEle;
   Float_t         electron_pt[50];   //[nEle]
   Float_t         electron_energy[50];   //[nEle]
   Float_t         electron_phi[50];   //[nEle]
   Float_t         electron_eta[50];   //[nEle]
   Float_t         electron_EoP[50];   //[nEle]
   Float_t         electron_OneOverEMinusOneOverP[50];   //[nEle]
   Float_t         electron_r9[50];   //[nEle]
   Float_t         electron_SigmaIetaIeta[50];   //[nEle]
   Float_t         electron_dEtaIn[50];   //[nEle]
   Float_t         electron_dPhiIn[50];   //[nEle]
   Float_t         electron_HoE[50];   //[nEle]
   Float_t         electron_sc_eta[50];   //[nEle]
   Float_t         electron_trkIso[50];   //[nEle]
   Float_t         electron_ecalIso[50];   //[nEle]
   Float_t         electron_hcalIso[50];   //[nEle]
   Float_t         electron_trkIso03[50];   //[nEle]
   Float_t         electron_ecalIso03[50];   //[nEle]
   Float_t         electron_hcalIso03[50];   //[nEle]
   Float_t         electron_chHad03Iso[50];   //[nEle]
   Float_t         electron_nHad03Iso[50];   //[nEle]
   Float_t         electron_phot03Iso[50];   //[nEle]
   Float_t         electron_chHad04Iso[50];   //[nEle]
   Float_t         electron_nHad04Iso[50];   //[nEle]
   Float_t         electron_phot04Iso[50];   //[nEle]
   Float_t         electron_chHad05Iso[50];   //[nEle]
   Float_t         electron_nHad05Iso[50];   //[nEle]
   Float_t         electron_phot05Iso[50];   //[nEle]
   Int_t           nPhot;
   Float_t         ptPhot[50];   //[nPhot]
   Float_t         ePhot[50];   //[nPhot]
   Float_t         escPhot[50];   //[nPhot]
   Float_t         escRegrPhot[50];   //[nPhot]
   Float_t         escRegrPhotError[50];   //[nPhot]
   Float_t         escPhFixPhot[50];   //[nPhot]
   Float_t         escPhFixPhotError[50];   //[nPhot]
   Float_t         escRawPhot[50];   //[nPhot]
   Float_t         etascPhot[50];   //[nPhot]
   Float_t         phiscPhot[50];   //[nPhot]
   Float_t         xscPhot[50];   //[nPhot]
   Float_t         yscPhot[50];   //[nPhot]
   Float_t         zscPhot[50];   //[nPhot]
   Float_t         xcaloPhot[50];   //[nPhot]
   Float_t         ycaloPhot[50];   //[nPhot]
   Float_t         zcaloPhot[50];   //[nPhot]
   Float_t         eseedPhot[50];   //[nPhot]
   Float_t         etaPhot[50];   //[nPhot]
   Float_t         phiPhot[50];   //[nPhot]
   Float_t         timePhot;
   Float_t         e4SwissCrossPhot[50];   //[nPhot]
   Int_t           hasPixelSeedPhot[50];   //[nPhot]
   Int_t           hasMatchedPromptElePhot[50];   //[nPhot]
   Int_t           hasMatchedConvPhot[50];   //[nPhot]
   Bool_t          isEBPhot[50];   //[nPhot]
   Bool_t          isEEPhot[50];   //[nPhot]
   Bool_t          isEBEEGapPhot[50];   //[nPhot]
   Int_t           ntracksConvPhot[50];   //[nPhot]
   Bool_t          isValidVtxConvPhot[50];   //[nPhot]
   Float_t         pairInvmassConvPhot[50];   //[nPhot]
   Float_t         pairCotThetaSeperationConvPhot[50];   //[nPhot]
   Float_t         pairmomentumXConvPhot[50];   //[nPhot]
   Float_t         pairmomentumYConvPhot[50];   //[nPhot]
   Float_t         pairmomentumZConvPhot[50];   //[nPhot]
   Float_t         chi2ConvPhot[50];   //[nPhot]
   Float_t         nDofConvPhot[50];   //[nPhot]
   Float_t         eOverPConvPhot[50];   //[nPhot]
   Float_t         convVxConvPhot[50];   //[nPhot]
   Float_t         convVyConvPhot[50];   //[nPhot]
   Float_t         convVzConvPhot[50];   //[nPhot]
   Float_t         distOfMinimumApproachConvPhot[50];   //[nPhot]
   Float_t         dPhiTracksAtVtxConvPhot[50];   //[nPhot]
   Bool_t          pid_isEM[50];   //[nPhot]
   Bool_t          pid_isLoose[50];   //[nPhot]
   Bool_t          pid_isTight[50];   //[nPhot]
   Float_t         pid_jurECAL[50];   //[nPhot]
   Float_t         pid_twrHCAL[50];   //[nPhot]
   Float_t         pid_HoverE[50];   //[nPhot]
   Float_t         pid_hlwTrack[50];   //[nPhot]
   Float_t         pid_hlwTrackNoDz[50];   //[nPhot]
   Float_t         r9Phot[50];   //[nPhot]
   Float_t         s4RatioPhot[50];   //[nPhot]
   Float_t         sigmaRRPhot[50];   //[nPhot]
   Float_t         pid_etawid[50];   //[nPhot]
   Float_t         pid_jurECAL03[50];   //[nPhot]
   Float_t         pid_twrHCAL03[50];   //[nPhot]
   Float_t         pid_hlwTrack03[50];   //[nPhot]
   Float_t         pid_hlwTrack03NoDz[50];   //[nPhot]
   Float_t         pid_hlwTrack03ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged01ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged02ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged03ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged04ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged05ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoCharged06ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons01ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons02ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons03ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons04ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons05ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoPhotons06ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals01ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals02ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals03ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals04ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals05ForCiC[50];   //[nPhot]
   Float_t         pid_pfIsoNeutrals06ForCiC[50];   //[nPhot]
   Float_t         ptiso004Phot[50];   //[nPhot]
   Int_t           ntrkiso004Phot[50];   //[nPhot]
   Float_t         ptiso035Phot[50];   //[nPhot]
   Int_t           ntrkiso035Phot[50];   //[nPhot]
   Float_t         ptiso04Phot[50];   //[nPhot]
   Int_t           ntrkiso04Phot[50];   //[nPhot]
   Float_t         hcalovecal04Phot[50];   //[nPhot]
   Float_t         ecaliso04Phot[50];   //[nPhot]
   Float_t         pid_scetawid[50];   //[nPhot]
   Float_t         pid_scphiwid[50];   //[nPhot]
   Float_t         pid_lambdaRatio[50];   //[nPhot]
   Float_t         pid_esXwidth[50];   //[nPhot]
   Float_t         pid_esYwidth[50];   //[nPhot]
   Float_t         sMajMajPhot[50];   //[nPhot]
   Float_t         sMinMinPhot[50];   //[nPhot]
   Float_t         alphaPhot[50];   //[nPhot]
   Float_t         sEtaEtaPhot[50];   //[nPhot]
   Float_t         sEtaPhiPhot[50];   //[nPhot]
   Float_t         sPhiPhiPhot[50];   //[nPhot]
   Float_t         E1Phot[50];   //[nPhot]
   Float_t         E2OverE9Phot[50];   //[nPhot]
   Float_t         E4Phot[50];   //[nPhot]
   Float_t         E9Phot[50];   //[nPhot]
   Float_t         E25Phot[50];   //[nPhot]
   Int_t           ieleassocPhot[50];   //[nPhot]
   Float_t         pid_deltaRToTrackPhot[50];   //[nPhot]
   Int_t           passPreselection[50];   //[nPhot]
   Int_t           isEleTag_match[50];   //[nEle]
   Int_t           isEleProbe_match[50];   //[nPhot]
   Int_t           isEleProbe_ele_match[50];   //[nEle]
   Float_t         deltaR_EleTagGenReco[50];   //[nEle]
   Float_t         deltaR_EleProbeGenReco[50];   //[nPhot]
   Float_t         genEleMatched_index_tag[50];   //[nEle]
   Float_t         genEleMatched_index_probe[50];   //[nPhot]
   Int_t           passLooseElePtEta_match[50];   //[nPhot]
   Int_t           passLooseEleID_match[50];   //[nPhot]
   Int_t           passLooseEleImpactPar_match[50];   //[nPhot]
   Int_t           passLooseEleIsoRel_match[50];   //[nPhot]
   Int_t           passLooseEleMinHits_match[50];   //[nPhot]
   Int_t           passMediumElePtEta_match[50];   //[nPhot]
   Int_t           passMediumEleID_match[50];   //[nPhot]
   Int_t           passMediumEleImpactPar_match[50];   //[nPhot]
   Int_t           passMediumEleIsoRel_match[50];   //[nPhot]
   Int_t           passMediumEleMinHits_match[50];   //[nPhot]
   Int_t           passTightElePtEta_match[50];   //[nPhot]
   Int_t           passTightEleID_match[50];   //[nPhot]
   Int_t           passTightEleImpactPar_match[50];   //[nPhot]
   Int_t           passTightEleIsoRel_match[50];   //[nPhot]
   Int_t           passTightEleMinHits_match[50];   //[nPhot]
   Float_t         invMassEle_match[50];
   Int_t           isEleTag[50];   //[nEle]
   Int_t           isEleProbe[50];   //[nPhot]
   Int_t           isEleProbe_ele[50];   //[nEle]
   Int_t           passLooseElePtEta[50];   //[nPhot]
   Int_t           passLooseEleID[50];   //[nPhot]
   Int_t           passLooseEleImpactPar[50];   //[nPhot]
   Int_t           passLooseEleIsoRel[50];   //[nPhot]
   Int_t           passLooseEleMinHits[50];   //[nPhot]
   Int_t           passMediumElePtEta[50];   //[nPhot]
   Int_t           passMediumEleID[50];   //[nPhot]
   Int_t           passMediumEleImpactPar[50];   //[nPhot]
   Int_t           passMediumEleIsoRel[50];   //[nPhot]
   Int_t           passMediumEleMinHits[50];   //[nPhot]
   Int_t           passTightElePtEta[50];   //[nPhot]
   Int_t           passTightEleID[50];   //[nPhot]
   Int_t           passTightEleImpactPar[50];   //[nPhot]
   Int_t           passTightEleIsoRel[50];   //[nPhot]
   Int_t           passTightEleMinHits[50];   //[nPhot]
   Float_t         invMassEle[50];
   Float_t         BDT_output[50];   //[nPhot]
   vector<string>  *firedHLTNames;
   Float_t         epfMet;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_vtxId;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_NtotEvents;   //!
   TBranch        *b_xsection;   //!
   TBranch        *b_EquivLumi;   //!
   TBranch        *b_SampleID;   //!
   TBranch        *b_pu_weight;   //!
   TBranch        *b_pu_weight30;   //!
   TBranch        *b_pu_weight50;   //!
   TBranch        *b_pu_weight75;   //!
   TBranch        *b_pu_weight90;   //!
   TBranch        *b_LOGamma;   //!
   TBranch        *b_ISRGamma;   //!
   TBranch        *b_FSRGamma;   //!
   TBranch        *b_rhoAllJets;   //!
   TBranch        *b_rhoPF;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_energy;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_EoP;   //!
   TBranch        *b_electron_OneOverEMinusOneOverP;   //!
   TBranch        *b_electron_r9;   //!
   TBranch        *b_electron_SigmaIetaIeta;   //!
   TBranch        *b_electron_dEtaIn;   //!
   TBranch        *b_electron_dPhiIn;   //!
   TBranch        *b_electron_HoE;   //!
   TBranch        *b_electron_sc_eta;   //!
   TBranch        *b_electron_trkIso;   //!
   TBranch        *b_electron_ecalIso;   //!
   TBranch        *b_electron_hcalIso;   //!
   TBranch        *b_electron_trkIso03;   //!
   TBranch        *b_electron_ecalIso03;   //!
   TBranch        *b_electron_hcalIso03;   //!
   TBranch        *b_electron_chHad03Iso;   //!
   TBranch        *b_electron_nHad03Iso;   //!
   TBranch        *b_electron_phot03Iso;   //!
   TBranch        *b_electron_chHad04Iso;   //!
   TBranch        *b_electron_nHad04Iso;   //!
   TBranch        *b_electron_phot04Iso;   //!
   TBranch        *b_electron_chHad05Iso;   //!
   TBranch        *b_electron_nHad05Iso;   //!
   TBranch        *b_electron_phot05Iso;   //!
   TBranch        *b_nPhot;   //!
   TBranch        *b_ptPhot;   //!
   TBranch        *b_ePhot;   //!
   TBranch        *b_escPhot;   //!
   TBranch        *b_escRegrPhot;   //!
   TBranch        *b_escRegrPhotError;   //!
   TBranch        *b_escPhFixPhot;   //!
   TBranch        *b_escPhFixPhotError;   //!
   TBranch        *b_escRawPhot;   //!
   TBranch        *b_etascPhot;   //!
   TBranch        *b_phiscPhot;   //!
   TBranch        *b_xscPhot;   //!
   TBranch        *b_yscPhot;   //!
   TBranch        *b_zscPhot;   //!
   TBranch        *b_xcaloPhot;   //!
   TBranch        *b_ycaloPhot;   //!
   TBranch        *b_zcaloPhot;   //!
   TBranch        *b_eseedPhot;   //!
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
   TBranch        *b_r9Phot;   //!
   TBranch        *b_s4RatioPhot;   //!
   TBranch        *b_sigmaRRPhot;   //!
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
   TBranch        *b_passPreselection;   //!
   TBranch        *b_isEleTag_match;   //!
   TBranch        *b_isEleProbe_match;   //!
   TBranch        *b_isEleProbe_ele_match;   //!
   TBranch        *b_deltaR_EleTagGenReco;   //!
   TBranch        *b_deltaR_EleProbeGenReco;   //!
   TBranch        *b_genEleMatched_index_tag;   //!
   TBranch        *b_genEleMatched_index_probe;   //!
   TBranch        *b_passLooseElePtEta_match;   //!
   TBranch        *b_passLooseEleID_match;   //!
   TBranch        *b_passLooseEleImpactPar_match;   //!
   TBranch        *b_passLooseEleIsoRel_match;   //!
   TBranch        *b_passLooseEleMinHits_match;   //!
   TBranch        *b_passMediumElePtEta_match;   //!
   TBranch        *b_passMediumEleID_match;   //!
   TBranch        *b_passMediumEleImpactPar_match;   //!
   TBranch        *b_passMediumEleIsoRel_match;   //!
   TBranch        *b_passMediumEleMinHits_match;   //!
   TBranch        *b_passTightElePtEta_match;   //!
   TBranch        *b_passTightEleID_match;   //!
   TBranch        *b_passTightEleImpactPar_match;   //!
   TBranch        *b_passTightEleIsoRel_match;   //!
   TBranch        *b_passTightEleMinHits_match;   //!
   TBranch        *b_invMassEle_match;   //!
   TBranch        *b_isEleTag;   //!
   TBranch        *b_isEleProbe;   //!
   TBranch        *b_isEleProbe_ele;   //!
   TBranch        *b_passLooseElePtEta;   //!
   TBranch        *b_passLooseEleID;   //!
   TBranch        *b_passLooseEleImpactPar;   //!
   TBranch        *b_passLooseEleIsoRel;   //!
   TBranch        *b_passLooseEleMinHits;   //!
   TBranch        *b_passMediumElePtEta;   //!
   TBranch        *b_passMediumEleID;   //!
   TBranch        *b_passMediumEleImpactPar;   //!
   TBranch        *b_passMediumEleIsoRel;   //!
   TBranch        *b_passMediumEleMinHits;   //!
   TBranch        *b_passTightElePtEta;   //!
   TBranch        *b_passTightEleID;   //!
   TBranch        *b_passTightEleImpactPar;   //!
   TBranch        *b_passTightEleIsoRel;   //!
   TBranch        *b_passTightEleMinHits;   //!
   TBranch        *b_invMassEle;   //!
   TBranch        *b_BDT_output;   //!
   TBranch        *b_firedHLTNames;   //!
   TBranch        *b_epfMet;   //!

   riduttore(TTree *tree=0);
   virtual ~riduttore();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   bool     isHLT_TandP();
   bool     isHLT_30();
   bool     isHLT_50();
   bool     isHLT_75();
   bool     isHLT_90();
};

#endif

#ifdef riduttore_cxx
riduttore::riduttore(TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file 
  // used to generate this class and read the Tree.                                                
  if (tree == 0) {
    TChain * chain = new TChain("AnaTree","");
    // chain->Add("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv3_data.cicpfloose..DrellYan_v1_BDTbug/redntp_DoubleElectron_Run2012*.root/AnaTree");
    chain->Add("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2_extra.cicpfloose..DrellYan_v1_BDTbug/redntp_DYJetsToLL_M-50*.root/AnaTree");
    tree = chain;
  }
  Init(tree);
}

riduttore::~riduttore()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t riduttore::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t riduttore::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void riduttore::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   firedHLTNames = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("isMC", &isMC, &b_isMC);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("vtxId", &vtxId, &b_vtxId);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("NtotEvents", &NtotEvents, &b_NtotEvents);
   fChain->SetBranchAddress("xsection", &xsection, &b_xsection);
   fChain->SetBranchAddress("EquivLumi", &EquivLumi, &b_EquivLumi);
   fChain->SetBranchAddress("SampleID", &SampleID, &b_SampleID);
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight);
   fChain->SetBranchAddress("pu_weight30", &pu_weight30, &b_pu_weight30);
   fChain->SetBranchAddress("pu_weight50", &pu_weight50, &b_pu_weight50);
   fChain->SetBranchAddress("pu_weight75", &pu_weight75, &b_pu_weight75);
   fChain->SetBranchAddress("pu_weight90", &pu_weight90, &b_pu_weight90);
   fChain->SetBranchAddress("LOGamma", &LOGamma, &b_LOGamma);
   fChain->SetBranchAddress("ISRGamma", &ISRGamma, &b_ISRGamma);
   fChain->SetBranchAddress("FSRGamma", &FSRGamma, &b_FSRGamma);
   fChain->SetBranchAddress("rhoAllJets", &rhoAllJets, &b_rhoAllJets);
   fChain->SetBranchAddress("rhoPF", &rhoPF, &b_rhoPF);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("electron_pt", electron_pt, &b_electron_pt);
   fChain->SetBranchAddress("electron_energy", electron_energy, &b_electron_energy);
   fChain->SetBranchAddress("electron_phi", electron_phi, &b_electron_phi);
   fChain->SetBranchAddress("electron_eta", electron_eta, &b_electron_eta);
   fChain->SetBranchAddress("electron_EoP", electron_EoP, &b_electron_EoP);
   fChain->SetBranchAddress("electron_OneOverEMinusOneOverP", electron_OneOverEMinusOneOverP, &b_electron_OneOverEMinusOneOverP);
   fChain->SetBranchAddress("electron_r9", electron_r9, &b_electron_r9);
   fChain->SetBranchAddress("electron_SigmaIetaIeta", electron_SigmaIetaIeta, &b_electron_SigmaIetaIeta);
   fChain->SetBranchAddress("electron_dEtaIn", electron_dEtaIn, &b_electron_dEtaIn);
   fChain->SetBranchAddress("electron_dPhiIn", electron_dPhiIn, &b_electron_dPhiIn);
   fChain->SetBranchAddress("electron_HoE", electron_HoE, &b_electron_HoE);
   fChain->SetBranchAddress("electron_sc_eta", electron_sc_eta, &b_electron_sc_eta);
   fChain->SetBranchAddress("electron_trkIso", electron_trkIso, &b_electron_trkIso);
   fChain->SetBranchAddress("electron_ecalIso", electron_ecalIso, &b_electron_ecalIso);
   fChain->SetBranchAddress("electron_hcalIso", electron_hcalIso, &b_electron_hcalIso);
   fChain->SetBranchAddress("electron_trkIso03", electron_trkIso03, &b_electron_trkIso03);
   fChain->SetBranchAddress("electron_ecalIso03", electron_ecalIso03, &b_electron_ecalIso03);
   fChain->SetBranchAddress("electron_hcalIso03", electron_hcalIso03, &b_electron_hcalIso03);
   fChain->SetBranchAddress("electron_chHad03Iso", electron_chHad03Iso, &b_electron_chHad03Iso);
   fChain->SetBranchAddress("electron_nHad03Iso", electron_nHad03Iso, &b_electron_nHad03Iso);
   fChain->SetBranchAddress("electron_phot03Iso", electron_phot03Iso, &b_electron_phot03Iso);
   fChain->SetBranchAddress("electron_chHad04Iso", electron_chHad04Iso, &b_electron_chHad04Iso);
   fChain->SetBranchAddress("electron_nHad04Iso", electron_nHad04Iso, &b_electron_nHad04Iso);
   fChain->SetBranchAddress("electron_phot04Iso", electron_phot04Iso, &b_electron_phot04Iso);
   fChain->SetBranchAddress("electron_chHad05Iso", electron_chHad05Iso, &b_electron_chHad05Iso);
   fChain->SetBranchAddress("electron_nHad05Iso", electron_nHad05Iso, &b_electron_nHad05Iso);
   fChain->SetBranchAddress("electron_phot05Iso", electron_phot05Iso, &b_electron_phot05Iso);
   fChain->SetBranchAddress("nPhot", &nPhot, &b_nPhot);
   fChain->SetBranchAddress("ptPhot", ptPhot, &b_ptPhot);
   fChain->SetBranchAddress("ePhot", ePhot, &b_ePhot);
   fChain->SetBranchAddress("escPhot", escPhot, &b_escPhot);
   fChain->SetBranchAddress("escRegrPhot", escRegrPhot, &b_escRegrPhot);
   fChain->SetBranchAddress("escRegrPhotError", escRegrPhotError, &b_escRegrPhotError);
   fChain->SetBranchAddress("escPhFixPhot", escPhFixPhot, &b_escPhFixPhot);
   fChain->SetBranchAddress("escPhFixPhotError", escPhFixPhotError, &b_escPhFixPhotError);
   fChain->SetBranchAddress("escRawPhot", escRawPhot, &b_escRawPhot);
   fChain->SetBranchAddress("etascPhot", etascPhot, &b_etascPhot);
   fChain->SetBranchAddress("phiscPhot", phiscPhot, &b_phiscPhot);
   fChain->SetBranchAddress("xscPhot", xscPhot, &b_xscPhot);
   fChain->SetBranchAddress("yscPhot", yscPhot, &b_yscPhot);
   fChain->SetBranchAddress("zscPhot", zscPhot, &b_zscPhot);
   fChain->SetBranchAddress("xcaloPhot", xcaloPhot, &b_xcaloPhot);
   fChain->SetBranchAddress("ycaloPhot", ycaloPhot, &b_ycaloPhot);
   fChain->SetBranchAddress("zcaloPhot", zcaloPhot, &b_zcaloPhot);
   fChain->SetBranchAddress("eseedPhot", eseedPhot, &b_eseedPhot);
   fChain->SetBranchAddress("etaPhot", etaPhot, &b_etaPhot);
   fChain->SetBranchAddress("phiPhot", phiPhot, &b_phiPhot);
   fChain->SetBranchAddress("timePhot", &timePhot, &b_timePhot);
   fChain->SetBranchAddress("e4SwissCrossPhot", e4SwissCrossPhot, &b_e4SwissCrossPhot);
   fChain->SetBranchAddress("hasPixelSeedPhot", hasPixelSeedPhot, &b_hasPixelSeedPhot);
   fChain->SetBranchAddress("hasMatchedPromptElePhot", hasMatchedPromptElePhot, &b_hasMatchedPromptElePhot);
   fChain->SetBranchAddress("hasMatchedConvPhot", hasMatchedConvPhot, &b_hasMatchedConvPhot);
   fChain->SetBranchAddress("isEBPhot", isEBPhot, &b_isEBPhot);
   fChain->SetBranchAddress("isEEPhot", isEEPhot, &b_isEEPhot);
   fChain->SetBranchAddress("isEBEEGapPhot", isEBEEGapPhot, &b_isEBEEGapPhot);
   fChain->SetBranchAddress("ntracksConvPhot", ntracksConvPhot, &b_ntracksConvPhot);
   fChain->SetBranchAddress("isValidVtxConvPhot", isValidVtxConvPhot, &b_isValidVtxConvPhot);
   fChain->SetBranchAddress("pairInvmassConvPhot", pairInvmassConvPhot, &b_pairInvmassConvPhot);
   fChain->SetBranchAddress("pairCotThetaSeperationConvPhot", pairCotThetaSeperationConvPhot, &b_pairCotThetaSeperationConvPhot);
   fChain->SetBranchAddress("pairmomentumXConvPhot", pairmomentumXConvPhot, &b_pairmomentumXConvPhot);
   fChain->SetBranchAddress("pairmomentumYConvPhot", pairmomentumYConvPhot, &b_pairmomentumYConvPhot);
   fChain->SetBranchAddress("pairmomentumZConvPhot", pairmomentumZConvPhot, &b_pairmomentumZConvPhot);
   fChain->SetBranchAddress("chi2ConvPhot", chi2ConvPhot, &b_chi2ConvPhot);
   fChain->SetBranchAddress("nDofConvPhot", nDofConvPhot, &b_nDofConvPhot);
   fChain->SetBranchAddress("eOverPConvPhot", eOverPConvPhot, &b_eOverPConvPhot);
   fChain->SetBranchAddress("convVxConvPhot", convVxConvPhot, &b_convVxConvPhot);
   fChain->SetBranchAddress("convVyConvPhot", convVyConvPhot, &b_convVyConvPhot);
   fChain->SetBranchAddress("convVzConvPhot", convVzConvPhot, &b_convVzConvPhot);
   fChain->SetBranchAddress("distOfMinimumApproachConvPhot", distOfMinimumApproachConvPhot, &b_distOfMinimumApproachConvPhot);
   fChain->SetBranchAddress("dPhiTracksAtVtxConvPhot", dPhiTracksAtVtxConvPhot, &b_dPhiTracksAtVtxConvPhot);
   fChain->SetBranchAddress("pid_isEM", pid_isEM, &b_pid_isEM);
   fChain->SetBranchAddress("pid_isLoose", pid_isLoose, &b_pid_isLoose);
   fChain->SetBranchAddress("pid_isTight", pid_isTight, &b_pid_isTight);
   fChain->SetBranchAddress("pid_jurECAL", pid_jurECAL, &b_pid_jurECAL);
   fChain->SetBranchAddress("pid_twrHCAL", pid_twrHCAL, &b_pid_twrHCAL);
   fChain->SetBranchAddress("pid_HoverE", pid_HoverE, &b_pid_HoverE);
   fChain->SetBranchAddress("pid_hlwTrack", pid_hlwTrack, &b_pid_hlwTrack);
   fChain->SetBranchAddress("pid_hlwTrackNoDz", pid_hlwTrackNoDz, &b_pid_hlwTrackNoDz);
   fChain->SetBranchAddress("r9Phot", r9Phot, &b_r9Phot);
   fChain->SetBranchAddress("s4RatioPhot", s4RatioPhot, &b_s4RatioPhot);
   fChain->SetBranchAddress("sigmaRRPhot", sigmaRRPhot, &b_sigmaRRPhot);
   fChain->SetBranchAddress("pid_etawid", pid_etawid, &b_pid_etawid);
   fChain->SetBranchAddress("pid_jurECAL03", pid_jurECAL03, &b_pid_jurECAL03);
   fChain->SetBranchAddress("pid_twrHCAL03", pid_twrHCAL03, &b_pid_twrHCAL03);
   fChain->SetBranchAddress("pid_hlwTrack03", pid_hlwTrack03, &b_pid_hlwTrack03);
   fChain->SetBranchAddress("pid_hlwTrack03NoDz", pid_hlwTrack03NoDz, &b_pid_hlwTrack03NoDz);
   fChain->SetBranchAddress("pid_hlwTrack03ForCiC", pid_hlwTrack03ForCiC, &b_pid_hlwTrack03ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged01ForCiC", pid_pfIsoCharged01ForCiC, &b_pid_pfIsoCharged01ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged02ForCiC", pid_pfIsoCharged02ForCiC, &b_pid_pfIsoCharged02ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged03ForCiC", pid_pfIsoCharged03ForCiC, &b_pid_pfIsoCharged03ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged04ForCiC", pid_pfIsoCharged04ForCiC, &b_pid_pfIsoCharged04ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged05ForCiC", pid_pfIsoCharged05ForCiC, &b_pid_pfIsoCharged05ForCiC);
   fChain->SetBranchAddress("pid_pfIsoCharged06ForCiC", pid_pfIsoCharged06ForCiC, &b_pid_pfIsoCharged06ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons01ForCiC", pid_pfIsoPhotons01ForCiC, &b_pid_pfIsoPhotons01ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons02ForCiC", pid_pfIsoPhotons02ForCiC, &b_pid_pfIsoPhotons02ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons03ForCiC", pid_pfIsoPhotons03ForCiC, &b_pid_pfIsoPhotons03ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons04ForCiC", pid_pfIsoPhotons04ForCiC, &b_pid_pfIsoPhotons04ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons05ForCiC", pid_pfIsoPhotons05ForCiC, &b_pid_pfIsoPhotons05ForCiC);
   fChain->SetBranchAddress("pid_pfIsoPhotons06ForCiC", pid_pfIsoPhotons06ForCiC, &b_pid_pfIsoPhotons06ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals01ForCiC", pid_pfIsoNeutrals01ForCiC, &b_pid_pfIsoNeutrals01ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals02ForCiC", pid_pfIsoNeutrals02ForCiC, &b_pid_pfIsoNeutrals02ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals03ForCiC", pid_pfIsoNeutrals03ForCiC, &b_pid_pfIsoNeutrals03ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals04ForCiC", pid_pfIsoNeutrals04ForCiC, &b_pid_pfIsoNeutrals04ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals05ForCiC", pid_pfIsoNeutrals05ForCiC, &b_pid_pfIsoNeutrals05ForCiC);
   fChain->SetBranchAddress("pid_pfIsoNeutrals06ForCiC", pid_pfIsoNeutrals06ForCiC, &b_pid_pfIsoNeutrals06ForCiC);
   fChain->SetBranchAddress("ptiso004Phot", ptiso004Phot, &b_ptiso004Phot);
   fChain->SetBranchAddress("ntrkiso004Phot", ntrkiso004Phot, &b_ntrkiso004Phot);
   fChain->SetBranchAddress("ptiso035Phot", ptiso035Phot, &b_ptiso035Phot);
   fChain->SetBranchAddress("ntrkiso035Phot", ntrkiso035Phot, &b_ntrkiso035Phot);
   fChain->SetBranchAddress("ptiso04Phot", ptiso04Phot, &b_ptiso04Phot);
   fChain->SetBranchAddress("ntrkiso04Phot", ntrkiso04Phot, &b_ntrkiso04Phot);
   fChain->SetBranchAddress("hcalovecal04Phot", hcalovecal04Phot, &b_hcalovecal04Phot);
   fChain->SetBranchAddress("ecaliso04Phot", ecaliso04Phot, &b_ecaliso04Phot);
   fChain->SetBranchAddress("pid_scetawid", pid_scetawid, &b_pid_scetawid);
   fChain->SetBranchAddress("pid_scphiwid", pid_scphiwid, &b_pid_scphiwid);
   fChain->SetBranchAddress("pid_lambdaRatio", pid_lambdaRatio, &b_pid_lambdaRatio);
   fChain->SetBranchAddress("pid_esXwidth", pid_esXwidth, &b_pid_esXwidth);
   fChain->SetBranchAddress("pid_esYwidth", pid_esYwidth, &b_pid_esYwidth);
   fChain->SetBranchAddress("sMajMajPhot", sMajMajPhot, &b_sMajMajPhot);
   fChain->SetBranchAddress("sMinMinPhot", sMinMinPhot, &b_sMinMinPhot);
   fChain->SetBranchAddress("alphaPhot", alphaPhot, &b_alphaPhot);
   fChain->SetBranchAddress("sEtaEtaPhot", sEtaEtaPhot, &b_sEtaEtaPhot);
   fChain->SetBranchAddress("sEtaPhiPhot", sEtaPhiPhot, &b_sEtaPhiPhot);
   fChain->SetBranchAddress("sPhiPhiPhot", sPhiPhiPhot, &b_sPhiPhiPhot);
   fChain->SetBranchAddress("E1Phot", E1Phot, &b_E1Phot);
   fChain->SetBranchAddress("E2OverE9Phot", E2OverE9Phot, &b_E2OverE9Phot);
   fChain->SetBranchAddress("E4Phot", E4Phot, &b_E4Phot);
   fChain->SetBranchAddress("E9Phot", E9Phot, &b_E9Phot);
   fChain->SetBranchAddress("E25Phot", E25Phot, &b_E25Phot);
   fChain->SetBranchAddress("ieleassocPhot", ieleassocPhot, &b_ieleassocPhot);
   fChain->SetBranchAddress("pid_deltaRToTrackPhot", pid_deltaRToTrackPhot, &b_pid_deltaRToTrackPhot);
   fChain->SetBranchAddress("passPreselection", passPreselection, &b_passPreselection);
   fChain->SetBranchAddress("isEleTag_match", isEleTag_match, &b_isEleTag_match);
   fChain->SetBranchAddress("isEleProbe_match", isEleProbe_match, &b_isEleProbe_match);
   fChain->SetBranchAddress("isEleProbe_ele_match", isEleProbe_ele_match, &b_isEleProbe_ele_match);
   fChain->SetBranchAddress("deltaR_EleTagGenReco", deltaR_EleTagGenReco, &b_deltaR_EleTagGenReco);
   fChain->SetBranchAddress("deltaR_EleProbeGenReco", deltaR_EleProbeGenReco, &b_deltaR_EleProbeGenReco);
   fChain->SetBranchAddress("genEleMatched_index_tag", genEleMatched_index_tag, &b_genEleMatched_index_tag);
   fChain->SetBranchAddress("genEleMatched_index_probe", genEleMatched_index_probe, &b_genEleMatched_index_probe);
   fChain->SetBranchAddress("passLooseElePtEta_match", passLooseElePtEta_match, &b_passLooseElePtEta_match);
   fChain->SetBranchAddress("passLooseEleID_match", passLooseEleID_match, &b_passLooseEleID_match);
   fChain->SetBranchAddress("passLooseEleImpactPar_match", passLooseEleImpactPar_match, &b_passLooseEleImpactPar_match);
   fChain->SetBranchAddress("passLooseEleIsoRel_match", passLooseEleIsoRel_match, &b_passLooseEleIsoRel_match);
   fChain->SetBranchAddress("passLooseEleMinHits_match", passLooseEleMinHits_match, &b_passLooseEleMinHits_match);
   fChain->SetBranchAddress("passMediumElePtEta_match", passMediumElePtEta_match, &b_passMediumElePtEta_match);
   fChain->SetBranchAddress("passMediumEleID_match", passMediumEleID_match, &b_passMediumEleID_match);
   fChain->SetBranchAddress("passMediumEleImpactPar_match", passMediumEleImpactPar_match, &b_passMediumEleImpactPar_match);
   fChain->SetBranchAddress("passMediumEleIsoRel_match", passMediumEleIsoRel_match, &b_passMediumEleIsoRel_match);
   fChain->SetBranchAddress("passMediumEleMinHits_match", passMediumEleMinHits_match, &b_passMediumEleMinHits_match);
   fChain->SetBranchAddress("passTightElePtEta_match", passTightElePtEta_match, &b_passTightElePtEta_match);
   fChain->SetBranchAddress("passTightEleID_match", passTightEleID_match, &b_passTightEleID_match);
   fChain->SetBranchAddress("passTightEleImpactPar_match", passTightEleImpactPar_match, &b_passTightEleImpactPar_match);
   fChain->SetBranchAddress("passTightEleIsoRel_match", passTightEleIsoRel_match, &b_passTightEleIsoRel_match);
   fChain->SetBranchAddress("passTightEleMinHits_match", passTightEleMinHits_match, &b_passTightEleMinHits_match);
   fChain->SetBranchAddress("invMassEle_match", invMassEle_match, &b_invMassEle_match);
   fChain->SetBranchAddress("isEleTag", isEleTag, &b_isEleTag);
   fChain->SetBranchAddress("isEleProbe", isEleProbe, &b_isEleProbe);
   fChain->SetBranchAddress("isEleProbe_ele", isEleProbe_ele, &b_isEleProbe_ele);
   fChain->SetBranchAddress("passLooseElePtEta", passLooseElePtEta, &b_passLooseElePtEta);
   fChain->SetBranchAddress("passLooseEleID", passLooseEleID, &b_passLooseEleID);
   fChain->SetBranchAddress("passLooseEleImpactPar", passLooseEleImpactPar, &b_passLooseEleImpactPar);
   fChain->SetBranchAddress("passLooseEleIsoRel", passLooseEleIsoRel, &b_passLooseEleIsoRel);
   fChain->SetBranchAddress("passLooseEleMinHits", passLooseEleMinHits, &b_passLooseEleMinHits);
   fChain->SetBranchAddress("passMediumElePtEta", passMediumElePtEta, &b_passMediumElePtEta);
   fChain->SetBranchAddress("passMediumEleID", passMediumEleID, &b_passMediumEleID);
   fChain->SetBranchAddress("passMediumEleImpactPar", passMediumEleImpactPar, &b_passMediumEleImpactPar);
   fChain->SetBranchAddress("passMediumEleIsoRel", passMediumEleIsoRel, &b_passMediumEleIsoRel);
   fChain->SetBranchAddress("passMediumEleMinHits", passMediumEleMinHits, &b_passMediumEleMinHits);
   fChain->SetBranchAddress("passTightElePtEta", passTightElePtEta, &b_passTightElePtEta);
   fChain->SetBranchAddress("passTightEleID", passTightEleID, &b_passTightEleID);
   fChain->SetBranchAddress("passTightEleImpactPar", passTightEleImpactPar, &b_passTightEleImpactPar);
   fChain->SetBranchAddress("passTightEleIsoRel", passTightEleIsoRel, &b_passTightEleIsoRel);
   fChain->SetBranchAddress("passTightEleMinHits", passTightEleMinHits, &b_passTightEleMinHits);
   fChain->SetBranchAddress("invMassEle", invMassEle, &b_invMassEle);
   fChain->SetBranchAddress("BDT_output", BDT_output, &b_BDT_output);
   fChain->SetBranchAddress("firedHLTNames", &firedHLTNames, &b_firedHLTNames);
   fChain->SetBranchAddress("epfMet", &epfMet, &b_epfMet);
   Notify();
}

Bool_t riduttore::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void riduttore::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t riduttore::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef riduttore_cxx
