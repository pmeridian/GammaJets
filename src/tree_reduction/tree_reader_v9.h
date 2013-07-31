//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 19 08:46:43 2013 by ROOT version 5.32/00
// from TTree pippo/Analysis tree
// found on file: root://cmseos.fnal.gov//eos/uscms/store/user/meridian/data/53xv4/Photon_Run2012A-22Jan2013-v1/output_91_5_8qO.root
//////////////////////////////////////////////////////////

#ifndef tree_reader_v9_h
#define tree_reader_v9_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class tree_reader_v9 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         genpt;
   Int_t           genProcessId;
   Float_t         genQScale;
   Bool_t          isMC;
   Bool_t          passEcalLaserFilter;
   Bool_t          passHBHENoiseFilter;
   Bool_t          passCSCTightHaloFilter;
   Bool_t          passhcalLaserEventFilter;
   Bool_t          passEcalDeadCellTriggerPrimitiveFilter;
   Bool_t          passtrackingFailureFilter;
   Bool_t          passeeBadScFilter;
   Int_t           store;
   Int_t           lbn;
   Int_t           bx;
   Int_t           orbit;
   Int_t           run;
   Int_t           event;
   Float_t         rhoPF;
   Float_t         rhoCalo;
   Float_t         rhoAllJets;
   Int_t           nMC;
   Int_t           pdgIdMC[1];   //[nMC]
   Int_t           statusMC[1];   //[nMC]
   Int_t           motherIDMC[1];   //[nMC]
   Float_t         ptMC [1];   //[nMC]
   Float_t         eMC  [1];   //[nMC]
   Float_t         etaMC[1];   //[nMC]
   Float_t         phiMC[1];   //[nMC]
   Float_t         isoParticleChargedDR01MC[1];   //[nMC]
   Float_t         isoParticleChargedDR02MC[1];   //[nMC]
   Float_t         isoParticleChargedDR03MC[1];   //[nMC]
   Float_t         isoParticleChargedDR04MC[1];   //[nMC]
   Float_t         isoParticleChargedDR05MC[1];   //[nMC]
   Float_t         isoParticleEMNeutralDR01MC[1];   //[nMC]
   Float_t         isoParticleEMNeutralDR02MC[1];   //[nMC]
   Float_t         isoParticleEMNeutralDR03MC[1];   //[nMC]
   Float_t         isoParticleEMNeutralDR04MC[1];   //[nMC]
   Float_t         isoParticleEMNeutralDR05MC[1];   //[nMC]
   Float_t         isoParticleHADNeutralDR01MC[1];   //[nMC]
   Float_t         isoParticleHADNeutralDR02MC[1];   //[nMC]
   Float_t         isoParticleHADNeutralDR03MC[1];   //[nMC]
   Float_t         isoParticleHADNeutralDR04MC[1];   //[nMC]
   Float_t         isoParticleHADNeutralDR05MC[1];   //[nMC]
   Float_t         isoPartonDR01MC[1];   //[nMC]
   Float_t         isoPartonDR02MC[1];   //[nMC]
   Float_t         isoPartonDR03MC[1];   //[nMC]
   Float_t         isoPartonDR04MC[1];   //[nMC]
   Float_t         isoPartonDR05MC[1];   //[nMC]
   Int_t           pu_n;
   Int_t           pu_true_n;
   Float_t         pu_zpos[1];   //[pu_n]
   Float_t         pu_sumpt_lowpt[1];   //[pu_n]
   Float_t         pu_sumpt_highpt[1];   //[pu_n]
   Float_t         pu_ntrks_lowpt[1];   //[pu_n]
   Float_t         pu_ntrks_highpt[1];   //[pu_n]
   Int_t           nPhot;
   Float_t         ptPhot [8];   //[nPhot]
   Float_t         ePhot  [8];   //[nPhot]
   Float_t         escPhot  [8];   //[nPhot]
   Float_t         escRegrPhot  [8];   //[nPhot]
   Float_t         escRegrPhotError  [8];   //[nPhot]
   Float_t         escPhFixPhot  [8];   //[nPhot]
   Float_t         escPhFixPhotError  [8];   //[nPhot]
   Float_t         escRawPhot  [8];   //[nPhot]
   Float_t         etascPhot  [8];   //[nPhot]
   Float_t         phiscPhot  [8];   //[nPhot]
   Float_t         xscPhot  [8];   //[nPhot]
   Float_t         yscPhot  [8];   //[nPhot]
   Float_t         zscPhot  [8];   //[nPhot]
   Float_t         xcaloPhot  [8];   //[nPhot]
   Float_t         ycaloPhot  [8];   //[nPhot]
   Float_t         zcaloPhot  [8];   //[nPhot]
   Float_t         eseedPhot  [8];   //[nPhot]
   Float_t         etaPhot[8];   //[nPhot]
   Float_t         phiPhot[8];   //[nPhot]
   Float_t         timePhot[8];   //[nPhot]
   Float_t         e4SwissCrossPhot[8];   //[nPhot]
   Int_t           hasPixelSeedPhot[8];   //[nPhot]
   Int_t           hasMatchedPromptElePhot[8];   //[nPhot]
   Int_t           hasMatchedConvPhot[8];   //[nPhot]
   Bool_t          isEBPhot[8];   //[nPhot]
   Bool_t          isEEPhot[8];   //[nPhot]
   Bool_t          isEBEEGapPhot[8];   //[nPhot]
   Int_t           ntracksConvPhot[8];   //[nPhot]
   Bool_t          isValidVtxConvPhot[8];   //[nPhot]
   Float_t         pairInvmassConvPhot[8];   //[nPhot]
   Float_t         pairCotThetaSeperationConvPhot[8];   //[nPhot]
   Float_t         pairmomentumXConvPhot[8];   //[nPhot]
   Float_t         pairmomentumYConvPhot[8];   //[nPhot]
   Float_t         pairmomentumZConvPhot[8];   //[nPhot]
   Float_t         chi2ConvPhot[8];   //[nPhot]
   Float_t         nDofConvPhot[8];   //[nPhot]
   Float_t         eOverPConvPhot[8];   //[nPhot]
   Float_t         convVxConvPhot[8];   //[nPhot]
   Float_t         convVyConvPhot[8];   //[nPhot]
   Float_t         convVzConvPhot[8];   //[nPhot]
   Float_t         distOfMinimumApproachConvPhot[8];   //[nPhot]
   Float_t         dPhiTracksAtVtxConvPhot[8];   //[nPhot]
   Bool_t          pid_isEM[8];   //[nPhot]
   Bool_t          pid_isLoose[8];   //[nPhot]
   Bool_t          pid_isTight[8];   //[nPhot]
   Float_t         pid_jurECAL[8];   //[nPhot]
   Float_t         pid_twrHCAL[8];   //[nPhot]
   Float_t         pid_HoverE[8];   //[nPhot]
   Float_t         pid_hlwTrack[8];   //[nPhot]
   Float_t         pid_hlwTrackNoDz[8];   //[nPhot]
   Float_t         pid_hlwTrackForCiC[40][100];
   Float_t         pid_etawid[8];   //[nPhot]
   Float_t         pid_jurECAL03[8];   //[nPhot]
   Float_t         pid_twrHCAL03[8];   //[nPhot]
   Float_t         pid_hlwTrack03[8];   //[nPhot]
   Float_t         pid_hlwTrack03NoDz[8];   //[nPhot]
   Float_t         pid_hlwTrack03ForCiC[40][100];
   Float_t         pid_pfIsoCharged01ForCiC[40][100];
   Float_t         pid_pfIsoCharged02ForCiC[40][100];
   Float_t         pid_pfIsoCharged03ForCiC[40][100];
   Float_t         pid_pfIsoCharged04ForCiC[40][100];
   Float_t         pid_pfIsoCharged05ForCiC[40][100];
   Float_t         pid_pfIsoCharged06ForCiC[40][100];
   Float_t         pid_pfIsoPhotons01ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoPhotons02ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoPhotons03ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoPhotons04ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoPhotons05ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoPhotons06ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals01ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals02ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals03ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals04ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals05ForCiC[8];   //[nPhot]
   Float_t         pid_pfIsoNeutrals06ForCiC[8];   //[nPhot]
   Float_t         ptiso004Phot[8];   //[nPhot]
   Int_t           ntrkiso004Phot[8];   //[nPhot]
   Float_t         ptiso035Phot[8];   //[nPhot]
   Int_t           ntrkiso035Phot[8];   //[nPhot]
   Float_t         ptiso04Phot[8];   //[nPhot]
   Int_t           ntrkiso04Phot[8];   //[nPhot]
   Float_t         hcalovecal04Phot[8];   //[nPhot]
   Float_t         ecaliso04Phot[8];   //[nPhot]
   Float_t         pid_scetawid[8];   //[nPhot]
   Float_t         pid_scphiwid[8];   //[nPhot]
   Float_t         pid_lambdaRatio[8];   //[nPhot]
   Float_t         pid_esXwidth[8];   //[nPhot]
   Float_t         pid_esYwidth[8];   //[nPhot]
   Float_t         sMajMajPhot[8];   //[nPhot]
   Float_t         sMinMinPhot[8];   //[nPhot]
   Float_t         alphaPhot[8];   //[nPhot]
   Float_t         sEtaEtaPhot[8];   //[nPhot]
   Float_t         sEtaPhiPhot[8];   //[nPhot]
   Float_t         sPhiPhiPhot[8];   //[nPhot]
   Float_t         E1Phot[8];   //[nPhot]
   Float_t         E2OverE9Phot[8];   //[nPhot]
   Float_t         E4Phot[8];   //[nPhot]
   Float_t         E9Phot[8];   //[nPhot]
   Float_t         E25Phot[8];   //[nPhot]
   Int_t           ieleassocPhot[8];   //[nPhot]
   Float_t         pid_deltaRToTrackPhot[8];   //[nPhot]
   Int_t           nElePhot;
   Float_t         pid_jurECALElePhot [5];   //[nElePhot]
   Float_t         pid_twrHCALElePhot [5];   //[nElePhot]
   Float_t         pid_HoverEElePhot [5];   //[nElePhot]
   Float_t         pid_hlwTrackElePhot [5];   //[nElePhot]
   Float_t         pid_etawidElePhot [5];   //[nElePhot]
   Float_t         pid_dphivtxElePhot [5];   //[nElePhot]
   Float_t         pid_detavtxElePhot [5];   //[nElePhot]
   Int_t           pid_mishitsElePhot [5];   //[nElePhot]
   Float_t         pid_distElePhot [5];   //[nElePhot]
   Float_t         pid_dcotElePhot [5];   //[nElePhot]
   Float_t         pid_ptElePhot [5];   //[nElePhot]
   Int_t           nJet_akt5;
   Float_t         ptJet_akt5 [86];   //[nJet_akt5]
   Float_t         ptCorrJet_akt5 [86];   //[nJet_akt5]
   Float_t         eJet_akt5  [86];   //[nJet_akt5]
   Float_t         etaJet_akt5[86];   //[nJet_akt5]
   Float_t         phiJet_akt5[86];   //[nJet_akt5]
   Float_t         emfJet_akt5[86];   //[nJet_akt5]
   Float_t         n90Jet_akt5[86];   //[nJet_akt5]
   Float_t         n90HitsJet_akt5[86];   //[nJet_akt5]
   Float_t         fHPDJet_akt5[86];   //[nJet_akt5]
   Float_t         fRBXJet_akt5[86];   //[nJet_akt5]
   Int_t           nJet_akt7;
   Float_t         ptJet_akt7 [54];   //[nJet_akt7]
   Float_t         ptCorrJet_akt7 [86];   //[nJet_akt5]
   Float_t         eJet_akt7  [54];   //[nJet_akt7]
   Float_t         etaJet_akt7[54];   //[nJet_akt7]
   Float_t         phiJet_akt7[54];   //[nJet_akt7]
   Float_t         emfJet_akt7[54];   //[nJet_akt7]
   Float_t         n90Jet_akt7[54];   //[nJet_akt7]
   Float_t         n90HitsJet_akt7[54];   //[nJet_akt7]
   Float_t         fHPDJet_akt7[54];   //[nJet_akt7]
   Float_t         fRBXJet_akt7[54];   //[nJet_akt7]
   Int_t           nJet_pfakt5;
   Float_t         ptJet_pfakt5 [95];   //[nJet_pfakt5]
   Float_t         ptCorrJet_pfakt5 [95];   //[nJet_pfakt5]
   Float_t         eJet_pfakt5  [95];   //[nJet_pfakt5]
   Float_t         etaJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptDJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         rmsCandJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         rmsCandTrueJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         rmsCandTrue_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         axis1Jet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         axis2Jet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pullJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         tanaJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptD_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         rmsCandTrue_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         axis1_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         axis2_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pull_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         tana_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         RchgJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         RneutralJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         RJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         Rchg_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nChg_ptCutJet_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nChg_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nChg_ptCut_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nNeutral_ptCutJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pTMaxJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pTMaxChgJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pTMaxNeutralJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         pTMaxChg_QCJet_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_dRMean_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_frac01_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_frac02_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_frac03_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_frac04_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_frac05_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_nNeutrals_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_beta_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_betaStar_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_dZ_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_nCharged_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_dR2Mean_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetId_betaStarClassic_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetIdSimple_mva_pfakt5[95];   //[nJet_pfakt5]
   Int_t           jetIdSimple_wp_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetIdFull_mva_pfakt5[95];   //[nJet_pfakt5]
   Int_t           jetIdFull_wp_pfakt5[95];   //[nJet_pfakt5]
   Float_t         jetIdCutBased_mva_pfakt5[95];   //[nJet_pfakt5]
   Int_t           jetIdCutBased_wp_pfakt5[95];   //[nJet_pfakt5]
   Float_t         beta_pfakt5[100][100];
   Float_t         betaStar_pfakt5[100][100];
   Float_t         combinedSecondaryVertexBJetTags[95];   //[nJet_pfakt5]
   Float_t         combinedSecondaryVertexMVABJetTags[95];   //[nJet_pfakt5]
   Float_t         jetBProbabilityBJetTags[95];   //[nJet_pfakt5]
   Float_t         jetProbabilityBJetTags[95];   //[nJet_pfakt5]
   Float_t         simpleSecondaryVertexHighEffBJetTags[95];   //[nJet_pfakt5]
   Float_t         simpleSecondaryVertexHighPurBJetTags[95];   //[nJet_pfakt5]
   Float_t         softMuonBJetTags[95];   //[nJet_pfakt5]
   Float_t         softMuonByIP3dBJetTags[95];   //[nJet_pfakt5]
   Float_t         softMuonByPtBJetTags[95];   //[nJet_pfakt5]
   Float_t         softElectronByIP3dBJetTags[95];   //[nJet_pfakt5]
   Float_t         softElectronByPtBJetTags[95];   //[nJet_pfakt5]
   Float_t         trackCountingHighPurBJetTags[95];   //[nJet_pfakt5]
   Float_t         trackCountingHighEffBJetTags[95];   //[nJet_pfakt5]
   Int_t           npfcand_all;
   Int_t           nChargedHadrons_uncl;
   Int_t           nChargedHadronsgoodvtx_uncl;
   Int_t           nChargedHadronsnoothervtx_uncl;
   Int_t           nPhotons_uncl;
   Int_t           nMuons_uncl;
   Int_t           nElectrons_uncl;
   Int_t           nNeutralHadrons_uncl;
   Int_t           nHFHadrons_uncl;
   Int_t           nHFEM_uncl;
   Float_t         epfcand_all;
   Float_t         eChargedHadrons_uncl;
   Float_t         eChargedHadronsgoodvtx_uncl;
   Float_t         eChargedHadronsnoothervtx_uncl;
   Float_t         ePhotons_uncl;
   Float_t         eMuons_uncl;
   Float_t         eElectrons_uncl;
   Float_t         eNeutralHadrons_uncl;
   Float_t         eHFHadrons_uncl;
   Float_t         eHFEM_uncl;
   Float_t         ptpfcand_all;
   Float_t         ptChargedHadrons_uncl;
   Float_t         ptChargedHadronsgoodvtx_uncl;
   Float_t         ptChargedHadronsnoothervtx_uncl;
   Float_t         ptPhotons_uncl;
   Float_t         ptMuons_uncl;
   Float_t         ptElectrons_uncl;
   Float_t         ptNeutralHadrons_uncl;
   Float_t         ptHFHadrons_uncl;
   Float_t         ptHFEM_uncl;
   Float_t         ptpfcand_all;
   Float_t         etaChargedHadrons_uncl;
   Float_t         etaChargedHadronsgoodvtx_uncl;
   Float_t         etaChargedHadronsnoothervtx_uncl;
   Float_t         etaPhotons_uncl;
   Float_t         etaMuons_uncl;
   Float_t         etaElectrons_uncl;
   Float_t         etaNeutralHadrons_uncl;
   Float_t         etaHFHadrons_uncl;
   Float_t         etaHFEM_uncl;
   Float_t         ptpfcand_all;
   Float_t         phiChargedHadrons_uncl;
   Float_t         phiChargedHadronsgoodvtx_uncl;
   Float_t         phiChargedHadronsnoothervtx_uncl;
   Float_t         phiPhotons_uncl;
   Float_t         phiMuons_uncl;
   Float_t         phiElectrons_uncl;
   Float_t         phiNeutralHadrons_uncl;
   Float_t         phiHFHadrons_uncl;
   Float_t         phiHFEM_uncl;
   Float_t         sumptpfcand_all;
   Float_t         sumptChargedHadrons_uncl;
   Float_t         sumptChargedHadronsgoodvtx_uncl;
   Float_t         sumptChargedHadronsnoothervtx_uncl;
   Float_t         sumptPhotons_uncl;
   Float_t         sumptMuons_uncl;
   Float_t         sumptElectrons_uncl;
   Float_t         sumptNeutralHadrons_uncl;
   Float_t         sumptHFHadrons_uncl;
   Float_t         sumptHFEM_uncl;
   Float_t         sumptpfcand_all;
   Int_t           nChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nPhotons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nMuons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nElectrons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nHFEM_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ePhotons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eMuons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eElectrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         eHFEM_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptPhotons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptMuons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptElectrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         ptHFEM_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaPhotons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaMuons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaElectrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         etaHFEM_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiPhotons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiMuons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiElectrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         phiHFEM_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptChargedHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptChargedHadronsgoodvtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptChargedHadronsnoothervtx_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptPhotons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptMuons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptElectrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptNeutralHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptHFHadrons_pfakt5[95];   //[nJet_pfakt5]
   Float_t         sumptHFEM_pfakt5[95];   //[nJet_pfakt5]
   Int_t           nJet_pfakt7;
   Float_t         ptJet_pfakt7 [59];   //[nJet_pfakt7]
   Float_t         ptCorrJet_pfakt7 [59];   //[nJet_pfakt7]
   Float_t         eJet_pfakt7  [59];   //[nJet_pfakt7]
   Float_t         etaJet_pfakt7[59];   //[nJet_pfakt7]
   Float_t         phiJet_pfakt7[59];   //[nJet_pfakt7]
   Int_t           nJetGen_akt5;
   Float_t         ptJetGen_akt5 [1];   //[nJetGen_akt5]
   Float_t         eJetGen_akt5  [1];   //[nJetGen_akt5]
   Float_t         etaJetGen_akt5[1];   //[nJetGen_akt5]
   Float_t         phiJetGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nMuonsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nElectronsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nPhotonsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nTracksGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nNeutralHadronsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nHFHadronsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nHFEMGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nNeutronsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nK0LGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nK0SGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nLambdasGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nCsiGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nOtherNeutralHadronsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eMuonsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eElectronsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         ePhotonsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eTracksGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eNeutralHadronsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eHFHadronsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eHFEMGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eNeutronsGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eK0LGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eK0SGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eLambdasGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eCsiGen_akt5[1];   //[nJetGen_akt5]
   Float_t         eOtherNeutralHadronsGen_akt5[1];   //[nJetGen_akt5]
   Int_t           nJetGen_akt7;
   Float_t         ptJetGen_akt7 [1];   //[nJetGen_akt7]
   Float_t         eJetGen_akt7  [1];   //[nJetGen_akt7]
   Float_t         etaJetGen_akt7[1];   //[nJetGen_akt7]
   Float_t         phiJetGen_akt7[1];   //[nJetGen_akt7]
   Int_t           nvertex;
   Float_t         sMet  ;
   Float_t         eMet  ;
   Float_t         phiMet;
   Float_t         signifMet;
   Float_t         sCorrMet  ;
   Float_t         eCorrMet  ;
   Float_t         phiCorrMet;
   Float_t         signifCorrMet;
   Float_t         sNoHFMet  ;
   Float_t         eNoHFMet  ;
   Float_t         phiNoHFMet;
   Float_t         signifNoHFMet;
   Float_t         stcMet;
   Float_t         etcMet;
   Float_t         phitcMet;
   Float_t         signiftcMet;
   Float_t         sglobalPfMet;
   Float_t         eglobalPfMet;
   Float_t         phiglobalPfMet;
   Float_t         signifglobalPfMet;
   Float_t         scentralPfMet;
   Float_t         ecentralPfMet;
   Float_t         phicentralPfMet;
   Float_t         signifcentralPfMet;
   Float_t         eassocPfMet[40];   //[nvertex]
   Float_t         phiassocPfMet[40];   //[nvertex]
   Float_t         signifassocPfMet[40];   //[nvertex]
   Float_t         eassocOtherVtxPfMet[40];   //[nvertex]
   Float_t         phiassocOtherVtxPfMet[40];   //[nvertex]
   Float_t         signifassocOtherVtxPfMet[40];   //[nvertex]
   Float_t         etrkPfMet[40];   //[nvertex]
   Float_t         phitrkPfMet[40];   //[nvertex]
   Float_t         signiftrkPfMet[40];   //[nvertex]
   Float_t         ecleanPfMet[40];   //[nvertex]
   Float_t         phicleanPfMet[40];   //[nvertex]
   Float_t         signifcleanPfMet[40];   //[nvertex]
   Float_t         globalPfSums[12];
   Float_t         spfMet;
   Float_t         epfMet;
   Float_t         phipfMet;
   Float_t         signifpfMet;
   Float_t         spfMetType1;
   Float_t         epfMetType1;
   Float_t         phipfMetType1;
   Float_t         signifpfMetType1;
   Float_t         sMetGen;
   Float_t         eMetGen;
   Float_t         phiMetGen;
   Float_t         signifMetGen;
   Float_t         sMetGen2;
   Float_t         eMetGen2;
   Float_t         phiMetGen2;
   Float_t         vxMC;
   Float_t         vyMC;
   Float_t         vzMC;
   Float_t         vx[40];   //[nvertex]
   Float_t         vy[40];   //[nvertex]
   Float_t         vz[40];   //[nvertex]
   Float_t         vntracks[40];   //[nvertex]
   Float_t         vchi2[40];   //[nvertex]
   Float_t         vndof[40];   //[nvertex]
   Float_t         vlogsumpt2[40];   //[nvertex]
   Int_t           nPreselPhotonPairs;
   Int_t           indexPreselPhot1[3];   //[nPreselPhotonPairs]
   Int_t           indexPreselPhot2[3];   //[nPreselPhotonPairs]
   Int_t           vrankPhotonPairs[3];   //[nPreselPhotonPairs]
   Float_t         vevtMvaPhotonPairs[3];   //[nPreselPhotonPairs]
   Float_t         vevtProbPhotonPairs[3];   //[nPreselPhotonPairs]
   Float_t         vptbalPhotonPairs[3];   //[nPreselPhotonPairs]
   Float_t         vptasymPhotonPairs[3];   //[nPreselPhotonPairs]
   Int_t           nHLT;
   Int_t           hltNamesLen;
   vector<string>  *HLTNames;
   vector<bool>    *HLTResults;
   Int_t           trg17_SC_ele_n;
   Float_t         trg17_SC_ele_eta[8];   //[ElectronRefs0_n]
   Float_t         trg17_SC_ele_et[8];   //[ElectronRefs0_n]
   Float_t         trg17_SC_ele_phi[8];   //[ElectronRefs0_n]
   Int_t           trg32_ele_n;
   Float_t         trg32_ele_eta[8];   //[ElectronRefs1_n]
   Float_t         trg32_ele_et[8];   //[ElectronRefs1_n]
   Float_t         trg32_ele_phi[8];   //[ElectronRefs1_n]
   Int_t           trg8_ele_n;
   Float_t         trg8_ele_eta[8];   //[ElectronRefs2_n]
   Float_t         trg8_ele_et[8];   //[ElectronRefs2_n]
   Float_t         trg8_ele_phi[8];   //[ElectronRefs2_n]
   Int_t           trg17_ele_n;
   Float_t         trg17_ele_eta[8];   //[ElectronRefs3_n]
   Float_t         trg17_ele_et[8];   //[ElectronRefs3_n]
   Float_t         trg17_ele_phi[8];   //[ElectronRefs3_n]
   Int_t           trg8_mass50_ele_n;
   Float_t         trg8_mass50_ele_eta[8];   //[ElectronRefs4_n]
   Float_t         trg8_mass50_ele_et[8];   //[ElectronRefs4_n]
   Float_t         trg8_mass50_ele_phi[8];   //[ElectronRefs4_n]
   Int_t           trg17_mass50_ele_n;
   Float_t         trg17_mass50_ele_eta[8];   //[ElectronRefs5_n]
   Float_t         trg17_mass50_ele_et[8];   //[ElectronRefs5_n]
   Float_t         trg17_mass50_ele_phi[8];   //[ElectronRefs5_n]
   Int_t           trg4_mass50_SC_n;
   Float_t         trg4_mass50_SC_eta[8];   //[ElectronRefs6_n]
   Float_t         trg4_mass50_SC_et[8];   //[ElectronRefs6_n]
   Float_t         trg4_mass50_SC_phi[8];   //[ElectronRefs6_n]
   Int_t           trg20_mass50_ele_n;
   Float_t         trg20_mass50_ele_eta[4];   //[ElectronRefs7_n]
   Float_t         trg20_mass50_ele_et[4];   //[ElectronRefs7_n]
   Float_t         trg20_mass50_ele_phi[4];   //[ElectronRefs7_n]
   Int_t           trg20_phoIDCaloVL_n;
   Float_t         trg20_phoIDCaloVL_eta[1];   //[PhotonRefs0_n]
   Float_t         trg20_phoIDCaloVL_et[1];   //[PhotonRefs0_n]
   Float_t         trg20_phoIDCaloVL_phi[1];   //[PhotonRefs0_n]
   Int_t           trg30_phoIDCaloVL_n;
   Float_t         trg30_phoIDCaloVL_eta[2];   //[PhotonRefs1_n]
   Float_t         trg30_phoIDCaloVL_et[2];   //[PhotonRefs1_n]
   Float_t         trg30_phoIDCaloVL_phi[2];   //[PhotonRefs1_n]
   Int_t           trg50_phoIDCaloVL_n;
   Float_t         trg50_phoIDCaloVL_eta[2];   //[PhotonRefs2_n]
   Float_t         trg50_phoIDCaloVL_et[2];   //[PhotonRefs2_n]
   Float_t         trg50_phoIDCaloVL_phi[2];   //[PhotonRefs2_n]
   Int_t           trg75_phoIDCaloVL_n;
   Float_t         trg75_phoIDCaloVL_eta[2];   //[PhotonRefs3_n]
   Float_t         trg75_phoIDCaloVL_et[2];   //[PhotonRefs3_n]
   Float_t         trg75_phoIDCaloVL_phi[2];   //[PhotonRefs3_n]
   Int_t           trg90_phoIDCaloVL_n;
   Float_t         trg90_phoIDCaloVL_eta[2];   //[PhotonRefs4_n]
   Float_t         trg90_phoIDCaloVL_et[2];   //[PhotonRefs4_n]
   Float_t         trg90_phoIDCaloVL_phi[2];   //[PhotonRefs4_n]
   Int_t           nEle;
   Float_t         electron_px[6];   //[nEle]
   Float_t         electron_py[6];   //[nEle]
   Float_t         electron_pz[6];   //[nEle]
   Float_t         electron_vx[6];   //[nEle]
   Float_t         electron_vy[6];   //[nEle]
   Float_t         electron_vz[6];   //[nEle]
   Float_t         electron_pt[6];   //[nEle]
   Float_t         electron_eta[6];   //[nEle]
   Float_t         electron_phi[6];   //[nEle]
   Float_t         electron_energy[6];   //[nEle]
   Float_t         electron_ecalEnergy[6];   //[nEle]
   Float_t         electron_trackPatVtx[6];   //[nEle]
   Float_t         electron_charge[6];   //[nEle]
   Float_t         electron_fBrem[6];   //[nEle]
   Float_t         electron_dist[6];   //[nEle]
   Float_t         electron_dcot[6];   //[nEle]
   Int_t           electron_misHits[6];   //[nEle]
   Int_t           electron_matchedConv[6];   //[nEle]
   Int_t           electron_seedType[6];   //[nEle]
   Float_t         electron_EoP[6];   //[nEle]
   Float_t         electron_OneOverEMinusOneOverP[6];   //[nEle]
   Float_t         electron_r9[6];   //[nEle]
   Int_t           electron_nSubClusters[6];   //[nEle]
   Float_t         electron_trkIso[6];   //[nEle]
   Float_t         electron_ecalIso[6];   //[nEle]
   Float_t         electron_hcalIso[6];   //[nEle]
   Float_t         electron_trkIso03[6];   //[nEle]
   Float_t         electron_ecalIso03[6];   //[nEle]
   Float_t         electron_hcalIso03[6];   //[nEle]
   Float_t         electron_SigmaIetaIeta[6];   //[nEle]
   Float_t         electron_SigmaIphiIphi[6];   //[nEle]
   Float_t         electron_dEtaIn[6];   //[nEle]
   Float_t         electron_dPhiIn[6];   //[nEle]
   Float_t         electron_HoE[6];   //[nEle]
   Float_t         electron_pFlowMVA[6];   //[nEle]
   Float_t         electron_sc_energy[6];   //[nEle]
   Float_t         electron_sc_eta[6];   //[nEle]
   Float_t         electron_sc_phi[6];   //[nEle]
   Float_t         electron_mvaNonTrig[6];   //[nEle]
   Float_t         electron_mvaTrig[6];   //[nEle]
   Float_t         electron_chHad03Iso[6];   //[nEle]
   Float_t         electron_nHad03Iso[6];   //[nEle]
   Float_t         electron_phot03Iso[6];   //[nEle]
   Float_t         electron_chHad04Iso[6];   //[nEle]
   Float_t         electron_nHad04Iso[6];   //[nEle]
   Float_t         electron_phot04Iso[6];   //[nEle]
   Float_t         electron_chHad05Iso[6];   //[nEle]
   Float_t         electron_nHad05Iso[6];   //[nEle]
   Float_t         electron_phot05Iso[6];   //[nEle]
   Bool_t          isBeamHaloGlobalLoosePass;
   Bool_t          isBeamHaloGlobalTightPass;
   Bool_t          isBeamHaloHcalLoosePass;
   Bool_t          isBeamHaloHcalTightPass;
   Bool_t          isBeamHaloCSCLoosePass;
   Bool_t          isBeamHaloCSCTightPass;
   Bool_t          isBeamHaloEcalLoosePass;
   Bool_t          isBeamHaloEcalTightPass;
   Bool_t          isBeamHaloIDTightPass;
   Bool_t          isBeamHaloIDLoosePass;
   Bool_t          isSmellsLikeHalo_Tag;
   Bool_t          isLooseHalo_Tag;
   Bool_t          isTightHalo_Tag;
   Bool_t          isExtremeTightHalo_Tag;
   Int_t           nMuons;
   Float_t         Muon_px[25];   //[nMuons]
   Float_t         Muon_py[25];   //[nMuons]
   Float_t         Muon_pz[25];   //[nMuons]
   Float_t         Muon_vx[25];   //[nMuons]
   Float_t         Muon_vy[25];   //[nMuons]
   Float_t         Muon_vz[25];   //[nMuons]
   Float_t         Muon_pt[25];   //[nMuons]
   Float_t         Muon_eta[25];   //[nMuons]
   Float_t         Muon_phi[25];   //[nMuons]
   Float_t         Muon_energy[25];   //[nMuons]
   Float_t         Muon_charge[25];   //[nMuons]
   Bool_t          Muon_isGlobalMuon[25];   //[nMuons]
   Bool_t          Muon_isTrackerMuon[25];   //[nMuons]
   Bool_t          Muon_isStandAloneMuon[25];   //[nMuons]
   Int_t           Muon_trkLayerWithMeas[25];   //[nMuons]
   Bool_t          Muon_InnerTrack_isNonnull[25];   //[nMuons]
   Bool_t          Muon_OuterTrack_isNonnull[25];   //[nMuons]
   Float_t         Muon_OuterPoint_x[25];   //[nMuons]
   Float_t         Muon_OuterPoint_y[25];   //[nMuons]
   Float_t         Muon_OuterPoint_z[25];   //[nMuons]
   Bool_t          Muon_isPFMuon[25];   //[nMuons]
   Float_t         Muon_pfiso04_chHad[25];   //[nMuons]
   Float_t         Muon_pfiso04_chPar[25];   //[nMuons]
   Float_t         Muon_pfiso04_nHad[25];   //[nMuons]
   Float_t         Muon_pfiso04_Phot[25];   //[nMuons]
   Float_t         Muon_pfiso04_PUPt[25];   //[nMuons]
   Float_t         Muon_pfiso03_chHad[25];   //[nMuons]
   Float_t         Muon_pfiso03_chPar[25];   //[nMuons]
   Float_t         Muon_pfiso03_nHad[25];   //[nMuons]
   Float_t         Muon_pfiso03_Phot[25];   //[nMuons]
   Float_t         Muon_pfiso03_PUPt[25];   //[nMuons]
   Float_t         Muon_InnerPoint_x[25];   //[nMuons]
   Float_t         Muon_InnerPoint_y[25];   //[nMuons]
   Float_t         Muon_InnerPoint_z[25];   //[nMuons]
   Float_t         Muon_trackIso[25];   //[nMuons]
   Float_t         Muon_ecalIso[25];   //[nMuons]
   Float_t         Muon_hcalIso[25];   //[nMuons]
   Float_t         Muon_relIso[25];   //[nMuons]
   Int_t           Muon_normChi2[25];   //[nMuons]
   Int_t           Muon_validHits[25];   //[nMuons]
   Int_t           Muon_tkHits[25];   //[nMuons]
   Int_t           Muon_pixHits[25];   //[nMuons]
   Int_t           Muon_numberOfMatches[25];   //[nMuons]
   Int_t           nCosmicMuons;
   Float_t         CosmicMuon_px[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_py[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_pz[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_pt[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_eta[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_phi[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_energy[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_charge[30];   //[nCosmicMuons]
   Bool_t          CosmicMuon_isGlobalMuon[30];   //[nCosmicMuons]
   Bool_t          CosmicMuon_isTrackerMuon[30];   //[nCosmicMuons]
   Bool_t          CosmicMuon_isStandAloneMuon[30];   //[nCosmicMuons]
   Bool_t          CosmicMuon_InnerTrack_isNonnull[30];   //[nCosmicMuons]
   Bool_t          CosmicMuon_OuterTrack_isNonnull[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_OuterPoint_x[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_OuterPoint_y[30];   //[nCosmicMuons]
   Float_t         CosmicMuon_OuterPoint_z[30];   //[nCosmicMuons]
   Double_t        Xsec;

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
   TBranch        *b_isoParticleChargedDR01MC;   //!
   TBranch        *b_isoParticleChargedDR02MC;   //!
   TBranch        *b_isoParticleChargedDR03MC;   //!
   TBranch        *b_isoParticleChargedDR04MC;   //!
   TBranch        *b_isoParticleChargedDR05MC;   //!
   TBranch        *b_isoParticleEMNeutralDR01MC;   //!
   TBranch        *b_isoParticleEMNeutralDR02MC;   //!
   TBranch        *b_isoParticleEMNeutralDR03MC;   //!
   TBranch        *b_isoParticleEMNeutralDR04MC;   //!
   TBranch        *b_isoParticleEMNeutralDR05MC;   //!
   TBranch        *b_isoParticleHADNeutralDR01MC;   //!
   TBranch        *b_isoParticleHADNeutralDR02MC;   //!
   TBranch        *b_isoParticleHADNeutralDR03MC;   //!
   TBranch        *b_isoParticleHADNeutralDR04MC;   //!
   TBranch        *b_isoParticleHADNeutralDR05MC;   //!
   TBranch        *b_isoPartonDR01MC;   //!
   TBranch        *b_isoPartonDR02MC;   //!
   TBranch        *b_isoPartonDR03MC;   //!
   TBranch        *b_isoPartonDR04MC;   //!
   TBranch        *b_isoPartonDR05MC;   //!
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
   TBranch        *b_rmsCandTrue_QCJet_pfakt5;   //!
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
   TBranch        *b_ptpfcand_all;   //!
   TBranch        *b_ptChargedHadrons_uncl;   //!
   TBranch        *b_ptChargedHadronsgoodvtx_uncl;   //!
   TBranch        *b_ptChargedHadronsnoothervtx_uncl;   //!
   TBranch        *b_ptPhotons_uncl;   //!
   TBranch        *b_ptMuons_uncl;   //!
   TBranch        *b_ptElectrons_uncl;   //!
   TBranch        *b_ptNeutralHadrons_uncl;   //!
   TBranch        *b_ptHFHadrons_uncl;   //!
   TBranch        *b_ptHFEM_uncl;   //!
   TBranch        *b_ptpfcand_all;   //!
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
   TBranch        *b_sumptpfcand_all;   //!
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
   TBranch        *b_ElectronRefs0_n;   //!
   TBranch        *b_trg17_SC_ele_eta;   //!
   TBranch        *b_trg17_SC_ele_et;   //!
   TBranch        *b_trg17_SC_ele_phi;   //!
   TBranch        *b_ElectronRefs1_n;   //!
   TBranch        *b_trg32_ele_eta;   //!
   TBranch        *b_trg32_ele_et;   //!
   TBranch        *b_trg32_ele_phi;   //!
   TBranch        *b_ElectronRefs2_n;   //!
   TBranch        *b_trg8_ele_eta;   //!
   TBranch        *b_trg8_ele_et;   //!
   TBranch        *b_trg8_ele_phi;   //!
   TBranch        *b_ElectronRefs3_n;   //!
   TBranch        *b_trg17_ele_eta;   //!
   TBranch        *b_trg17_ele_et;   //!
   TBranch        *b_trg17_ele_phi;   //!
   TBranch        *b_ElectronRefs4_n;   //!
   TBranch        *b_trg8_mass50_ele_eta;   //!
   TBranch        *b_trg8_mass50_ele_et;   //!
   TBranch        *b_trg8_mass50_ele_phi;   //!
   TBranch        *b_ElectronRefs5_n;   //!
   TBranch        *b_trg17_mass50_ele_eta;   //!
   TBranch        *b_trg17_mass50_ele_et;   //!
   TBranch        *b_trg17_mass50_ele_phi;   //!
   TBranch        *b_ElectronRefs6_n;   //!
   TBranch        *b_trg4_mass50_SC_eta;   //!
   TBranch        *b_trg4_mass50_SC_et;   //!
   TBranch        *b_trg4_mass50_SC_phi;   //!
   TBranch        *b_ElectronRefs7_n;   //!
   TBranch        *b_trg20_mass50_ele_eta;   //!
   TBranch        *b_trg20_mass50_ele_et;   //!
   TBranch        *b_trg20_mass50_ele_phi;   //!
   TBranch        *b_PhotonRefs0_n;   //!
   TBranch        *b_trg20_phoIDCaloVL_eta;   //!
   TBranch        *b_trg20_phoIDCaloVL_et;   //!
   TBranch        *b_trg20_phoIDCaloVL_phi;   //!
   TBranch        *b_PhotonRefs1_n;   //!
   TBranch        *b_trg30_phoIDCaloVL_eta;   //!
   TBranch        *b_trg30_phoIDCaloVL_et;   //!
   TBranch        *b_trg30_phoIDCaloVL_phi;   //!
   TBranch        *b_PhotonRefs2_n;   //!
   TBranch        *b_trg50_phoIDCaloVL_eta;   //!
   TBranch        *b_trg50_phoIDCaloVL_et;   //!
   TBranch        *b_trg50_phoIDCaloVL_phi;   //!
   TBranch        *b_PhotonRefs3_n;   //!
   TBranch        *b_trg75_phoIDCaloVL_eta;   //!
   TBranch        *b_trg75_phoIDCaloVL_et;   //!
   TBranch        *b_trg75_phoIDCaloVL_phi;   //!
   TBranch        *b_PhotonRefs4_n;   //!
   TBranch        *b_trg90_phoIDCaloVL_eta;   //!
   TBranch        *b_trg90_phoIDCaloVL_et;   //!
   TBranch        *b_trg90_phoIDCaloVL_phi;   //!
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

   tree_reader_v9(TTree *tree=0);
   virtual ~tree_reader_v9();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_reader_v9_cxx
tree_reader_v9::tree_reader_v9(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://cmseos.fnal.gov//eos/uscms/store/user/meridian/data/53xv4/Photon_Run2012A-22Jan2013-v1/output_91_5_8qO.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://cmseos.fnal.gov//eos/uscms/store/user/meridian/data/53xv4/Photon_Run2012A-22Jan2013-v1/output_91_5_8qO.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://cmseos.fnal.gov//eos/uscms/store/user/meridian/data/53xv4/Photon_Run2012A-22Jan2013-v1/output_91_5_8qO.root:/myanalysis");
      dir->GetObject("pippo",tree);

   }
   Init(tree);
}

tree_reader_v9::~tree_reader_v9()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree_reader_v9::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree_reader_v9::LoadTree(Long64_t entry)
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

void tree_reader_v9::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   HLTNames = 0;
   HLTResults = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("genpt", &genpt, &b_genpt);
   fChain->SetBranchAddress("genProcessId", &genProcessId, &b_genProcessId);
   fChain->SetBranchAddress("genQScale", &genQScale, &b_genQScale);
   fChain->SetBranchAddress("isMC", &isMC, &b_isMC);
   fChain->SetBranchAddress("passEcalLaserFilter", &passEcalLaserFilter, &b_passEcalLaserFilter);
   fChain->SetBranchAddress("passHBHENoiseFilter", &passHBHENoiseFilter, &b_passHBHENoiseFilter);
   fChain->SetBranchAddress("passCSCTightHaloFilter", &passCSCTightHaloFilter, &b_passCSCTightHaloFilter);
   fChain->SetBranchAddress("passhcalLaserEventFilter", &passhcalLaserEventFilter, &b_passhcalLaserEventFilter);
   fChain->SetBranchAddress("passEcalDeadCellTriggerPrimitiveFilter", &passEcalDeadCellTriggerPrimitiveFilter, &b_passEcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("passtrackingFailureFilter", &passtrackingFailureFilter, &b_passtrackingFailureFilter);
   fChain->SetBranchAddress("passeeBadScFilter", &passeeBadScFilter, &b_passeeBadScFilter);
   fChain->SetBranchAddress("store", &store, &b_store);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("orbit", &orbit, &b_orbit);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("rhoPF", &rhoPF, &b_rhoPF);
   fChain->SetBranchAddress("rhoCalo", &rhoCalo, &b_rhoCalo);
   fChain->SetBranchAddress("rhoAllJets", &rhoAllJets, &b_rhoAllJets);
   fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
   fChain->SetBranchAddress("pdgIdMC", &pdgIdMC, &b_pdgIdMC);
   fChain->SetBranchAddress("statusMC", &statusMC, &b_statusMC);
   fChain->SetBranchAddress("motherIDMC", &motherIDMC, &b_motherIDMC);
   fChain->SetBranchAddress("ptMC ", &ptMC , &b_ptMC );
   fChain->SetBranchAddress("eMC  ", &eMC  , &b_eMC  );
   fChain->SetBranchAddress("etaMC", &etaMC, &b_etaMC);
   fChain->SetBranchAddress("phiMC", &phiMC, &b_phiMC);
   fChain->SetBranchAddress("isoParticleChargedDR01MC", &isoParticleChargedDR01MC, &b_isoParticleChargedDR01MC);
   fChain->SetBranchAddress("isoParticleChargedDR02MC", &isoParticleChargedDR02MC, &b_isoParticleChargedDR02MC);
   fChain->SetBranchAddress("isoParticleChargedDR03MC", &isoParticleChargedDR03MC, &b_isoParticleChargedDR03MC);
   fChain->SetBranchAddress("isoParticleChargedDR04MC", &isoParticleChargedDR04MC, &b_isoParticleChargedDR04MC);
   fChain->SetBranchAddress("isoParticleChargedDR05MC", &isoParticleChargedDR05MC, &b_isoParticleChargedDR05MC);
   fChain->SetBranchAddress("isoParticleEMNeutralDR01MC", &isoParticleEMNeutralDR01MC, &b_isoParticleEMNeutralDR01MC);
   fChain->SetBranchAddress("isoParticleEMNeutralDR02MC", &isoParticleEMNeutralDR02MC, &b_isoParticleEMNeutralDR02MC);
   fChain->SetBranchAddress("isoParticleEMNeutralDR03MC", &isoParticleEMNeutralDR03MC, &b_isoParticleEMNeutralDR03MC);
   fChain->SetBranchAddress("isoParticleEMNeutralDR04MC", &isoParticleEMNeutralDR04MC, &b_isoParticleEMNeutralDR04MC);
   fChain->SetBranchAddress("isoParticleEMNeutralDR05MC", &isoParticleEMNeutralDR05MC, &b_isoParticleEMNeutralDR05MC);
   fChain->SetBranchAddress("isoParticleHADNeutralDR01MC", &isoParticleHADNeutralDR01MC, &b_isoParticleHADNeutralDR01MC);
   fChain->SetBranchAddress("isoParticleHADNeutralDR02MC", &isoParticleHADNeutralDR02MC, &b_isoParticleHADNeutralDR02MC);
   fChain->SetBranchAddress("isoParticleHADNeutralDR03MC", &isoParticleHADNeutralDR03MC, &b_isoParticleHADNeutralDR03MC);
   fChain->SetBranchAddress("isoParticleHADNeutralDR04MC", &isoParticleHADNeutralDR04MC, &b_isoParticleHADNeutralDR04MC);
   fChain->SetBranchAddress("isoParticleHADNeutralDR05MC", &isoParticleHADNeutralDR05MC, &b_isoParticleHADNeutralDR05MC);
   fChain->SetBranchAddress("isoPartonDR01MC", &isoPartonDR01MC, &b_isoPartonDR01MC);
   fChain->SetBranchAddress("isoPartonDR02MC", &isoPartonDR02MC, &b_isoPartonDR02MC);
   fChain->SetBranchAddress("isoPartonDR03MC", &isoPartonDR03MC, &b_isoPartonDR03MC);
   fChain->SetBranchAddress("isoPartonDR04MC", &isoPartonDR04MC, &b_isoPartonDR04MC);
   fChain->SetBranchAddress("isoPartonDR05MC", &isoPartonDR05MC, &b_isoPartonDR05MC);
   fChain->SetBranchAddress("pu_n", &pu_n, &b_pu_n);
   fChain->SetBranchAddress("pu_true_n", &pu_true_n, &b_pu_true_n);
   fChain->SetBranchAddress("pu_zpos", &pu_zpos, &b_pu_zpos);
   fChain->SetBranchAddress("pu_sumpt_lowpt", &pu_sumpt_lowpt, &b_pu_sumpt_lowpt);
   fChain->SetBranchAddress("pu_sumpt_highpt", &pu_sumpt_highpt, &b_pu_sumpt_highpt);
   fChain->SetBranchAddress("pu_ntrks_lowpt", &pu_ntrks_lowpt, &b_pu_ntrks_lowpt);
   fChain->SetBranchAddress("pu_ntrks_highpt", &pu_ntrks_highpt, &b_pu_ntrks_highpt);
   fChain->SetBranchAddress("nPhot", &nPhot, &b_nPhot);
   fChain->SetBranchAddress("ptPhot ", ptPhot , &b_ptPhot );
   fChain->SetBranchAddress("ePhot  ", ePhot  , &b_ePhot  );
   fChain->SetBranchAddress("escPhot  ", escPhot  , &b_escPhot  );
   fChain->SetBranchAddress("escRegrPhot  ", escRegrPhot  , &b_escRegrPhot  );
   fChain->SetBranchAddress("escRegrPhotError  ", escRegrPhotError  , &b_escRegrPhotError  );
   fChain->SetBranchAddress("escPhFixPhot  ", escPhFixPhot  , &b_escPhFixPhot  );
   fChain->SetBranchAddress("escPhFixPhotError  ", escPhFixPhotError  , &b_escPhFixPhotError  );
   fChain->SetBranchAddress("escRawPhot  ", escRawPhot  , &b_escRawPhot  );
   fChain->SetBranchAddress("etascPhot  ", etascPhot  , &b_etascPhot  );
   fChain->SetBranchAddress("phiscPhot  ", phiscPhot  , &b_phiscPhot  );
   fChain->SetBranchAddress("xscPhot  ", xscPhot  , &b_xscPhot  );
   fChain->SetBranchAddress("yscPhot  ", yscPhot  , &b_yscPhot  );
   fChain->SetBranchAddress("zscPhot  ", zscPhot  , &b_zscPhot  );
   fChain->SetBranchAddress("xcaloPhot  ", xcaloPhot  , &b_xcaloPhot  );
   fChain->SetBranchAddress("ycaloPhot  ", ycaloPhot  , &b_ycaloPhot  );
   fChain->SetBranchAddress("zcaloPhot  ", zcaloPhot  , &b_zcaloPhot  );
   fChain->SetBranchAddress("eseedPhot  ", eseedPhot  , &b_eseedPhot  );
   fChain->SetBranchAddress("etaPhot", etaPhot, &b_etaPhot);
   fChain->SetBranchAddress("phiPhot", phiPhot, &b_phiPhot);
   fChain->SetBranchAddress("timePhot", timePhot, &b_timePhot);
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
   fChain->SetBranchAddress("pid_hlwTrackForCiC", pid_hlwTrackForCiC, &b_pid_hlwTrackBestRank);
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
   fChain->SetBranchAddress("nElePhot", &nElePhot, &b_nElePhot);
   fChain->SetBranchAddress("pid_jurECALElePhot ", pid_jurECALElePhot , &b_pid_jurECALElePhot );
   fChain->SetBranchAddress("pid_twrHCALElePhot ", pid_twrHCALElePhot , &b_pid_twrHCALElePhot );
   fChain->SetBranchAddress("pid_HoverEElePhot ", pid_HoverEElePhot , &b_pid_HoverEElePhot );
   fChain->SetBranchAddress("pid_hlwTrackElePhot ", pid_hlwTrackElePhot , &b_pid_hlwTrackElePhot );
   fChain->SetBranchAddress("pid_etawidElePhot ", pid_etawidElePhot , &b_pid_etawidElePhot );
   fChain->SetBranchAddress("pid_dphivtxElePhot ", pid_dphivtxElePhot , &b_pid_dphivtxElePhot );
   fChain->SetBranchAddress("pid_detavtxElePhot ", pid_detavtxElePhot , &b_pid_detavtxElePhot );
   fChain->SetBranchAddress("pid_mishitsElePhot ", pid_mishitsElePhot , &b_pid_mishitsElePhot );
   fChain->SetBranchAddress("pid_distElePhot ", pid_distElePhot , &b_pid_distElePhot );
   fChain->SetBranchAddress("pid_dcotElePhot ", pid_dcotElePhot , &b_pid_dcotElePhot );
   fChain->SetBranchAddress("pid_ptElePhot ", pid_ptElePhot , &b_pid_ptElePhot );
   fChain->SetBranchAddress("nJet_akt5", &nJet_akt5, &b_nJet_akt5);
   fChain->SetBranchAddress("ptJet_akt5 ", ptJet_akt5 , &b_ptJet_akt5 );
   fChain->SetBranchAddress("ptCorrJet_akt5 ", ptCorrJet_akt5 , &b_ptCorrJet_akt5 );
   fChain->SetBranchAddress("eJet_akt5  ", eJet_akt5  , &b_eJet_akt5  );
   fChain->SetBranchAddress("etaJet_akt5", etaJet_akt5, &b_etaJet_akt5);
   fChain->SetBranchAddress("phiJet_akt5", phiJet_akt5, &b_phiJet_akt5);
   fChain->SetBranchAddress("emfJet_akt5", emfJet_akt5, &b_emfJet_akt5);
   fChain->SetBranchAddress("n90Jet_akt5", n90Jet_akt5, &b_n90Jet_akt5);
   fChain->SetBranchAddress("n90HitsJet_akt5", n90HitsJet_akt5, &b_n90HitsJet_akt5);
   fChain->SetBranchAddress("fHPDJet_akt5", fHPDJet_akt5, &b_fHPDJet_akt5);
   fChain->SetBranchAddress("fRBXJet_akt5", fRBXJet_akt5, &b_fRBXJet_akt5);
   fChain->SetBranchAddress("nJet_akt7", &nJet_akt7, &b_nJet_akt7);
   fChain->SetBranchAddress("ptJet_akt7 ", ptJet_akt7 , &b_ptJet_akt7 );
   fChain->SetBranchAddress("ptCorrJet_akt7 ", ptCorrJet_akt7 , &b_ptCorrJet_akt7 );
   fChain->SetBranchAddress("eJet_akt7  ", eJet_akt7  , &b_eJet_akt7  );
   fChain->SetBranchAddress("etaJet_akt7", etaJet_akt7, &b_etaJet_akt7);
   fChain->SetBranchAddress("phiJet_akt7", phiJet_akt7, &b_phiJet_akt7);
   fChain->SetBranchAddress("emfJet_akt7", emfJet_akt7, &b_emfJet_akt7);
   fChain->SetBranchAddress("n90Jet_akt7", n90Jet_akt7, &b_n90Jet_akt7);
   fChain->SetBranchAddress("n90HitsJet_akt7", n90HitsJet_akt7, &b_n90HitsJet_akt7);
   fChain->SetBranchAddress("fHPDJet_akt7", fHPDJet_akt7, &b_fHPDJet_akt7);
   fChain->SetBranchAddress("fRBXJet_akt7", fRBXJet_akt7, &b_fRBXJet_akt7);
   fChain->SetBranchAddress("nJet_pfakt5", &nJet_pfakt5, &b_nJet_pfakt5);
   fChain->SetBranchAddress("ptJet_pfakt5 ", ptJet_pfakt5 , &b_ptJet_pfakt5 );
   fChain->SetBranchAddress("ptCorrJet_pfakt5 ", ptCorrJet_pfakt5 , &b_ptCorrJet_pfakt5 );
   fChain->SetBranchAddress("eJet_pfakt5  ", eJet_pfakt5  , &b_eJet_pfakt5  );
   fChain->SetBranchAddress("etaJet_pfakt5", etaJet_pfakt5, &b_etaJet_pfakt5);
   fChain->SetBranchAddress("phiJet_pfakt5", phiJet_pfakt5, &b_phiJet_pfakt5);
   fChain->SetBranchAddress("ptDJet_pfakt5", ptDJet_pfakt5, &b_ptDJet_pfakt5);
   fChain->SetBranchAddress("rmsCandJet_pfakt5", rmsCandJet_pfakt5, &b_rmsCandJet_pfakt5);
   fChain->SetBranchAddress("rmsCandTrueJet_pfakt5", rmsCandTrueJet_pfakt5, &b_rmsCandTrueJet_pfakt5);
   fChain->SetBranchAddress("rmsCandTrue_QCJet_pfakt5", rmsCandTrue_QCJet_pfakt5, &b_rmsCandTrue_QCJet_pfakt5);
   fChain->SetBranchAddress("axis1Jet_pfakt5", axis1Jet_pfakt5, &b_axis1Jet_pfakt5);
   fChain->SetBranchAddress("axis2Jet_pfakt5", axis2Jet_pfakt5, &b_axis2Jet_pfakt5);
   fChain->SetBranchAddress("pullJet_pfakt5", pullJet_pfakt5, &b_pullJet_pfakt5);
   fChain->SetBranchAddress("tanaJet_pfakt5", tanaJet_pfakt5, &b_tanaJet_pfakt5);
   fChain->SetBranchAddress("ptD_QCJet_pfakt5", ptD_QCJet_pfakt5, &b_ptD_QCJet_pfakt5);
//    fChain->SetBranchAddress("rmsCandTrue_QCJet_pfakt5", rmsCandTrue_QCJet_pfakt5, &b_rmsCandTrue_QCJet_pfakt5);
   fChain->SetBranchAddress("axis1_QCJet_pfakt5", axis1_QCJet_pfakt5, &b_axis1_QCJet_pfakt5);
   fChain->SetBranchAddress("axis2_QCJet_pfakt5", axis2_QCJet_pfakt5, &b_axis2_QCJet_pfakt5);
   fChain->SetBranchAddress("pull_QCJet_pfakt5", pull_QCJet_pfakt5, &b_pull_QCJet_pfakt5);
   fChain->SetBranchAddress("tana_QCJet_pfakt5", tana_QCJet_pfakt5, &b_tana_QCJet_pfakt5);
   fChain->SetBranchAddress("RchgJet_pfakt5", RchgJet_pfakt5, &b_RchgJet_pfakt5);
   fChain->SetBranchAddress("RneutralJet_pfakt5", RneutralJet_pfakt5, &b_RneutralJet_pfakt5);
   fChain->SetBranchAddress("RJet_pfakt5", RJet_pfakt5, &b_RJet_pfakt5);
   fChain->SetBranchAddress("Rchg_QCJet_pfakt5", Rchg_QCJet_pfakt5, &b_Rchg_QCJet_pfakt5);
   fChain->SetBranchAddress("nChg_ptCutJet_pfakt5", nChg_ptCutJet_pfakt5, &b_nChg_ptCutJet_pfakt5);
   fChain->SetBranchAddress("nChg_QCJet_pfakt5", nChg_QCJet_pfakt5, &b_nChg_QCJet_pfakt5);
   fChain->SetBranchAddress("nChg_ptCut_QCJet_pfakt5", nChg_ptCut_QCJet_pfakt5, &b_nChg_ptCut_QCJet_pfakt5);
   fChain->SetBranchAddress("nNeutral_ptCutJet_pfakt5", nNeutral_ptCutJet_pfakt5, &b_nNeutral_ptCutJet_pfakt5);
   fChain->SetBranchAddress("pTMaxJet_pfakt5", pTMaxJet_pfakt5, &b_pTMaxJet_pfakt5);
   fChain->SetBranchAddress("pTMaxChgJet_pfakt5", pTMaxChgJet_pfakt5, &b_pTMaxChgJet_pfakt5);
   fChain->SetBranchAddress("pTMaxNeutralJet_pfakt5", pTMaxNeutralJet_pfakt5, &b_pTMaxNeutralJet_pfakt5);
   fChain->SetBranchAddress("pTMaxChg_QCJet_pfakt5", pTMaxChg_QCJet_pfakt5, &b_pTMaxChg_QCJet_pfakt5);
   fChain->SetBranchAddress("jetId_dRMean_pfakt5", jetId_dRMean_pfakt5, &b_jetId_dRMean_pfakt5);
   fChain->SetBranchAddress("jetId_frac01_pfakt5", jetId_frac01_pfakt5, &b_jetId_frac01_pfakt5);
   fChain->SetBranchAddress("jetId_frac02_pfakt5", jetId_frac02_pfakt5, &b_jetId_frac02_pfakt5);
   fChain->SetBranchAddress("jetId_frac03_pfakt5", jetId_frac03_pfakt5, &b_jetId_frac03_pfakt5);
   fChain->SetBranchAddress("jetId_frac04_pfakt5", jetId_frac04_pfakt5, &b_jetId_frac04_pfakt5);
   fChain->SetBranchAddress("jetId_frac05_pfakt5", jetId_frac05_pfakt5, &b_jetId_frac05_pfakt5);
   fChain->SetBranchAddress("jetId_nNeutrals_pfakt5", jetId_nNeutrals_pfakt5, &b_jetId_nNeutrals_pfakt5);
   fChain->SetBranchAddress("jetId_beta_pfakt5", jetId_beta_pfakt5, &b_jetId_beta_pfakt5);
   fChain->SetBranchAddress("jetId_betaStar_pfakt5", jetId_betaStar_pfakt5, &b_jetId_betaStar_pfakt5);
   fChain->SetBranchAddress("jetId_dZ_pfakt5", jetId_dZ_pfakt5, &b_jetId_dZ_pfakt5);
   fChain->SetBranchAddress("jetId_nCharged_pfakt5", jetId_nCharged_pfakt5, &b_jetId_nCharged_pfakt5);
   fChain->SetBranchAddress("jetId_dR2Mean_pfakt5", jetId_dR2Mean_pfakt5, &b_jetId_dR2Mean_pfakt5);
   fChain->SetBranchAddress("jetId_betaStarClassic_pfakt5", jetId_betaStarClassic_pfakt5, &b_jetId_betaStarClassic_pfakt5);
   fChain->SetBranchAddress("jetIdSimple_mva_pfakt5", jetIdSimple_mva_pfakt5, &b_jetIdSimple_mva_pfakt5);
   fChain->SetBranchAddress("jetIdSimple_wp_pfakt5", jetIdSimple_wp_pfakt5, &b_jetIdSimple_wp_pfakt5);
   fChain->SetBranchAddress("jetIdFull_mva_pfakt5", jetIdFull_mva_pfakt5, &b_jetIdFull_mva_pfakt5);
   fChain->SetBranchAddress("jetIdFull_wp_pfakt5", jetIdFull_wp_pfakt5, &b_jetIdFull_wp_pfakt5);
   fChain->SetBranchAddress("jetIdCutBased_mva_pfakt5", jetIdCutBased_mva_pfakt5, &b_jetIdCutBased_mva_pfakt5);
   fChain->SetBranchAddress("jetIdCutBased_wp_pfakt5", jetIdCutBased_wp_pfakt5, &b_jetIdCutBased_wp_pfakt5);
   fChain->SetBranchAddress("beta_pfakt5", beta_pfakt5, &b_beta_pfakt5);
   fChain->SetBranchAddress("betaStar_pfakt5", betaStar_pfakt5, &b_betaStar_pfakt5);
   fChain->SetBranchAddress("combinedSecondaryVertexBJetTags", combinedSecondaryVertexBJetTags, &b_combinedSecondaryVertexBJetTags);
   fChain->SetBranchAddress("combinedSecondaryVertexMVABJetTags", combinedSecondaryVertexMVABJetTags, &b_combinedSecondaryVertexMVABJetTags);
   fChain->SetBranchAddress("jetBProbabilityBJetTags", jetBProbabilityBJetTags, &b_jetBProbabilityBJetTags);
   fChain->SetBranchAddress("jetProbabilityBJetTags", jetProbabilityBJetTags, &b_jetProbabilityBJetTags);
   fChain->SetBranchAddress("simpleSecondaryVertexHighEffBJetTags", simpleSecondaryVertexHighEffBJetTags, &b_simpleSecondaryVertexHighEffBJetTags);
   fChain->SetBranchAddress("simpleSecondaryVertexHighPurBJetTags", simpleSecondaryVertexHighPurBJetTags, &b_simpleSecondaryVertexHighPurBJetTags);
   fChain->SetBranchAddress("softMuonBJetTags", softMuonBJetTags, &b_softMuonBJetTags);
   fChain->SetBranchAddress("softMuonByIP3dBJetTags", softMuonByIP3dBJetTags, &b_softMuonByIP3dBJetTags);
   fChain->SetBranchAddress("softMuonByPtBJetTags", softMuonByPtBJetTags, &b_softMuonByPtBJetTags);
   fChain->SetBranchAddress("softElectronByIP3dBJetTags", softElectronByIP3dBJetTags, &b_softElectronByIP3dBJetTags);
   fChain->SetBranchAddress("softElectronByPtBJetTags", softElectronByPtBJetTags, &b_softElectronByPtBJetTags);
   fChain->SetBranchAddress("trackCountingHighPurBJetTags", trackCountingHighPurBJetTags, &b_trackCountingHighPurBJetTags);
   fChain->SetBranchAddress("trackCountingHighEffBJetTags", trackCountingHighEffBJetTags, &b_trackCountingHighEffBJetTags);
   fChain->SetBranchAddress("npfcand_all", &npfcand_all, &b_npfcand_all);
   fChain->SetBranchAddress("nChargedHadrons_uncl", &nChargedHadrons_uncl, &b_nChargedHadrons_uncl);
   fChain->SetBranchAddress("nChargedHadronsgoodvtx_uncl", &nChargedHadronsgoodvtx_uncl, &b_nChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("nChargedHadronsnoothervtx_uncl", &nChargedHadronsnoothervtx_uncl, &b_nChargedHadronsothervtx_uncl);
   fChain->SetBranchAddress("nPhotons_uncl", &nPhotons_uncl, &b_nPhotons_uncl);
   fChain->SetBranchAddress("nMuons_uncl", &nMuons_uncl, &b_nMuons_uncl);
   fChain->SetBranchAddress("nElectrons_uncl", &nElectrons_uncl, &b_nElectrons_uncl);
   fChain->SetBranchAddress("nNeutralHadrons_uncl", &nNeutralHadrons_uncl, &b_nNeutralHadrons_uncl);
   fChain->SetBranchAddress("nHFHadrons_uncl", &nHFHadrons_uncl, &b_nHFHadrons_uncl);
   fChain->SetBranchAddress("nHFEM_uncl", &nHFEM_uncl, &b_nHFEM_uncl);
   fChain->SetBranchAddress("epfcand_all", &epfcand_all, &b_epfcand_all);
   fChain->SetBranchAddress("eChargedHadrons_uncl", &eChargedHadrons_uncl, &b_eChargedHadrons_uncl);
   fChain->SetBranchAddress("eChargedHadronsgoodvtx_uncl", &eChargedHadronsgoodvtx_uncl, &b_eChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("eChargedHadronsnoothervtx_uncl", &eChargedHadronsnoothervtx_uncl, &b_eChargedHadronsnoothervtx_uncl);
   fChain->SetBranchAddress("ePhotons_uncl", &ePhotons_uncl, &b_ePhotons_uncl);
   fChain->SetBranchAddress("eMuons_uncl", &eMuons_uncl, &b_eMuons_uncl);
   fChain->SetBranchAddress("eElectrons_uncl", &eElectrons_uncl, &b_eElectrons_uncl);
   fChain->SetBranchAddress("eNeutralHadrons_uncl", &eNeutralHadrons_uncl, &b_eNeutralHadrons_uncl);
   fChain->SetBranchAddress("eHFHadrons_uncl", &eHFHadrons_uncl, &b_eHFHadrons_uncl);
   fChain->SetBranchAddress("eHFEM_uncl", &eHFEM_uncl, &b_eHFEM_uncl);
   fChain->SetBranchAddress("ptpfcand_all", &ptpfcand_all, &b_ptpfcand_all);
   fChain->SetBranchAddress("ptChargedHadrons_uncl", &ptChargedHadrons_uncl, &b_ptChargedHadrons_uncl);
   fChain->SetBranchAddress("ptChargedHadronsgoodvtx_uncl", &ptChargedHadronsgoodvtx_uncl, &b_ptChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("ptChargedHadronsnoothervtx_uncl", &ptChargedHadronsnoothervtx_uncl, &b_ptChargedHadronsnoothervtx_uncl);
   fChain->SetBranchAddress("ptPhotons_uncl", &ptPhotons_uncl, &b_ptPhotons_uncl);
   fChain->SetBranchAddress("ptMuons_uncl", &ptMuons_uncl, &b_ptMuons_uncl);
   fChain->SetBranchAddress("ptElectrons_uncl", &ptElectrons_uncl, &b_ptElectrons_uncl);
   fChain->SetBranchAddress("ptNeutralHadrons_uncl", &ptNeutralHadrons_uncl, &b_ptNeutralHadrons_uncl);
   fChain->SetBranchAddress("ptHFHadrons_uncl", &ptHFHadrons_uncl, &b_ptHFHadrons_uncl);
   fChain->SetBranchAddress("ptHFEM_uncl", &ptHFEM_uncl, &b_ptHFEM_uncl);
//    fChain->SetBranchAddress("ptpfcand_all", &ptpfcand_all, &b_ptpfcand_all);
   fChain->SetBranchAddress("etaChargedHadrons_uncl", &etaChargedHadrons_uncl, &b_etaChargedHadrons_uncl);
   fChain->SetBranchAddress("etaChargedHadronsgoodvtx_uncl", &etaChargedHadronsgoodvtx_uncl, &b_etaChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("etaChargedHadronsnoothervtx_uncl", &etaChargedHadronsnoothervtx_uncl, &b_etaChargedHadronsnoothervtx_uncl);
   fChain->SetBranchAddress("etaPhotons_uncl", &etaPhotons_uncl, &b_etaPhotons_uncl);
   fChain->SetBranchAddress("etaMuons_uncl", &etaMuons_uncl, &b_etaMuons_uncl);
   fChain->SetBranchAddress("etaElectrons_uncl", &etaElectrons_uncl, &b_etaElectrons_uncl);
   fChain->SetBranchAddress("etaNeutralHadrons_uncl", &etaNeutralHadrons_uncl, &b_etaNeutralHadrons_uncl);
   fChain->SetBranchAddress("etaHFHadrons_uncl", &etaHFHadrons_uncl, &b_etaHFHadrons_uncl);
   fChain->SetBranchAddress("etaHFEM_uncl", &etaHFEM_uncl, &b_etaHFEM_uncl);
//    fChain->SetBranchAddress("ptpfcand_all", &ptpfcand_all, &b_ptpfcand_all);
   fChain->SetBranchAddress("phiChargedHadrons_uncl", &phiChargedHadrons_uncl, &b_phiChargedHadrons_uncl);
   fChain->SetBranchAddress("phiChargedHadronsgoodvtx_uncl", &phiChargedHadronsgoodvtx_uncl, &b_phiChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("phiChargedHadronsnoothervtx_uncl", &phiChargedHadronsnoothervtx_uncl, &b_phiChargedHadronsnoothervtx_uncl);
   fChain->SetBranchAddress("phiPhotons_uncl", &phiPhotons_uncl, &b_phiPhotons_uncl);
   fChain->SetBranchAddress("phiMuons_uncl", &phiMuons_uncl, &b_phiMuons_uncl);
   fChain->SetBranchAddress("phiElectrons_uncl", &phiElectrons_uncl, &b_phiElectrons_uncl);
   fChain->SetBranchAddress("phiNeutralHadrons_uncl", &phiNeutralHadrons_uncl, &b_phiNeutralHadrons_uncl);
   fChain->SetBranchAddress("phiHFHadrons_uncl", &phiHFHadrons_uncl, &b_phiHFHadrons_uncl);
   fChain->SetBranchAddress("phiHFEM_uncl", &phiHFEM_uncl, &b_phiHFEM_uncl);
   fChain->SetBranchAddress("sumptpfcand_all", &sumptpfcand_all, &b_sumptpfcand_all);
   fChain->SetBranchAddress("sumptChargedHadrons_uncl", &sumptChargedHadrons_uncl, &b_sumptChargedHadrons_uncl);
   fChain->SetBranchAddress("sumptChargedHadronsgoodvtx_uncl", &sumptChargedHadronsgoodvtx_uncl, &b_sumptChargedHadronsgoodvtx_uncl);
   fChain->SetBranchAddress("sumptChargedHadronsnoothervtx_uncl", &sumptChargedHadronsnoothervtx_uncl, &b_sumptChargedHadronsnoothervtx_uncl);
   fChain->SetBranchAddress("sumptPhotons_uncl", &sumptPhotons_uncl, &b_sumptPhotons_uncl);
   fChain->SetBranchAddress("sumptMuons_uncl", &sumptMuons_uncl, &b_sumptMuons_uncl);
   fChain->SetBranchAddress("sumptElectrons_uncl", &sumptElectrons_uncl, &b_sumptElectrons_uncl);
   fChain->SetBranchAddress("sumptNeutralHadrons_uncl", &sumptNeutralHadrons_uncl, &b_sumptNeutralHadrons_uncl);
   fChain->SetBranchAddress("sumptHFHadrons_uncl", &sumptHFHadrons_uncl, &b_sumptHFHadrons_uncl);
   fChain->SetBranchAddress("sumptHFEM_uncl", &sumptHFEM_uncl, &b_sumptHFEM_uncl);
//    fChain->SetBranchAddress("sumptpfcand_all", &sumptpfcand_all, &b_sumptpfcand_all);
   fChain->SetBranchAddress("nChargedHadrons_pfakt5", nChargedHadrons_pfakt5, &b_nChargedHadrons_pfakt5);
   fChain->SetBranchAddress("nChargedHadronsgoodvtx_pfakt5", nChargedHadronsgoodvtx_pfakt5, &b_nChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("nChargedHadronsnoothervtx_pfakt5", nChargedHadronsnoothervtx_pfakt5, &b_nChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("nPhotons_pfakt5", nPhotons_pfakt5, &b_nPhotons_pfakt5);
   fChain->SetBranchAddress("nMuons_pfakt5", nMuons_pfakt5, &b_nMuons_pfakt5);
   fChain->SetBranchAddress("nElectrons_pfakt5", nElectrons_pfakt5, &b_nElectrons_pfakt5);
   fChain->SetBranchAddress("nNeutralHadrons_pfakt5", nNeutralHadrons_pfakt5, &b_nNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("nHFHadrons_pfakt5", nHFHadrons_pfakt5, &b_nHFHadrons_pfakt5);
   fChain->SetBranchAddress("nHFEM_pfakt5", nHFEM_pfakt5, &b_nHFEM_pfakt5);
   fChain->SetBranchAddress("eChargedHadrons_pfakt5", eChargedHadrons_pfakt5, &b_eChargedHadrons_pfakt5);
   fChain->SetBranchAddress("eChargedHadronsgoodvtx_pfakt5", eChargedHadronsgoodvtx_pfakt5, &b_eChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("eChargedHadronsnoothervtx_pfakt5", eChargedHadronsnoothervtx_pfakt5, &b_eChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("ePhotons_pfakt5", ePhotons_pfakt5, &b_ePhotons_pfakt5);
   fChain->SetBranchAddress("eMuons_pfakt5", eMuons_pfakt5, &b_eMuons_pfakt5);
   fChain->SetBranchAddress("eElectrons_pfakt5", eElectrons_pfakt5, &b_eElectrons_pfakt5);
   fChain->SetBranchAddress("eNeutralHadrons_pfakt5", eNeutralHadrons_pfakt5, &b_eNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("eHFHadrons_pfakt5", eHFHadrons_pfakt5, &b_eHFHadrons_pfakt5);
   fChain->SetBranchAddress("eHFEM_pfakt5", eHFEM_pfakt5, &b_eHFEM_pfakt5);
   fChain->SetBranchAddress("ptChargedHadrons_pfakt5", ptChargedHadrons_pfakt5, &b_ptChargedHadrons_pfakt5);
   fChain->SetBranchAddress("ptChargedHadronsgoodvtx_pfakt5", ptChargedHadronsgoodvtx_pfakt5, &b_ptChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("ptChargedHadronsnoothervtx_pfakt5", ptChargedHadronsnoothervtx_pfakt5, &b_ptChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("ptPhotons_pfakt5", ptPhotons_pfakt5, &b_ptPhotons_pfakt5);
   fChain->SetBranchAddress("ptMuons_pfakt5", ptMuons_pfakt5, &b_ptMuons_pfakt5);
   fChain->SetBranchAddress("ptElectrons_pfakt5", ptElectrons_pfakt5, &b_ptElectrons_pfakt5);
   fChain->SetBranchAddress("ptNeutralHadrons_pfakt5", ptNeutralHadrons_pfakt5, &b_ptNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("ptHFHadrons_pfakt5", ptHFHadrons_pfakt5, &b_ptHFHadrons_pfakt5);
   fChain->SetBranchAddress("ptHFEM_pfakt5", ptHFEM_pfakt5, &b_ptHFEM_pfakt5);
   fChain->SetBranchAddress("etaChargedHadrons_pfakt5", etaChargedHadrons_pfakt5, &b_etaChargedHadrons_pfakt5);
   fChain->SetBranchAddress("etaChargedHadronsgoodvtx_pfakt5", etaChargedHadronsgoodvtx_pfakt5, &b_etaChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("etaChargedHadronsnoothervtx_pfakt5", etaChargedHadronsnoothervtx_pfakt5, &b_etaChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("etaPhotons_pfakt5", etaPhotons_pfakt5, &b_etaPhotons_pfakt5);
   fChain->SetBranchAddress("etaMuons_pfakt5", etaMuons_pfakt5, &b_etaMuons_pfakt5);
   fChain->SetBranchAddress("etaElectrons_pfakt5", etaElectrons_pfakt5, &b_etaElectrons_pfakt5);
   fChain->SetBranchAddress("etaNeutralHadrons_pfakt5", etaNeutralHadrons_pfakt5, &b_etaNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("etaHFHadrons_pfakt5", etaHFHadrons_pfakt5, &b_etaHFHadrons_pfakt5);
   fChain->SetBranchAddress("etaHFEM_pfakt5", etaHFEM_pfakt5, &b_etaHFEM_pfakt5);
   fChain->SetBranchAddress("phiChargedHadrons_pfakt5", phiChargedHadrons_pfakt5, &b_phiChargedHadrons_pfakt5);
   fChain->SetBranchAddress("phiChargedHadronsgoodvtx_pfakt5", phiChargedHadronsgoodvtx_pfakt5, &b_phiChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("phiChargedHadronsnoothervtx_pfakt5", phiChargedHadronsnoothervtx_pfakt5, &b_phiChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("phiPhotons_pfakt5", phiPhotons_pfakt5, &b_phiPhotons_pfakt5);
   fChain->SetBranchAddress("phiMuons_pfakt5", phiMuons_pfakt5, &b_phiMuons_pfakt5);
   fChain->SetBranchAddress("phiElectrons_pfakt5", phiElectrons_pfakt5, &b_phiElectrons_pfakt5);
   fChain->SetBranchAddress("phiNeutralHadrons_pfakt5", phiNeutralHadrons_pfakt5, &b_phiNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("phiHFHadrons_pfakt5", phiHFHadrons_pfakt5, &b_phiHFHadrons_pfakt5);
   fChain->SetBranchAddress("phiHFEM_pfakt5", phiHFEM_pfakt5, &b_phiHFEM_pfakt5);
   fChain->SetBranchAddress("sumptChargedHadrons_pfakt5", sumptChargedHadrons_pfakt5, &b_sumptChargedHadrons_pfakt5);
   fChain->SetBranchAddress("sumptChargedHadronsgoodvtx_pfakt5", sumptChargedHadronsgoodvtx_pfakt5, &b_sumptChargedHadronsgoodvtx_pfakt5);
   fChain->SetBranchAddress("sumptChargedHadronsnoothervtx_pfakt5", sumptChargedHadronsnoothervtx_pfakt5, &b_sumptChargedHadronsnoothervtx_pfakt5);
   fChain->SetBranchAddress("sumptPhotons_pfakt5", sumptPhotons_pfakt5, &b_sumptPhotons_pfakt5);
   fChain->SetBranchAddress("sumptMuons_pfakt5", sumptMuons_pfakt5, &b_sumptMuons_pfakt5);
   fChain->SetBranchAddress("sumptElectrons_pfakt5", sumptElectrons_pfakt5, &b_sumptElectrons_pfakt5);
   fChain->SetBranchAddress("sumptNeutralHadrons_pfakt5", sumptNeutralHadrons_pfakt5, &b_sumptNeutralHadrons_pfakt5);
   fChain->SetBranchAddress("sumptHFHadrons_pfakt5", sumptHFHadrons_pfakt5, &b_sumptHFHadrons_pfakt5);
   fChain->SetBranchAddress("sumptHFEM_pfakt5", sumptHFEM_pfakt5, &b_sumptHFEM_pfakt5);
   fChain->SetBranchAddress("nJet_pfakt7", &nJet_pfakt7, &b_nJet_pfakt7);
   fChain->SetBranchAddress("ptJet_pfakt7 ", ptJet_pfakt7 , &b_ptJet_pfakt7 );
   fChain->SetBranchAddress("ptCorrJet_pfakt7 ", ptCorrJet_pfakt7 , &b_ptCorrJet_pfakt7 );
   fChain->SetBranchAddress("eJet_pfakt7  ", eJet_pfakt7  , &b_eJet_pfakt7  );
   fChain->SetBranchAddress("etaJet_pfakt7", etaJet_pfakt7, &b_etaJet_pfakt7);
   fChain->SetBranchAddress("phiJet_pfakt7", phiJet_pfakt7, &b_phiJet_pfakt7);
   fChain->SetBranchAddress("nJetGen_akt5", &nJetGen_akt5, &b_nJetGen_akt5);
   fChain->SetBranchAddress("ptJetGen_akt5 ", &ptJetGen_akt5 , &b_ptJetGen_akt5 );
   fChain->SetBranchAddress("eJetGen_akt5  ", &eJetGen_akt5  , &b_eJetGen_akt5  );
   fChain->SetBranchAddress("etaJetGen_akt5", &etaJetGen_akt5, &b_etaJetGen_akt5);
   fChain->SetBranchAddress("phiJetGen_akt5", &phiJetGen_akt5, &b_phiJetGen_akt5);
   fChain->SetBranchAddress("nMuonsGen_akt5", &nMuonsGen_akt5, &b_nMuonsGen_akt5);
   fChain->SetBranchAddress("nElectronsGen_akt5", &nElectronsGen_akt5, &b_nElectronsGen_akt5);
   fChain->SetBranchAddress("nPhotonsGen_akt5", &nPhotonsGen_akt5, &b_nPhotonsGen_akt5);
   fChain->SetBranchAddress("nTracksGen_akt5", &nTracksGen_akt5, &b_nTracksGen_akt5);
   fChain->SetBranchAddress("nNeutralHadronsGen_akt5", &nNeutralHadronsGen_akt5, &b_nNeutralHadronsGen_akt5);
   fChain->SetBranchAddress("nHFHadronsGen_akt5", &nHFHadronsGen_akt5, &b_nHFHadronsGen_akt5);
   fChain->SetBranchAddress("nHFEMGen_akt5", &nHFEMGen_akt5, &b_nHFEMGen_akt5);
   fChain->SetBranchAddress("nNeutronsGen_akt5", &nNeutronsGen_akt5, &b_nNeutronsGen_akt5);
   fChain->SetBranchAddress("nK0LGen_akt5", &nK0LGen_akt5, &b_nK0LGen_akt5);
   fChain->SetBranchAddress("nK0SGen_akt5", &nK0SGen_akt5, &b_nK0SGen_akt5);
   fChain->SetBranchAddress("nLambdasGen_akt5", &nLambdasGen_akt5, &b_nLambdasGen_akt5);
   fChain->SetBranchAddress("nCsiGen_akt5", &nCsiGen_akt5, &b_nCsiGen_akt5);
   fChain->SetBranchAddress("nOtherNeutralHadronsGen_akt5", &nOtherNeutralHadronsGen_akt5, &b_nOtherNeutralHadronsGen_akt5);
   fChain->SetBranchAddress("eMuonsGen_akt5", &eMuonsGen_akt5, &b_eMuonsGen_akt5);
   fChain->SetBranchAddress("eElectronsGen_akt5", &eElectronsGen_akt5, &b_eElectronsGen_akt5);
   fChain->SetBranchAddress("ePhotonsGen_akt5", &ePhotonsGen_akt5, &b_ePhotonsGen_akt5);
   fChain->SetBranchAddress("eTracksGen_akt5", &eTracksGen_akt5, &b_eTracksGen_akt5);
   fChain->SetBranchAddress("eNeutralHadronsGen_akt5", &eNeutralHadronsGen_akt5, &b_eNeutralHadronsGen_akt5);
   fChain->SetBranchAddress("eHFHadronsGen_akt5", &eHFHadronsGen_akt5, &b_eHFHadronsGen_akt5);
   fChain->SetBranchAddress("eHFEMGen_akt5", &eHFEMGen_akt5, &b_eHFEMGen_akt5);
   fChain->SetBranchAddress("eNeutronsGen_akt5", &eNeutronsGen_akt5, &b_eNeutronsGen_akt5);
   fChain->SetBranchAddress("eK0LGen_akt5", &eK0LGen_akt5, &b_eK0LGen_akt5);
   fChain->SetBranchAddress("eK0SGen_akt5", &eK0SGen_akt5, &b_eK0SGen_akt5);
   fChain->SetBranchAddress("eLambdasGen_akt5", &eLambdasGen_akt5, &b_eLambdasGen_akt5);
   fChain->SetBranchAddress("eCsiGen_akt5", &eCsiGen_akt5, &b_eCsiGen_akt5);
   fChain->SetBranchAddress("eOtherNeutralHadronsGen_akt5", &eOtherNeutralHadronsGen_akt5, &b_eOtherNeutralHadronsGen_akt5);
   fChain->SetBranchAddress("nJetGen_akt7", &nJetGen_akt7, &b_nJetGen_akt7);
   fChain->SetBranchAddress("ptJetGen_akt7 ", &ptJetGen_akt7 , &b_ptJetGen_akt7 );
   fChain->SetBranchAddress("eJetGen_akt7  ", &eJetGen_akt7  , &b_eJetGen_akt7  );
   fChain->SetBranchAddress("etaJetGen_akt7", &etaJetGen_akt7, &b_etaJetGen_akt7);
   fChain->SetBranchAddress("phiJetGen_akt7", &phiJetGen_akt7, &b_phiJetGen_akt7);
   fChain->SetBranchAddress("nvertex", &nvertex, &b_nvertex);
   fChain->SetBranchAddress("sMet  ", &sMet  , &b_sMet);
   fChain->SetBranchAddress("eMet  ", &eMet  , &b_eMet);
   fChain->SetBranchAddress("phiMet", &phiMet, &b_phiMet);
   fChain->SetBranchAddress("signifMet", &signifMet, &b_signifMet);
   fChain->SetBranchAddress("sCorrMet  ", &sCorrMet  , &b_sCorrMet);
   fChain->SetBranchAddress("eCorrMet  ", &eCorrMet  , &b_eCorrMet);
   fChain->SetBranchAddress("phiCorrMet", &phiCorrMet, &b_phiCorrMet);
   fChain->SetBranchAddress("signifCorrMet", &signifCorrMet, &b_signifCorrMet);
   fChain->SetBranchAddress("sNoHFMet  ", &sNoHFMet  , &b_sNoHFMet);
   fChain->SetBranchAddress("eNoHFMet  ", &eNoHFMet  , &b_eNoHFMet);
   fChain->SetBranchAddress("phiNoHFMet", &phiNoHFMet, &b_phiNoHFMet);
   fChain->SetBranchAddress("signifNoHFMet", &signifNoHFMet, &b_signifNoHFMet);
   fChain->SetBranchAddress("stcMet", &stcMet, &b_stcMet);
   fChain->SetBranchAddress("etcMet", &etcMet, &b_etcMet);
   fChain->SetBranchAddress("phitcMet", &phitcMet, &b_phitcMet);
   fChain->SetBranchAddress("signiftcMet", &signiftcMet, &b_signiftcMet);
   fChain->SetBranchAddress("sglobalPfMet", &sglobalPfMet, &b_sglobalPfMet);
   fChain->SetBranchAddress("eglobalPfMet", &eglobalPfMet, &b_eglobalPfMet);
   fChain->SetBranchAddress("phiglobalPfMet", &phiglobalPfMet, &b_phiglobalPfMet);
   fChain->SetBranchAddress("signifglobalPfMet", &signifglobalPfMet, &b_signifglobalPfMet);
   fChain->SetBranchAddress("scentralPfMet", &scentralPfMet, &b_scentralPfMet);
   fChain->SetBranchAddress("ecentralPfMet", &ecentralPfMet, &b_ecentralPfMet);
   fChain->SetBranchAddress("phicentralPfMet", &phicentralPfMet, &b_phicentralPfMet);
   fChain->SetBranchAddress("signifcentralPfMet", &signifcentralPfMet, &b_signifcentralPfMet);
   fChain->SetBranchAddress("eassocPfMet", eassocPfMet, &b_eassocPfMet);
   fChain->SetBranchAddress("phiassocPfMet", phiassocPfMet, &b_phiassocPfMet);
   fChain->SetBranchAddress("signifassocPfMet", signifassocPfMet, &b_signifassocPfMet);
   fChain->SetBranchAddress("eassocOtherVtxPfMet", eassocOtherVtxPfMet, &b_eassocOtherVtxPfMet);
   fChain->SetBranchAddress("phiassocOtherVtxPfMet", phiassocOtherVtxPfMet, &b_phiassocOtherVtxPfMet);
   fChain->SetBranchAddress("signifassocOtherVtxPfMet", signifassocOtherVtxPfMet, &b_signifassocOtherVtxPfMet);
   fChain->SetBranchAddress("etrkPfMet", etrkPfMet, &b_etrkPfMet);
   fChain->SetBranchAddress("phitrkPfMet", phitrkPfMet, &b_phitrkPfMet);
   fChain->SetBranchAddress("signiftrkPfMet", signiftrkPfMet, &b_signiftrkPfMet);
   fChain->SetBranchAddress("ecleanPfMet", ecleanPfMet, &b_ecleanPfMet);
   fChain->SetBranchAddress("phicleanPfMet", phicleanPfMet, &b_phicleanPfMet);
   fChain->SetBranchAddress("signifcleanPfMet", signifcleanPfMet, &b_signifcleanPfMet);
   fChain->SetBranchAddress("globalPfSums", globalPfSums, &b_globalPfSums);
   fChain->SetBranchAddress("spfMet", &spfMet, &b_spfMet);
   fChain->SetBranchAddress("epfMet", &epfMet, &b_epfMet);
   fChain->SetBranchAddress("phipfMet", &phipfMet, &b_phipfMet);
   fChain->SetBranchAddress("signifpfMet", &signifpfMet, &b_signifpfMet);
   fChain->SetBranchAddress("spfMetType1", &spfMetType1, &b_spfMetType1);
   fChain->SetBranchAddress("epfMetType1", &epfMetType1, &b_epfMetType1);
   fChain->SetBranchAddress("phipfMetType1", &phipfMetType1, &b_phipfMetType1);
   fChain->SetBranchAddress("signifpfMetType1", &signifpfMetType1, &b_signifpfMetType1);
   fChain->SetBranchAddress("sMetGen", &sMetGen, &b_sMetGen);
   fChain->SetBranchAddress("eMetGen", &eMetGen, &b_eMetGen);
   fChain->SetBranchAddress("phiMetGen", &phiMetGen, &b_phiMetGen);
   fChain->SetBranchAddress("signifMetGen", &signifMetGen, &b_signifMetGen);
   fChain->SetBranchAddress("sMetGen2", &sMetGen2, &b_sMetGen2);
   fChain->SetBranchAddress("eMetGen2", &eMetGen2, &b_eMetGen2);
   fChain->SetBranchAddress("phiMetGen2", &phiMetGen2, &b_phiMetGen2);
   fChain->SetBranchAddress("vxMC", &vxMC, &b_vxMC);
   fChain->SetBranchAddress("vyMC", &vyMC, &b_vyMC);
   fChain->SetBranchAddress("vzMC", &vzMC, &b_vzMC);
   fChain->SetBranchAddress("vx", vx, &b_vx);
   fChain->SetBranchAddress("vy", vy, &b_vy);
   fChain->SetBranchAddress("vz", vz, &b_vz);
   fChain->SetBranchAddress("vntracks", vntracks, &b_vntracks);
   fChain->SetBranchAddress("vchi2", vchi2, &b_vchi2);
   fChain->SetBranchAddress("vndof", vndof, &b_vndof);
   fChain->SetBranchAddress("vlogsumpt2", vlogsumpt2, &b_vlogsumpt2);
   fChain->SetBranchAddress("nPreselPhotonPairs", &nPreselPhotonPairs, &b_nPreselPhotonPairs);
   fChain->SetBranchAddress("indexPreselPhot1", indexPreselPhot1, &b_indexPreselPhot1);
   fChain->SetBranchAddress("indexPreselPhot2", indexPreselPhot2, &b_indexPreselPhot2);
   fChain->SetBranchAddress("vrankPhotonPairs", vrankPhotonPairs, &b_vrankPhotonPairs);
   fChain->SetBranchAddress("vevtMvaPhotonPairs", vevtMvaPhotonPairs, &b_vevtMvaPhotonPairs);
   fChain->SetBranchAddress("vevtProbPhotonPairs", vevtProbPhotonPairs, &b_vevtProbPhotonPairs);
   fChain->SetBranchAddress("vptbalPhotonPairs", vptbalPhotonPairs, &b_vptbalPhotonPairs);
   fChain->SetBranchAddress("vptasymPhotonPairs", vptasymPhotonPairs, &b_vptasymPhotonPairs);
   fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
   fChain->SetBranchAddress("hltNamesLen", &hltNamesLen, &b_hltNamesLen);
   fChain->SetBranchAddress("HLTNames", &HLTNames, &b_HLTNames);
   fChain->SetBranchAddress("HLTResults", &HLTResults, &b_HLTResults);
   fChain->SetBranchAddress("trg17_SC_ele_n", &trg17_SC_ele_n, &b_ElectronRefs0_n);
   fChain->SetBranchAddress("trg17_SC_ele_eta", trg17_SC_ele_eta, &b_trg17_SC_ele_eta);
   fChain->SetBranchAddress("trg17_SC_ele_et", trg17_SC_ele_et, &b_trg17_SC_ele_et);
   fChain->SetBranchAddress("trg17_SC_ele_phi", trg17_SC_ele_phi, &b_trg17_SC_ele_phi);
   fChain->SetBranchAddress("trg32_ele_n", &trg32_ele_n, &b_ElectronRefs1_n);
   fChain->SetBranchAddress("trg32_ele_eta", trg32_ele_eta, &b_trg32_ele_eta);
   fChain->SetBranchAddress("trg32_ele_et", trg32_ele_et, &b_trg32_ele_et);
   fChain->SetBranchAddress("trg32_ele_phi", trg32_ele_phi, &b_trg32_ele_phi);
   fChain->SetBranchAddress("trg8_ele_n", &trg8_ele_n, &b_ElectronRefs2_n);
   fChain->SetBranchAddress("trg8_ele_eta", trg8_ele_eta, &b_trg8_ele_eta);
   fChain->SetBranchAddress("trg8_ele_et", trg8_ele_et, &b_trg8_ele_et);
   fChain->SetBranchAddress("trg8_ele_phi", trg8_ele_phi, &b_trg8_ele_phi);
   fChain->SetBranchAddress("trg17_ele_n", &trg17_ele_n, &b_ElectronRefs3_n);
   fChain->SetBranchAddress("trg17_ele_eta", trg17_ele_eta, &b_trg17_ele_eta);
   fChain->SetBranchAddress("trg17_ele_et", trg17_ele_et, &b_trg17_ele_et);
   fChain->SetBranchAddress("trg17_ele_phi", trg17_ele_phi, &b_trg17_ele_phi);
   fChain->SetBranchAddress("trg8_mass50_ele_n", &trg8_mass50_ele_n, &b_ElectronRefs4_n);
   fChain->SetBranchAddress("trg8_mass50_ele_eta", trg8_mass50_ele_eta, &b_trg8_mass50_ele_eta);
   fChain->SetBranchAddress("trg8_mass50_ele_et", trg8_mass50_ele_et, &b_trg8_mass50_ele_et);
   fChain->SetBranchAddress("trg8_mass50_ele_phi", trg8_mass50_ele_phi, &b_trg8_mass50_ele_phi);
   fChain->SetBranchAddress("trg17_mass50_ele_n", &trg17_mass50_ele_n, &b_ElectronRefs5_n);
   fChain->SetBranchAddress("trg17_mass50_ele_eta", trg17_mass50_ele_eta, &b_trg17_mass50_ele_eta);
   fChain->SetBranchAddress("trg17_mass50_ele_et", trg17_mass50_ele_et, &b_trg17_mass50_ele_et);
   fChain->SetBranchAddress("trg17_mass50_ele_phi", trg17_mass50_ele_phi, &b_trg17_mass50_ele_phi);
   fChain->SetBranchAddress("trg4_mass50_SC_n", &trg4_mass50_SC_n, &b_ElectronRefs6_n);
   fChain->SetBranchAddress("trg4_mass50_SC_eta", trg4_mass50_SC_eta, &b_trg4_mass50_SC_eta);
   fChain->SetBranchAddress("trg4_mass50_SC_et", trg4_mass50_SC_et, &b_trg4_mass50_SC_et);
   fChain->SetBranchAddress("trg4_mass50_SC_phi", trg4_mass50_SC_phi, &b_trg4_mass50_SC_phi);
   fChain->SetBranchAddress("trg20_mass50_ele_n", &trg20_mass50_ele_n, &b_ElectronRefs7_n);
   fChain->SetBranchAddress("trg20_mass50_ele_eta", trg20_mass50_ele_eta, &b_trg20_mass50_ele_eta);
   fChain->SetBranchAddress("trg20_mass50_ele_et", trg20_mass50_ele_et, &b_trg20_mass50_ele_et);
   fChain->SetBranchAddress("trg20_mass50_ele_phi", trg20_mass50_ele_phi, &b_trg20_mass50_ele_phi);
   fChain->SetBranchAddress("trg20_phoIDCaloVL_n", &trg20_phoIDCaloVL_n, &b_PhotonRefs0_n);
   fChain->SetBranchAddress("trg20_phoIDCaloVL_eta", &trg20_phoIDCaloVL_eta, &b_trg20_phoIDCaloVL_eta);
   fChain->SetBranchAddress("trg20_phoIDCaloVL_et", &trg20_phoIDCaloVL_et, &b_trg20_phoIDCaloVL_et);
   fChain->SetBranchAddress("trg20_phoIDCaloVL_phi", &trg20_phoIDCaloVL_phi, &b_trg20_phoIDCaloVL_phi);
   fChain->SetBranchAddress("trg30_phoIDCaloVL_n", &trg30_phoIDCaloVL_n, &b_PhotonRefs1_n);
   fChain->SetBranchAddress("trg30_phoIDCaloVL_eta", trg30_phoIDCaloVL_eta, &b_trg30_phoIDCaloVL_eta);
   fChain->SetBranchAddress("trg30_phoIDCaloVL_et", trg30_phoIDCaloVL_et, &b_trg30_phoIDCaloVL_et);
   fChain->SetBranchAddress("trg30_phoIDCaloVL_phi", trg30_phoIDCaloVL_phi, &b_trg30_phoIDCaloVL_phi);
   fChain->SetBranchAddress("trg50_phoIDCaloVL_n", &trg50_phoIDCaloVL_n, &b_PhotonRefs2_n);
   fChain->SetBranchAddress("trg50_phoIDCaloVL_eta", trg50_phoIDCaloVL_eta, &b_trg50_phoIDCaloVL_eta);
   fChain->SetBranchAddress("trg50_phoIDCaloVL_et", trg50_phoIDCaloVL_et, &b_trg50_phoIDCaloVL_et);
   fChain->SetBranchAddress("trg50_phoIDCaloVL_phi", trg50_phoIDCaloVL_phi, &b_trg50_phoIDCaloVL_phi);
   fChain->SetBranchAddress("trg75_phoIDCaloVL_n", &trg75_phoIDCaloVL_n, &b_PhotonRefs3_n);
   fChain->SetBranchAddress("trg75_phoIDCaloVL_eta", trg75_phoIDCaloVL_eta, &b_trg75_phoIDCaloVL_eta);
   fChain->SetBranchAddress("trg75_phoIDCaloVL_et", trg75_phoIDCaloVL_et, &b_trg75_phoIDCaloVL_et);
   fChain->SetBranchAddress("trg75_phoIDCaloVL_phi", trg75_phoIDCaloVL_phi, &b_trg75_phoIDCaloVL_phi);
   fChain->SetBranchAddress("trg90_phoIDCaloVL_n", &trg90_phoIDCaloVL_n, &b_PhotonRefs4_n);
   fChain->SetBranchAddress("trg90_phoIDCaloVL_eta", trg90_phoIDCaloVL_eta, &b_trg90_phoIDCaloVL_eta);
   fChain->SetBranchAddress("trg90_phoIDCaloVL_et", trg90_phoIDCaloVL_et, &b_trg90_phoIDCaloVL_et);
   fChain->SetBranchAddress("trg90_phoIDCaloVL_phi", trg90_phoIDCaloVL_phi, &b_trg90_phoIDCaloVL_phi);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("electron_px", electron_px, &b_electron_px);
   fChain->SetBranchAddress("electron_py", electron_py, &b_electron_py);
   fChain->SetBranchAddress("electron_pz", electron_pz, &b_electron_pz);
   fChain->SetBranchAddress("electron_vx", electron_vx, &b_electron_vx);
   fChain->SetBranchAddress("electron_vy", electron_vy, &b_electron_vy);
   fChain->SetBranchAddress("electron_vz", electron_vz, &b_electron_vz);
   fChain->SetBranchAddress("electron_pt", electron_pt, &b_electron_pt);
   fChain->SetBranchAddress("electron_eta", electron_eta, &b_electron_eta);
   fChain->SetBranchAddress("electron_phi", electron_phi, &b_electron_phi);
   fChain->SetBranchAddress("electron_energy", electron_energy, &b_electron_energy);
   fChain->SetBranchAddress("electron_ecalEnergy", electron_ecalEnergy, &b_electron_ecalEnergy);
   fChain->SetBranchAddress("electron_trackPatVtx", electron_trackPatVtx, &b_electron_trackPatVtx);
   fChain->SetBranchAddress("electron_charge", electron_charge, &b_electron_charge);
   fChain->SetBranchAddress("electron_fBrem", electron_fBrem, &b_electron_fBrem);
   fChain->SetBranchAddress("electron_dist", electron_dist, &b_electron_dist);
   fChain->SetBranchAddress("electron_dcot", electron_dcot, &b_electron_dcot);
   fChain->SetBranchAddress("electron_misHits", electron_misHits, &b_electron_misHits);
   fChain->SetBranchAddress("electron_matchedConv", electron_matchedConv, &b_electron_matchedConv);
   fChain->SetBranchAddress("electron_seedType", electron_seedType, &b_electron_seedType);
   fChain->SetBranchAddress("electron_EoP", electron_EoP, &b_electron_EoP);
   fChain->SetBranchAddress("electron_OneOverEMinusOneOverP", electron_OneOverEMinusOneOverP, &b_electron_OneOverEMinusOneOverP);
   fChain->SetBranchAddress("electron_r9", electron_r9, &b_electron_r9);
   fChain->SetBranchAddress("electron_nSubClusters", electron_nSubClusters, &b_electron_nSubClusters);
   fChain->SetBranchAddress("electron_trkIso", electron_trkIso, &b_electron_trkIso);
   fChain->SetBranchAddress("electron_ecalIso", electron_ecalIso, &b_electron_ecalIso);
   fChain->SetBranchAddress("electron_hcalIso", electron_hcalIso, &b_electron_hcalIso);
   fChain->SetBranchAddress("electron_trkIso03", electron_trkIso03, &b_electron_trkIso03);
   fChain->SetBranchAddress("electron_ecalIso03", electron_ecalIso03, &b_electron_ecalIso03);
   fChain->SetBranchAddress("electron_hcalIso03", electron_hcalIso03, &b_electron_hcalIso03);
   fChain->SetBranchAddress("electron_SigmaIetaIeta", electron_SigmaIetaIeta, &b_electron_SigmaIetaIeta);
   fChain->SetBranchAddress("electron_SigmaIphiIphi", electron_SigmaIphiIphi, &b_electron_SigmaIphiIphi);
   fChain->SetBranchAddress("electron_dEtaIn", electron_dEtaIn, &b_electron_dEtaIn);
   fChain->SetBranchAddress("electron_dPhiIn", electron_dPhiIn, &b_electron_dPhiIn);
   fChain->SetBranchAddress("electron_HoE", electron_HoE, &b_electron_HoE);
   fChain->SetBranchAddress("electron_pFlowMVA", electron_pFlowMVA, &b_electron_pFlowMVA);
   fChain->SetBranchAddress("electron_sc_energy", electron_sc_energy, &b_electron_sc_energy);
   fChain->SetBranchAddress("electron_sc_eta", electron_sc_eta, &b_electron_sc_eta);
   fChain->SetBranchAddress("electron_sc_phi", electron_sc_phi, &b_electron_sc_phi);
   fChain->SetBranchAddress("electron_mvaNonTrig", electron_mvaNonTrig, &b_electron_mvaNonTrig);
   fChain->SetBranchAddress("electron_mvaTrig", electron_mvaTrig, &b_electron_mvaTrig);
   fChain->SetBranchAddress("electron_chHad03Iso", electron_chHad03Iso, &b_electron_chHad03Iso);
   fChain->SetBranchAddress("electron_nHad03Iso", electron_nHad03Iso, &b_electron_nHad03Iso);
   fChain->SetBranchAddress("electron_phot03Iso", electron_phot03Iso, &b_electron_phot03Iso);
   fChain->SetBranchAddress("electron_chHad04Iso", electron_chHad04Iso, &b_electron_chHad04Iso);
   fChain->SetBranchAddress("electron_nHad04Iso", electron_nHad04Iso, &b_electron_nHad04Iso);
   fChain->SetBranchAddress("electron_phot04Iso", electron_phot04Iso, &b_electron_phot04Iso);
   fChain->SetBranchAddress("electron_chHad05Iso", electron_chHad05Iso, &b_electron_chHad05Iso);
   fChain->SetBranchAddress("electron_nHad05Iso", electron_nHad05Iso, &b_electron_nHad05Iso);
   fChain->SetBranchAddress("electron_phot05Iso", electron_phot05Iso, &b_electron_phot05Iso);
   fChain->SetBranchAddress("isBeamHaloGlobalLoosePass", &isBeamHaloGlobalLoosePass, &b_isBeamHaloGlobalLoosePass);
   fChain->SetBranchAddress("isBeamHaloGlobalTightPass", &isBeamHaloGlobalTightPass, &b_isBeamHaloGloablTightPass);
   fChain->SetBranchAddress("isBeamHaloHcalLoosePass", &isBeamHaloHcalLoosePass, &b_isBeamHaloHcalLoosePass);
   fChain->SetBranchAddress("isBeamHaloHcalTightPass", &isBeamHaloHcalTightPass, &b_isBeamHaloHcalTightPass);
   fChain->SetBranchAddress("isBeamHaloCSCLoosePass", &isBeamHaloCSCLoosePass, &b_isBeamHaloCSCLoosePass);
   fChain->SetBranchAddress("isBeamHaloCSCTightPass", &isBeamHaloCSCTightPass, &b_isBeamHaloCSCTightPass);
   fChain->SetBranchAddress("isBeamHaloEcalLoosePass", &isBeamHaloEcalLoosePass, &b_isBeamHaloEcalLoosePass);
   fChain->SetBranchAddress("isBeamHaloEcalTightPass", &isBeamHaloEcalTightPass, &b_isBeamHaloEcalTightPass);
   fChain->SetBranchAddress("isBeamHaloIDTightPass", &isBeamHaloIDTightPass, &b_isBeamHaloIDTightPass);
   fChain->SetBranchAddress("isBeamHaloIDLoosePass", &isBeamHaloIDLoosePass, &b_isBeamHaloIDLoosePass);
   fChain->SetBranchAddress("isSmellsLikeHalo_Tag", &isSmellsLikeHalo_Tag, &b_isSmellsLikeHalo_Tag);
   fChain->SetBranchAddress("isLooseHalo_Tag", &isLooseHalo_Tag, &b_isLooseHalo_Tag);
   fChain->SetBranchAddress("isTightHalo_Tag", &isTightHalo_Tag, &b_isTightHalo_Tag);
   fChain->SetBranchAddress("isExtremeTightHalo_Tag", &isExtremeTightHalo_Tag, &b_isExtremeTightHalo_Tag);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("Muon_px", Muon_px, &b_Muon_px);
   fChain->SetBranchAddress("Muon_py", Muon_py, &b_Muon_py);
   fChain->SetBranchAddress("Muon_pz", Muon_pz, &b_Muon_pz);
   fChain->SetBranchAddress("Muon_vx", Muon_vx, &b_Muon_vx);
   fChain->SetBranchAddress("Muon_vy", Muon_vy, &b_Muon_vy);
   fChain->SetBranchAddress("Muon_vz", Muon_vz, &b_Muon_vz);
   fChain->SetBranchAddress("Muon_pt", Muon_pt, &b_Muon_pt);
   fChain->SetBranchAddress("Muon_eta", Muon_eta, &b_Muon_eta);
   fChain->SetBranchAddress("Muon_phi", Muon_phi, &b_Muon_phi);
   fChain->SetBranchAddress("Muon_energy", Muon_energy, &b_Muon_energy);
   fChain->SetBranchAddress("Muon_charge", Muon_charge, &b_Muon_charge);
   fChain->SetBranchAddress("Muon_isGlobalMuon", Muon_isGlobalMuon, &b_Muon_isGlobalMuon);
   fChain->SetBranchAddress("Muon_isTrackerMuon", Muon_isTrackerMuon, &b_Muon_isTrackerMuon);
   fChain->SetBranchAddress("Muon_isStandAloneMuon", Muon_isStandAloneMuon, &b_Muon_isStandAloneMuon);
   fChain->SetBranchAddress("Muon_trkLayerWithMeas", Muon_trkLayerWithMeas, &b_Muon_trkLayerWithMeas);
   fChain->SetBranchAddress("Muon_InnerTrack_isNonnull", Muon_InnerTrack_isNonnull, &b_Muon_InnerTrack_isNonnull);
   fChain->SetBranchAddress("Muon_OuterTrack_isNonnull", Muon_OuterTrack_isNonnull, &b_Muon_OuterTrack_isNonnull);
   fChain->SetBranchAddress("Muon_OuterPoint_x", Muon_OuterPoint_x, &b_Muon_OuterPoint_x);
   fChain->SetBranchAddress("Muon_OuterPoint_y", Muon_OuterPoint_y, &b_Muon_OuterPoint_y);
   fChain->SetBranchAddress("Muon_OuterPoint_z", Muon_OuterPoint_z, &b_Muon_OuterPoint_z);
   fChain->SetBranchAddress("Muon_isPFMuon", Muon_isPFMuon, &b_Muon_isPFMuon);
   fChain->SetBranchAddress("Muon_pfiso04_chHad", Muon_pfiso04_chHad, &b_Muon_pfiso04_chHad);
   fChain->SetBranchAddress("Muon_pfiso04_chPar", Muon_pfiso04_chPar, &b_Muon_pfiso04_chPar);
   fChain->SetBranchAddress("Muon_pfiso04_nHad", Muon_pfiso04_nHad, &b_Muon_pfiso04_nHad);
   fChain->SetBranchAddress("Muon_pfiso04_Phot", Muon_pfiso04_Phot, &b_Muon_pfiso04_Phot);
   fChain->SetBranchAddress("Muon_pfiso04_PUPt", Muon_pfiso04_PUPt, &b_Muon_pfiso04_PUPt);
   fChain->SetBranchAddress("Muon_pfiso03_chHad", Muon_pfiso03_chHad, &b_Muon_pfiso03_chHad);
   fChain->SetBranchAddress("Muon_pfiso03_chPar", Muon_pfiso03_chPar, &b_Muon_pfiso03_chPar);
   fChain->SetBranchAddress("Muon_pfiso03_nHad", Muon_pfiso03_nHad, &b_Muon_pfiso03_nHad);
   fChain->SetBranchAddress("Muon_pfiso03_Phot", Muon_pfiso03_Phot, &b_Muon_pfiso03_Phot);
   fChain->SetBranchAddress("Muon_pfiso03_PUPt", Muon_pfiso03_PUPt, &b_Muon_pfiso03_PUPt);
   fChain->SetBranchAddress("Muon_InnerPoint_x", Muon_InnerPoint_x, &b_Muon_InnerPoint_x);
   fChain->SetBranchAddress("Muon_InnerPoint_y", Muon_InnerPoint_y, &b_Muon_InnerPoint_y);
   fChain->SetBranchAddress("Muon_InnerPoint_z", Muon_InnerPoint_z, &b_Muon_InnerPoint_z);
   fChain->SetBranchAddress("Muon_trackIso", Muon_trackIso, &b_Muon_trackIso);
   fChain->SetBranchAddress("Muon_ecalIso", Muon_ecalIso, &b_Muon_ecalIso);
   fChain->SetBranchAddress("Muon_hcalIso", Muon_hcalIso, &b_Muon_hcalIso);
   fChain->SetBranchAddress("Muon_relIso", Muon_relIso, &b_Muon_relIso);
   fChain->SetBranchAddress("Muon_normChi2", Muon_normChi2, &b_Muon_normChi2);
   fChain->SetBranchAddress("Muon_validHits", Muon_validHits, &b_Muon_validHits);
   fChain->SetBranchAddress("Muon_tkHits", Muon_tkHits, &b_Muon_tkHits);
   fChain->SetBranchAddress("Muon_pixHits", Muon_pixHits, &b_Muon_pixHits);
   fChain->SetBranchAddress("Muon_numberOfMatches", Muon_numberOfMatches, &b_Muon_numberOfMatches);
   fChain->SetBranchAddress("nCosmicMuons", &nCosmicMuons, &b_nCosmicMuons);
   fChain->SetBranchAddress("CosmicMuon_px", CosmicMuon_px, &b_CosmicMuon_px);
   fChain->SetBranchAddress("CosmicMuon_py", CosmicMuon_py, &b_CosmicMuon_py);
   fChain->SetBranchAddress("CosmicMuon_pz", CosmicMuon_pz, &b_CosmicMuon_pz);
   fChain->SetBranchAddress("CosmicMuon_pt", CosmicMuon_pt, &b_CosmicMuon_pt);
   fChain->SetBranchAddress("CosmicMuon_eta", CosmicMuon_eta, &b_CosmicMuon_eta);
   fChain->SetBranchAddress("CosmicMuon_phi", CosmicMuon_phi, &b_CosmicMuon_phi);
   fChain->SetBranchAddress("CosmicMuon_energy", CosmicMuon_energy, &b_CosmicMuon_energy);
   fChain->SetBranchAddress("CosmicMuon_charge", CosmicMuon_charge, &b_CosmicMuon_charge);
   fChain->SetBranchAddress("CosmicMuon_isGlobalMuon", CosmicMuon_isGlobalMuon, &b_CosmicMuon_isGlobalMuon);
   fChain->SetBranchAddress("CosmicMuon_isTrackerMuon", CosmicMuon_isTrackerMuon, &b_CosmicMuon_isTrackerMuon);
   fChain->SetBranchAddress("CosmicMuon_isStandAloneMuon", CosmicMuon_isStandAloneMuon, &b_CosmicMuon_isStandAloneMuon);
   fChain->SetBranchAddress("CosmicMuon_InnerTrack_isNonnull", CosmicMuon_InnerTrack_isNonnull, &b_CosmicMuon_InnerTrack_isNonnull);
   fChain->SetBranchAddress("CosmicMuon_OuterTrack_isNonnull", CosmicMuon_OuterTrack_isNonnull, &b_CosmicMuon_OuterTrack_isNonnull);
   fChain->SetBranchAddress("CosmicMuon_OuterPoint_x", CosmicMuon_OuterPoint_x, &b_CosmicMuon_OuterPoint_x);
   fChain->SetBranchAddress("CosmicMuon_OuterPoint_y", CosmicMuon_OuterPoint_y, &b_CosmicMuon_OuterPoint_y);
   fChain->SetBranchAddress("CosmicMuon_OuterPoint_z", CosmicMuon_OuterPoint_z, &b_CosmicMuon_OuterPoint_z);
   fChain->SetBranchAddress("Xsec", &Xsec, &b_Xsec);
   Notify();
}

Bool_t tree_reader_v9::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree_reader_v9::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree_reader_v9::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_reader_v9_cxx
