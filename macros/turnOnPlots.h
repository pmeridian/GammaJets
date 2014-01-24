//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 14 16:29:42 2014 by ROOT version 5.30/02
// from TTree finalTreeTurnOn/finalTreeTurnOn
// found on file: myTurnOnFile.root
//////////////////////////////////////////////////////////

#ifndef turnOnPlots_h
#define turnOnPlots_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class turnOnPlots {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         ptGamma20;
   Float_t         ptGamma30;
   Float_t         ptGamma50;
   Float_t         ptGamma75;
   Float_t         ptGamma90;
   Float_t         ptOnlineGamma20;
   Float_t         ptOnlineGamma30;
   Float_t         ptOnlineGamma50;
   Float_t         ptOnlineGamma75;
   Float_t         ptOnlineGamma90;
   Float_t         etaGamma20;
   Float_t         etaGamma30;
   Float_t         etaGamma50;
   Float_t         etaGamma75;
   Float_t         etaGamma90;
   UInt_t          hltmatchGamma20;
   UInt_t          hltmatchGamma30;
   UInt_t          hltmatchGamma50;
   UInt_t          hltmatchGamma75;
   UInt_t          hltmatchGamma90;
   UInt_t          passHLT30;
   UInt_t          passHLT50;
   UInt_t          passHLT75;
   UInt_t          passHLT90;
   UInt_t          passHLT135;
   UInt_t          passHLT150;
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   UInt_t          nvtx;
   Float_t         rho;

   // List of branches
   TBranch        *b_ptGamma20;   //!
   TBranch        *b_ptGamma30;   //!
   TBranch        *b_ptGamma50;   //!
   TBranch        *b_ptGamma75;   //!
   TBranch        *b_ptGamma90;   //!
   TBranch        *b_ptOnlineGamma20;   //!
   TBranch        *b_ptOnlineGamma30;   //!
   TBranch        *b_ptOnlineGamma50;   //!
   TBranch        *b_ptOnlineGamma75;   //!
   TBranch        *b_ptOnlineGamma90;   //!
   TBranch        *b_etaGamma20;   //!
   TBranch        *b_etaGamma30;   //!
   TBranch        *b_etaGamma50;   //!
   TBranch        *b_etaGamma75;   //!
   TBranch        *b_etaGamma90;   //!
   TBranch        *b_hltmatchGamma20;   //!
   TBranch        *b_hltmatchGamma30;   //!
   TBranch        *b_hltmatchGamma50;   //!
   TBranch        *b_hltmatchGamma75;   //!
   TBranch        *b_hltmatchGamma90;   //!
   TBranch        *b_passHLT30;   //!
   TBranch        *b_passHLT50;   //!
   TBranch        *b_passHLT75;   //!
   TBranch        *b_passHLT90;   //!
   TBranch        *b_passHLT135;   //!
   TBranch        *b_passHLT150;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_rho;   //!

   turnOnPlots(TTree *tree=0);
   virtual ~turnOnPlots();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef turnOnPlots_cxx
turnOnPlots::turnOnPlots(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("myTurnOnFile2012.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("myTurnOnFile2012.root");
      }
      f->GetObject("finalTreeTurnOn",tree);

   }
   Init(tree);
}

turnOnPlots::~turnOnPlots()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t turnOnPlots::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t turnOnPlots::LoadTree(Long64_t entry)
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

void turnOnPlots::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ptGamma20", &ptGamma20, &b_ptGamma20);
   fChain->SetBranchAddress("ptGamma30", &ptGamma30, &b_ptGamma30);
   fChain->SetBranchAddress("ptGamma50", &ptGamma50, &b_ptGamma50);
   fChain->SetBranchAddress("ptGamma75", &ptGamma75, &b_ptGamma75);
   fChain->SetBranchAddress("ptGamma90", &ptGamma90, &b_ptGamma90);
   fChain->SetBranchAddress("ptOnlineGamma20", &ptOnlineGamma20, &b_ptOnlineGamma20);
   fChain->SetBranchAddress("ptOnlineGamma30", &ptOnlineGamma30, &b_ptOnlineGamma30);
   fChain->SetBranchAddress("ptOnlineGamma50", &ptOnlineGamma50, &b_ptOnlineGamma50);
   fChain->SetBranchAddress("ptOnlineGamma75", &ptOnlineGamma75, &b_ptOnlineGamma75);
   fChain->SetBranchAddress("ptOnlineGamma90", &ptOnlineGamma90, &b_ptOnlineGamma90);
   fChain->SetBranchAddress("etaGamma20", &etaGamma20, &b_etaGamma20);
   fChain->SetBranchAddress("etaGamma30", &etaGamma30, &b_etaGamma30);
   fChain->SetBranchAddress("etaGamma50", &etaGamma50, &b_etaGamma50);
   fChain->SetBranchAddress("etaGamma75", &etaGamma75, &b_etaGamma75);
   fChain->SetBranchAddress("etaGamma90", &etaGamma90, &b_etaGamma90);
   fChain->SetBranchAddress("hltmatchGamma20", &hltmatchGamma20, &b_hltmatchGamma20);
   fChain->SetBranchAddress("hltmatchGamma30", &hltmatchGamma30, &b_hltmatchGamma30);
   fChain->SetBranchAddress("hltmatchGamma50", &hltmatchGamma50, &b_hltmatchGamma50);
   fChain->SetBranchAddress("hltmatchGamma75", &hltmatchGamma75, &b_hltmatchGamma75);
   fChain->SetBranchAddress("hltmatchGamma90", &hltmatchGamma90, &b_hltmatchGamma90);
   fChain->SetBranchAddress("passHLT30", &passHLT30, &b_passHLT30);
   fChain->SetBranchAddress("passHLT50", &passHLT50, &b_passHLT50);
   fChain->SetBranchAddress("passHLT75", &passHLT75, &b_passHLT75);
   fChain->SetBranchAddress("passHLT90", &passHLT90, &b_passHLT90);
   fChain->SetBranchAddress("passHLT135", &passHLT135, &b_passHLT135);
   fChain->SetBranchAddress("passHLT150", &passHLT150, &b_passHLT150);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   Notify();
}

Bool_t turnOnPlots::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void turnOnPlots::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t turnOnPlots::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef turnOnPlots_cxx
