#include "TagAndProbeTree.h"
#include "EnergyScaleCorrection.h"
#include "JSON.h"
#include <TH2.h>
#include <TStyle.h>
#include <TString.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

#define MAX_PU_REWEIGHT 60

using std::cout;
using std::endl;


TagAndProbeTree::TagAndProbeTree(TTree *tree, const TString& outname) : tree_reader_V8(tree), jsonFile(0) //, scaleCorrections_(0)
{  
  hOutputFile = TFile::Open(outname, "RECREATE" ) ;
  
  // must be set by the user 
  EquivLumi = -1.;
  xsection = -1.;
  NtotEvents = -1;
  SampleID = -1;
  gen_=new TRandom3(0);
  
  //tmvaReaderID_Single_Endcap=0;
  //tmvaReaderID_Single_Barrel=0;
}

TagAndProbeTree::~TagAndProbeTree() {
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
}

vector<int> TagAndProbeTree::firstones(Float_t *vec, vector<bool> *asso, int number){
  
  vector<int> themax;
  
  for(int j=0; j<number; j++) {
    double maxtemp(-999); 
    int idmaxtemp(-999);

    for (int i=0; i<int(asso->size()); i++) {
      bool skip(0);
      for(int ss=0; ss<j; ss++) { 
	if ( i == themax.at(ss) )   
	  skip = 1;
      }
      if ( vec[i] > maxtemp && asso->at(i) && !skip) {
	maxtemp = vec[i];
	idmaxtemp = i;
      }
    }
    themax.push_back(idmaxtemp);
  }
  return themax;
}




void TagAndProbeTree::Loop() {


  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;


  JSON* myjson=0;
  if (jsonFile) {
    std::cout << "Reading JSON :: " << jsonFile << std::endl;
    myjson=new JSON(jsonFile);
  }


  cout << "json file assigned" << endl; 

  hOutputFile->cd();   
  
  /********************************************************/
  TH1D elegen1("elegen1","elegen1", 100, 0.,300.);
  
  
  /********************************************************
   *                                                      *
   *                      TREE INIT                       *
   *                                                      *
   ********************************************************/


  
  ana_tree = new TTree ("AnaTree","Reduced tree for final analysis");
  //ana_tree = new TTree ("AnaTree","Reduced tree for final analysis, 2") ;
  // general

  //output BDT
  Float_t         BDT_output[20]; 
  Float_t         r9Phot[20];     
  Float_t         s4RatioPhot[20];
  Float_t         sigmaRRPhot[20];


  //isocharged using the vertex 0
  Float_t         pid_pfIsoCharged01ForCiC_[20];
  Float_t         pid_pfIsoCharged02ForCiC_[20];
  Float_t         pid_pfIsoCharged03ForCiC_[20];
  Float_t         pid_pfIsoCharged04ForCiC_[20];
  Float_t         pid_pfIsoCharged05ForCiC_[20];
  Float_t         pid_pfIsoCharged06ForCiC_[20]; 

  //pass preselection
  Int_t           passPreselection[20];
  
  //electrons
 
  Int_t           isEleTag_match[20];
  Int_t           isEleProbe_match[20];
  Int_t           isEleProbe_ele_match[20];
  Int_t           passLooseElePtEta_match[20];
  Int_t           passLooseEleID_match[20];
  Int_t           passLooseEleImpactPar_match[20];
  Int_t           passLooseEleIsoRel_match[20];
  Int_t           passLooseEleMinHits_match[20];
  Int_t           passMediumElePtEta_match[20];
  Int_t           passMediumEleID_match[20];
  Int_t           passMediumEleImpactPar_match[20];
  Int_t           passMediumEleIsoRel_match[20];
  Int_t           passMediumEleMinHits_match[20];
  Int_t           passTightElePtEta_match[20];
  Int_t           passTightEleID_match[20];
  Int_t           passTightEleImpactPar_match[20];
  Int_t           passTightEleIsoRel_match[20];
  Int_t           passTightEleMinHits_match[20];

  Int_t           genEleMatched_index_tag[20];
  Int_t           genEleMatched_index_probe[20];
  Float_t         deltaR_EleTagGenReco[20];
  Float_t         deltaR_EleProbeGenReco[20];
  Float_t         invMassEle_match[20];

  Int_t           isEleTag[20];
  Int_t           isEleProbe[20];
  Int_t           isEleProbe_ele[20];
  Float_t         invMassEle[20];

  Int_t           passLooseElePtEta[20];
  Int_t           passLooseEleID[20];
  Int_t           passLooseEleImpactPar[20];
  Int_t           passLooseEleIsoRel[20];
  Int_t           passLooseEleMinHits[20];
  Int_t           passMediumElePtEta[20];
  Int_t           passMediumEleID[20];
  Int_t           passMediumEleImpactPar[20];
  Int_t           passMediumEleIsoRel[20];
  Int_t           passMediumEleMinHits[20];
  Int_t           passTightElePtEta[20];
  Int_t           passTightEleID[20];
  Int_t           passTightEleImpactPar[20];
  Int_t           passTightEleIsoRel[20];
  Int_t           passTightEleMinHits[20];
  
  cout << "Definisco i branch" << endl;
    
  ana_tree->Branch("run",&runRN,"run/I");
  ana_tree->Branch("event",&eventRN,"event/I");
  ana_tree->Branch("lumi",&lumi,"lumi/I");
  ana_tree->Branch("isMC",&isMC,"isMC/I");
  ana_tree->Branch("nvtx",&nvtx,"nvtx/F");
  // vertex
  ana_tree->Branch("vtxId",   &vtxId,   "vtxId/I");

  ana_tree->Branch("npu",&npu,"npu/I");
  ana_tree->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree->Branch("xsection",&xsection,"xsection/F");
  ana_tree->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree->Branch("SampleID",&SampleID,"SampleID/I");
  ana_tree->Branch("pu_weight",&pu_weight,"pu_weight/F");
  ana_tree->Branch("pu_weight30",&pu_weight30,"pu_weight30/F");
  ana_tree->Branch("pu_weight50",&pu_weight50,"pu_weight50/F");
  ana_tree->Branch("pu_weight75",&pu_weight75,"pu_weight75/F");
  ana_tree->Branch("pu_weight90",&pu_weight90,"pu_weight90/F");

  ana_tree->Branch("LOGamma",    &LOGamma,    "LOGamma/I");
  ana_tree->Branch("ISRGamma",   &ISRGamma,   "ISRGamma/I");
  ana_tree->Branch("FSRGamma",   &FSRGamma,   "FSRGamma/I");


  ana_tree->Branch("rhoAllJets",&rhoAllJets,"rhoAllJets/F");
  ana_tree->Branch("rhoPF",&rhoPF,"rhoPF/F");		   



  //electrons (for tag)
  ana_tree->Branch("nEle",&nEle, "nEle/I");
  ana_tree->Branch("electron_pt",    electron_pt    ,"electron_pt[nEle]/F");
  ana_tree->Branch("electron_energy",electron_energy,"electron_energy[nEle]/F");
  ana_tree->Branch("electron_phi",   electron_phi   ,"electron_phi[nEle]/F");
  ana_tree->Branch("electron_eta",   electron_eta   ,"electron_eta[nEle]/F");
  ana_tree->Branch("electron_EoP",                   electron_EoP		    , "electron_EoP[nEle]/F");
  ana_tree->Branch("electron_OneOverEMinusOneOverP", electron_OneOverEMinusOneOverP, "electron_OneOverEMinusOneOverP[nEle]/F");
  ana_tree->Branch("electron_r9"                   , electron_r9		    , "electron_r9[nEle]/F");
  ana_tree->Branch("electron_SigmaIetaIeta"        , electron_SigmaIetaIeta	    , "electron_SigmaIetaIeta[nEle]/F");
  ana_tree->Branch("electron_dEtaIn"               , electron_dEtaIn		    , "electron_dEtaIn[nEle]/F");
  ana_tree->Branch("electron_dPhiIn"               , electron_dPhiIn		    , "electron_dPhiIn[nEle]/F");              
  ana_tree->Branch("electron_HoE"                  , electron_HoE		    , "electron_HoE[nEle]/F");
  ana_tree->Branch("electron_sc_eta"               , electron_sc_eta               , "electron_sc_eta[nEle]/F");                 
  ana_tree->Branch("electron_trkIso"    , electron_trkIso    ,"electron_trkIso[nEle]/F"    );
  ana_tree->Branch("electron_ecalIso"   , electron_ecalIso   ,"electron_ecalIso[nEle]/F"   );
  ana_tree->Branch("electron_hcalIso"   , electron_hcalIso   ,"electron_hcalIso[nEle]/F"   );
  ana_tree->Branch("electron_trkIso03"  , electron_trkIso03  ,"electron_trkIso03[nEle]/F"  );
  ana_tree->Branch("electron_ecalIso03" , electron_ecalIso03 ,"electron_ecalIso03[nEle]/F" );
  ana_tree->Branch("electron_hcalIso03" , electron_hcalIso03 ,"electron_hcalIso03[nEle]/F" );
  ana_tree->Branch("electron_chHad03Iso", electron_chHad03Iso,"electron_chHad03Iso[nEle]/F");
  ana_tree->Branch("electron_nHad03Iso" , electron_nHad03Iso ,"electron_nHad03Iso[nEle]/F" );
  ana_tree->Branch("electron_phot03Iso" , electron_phot03Iso ,"electron_phot03Iso[nEle]/F" );
  ana_tree->Branch("electron_chHad04Iso", electron_chHad04Iso,"electron_chHad04Iso[nEle]/F");
  ana_tree->Branch("electron_nHad04Iso" , electron_nHad04Iso ,"electron_nHad04Iso[nEle]/F" );
  ana_tree->Branch("electron_phot04Iso" , electron_phot04Iso ,"electron_phot04Iso[nEle]/F" );
  ana_tree->Branch("electron_chHad05Iso", electron_chHad05Iso,"electron_chHad05Iso[nEle]/F");
  ana_tree->Branch("electron_nHad05Iso" , electron_nHad05Iso ,"electron_nHad05Iso[nEle]/F" );
  ana_tree->Branch("electron_phot05Iso" , electron_phot05Iso ,"electron_phot05Iso[nEle]/F" );
  

  //photons (for probe)
  ana_tree->Branch("nPhot", &nPhot, "nPhot/I");
  ana_tree->Branch("ptPhot", ptPhot, "ptPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ePhot", ePhot,  "ePhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escPhot", escPhot, "escPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escRegrPhot", escRegrPhot, "escRegrPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escRegrPhotError", escRegrPhotError, "escRegrPhotError[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escPhFixPhot", escPhFixPhot, "escPhFixPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escPhFixPhotError", escPhFixPhotError, "escPhFixPhotError[nPhot]/F");   //[nPhot]
  ana_tree->Branch("escRawPhot", escRawPhot, "escRawPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("etascPhot", etascPhot, "etascPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("phiscPhot", phiscPhot, "phiscPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("xscPhot", phiscPhot, "phiscPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("yscPhot", yscPhot, "yscPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("zscPhot", zscPhot, "zscPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("xcaloPhot", xcaloPhot, "xcaloPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ycaloPhot", ycaloPhot, "ycaloPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("zcaloPhot", zcaloPhot, "zcaloPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("eseedPhot", eseedPhot, "eseedPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("etaPhot", etaPhot, "etaPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("phiPhot", phiPhot, "phiPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("timePhot", timePhot, "timePhot/F"[nPhot]);   //[nPhot]
  ana_tree->Branch("e4SwissCrossPhot",e4SwissCrossPhot, "e4SwissCrossPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("hasPixelSeedPhot", hasPixelSeedPhot, "hasPixelSeedPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("hasMatchedPromptElePhot", hasMatchedPromptElePhot, "hasMatchedPromptElePhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("hasMatchedConvPhot", hasMatchedConvPhot, "hasMatchedConvPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("isEBPhot", isEBPhot, "isEBPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("isEEPhot", isEEPhot, "isEEPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("isEBEEGapPhot", isEBEEGapPhot, "isEBEEGapPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("ntracksConvPhot", ntracksConvPhot, "ntracksConvPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("isValidVtxConvPhot", isValidVtxConvPhot, "isValidVtxConvPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pairInvmassConvPhot", pairInvmassConvPhot, "pairInvmassConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pairCotThetaSeperationConvPhot", pairCotThetaSeperationConvPhot, "pairCotThetaSeperationConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pairmomentumXConvPhot", pairmomentumXConvPhot, "pairmomentumXConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pairmomentumYConvPhot", pairmomentumYConvPhot, "pairmomentumYConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pairmomentumZConvPhot", pairmomentumZConvPhot, "pairmomentumZConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("chi2ConvPhot", chi2ConvPhot, "chi2ConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("nDofConvPhot", nDofConvPhot, "nDofConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("eOverPConvPhot", eOverPConvPhot, "eOverPConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("convVxConvPhot", convVxConvPhot, "convVxConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("convVyConvPhot", convVyConvPhot, "convVyConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("convVzConvPhot", convVzConvPhot, "convVzConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("distOfMinimumApproachConvPhot", distOfMinimumApproachConvPhot, "distOfMinimumApproachConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("dPhiTracksAtVtxConvPhot", dPhiTracksAtVtxConvPhot, "dPhiTracksAtVtxConvPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_isEM", pid_isEM, "pid_isEM[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_isLoose", pid_isLoose, "pid_isLoose[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_isTight", pid_isTight, "pid_isTight[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_jurECAL", pid_jurECAL, "pid_jurECAL[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_twrHCAL", pid_twrHCAL, "pid_twrHCAL[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_HoverE", pid_HoverE, "pid_HoverE[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack", pid_hlwTrack, "pid_hlwTrack[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrackNoDz", pid_hlwTrackNoDz, "pid_hlwTrackNoDz[nPhot]/F") ;   //[nPhot]
  //    ana_tree->Branch("pid_hlwTrackForCiC[40][100];

  ana_tree->Branch("r9Phot", r9Phot, "r9Phot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("s4RatioPhot", s4RatioPhot, "s4RatioPhot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("sigmaRRPhot", sigmaRRPhot, "sigmaRRPhot[nPhot]/F") ;   //[nPhot]


  ana_tree->Branch("pid_etawid", pid_etawid, "pid_etawid[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_jurECAL03", pid_jurECAL03, "pid_jurECAL03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_twrHCAL03", pid_twrHCAL03, "pid_twrHCAL03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03", pid_hlwTrack03, "pid_hlwTrack03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03NoDz", pid_hlwTrack03NoDz, "pid_hlwTrack03NoDz[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03ForCiC", pid_hlwTrack03ForCiC, "pid_hlwTrack03ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged01ForCiC", pid_pfIsoCharged01ForCiC_, "pid_pfIsoCharged01ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged02ForCiC", pid_pfIsoCharged02ForCiC_, "pid_pfIsoCharged02ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged03ForCiC", pid_pfIsoCharged03ForCiC_, "pid_pfIsoCharged03ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged04ForCiC", pid_pfIsoCharged04ForCiC_, "pid_pfIsoCharged04ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged05ForCiC", pid_pfIsoCharged05ForCiC_, "pid_pfIsoCharged05ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged06ForCiC", pid_pfIsoCharged06ForCiC_, "pid_pfIsoCharged06ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoPhotons01ForCiC", pid_pfIsoPhotons01ForCiC, "pid_pfIsoPhotons01ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoPhotons02ForCiC", pid_pfIsoPhotons02ForCiC, "pid_pfIsoPhotons02ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoPhotons03ForCiC", pid_pfIsoPhotons03ForCiC, "pid_pfIsoPhotons03ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoPhotons04ForCiC", pid_pfIsoPhotons04ForCiC, "pid_pfIsoPhotons04ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoPhotons05ForCiC", pid_pfIsoPhotons05ForCiC, "pid_pfIsoPhotons05ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoPhotons06ForCiC", pid_pfIsoPhotons06ForCiC, "pid_pfIsoPhotons06ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals01ForCiC", pid_pfIsoNeutrals01ForCiC, "pid_pfIsoNeutrals01ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals02ForCiC", pid_pfIsoNeutrals02ForCiC, "pid_pfIsoNeutrals02ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals03ForCiC", pid_pfIsoNeutrals03ForCiC, "pid_pfIsoNeutrals03ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals04ForCiC", pid_pfIsoNeutrals04ForCiC, "pid_pfIsoNeutrals04ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals05ForCiC", pid_pfIsoNeutrals05ForCiC, "pid_pfIsoNeutrals05ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoNeutrals06ForCiC", pid_pfIsoNeutrals06ForCiC, "pid_pfIsoNeutrals06ForCiC[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ptiso004Phot", ptiso004Phot, "ptiso004Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ntrkiso004Phot", ntrkiso004Phot, "ntrkiso004Phot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("ptiso035Phot", ptiso035Phot, "ptiso035Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ntrkiso035Phot", ntrkiso035Phot, "ntrkiso035Phot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("ptiso04Phot", ptiso04Phot, "ptiso04Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ntrkiso04Phot", ntrkiso04Phot, "ntrkiso04Phot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("hcalovecal04Phot", hcalovecal04Phot, "hcalovecal04Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ecaliso04Phot", ecaliso04Phot, "ecaliso04Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_scetawid", pid_scetawid, "pid_scetawid[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_scphiwid", pid_scphiwid, "pid_scphiwid[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_lambdaRatio", pid_lambdaRatio, "pid_lambdaRatio[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_esXwidth", pid_esXwidth, "pid_esXwidth[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_esYwidth", pid_esYwidth, "pid_esYwidth[nPhot]/F");   //[nPhot]
  ana_tree->Branch("sMajMajPhot", sMajMajPhot, "sMajMajPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("sMinMinPhot", sMinMinPhot, "sMinMinPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("alphaPhot", alphaPhot, "alphaPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("sEtaEtaPhot", sEtaEtaPhot, "sEtaEtaPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("sEtaPhiPhot", sEtaPhiPhot, "sEtaPhiPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("sPhiPhiPhot", sPhiPhiPhot, "sPhiPhiPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("E1Phot", E1Phot, "E1Phot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("E2OverE9Phot", E2OverE9Phot, "E2OverE9Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("E4Phot", E4Phot, "E4Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("E9Phot", E9Phot, "E9Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("E25Phot", E25Phot, "E25Phot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("ieleassocPhot", ieleassocPhot, "ieleassocPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("pid_deltaRToTrackPhot", pid_deltaRToTrackPhot, "pid_deltaRToTrackPhot[nPhot]/F");   //[nPhot]

  ana_tree->Branch("passPreselection",passPreselection,"passPreselection[nPhot]/I");		   
 
  ana_tree->Branch("isEleTag_match", isEleTag_match, "isEleTag_match[nEle]/I");
  ana_tree->Branch("isEleProbe_match", isEleProbe_match, "isEleProbe_match[nPhot]/I");
  ana_tree->Branch("isEleProbe_ele_match", isEleProbe_ele_match, "isEleProbe_ele_match[nEle]/I");
  ana_tree->Branch("deltaR_EleTagGenReco", deltaR_EleTagGenReco, "deltaREleGenReco[nEle]/F");
  ana_tree->Branch("deltaR_EleProbeGenReco", deltaR_EleProbeGenReco, "deltaREleGenReco[nPhot]/F");
  ana_tree->Branch("genEleMatched_index_tag", genEleMatched_index_tag, "genEleMatched_index_tag[nEle]/F");
  ana_tree->Branch("genEleMatched_index_probe", genEleMatched_index_probe, "genEleMatched_index_probe[nPhot]/F");
  		   
  ana_tree->Branch("passLooseElePtEta_match", passLooseElePtEta_match, "passLooseElePtEta_match[nPhot]/I");
  ana_tree->Branch("passLooseEleID_match", passLooseEleID_match, "passLooseEleID_match[nPhot]/I");
  ana_tree->Branch("passLooseEleImpactPar_match", passLooseEleImpactPar_match, "passLooseEleImpactPar_match[nPhot]/I");
  ana_tree->Branch("passLooseEleIsoRel_match", passLooseEleIsoRel_match, "passLooseEleIsoRel_match[nPhot]/I");
  ana_tree->Branch("passLooseEleMinHits_match", passLooseEleMinHits_match, "passLooseEleMinHits_match[nPhot]/I");
  ana_tree->Branch("passMediumElePtEta_match", passMediumElePtEta_match, "passMediumElePtEta_match[nPhot]/I");
  ana_tree->Branch("passMediumEleID_match", passMediumEleID_match, "passMediumEleID_match[nPhot]/I");
  ana_tree->Branch("passMediumEleImpactPar_match", passMediumEleImpactPar_match, "passMediumEleImpactPar_match[nPhot]/I");
  ana_tree->Branch("passMediumEleIsoRel_match", passMediumEleIsoRel_match, "passMediumEleIsoRel_match[nPhot]/I");
  ana_tree->Branch("passMediumEleMinHits_match", passMediumEleMinHits_match, "passMediumEleMinHits_match[nPhot]/I");
  ana_tree->Branch("passTightElePtEta_match", passTightElePtEta_match, "passTightElePtEta_match[nPhot]/I");
  ana_tree->Branch("passTightEleID_match", passTightEleID_match, "passTightEleID_match[nPhot]/I");
  ana_tree->Branch("passTightEleImpactPar_match", passTightEleImpactPar_match, "passTightEleImpactPar_match[nPhot]/I");
  ana_tree->Branch("passTightEleIsoRel_match", passTightEleIsoRel_match, "passTightEleIsoRel_match[nPhot]/I");
  ana_tree->Branch("passTightEleMinHits_match", passTightEleMinHits_match, "passTightEleMinHits_match[nPhot]/I");
  		   
  		   
  ana_tree->Branch("invMassEle_match", invMassEle_match, "invMassEle_match[20]/F");
  		   
  ana_tree->Branch("isEleTag", isEleTag, "isEleTag[nEle]/I");
  ana_tree->Branch("isEleProbe", isEleProbe, "isEleProbe[nPhot]/I");
  ana_tree->Branch("isEleProbe_ele", isEleProbe_ele, "isEleProbe_ele[nEle]/I");
  		   
  ana_tree->Branch("passLooseElePtEta", passLooseElePtEta, "passLooseElePtEta[nPhot]/I");
  ana_tree->Branch("passLooseEleID", passLooseEleID, "passLooseEleID[nPhot]/I");
  ana_tree->Branch("passLooseEleImpactPar", passLooseEleImpactPar, "passLooseEleImpactPar[nPhot]/I");
  ana_tree->Branch("passLooseEleIsoRel", passLooseEleIsoRel, "passLooseEleIsoRel[nPhot]/I");
  ana_tree->Branch("passLooseEleMinHits", passLooseEleMinHits, "passLooseEleMinHits[nPhot]/I");
  ana_tree->Branch("passMediumElePtEta", passMediumElePtEta, "passMediumElePtEta[nPhot]/I");
  ana_tree->Branch("passMediumEleID", passMediumEleID, "passMediumEleID[nPhot]/I");
  ana_tree->Branch("passMediumEleImpactPar", passMediumEleImpactPar, "passMediumEleImpactPar[nPhot]/I");
  ana_tree->Branch("passMediumEleIsoRel", passMediumEleIsoRel, "passMediumEleIsoRel[nPhot]/I");
  ana_tree->Branch("passMediumEleMinHits", passMediumEleMinHits, "passMediumEleMinHits[nPhot]/I");
  ana_tree->Branch("passTightElePtEta", passTightElePtEta, "passTightElePtEta[nPhot]/I");
  ana_tree->Branch("passTightEleID", passTightEleID, "passTightEleID[nPhot]/I");
  ana_tree->Branch("passTightEleImpactPar", passTightEleImpactPar, "passTightEleImpactPar[nPhot]/I");
  ana_tree->Branch("passTightEleIsoRel", passTightEleIsoRel, "passTightEleIsoRel[nPhot]/I");
  ana_tree->Branch("passTightEleMinHits", passTightEleMinHits, "passTightEleMinHits[nPhot]/I");
  

  ana_tree->Branch("invMassEle", invMassEle, "invMassEle[20]/F");
  ana_tree->Branch("BDT_output", BDT_output, "BDT_output[nPhot]/F") ;   //[nPhot]

  // triggering paths      
  ana_tree->Branch("firedHLTNames",  &aHLTNames);

  //pfMET
  ana_tree->Branch("epfMet", &epfMet, "epfMet/F");

  /********************************************************
   *                                                      *
   *                   INITIALIZATIONS                    *
   *                                                      *
   ********************************************************/
  
  // temp varables to keep track of the file being processed
  TString foldname("");
  TString currfilename("");
  int ifile(0);
  int nfiles = ((TChain*)fChain)->GetListOfFiles()->GetEntries();
  
  int nprocessed = 0;
  int nredntp = 0;
  int  nNoMatching = 0;
  int nNoReco = 0;
  int nEleEvents = 0;
  int nEleTag_tot(0), nEleProbe_tot(0);

  TH1F* h_genNotMatched = new TH1F("h_genNotMatched", "", 120, -2.5, 2.5 );

  float lowEdges[6] = {0., 20., 30., 40., 50., 100.};

  TH1F* h_ptProbe_denominator_match_0 = new TH1F("h_ptProbe_denominator_match_0", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_match_1 = new TH1F("h_ptProbe_denominator_match_1", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_match_2 = new TH1F("h_ptProbe_denominator_match_2", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_match_3 = new TH1F("h_ptProbe_denominator_match_3", "", 5, lowEdges);

  TH1F* h_ptProbe_match_0 = new TH1F("h_ptProbe_match_0", "", 5, lowEdges);
  TH1F* h_ptProbe_match_1 = new TH1F("h_ptProbe_match_1", "", 5, lowEdges);
  TH1F* h_ptProbe_match_2 = new TH1F("h_ptProbe_match_2", "", 5, lowEdges);
  TH1F* h_ptProbe_match_3 = new TH1F("h_ptProbe_match_3", "", 5, lowEdges);

  /*
  TH1F* h_effVSpt_eta_0 = new TH1F("h_effVSpt_eta_0", "", 5, lowEdges); 
  TH1F* h_effVSpt_eta_1 = new TH1F("h_effVSpt_eta_1", "", 5, lowEdges);
  TH1F* h_effVSpt_eta_2 = new TH1F("h_effVSpt_eta_2", "", 5, lowEdges);
  TH1F* h_effVSpt_eta_3 = new TH1F("h_effVSpt_eta_3", "", 5, lowEdges);
  */

  TH1F* h_ptProbe_denominator_0 = new TH1F("h_ptProbe_denominator_0", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_1 = new TH1F("h_ptProbe_denominator_1", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_2 = new TH1F("h_ptProbe_denominator_2", "", 5, lowEdges);
  TH1F* h_ptProbe_denominator_3 = new TH1F("h_ptProbe_denominator_3", "", 5, lowEdges);

  TH1F* h_ptProbe_0 = new TH1F("h_ptProbe_0", "", 5, lowEdges);
  TH1F* h_ptProbe_1 = new TH1F("h_ptProbe_1", "", 5, lowEdges);
  TH1F* h_ptProbe_2 = new TH1F("h_ptProbe_2", "", 5, lowEdges);
  TH1F* h_ptProbe_3 = new TH1F("h_ptProbe_3", "", 5, lowEdges);


  TH1F* h_pt_denominator_0 = new TH1F("h_pt_denominator_0", "", 5, lowEdges);
  TH1F* h_pt_denominator_1 = new TH1F("h_pt_denominator_1", "", 5, lowEdges);
  TH1F* h_pt_denominator_2 = new TH1F("h_pt_denominator_2", "", 5, lowEdges);
  TH1F* h_pt_denominator_3 = new TH1F("h_pt_denominator_3", "", 5, lowEdges);

  TH1F* h_pt_0 = new TH1F("h_pt_0", "", 5, lowEdges);
  TH1F* h_pt_1 = new TH1F("h_pt_1", "", 5, lowEdges);
  TH1F* h_pt_2 = new TH1F("h_pt_2", "", 5, lowEdges);
  TH1F* h_pt_3 = new TH1F("h_pt_3", "", 5, lowEdges);

  //cout << "Set MVA variables" << endl;
  /*******************************************************
   *                   SET MVA VAR                       *   
   *******************************************************/
  
  // photonID MVA
  tmvaReaderID_Single_Endcap=0;
  tmvaReaderID_Single_Barrel=0;
  if (!tmvaReaderID_Single_Barrel || !tmvaReaderID_Single_Endcap) SetAllMVA();
  
  
  /********************************************************
   *                                                      *
   *                       LOOP                           *
   *                                                      *
   ********************************************************/

  cout << "Sto per entrare nel loop" << endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (myjson && nMC<=0) 
      if (!myjson->isGoodLS(run,lbn)) continue;

  
    //if (scaleCorrections_) correctPhotons(true);
    
    // print name of current file
    currfilename = TString(fChain->GetCurrentFile()->GetName());
    if(currfilename != foldname) {
      ifile++;
      cout << "Opening file " << ifile << " of "  << nfiles << "\n"
	   << currfilename  << "\n"
	   << "------------------------------"
	   << endl;
      foldname = currfilename;
    }


    if (nprocessed%1000 == 0) cout << "Events " << nprocessed << " processed; Run " << run << " LS " << lbn << endl;
    nprocessed++;
    
    if(nEle == 0) continue;

    //cout << "nEle : " << nEle << "   nPhot : " << nPhot << endl;
 

    int nGenElectrons(0);
    int isElectronFromZ[nMC];
    int neletag(0), neleprobe(0);
    
    // vector<TVector3> genElectron_tag, genElectron_probe ;
    //vector<TLorentzVector> genElectron ;
    TLorentzVector gen_tag, gen_probe, reco_tag, reco_probe, gen, reco;
    //vector<bool> vec_iselefromz(nMC);
  
    float r9_phot[20];      
    float s4Ratio_phot[20];
    float sigmaRR[20];     


    int edge_phot, edge_ele;
    if(nPhot>20) edge_phot = 20;
    else edge_phot = nPhot;
    if(nEle>20) edge_ele = 20;
    else edge_ele = nEle;


    for(int i=0; i<20; i++){
      r9_phot[i] = -999.;     
      s4Ratio_phot[i] = -999.;
      sigmaRR[i] = -999.;     
    }

    /********************************************************
     *                                                      *
     *                 LOOP :: GEN ANALYSIS                 *
     *                                                      *
     ********************************************************/
    
      
    if(isMC) {
      

      /// init of mc related variables
      //if(nEle>0) cout << "Loop over nMC" << endl;
      for(int i=0; i<nMC; i++) {
	//	cout << "initializing gen ele" << endl;
	isElectronFromZ[i] =0;
	gen.SetPtEtaPhiE(-999., -999., -999, -999.);
	//cout << "event : " << event  << "   nMC : " << nMC << "    i : " << i << "    pdgIdMC : " << pdgIdMC[i] << "      pdgIdMC[motherIDMC] : " << pdgIdMC[motherIDMC[i]] << endl;
	if( TMath::Abs(pdgIdMC[i])==11  && TMath::Abs(pdgIdMC[motherIDMC[i]])==23
	    && (statusMC[i]==1 || statusMC[i]==3) 
	    //&& ptMC[i] > 20 
	    //&& (TMath::Abs(etaMC[i])<1.4442 || (TMath::Abs(etaMC[i])>1.566 && TMath::Abs(etaMC[i])<2.5)) 
	    //da cambiare
	  ){
	  //cout << "gen electron found!" << endl;
	  if(nGenElectrons > 2) cout << "piu` di 2 elettroni dalla Z!!" << endl;
	  nGenElectrons++;
	  isElectronFromZ[i]= 1;
	  
	  gen.SetPtEtaPhiE(ptMC[i], etaMC[i], phiMC[i], eMC[i]);
	  //genElectron.push_back(gen); 
	  
	  //if(pdgIdMC[i]>0) {
	  //  gen_tag.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	  //  genElectron_tag.push_back(gen_tag);
	  //}
	  //else if(pdgIdMC[i]<0) {
	  //  gen_probe.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	  //  genElectron_probe.push_back(gen_probe);	  
	  //} 
	  //cout << "sto uscendo dall'if" << endl;	  
	}
	
	//genElectron.push_back(gen);             

      }
      //cout << "esco dal ciclo su nMC" << endl;

      if(nGenElectrons==2) nEleEvents++;
      if (nGenElectrons!=0 && nGenElectrons!=2) {
	cout << "gen electrons from Z : " << nGenElectrons << endl;
	for(int i=0; i<nMC; i++){
	  if(isElectronFromZ[i])
	    cout << "ststusMC  : "<< statusMC[i] << "    motherID "<< i << " : " << pdgIdMC[motherIDMC[i]] << endl;
	}
      }
      //for(int i=0; i<nMC; i++) {
      //	vec_iselefromz[i] = isElectronFromZ[i];
      //}
    }
    
    //cout << "esco dall'if( isMC)" << endl;


    //nel vecchio file if(isgjetqcd && counter > 1) continue;    
    
    /*
    //gen level electrons
    vector<int> genEleFromZ;   
    if(isMC && nGenElectrons==2)  {
      genEleFromZ = firstones(ptMC,&vec_iselefromz,2);
      
      cout << "ho usato la funzione firstones" << endl;
      cout << "ptMC 1 : " << genEleFromZ[0] << "    ptMC 2 : " << genEleFromZ[1] << endl;
    }
    */

    // pu weights
    npu = pu_n;
    
    
    // for dedicated HLT selections
    if(npu<MAX_PU_REWEIGHT && nMC>0) {

      if(puweights_.size()>0) 
	pu_weight = puweights_[npu];
      else
	pu_weight = 1;
        
  
      if(puweights30_.size()>0)
	pu_weight30 = puweights30_[npu];
      else
	pu_weight30 = 1.;
      
      if(puweights50_.size()>0)
	pu_weight50 = puweights50_[npu];
      else
	pu_weight50 = 1.;
      
      if(puweights75_.size()>0)
	pu_weight75 = puweights75_[npu];
      else
	pu_weight75 = 1.;
      
      if(puweights90_.size()>0)
	pu_weight90 = puweights90_[npu];
      else
	pu_weight90 = 1.;
    }

    //cout << "set weight" << endl;
    weight=pu_weight;
    //cout << "weight : " << weight << endl;

    // to be used after
    if(isMC && nGenElectrons==2) elegen1.Fill(1.,weight);

    //cout << " elegen1 filled with 1 " << endl; 

    // skip events where the number of jets, photons, and vertexes is above the maximum allowed value
    if (nPhot>30) {
      cout << "number of photons = " << nPhot << " and above threshold of 30; skipping" << endl;
      continue;
    }
    if (nJet_pfakt5 > 200) {
      cout << "number of nJet_pfakt5 = " << nJet_pfakt5 << " and above threshold of 200; skipping" << endl;
      continue;
    }
    if (nJetGen_akt5 > 200) {
      cout << "number of nJetGen_akt5 = " << nJetGen_akt5 << " and above threshold of 200; skipping" << endl;
      continue;
    }
    if (nvertex > MAX_PU_REWEIGHT) {
      cout << "number of nvertex = " << nvertex << " and above threshold of " << MAX_PU_REWEIGHT << "; skipping" << endl;
      continue;
    }

    // reconstructed variables -----------------------------------------

    //cout << "HLT paths" << endl;
    // firing HLT paths
    aHLTNames = new std::vector<std::string>;
    aHLTNames -> clear();
    for (int ii=0; ii<(HLTResults->size()); ii++) {
      if ((*HLTResults)[ii]) {
        aHLTNames->push_back((*HLTNames)[ii]);
      }
    }
    
    

    //cout << "starting reco analysis" << endl;
    //cout << "nEle : " << nEle << "    nPhot : " << nPhot << endl;


    /***************************************************
     *                                                 *
     *                 RECO ELE & PHOTONS              *
     *                                                 *
     ***************************************************/
    

    //----------------------------------------------
    //            cluster shape corrections
    //----------------------------------------------


    for (int i=0; i<edge_phot; i++){
      
      float rr2 = 0;
      rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
      //tmva_photonid_ESEffSigmaRR = 0.0; 
      
      float r9phot = E9Phot[i] / escRawPhot[i];
      float s4phot = E4Phot[i] / E25Phot[i];


      r9_phot[i]      = r9phot;
      s4Ratio_phot[i] = s4phot;
      sigmaRR[i]      = TMath::Sqrt(rr2);	

      //cout << "setaeta before: " << pid_etawid[i] << "  " << endl;    
      //ClusterShape(i, electron_SigmaIetaIeta[i], electron_dEtaIn[i], electron_dPhiIn[i], electron_r9[i]);      
      ClusterShape(&i, &pid_etawid[i], &pid_scetawid[i], &pid_scphiwid[i], &r9phot, &s4phot);
      //cout << "setaeta after: " << pid_etawid[i] << "  " << endl << endl;    
      
    }
    //cout << "cluster shape correction done" << endl
    // << "start defining cuts" << endl;


    //if(nEle>0)  cout << "Parte di analisi reco"  << endl;

    // Photon ID selection 2012
    // this is the tight WP  (for probe electron) 
    // in https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
    photonidcuts2012 eleprobe_tight2012;
    eleprobe_tight2012.eta       = 2.5;
    eleprobe_tight2012.crack1    = 1.4442;
    eleprobe_tight2012.crack2    = 1.566;
    eleprobe_tight2012.pt        = 20.;
    eleprobe_tight2012.setaetaEB = 0.011;
    eleprobe_tight2012.setaetaEE = 0.031;
    eleprobe_tight2012.hoeEB     = 0.05;
    eleprobe_tight2012.hoeEE     = 0.05;
    
    // Photon ID selection 2012
    // this is the medium WP  (for probe electron) 
    // in https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
    photonidcuts2012 eleprobe_medium2012;
    eleprobe_medium2012.eta       = 2.5;
    eleprobe_medium2012.crack1    = 1.4442;
    eleprobe_medium2012.crack2    = 1.566;
    eleprobe_medium2012.pt        = 20.;
    eleprobe_medium2012.setaetaEB = 0.011;
    eleprobe_medium2012.setaetaEE = 0.033;
    eleprobe_medium2012.hoeEB     = 0.05;
    eleprobe_medium2012.hoeEE     = 0.05;
    
    // Photon ID selection 2012
    // this is the loose WP (for probe electron) 
    // in https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
    photonidcuts2012 eleprobe_loose2012;
    eleprobe_loose2012.eta       = 2.5;
    eleprobe_loose2012.crack1    = 1.4442;
    eleprobe_loose2012.crack2    = 1.566;
    eleprobe_loose2012.pt        = 20.;
    eleprobe_loose2012.setaetaEB = 0.012;
    eleprobe_loose2012.setaetaEE = 0.034;
    eleprobe_loose2012.hoeEB     = 0.05;
    eleprobe_loose2012.hoeEE     = 0.05;
    

    /***************************************************
     *                                                 *
     *                 RECO ELECTRONS                  *
     *                                                 *
     ***************************************************/
    //if(nEle>0)  cout << "Parte di analisi reco"  << endl;

    // Lepton tag selection 2012: electrons
    // this is the tight WP (for  the tag and probe) 
    // in https://twiki.cern.ch/twiki/bin/view/CMS/EgammaCutBasedIdentification
    electronidcuts2012 eletag_tight2012;
    eletag_tight2012.eta       = 2.5;
    eletag_tight2012.crack1    = 1.4442;
    eletag_tight2012.crack2    = 1.566;
    eletag_tight2012.pt        = 20.;
    eletag_tight2012.setaetaEB = 0.01;
    eletag_tight2012.setaetaEE = 0.03;
    eletag_tight2012.dphiEB    = 0.03;   
    eletag_tight2012.dphiEE    = 0.02;   
    eletag_tight2012.detaEB    = 0.004;
    eletag_tight2012.detaEE    = 0.005;
    eletag_tight2012.hoeEB     = 0.12;
    eletag_tight2012.hoeEE     = 0.10;
    eletag_tight2012.oemopEB   = 0.05;
    eletag_tight2012.oemopEE   = 0.05;
    eletag_tight2012.d0EB      = 0.02;
    eletag_tight2012.d0EE      = 0.02;
    eletag_tight2012.dzEB      = 0.1;
    eletag_tight2012.dzEE      = 0.1;
    eletag_tight2012.minhitsEB = 0;
    eletag_tight2012.minhitsEE = 0;
    eletag_tight2012.iso_relEB = 0.10;  
    eletag_tight2012.iso_relEE = 0.10;

    /*
    // Lepton tag selection 2012: electrons
    // this is the medium WP
    // in https://twiki.cern.ch/twiki/bin/view/CMS/EgammaCutBasedIdentification
    electronidcuts2012 eletag_medium2012;
    eletag_medium2012.eta       = 2.5;
    eletag_medium2012.crack1    = 1.4442;
    eletag_medium2012.crack2    = 1.566;
    eletag_medium2012.pt        = 20.;
    eletag_medium2012.setaetaEB = 0.01;
    eletag_medium2012.setaetaEE = 0.03;
    eletag_medium2012.dphiEB    = 0.06;   
    eletag_medium2012.dphiEE    = 0.03;   
    eletag_medium2012.detaEB    = 0.004;
    eletag_medium2012.detaEE    = 0.007;
    eletag_medium2012.hoeEB     = 0.12;
    eletag_medium2012.hoeEE     = 0.10;
    eletag_medium2012.oemopEB   = 0.05;
    eletag_medium2012.oemopEE   = 0.05;
    eletag_medium2012.d0EB      = 0.02;
    eletag_medium2012.d0EE      = 0.02;
    eletag_medium2012.dzEB      = 0.1;
    eletag_medium2012.dzEE      = 0.1;
    eletag_medium2012.minhitsEB = 1;
    eletag_medium2012.minhitsEE = 1;
    eletag_medium2012.iso_relEB = 0.15;  
    eletag_medium2012.iso_relEE = 0.15;

    // Lepton tag selection 2012: electrons
    // this is the loose WP
    // in https://twiki.cern.ch/twiki/bin/view/CMS/EgammaCutBasedIdentification
    electronidcuts2012 eletag_loose2012;
    eletag_loose2012.eta       = 2.5;
    eletag_loose2012.crack1    = 1.4442;
    eletag_loose2012.crack2    = 1.566;
    eletag_loose2012.pt        = 20.;
    eletag_loose2012.setaetaEB = 0.01;
    eletag_loose2012.setaetaEE = 0.03;
    eletag_loose2012.dphiEB    = 0.15;   
    eletag_loose2012.dphiEE    = 0.10;   
    eletag_loose2012.detaEB    = 0.007;
    eletag_loose2012.detaEE    = 0.009;
    eletag_loose2012.hoeEB     = 0.12;
    eletag_loose2012.hoeEE     = 0.10;
    eletag_loose2012.oemopEB   = 0.05;
    eletag_loose2012.oemopEE   = 0.05;
    eletag_loose2012.d0EB      = 0.02;
    eletag_loose2012.d0EE      = 0.02;
    eletag_loose2012.dzEB      = 0.2;
    eletag_loose2012.dzEE      = 0.2;
    eletag_loose2012.minhitsEB = 1;
    eletag_loose2012.minhitsEE = 1;
    eletag_loose2012.iso_relEB = 0.15;  
    eletag_loose2012.iso_relEE = 0.15;

    */
    /////////////////////////////////////////////////////////////////////
    //int countPreselPhot = 0;  
    int isEle_tag_match[20];
    int isEle_probe_match[20];
    int isEle_probe_ele_match[20];
    
    int passLoose_ElePtEta_match[20];
    int passLoose_EleID_match[20];
    int passLoose_EleImpactPar_match[20];
    int passLoose_EleIsoRel_match[20];
    int passLoose_EleMinHits_match[20];
    int passMedium_ElePtEta_match[20];
    int passMedium_EleID_match[20];
    int passMedium_EleImpactPar_match[20];
    int passMedium_EleIsoRel_match[20];
    int passMedium_EleMinHits_match[20];
    int passTight_ElePtEta_match[20];
    int passTight_EleID_match[20];
    int passTight_EleImpactPar_match[20];
    int passTight_EleIsoRel_match[20];
    int passTight_EleMinHits_match[20];


    TLorentzVector  ele, phot;
    TLorentzVector vector_ele[20], vector_phot[20]; 
    int vec_genMatched_index_tag[20];
    int vec_genMatched_index_probe[20];

    //int vec_recoMatched_index[nEle] = {-999.};
    float vec_deltaR_tag[20] ;
    float vec_deltaR_probe[20] ;
    float deltaR, deltaRmin;
    int recoMatched_index = -999.;
    int genMatched_index = -999.;
    //vector<float> vec_invmass_match;
    float vec_invmass_match[20];
    float invmass_match = - 999.;

    int isEle_tag[20];
    int isEle_probe[20];
    int isEle_probe_ele[20];
    float vec_invmass[20];
    float invmass = - 999.;

    int pass_preselection[20];

    int passLoose_ElePtEta[20];    
    int passLoose_EleID[20];       
    int passLoose_EleImpactPar[20];
    int passLoose_EleIsoRel[20];   
    int passLoose_EleMinHits[20];  
    int passMedium_ElePtEta[20];    
    int passMedium_EleID[20];       
    int passMedium_EleImpactPar[20];
    int passMedium_EleIsoRel[20];   
    int passMedium_EleMinHits[20];  
    int passTight_ElePtEta[20];    
    int passTight_EleID[20];       
    int passTight_EleImpactPar[20];
    int passTight_EleIsoRel[20];   
    int passTight_EleMinHits[20];  

    //cout << "initialization of reco quantities" << endl;
    //initialization
    for (int i=0; i<20; i++){
      isEle_tag_match[i] = 0;
      isEle_probe_match[i] = 0;
      isEle_probe_ele_match[i] = 0;
      vec_genMatched_index_tag[i] = -999.;
      vec_genMatched_index_probe[i] = -999.;
      vec_deltaR_tag[i] = -999.;
      vec_deltaR_probe[i] = -999.;
      vec_invmass_match[i] = -999.;

      pass_preselection[i]=0;

      passLoose_ElePtEta_match[i] = 0;   
      passLoose_EleID_match[i] = 0;          
      passLoose_EleImpactPar_match[i] = 0;   
      passLoose_EleIsoRel_match[i] = 0;      
      passLoose_EleMinHits_match[i] = 0;     
      passMedium_ElePtEta_match[i] = 0;   
      passMedium_EleID_match[i] = 0;          
      passMedium_EleImpactPar_match[i] = 0;   
      passMedium_EleIsoRel_match[i] = 0;      
      passMedium_EleMinHits_match[i] = 0;     
      passTight_ElePtEta_match[i] = 0;   
      passTight_EleID_match[i] = 0;          
      passTight_EleImpactPar_match[i] = 0;   
      passTight_EleIsoRel_match[i] = 0;      
      passTight_EleMinHits_match[i] = 0;     

      isEle_tag[i] = 0;
      isEle_probe[i] = 0;
      isEle_probe_ele[i] = 0;
      vec_invmass[i] = -999.;

      passLoose_ElePtEta[i] = 0;   
      passLoose_EleID[i] = 0;          
      passLoose_EleImpactPar[i] = 0;   
      passLoose_EleIsoRel[i] = 0;      
      passLoose_EleMinHits[i] = 0;     
      passMedium_ElePtEta[i] = 0;   
      passMedium_EleID[i] = 0;          
      passMedium_EleImpactPar[i] = 0;   
      passMedium_EleIsoRel[i] = 0;      
      passMedium_EleMinHits[i] = 0;     
      passTight_ElePtEta[i] = 0;   
      passTight_EleID[i] = 0;          
      passTight_EleImpactPar[i] = 0;   
      passTight_EleIsoRel[i] = 0;      
      passTight_EleMinHits[i] = 0;     

    }

    //cout << "initialized" << endl
    // << "filling 4vectors of ele and phots" << endl;

    vector<bool> idpasseletag2012(13);
    //vector<bool*> idpasseleprobe2012(5);;
    //bool* idpasseletag2012[13];
    bool* idpasseleprobe2012[5];

    //cout << "starting loop for electrons" << endl;


    //cout << "starting loop for photons" << endl;
    for(int iPhot=0; iPhot<nPhot; iPhot++ ){
      phot.SetPtEtaPhiE(ptPhot[iPhot], etaPhot[iPhot], phiPhot[iPhot], ePhot[iPhot]);
      vector_phot[iPhot] = phot;

      //cout << "iPhot : "<< iPhot << "   ptPhot : " << ptPhot[iPhot] << endl;
    }


    //cout << "nEle : " << nEle << endl;
    for(int iEle=0; iEle<nEle; iEle++ ){
      ele.SetPtEtaPhiE(electron_pt[iEle], electron_eta[iEle], electron_phi[iEle], electron_energy[iEle]);
      vector_ele[iEle] = ele;

      //cout << "iEle : "<< iEle << "   electron_pt : " << electron_pt[iEle] << endl;
    }
    
    int thereIsOneTag_match = 0; 


    //cout << "starting Tag&Probe matching" << endl;



    /************************************************************
     *                                                          *
     *                       PRESELECTION                       *
     *                                                          *
     ************************************************************/


    for(int iPhot=0; iPhot<edge_phot; iPhot++){
      if(PhotonMITPreSelection(iPhot,0,0)) pass_preselection[iPhot] = 1;
      //if(pass_preselection[iPhot]!=0 && pass_preselection[iPhot]!=1) cout << "pass_preselection : " << pass_preselection[iPhot] << endl;
    }


    if(isMC) {
      /*---------------------------------------------------------------
	
                         Tag&Probe matching
      
      ---------------------------------------------------------------*/

  
      //if(nEle>0) cout << "Probe electrons" << endl;
      //for probe electrons with match

      for(int i =0; i<nMC; i++){
	if(isElectronFromZ[i]) {
	  gen.SetPtEtaPhiE(ptMC[i],etaMC[i],phiMC[i],eMC[i]);
	  deltaRmin = 0.2;
	  recoMatched_index = -999.;
	  genMatched_index = -999.;

	  for(int j=0; j<edge_phot; j++) {
	    phot.SetPtEtaPhiE(ptPhot[j], etaPhot[j], phiPhot[j], ePhot[j]);
	    deltaR = gen.DeltaR(phot);
	    
	    if(pass_preselection[j]
	       && deltaR<deltaRmin  
	       && ptPhot[j]>20. 
	       && ( TMath::Abs(etascPhot[j])<1.4442 || (TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.5)) 

	       ) {
	      
	      //if (ptPhot[j]<20.) cout << "ptPhot = " << ptPhot[j] << " !!! " << endl; 
	      //if (TMath::Abs(etascPhot[j])>2.5) cout << "etascPhot = " << etascPhot[j] << " !!! " << endl; 
	      deltaRmin = deltaR;
	      recoMatched_index = j;
	      
	      genMatched_index = i;
	    }
	    
	  }
	  if(recoMatched_index >= 0){
	    
	    vec_deltaR_probe[recoMatched_index] = deltaRmin;
	    vec_genMatched_index_probe[recoMatched_index] = genMatched_index;
	    isEle_probe_match[recoMatched_index] = 1;
	    
	    //if (ptPhot[recoMatched_index]<20.) cout << "ptPhot = " << ptPhot[recoMatched_index] << " !!! " << endl;
	    //if (TMath::Abs(etascPhot[recoMatched_index])>2.5) cout << "etascPhot = " << etascPhot[recoMatched_index] << " !!! " << 
	    
	    neleprobe++;
	    if(nGenElectrons==2) nEleProbe_tot++;
	    
	  }
	  else {
	    h_genNotMatched->Fill(etaMC[i]);
	    
	  }
	}
	
      }

      if(nEle >= 2 && neleprobe<2 && nGenElectrons==2 ) {
	
	nNoMatching++;
	/*
	  cout << "------------- event with neleprobe<2 && nGenElectrons==2  ----------------" << endl;
	  
	  for(int i=0; i<nMC; i++){
	  if(isElectronFromZ[i]){
	  cout << "Gen : (" << ptMC[i] <<", " << etaMC[i] << ", " << phiMC[i] << ", " << eMC[i] << ")" << endl;
	  }
	  }
	  
	  for(int i=0; i<nEle; i++){
	  cout << "Reco : (" << electron_pt[i] << ", " << electron_eta[i] << ", " << electron_phi[i] << ", " << electron_energy[i] << ")" << endl;
	  
	  }
	*/
      }
      
      if(nEle <2 && neleprobe<2 && nGenElectrons==2 ) {
	
	nNoReco++;
	/*  cout << "------------- event with nEle<2 && neleprobe<2 && nGenElectrons==2  ----------------" << endl;
	    
	for(int i=0; i<nMC; i++){
	if(isElectronFromZ[i]){
	cout << "Gen : (" << ptMC[i] <<", " << etaMC[i] << ", " << phiMC[i] << ", " << eMC[i] << ")" << endl;
	}
	}
	
	for(int i=0; i<nEle; i++){
	cout << "Reco : (" << electron_pt[i] << ", " << electron_eta[i] << ", " << electron_phi[i] << ", " << electron_energy[i] << ")" << endl;
	
	}
	*/
      }
      
      
      //if(nEle>0) cout << "Tag electrons" << endl;
      //for tag electrons

      for(int i =0; i<nMC; i++){
	if(isElectronFromZ[i]) {
	  gen.SetPtEtaPhiE(ptMC[i],etaMC[i],phiMC[i],eMC[i]);
	  deltaRmin = 0.2;
	  recoMatched_index = -999.;
	  genMatched_index = -999.; 
	  for(int j=0; j<edge_ele; j++) {
	    ele.SetPtEtaPhiE(electron_pt[j], electron_eta[j], electron_phi[j], electron_energy[j]);
	    deltaR = gen.DeltaR(ele);
	    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    if(deltaR<deltaRmin  && leptonCutsEle2012(j, eletag_tight2012, &idpasseletag2012)) {
	      //if(deltaR<deltaRmin  && leptonCutsEle2012(j, eletag_tight2012, idpasseletag2012)) {
	      deltaRmin = deltaR;
	      recoMatched_index = j;
	      genMatched_index = i;
	    }
	  }
	  if(recoMatched_index >= 0){
	    
	    vec_deltaR_tag[recoMatched_index] = deltaRmin;
	    vec_genMatched_index_tag[recoMatched_index] = genMatched_index;
	    isEle_tag_match[recoMatched_index] = 1;
	    neletag++;
	    if(nGenElectrons==2) nEleTag_tot++;
	
	  }
	}
      }
   

      
      //correspondence photon_reco-electron_reco
      
      float best_invmass_match, d_invmass_match;
      int ele_index = -999; 
      TLorentzVector sum;
      
      for(int i=0; i<20; i++){
	isEle_probe_ele_match[i] = 0; 
      }
      
      for(int i=0; i<edge_phot; i++) {
	invmass_match = -999.;
	best_invmass_match = -999;
	
	//      d_invmass_match = 30.;
	//d_invmass_match = 90.;
	if(isEle_probe_match[i]) {

	  for(int j=0; j<edge_ele; j++) {
	    sum = vector_ele[j] + vector_phot[i];
	    invmass_match = sum.M();
	    //if(invmass_match < 5.) cout << "invmass_match : " << invmass_match << endl;
	    if(TMath::Abs(invmass_match) < TMath::Abs(best_invmass_match) ){
	      best_invmass_match = invmass_match;
	      ele_index = j;
	    }
	    if(j==(edge_ele-1) && TMath::Abs(best_invmass_match)<5.) {
	      isEle_probe_ele_match[ele_index] = 1;
	      //cout << "best_invmass_match : " << best_invmass_match << endl;
	    }
	  }
	}
      }
      //compute invmass for each couple (should eliminate double counting and invmass=0)
      int ncouples_match =0;
      for (int i=0; i<edge_ele; i++){
	if(isEle_tag_match[i]) {
	  for (int j=i+1;  j<edge_ele ; j++){
	    if(isEle_probe_ele_match[j]){
	      sum = vector_ele[i]+vector_ele[j];
	      invmass_match = sum.M();
	      //cout << "invmass_match : " << invmass_match << endl;
	      vec_invmass_match[ncouples_match] = invmass_match;
	      ncouples_match++;
	    }
	  }
	}
      }
    
      //if(ncouples_match>0){
      //cout << "ncouples_match = " << ncouples_match << endl;
      //cout << "combinatorio = " << endl;
      //}
      
      thereIsOneTag_match = 0; 
      for (int i=0; i<edge_ele; i++) {
	if(isEle_tag_match[i]) thereIsOneTag_match += 1;
      }
      
      //cout << "thereIsOneTag : " << thereIsOneTag << endl;
      if(thereIsOneTag_match) {
	for (int j=0; j<edge_phot; j++) {
	  if(isEle_probe_match[j]) {
	    
	    //------------------------------------------
	    //                bool elepass (loose WP)
	    //------------------------------------------
	    //photonIDCuts2012(j, eleprobe_loose2012, &idpasseleprobe2012);
	    photonIDCuts2012(j, eleprobe_loose2012, idpasseleprobe2012);
	    
	    if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       {
	      passLoose_ElePtEta_match[j] = 1;    
	    }
	    //cout << "passed pt and eta cut" << endl; 
	    //if(ptPhot[j]>20 && TMath::Abs(etascPhot[j])<2.5 && passLoose_ElePtEta_match[j]==0)  {
	    //  cout << "not passing pt and eta cut : ptPhot = " << ptPhot[j] << "   etascPhot[j] = " << etascPhot[j] << endl;
	    //}
	    
	    if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	       //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	       )   passLoose_EleID_match[j] = 1;          
	    
	    //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passLoose_EleImpactPar_match[i] = 0;   
	    //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passLoose_EleIsoRel_match[i] = 0;      
	    //if(idpasseleprobe2012[12])      passLoose_EleMinHits_match[i] = 0;     
	    
	    
	    //cout << "pass pt : " << *idpasseleprobe2012[0] << "   pass eta : " << *idpasseleprobe2012[1] << "   pass eta_crack : " << *idpasseleprobe2012[2] << "   passLoose_ElePtEta_match : " << passLoose_ElePtEta_match[j] << "   passLoose_EleID_match : " << passLoose_EleID_match[j] << endl;
	    
	    
	    //------------------------------------------
	    //                bool elepass (medium WP)
	    //------------------------------------------
	    photonIDCuts2012(j, eleprobe_medium2012, idpasseleprobe2012);
	    if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       passMedium_ElePtEta_match[j] = 1;    
	    if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	       //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	       )   passMedium_EleID_match[j] = 1;          
	    //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passMedium_EleImpactPar_match[i] = 0;   
	    //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passMedium_EleIsoRel_match[i] = 0;      
	    //if(idpasseleprobe2012[12])      passMedium_EleMinHits_match[i] = 0;     
	    
	    //------------------------------------------
	    //                bool elepass (tight WP)
	    //------------------------------------------
	    photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012);
	    if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       passTight_ElePtEta_match[j] = 1;    
	    if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	       //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	       )   passTight_EleID_match[j] = 1;          
	    //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passTight_EleImpactPar_match[i] = 0;   
	    //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passTight_EleIsoRel_match[i] = 0;      
	    //if(idpasseleprobe2012[12])      passTight_EleMinHits_match[i] = 0;     
	    
	  }
	  
	}
      }
      
    }
    

    //cout << "starting Tag&Probe no matching" << endl; 
    //if isMC OR !isMC
    /*---------------------------------------------------------------
      
                          Tag&Probe no matching
    
    ---------------------------------------------------------------*/
    

    //if(nEle>0) cout << "Tag electrons" << endl;
    //for tag electrons
    
    int recoTag_index;
    for(int j=0; j<edge_ele; j++) {
      recoTag_index = -999;
      if(leptonCutsEle2012(j, eletag_tight2012, &idpasseletag2012)) {
	//if(leptonCutsEle2012(j, eletag_tight2012, idpasseletag2012)) {
	recoTag_index = j;
      }
      if(recoTag_index >= 0){
	isEle_tag[recoTag_index] = 1;
      }
    }
    
    int recoProbe_index;
    for(int j=0; j<edge_phot; j++) {
      recoProbe_index = -999;
      if(pass_preselection[j]
	 && ptPhot[j]>20.  
	 && (TMath::Abs(etascPhot[j])<1.4442 || (TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.5))

	 )  {
	recoProbe_index = j;
	
	if(recoProbe_index >= 0){
	  isEle_probe[recoProbe_index] = 1;
	  //if (ptPhot[j]<20.) cout << "ptPhot = " << ptPhot[j] << " !!! " << endl; 
	  //if (TMath::Abs(etascPhot[j])>2.5) cout << "etascPhot = " << etascPhot[j] << " !!! " << endl; 
	}
      }
    }
    
    

    float best_invmass, d_invmass;
    TLorentzVector sum;
    int ele_index = -999; 


    //
    for(int i=0; i<20; i++){
      isEle_probe_ele[i] = 0; 
    }

    for(int i=0; i<edge_phot; i++) {
      invmass = -999.;
      best_invmass = -999;

      //      d_invmass = 30.;                                                                                                                   
      //d_invmass = 90.;                                                                                                                         
      if(isEle_probe[i]) {
        for(int j=0; j<edge_ele; j++) {
          sum = vector_ele[j] + vector_phot[i];
          invmass = sum.M();
          //if(invmass < 5.) cout << "invmass : " << invmass << endl;                                                                
          if(TMath::Abs(invmass) < TMath::Abs(best_invmass) ){
            best_invmass = invmass;
            ele_index = j;
          }
          if(j==(edge_ele-1) && TMath::Abs(best_invmass)<5.) {
            isEle_probe_ele[ele_index] = 1;
            //cout << "best_invmass : " << best_invmass << endl;                                                                           
          }
        }
      }
    }
    


    /*
    
    for(int i=0; i<nPhot; i++) {
      invmass = -999.;
      best_invmass = -999;
      
      //      d_invmass = 30.;
      //d_invmass = 90.;
      if(isEle_probe[i]) {
	for(int j=0; j<nEle; j++) {
	  sum_nomatch = vector_ele[j] + vector_phot[i];
	  invmass = sum_nomatch.M();
	  //cout << "invmass : " << invmass << endl;
	  if(TMath::Abs(invmass)<best_invmass ){
	    best_invmass = invmass;
	    ele_index = j;
	  }
	  if(j==(nEle-1) && TMath::Abs(best_invmass)<5.) isEle_probe_ele[ele_index] = 1;
	}
      }
    }
    */
    //compute invmass for each couple (should eliminate double counting and invmass=0)
    int ncouples =0;
    for (int i=0; i<edge_ele; i++){
      if(isEle_tag[i]) {
	for (int j=i+1;  j<edge_ele; j++){
	  if(isEle_probe_ele[j]){
	    sum = vector_ele[i]+vector_ele[j];
	    invmass = sum.M();
	    vec_invmass[ncouples] = invmass;
	    ncouples++;
	  }
	  
	}
      }
    }
    
    //if(ncouples>0){
    //  cout << "ncouples = " << ncouples << endl;
    //  cout << "combinatorio = " << endl;
    //}
    
    
    /*
      For(int i=0; i<nEle; i++) {
      invmass = -999.;
      best_invmass = -999.;
      
      //      d_invmass = 30.;
      d_invmass = 90.;
      if(isEle_tag[i]) {
	for(int j=0; j<nPhot; j++) {
	  if(isEle_probe[j] ){
	    sum_nomatch = vector_ele[i] + vector_ele[j];
	    invmass = sum_nomatch.M();
	    //cout << "invmass : " << invmass << endl;
	    if(TMath::Abs(invmass-90.)<d_invmass ){
	      d_invmass = TMath::Abs(invmass-90);
	      best_invmass = invmass;
	    }
      */


    int thereIsOneTag = 0; 
    for (int i=0; i<edge_ele; i++) {
      if(isEle_tag[i]) thereIsOneTag += 1;
    }
    
    if(thereIsOneTag) {
      for (int j=0; j<edge_phot; j++) {
	if(isEle_probe[j]) {
	  
	  //------------------------------------------
	  //                bool elepass (loose WP)
	  //------------------------------------------
	  photonIDCuts2012(j, eleprobe_loose2012, idpasseleprobe2012);
	  if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       passLoose_ElePtEta[j] = 1;    
	  if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	     //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	     )   passLoose_EleID[j] = 1;          
	  //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passLoose_EleImpactPar[i] = 0;   
	  //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passLoose_EleIsoRel[i] = 0;      
	  //if(idpasseleprobe2012[12])      passLoose_EleMinHits[i] = 0;     
	
	  if((ptPhot[j]>20 && TMath::Abs(etascPhot[j])<2.5) && passLoose_ElePtEta[j]==0)  {
	    cout << "not passing pt and eta cut : ptPhot = " << ptPhot[j] << "   etascPhot = " << etascPhot[j] << endl;
	    cout << "pass pt : " << *idpasseleprobe2012[0] << "   pass eta : " << *idpasseleprobe2012[1] << "   pass eta_crack : " << *idpasseleprobe2012[2] << "   passLoose_ElePtEta : " << passLoose_ElePtEta[j] << endl;
	    
	  }
  
	  //------------------------------------------
	  //                bool elepass (medium WP)
	  //------------------------------------------
	  photonIDCuts2012(j, eleprobe_medium2012, idpasseleprobe2012);
	  if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       passMedium_ElePtEta[j] = 1;    
	  if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	     //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	     )   passMedium_EleID[j] = 1;          
	  //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passMedium_EleImpactPar[i] = 0;   
	  //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passMedium_EleIsoRel[i] = 0;      
	  //if(idpasseleprobe2012[12])      passMedium_EleMinHits[i] = 0;     
	  
	  //------------------------------------------
	  //                bool elepass (tight WP)
	  //------------------------------------------
	  photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012);
	  if(*idpasseleprobe2012[0] && *idpasseleprobe2012[1] && *idpasseleprobe2012[2])       passTight_ElePtEta[j] = 1;    
	  if(*idpasseleprobe2012[3] && *idpasseleprobe2012[4] 
	     //&& idpasseleprobe2012[5] && idpasseleprobe2012[6] && idpasseleprobe2012[7]
	     )   passTight_EleID[j] = 1;          
	  //if(idpasseleprobe2012[8] && idpasseleprobe2012[9])       passTight_EleImpactPar[i] = 0;   
	  //if(idpasseleprobe2012[10] && idpasseleprobe2012[11])     passTight_EleIsoRel[i] = 0;      
	  //if(idpasseleprobe2012[12])      passTight_EleMinHits[i] = 0;     
	  
	}
      }
    }

  

    //    cout << "Photon ID MVA" << endl;
    /****************************************************
     *                                                  *
     *                PHOTON ID MVA                     *
     *                                                  *
     ****************************************************/
   
    Float_t theIdMva[20];
    for(int iGamma=0; iGamma<20; iGamma++) {
      theIdMva[iGamma] = -999.;
    }
    // photon ID MVA
    for(int iGamma=0; iGamma<edge_phot; iGamma++) {
      /*if(isEleProbe[iGamma])*/  theIdMva[iGamma] = PhotonIDMVA(iGamma);   
    }

    //cout << "starting SAVING RECO VARIABLES IN TTREE " << endl;  
      
    /*****************************************************
     *                                                  *
     *        SAVING RECO VARIABLES IN TTREE            *
     *                                                  *
     ****************************************************/
    
    
    //if(nEle>10) edge = 10;
    //else edge = nEle;    

    for(int i=0; i<edge_ele; i++) {
      isEleTag_match[i] = isEle_tag_match[i];
      isEleProbe_ele_match[i] = isEle_probe_ele_match[i];
      genEleMatched_index_tag[i] = vec_genMatched_index_tag[i];
      deltaR_EleTagGenReco[i] = vec_deltaR_tag[i];
      
      isEleTag[i] = isEle_tag[i];
      isEleProbe_ele[i] = isEle_probe_ele[i];
      
    }
    

    //if(nPhot>10) edge = 10;
    //else edge = nPhot;    
    for(int i=0; i<edge_phot; i++) {

      r9Phot[i] = r9_phot[i]      ;
      s4RatioPhot[i] = s4Ratio_phot[i] ;
      sigmaRRPhot[i] = sigmaRR[i]      ;

      BDT_output[i] = theIdMva[i] ;
      
      genEleMatched_index_probe[i] = vec_genMatched_index_probe[i];
      deltaR_EleProbeGenReco[i] = vec_deltaR_probe[i];
      
      pid_pfIsoCharged01ForCiC_[i] = pid_pfIsoCharged01ForCiC[i][0];
      pid_pfIsoCharged02ForCiC_[i] = pid_pfIsoCharged02ForCiC[i][0];
      pid_pfIsoCharged03ForCiC_[i] = pid_pfIsoCharged03ForCiC[i][0];
      pid_pfIsoCharged04ForCiC_[i] = pid_pfIsoCharged04ForCiC[i][0];
      pid_pfIsoCharged05ForCiC_[i] = pid_pfIsoCharged05ForCiC[i][0];
      pid_pfIsoCharged06ForCiC_[i] = pid_pfIsoCharged06ForCiC[i][0];
      
      passPreselection[i] = pass_preselection[i];      
      if(passPreselection[i]!=1 && passPreselection[i]!=0) cout << "passPreselection : " << passPreselection[i] << endl;

      isEleProbe_match[i] = isEle_probe_match[i];

      passLooseElePtEta_match[i] = passLoose_ElePtEta_match[i];
      passLooseEleID_match[i] = passLoose_EleID_match[i];
      passLooseEleImpactPar_match[i] = passLoose_EleImpactPar_match[i];
      passLooseEleIsoRel_match[i] = passLoose_EleIsoRel_match[i];
      passLooseEleMinHits_match[i] = passLoose_EleMinHits_match[i];
      passMediumElePtEta_match[i] = passMedium_ElePtEta_match[i];
      passMediumEleID_match[i] = passMedium_EleID_match[i];
      passMediumEleImpactPar_match[i] = passMedium_EleImpactPar_match[i];
      passMediumEleIsoRel_match[i] = passMedium_EleIsoRel_match[i];
      passMediumEleMinHits_match[i] = passMedium_EleMinHits_match[i];
      passTightElePtEta_match[i] = passTight_ElePtEta_match[i];
      passTightEleID_match[i] = passTight_EleID_match[i];
      passTightEleImpactPar_match[i] = passTight_EleImpactPar_match[i];
      passTightEleIsoRel_match[i] = passTight_EleIsoRel_match[i];
      passTightEleMinHits_match[i] = passTight_EleMinHits_match[i];
      
      
      isEleProbe[i] = isEle_probe[i];
      
      passLooseElePtEta[i] = passLoose_ElePtEta[i];
      passLooseEleID[i] = passLoose_EleID[i];
      passLooseEleImpactPar[i] = passLoose_EleImpactPar[i];
      passLooseEleIsoRel[i] = passLoose_EleIsoRel[i];
      passLooseEleMinHits[i] = passLoose_EleMinHits[i];
      passMediumElePtEta[i] = passMedium_ElePtEta[i];
      passMediumEleID[i] = passMedium_EleID[i];
      passMediumEleImpactPar[i] = passMedium_EleImpactPar[i];
      passMediumEleIsoRel[i] = passMedium_EleIsoRel[i];
      passMediumEleMinHits[i] = passMedium_EleMinHits[i];
      passTightElePtEta[i] = passTight_ElePtEta[i];
      passTightEleID[i] = passTight_EleID[i];
      passTightEleImpactPar[i] = passTight_EleImpactPar[i];
      passTightEleIsoRel[i] = passTight_EleIsoRel[i];
      passTightEleMinHits[i] = passTight_EleMinHits[i];

      
      /*
      if((ptPhot[i]>20 && TMath::Abs(etascPhot[i])<2.5) && passLoose_ElePtEta_match[i]==0)  {
	cout << "not passing pt and eta cut : ptPhot = " << ptPhot[i] << "   etascPhot[i] = " << etascPhot[i] << endl;
	cout << "   passLooseElePtEta_match : " << passLooseElePtEta_match[i] <<"   passLoose_ElePtEta_match : " << passLoose_ElePtEta_match[i] << endl;
	
      }
      */
  
    }     
     /*
    cout << "isEle_probe_match = (" << isEleProbe_match[0];
    for(int i=1; i<nEle; i++) {
      cout  << "," << isEleProbe_match[i];
    }
    cout << ")" << endl; 
    
    cout << "isEleTag_match = (" << isEleTag_match[0];
    for(int i=1; i<nEle; i++) {
      cout  << "," << isEleTag_match[i];
      }
      cout << ")" << endl; 
     */
    for(int i=0; i<20; i++) {
      invMassEle_match[i] = vec_invmass_match[i];
      invMassEle[i] = vec_invmass[i];
    }
    nvtx = nvertex;
    runRN = run;
    eventRN = event;
    lumi = lbn;
    
    // check LO gammas - to remove duplicate events in different MC samples
    LOGamma  = countLOGenGamma();
    ISRGamma = countISRGenGamma();
    FSRGamma = countFSRGenGamma();
    
    // check if the first vertex is good
    vtxId=0;
    float rhoVtx=sqrt(vx[0]*vx[0]+vy[0]*vy[0]);
    if (vndof[0]<4 || fabs(vz[0])>24. || rhoVtx>2.) vtxId=-555;
    
    int fillTree = 0;
    fillTree = (thereIsOneTag_match || thereIsOneTag);  //at least one tag
        
    //cout << "fill the tree : " << fillTree << endl;

    if(fillTree && jentry%10000==0 ) {
      
      cout << endl << "event : " << event << endl;
      cout << "ptPhot     etascPhot    isElePRobe_match    isEleProbe" << endl;
      for(int i=0; i<nPhot; i++){
	cout << ptPhot[i] << "    "  << etascPhot[i] << "    " << isEleProbe_match[i] << "     " << isEleProbe[i] << endl;
      }
      cout << "electron_pt     electron_eta    isEleTag    isEleProbe_ele" << endl;
      for(int i=0; i<nEle; i++) {
	cout << electron_pt[i] << "   " << electron_eta[i] << "    " << isEleTag[i] << "    " << isEleProbe_ele[i] << endl;
      }
    }
     

    if(fillTree)  ana_tree->Fill();

    
    /*
    cout << "Fill some histograms" << endl;

    // 
    //                I TAG SONO ANCHE PROBE !!
    //

    for(int i=0; i<nEle; i++) {
      if(isEleTag_match[i]) {
	for(int j=0; j<nPhot; j++) {
	  if(isEleProbe_ele_match[j] ){	
	    
	    //fill histograms
	    if     (TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)   h_ptProbe_denominator_match_0->Fill(ptPhot[j], weight);  
	    else if(TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_ptProbe_denominator_match_1->Fill(ptPhot[j], weight);
	    else if(TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)  h_ptProbe_denominator_match_2->Fill(ptPhot[j], weight);
	    else if(TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)  h_ptProbe_denominator_match_3->Fill(ptPhot[j], weight);
	  
	    if     (photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)   h_ptProbe_match_0->Fill(ptPhot[j], weight);  
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_ptProbe_match_1->Fill(ptPhot[j], weight);
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)  h_ptProbe_match_2->Fill(ptPhot[j], weight);
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)  h_ptProbe_match_3->Fill(ptPhot[j], weight);
          

	  }
	}
      }
    }
  
    for(int i=0; i<nEle; i++) {
      if(isEleTag[i]) {
	for(int j=0; j<nPhot; j++) {

	    if     (TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)   h_ptProbe_denominator_0->Fill(ptPhot[j], weight);  
	    else if(TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_ptProbe_denominator_1->Fill(ptPhot[j], weight);
	    else if(TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)  h_ptProbe_denominator_2->Fill(ptPhot[j], weight);
	    else if(TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)  h_ptProbe_denominator_3->Fill(ptPhot[j], weight);
	    	  

	    if     (photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)   h_ptProbe_0->Fill(ptPhot[j], weight);  
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_ptProbe_1->Fill(ptPhot[j], weight);
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)  h_ptProbe_2->Fill(ptPhot[j], weight);
	    else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)  h_ptProbe_3->Fill(ptPhot[j], weight);
          

	}
      }
    }

    for(int i=0; i<nEle; i++) {
      
      for(int j=0; j<nEle; j++) {
	if(isEleProbe_ele[j]){
	  if     (TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)      h_pt_denominator_0->Fill(ptPhot[j], weight);
	  else if(TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_pt_denominator_1->Fill(ptPhot[j], weight);
	  else if(TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)    h_pt_denominator_2->Fill(ptPhot[j], weight);
	  else if(TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)      h_pt_denominator_3->Fill(ptPhot[j], weight);
	  
	  if     (photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0. && TMath::Abs(etascPhot[j])<0.8)      h_pt_0->Fill(ptPhot[j], weight);
	  else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>0.8 && TMath::Abs(etascPhot[j])<1.4442)  h_pt_1->Fill(ptPhot[j], weight);
	  else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.)    h_pt_2->Fill(ptPhot[j], weight);
	  else if(photonIDCuts2012(j, eleprobe_tight2012, idpasseleprobe2012) && TMath::Abs(etascPhot[j])>2. && TMath::Abs(etascPhot[j])<2.5)      h_pt_3->Fill(ptPhot[j], weight);
	  
	}
      }
      
    }

    
    */
     


  /*
    h_effVSpt_eta_0 = (TH1F*)h_ptProbe_match_0->Clone("h_effVSpt_eta_0");
    h_effVSpt_eta_1 = (TH1F*)h_ptProbe_match_1->Clone("h_effVSpt_eta_1"); 
    h_effVSpt_eta_2 = (TH1F*)h_ptProbe_match_2->Clone("h_effVSpt_eta_2"); 
    h_effVSpt_eta_3 = (TH1F*)h_ptProbe_match_3->Clone("h_effVSpt_eta_3"); 
    
    
    h_effVSpt_eta_0->Divide(h_ptProbe_denominator_match_0);
    h_effVSpt_eta_1->Divide(h_ptProbe_denominator_match_1);
    h_effVSpt_eta_2->Divide(h_ptProbe_denominator_match_2);
    h_effVSpt_eta_3->Divide(h_ptProbe_denominator_match_3);
  */
  

    //cout << "closing the loop" << endl;

  }    
    
    cout << "nNoMatching : " << nNoMatching << " of  " << nEleEvents << "  events with 2 gen electrons" << endl;  
    cout << "nNoReco : " << nNoReco << " of  " << nEleEvents << "  events with 2 gen electrons" << endl;
    cout << "neletag tot : " << nEleTag_tot <<   " of  " << nEleEvents*2. << "  gen electrons     tag_eff = " << nEleTag_tot/(nEleEvents*2.) << endl;
    cout << "neleprobe tot : " << nEleProbe_tot <<   " of  " << nEleEvents*2. << "  gen electrons   probe_eff = " << nEleProbe_tot/(nEleEvents*2.) << endl;
    
    delete aHLTNames;
    
    
    // h_genNotMatched->Write();  
    //ana_tree->Write();
    
}

  
bool TagAndProbeTree::PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) {

  int photon_category = PhotonCategory(photon_index);

  float mitCuts_hoe[4]                 = {0.082,0.075,0.075,0.075};                                        
  float mitCuts_sieie[4]               = {0.014,0.014,0.034,0.034};                                        
  float mitCuts_ecaliso[4]             = {50,4,50,4};                                                      
  float mitCuts_hcaliso[4]             = {50,4,50,4};                                                      
  float mitCuts_trkiso[4]              = {50,4,50,4};                                                      
  //float mitCuts_hcalecal[4]            = {3,3,3,3};                                                        
  //float mitCuts_abstrkiso[4]           = {2.8,2.8,2.8,2.8};                                                
  //float mitCuts_trkiso_hollow03[4]     = {4,4,4,4};                                                       
  //float mitCuts_drtotk_25_99[4]	= {0.26,0.029,0.0062,0.0055};
  float mitCuts_pfiso[4]               = {4,4,4,4};
  
  float val_hoe        = pid_HoverE[photon_index];
  float val_sieie      = pid_etawid[photon_index];                                                          
  float val_ecaliso = pid_jurECAL03[photon_index] - 0.012*ptPhot[photon_index];                              
  float val_hcaliso = pid_twrHCAL03[photon_index] - 0.005*ptPhot[photon_index]; 
  float val_trkiso  = pid_hlwTrack03[photon_index] - 0.002*ptPhot[photon_index]; 
  
  //float val_hcalecal   = (pho_ecalsumetconedr03[photon_index]+pho_hcalsumetconedr03[photon_index]-rho_algo1*rhofac);                                             
  //float val_abstrkiso  = (*pho_tkiso_recvtx_030_002_0000_10_01)[photon_index][vertex_index];                
  //float val_trkiso_hollow03 = pho_trksumpthollowconedr03[photon_index];                                    
  //float val_drtotk_25_99 = pho_drtotk_25_99[photon_index];
  int val_pho_isconv = !hasMatchedPromptElePhot[photon_index];
  float val_pfiso02 = pid_pfIsoCharged02ForCiC[photon_index][vertex_index];

  
      
  if (val_hoe             >= mitCuts_hoe[photon_category]         ) return false;                                           
  if (val_sieie           >= mitCuts_sieie[photon_category]       ) return false;
  if (val_ecaliso         >= mitCuts_ecaliso[photon_category]     ) return false;
  if (val_hcaliso         >= mitCuts_hcaliso[photon_category]     ) return false;                                           
  if (val_trkiso          >= mitCuts_trkiso[photon_category]      ) return false;
  
  if ((!val_pho_isconv && electronVeto) ) return false; // Electron Rejection based Conversion Safe Veto

  if (val_pfiso02 >= mitCuts_pfiso[photon_category]) return false;            
  
  return true;
}


void TagAndProbeTree::SetPuWeights(std::string puWeightFile)
{
  if (puWeightFile == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }
  
  std::cout << "PU REWEIGHTING:: Using file " << puWeightFile << std::endl;
  
  TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  f_pu->cd();
  
  TH1D *puweights = 0;
  TH1D *gen_pu = 0;
  
  gen_pu= (TH1D*) f_pu->Get("generated_pu");
  puweights= (TH1D*) f_pu->Get("weights");
  
  if (!puweights || !gen_pu) {
    std::cout << "weights histograms  not found in file " << puWeightFile << std::endl;
    return;
  }
  
  TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
  weightedPU->Multiply(puweights);
  //Rescaling weights in order to preserve same integral of events
  TH1D* weights= (TH1D*)puweights->Clone("rescaledWeights");
  weights->Scale( gen_pu->Integral(1,MAX_PU_REWEIGHT) / weightedPU->Integral(1,MAX_PU_REWEIGHT) );
  
  float sumPuWeights=0.;
  for (int i = 0; i<MAX_PU_REWEIGHT; i++) {
    float weight=1.;
    weight=weights->GetBinContent(i+1);
    sumPuWeights+=weight;
    puweights_.push_back(weight);
  }
}


// leave the main pu weight as it is. Add this new one for dedicated HLT patsh
void TagAndProbeTree::SetPuWeightsHLT(std::string puWeightFileHLT, int hltThresh)
{
  if (puWeightFileHLT == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }
  
  std::cout << "PU REWEIGHTING:: Using file " << puWeightFileHLT << " with HLT threshold " << hltThresh << std::endl;
  
  TFile *f_pu  = new TFile(puWeightFileHLT.c_str(),"READ");
  f_pu->cd();
  
  TH1D *puweights = 0;
  TH1D *gen_pu = 0;
  
  gen_pu= (TH1D*) f_pu->Get("generated_pu");
  puweights= (TH1D*) f_pu->Get("weights");
  
  if (!puweights || !gen_pu) {
    std::cout << "weights histograms not found in file " << puWeightFileHLT << std::endl;
    return;
  }
  
  TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
  weightedPU->Multiply(puweights);
  //Rescaling weights in order to preserve same integral of events
  TH1D* weights= (TH1D*)puweights->Clone("rescaledWeights");
  weights->Scale( gen_pu->Integral(1,MAX_PU_REWEIGHT) / weightedPU->Integral(1,MAX_PU_REWEIGHT) );
  
  float sumPuWeights=0.;
  for (int i = 0; i<MAX_PU_REWEIGHT; i++) {
    float weight=1.;
    weight=weights->GetBinContent(i+1);
    sumPuWeights+=weight;
    if (hltThresh==30) puweights30_.push_back(weight);
    if (hltThresh==50) puweights50_.push_back(weight);
    if (hltThresh==75) puweights75_.push_back(weight);
    if (hltThresh==90) puweights90_.push_back(weight);
  }
}




void TagAndProbeTree::ClusterShape(Int_t* i, Float_t* tmva_photonid_sieie, Float_t* tmva_photonid_etawidth, Float_t* tmva_photonid_phiwidth, Float_t* tmva_photonid_r9, Float_t* tmva_photonid_s4ratio)
{
  /*
  //  Float_t mva = 999.;
  tmva_photonid_sieie        = pid_etawid[i];
  tmva_photonid_sieip        = sEtaPhiPhot[i];
  tmva_photonid_etawidth     = pid_scetawid[i];
  tmva_photonid_phiwidth     = pid_scphiwid[i];
  tmva_photonid_r9           = E9Phot[i] / escRawPhot[i];
  tmva_photonid_lambdaratio  = pid_lambdaRatio[i];
  
  tmva_photonid_s4ratio  = E4Phot[i]/E25PhotC[i];
  tmva_photonid_eventrho = rhoAllJets;
  tmva_photonid_sceta    = etascPhot[i];

  float rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
  tmva_photonid_ESEffSigmaRR = 0.0; 
  if(rr2>0. && rr2<999999.) 
    tmva_photonid_ESEffSigmaRR = sqrt(rr2);
    
  
  //  double pfchargedisobad03=0.;
  //for(int ivtx=0; ivtx<nvertex; ivtx++) {
  //  pfchargedisobad03=pid_pfIsoCharged03ForCiC[iPhoton][ivtx]>pfchargedisobad03?pid_pfIsoCharged03ForCiC[iPhoton][ivtx]:pfchargedisobad03;
  //}
  
  
  float rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
  tmva_photonid_ESEffSigmaRR = 0.0; 
  if(rr2>0. && rr2<999999.) 
    tmva_photonid_ESEffSigmaRR = sqrt(rr2);
  
  
  */
  //2012 rescalings for MC
  if (nMC>0)
    {
      if (isEBPhot[*i]) {
	*tmva_photonid_r9 = 1.0045*(*tmva_photonid_r9) + 0.0010;
	*tmva_photonid_s4ratio = 1.01894*(*tmva_photonid_s4ratio) - 0.01034;
	*tmva_photonid_sieie = 0.891832*(*tmva_photonid_sieie) + 0.0009133;
	*tmva_photonid_etawidth =  1.04302*(*tmva_photonid_etawidth) - 0.000618;
	*tmva_photonid_phiwidth =  1.00002*(*tmva_photonid_phiwidth) - 0.000371;
      } else {
	*tmva_photonid_r9 = 1.0086*(*tmva_photonid_r9) - 0.0007;
	*tmva_photonid_s4ratio = 1.04969*(*tmva_photonid_s4ratio) - 0.03642;
	*tmva_photonid_sieie = 0.99470*(*tmva_photonid_sieie) + 0.00003;
	*tmva_photonid_etawidth =  0.903254*(*tmva_photonid_etawidth) + 0.001346;
	*tmva_photonid_phiwidth =  0.99992*(*tmva_photonid_phiwidth) - 0.00000048;
      }
    }


}


bool TagAndProbeTree::leptonCutsEle2012(int i, electronidcuts2012 const& pid, vector<bool> *vpass) {

  /*****************************************************************************
   *                                                                           *
   *                     ELECTRON SELECTION (for tag)                          *
   *                                                                           *  
   *****************************************************************************/
  
    bool pt, eta, crack;
    bool setaeta, deta, dphi, hoe, oeMop;
    bool minhits, matchconv;
    bool d0, dz;
    bool isol;
    
    // acceptance                                                                                                                            
    pt    = electron_pt[i] > pid.pt;
    eta   = fabs(electron_sc_eta[i]) < pid.eta;
    crack = fabs(electron_sc_eta[i]) < pid.crack1 || fabs(electron_sc_eta[i]) > pid.crack2;
    
    ////////////////////////////////////////////////////////////////////
    // impact parameters                                                                                                                     
    //  float d0Ele = eleDxyPV(i,vrankPhotonPairs[0]);
    //  float dzEle = eleDzPV(i,vrankPhotonPairs[0]); 
    float d0Ele = eleDxyPV(i,0);
    float dzEle = eleDzPV(i, 0); 
    
    //  cout << "vrankPhotonPairs[0] = " << vrankPhotonPairs[0] << endl;
    
    
    // effective areas - chiara: ancora da controllare. Va usato 2012 x area effettiva o 2011? quale somma prendo?
    float abseta = fabs(electron_sc_eta[i]);
    ElectronEffectiveArea::ElectronEffectiveAreaType effAreaGammaAndNeutralHad_ = ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03;
    ElectronEffectiveArea::ElectronEffectiveAreaTarget effAreaTarget_   = ElectronEffectiveArea::kEleEAData2012;
    float eff_area_ganh = ElectronEffectiveArea::GetElectronEffectiveArea(effAreaGammaAndNeutralHad_, abseta, effAreaTarget_);
    
    // isolation                                                                                                                             
    float theIsolation = electron_chHad03Iso[i];
    theIsolation += max<float>(0.,(electron_nHad03Iso[i]+electron_phot03Iso[i]-eff_area_ganh*rhoAllJets));
    
    
    
    // full selection                                                                                                                        
    if (abseta<1.4442) {
      setaeta   = electron_SigmaIetaIeta[i] < pid.setaetaEB;
      deta      = fabs(electron_dEtaIn[i]) < pid.detaEB;
      dphi      = fabs(electron_dPhiIn[i]) < pid.dphiEB;
      hoe       = electron_HoE[i] < pid.hoeEB;
      oeMop     = fabs(1./electron_ecalEnergy[i] - 1./electron_trackPatVtx[i]) < pid.oemopEB ;
      d0        = fabs(d0Ele) < pid.d0EB;
      dz        = fabs(dzEle) < pid.dzEB;
      minhits   = electron_misHits[i] <= pid.minhitsEB;
      matchconv = electron_matchedConv[i]==0;
      isol      = theIsolation < electron_pt[i]* pid.iso_relEB;
    } else {
      setaeta = electron_SigmaIetaIeta[i] < pid.setaetaEE;
      deta    = fabs(electron_dEtaIn[i]) < pid.detaEE;
      dphi    = fabs(electron_dPhiIn[i]) < pid.dphiEE;
      hoe     = electron_HoE[i] < pid.hoeEE;
      oeMop   = fabs(1./electron_ecalEnergy[i] - 1./electron_trackPatVtx[i]) < pid.oemopEE;
      d0      = fabs(d0Ele) < pid.d0EE;
      dz      = fabs(dzEle) < pid.dzEE;
      minhits = electron_misHits[i] <= pid.minhitsEE;
      matchconv = electron_matchedConv[i]==0;
      isol    = theIsolation < electron_pt[i]* pid.iso_relEE;
  }

    if (vpass) {
      if((*vpass).size()!=13) { cout << "major failure in LeptonCutsEle2012! (*vpass).size()!=13.. die!" << endl; exit(0) ; }
      (*vpass)[0]  = pt;
      (*vpass)[1]  = eta;
      (*vpass)[2]  = crack;
      (*vpass)[3]  = setaeta;
      (*vpass)[4]  = deta;
      (*vpass)[5]  = dphi;
      (*vpass)[6]  = hoe;
      (*vpass)[7]  = oeMop;
      (*vpass)[8]  = d0;
      (*vpass)[9]  = dz;
      (*vpass)[10] = minhits;
      (*vpass)[11] = matchconv;
      (*vpass)[12] = isol;
    }
  
    return (pt && eta && crack && setaeta && deta && dphi && hoe && oeMop && d0 && dz && minhits && matchconv && isol);
}



bool TagAndProbeTree::photonIDCuts2012(int i, photonidcuts2012 const& pid, bool* vpass[]) {
//bool TagAndProbeTree::photonIDCuts2012(int i, photonidcuts2012 const& pid, vector<bool*> vpass) {

  /*****************************************************************************
   *                                                                           *
   *                                PHOTON                                     *
   *                                                                           *  
   *****************************************************************************/
  
  /////////////////////////////////     for the photon  ///////////////////////////////////////////////////////////////////

    
    bool pt, eta, crack;
    bool setaeta, hoe;
    bool electronveto;
    bool isol;
    
    // selection
    pt    = ptPhot[i] > pid.pt;
    eta   = fabs(etascPhot[i]) < pid.eta;
    crack = fabs(etascPhot[i]) < pid.crack1 || fabs(etascPhot[i]) > pid.crack2;
    
    //cout << "ptPhot : " <<  ptPhot[i] << "   etascPhot : " << etascPhot[i] << endl; 
    //cout  << "pt :  " << pt << "  eta : " << eta << "   crack : " << crack << endl << endl;
    
    //  cout << "vrankPhotonPairs[0] = " << vrankPhotonPairs[0] << endl;
    
    float abseta = fabs(etascPhot[i]);
    
    // ID selection (not isolation)
    if (abseta<1.4442) {
      setaeta   = pid_etawid[i] < pid.setaetaEB;
      hoe       = pid_HoverE[i] < pid.hoeEB;

    } else {
      setaeta = pid_etawid[i] < pid.setaetaEE;
      hoe     = pid_HoverE[i] < pid.hoeEE;
    }

    //if (vpass) {
    //if((*vpass).size()!=5) { cout << "major failure in PhotonCuts2012! (*vpass).size()!=5.. die!" << endl; exit(0) ; }

   
    //(*vpass[0])  = pt;	
    //(*vpass)[1]  = eta;	
    //(*vpass)[2]  = crack;	
    //(*vpass)[3]  = setaeta;	
    //(*vpass)[4]  = hoe;       

    //}
   
    vpass[0]  = &pt;	
    vpass[1]  = &eta;	
    vpass[2]  = &crack;	
    vpass[3]  = &setaeta;	
    vpass[4]  = &hoe;       
    

    //cout << *(vpass[3]) << "    " << (*vpass)[3] << endl;

    return (pt && eta && crack && setaeta && hoe );

}


double TagAndProbeTree::eleDzPV(int iele, int iPV) {
  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(electron_vx[iele],electron_vy[iele],electron_vz[iele]);  
  TVector3 lepMom(electron_px[iele],electron_py[iele],electron_pz[iele]);
  return trackDzPV(PVPos,lepVPos,lepMom);
}

double TagAndProbeTree::eleDxyPV(int iele, int iPV) {
  TVector3 PVPos(vx[iPV],vy[iPV],vz[iPV]);
  TVector3 lepVPos(electron_vx[iele],electron_vy[iele],electron_vz[iele]);
  TVector3 lepMom(electron_px[iele],electron_py[iele],electron_pz[iele]);
  return trackDxyPV(PVPos,lepVPos,lepMom);
}

double TagAndProbeTree::trackDzPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom) {
  float trackPt = trackMom.Pt();
  return (trackVPos.Z()-PVPos.Z()) - ((trackVPos.X()-PVPos.X())*trackMom.X()+(trackVPos.Y()-PVPos.Y())*trackMom.Y())/trackPt *trackMom.Pz()/trackPt;
}

double TagAndProbeTree::trackDxyPV(TVector3 PVPos, TVector3 trackVPos, TVector3 trackMom) {
  return ( - (trackVPos.X()-PVPos.X())*trackMom.Y() + (trackVPos.Y()-PVPos.Y())*trackMom.X() ) / trackMom.Pt();
}


// to compute photonID MVA
Float_t TagAndProbeTree::PhotonIDMVA(Int_t i) {

  Float_t mva = 999.;

  float rr2 = 0;
  rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
  //tmva_photonid_ESEffSigmaRR = 0.0; 
  float rr = TMath::Sqrt(rr2); 

  float r9phot = E9Phot[i] / escRawPhot[i];
  float s4phot = E4Phot[i] / E25Phot[i];
  

  tmva_photonid_etawidth     = pid_scetawid[i];
  tmva_photonid_phiwidth     = pid_scphiwid[i];
  tmva_photonid_sieie        = pid_etawid[i];
  tmva_photonid_sieip        = sEtaPhiPhot[i];
  tmva_photonid_s4ratio      = s4phot;
  tmva_photonid_r9           = r9phot;
  tmva_photonid_pt           = ptPhot[i];
  tmva_photonid_sceta        = etascPhot[i];
  tmva_photonid_rr           = 0.0; 
  tmva_photonid_eventrho     = rhoAllJets;
  
  if (rr>0. && rr<99999.) tmva_photonid_rr = rr;


  bool isEBphot = true;
  if (fabs(etascPhot[i])>1.5) isEBphot = false; 

  if (isEBphot)
    mva = tmvaReaderID_Single_Barrel->EvaluateMVA("BDT");
  else
    mva = tmvaReaderID_Single_Endcap->EvaluateMVA("BDT");
  
  //  cout << "mva : " << mva << endl;
  return mva;
}

void TagAndProbeTree::SetAllMVA() {

  tmvaReaderID_Single_Barrel = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Barrel->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Barrel->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Barrel->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Barrel->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  //tmvaReaderID_Single_Barrel->AddVariable("ptPhot_presel",       &tmva_photonid_pt );
  tmvaReaderID_Single_Barrel->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Barrel->AddVariable("rhoAllJets",          &tmva_photonid_eventrho );
  tmvaReaderID_Single_Barrel->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );
  tmvaReaderID_Single_Barrel->AddSpectator("ptPhot_presel",      &tmva_photonid_pt );

  tmvaReaderID_Single_Endcap = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Endcap->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Endcap->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Endcap->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Endcap->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  //tmvaReaderID_Single_Endcap->AddVariable("ptPhot_presel",       &tmva_photonid_pt );
  tmvaReaderID_Single_Endcap->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Endcap->AddVariable("rhoAllJets",          &tmva_photonid_eventrho );
  tmvaReaderID_Single_Endcap->AddVariable("rr_presel",           &tmva_photonid_rr );
  tmvaReaderID_Single_Endcap->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );
  tmvaReaderID_Single_Endcap->AddSpectator("ptPhot_presel",      &tmva_photonid_pt );

  /*
    std::cout << "Booking PhotonID EB MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EB/TMVAClassification_BDT.weights.xml" << endl;
    tmvaReaderID_Single_Barrel->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EB/TMVAClassification_BDT.weights.xml");
    std::cout << "Booking PhotonID EE MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EE/TMVAClassification_BDT.weights.xml" << endl;
    tmvaReaderID_Single_Endcap->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EE/TMVAClassification_BDT.weights.xml");
  */
  
  std::cout << "Booking PhotonID EB MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EB/TMVAClassification_BDTG.weights.xml" << endl;
  tmvaReaderID_Single_Barrel->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EB/TMVAClassification_BDTG.weights.xml");
  std::cout << "Booking PhotonID EE MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EE/TMVAClassification_BDTG.weights.xml" << endl;
  tmvaReaderID_Single_Endcap->BookMVA("BDT","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_withRho_EE/TMVAClassification_BDTG.weights.xml");
  
}



int TagAndProbeTree::countLOGenGamma(){
  
  int totLO = 0;
  for (int ii=0; ii<nMC; ii++) {
    int myStatus = statusMC[ii];
    int myId     = pdgIdMC[ii];
    if (myStatus==3 && myId==22) {
      int myMoth   = motherIDMC[ii];
      int myMothId = abs(pdgIdMC[myMoth]);
      if (myMothId<=25) totLO++;   // quarks, gluons, W, Z and ZHiggs as mothers
    }
  }
  return totLO;
}

int TagAndProbeTree::countISRGenGamma(){
  
  int totISR = 0;
  for (int ii=0; ii<nMC; ii++) {
    int myStatus = statusMC[ii];
    int myId     = pdgIdMC[ii];
    if (myStatus==1 && myId==22) {
      int myMoth   = motherIDMC[ii];
      int myMothId = abs(pdgIdMC[myMoth]);
      if (myMothId<11 || myMothId==21) totISR++;   // quarks and gluons as mothers
    }
  }
  return totISR;
}

int TagAndProbeTree::countFSRGenGamma(){
  
  int totFSR = 0;
  for (int ii=0; ii<nMC; ii++) {
    int myStatus = statusMC[ii];
    int myId     = pdgIdMC[ii];
    if (myStatus==1 && myId==22) {
      int myMoth   = motherIDMC[ii];
      int myMothId = abs(pdgIdMC[myMoth]);
      if (myMothId>10 && myMothId<21) totFSR++;   // leptons as mothers
    }
  }
  return totFSR;
}
