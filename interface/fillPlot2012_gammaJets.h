//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  6 17:13:02 2013 by ROOT version 5.32/00
// from TTree AnaTree/Reduced tree for final analysis
// found on file: redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6_69.root
//////////////////////////////////////////////////////////

#ifndef fillPlot2012_gammaJets_h
#define fillPlot2012_gammaJets_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>
#include <vector>

class fillPlot2012_gammaJets {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Cuts values                   
   double ptphot1cut;
   int ebcat;
   int r9cat;

   // bool to decide if we want to write output txt file 
   std::string writetxt;
   std::string writeRoot;

   // bool for switching on smearing and smearing parameters 
   bool dopureweight;

   // vector of pu weights 
   std::vector<Double_t> puweights_;
   double weights_[15][15];

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
   Float_t         ptPhot_presel[100];   //[nPhot_presel]
   Float_t         ePhot_presel[100];   //[nPhot_presel]
   Float_t         etascPhot_presel  [100];   //[nPhot_presel]
   Float_t         etaPhot_presel[100];   //[nPhot_presel]
   Float_t         phiPhot_presel[100];   //[nPhot_presel]
   Float_t         pid_jurECAL03_presel[100];   //[nPhot_presel]
   Float_t         pid_twrHCAL03_presel[100];   //[nPhot_presel]
   Float_t         pid_hlwTrack03_presel[100];   //[nPhot_presel]
   Float_t         pid_jurECAL04_presel[100];   //[nPhot_presel]
   Float_t         pid_twrHCAL04_presel[100];   //[nPhot_presel]
   Float_t         pid_hlwTrack04_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged01ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged02ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged03ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged04ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged05ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoCharged06ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons01ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons02ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons03ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons04ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons05ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoPhotons06ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals01ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals02ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals03ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals04ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals05ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_pfIsoNeutrals06ForCiC_presel[100];   //[nPhot_presel]
   Float_t         pid_scetawid_presel[100];   //[nPhot_presel]
   Float_t         pid_scphiwid_presel[100];   //[nPhot_presel]
   Float_t         pid_lambdaRatio_presel[100];   //[nPhot_presel]
   Float_t         pid_HoverE_presel[100];   //[nPhot_presel]
   Float_t         sEtaEtaPhot_presel[100];   //[nPhot_presel]
   Float_t         sEtaPhiPhot_presel[100];   //[nPhot_presel]
   Float_t         s4RatioPhot_presel[100];   //[nPhot_presel]
   Float_t         r9Phot_presel[100];   //[nPhot_presel]
   Float_t         rhoAllJets;
   Float_t         rhoPF;
   Float_t         rr_presel[100];   //[nPhot_presel]
   Int_t           isMatchedPhot[100];   //[nPhot_presel]
   Float_t         deltaRGenReco[100];   //[nPhot_gen]
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

   fillPlot2012_gammaJets(TTree *tree=0);
   virtual ~fillPlot2012_gammaJets();
   virtual void     getweights();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Setcuts(double pt1=50, int eb = 1, int r9 = 1);
   virtual TH1D*    Plot(string var, string name, int nbin=200, double min=90, double max=190, int signal=50);
   virtual void     Writetxt(char * filename);
   virtual void     WriteRoot(char * filename);
   virtual void     SetPuWeights(bool isData = 0,std::string file = "");
   virtual void     DoPuReweight();
   virtual Bool_t   Notify();

   bool isHLT_50();
   bool isHLT_75();
   bool isHLT_150();
   int effectiveAreaRegion(float theEta);
};

#endif

#ifdef fillPlot2012_gammaJets_cxx
fillPlot2012_gammaJets::fillPlot2012_gammaJets(TTree *tree) 
{
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6_69.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6_69.root");
      }
      f->GetObject("AnaTree",tree);

   }
   Init(tree);
   writetxt = "";
   writeRoot = "";
   dopureweight = 0;
}

fillPlot2012_gammaJets::~fillPlot2012_gammaJets()
{
   if (!fChain) return;
}

Int_t fillPlot2012_gammaJets::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fillPlot2012_gammaJets::LoadTree(Long64_t entry)
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

void fillPlot2012_gammaJets::Init(TTree *tree)
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

Bool_t fillPlot2012_gammaJets::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef fillPlot2012_gammaJets_cxx
