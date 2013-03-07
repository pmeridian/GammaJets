#include "SingleGammaTree_forMVA.h"
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


SingleGammaTree_forMVA::SingleGammaTree_forMVA(TTree *tree, const TString& outname) : tree_reader_V8(tree), jsonFile(0) //, scaleCorrections_(0)
{  
  hOutputFile = TFile::Open(outname, "RECREATE" ) ;
  
  // must be set by the user 
  EquivLumi = -1.;
  xsection = -1.;
  NtotEvents = -1;
  SampleID = -1;
  gen_=new TRandom3(0);
  
  tmvaReaderID_Single_Endcap=0;
  tmvaReaderID_Single_Barrel=0;
}

SingleGammaTree_forMVA::~SingleGammaTree_forMVA() {
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
}

vector<int> SingleGammaTree_forMVA::firstones(Float_t *vec, vector<bool> *asso, int number){
  
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




void SingleGammaTree_forMVA::Loop() {

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;


  JSON* myjson=0;
  if (jsonFile) {
    std::cout << "Reading JSON" << jsonFile << std::endl;
    myjson=new JSON(jsonFile);
  }
  


  hOutputFile->cd();   
  
  /********************************************************/
  TH1D ptphotgen1("ptphotgen1","ptphotgen1", 100, 0.,300.);
  //int n_ptphotgen1;    
  
  /********************************************************
   *                                                      *
   *                      TREE INIT                       *
   *                                                      *
   ********************************************************/


  int nPhot_presel, nPhot_gen;
  float ptPhot_presel[nPhot_presel];
  float ePhot_presel[nPhot_presel];
  float phiPhot_presel[nPhot_presel];
  float etaPhot_presel[nPhot_presel];

  float deltaRGenReco[nPhot_gen];
  int isMatchedPhot[nPhot_presel];

  float pid_scetawid_presel[nPhot_presel];
  float pid_scphiwid_presel[nPhot_presel]; 
  float sEtaEtaPhot_presel[nPhot_presel];
  float sEtaPhiPhot_presel[nPhot_presel];
  float s4RatioPhot_presel[nPhot_presel];
  float r9Phot_presel[nPhot_presel];
  float etascPhot_presel[nPhot_presel];


  float rr_presel[nPhot_presel];

  //photon id
  float pid_lambdaRatio_presel[nPhot_presel];
  float pid_HoverE_presel[nPhot_presel];

  float pid_jurECAL03_presel[nPhot_presel];
  float pid_twrHCAL03_presel[nPhot_presel];
  float pid_hlwTrack03_presel[nPhot_presel];

  float pid_jurECAL04_presel[nPhot_presel];
  float pid_twrHCAL04_presel[nPhot_presel];
  float pid_hlwTrack04_presel[nPhot_presel];

  float pid_pfIsoCharged01ForCiC_presel[nPhot_presel];
  float pid_pfIsoCharged02ForCiC_presel[nPhot_presel];
  float pid_pfIsoCharged03ForCiC_presel[nPhot_presel];
  float pid_pfIsoCharged04ForCiC_presel[nPhot_presel];
  float pid_pfIsoCharged05ForCiC_presel[nPhot_presel];
  float pid_pfIsoCharged06ForCiC_presel[nPhot_presel];

  float pid_pfIsoPhotons01ForCiC_presel[nPhot_presel];
  float pid_pfIsoPhotons02ForCiC_presel[nPhot_presel];
  float pid_pfIsoPhotons03ForCiC_presel[nPhot_presel];
  float pid_pfIsoPhotons04ForCiC_presel[nPhot_presel];
  float pid_pfIsoPhotons05ForCiC_presel[nPhot_presel];
  float pid_pfIsoPhotons06ForCiC_presel[nPhot_presel];
  
  float pid_pfIsoNeutrals01ForCiC_presel[nPhot_presel];
  float pid_pfIsoNeutrals02ForCiC_presel[nPhot_presel];
  float pid_pfIsoNeutrals03ForCiC_presel[nPhot_presel];
  float pid_pfIsoNeutrals04ForCiC_presel[nPhot_presel];
  float pid_pfIsoNeutrals05ForCiC_presel[nPhot_presel];
  float pid_pfIsoNeutrals06ForCiC_presel[nPhot_presel];
  

  //  TTree* ana_tree_train, ana_tree_test;
  ana_tree_train = new TTree("AnaTree_train","Reduced tree, training ") ;
  ana_tree_test = new TTree("AnaTree_test","Reduced tree, test ") ;
  
  // general
  
  ana_tree_train->Branch("run",&runRN,"run/I");
  ana_tree_train->Branch("event",&eventRN,"event/I");
  ana_tree_train->Branch("lumi",&lumi,"lumi/I");
  ana_tree_train->Branch("nvtx",&nvtx,"nvtx/F");

  ana_tree_train->Branch("npu",&npu,"npu/I");
  ana_tree_train->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree_train->Branch("xsection",&xsection,"xsection/F");
  ana_tree_train->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree_train->Branch("SampleID",&SampleID,"SampleID/I");
  ana_tree_train->Branch("pu_weight",&pu_weight,"pu_weight/F");
  
  // photons
  ana_tree_train->Branch("nPhot_gen",&nPhot_gen,"nPhot_gen/I");
  ana_tree_train->Branch("nPhot_presel",&nPhot_presel,"nPhot_presel/I");
  ana_tree_train->Branch("ptPhot_presel",ptPhot_presel,"ptPhot_presel[nPhot_presel]/F");
  ana_tree_train->Branch("ePhot_presel",ePhot_presel,"ePhot_presel[nPhot_presel]/F");
  ana_tree_train->Branch("etascPhot_presel  ",etascPhot_presel  ,"etascPhot_presel[nPhot_presel]/F");

  /*
  ana_tree_train->Branch("escPhot  ",&escPhot  ,"escPhot[nPhot]/F");
  ana_tree_train->Branch("escRegrPhot  ",&escRegrPhot  ,"escRegrPhot[nPhot]/F");
  ana_tree_train->Branch("escRegrPhotError  ",&escRegrPhotError  ,"escRegrPhotError[nPhot]/F");
  ana_tree_train->Branch("escPhFixPhot  ",&escPhFixPhot  ,"escPhFixPhot[nPhot]/F");
  ana_tree_train->Branch("escPhFixPhotError  ",&escPhFixPhotError  ,"escPhFixPhotError[nPhot]/F");
  ana_tree_train->Branch("escRawPhot  ",&escRawPhot  ,"escRawPhot[nPhot]/F");
  
  ana_tree_train->Branch("phisPhot  ",&phiscPhot  ,"phiscPhot[nPhot]/F");
  ana_tree_train->Branch("xscPhot  ",&xscPhot  ,"xscPhot[nPhot]/F");
  ana_tree_train->Branch("yscPhot  ",&yscPhot  ,"yscPhot[nPhot]/F");
  ana_tree_train->Branch("zscPhot  ",&zscPhot  ,"zscPhot[nPhot]/F");
  ana_tree_train->Branch("xcaloPhot  ",&xcaloPhot  ,"xcaloPhot[nPhot]/F");
  ana_tree_train->Branch("ycaloPhot  ",&ycaloPhot  ,"ycaloPhot[nPhot]/F");
  ana_tree_train->Branch("zcaloPhot  ",&zcaloPhot  ,"zcaloPhot[nPhot]/F");
  ana_tree_train->Branch("eseedPhot  ",&eseedPhot  ,"eseedPhot[nPhot]/F");
  */
  ana_tree_train->Branch("etaPhot_presel",etaPhot_presel,"etaPhot[nPhot_presel]/F");
  ana_tree_train->Branch("phiPhot_presel",phiPhot_presel,"phiPhot[nPhot_presel]/F");
  /*  
  ana_tree_train->Branch("timePhot",&timePhot,"timePhot[nPhot]/F");
  ana_tree_train->Branch("e4SwissCrossPhot",&e4SwissCrossPhot,"e4SwissCrossPhot[nPhot]/F");
  ana_tree_train->Branch("hasPixelSeedPhot",&hasPixelSeedPhot,"hasPixelSeedPhot[nPhot]/I");
  ana_tree_train->Branch("hasMatchedPromptElePhot",&hasMatchedPromptElePhot,"hasMatchedPromptElePhot[nPhot]/I");
  ana_tree_train->Branch("hasMatchedConvPhot",&hasMatchedConvPhot,"hasMatchedConvPhot[nPhot]/I");
  ana_tree_train->Branch("isEBPhot",&isEBPhot, "isEBPhot[nPhot]/O");
  ana_tree_train->Branch("isEEPhot",&isEEPhot, "isEEPhot[nPhot]/O");
  ana_tree_train->Branch("isEBEEGapPhot",&isEBEEGapPhot, "isEBEEGapPhot[nPhot]/O");

  ana_tree_train->Branch("ntracksConvPhot",nTracksConvPhot,"nTracksConvPhot[nPhot]/I");
  ana_tree_train->Branch("isValidVtxConvPhot",isValidVtxConvPhot,"isValidVtxConvPhot[nPhot]/O");
  ana_tree_train->Branch("pairInvmassConvPhot",pairInvariantMassConvPhot,"pairInvariantMassConvPhot[nPhot]/F");
  ana_tree_train->Branch("pairCotThetaSeperationConvPhot",pairCotThetaSeparationConvPhot,"pairCotThetaSeparationConvPhot[nPhot]/F");
  ana_tree_train->Branch("pairmomentumXConvPhot",pairMomentum_xConvPhot,"pairMomentum_xConvPhot[nPhot]/F");
  ana_tree_train->Branch("pairmomentumYConvPhot",pairMomentum_yConvPhot,"pairMomentum_yConvPhot[nPhot]/F");
  ana_tree_train->Branch("pairmomentumZConvPhot",pairMomentum_zConvPhot,"pairMomentum_zConvPhot[nPhot]/F");
  ana_tree_train->Branch("chi2ConvPhot",chi2ConvPhot,"chi2ConvPhot[nPhot]/F");
  ana_tree_train->Branch("nDofConvPhot",nDofConvPhot,"nDofConvPhot[nPhot]/F");
  ana_tree_train->Branch("eOverPConvPhot",eOverPConvPhot,"eOverPConvPhot[nPhot]/F");
  ana_tree_train->Branch("convVxConvPhot",conv_vxConvPhot,"conv_vxConvPhot[nPhot]/F");
  ana_tree_train->Branch("convVyConvPhot",conv_vyConvPhot,"conv_vyConvPhot[nPhot]/F");
  ana_tree_train->Branch("convVzConvPhot",conv_vzConvPhot,"conv_vzConvPhot[nPhot]/F");
  ana_tree_train->Branch("distOfMinimumApproachConvPhot",distOfMinimumApproachConvPhot,"distOfMinimumApproachConvPhot[nPhot]/F");
  ana_tree_train->Branch("dPhiTracksAtVtxConvPhot",dPhiTracksAtVtxConvPhot,"dPhiTracksAtVtxConvPhot[nPhot]/F");
  //   ana_tree_train->Branch("dPhiTracksAtEcalConvPhot",dPhiTracksAtEcalConvPhot,"dPhiTracksAtEcalConvPhot[nPhot]/F");
  //   ana_tree_train->Branch("dEtaTracksAtEcalConvPhot",dEtaTracksAtEcalConvPhot,"dEtaTracksAtEcalConvPhot[nPhot]/F");
  */

  /*
  // Default photon ID
  ana_tree_train->Branch("pid_isEM",&pid_isEM,"pid_isEM[nPhot]/O");
  ana_tree_train->Branch("pid_isLoose",&pid_isLoose,"pid_isLoose[nPhot]/O");
  ana_tree_train->Branch("pid_isTight",&pid_isTight,"pid_isTight[nPhot]/O");
  ana_tree_train->Branch("pid_jurECAL",&pid_jurECAL,"pid_jurECAL[nPhot]/F");
  ana_tree_train->Branch("pid_twrHCAL",&pid_twrHCAL,"pid_twrHCAL[nPhot]/F");
  ana_tree_train->Branch("pid_HoverE",&pid_HoverE,"pid_HoverE[nPhot]/F");
  ana_tree_train->Branch("pid_hlwTrack",&pid_hlwTrack,"pid_hlwTarck[nPhot]/F");
  ana_tree_train->Branch("pid_hlwTrackNoDz",&pid_hlwTrackNoDz,"pid_hlwTrackNoDz[nPhot]/F");
  ana_tree_train->Branch("pid_hlwTrackForCiC",&pid_hlwTrackForCiC,"pid_hlwTrackBestRank[40][100]/F");
  ana_tree_train->Branch("pid_etawid",&pid_etawid,"pid_etawid[nPhot]/F");
  */



  ana_tree_train->Branch("pid_jurECAL03_presel",pid_jurECAL03_presel,"pid_jurECAL03_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_twrHCAL03_presel",pid_twrHCAL03_presel,"pid_twrHCAL03_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_hlwTrack03_presel",pid_hlwTrack03_presel,"pid_hlwTrack03_presel[nPhot_presel]/F");

  ana_tree_train->Branch("pid_jurECAL04_presel",pid_jurECAL04_presel,"pid_jurECAL04_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_twrHCAL04_presel",pid_twrHCAL04_presel,"pid_twrHCAL04_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_hlwTrack04_presel",pid_hlwTrack04_presel,"pid_hlwTrack04_presel[nPhot_presel]/F");

  ana_tree_train->Branch("pid_pfIsoCharged01ForCiC_presel",pid_pfIsoCharged01ForCiC_presel,"pid_pfIsoCharged01ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoCharged02ForCiC_presel",pid_pfIsoCharged02ForCiC_presel,"pid_pfIsoCharged02ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoCharged03ForCiC_presel",pid_pfIsoCharged03ForCiC_presel,"pid_pfIsoCharged03ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoCharged04ForCiC_presel",pid_pfIsoCharged04ForCiC_presel,"pid_pfIsoCharged04ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoCharged05ForCiC_presel",pid_pfIsoCharged05ForCiC_presel,"pid_pfIsoCharged05ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoCharged06ForCiC_presel",pid_pfIsoCharged06ForCiC_presel,"pid_pfIsoCharged06ForCiC_presel[nPhot_presel]/F");
		    				    		    
  ana_tree_train->Branch("pid_pfIsoPhotons01ForCiC_presel",pid_pfIsoPhotons01ForCiC_presel,"pid_pfIsoPhotons01ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoPhotons02ForCiC_presel",pid_pfIsoPhotons02ForCiC_presel,"pid_pfIsoPhotons02ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoPhotons03ForCiC_presel",pid_pfIsoPhotons03ForCiC_presel,"pid_pfIsoPhotons03ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoPhotons04ForCiC_presel",pid_pfIsoPhotons04ForCiC_presel,"pid_pfIsoPhotons04ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoPhotons05ForCiC_presel",pid_pfIsoPhotons05ForCiC_presel,"pid_pfIsoPhotons05ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoPhotons06ForCiC_presel",pid_pfIsoPhotons06ForCiC_presel,"pid_pfIsoPhotons06ForCiC_presel[nPhot_presel]/F");
		    				    		    
  ana_tree_train->Branch("pid_pfIsoNeutrals01ForCiC_presel",pid_pfIsoNeutrals01ForCiC_presel,"pid_pfIsoNeutrals01ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoNeutrals02ForCiC_presel",pid_pfIsoNeutrals02ForCiC_presel,"pid_pfIsoNeutrals02ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoNeutrals03ForCiC_presel",pid_pfIsoNeutrals03ForCiC_presel,"pid_pfIsoNeutrals03ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoNeutrals04ForCiC_presel",pid_pfIsoNeutrals04ForCiC_presel,"pid_pfIsoNeutrals04ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoNeutrals05ForCiC_presel",pid_pfIsoNeutrals05ForCiC_presel,"pid_pfIsoNeutrals05ForCiC_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_pfIsoNeutrals06ForCiC_presel",pid_pfIsoNeutrals06ForCiC_presel,"pid_pfIsoNeutrals06ForCiC_presel[nPhot_presel]/F");
  /*

  ana_tree_train->Branch("ptiso004Phot",&ptiso004Phot,"ptiso004Phot[nPhot]/F");
  ana_tree_train->Branch("ntrkiso004Phot",&ntrkiso004Phot,"ntrkiso004Phot[nPhot]/I");
  ana_tree_train->Branch("ptiso035Phot",&ptiso035Phot,"ptiso035Phot[nPhot]/F");
  ana_tree_train->Branch("ntrkiso035Phot",&ntrkiso035Phot,"ntrkiso035Phot[nPhot]/I");
  ana_tree_train->Branch("ptiso04Phot",&ptiso04Phot,"ptiso04Phot[nPhot]/F");
  ana_tree_train->Branch("ntrkiso04Phot",&ntrkiso04Phot,"ntrkiso04Phot[nPhot]/I");

  ana_tree_train->Branch("hcalovecal04Phot",&hcalovecal04Phot,"hcalovecal04Phot[nPhot]/F"); 
  ana_tree_train->Branch("ecaliso04Phot",&ecaliso04Phot,"ecaliso04Phot[nPhot]/F");  
  */
  ana_tree_train->Branch("pid_scetawid_presel",pid_scetawid_presel,"pid_scetawid_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_scphiwid_presel",pid_scphiwid_presel,"pid_scphiwid_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_lambdaRatio_presel",pid_lambdaRatio_presel,"pid_lambdaRatio_presel[nPhot_presel]/F");
  ana_tree_train->Branch("pid_HoverE_presel",pid_HoverE_presel,"pid_HoverE_presel[nPhot_presel]/F");
  
  /*ana_tree_train->Branch("pid_esXwidth",&pid_esXwidth,"pid_esXwidth[nPhot]/F");
  ana_tree_train->Branch("pid_esYwidth",&pid_esYwidth,"pid_esYwidth[nPhot]/F");
  
  ana_tree_train->Branch("sMajMajPhot",&sMajMajPhot,"sMajMaj2Phot[nPhot]/F");
  ana_tree_train->Branch("sMinMinPhot",&sMinMinPhot,"sMinMin2Phot[nPhot]/F");
  ana_tree_train->Branch("alphaPhot",&alphaPhot,"alphaPhot[nPhot]/F");
  */

  ana_tree_train->Branch("sEtaEtaPhot_presel",sEtaEtaPhot_presel,"sEtaEtaPhot_presel[nPhot_presel]/F");
  ana_tree_train->Branch("sEtaPhiPhot_presel",sEtaPhiPhot_presel,"sEtaPhiPhot_presel[nPhot_presel]/F");
  ana_tree_train->Branch("s4RatioPhot_presel",s4RatioPhot_presel,"s4RatrioPhot_presel[nPhot_presel]/F"); //new
  ana_tree_train->Branch("r9Phot_presel",r9Phot_presel,"r9Phot_presel[nPhot_presel]/F"); //new
  ana_tree_train->Branch("rhoAllJets",&rhoAllJets,"rhoAllJets/F");
  ana_tree_train->Branch("rhoPF",&rhoPF,"rhoPF/F");

  ana_tree_train->Branch("rr_presel",rr_presel,"rr_presel[nPhot_presel]/F"); //new

  /*
  ana_tree_train->Branch("sPhiPhiPhot",&sPhiPhiPhot,"sPhiPhiPhot[nPhot]/F");
  ana_tree_train->Branch("E1Phot",&E1Phot,"E1Phot[nPhot]/F");
  ana_tree_train->Branch("E2OverE9Phot",&E2OverE9Phot,"E2OverE9Phot[nPhot]/F");
  ana_tree_train->Branch("E4Phot",&E4Phot,"E4Phot[nPhot]/F");  
  
  ana_tree_train->Branch("E25Phot",&E25Phot,"E25Phot[nPhot]/F");

  ana_tree_train->Branch("ieleassocPhot",&ieleassocPhot,"ieleassocPhot[nPhot]/I");
  ana_tree_train->Branch("pid_deltaRToTrackPhot",&pid_deltaRToTrackPhot,"pid_deltaRToTrackPhot[nPhot]/F");
  ana_tree_train->Branch("E9Phot",&E9Phot,"E9Phot[nPhot]/F");
  ana_tree_train->Branch("nElePhot",&nElePhot,"nElePhot/I");
  ana_tree_train->Branch("pid_jurECALElePhot ",&pid_jurECALElePhot ,"pid_jurECALElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_twrHCALElePhot ",&pid_twrHCALElePhot ,"pid_twrHCALElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_HoverEElePhot ",&pid_HoverEElePhot ,"pid_HoverEElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_hlwTrackElePhot ",&pid_hlwTrackElePhot ,"pid_hlwTrackElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_etawidElePhot ",&pid_etawidElePhot ,"pid_etawidElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_dphivtxElePhot ",&pid_dphivtxElePhot ,"pid_dphivtxElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_detavtxElePhot ",&pid_detavtxElePhot ,"pid_detavtxElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_mishitsElePhot ",&pid_mishitsElePhot ,"pid_mishitsElePhot[nElePhot]/I");
  ana_tree_train->Branch("pid_distElePhot ",&pid_distElePhot ,"pid_distElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_dcotElePhot ",&pid_dcotElePhot ,"pid_dcotElePhot[nElePhot]/F");
  ana_tree_train->Branch("pid_ptElePhot ",&pid_ptElePhot ,"pid_ptElePhot[nElePhot]/F");
  */

  /*
  // vtx
  ana_tree_train->Branch("vtxId",&vtxId,"vtxId/I");
  ana_tree_train->Branch("vtxPos_x",&vtxPos_x,"vtxPos_x/F");
  ana_tree_train->Branch("vtxPos_y",&vtxPos_y,"vtxPos_y/F");
  ana_tree_train->Branch("vtxPos_z",&vtxPos_z,"vtxPos_z/F");
  ana_tree_train->Branch("allHLTResults",  &aHLTResults);
  */
  ana_tree_train->Branch("isMatchedPhot", isMatchedPhot, "isMatchedPhot[nPhot_presel]/I"  );
  ana_tree_train->Branch("deltaRGenReco", deltaRGenReco, "deltaRGenReco[nPhot_gen]/F"  );
  // triggering paths                                                                                                                 
  ana_tree_train->Branch("firedHLTNames",  &aHLTNames);

  //**************************//
  //         test tree        //
  //**************************//

  ana_tree_test->Branch("run",&runRN,"run/I");
  ana_tree_test->Branch("event",&eventRN,"event/I");
  ana_tree_test->Branch("lumi",&lumi,"lumi/I");
  ana_tree_test->Branch("nvtx",&nvtx,"nvtx/F");

  ana_tree_test->Branch("npu",&npu,"npu/I");
  ana_tree_test->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree_test->Branch("xsection",&xsection,"xsection/F");
  ana_tree_test->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree_test->Branch("SampleID",&SampleID,"SampleID/I");
  ana_tree_test->Branch("pu_weight",&pu_weight,"pu_weight/F");
  
  // photons
  ana_tree_test->Branch("nPhot_gen",&nPhot_gen,"nPhot_gen/I");
  ana_tree_test->Branch("nPhot_presel",&nPhot_presel,"nPhot_presel/I");
  ana_tree_test->Branch("ptPhot_presel",ptPhot_presel,"ptPhot_presel[nPhot_presel]/F");
  ana_tree_test->Branch("ePhot_presel",ePhot_presel,"ePhot_presel[nPhot_presel]/F");
  ana_tree_test->Branch("etascPhot_presel  ",etascPhot_presel  ,"etascPhot_presel[nPhot_presel]/F");
  ana_tree_test->Branch("etaPhot_presel",etaPhot_presel,"etaPhot[nPhot_presel]/F");
  ana_tree_test->Branch("phiPhot_presel",phiPhot_presel,"phiPhot[nPhot_presel]/F");

  // Default photon ID
  ana_tree_test->Branch("pid_jurECAL03_presel",pid_jurECAL03_presel,"pid_jurECAL03_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_twrHCAL03_presel",pid_twrHCAL03_presel,"pid_twrHCAL03_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_hlwTrack03_presel",pid_hlwTrack03_presel,"pid_hlwTrack03_presel[nPhot_presel]/F");

  ana_tree_test->Branch("pid_jurECAL04_presel",pid_jurECAL04_presel,"pid_jurECAL04_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_twrHCAL04_presel",pid_twrHCAL04_presel,"pid_twrHCAL04_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_hlwTrack04_presel",pid_hlwTrack04_presel,"pid_hlwTrack04_presel[nPhot_presel]/F");

  ana_tree_test->Branch("pid_pfIsoCharged01ForCiC_presel",pid_pfIsoCharged01ForCiC_presel,"pid_pfIsoCharged01ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoCharged02ForCiC_presel",pid_pfIsoCharged02ForCiC_presel,"pid_pfIsoCharged02ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoCharged03ForCiC_presel",pid_pfIsoCharged03ForCiC_presel,"pid_pfIsoCharged03ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoCharged04ForCiC_presel",pid_pfIsoCharged04ForCiC_presel,"pid_pfIsoCharged04ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoCharged05ForCiC_presel",pid_pfIsoCharged05ForCiC_presel,"pid_pfIsoCharged05ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoCharged06ForCiC_presel",pid_pfIsoCharged06ForCiC_presel,"pid_pfIsoCharged06ForCiC_presel[nPhot_presel]/F");
		    				    		    
  ana_tree_test->Branch("pid_pfIsoPhotons01ForCiC_presel",pid_pfIsoPhotons01ForCiC_presel,"pid_pfIsoPhotons01ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoPhotons02ForCiC_presel",pid_pfIsoPhotons02ForCiC_presel,"pid_pfIsoPhotons02ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoPhotons03ForCiC_presel",pid_pfIsoPhotons03ForCiC_presel,"pid_pfIsoPhotons03ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoPhotons04ForCiC_presel",pid_pfIsoPhotons04ForCiC_presel,"pid_pfIsoPhotons04ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoPhotons05ForCiC_presel",pid_pfIsoPhotons05ForCiC_presel,"pid_pfIsoPhotons05ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoPhotons06ForCiC_presel",pid_pfIsoPhotons06ForCiC_presel,"pid_pfIsoPhotons06ForCiC_presel[nPhot_presel]/F");
		    				    		    
  ana_tree_test->Branch("pid_pfIsoNeutrals01ForCiC_presel",pid_pfIsoNeutrals01ForCiC_presel,"pid_pfIsoNeutrals01ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoNeutrals02ForCiC_presel",pid_pfIsoNeutrals02ForCiC_presel,"pid_pfIsoNeutrals02ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoNeutrals03ForCiC_presel",pid_pfIsoNeutrals03ForCiC_presel,"pid_pfIsoNeutrals03ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoNeutrals04ForCiC_presel",pid_pfIsoNeutrals04ForCiC_presel,"pid_pfIsoNeutrals04ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoNeutrals05ForCiC_presel",pid_pfIsoNeutrals05ForCiC_presel,"pid_pfIsoNeutrals05ForCiC_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_pfIsoNeutrals06ForCiC_presel",pid_pfIsoNeutrals06ForCiC_presel,"pid_pfIsoNeutrals06ForCiC_presel[nPhot_presel]/F");

  ana_tree_test->Branch("pid_scetawid_presel",pid_scetawid_presel,"pid_scetawid_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_scphiwid_presel",pid_scphiwid_presel,"pid_scphiwid_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_lambdaRatio_presel",pid_lambdaRatio_presel,"pid_lambdaRatio_presel[nPhot_presel]/F");
  ana_tree_test->Branch("pid_HoverE_presel",pid_HoverE_presel,"pid_HoverE_presel[nPhot_presel]/F");

  ana_tree_test->Branch("sEtaEtaPhot_presel",sEtaEtaPhot_presel,"sEtaEtaPhot_presel[nPhot_presel]/F");
  ana_tree_test->Branch("sEtaPhiPhot_presel",sEtaPhiPhot_presel,"sEtaPhiPhot_presel[nPhot_presel]/F");
  ana_tree_test->Branch("s4RatioPhot_presel",s4RatioPhot_presel,"s4RatrioPhot_presel[nPhot_presel]/F"); //new
  ana_tree_test->Branch("r9Phot_presel",r9Phot_presel,"r9Phot_presel[nPhot_presel]/F"); //new
  ana_tree_test->Branch("rhoAllJets",&rhoAllJets,"rhoAllJets/F");
  ana_tree_test->Branch("rhoPF",&rhoPF,"rhoPF/F");

  ana_tree_test->Branch("rr_presel",rr_presel,"rr_presel[nPhot_presel]/F"); //new

  ana_tree_test->Branch("isMatchedPhot", isMatchedPhot, "isMatchedPhot[nPhot_presel]/I"  );
  ana_tree_test->Branch("deltaRGenReco", deltaRGenReco, "deltaRGenReco[nPhot_gen]/F"  );
  // triggering paths                                                                                                                 
  ana_tree_test->Branch("firedHLTNames",  &aHLTNames);



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
    

  /********************************************************
   *                                                      *
   *                       LOOP                           *
   *                                                      *
   ********************************************************/

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (myjson && nMC<=0) 
      if (!myjson->isGoodLS(run,lbn)) continue;
      
    nprocessed++;
    if (nprocessed%1000 == 0) cout << "Events " << nprocessed << " processed; Run " << run << " LS " << lbn << endl;
  
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

      
    /********************************************************
     *                                                      *
     *                 LOOP :: GEN ANALYSIS                 *
     *                                                      *
     ********************************************************/

    int nGenPhot(0);
    vector<bool> photassocMC;
    //    TVector3 recoPhot[nPhot_presel]; 
    vector<TVector3> genPhot, recoPhot;
    TVector3 gen, reco;
       
    /// init of mc related variables
        
    for(int i=0; i<nMC; i++) {
      
      if((pdgIdMC[i] == 22 && statusMC[i] == 3) || 	 
	 (pdgIdMC[i] == 22 && statusMC[i] == 1 && (TMath::Abs(pdgIdMC[motherIDMC[i]])<=10 || TMath::Abs(pdgIdMC[motherIDMC[i]])==21 ) )){

	photassocMC.push_back(1);	

	nGenPhot++;
	gen.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	genPhot.push_back(gen);
      }
      else
	photassocMC.push_back(0);
         
      /// if there are photons coming not from a photon or a higgs
      //if(pdgIdMC[i] == 22 && statusMC[i] == 1 && TMath::Abs(pdgIdMC[motherIDMC[i]])<21) nGenPhot++;

    }
    nPhot_gen = nGenPhot;
    //    if (nGenPhot != 1) cout << "nGenPhot:  " << nGenPhot << endl; 


    /***************************************************
     *                                                 *
     *           IDENTIFYING PHYSICS PROCESS           *
     *                                                 *
     ***************************************************/
    
    //nel vecchio file if(isgjetqcd && counter > 1) continue;    
    
    // gen level gammas
    vector<int> firstfourgenphot   = firstones(ptMC,&photassocMC,4);
    //    vector<int> firstfourlogenphot = firstones(ptMC,&photassocMCLO,4);
    
    // gen level info for leptons from Zs or Ws
    //vector<int> genVHLepton;
    //genVHLepton.push_back(VHLeptonIndexes[0]);
    //genVHLepton.push_back(VHLeptonIndexes[1]);
    
    // pu weights
    npu = pu_n;
    if(npu<MAX_PU_REWEIGHT && puweights_.size()>0 && nMC>0) 
      pu_weight = puweights_[npu];
    else
      pu_weight = 1;
    
    weight=pu_weight;
    
    // to be used after
    ptphotgen1.Fill(ptMC[firstfourgenphot.at(0)],weight);
    


    
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
    // firing HLT paths
    aHLTNames = new std::vector<std::string>;
    aHLTNames -> clear();
    for (int ii=0; ii<(HLTResults->size()); ii++) {
      if ((*HLTResults)[ii]) {
        aHLTNames->push_back((*HLTNames)[ii]);
      }
    }

    
    /***************************************************
     *                                                 *
     *                 RECO PHOTONS                    *
     *                                                 *
     ***************************************************/

    int countPreselPhot = 0;  
    vector<bool> preselPhot;

    for (int i=0; i<nPhot; i++) {
      
      if( ptPhot[i] > 30 //eT threshold  
	  && PhotonMITPreSelection(i,0,1)  //isolation (trigger level)    
	  && ((TMath::Abs(etascPhot[i]) < 1.4442) || (TMath::Abs(etascPhot[i]) > 1.566 && TMath::Abs(etascPhot[i]) < 2.5)) )//ECAL
	{ 
	  countPreselPhot++;
	  preselPhot.push_back(1);
	
	} else{
	preselPhot.push_back(0);
      }
    }

    /****************************************************
     *                                                  *
     *        SAVING RECO VARIABLES IN TTREE    *
     *                                                  *
     ****************************************************/

    nPhot_presel = countPreselPhot;
    vector<float>  pt, energy, eta, phi, s4, r9, etasc, lambdaratio, scetawid, scphiwid, setaeta, setaphi, rr;

    //photon id
    vector<float> ecalIso03, hcalIso03, trackIso03, ecalIso04, hcalIso04, trackIso04, ecalIsoPf01, ecalIsoPf02, ecalIsoPf03, ecalIsoPf04, ecalIsoPf05, ecalIsoPf06,  hcalIsoPf01, hcalIsoPf02, hcalIsoPf03, hcalIsoPf04, hcalIsoPf05, hcalIsoPf06, hovere;
    
    vector<float> trackIsoPf01, trackIsoPf02, trackIsoPf03, trackIsoPf04, trackIsoPf05, trackIsoPf06;
    
    

    if (countPreselPhot > 0) {

      int j = 0;
      for(int i=0; i<nPhot; i++) {
	float rr2 = 0;
	rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
	//tmva_photonid_ESEffSigmaRR = 0.0; 
      
	float r9phot = E9Phot[i] / escRawPhot[i];
	float s4phot = E4Phot[i] / E25Phot[i];
	
	//cout << "setaeta before: " << pid_etawid[i] << "  " << endl;    
	ClusterShape(&i, &pid_etawid[i], &pid_scetawid[i], &pid_scphiwid[i], &r9phot, &s4phot);
	//cout << "setaeta after: " << pid_etawid[i] << "  " << endl << endl;    


	if(preselPhot[i] ) {
	  reco.SetPtEtaPhi(ptPhot[i],etaPhot[i],phiPhot[i]); 
	  recoPhot.push_back(reco);
	  pt.push_back(ptPhot[i]);
	  energy.push_back(ePhot[i]);
	  eta.push_back(etaPhot[i]);	 
	  phi.push_back(phiPhot[i]); 
	  s4.push_back(s4phot);
	  r9.push_back(r9phot);
	  etasc.push_back(etascPhot[i]);
	  lambdaratio.push_back(pid_lambdaRatio[i]);
	  scetawid.push_back(pid_scetawid[i]);
	  scphiwid.push_back(pid_scphiwid[i]);
	  setaeta.push_back(pid_etawid[i]);
	  setaphi.push_back(sEtaPhiPhot[i]);
	  rr.push_back(sqrt(rr2));

	  hovere.push_back(pid_HoverE[i]);
	  ecalIso03.push_back(pid_jurECAL03[i]);		  	   
	  hcalIso03.push_back(pid_twrHCAL03[i]);		  	   
	  trackIso03.push_back(pid_hlwTrack03[i]);
	  ecalIso04.push_back(pid_jurECAL[i]);		  	   
	  hcalIso04.push_back(pid_twrHCAL[i]);		  	   
	  trackIso04.push_back(pid_hlwTrack[i]);	  	   

	  ecalIsoPf01.push_back(pid_pfIsoPhotons01ForCiC[i]);	   
	  ecalIsoPf02.push_back(pid_pfIsoPhotons02ForCiC[i]);	   
	  ecalIsoPf03.push_back(pid_pfIsoPhotons03ForCiC[i]); 	   
	  ecalIsoPf04.push_back(pid_pfIsoPhotons04ForCiC[i]);	   
	  ecalIsoPf05.push_back(pid_pfIsoPhotons05ForCiC[i]);	   
	  ecalIsoPf06.push_back(pid_pfIsoPhotons06ForCiC[i]); 	   
	  hcalIsoPf01.push_back(pid_pfIsoNeutrals01ForCiC[i]);	   
	  hcalIsoPf02.push_back(pid_pfIsoNeutrals02ForCiC[i]);	   
	  hcalIsoPf03.push_back(pid_pfIsoNeutrals03ForCiC[i]);	   
	  hcalIsoPf04.push_back(pid_pfIsoNeutrals04ForCiC[i]);	   
	  hcalIsoPf05.push_back(pid_pfIsoNeutrals05ForCiC[i]);	   
	  hcalIsoPf06.push_back(pid_pfIsoNeutrals06ForCiC[i]);	   
	  
          trackIsoPf01.push_back(pid_pfIsoCharged01ForCiC[i][0]);
	  trackIsoPf02.push_back(pid_pfIsoCharged02ForCiC[i][0]);
	  trackIsoPf03.push_back(pid_pfIsoCharged03ForCiC[i][0]);
	  trackIsoPf04.push_back(pid_pfIsoCharged04ForCiC[i][0]);
	  trackIsoPf05.push_back(pid_pfIsoCharged05ForCiC[i][0]);
	  trackIsoPf06.push_back(pid_pfIsoCharged06ForCiC[i][0]);

	}
      } 
      for(int i=0; i<nPhot_presel; i++) {
	ptPhot_presel[i] = pt[i];
	ePhot_presel[i] = energy[i];
	etaPhot_presel[i] = eta[i];
	phiPhot_presel[i] = phi[i];
	//MVA variables
	pid_scetawid_presel[i] = scetawid[i];
	pid_scphiwid_presel[i] = scphiwid[i];
	sEtaEtaPhot_presel[i] = setaeta[i];
	sEtaPhiPhot_presel[i] = setaphi[i];

	s4RatioPhot_presel[i] = s4[i]; 
	r9Phot_presel[i] = r9[i];
	etascPhot_presel[i] = etasc[i];

	rr_presel[i] = rr[i];

	pid_lambdaRatio_presel[i] = lambdaratio[i]; 
	pid_HoverE_presel[i] = hovere[i];

	//if (TMath::Abs(etasc[i])>1.566) cout << "pt[" << i <<"] = " << pt[i] << "    etasc[" << i << "] = " << etasc[i] << endl;
	//iso variables
	pid_jurECAL03_presel[i] = ecalIso03[i];
	pid_twrHCAL03_presel[i] = hcalIso03[i];
	pid_hlwTrack03_presel[i]= trackIso03[i];
	pid_jurECAL04_presel[i] = ecalIso04[i];
	pid_twrHCAL04_presel[i] = hcalIso04[i];
	pid_hlwTrack04_presel[i]= trackIso04[i];

	pid_pfIsoPhotons01ForCiC_presel[i] = ecalIsoPf01[i];	   
	pid_pfIsoPhotons02ForCiC_presel[i] = ecalIsoPf02[i];	   
	pid_pfIsoPhotons03ForCiC_presel[i] = ecalIsoPf03[i]; 	   
	pid_pfIsoPhotons04ForCiC_presel[i] = ecalIsoPf04[i];	   
	pid_pfIsoPhotons05ForCiC_presel[i] = ecalIsoPf05[i];	   
	pid_pfIsoPhotons06ForCiC_presel[i] = ecalIsoPf06[i]; 	   
	pid_pfIsoNeutrals01ForCiC_presel[i] =hcalIsoPf01[i] ;	   
	pid_pfIsoNeutrals02ForCiC_presel[i] =hcalIsoPf02[i] ;	   
	pid_pfIsoNeutrals03ForCiC_presel[i] =hcalIsoPf03[i] ;	   
	pid_pfIsoNeutrals04ForCiC_presel[i] =hcalIsoPf04[i] ;	   
	pid_pfIsoNeutrals05ForCiC_presel[i] =hcalIsoPf05[i] ;	   
	pid_pfIsoNeutrals06ForCiC_presel[i] =hcalIsoPf06[i] ;	   
	
        pid_pfIsoCharged01ForCiC_presel[i] = trackIsoPf01[i];
	pid_pfIsoCharged02ForCiC_presel[i] = trackIsoPf02[i];
	pid_pfIsoCharged03ForCiC_presel[i] = trackIsoPf03[i];
	pid_pfIsoCharged04ForCiC_presel[i] = trackIsoPf04[i];
	pid_pfIsoCharged05ForCiC_presel[i] = trackIsoPf05[i];
	pid_pfIsoCharged06ForCiC_presel[i] = trackIsoPf06[i];
	
	 
      }


      //matching with gen photon(s)    
      float deltaRmin(0.3);
      int i_nPhot_matched(-1);
      vector<float> deltaR_gen_reco;
      vector<int> i_reco_matched;


      for(int i=0; i<nMC; i++){
	if(photassocMC[i]) {
	  gen.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	  for (int j=0; j<nPhot_presel; j++){
	    if(gen.DeltaR(recoPhot[j]) < deltaRmin) {
	      deltaRmin = gen.DeltaR(recoPhot[j]);
	      i_nPhot_matched = j;   
	    }
	  }

	  //if (i_nPhot_matched >= 0)  {
	  deltaR_gen_reco.push_back(deltaRmin);
	  i_reco_matched.push_back(i_nPhot_matched);
	  //}
	  //else {
	  //   deltaR_gen_reco.push_back(999.);
	  //i_reco_matched.push_back(-1);
	  //cout << "NO MATCHING PHOTON!" << endl;	
	  //}
	}
      }


      /*
      //find the minimum deltaR between couples gen-reco
      deltaRmin=0.3; //reinitialization --> cambiare nomi!!
      i_nPhot_matched = -1;
      for (int i=0; i<deltaR_gen_reco.size(); i++) {
	if(deltaR_gen_reco[i] <  deltaRmin) {
	  deltaRmin = deltaR_gen_reco[i]; 
	  i_nPhot_matched = i_reco_matched[i];
	}
      }
      */

      for(int i=0;  i<nPhot_presel; i++) isMatchedPhot[i] = 0;
      for(int i=0; i<deltaR_gen_reco.size(); i++) {
	if (i_nPhot_matched>=0 ) isMatchedPhot[i_reco_matched[i]] = 1;
	deltaRGenReco[i] = deltaR_gen_reco[i];
      }
      // various
      nvtx = nvertex;
      runRN = run;
      eventRN = event;
      lumi = lbn;
      if(jentry % 2 == 0) ana_tree_train->Fill();
      else if(jentry % 2 == 1) ana_tree_test->Fill();

    }
    delete aHLTNames;        
  }
  ptphotgen1.Write();
  ana_tree_train->Write();

}

bool SingleGammaTree_forMVA::PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) {

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


void SingleGammaTree_forMVA::SetPuWeights(std::string puWeightFile)
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

void SingleGammaTree_forMVA::ClusterShape(Int_t* iPhoton, Float_t* tmva_photonid_sieie, Float_t* tmva_photonid_etawidth, Float_t* tmva_photonid_phiwidth, Float_t* tmva_photonid_r9, Float_t* tmva_photonid_s4ratio)
{
  //  Float_t mva = 999.;
  /*
  double pfchargedisobad03=0.;
  for(int ivtx=0; ivtx<nvertex; ivtx++) {
    pfchargedisobad03=pid_pfIsoCharged03ForCiC[iPhoton][ivtx]>pfchargedisobad03?pid_pfIsoCharged03ForCiC[iPhoton][ivtx]:pfchargedisobad03;
  }
  
  //tmva_photonid_pfchargedisogood03 = pid_pfIsoCharged03ForCiC[iPhoton][vtx];
  //tmva_photonid_pfchargedisobad03  = pfchargedisobad03;
  //tmva_photonid_pfphotoniso03      = pid_pfIsoPhotons03ForCiC[iPhoton];
  //tmva_photonid_pfneutraliso03     = pid_pfIsoNeutrals03ForCiC[iPhoton]; 
  
  tmva_photonid_sieie        = pid_etawid[iPhoton];
  tmva_photonid_sieip        = sEtaPhiPhot[iPhoton];
  tmva_photonid_etawidth     = pid_scetawid[iPhoton];
  tmva_photonid_phiwidth     = pid_scphiwid[iPhoton];
  tmva_photonid_r9           = E9Phot[iPhoton]/escRawPhot[iPhoton];
  tmva_photonid_lambdaratio  = pid_lambdaRatio[iPhoton];
  
  tmva_photonid_s4ratio  = E4Phot[iPhoton]/E25Phot[iPhoton];
  tmva_photonid_eventrho = rhoAllJets;
  tmva_photonid_sceta    = etascPhot[iPhoton];
  
  float rr2=pid_esXwidth[iPhoton]*pid_esXwidth[iPhoton]+pid_esYwidth[iPhoton]*pid_esYwidth[iPhoton];
  tmva_photonid_ESEffSigmaRR = 0.0; 
  if(rr2>0. && rr2<999999.) 
    tmva_photonid_ESEffSigmaRR = sqrt(rr2);


  */
  //2012 rescalings for MC
  if (nMC>0)
    {
      if (isEBPhot[*iPhoton]) {
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


