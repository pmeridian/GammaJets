//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 11 21:12:57 2012 by ROOT version 5.30/02
// from TTree AnaTree/Reduced tree for final analysis
// found on file: ../../dati/Hgg/redntp.42xv6b_data.cicloose.regrPho_eCorr_30Nov.v2_jetid/merged/redntp_Photon-Run2011-30Nov2011-v1-DiPhotonSkimOnFly.root
//////////////////////////////////////////////////////////

#ifndef fillPlot2012_gammaJets_h
#define fillPlot2012_gammaJets_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TRandom3.h>

class fillPlot2012_gammaJets {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   //Cuts values                                                                
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
   Float_t         nvtx;
   Float_t         rhoPF;
   Float_t         rhoAllJets;
   Int_t           npu;
   Float_t         pu_weight;
   Float_t         gen_pt_gamma1;
   Float_t         gen_eta_gamma1;
   Float_t         gen_phi_gamma1;
   Int_t           oneLooseIsoMu;
   Int_t           oneTightIsoMu;
   Int_t           oneWP80Ele;
   Int_t           oneWP90Ele;
   Int_t           oneHwwEle;
   Int_t           oneHzzEle;
   Int_t           njets;
   Float_t         ecorrjet[9];   //[njets] 
   Float_t         ptjet[9];   //[njets] 
   Float_t         ptcorrjet[9];   //[njets] 
   Float_t         etajet[9];   //[njets] 
   Float_t         phijet[9];   //[njets] 
   Float_t         betajet[9];   //[njets] 
   Float_t         betastarjet[9];   //[njets] 
   Float_t         rmsjet[9];   //[njets]   
   Int_t           matchingMu[9];   //[njets]                                                                                      
   Int_t           matchingEle[9];   //[njets]                                                                                     
   Int_t           ngammas;
   Float_t         dRGenphot[9];
   Float_t         ptphot[9];
   Float_t         etaphot[9];
   Float_t         phiphot[9];
   Float_t         etascphot[9];
   Float_t         E1phot[9];
   Float_t         E9phot[9];
   Float_t         r9phot[9];
   Float_t         deltaRToTrackphot[9];
   Int_t           pid_haspixelseedphot[9];
   Float_t         pid_HoverEphot[9];
   Float_t         pid_sigmaIeIephot[9];
   Float_t         pid_hlwTrack04phot[9];
   Float_t         pid_jurECAL04phot[9];
   Float_t         pid_twrHCAL04phot[9];
   Int_t           pid_hasMatchedConvphot[9];
   Int_t           pid_hasMatchedPromptElephot[9];
   Float_t         pid_pfIsoCharged03phot[9];
   Float_t         pid_pfIsoPhotons03phot[9];
   Float_t         pid_pfIsoNeutrals03phot[9];
   Float_t         pid_pfIsoCharged04phot[9];
   Float_t         pid_pfIsoPhotons04phot[9];
   Float_t         pid_pfIsoNeutrals04phot[9];
   Float_t         pid_deltaRToTrackphot[9];
   Int_t           vtxId;
   Float_t         vtxPos_x;
   Float_t         vtxPos_y;
   Float_t         vtxPos_z;
   Int_t           nHLT;
   vector<string>  *allHLTNames;
   vector<bool>    *allHLTResults;

   // List of branches
   TBranch        *b_run;   //! 
   TBranch        *b_event;   //! 
   TBranch        *b_nvtx;   //! 
   TBranch        *b_rhoPF;   //!     
   TBranch        *b_rhoAllJets;   //! 
   TBranch        *b_npu;   //! 
   TBranch        *b_pu_weight;   //! 
   TBranch        *b_gen_pt_gamma1;   //! 
   TBranch        *b_gen_eta_gamma1;   //! 
   TBranch        *b_gen_phi_gamma1;   //! 
   TBranch        *b_oneLooseIsoMu;   //!                                                                                          
   TBranch        *b_oneTightIsoMu;   //!                                                                                          
   TBranch        *b_oneWP80Ele;   //!                                                                                             
   TBranch        *b_oneWP90Ele;   //!                                                                                             
   TBranch        *b_oneHwwEle;   //!                                                                                              
   TBranch        *b_oneHzzEle;   //!  
   TBranch        *b_njets;   //! 
   TBranch        *b_ecorrjet;   //! 
   TBranch        *b_ptjet;   //! 
   TBranch        *b_ptcorrjet;   //! 
   TBranch        *b_etajet;   //! 
   TBranch        *b_phijet;   //! 
   TBranch        *b_betajet;   //!
   TBranch        *b_betastarjet;   //! 
   TBranch        *b_rmsjet;   //! 
   TBranch        *b_matchingMu;   //!                                                                                             
   TBranch        *b_matchingEle;   //!                                                                                            
   TBranch        *b_ngammas;   //!
   TBranch        *b_dRGenphot;   //! 
   TBranch        *b_ptphot;   //! 
   TBranch        *b_etaphot;   //! 
   TBranch        *b_phiphot;   //! 
   TBranch        *b_etascphot;   //! 
   TBranch        *b_E1phot;   //! 
   TBranch        *b_E9phot;   //! 
   TBranch        *b_r9phot;   //! 
   TBranch        *b_deltaRToTrackphot;   //! 
   TBranch        *b_pid_haspixelseedphot;   //! 
   TBranch        *b_pid_HoverEphot;   //! 
   TBranch        *b_pid_sigmaIeIephot;   //! 
   TBranch        *b_pid_hlwTrack04phot;   //! 
   TBranch        *b_pid_jurECAL04phot;   //! 
   TBranch        *b_pid_twrHCAL04phot;   //! 
   TBranch        *b_pid_hasMatchedConvphot;   //! 
   TBranch        *b_pid_hasMatchedPromptElephot;   //! 
   TBranch        *b_pid_pfIsoCharged03phot;   //! 
   TBranch        *b_pid_pfIsoPhotons03phot;   //! 
   TBranch        *b_pid_pfIsoNeutrals03phot;   //! 
   TBranch        *b_pid_pfIsoCharged04phot;   //! 
   TBranch        *b_pid_pfIsoPhotons04phot;   //! 
   TBranch        *b_pid_pfIsoNeutrals04phot;   //! 
   TBranch        *b_pid_deltaRToTrackphot;   //!    
   TBranch        *b_vtxId;   //! 
   TBranch        *b_vtxPos_x;   //!
   TBranch        *b_vtxPos_y;   //! 
   TBranch        *b_vtxPos_z;   //! 
   TBranch        *b_nHLT;   //!                                                
   TBranch        *b_allHLTNames;   //!                                         
   TBranch        *b_allHLTResults;   //!  

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
};

#endif

#ifdef fillPlot2012_gammaJets_cxx
fillPlot2012_gammaJets::fillPlot2012_gammaJets(TTree *tree)
{
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../dati/Hgg/redntp.42xv6b_data.cicloose.regrPho_eCorr_30Nov.v2_jetid/merged/redntp_Photon-Run2011-30Nov2011-v1-DiPhotonSkimOnFly.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("../../dati/Hgg/redntp.42xv6b_data.cicloose.regrPho_eCorr_30Nov.v2_jetid/merged/redntp_Photon-Run2011-30Nov2011-v1-DiPhotonSkimOnFly.root");
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
  allHLTNames = 0;
  allHLTResults = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("rhoPF", &rhoPF, &b_rhoPF);
   fChain->SetBranchAddress("rhoAllJets", &rhoAllJets, &b_rhoAllJets);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight);
   fChain->SetBranchAddress("gen_pt_gamma1", &gen_pt_gamma1, &b_gen_pt_gamma1);
   fChain->SetBranchAddress("gen_eta_gamma1", &gen_eta_gamma1, &b_gen_eta_gamma1);
   fChain->SetBranchAddress("gen_phi_gamma1", &gen_phi_gamma1, &b_gen_phi_gamma1);
   fChain->SetBranchAddress("oneLooseIsoMu", &oneLooseIsoMu, &b_oneLooseIsoMu);
   fChain->SetBranchAddress("oneTightIsoMu", &oneTightIsoMu, &b_oneTightIsoMu);
   fChain->SetBranchAddress("oneWP80Ele", &oneWP80Ele, &b_oneWP80Ele);
   fChain->SetBranchAddress("oneWP90Ele", &oneWP90Ele, &b_oneWP90Ele);
   fChain->SetBranchAddress("oneHwwEle", &oneHwwEle, &b_oneHwwEle);
   fChain->SetBranchAddress("oneHzzEle", &oneHzzEle, &b_oneHzzEle);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("ecorrjet", ecorrjet, &b_ecorrjet);
   fChain->SetBranchAddress("ptjet", ptjet, &b_ptjet);
   fChain->SetBranchAddress("ptcorrjet", ptcorrjet, &b_ptcorrjet);
   fChain->SetBranchAddress("etajet", etajet, &b_etajet);
   fChain->SetBranchAddress("phijet", phijet, &b_phijet);
   fChain->SetBranchAddress("betajet", betajet, &b_betajet);
   fChain->SetBranchAddress("betastarjet", betastarjet, &b_betastarjet);
   fChain->SetBranchAddress("rmsjet", rmsjet, &b_rmsjet);
   fChain->SetBranchAddress("matchingMu", matchingMu, &b_matchingMu);
   fChain->SetBranchAddress("matchingEle", matchingEle, &b_matchingEle);
   fChain->SetBranchAddress("ngammas", &ngammas, &b_ngammas);
   fChain->SetBranchAddress("dRGenphot", dRGenphot, &b_dRGenphot);
   fChain->SetBranchAddress("ptphot", ptphot, &b_ptphot);
   fChain->SetBranchAddress("etaphot", etaphot, &b_etaphot);
   fChain->SetBranchAddress("phiphot", phiphot, &b_phiphot);
   fChain->SetBranchAddress("etascphot", etascphot, &b_etascphot);
   fChain->SetBranchAddress("E1phot", E1phot, &b_E1phot);
   fChain->SetBranchAddress("E9phot", E9phot, &b_E9phot);
   fChain->SetBranchAddress("r9phot", r9phot, &b_r9phot);
   fChain->SetBranchAddress("deltaRToTrackphot", deltaRToTrackphot, &b_deltaRToTrackphot);
   fChain->SetBranchAddress("pid_haspixelseedphot", pid_haspixelseedphot, &b_pid_haspixelseedphot);
   fChain->SetBranchAddress("pid_HoverEphot", pid_HoverEphot, &b_pid_HoverEphot);
   fChain->SetBranchAddress("pid_sigmaIeIephot", pid_sigmaIeIephot, &b_pid_sigmaIeIephot);
   fChain->SetBranchAddress("pid_hlwTrack04phot", pid_hlwTrack04phot, &b_pid_hlwTrack04phot);
   fChain->SetBranchAddress("pid_jurECAL04phot", pid_jurECAL04phot, &b_pid_jurECAL04phot);
   fChain->SetBranchAddress("pid_twrHCAL04phot", pid_twrHCAL04phot, &b_pid_twrHCAL04phot);
   fChain->SetBranchAddress("pid_hasMatchedConvphot", pid_hasMatchedConvphot, &b_pid_hasMatchedConvphot);
   fChain->SetBranchAddress("pid_hasMatchedPromptElephot", pid_hasMatchedPromptElephot, &b_pid_hasMatchedPromptElephot);
   fChain->SetBranchAddress("pid_pfIsoCharged03phot", pid_pfIsoCharged03phot, &b_pid_pfIsoCharged03phot);
   fChain->SetBranchAddress("pid_pfIsoPhotons03phot", pid_pfIsoPhotons03phot, &b_pid_pfIsoPhotons03phot);
   fChain->SetBranchAddress("pid_pfIsoNeutrals03phot", pid_pfIsoNeutrals03phot, &b_pid_pfIsoNeutrals03phot);
   fChain->SetBranchAddress("pid_pfIsoCharged04phot", pid_pfIsoCharged04phot, &b_pid_pfIsoCharged04phot);
   fChain->SetBranchAddress("pid_pfIsoPhotons04phot", pid_pfIsoPhotons04phot, &b_pid_pfIsoPhotons04phot);
   fChain->SetBranchAddress("pid_pfIsoNeutrals04phot", pid_pfIsoNeutrals04phot, &b_pid_pfIsoNeutrals04phot);
   fChain->SetBranchAddress("pid_deltaRToTrackphot", pid_deltaRToTrackphot, &b_pid_deltaRToTrackphot);
   fChain->SetBranchAddress("vtxId", &vtxId, &b_vtxId);
   fChain->SetBranchAddress("vtxPos_x", &vtxPos_x, &b_vtxPos_x);
   fChain->SetBranchAddress("vtxPos_y", &vtxPos_y, &b_vtxPos_y);
   fChain->SetBranchAddress("vtxPos_z", &vtxPos_z, &b_vtxPos_z);
   fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
   fChain->SetBranchAddress("allHLTNames", &allHLTNames, &b_allHLTNames);
   fChain->SetBranchAddress("allHLTResults", &allHLTResults, &b_allHLTResults);
   
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
