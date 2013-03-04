//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  1 14:34:16 2013 by ROOT version 5.32/00
// from TTree AnaTree/Reduced tree for final analysis
// found on file: /xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.noCorrections.singleGamma_v2_noPresel/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root
//////////////////////////////////////////////////////////

#ifndef tree_reader_h
#define tree_reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class tree_reader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumi;
   Float_t         nvtx;
   Int_t           npu;
   Int_t           NtotEvents;
   Float_t         xsection;
   Float_t         EquivLumi;
   Int_t           SampleID;
   Float_t         pu_weight;
   Int_t           nPhot_gen;
   Int_t           nPhot_presel;
   Float_t         ptPhot_presel[6];   //[nPhot_presel]
   Float_t         ePhot_presel[6];   //[nPhot_presel]
   Float_t         etascPhot_presel  [6];   //[nPhot_presel]
   Float_t         etaPhot_presel[6];   //[nPhot_presel]
   Float_t         phiPhot_presel[6];   //[nPhot_presel]
   Float_t         pid_jurECAL03_presel[6];   //[nPhot_presel]
   Float_t         pid_twrHCAL03_presel[6];   //[nPhot_presel]
   Float_t         pid_hlwTrack03_presel[6];   //[nPhot_presel]
   Float_t         pid_jurECAL04_presel[6];   //[nPhot_presel]
   Float_t         pid_twrHCAL04_presel[6];   //[nPhot_presel]
   Float_t         pid_hlwTrack04_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged01ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged02ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged03ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged04ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged05ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged06ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons01ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons02ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons03ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons04ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons05ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons06ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals01ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals02ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals03ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals04ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals05ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals06ForCiC_presel[6];   //[nPhot_presel]
   Float_t         pid_scetawid_presel[6];   //[nPhot_presel]
   Float_t         pid_scphiwid_presel[6];   //[nPhot_presel]
   Float_t         pid_lambdaRatio_presel[6];   //[nPhot_presel]
   Float_t         pid_HoverE_presel[6];   //[nPhot_presel]
   Float_t         sEtaEtaPhot_presel[6];   //[nPhot_presel]
   Float_t         sEtaPhiPhot_presel[6];   //[nPhot_presel]
   Float_t         s4RatioPhot_presel[6];   //[nPhot_presel]
   Float_t         r9Phot_presel[6];   //[nPhot_presel]
   Float_t         rhoAllJets;
   Float_t         rhoPF;
   Float_t         rr_presel[6];   //[nPhot_presel]
   Int_t           isMatchedPhot[6];   //[nPhot_presel]
   Float_t         deltaRGenReco[2];   //[nPhot_gen]
   vector<string>  *firedHLTNames;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_NtotEvents;   //!
   TBranch        *b_xsection;   //!
   TBranch        *b_EquivLumi;   //!
   TBranch        *b_SampleID;   //!
   TBranch        *b_pu_weight;   //!
   TBranch        *b_nPhot_gen;   //!
   TBranch        *b_nPhot_presel;   //!
   TBranch        *b_ptPhot_presel;   //!
   TBranch        *b_ePhot_presel;   //!
   TBranch        *b_etascPhot_presel  ;   //!
   TBranch        *b_etaPhot_presel;   //!
   TBranch        *b_phiPhot_presel;   //!
   TBranch        *b_pid_jurECAL03_presel;   //!
   TBranch        *b_pid_twrHCAL03_presel;   //!
   TBranch        *b_pid_hlwTrack03_presel;   //!
   TBranch        *b_pid_jurECAL04_presel;   //!
   TBranch        *b_pid_twrHCAL04_presel;   //!
   TBranch        *b_pid_hlwTrack04_presel;   //!
   TBranch        *b_pid_pfIsoCharged01ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoCharged02ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoCharged03ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoCharged04ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoCharged05ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoCharged06ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons01ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons02ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons03ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons04ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons05ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoPhotons06ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals01ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals02ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals03ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals04ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals05ForCiC_presel;   //!
   TBranch        *b_pid_pfIsoNeutrals06ForCiC_presel;   //!
   TBranch        *b_pid_scetawid_presel;   //!
   TBranch        *b_pid_scphiwid_presel;   //!
   TBranch        *b_pid_lambdaRatio_presel;   //!
   TBranch        *b_pid_HoverE_presel;   //!
   TBranch        *b_sEtaEtaPhot_presel;   //!
   TBranch        *b_sEtaPhiPhot_presel;   //!
   TBranch        *b_s4RatioPhot_presel;   //!
   TBranch        *b_r9Phot_presel;   //!
   TBranch        *b_rhoAllJets;   //!
   TBranch        *b_rhoPF;   //!
   TBranch        *b_rr_presel;   //!
   TBranch        *b_isMatchedPhot;   //!
   TBranch        *b_deltaRGenReco;   //!
   TBranch        *b_firedHLTNames;   //!

   tree_reader(TTree *tree=0);
   virtual ~tree_reader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_reader_cxx
tree_reader::tree_reader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.noCorrections.singleGamma_v2_noPresel/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.noCorrections.singleGamma_v2_noPresel/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
      }
      f->GetObject("AnaTree",tree);

   }
   Init(tree);
}

tree_reader::~tree_reader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree_reader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree_reader::LoadTree(Long64_t entry)
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

void tree_reader::Init(TTree *tree)
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
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("NtotEvents", &NtotEvents, &b_NtotEvents);
   fChain->SetBranchAddress("xsection", &xsection, &b_xsection);
   fChain->SetBranchAddress("EquivLumi", &EquivLumi, &b_EquivLumi);
   fChain->SetBranchAddress("SampleID", &SampleID, &b_SampleID);
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight);
   fChain->SetBranchAddress("nPhot_gen", &nPhot_gen, &b_nPhot_gen);
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
   fChain->SetBranchAddress("deltaRGenReco", deltaRGenReco, &b_deltaRGenReco);
   fChain->SetBranchAddress("firedHLTNames", &firedHLTNames, &b_firedHLTNames);
   Notify();
}

Bool_t tree_reader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree_reader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree_reader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_reader_cxx
