//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 17 16:50:07 2013 by ROOT version 5.32/00
// from TTree AnaTree/Reduced tree for final analysis
// found on file: /t3/users/meridian/GammaJets/reduced/redntp.53xv4.gjetpresel.noCorr.v1/merged/redntp_QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6.root
//////////////////////////////////////////////////////////

#ifndef TurnOnCurveGamma_h
#define TurnOnCurveGamma_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include "TMVA/Reader.h"

class TurnOnCurveGamma {
public :
   TTree          *fChain;      //! pointer to the analyzed TTree or TChain
   Int_t           fCurrent;    //! current Tree number in a TChain

#include "RedNtpFormat.h"       

   bool  isMVAinitialized;

   TFile*         outFile;
   TString        outputFile;

#include "FinalTreeTurnOn.h"   

   bool isHLT_30();
   bool isHLT_50();
   bool isHLT_75();
   bool isHLT_90();
   bool isHLT_135();
   bool isHLT_150();

   int effectiveAreaRegion(float theEta);

   std::vector<int> sortedPtPhotons();
   std::vector<int> preselectedPhotons(const std::vector<int>& photons);
   std::vector<int> selectedPhotons(const std::vector<int>& photons);

   void SetAllMVA();
   Float_t PhotonIDMVA(Int_t iPhoton);

   TTree* finalTreeTurnOn;
   void BookFinalTreeTurnOn();
   void FillTreeEvent();

   TMVA::Reader *tmvaReaderID_Single_Barrel, *tmvaReaderID_Single_Endcap;
   float tmva_photonid_etawidth, tmva_photonid_phiwidth;
   float tmva_photonid_sieie,    tmva_photonid_sieip;
   float tmva_photonid_s4ratio,  tmva_photonid_r9;
   float tmva_photonid_pt,       tmva_photonid_sceta;
   float tmva_photonid_rr;
   float tmva_photonid_nPhot, tmva_photonid_isMatchedPhot, tmva_photonid_ptWeight;
   float tmva_photonid_eventrho;

   // for the output tree
   bool isHLT30, isHLT50, isHLT75, isHLT90, isHLT135, isHLT150;
   bool isAZ, isAZ_tight;
   float mass, ptEle1, ptEle2, etaEle1, etaEle2;
   bool match20, match30, match50, match75, match90; 
   float eta_match20, eta_match30, eta_match50, eta_match75, eta_match90; 
   float pt_match20,  pt_match30,  pt_match50,  pt_match75,  pt_match90;
   float pt_online_match20,  pt_online_match30,  pt_online_match50,  pt_online_match75,  pt_online_match90;
   
   TurnOnCurveGamma(TTree *tree=0);
   virtual ~TurnOnCurveGamma();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TurnOnCurveGamma_cxx
TurnOnCurveGamma::TurnOnCurveGamma(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {

    TChain * chain = new TChain("AnaTree","");
    chain->Add("/xrootdfs/cms/local/meridian/GammaJets/reduced/redntp.53xv6_data_CERN.gjetpresel.noCorr.v2/*2012D*.root/AnaTree");

    tree = chain;
  }
  Init(tree);
}

TurnOnCurveGamma::~TurnOnCurveGamma()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t TurnOnCurveGamma::GetEntry(Long64_t entry)
{
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t TurnOnCurveGamma::LoadTree(Long64_t entry)
{
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void TurnOnCurveGamma::Init(TTree *tree)
{
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
  fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
  fChain->SetBranchAddress("LOGamma", &LOGamma, &b_LOGamma);
  fChain->SetBranchAddress("ISRGamma", &ISRGamma, &b_ISRGamma);
  fChain->SetBranchAddress("FSRGamma", &FSRGamma, &b_FSRGamma);
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
  fChain->SetBranchAddress("nPhot_gen", &nPhot_gen, &b_nPhot_gen);
  fChain->SetBranchAddress("deltaRMatch_gen", deltaRMatch_gen, &b_deltaRMatch_gen);
  fChain->SetBranchAddress("ptTrueMatch_gen", ptTrueMatch_gen, &b_ptTrueMatch_gen);
  fChain->SetBranchAddress("etaMatch_gen", etaMatch_gen, &b_etaMatch_gen);
  fChain->SetBranchAddress("phiMatch_gen", phiMatch_gen, &b_phiMatch_gen);
  fChain->SetBranchAddress("ptRecoMatch_gen", ptRecoMatch_gen, &b_ptRecoMatch_gen);
  fChain->SetBranchAddress("iRecoPhotMatch_gen", iRecoPhotMatch_gen, &b_iRecoPhotMatch_gen);
  fChain->SetBranchAddress("iso02_gen", iso02_gen, &b_iso02_gen);
  fChain->SetBranchAddress("iso03_gen", iso03_gen, &b_iso03_gen);
  fChain->SetBranchAddress("iso04_gen", iso04_gen, &b_iso04_gen);
  fChain->SetBranchAddress("iso05_gen", iso05_gen, &b_iso05_gen);
  fChain->SetBranchAddress("nPhot_presel", &nPhot_presel, &b_nPhot_presel);
  fChain->SetBranchAddress("ptPhot_presel", ptPhot_presel, &b_ptPhot_presel);
  fChain->SetBranchAddress("ePhot_presel", ePhot_presel, &b_ePhot_presel);
  fChain->SetBranchAddress("etascPhot_presel  ", etascPhot_presel  , &b_etascPhot_presel  );
  fChain->SetBranchAddress("etaPhot_presel", etaPhot_presel, &b_etaPhot_presel);
  fChain->SetBranchAddress("phiPhot_presel", phiPhot_presel, &b_phiPhot_presel);
  fChain->SetBranchAddress("pid_jurECAL03_presel", pid_jurECAL03_presel, &b_pid_jurECAL03_presel);
  fChain->SetBranchAddress("pid_twrHCAL03_presel", pid_twrHCAL03_presel, &b_pid_twrHCAL03_presel);
  fChain->SetBranchAddress("pid_hlwTrack03_presel", pid_hlwTrack03_presel, &b_pid_hlwTrack03_presel);
  fChain->SetBranchAddress("pid_jurECAL04_presel", pid_jurECAL04_presel, &b_pid_jurECAL04_presel);
  fChain->SetBranchAddress("pid_twrHCAL04_presel", pid_twrHCAL04_presel, &b_pid_twrHCAL04_presel);
  fChain->SetBranchAddress("pid_hlwTrack04_presel", pid_hlwTrack04_presel, &b_pid_hlwTrack04_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged01ForCiC_presel", pid_pfIsoCharged01ForCiC_presel, &b_pid_pfIsoCharged01ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged02ForCiC_presel", pid_pfIsoCharged02ForCiC_presel, &b_pid_pfIsoCharged02ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged03ForCiC_presel", pid_pfIsoCharged03ForCiC_presel, &b_pid_pfIsoCharged03ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged04ForCiC_presel", pid_pfIsoCharged04ForCiC_presel, &b_pid_pfIsoCharged04ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged05ForCiC_presel", pid_pfIsoCharged05ForCiC_presel, &b_pid_pfIsoCharged05ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoCharged06ForCiC_presel", pid_pfIsoCharged06ForCiC_presel, &b_pid_pfIsoCharged06ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons01ForCiC_presel", pid_pfIsoPhotons01ForCiC_presel, &b_pid_pfIsoPhotons01ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons02ForCiC_presel", pid_pfIsoPhotons02ForCiC_presel, &b_pid_pfIsoPhotons02ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons03ForCiC_presel", pid_pfIsoPhotons03ForCiC_presel, &b_pid_pfIsoPhotons03ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons04ForCiC_presel", pid_pfIsoPhotons04ForCiC_presel, &b_pid_pfIsoPhotons04ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons05ForCiC_presel", pid_pfIsoPhotons05ForCiC_presel, &b_pid_pfIsoPhotons05ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoPhotons06ForCiC_presel", pid_pfIsoPhotons06ForCiC_presel, &b_pid_pfIsoPhotons06ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals01ForCiC_presel", pid_pfIsoNeutrals01ForCiC_presel, &b_pid_pfIsoNeutrals01ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals02ForCiC_presel", pid_pfIsoNeutrals02ForCiC_presel, &b_pid_pfIsoNeutrals02ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals03ForCiC_presel", pid_pfIsoNeutrals03ForCiC_presel, &b_pid_pfIsoNeutrals03ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals04ForCiC_presel", pid_pfIsoNeutrals04ForCiC_presel, &b_pid_pfIsoNeutrals04ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals05ForCiC_presel", pid_pfIsoNeutrals05ForCiC_presel, &b_pid_pfIsoNeutrals05ForCiC_presel);
  fChain->SetBranchAddress("pid_pfIsoNeutrals06ForCiC_presel", pid_pfIsoNeutrals06ForCiC_presel, &b_pid_pfIsoNeutrals06ForCiC_presel);
  fChain->SetBranchAddress("pid_scetawid_presel", pid_scetawid_presel, &b_pid_scetawid_presel);
  fChain->SetBranchAddress("pid_scphiwid_presel", pid_scphiwid_presel, &b_pid_scphiwid_presel);
  fChain->SetBranchAddress("pid_lambdaRatio_presel", pid_lambdaRatio_presel, &b_pid_lambdaRatio_presel);
  fChain->SetBranchAddress("pid_HoverE_presel", pid_HoverE_presel, &b_pid_HoverE_presel);
  fChain->SetBranchAddress("sEtaEtaPhot_presel", sEtaEtaPhot_presel, &b_sEtaEtaPhot_presel);
  fChain->SetBranchAddress("sEtaPhiPhot_presel", sEtaPhiPhot_presel, &b_sEtaPhiPhot_presel);
  fChain->SetBranchAddress("s4RatioPhot_presel", s4RatioPhot_presel, &b_s4RatioPhot_presel);
  fChain->SetBranchAddress("r9Phot_presel", r9Phot_presel, &b_r9Phot_presel);
  fChain->SetBranchAddress("rhoAllJets", &rhoAllJets, &b_rhoAllJets);
  fChain->SetBranchAddress("rhoPF", &rhoPF, &b_rhoPF);
  fChain->SetBranchAddress("rr_presel", rr_presel, &b_rr_presel);
  fChain->SetBranchAddress("isMatchedPhot", isMatchedPhot, &b_isMatchedPhot);
  fChain->SetBranchAddress("iMatchedPhot", iMatchedPhot, &b_iMatchedPhot);
  fChain->SetBranchAddress("isTrig20CaloVLMatchedPhot", isTrig20CaloVLMatchedPhot, &b_isTrig20CaloVLMatchedPhot);
  fChain->SetBranchAddress("isTrig30CaloVLMatchedPhot", isTrig30CaloVLMatchedPhot, &b_isTrig30CaloVLMatchedPhot);
  fChain->SetBranchAddress("isTrig50CaloVLMatchedPhot", isTrig50CaloVLMatchedPhot, &b_isTrig50CaloVLMatchedPhot);
  fChain->SetBranchAddress("isTrig75CaloVLMatchedPhot", isTrig75CaloVLMatchedPhot, &b_isTrig75CaloVLMatchedPhot);
  fChain->SetBranchAddress("isTrig90CaloVLMatchedPhot", isTrig90CaloVLMatchedPhot, &b_isTrig90CaloVLMatchedPhot);
  fChain->SetBranchAddress("hltCandPt20CaloVLPhot", hltCandPt20CaloVLPhot, &b_hltCandPt20CaloVLPhot);
  fChain->SetBranchAddress("hltCandPt30CaloVLPhot", hltCandPt30CaloVLPhot, &b_hltCandPt30CaloVLPhot);
  fChain->SetBranchAddress("hltCandPt50CaloVLPhot", hltCandPt50CaloVLPhot, &b_hltCandPt50CaloVLPhot);
  fChain->SetBranchAddress("hltCandPt75CaloVLPhot", hltCandPt75CaloVLPhot, &b_hltCandPt75CaloVLPhot);
  fChain->SetBranchAddress("hltCandPt90CaloVLPhot", hltCandPt90CaloVLPhot, &b_hltCandPt90CaloVLPhot);
  fChain->SetBranchAddress("vtxId", &vtxId, &b_vtxId);
  fChain->SetBranchAddress("firedHLTNames", &firedHLTNames, &b_firedHLTNames);
  Notify();
}

Bool_t TurnOnCurveGamma::Notify()
{
  return kTRUE;
}

void TurnOnCurveGamma::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t TurnOnCurveGamma::Cut(Long64_t entry)
{
  return 1;
}
#endif // #ifdef TurnOnCurveGamma_cxx
