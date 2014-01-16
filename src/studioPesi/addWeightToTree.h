//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 12 17:53:02 2013 by ROOT version 5.32/00
// from TTree TreeIsoAndMVAInputs/TreeIsoAndMVAInputs
// found on file: /cmshome/gdimperi/GammaJet/CMSSW_5_3_11/src/GammaJets/tuples/finalized/redntp.53xv6_CERN.gjetpresel.noCorr.v1_withisoGen/G_Pt-15to30_8TeV_pythia6_hltcut30_hltiso0_mvaWP3.root
//////////////////////////////////////////////////////////

#ifndef addWeightToTree_h
#define addWeightToTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class addWeightToTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // new weight
   float isoW_EB_t;
   float isoW_EE_t;
   float isoW_EB_pt40_65_t;
   float isoW_EE_pt40_65_t;
   float isoW_EB_pt65_90_t;
   float isoW_EE_pt65_90_t;
   float isoW_EB_pt90_105_t;
   float isoW_EE_pt90_105_t;
   float isoW_EB_pt105_t;
   float isoW_EE_pt105_t;

   // Declaration of leaf types
   UInt_t          sampleIndex;
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   UInt_t          nvtx;
   Float_t         weight;
   Float_t         rho;
   Float_t         ptPhot;
   Int_t           isMatchedPhot;
   Int_t           isIsolatedGenPhot;
   Int_t           isPassedMVA;
   Float_t         etaPhot;
   Float_t         mvaIdPhot;
   Float_t         combinedPfIso03Phot;
   Float_t         sEtaEtaPhot;
   Float_t         sEtaPhiPhot;
   Float_t         scEtawid;
   Float_t         scPhiwid;
   Float_t         s4RatioPhot;
   Float_t         R9Phot;
   Float_t         sigmaRR;
   Float_t         iso03_gen;
   Float_t         pid_jurECAL03;
   Float_t         pid_twrHCAL03;
   Float_t         pid_hlwTrack03;
   Float_t         pid_pfIsoCharged03ForCiC;
   Float_t         pid_pfIsoPhotons03ForCiC;
   Float_t         pid_pfIsoNeutrals03ForCiC;
   Float_t         pid_pfIsoFPRCharged03_presel;
   Float_t         pid_pfIsoFPRNeutral03_presel;
   Float_t         pid_pfIsoFPRPhoton03_presel;
   Float_t         combinedPfIsoFPR03Phot;
   Float_t         pid_pfIsoFPRRandomConeCharged03_presel;
   Float_t         pid_pfIsoFPRRandomConeNeutral03_presel;
   Float_t         pid_pfIsoFPRRandomConePhoton03_presel;
   Float_t         combinedPfIsoFPRRandomCone03Phot;
   Float_t         correctedPfIsoCharged03;
   Float_t         correctedPfIsoNeutrals03;
   Float_t         correctedPfIsoPhotons03;
   Float_t         correctedPfIsoFPRCharged03;
   Float_t         correctedPfIsoFPRNeutrals03;
   Float_t         correctedPfIsoFPRPhotons03;
   Float_t         correctedPfIsoFPRRandomConeCharged03;
   Float_t         correctedPfIsoFPRRandomConeNeutrals03;
   Float_t         correctedPfIsoFPRRandomConePhotons03;

   // List of branches
   TBranch        *b_sampleIndex;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_weght;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_ptPhot;   //!
   TBranch        *b_isMatchedPhot;   //!
   TBranch        *b_isIsolatedGenPhot;   //!
   TBranch        *b_isPassedMVA;   //!
   TBranch        *b_etaPhot;   //!
   TBranch        *b_mvaIdPhot;   //!
   TBranch        *b_combinedPfIso03Phot;   //!
   TBranch        *b_sEtaEtaPhot;   //!
   TBranch        *b_sEtaPhiPhot;   //!
   TBranch        *b_scEtawid;   //!
   TBranch        *b_scPhiwid;   //!
   TBranch        *b_s4RatioPhot;   //!
   TBranch        *b_R9Phot;   //!
   TBranch        *b_sigmaRR;   //!
   TBranch        *b_iso03_gen;   //!
   TBranch        *b_pid_jurECAL03;   //!
   TBranch        *b_pid_twrHCAL03;   //!
   TBranch        *b_pid_hlwTrack03;   //!
   TBranch        *b_pid_pfIsoCharged03ForCiC;   //!
   TBranch        *b_pid_pfIsoPhotons03ForCiC;   //!
   TBranch        *b_pid_pfIsoNeutrals03ForCiC;   //!
   TBranch        *b_pid_pfIsoFPRCharged03_presel;   //!
   TBranch        *b_pid_pfIsoFPRNeutral03_presel;   //!
   TBranch        *b_pid_pfIsoFPRPhoton03_presel;   //!
   TBranch        *b_combinedPfIsoFPR03Phot;   //!
   TBranch        *b_pid_pfIsoFPRRandomConeCharged03_presel;   //!
   TBranch        *b_pid_pfIsoFPRRandomConeNeutral03_presel;   //!
   TBranch        *b_pid_pfIsoFPRRandomConePhoton03_presel;   //!
   TBranch        *b_combinedPfIsoFPRRandomCone03Phot;   //!
   TBranch        *b_correctedPfIsoCharged03;   //!
   TBranch        *b_correctedPfIsoNeutrals03;   //!
   TBranch        *b_correctedPfIsoPhotons03;   //!
   TBranch        *b_correctedPfIsoFPRCharged03;   //!
   TBranch        *b_correctedPfIsoFPRNeutrals03;   //!
   TBranch        *b_correctedPfIsoFPRPhotons03;   //!
   TBranch        *b_correctedPfIsoFPRRandomConeCharged03;   //!
   TBranch        *b_correctedPfIsoFPRRandomConeNeutrals03;   //!
   TBranch        *b_correctedPfIsoFPRRandomConePhotons03;   //!

   addWeightToTree(TTree *tree=0);
   virtual ~addWeightToTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void createBranches(TTree* treeWithWeights);
};

#endif

#ifdef addWeightToTree_cxx
addWeightToTree::addWeightToTree(TTree *tree) : fChain(0) 
{
  if (tree == 0) {
    
    TChain *chain = new TChain("finalTree","");
    
    // G+jets                                                                                                                            
    // chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/G_Pt*root");
    // qcd
    // chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/QCDEM*root");
    // data
    // chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/*2012A*root");
    // chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/*2012B*root");
    // chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/*2012C*root");
    chain->Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/*2012D*root");
    
    tree = chain;
  }
  Init(tree);
}

addWeightToTree::~addWeightToTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t addWeightToTree::GetEntry(Long64_t entry)
{
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t addWeightToTree::LoadTree(Long64_t entry)
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

void addWeightToTree::Init(TTree *tree)
{
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("sampleIndex", &sampleIndex, &b_sampleIndex);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
  fChain->SetBranchAddress("weight", &weight, &b_weght);
  fChain->SetBranchAddress("rho", &rho, &b_rho);
  fChain->SetBranchAddress("ptPhot", &ptPhot, &b_ptPhot);
  fChain->SetBranchAddress("isMatchedPhot", &isMatchedPhot, &b_isMatchedPhot);
  fChain->SetBranchAddress("isIsolatedGenPhot", &isIsolatedGenPhot, &b_isIsolatedGenPhot);
  fChain->SetBranchAddress("isPassedMVA", &isPassedMVA, &b_isPassedMVA);
  fChain->SetBranchAddress("etaPhot", &etaPhot, &b_etaPhot);
  fChain->SetBranchAddress("mvaIdPhot", &mvaIdPhot, &b_mvaIdPhot);
  fChain->SetBranchAddress("combinedPfIso03Phot", &combinedPfIso03Phot, &b_combinedPfIso03Phot);
  fChain->SetBranchAddress("sEtaEtaPhot", &sEtaEtaPhot, &b_sEtaEtaPhot);
  fChain->SetBranchAddress("sEtaPhiPhot", &sEtaPhiPhot, &b_sEtaPhiPhot);
  fChain->SetBranchAddress("scEtawid", &scEtawid, &b_scEtawid);
  fChain->SetBranchAddress("scPhiwid", &scPhiwid, &b_scPhiwid);
  fChain->SetBranchAddress("s4RatioPhot", &s4RatioPhot, &b_s4RatioPhot);
  fChain->SetBranchAddress("R9Phot", &R9Phot, &b_R9Phot);
  fChain->SetBranchAddress("sigmaRR", &sigmaRR, &b_sigmaRR);
  fChain->SetBranchAddress("iso03_gen", &iso03_gen, &b_iso03_gen);
  fChain->SetBranchAddress("pid_jurECAL03", &pid_jurECAL03, &b_pid_jurECAL03);
  fChain->SetBranchAddress("pid_twrHCAL03", &pid_twrHCAL03, &b_pid_twrHCAL03);
  fChain->SetBranchAddress("pid_hlwTrack03", &pid_hlwTrack03, &b_pid_hlwTrack03);
  fChain->SetBranchAddress("pid_pfIsoCharged03ForCiC", &pid_pfIsoCharged03ForCiC, &b_pid_pfIsoCharged03ForCiC);
  fChain->SetBranchAddress("pid_pfIsoPhotons03ForCiC", &pid_pfIsoPhotons03ForCiC, &b_pid_pfIsoPhotons03ForCiC);
  fChain->SetBranchAddress("pid_pfIsoNeutrals03ForCiC", &pid_pfIsoNeutrals03ForCiC, &b_pid_pfIsoNeutrals03ForCiC);
  fChain->SetBranchAddress("pid_pfIsoFPRCharged03_presel", &pid_pfIsoFPRCharged03_presel, &b_pid_pfIsoFPRCharged03_presel);
  fChain->SetBranchAddress("pid_pfIsoFPRNeutral03_presel", &pid_pfIsoFPRNeutral03_presel, &b_pid_pfIsoFPRNeutral03_presel);
  fChain->SetBranchAddress("pid_pfIsoFPRPhoton03_presel", &pid_pfIsoFPRPhoton03_presel, &b_pid_pfIsoFPRPhoton03_presel);
  fChain->SetBranchAddress("combinedPfIsoFPR03Phot", &combinedPfIsoFPR03Phot, &b_combinedPfIsoFPR03Phot);
  fChain->SetBranchAddress("pid_pfIsoFPRRandomConeCharged03_presel", &pid_pfIsoFPRRandomConeCharged03_presel, &b_pid_pfIsoFPRRandomConeCharged03_presel);
  fChain->SetBranchAddress("pid_pfIsoFPRRandomConeNeutral03_presel", &pid_pfIsoFPRRandomConeNeutral03_presel, &b_pid_pfIsoFPRRandomConeNeutral03_presel);
  fChain->SetBranchAddress("pid_pfIsoFPRRandomConePhoton03_presel", &pid_pfIsoFPRRandomConePhoton03_presel, &b_pid_pfIsoFPRRandomConePhoton03_presel);
  fChain->SetBranchAddress("combinedPfIsoFPRRandomCone03Phot", &combinedPfIsoFPRRandomCone03Phot, &b_combinedPfIsoFPRRandomCone03Phot);
  fChain->SetBranchAddress("correctedPfIsoCharged03", &correctedPfIsoCharged03, &b_correctedPfIsoCharged03);
  fChain->SetBranchAddress("correctedPfIsoNeutrals03", &correctedPfIsoNeutrals03, &b_correctedPfIsoNeutrals03);
  fChain->SetBranchAddress("correctedPfIsoPhotons03", &correctedPfIsoPhotons03, &b_correctedPfIsoPhotons03);
  fChain->SetBranchAddress("correctedPfIsoFPRCharged03", &correctedPfIsoFPRCharged03, &b_correctedPfIsoFPRCharged03);
  fChain->SetBranchAddress("correctedPfIsoFPRNeutrals03", &correctedPfIsoFPRNeutrals03, &b_correctedPfIsoFPRNeutrals03);
  fChain->SetBranchAddress("correctedPfIsoFPRPhotons03", &correctedPfIsoFPRPhotons03, &b_correctedPfIsoFPRPhotons03);
  fChain->SetBranchAddress("correctedPfIsoFPRRandomConeCharged03", &correctedPfIsoFPRRandomConeCharged03, &b_correctedPfIsoFPRRandomConeCharged03);
  fChain->SetBranchAddress("correctedPfIsoFPRRandomConeNeutrals03", &correctedPfIsoFPRRandomConeNeutrals03, &b_correctedPfIsoFPRRandomConeNeutrals03);
  fChain->SetBranchAddress("correctedPfIsoFPRRandomConePhotons03", &correctedPfIsoFPRRandomConePhotons03, &b_correctedPfIsoFPRRandomConePhotons03);
  Notify();
}

Bool_t addWeightToTree::Notify()
{
  return kTRUE;
}

void addWeightToTree::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t addWeightToTree::Cut(Long64_t entry)
{
  return 1;
}

void addWeightToTree::createBranches(TTree* treeWithWeights){

  treeWithWeights->Branch("etaPhot", &etaPhot, "etaPhot/F");
  treeWithWeights->Branch("ptPhot",  &ptPhot,  "ptPhot/F");
  treeWithWeights->Branch("mvaIdPhot", &mvaIdPhot, "mvaIdPhot/F");
  treeWithWeights->Branch("isMatchedPhot", &isMatchedPhot, "isMatchedPhot/I");
  treeWithWeights->Branch("iso03_gen", &iso03_gen, "iso03_gen/F");
  treeWithWeights->Branch("combinedPfIsoFPR03Phot", &combinedPfIsoFPR03Phot, "combinedPfIsoFPR03Phot/F");
  treeWithWeights->Branch("weight", &weight, "weight/F");
  treeWithWeights->Branch("isoW_EB", &isoW_EB_t, "isoW_EB/F");
  treeWithWeights->Branch("isoW_EE", &isoW_EE_t, "isoW_EE/F");
  treeWithWeights->Branch("isoW_EB_pt40_65",  &isoW_EB_pt40_65_t,  "isoW_EB_pt40_65/F");
  treeWithWeights->Branch("isoW_EE_pt40_65",  &isoW_EE_pt40_65_t,  "isoW_EE_pt40_65/F");
  treeWithWeights->Branch("isoW_EB_pt65_90",  &isoW_EB_pt65_90_t,  "isoW_EB_pt65_90/F");
  treeWithWeights->Branch("isoW_EE_pt65_90",  &isoW_EE_pt65_90_t,  "isoW_EE_pt65_90/F");
  treeWithWeights->Branch("isoW_EB_pt90_105", &isoW_EB_pt90_105_t, "isoW_EB_pt90_105/F");
  treeWithWeights->Branch("isoW_EE_pt90_105", &isoW_EE_pt90_105_t, "isoW_EE_pt90_105/F");
  treeWithWeights->Branch("isoW_EB_pt105",    &isoW_EB_pt105_t,    "isoW_EB_pt105/F");
  treeWithWeights->Branch("isoW_EE_pt105",    &isoW_EE_pt105_t,    "isoW_EE_pt105/F");
}

#endif // #ifdef addWeightToTree_cxx
