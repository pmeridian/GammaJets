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


TagAndProbeTree::TagAndProbeTree(TTree *tree, const TString& outname) : tree_reader_V9(tree), jsonFile(0) //, scaleCorrections_(0)
{  
  std::cout << "Creating output file " << outname << std::endl;
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

  bookOutputTree();

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
  
  

  //cout << "Set MVA variables" << endl;
  /*******************************************************
   *                   SET MVA VAR                       *   
   *******************************************************/
  
  // photonID MVA
  tmvaReaderID_Single_Endcap=0;
  tmvaReaderID_Single_Barrel=0;
  if (!tmvaReaderID_Single_Barrel || !tmvaReaderID_Single_Endcap) SetAllMVA();
  
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
  
  /********************************************************
   *                                                      *
   *                       LOOP                           *
   *                                                      *
   ********************************************************/

  cout << "starting the loop" << endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
  
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
    

    if (myjson && nMC<=0) 
      if (!myjson->isGoodLS(run,lbn)) continue;
    

    int nGenElectrons(0);
    int isElectronFromZ[nMC];
    int isElectronFromZIndex[nMC];
    int neletag(0), neleprobe(0);
    
    TLorentzVector gen;
  
    float r9_phot[nPhot];      
    float s4Ratio_phot[nPhot];
    float sigmaRR[nPhot];     
   

    nEleMC=0;

    /**********************************
     *       PU WEIGHT                *
     **********************************/

    // pu weights
    int npu = pu_n;

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

    /**********************************
     *       R9 WEIGHT                *
     **********************************/
    double r9Phot_;
    double weightr9;
    
    //nbin of r9weights histogram is 2100
    const int nbins_r9weight = 2100;
    const double binwidth_r9weight = 5.00000000000000010e-04;



    for(int iPhot=0; iPhot<nPhot; iPhot++){
      
      r9Phot_  = E9Phot[iPhot] / escRawPhot[iPhot];
      for(int i=0; i< nbins_r9weight; i++){
	weightr9 = 1.;
	
	if(r9Phot_>(i*binwidth_r9weight) && r9Phot_<((i+1)*binwidth_r9weight) && isEBPhot[i])  {
	  weightr9 = vec_r9_weight_EB[i];
	  r9_weight_[iPhot] = weightr9;
	  //cout << "r9 weight EB : " << weightr9 << endl;	
	  continue;
	}
	else if(r9Phot_>(i*binwidth_r9weight) && r9Phot_<((i+1)*binwidth_r9weight) && isEEPhot[i]) {
	  weightr9 = vec_r9_weight_EE[i];
	  r9_weight_[iPhot] = weightr9;
	  //cout << "r9 weight EE : " << weightr9 << endl;
	  continue;
	}
      }
      
    }     


    //cout << "set weight" << endl;
    float weight=pu_weight;
    //cout << "weight : " << weight << endl;

    // to be used after for equiv lumi calculation
    if(isMC) 
      elegen1.Fill(1.,weight);
    //cout << " elegen1 filled with 1 " << endl; 

    //Skip events with o electrons
    if(nEle == 0) continue;

    // skip events where the number of jets, photons, and vertexes is above the maximum allowed value
    if (nPhot>40) { //Should never happen
      cout << "number of photons = " << nPhot << " and above threshold of 30; skipping" << endl;
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
    //    aHLTNames -> clear();
    for (int ii=0; ii<(HLTResults->size()); ii++) {
      if ((*HLTResults)[ii]) {
        aHLTNames->push_back((*HLTNames)[ii]);
      }
    }
    
    
    
    
    //----------------------------------------------
    //            cluster shape corrections
    //----------------------------------------------
    //cout << "cluster shape corrections" << endl;
    
    for (int i=0; i<nPhot; i++)
      {
	float rr2 = 0;
	rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
	//tmva_photonid_ESEffSigmaRR = 0.0; 
	
	r9Phot[i]      = E9Phot[i] / escRawPhot[i];
	s4RatioPhot[i] = E4Phot[i] / E25Phot[i];
	sigmaRRPhot[i]      = TMath::Sqrt(rr2);	
	
	//Applying ClusterShapes corrections for photonID shower shapes in MC
	ClusterShape(&i, &pid_etawid[i], &pid_scetawid[i], &pid_scphiwid[i], &r9Phot[i], &s4RatioPhot[i]);

	//Taking for Photon Probes the vtx0 isolation 
	pid_hlwTrack03ForCiCVtx0[i]    =pid_hlwTrack03ForCiC[i][0];
	pid_hlwTrackForCiCVtx0[i]      =pid_hlwTrackForCiC[i][0];
	pid_pfIsoCharged01ForCiCVtx0[i]=pid_pfIsoCharged01ForCiC[i][0];
	pid_pfIsoCharged02ForCiCVtx0[i]=pid_pfIsoCharged02ForCiC[i][0];
	pid_pfIsoCharged03ForCiCVtx0[i]=pid_pfIsoCharged03ForCiC[i][0];
	pid_pfIsoCharged04ForCiCVtx0[i]=pid_pfIsoCharged04ForCiC[i][0];
	pid_pfIsoCharged05ForCiCVtx0[i]=pid_pfIsoCharged05ForCiC[i][0];
	pid_pfIsoCharged06ForCiCVtx0[i]=pid_pfIsoCharged03ForCiC[i][0];
      }
	
    //cout << "done cluster shape corrections" << endl;

    //int countPreselPhot = 0;  
    TLorentzVector  ele, phot;
    TLorentzVector vector_ele[nEle], vector_phot[nPhot]; 
    
    vector<bool> idpasseletag2012(13);
    vector<bool> idpass_photonID_2012(5);

    for(int iPhot=0; iPhot<nPhot; iPhot++ ){
      phot.SetPtEtaPhiE(ptPhot[iPhot], etaPhot[iPhot], phiPhot[iPhot], ePhot[iPhot]);
      vector_phot[iPhot] = phot;
      isGenMatchPhot[iPhot]=0;
      genMatchIndexPhot[iPhot]=-1;
    }
    
    for(int iEle=0; iEle<nEle; iEle++ ){
      ele.SetPtEtaPhiE(electron_pt[iEle], electron_eta[iEle], electron_phi[iEle], electron_energy[iEle]);
      vector_ele[iEle] = ele;
      isGenMatchEle[iEle]=0;
      genMatchIndexEle[iEle]=-1;
    }
    
    
    /***************************************************
     *                                                 *
     *                 REAL LOOP (after ini)           *
     *                                                 *
     ***************************************************/

    if(isMC) {
      //cout << "generator level matching" <<endl;
      /*---------------------------------------------------------------
	
                         Generator level matching
      
      ---------------------------------------------------------------*/
      /// init of mc related variables
      //if(nEle>0) cout << "Loop over nMC" << endl;
      for(int i=0; i<nMC; i++) {
	//	cout << "initializing gen ele" << endl;
	isElectronFromZ[i]=0;
	isElectronFromZIndex[i]=-1;
	gen.SetPtEtaPhiE(-999., -999., -999, -999.);

	if( TMath::Abs(pdgIdMC[i])==11  && TMath::Abs(pdgIdMC[motherIDMC[i]])==23
	    //	    && (statusMC[i]==1 || statusMC[i]==3) 
	    && (statusMC[i]==3) 
	    //&& ptMC[i] > 20 
	    //&& (TMath::Abs(etaMC[i])<1.4442 || (TMath::Abs(etaMC[i])>1.566 && TMath::Abs(etaMC[i])<2.5)) 
	    //da cambiare
	  ){
	  //	  cout << "event : " << event  << "   nMC : " << nMC << "    i : " << i << "    pdgIdMC : " << pdgIdMC[i] << "      pdgIdMC[motherIDMC] : " << pdgIdMC[motherIDMC[i]] << endl;
	  //cout << "gen electron found!" << endl;
	  if(nEleMC >= 2) cout << "More than 2 electrons from Z!!" << endl;
	  
	  isElectronFromZ[i]= 1;
	  isElectronFromZIndex[i]= nEleMC;
	  idEleMC[nEleMC]=i;
	  pdgIdEleMC[nEleMC]=pdgIdMC[i];   
	  statusEleMC[nEleMC]=statusMC[i];   
	  motherIDEleMC[nEleMC]=motherIDMC[i];   
	  ptEleMC [nEleMC]=ptMC [i];   
	  eEleMC  [nEleMC]=eMC  [i];   
	  etaEleMC[nEleMC]=etaMC[i];   
	  phiEleMC[nEleMC]=phiMC[i];   
	  nEleMC++;
	}
	

      }
      
      for(int i =0; i<nMC; i++)
	{
	  if(isElectronFromZ[i]) {
	    gen.SetPtEtaPhiE(ptMC[i],etaMC[i],phiMC[i],eMC[i]);

	    //Electrons Matching
	    float deltaRmin = 0.2;
	    int recoMatched_index = -999.;
	    int genMatched_index = -999.; 
	    for(int j=0; j<nEle; j++) {
	      float deltaR = gen.DeltaR(vector_ele[j]);
	      if(deltaR<deltaRmin) {
		deltaRmin = deltaR;
		recoMatched_index = j;
		genMatched_index = i;
	      }
	    }
	    if(recoMatched_index >= 0){
	      isGenMatchEle[recoMatched_index] = 1;
	      genMatchIndexEle[recoMatched_index] = isElectronFromZIndex[genMatched_index]; 
	    }


	    //Photons Matching
	    deltaRmin = 0.2;
	    recoMatched_index = -999.;
	    genMatched_index = -999.; 
	    for(int j=0; j<nPhot; j++) {
	      float deltaR = gen.DeltaR(vector_phot[j]);
	      if(deltaR<deltaRmin ) {
		deltaRmin = deltaR;
		recoMatched_index = j;
		genMatched_index = i;
	      }
	    }
	    if(recoMatched_index >= 0){
	      isGenMatchPhot[recoMatched_index] = 1;
	      genMatchIndexPhot[recoMatched_index] = isElectronFromZIndex[genMatched_index]; 
	    }
	  }

	}// end loop on MC electrons
    } //isMC
    
    /*---------------------------------------------------------------
      
    Tag&Probe tags for electrons and photons
    
    ---------------------------------------------------------------*/
    //cout << "saving variables in tree" << endl;

    bool atLeastOneTag=false;
    
    for(int j=0; j<nEle; j++) 
      {
	isTagTightEle[j]=leptonCutsEle2012(j, eletag_tight2012, &idpasseletag2012);
	isTagMediumEle[j]=leptonCutsEle2012(j, eletag_medium2012, &idpasseletag2012);
	isTagLooseEle[j]=leptonCutsEle2012(j, eletag_loose2012, &idpasseletag2012);
	if (isTagLooseEle[j] || isTagMediumEle[j] || isTagTightEle[j]) atLeastOneTag=true;
	
	// match with HLt candidates 
	TVector3 recoEle;
	recoEle.SetPtEtaPhi(electron_pt[j],electron_eta[j],electron_phi[j]);

	float deltaRmin17 = 0.3;
	int i_nEle17=-1;
	for(int jhlt=0; jhlt<trg17_mass50_ele_n; jhlt++) {
	  TVector3 trig;
	  if (trg17_mass50_ele_et[jhlt]<=0 || fabs(trg17_mass50_ele_eta[jhlt])>2.5 || fabs(trg17_mass50_ele_phi[jhlt])>TMath::Pi() ) continue;
	  trig.SetPtEtaPhi(trg17_mass50_ele_et[jhlt], trg17_mass50_ele_eta[jhlt], trg17_mass50_ele_phi[jhlt]);
	  if(recoEle.DeltaR(trig) < deltaRmin17) {
	    deltaRmin17 = recoEle.DeltaR(trig);
	    i_nEle17 = jhlt;
	  }
	}
	
	float deltaRmin20 = 0.3;
	int i_nEle20=-1;
	for(int jhlt=0; jhlt<trg20_mass50_ele_n; jhlt++) {
	  TVector3 trig;
	  if (trg20_mass50_ele_et[jhlt]<=0 || fabs(trg20_mass50_ele_eta[jhlt])>2.5 || fabs(trg20_mass50_ele_phi[jhlt])>TMath::Pi() ) continue;
	  trig.SetPtEtaPhi(trg20_mass50_ele_et[jhlt], trg20_mass50_ele_eta[jhlt], trg20_mass50_ele_phi[jhlt]);
	  if(recoEle.DeltaR(trig) < deltaRmin20) {
	    deltaRmin20 = recoEle.DeltaR(trig);
	    i_nEle20 = jhlt;
	  }
	}
	
	if (i_nEle17>-1)
	  isTrig17Mass50MatchedEle[j]=1;
	else
	  isTrig17Mass50MatchedEle[j]=0;
	
	if (i_nEle20>-1)
	  isTrig20Mass50MatchedEle[j]=1;
	else
	  isTrig20Mass50MatchedEle[j]=0;
      }

    for(int j=0; j<nPhot; j++) 
      {
	isProbePreselPhot[j]= (PhotonMITPreSelection(j,0,0) 
			  && ptPhot[j]>20.  
			  && (TMath::Abs(etascPhot[j])<1.4442 || (TMath::Abs(etascPhot[j])>1.566 && TMath::Abs(etascPhot[j])<2.5))
			  );
	
	isProbeTightPhot[j]= photonIDCuts2012(j, eleprobe_tight2012, &idpass_photonID_2012);
	isProbeMediumPhot[j]= photonIDCuts2012(j, eleprobe_medium2012, &idpass_photonID_2012);
	isProbeLoosePhot[j]= photonIDCuts2012(j, eleprobe_loose2012, &idpass_photonID_2012);
	mvaIDPhot[j] = PhotonIDMVA(j);   
	r9_weight[j] = r9_weight_[j];
      }

    vtxId=0;
    float rhoVtx=sqrt(vx[0]*vx[0]+vy[0]*vy[0]);
    if (vndof[0]<4 || fabs(vz[0])>24. || rhoVtx>2.) vtxId=-555;    

    if(atLeastOneTag || nEleMC>0)  ana_tree->Fill();
    
    delete aHLTNames;
    }

  elegen1.Write();
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


void TagAndProbeTree::SetR9Weights(std::string r9WeightFile)
{
  if(r9WeightFile == "") {                                      
    std::cout << "you need a weights file to use this function" << std::endl;
    return;                                                   
  }
  std::cout << "R9 REWEIGHTING:: Using file " << r9WeightFile << std::endl;
  
  TFile *f_r9  = new TFile(r9WeightFile.c_str(),"READ");
  f_r9->cd();
  
  TH1F *r9weights_EB = 0;
  TH1F *r9weights_EE = 0;

  r9weights_EB= (TH1F*) f_r9->Get("R9WeightEBAll");
  r9weights_EE= (TH1F*) f_r9->Get("R9WeightEEAll");
  
  float weightr9;

  if (!r9weights_EB || !r9weights_EE) {
    std::cout << "weights histograms  not found in file " << r9WeightFile << std::endl;
    return;
  }
  

  for(int i=0; i<2100; i++){
    vec_r9_weight_EB[i] = 1.;
    vec_r9_weight_EE[i] = 1.;

    vec_r9_weight_EB[i] = r9weights_EB->GetBinContent(i+1);
    vec_r9_weight_EE[i] = r9weights_EE->GetBinContent(i+1);

    cout << "vec_r9_weight_EB[" << i << "] = " << vec_r9_weight_EB[i] << endl;

  }

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



bool TagAndProbeTree::photonIDCuts2012(int i, photonidcuts2012 const& pid, vector<bool> *vpass) {
//bool TagAndProbeTree::photonIDCuts2012(int i, photonidcuts2012 const& pid, ) {

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
    if (vpass)
      {
	(*vpass)[0]  = pt;	
	(*vpass)[1]  = eta;	
	(*vpass)[2]  = crack;	
	(*vpass)[3]  = setaeta;	
	(*vpass)[4]  = hoe;  
      }
    

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

//   float rr2 = 0;
//   rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
//   //tmva_photonid_ESEffSigmaRR = 0.0; 
//   float rr = TMath::Sqrt(rr2); 

//   float r9phot = E9Phot[i] / escRawPhot[i];
//   float s4phot = E4Phot[i] / E25Phot[i];
  

  tmva_photonid_etawidth     = pid_scetawid[i];
  tmva_photonid_phiwidth     = pid_scphiwid[i];
  tmva_photonid_sieie        = pid_etawid[i];
  tmva_photonid_sieip        = sEtaPhiPhot[i];
  tmva_photonid_s4ratio      = s4RatioPhot[i];
  tmva_photonid_r9           = r9Phot[i];
  tmva_photonid_pt           = ptPhot[i];
  tmva_photonid_sceta        = etascPhot[i];
  tmva_photonid_rr           = 0.0; 
  tmva_photonid_eventrho     = rhoAllJets;
  
  tmva_photonid_rr = sigmaRRPhot[i];


  bool isEBphot = true;
  if (fabs(etascPhot[i])>1.479) isEBphot = false; 

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
  
  std::cout << "Booking PhotonID EB MVA with file " << photonLevelNewIDMVA_EB << endl;
  tmvaReaderID_Single_Barrel->BookMVA("BDT",photonLevelNewIDMVA_EB);
  std::cout << "Booking PhotonID EE MVA with file " << photonLevelNewIDMVA_EE  << endl;
  tmvaReaderID_Single_Endcap->BookMVA("BDT",photonLevelNewIDMVA_EE);
  
}

void TagAndProbeTree::bookOutputTree()
{
  ana_tree = new TTree ("AnaTree","Reduced tree for final analysis");

  cout << "Booking branches" << endl;
    
  ana_tree->Branch("run",&run,"run/I");
  ana_tree->Branch("event",&event,"event/I");
  ana_tree->Branch("lumi",&lbn,"lumi/I");
  ana_tree->Branch("isMC",&isMC,"isMC/I");
  ana_tree->Branch("nvtx",&nvertex,"nvtx/I");
  // vertex
  ana_tree->Branch("vtxId",   &vtxId,   "vtxId/I");

  ana_tree->Branch("npu",&pu_n,"npu/I");
  ana_tree->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree->Branch("xsection",&xsection,"xsection/F");
  ana_tree->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree->Branch("SampleID",&SampleID,"SampleID/I");

  ana_tree->Branch("pu_weight",&pu_weight,"pu_weight/F");
  ana_tree->Branch("pu_weight30",&pu_weight30,"pu_weight30/F");
  ana_tree->Branch("pu_weight50",&pu_weight50,"pu_weight50/F");
  ana_tree->Branch("pu_weight75",&pu_weight75,"pu_weight75/F");
  ana_tree->Branch("pu_weight90",&pu_weight90,"pu_weight90/F");

  ana_tree->Branch("nPhot", &nPhot, "nPhot/I");
  ana_tree->Branch("r9_weight",r9_weight,"r9_weight[nPhot]/F");

  ana_tree->Branch("rhoAllJets",&rhoAllJets,"rhoAllJets/F");
  ana_tree->Branch("rhoPF",&rhoPF,"rhoPF/F");		   

  ana_tree->Branch("nEleMC",&nEleMC,"nEleMC/I");
  ana_tree->Branch("idEleMC",idEleMC,"idEleMC[nEleMC]/I");
  ana_tree->Branch("pdgIdEleMC",pdgIdEleMC,"pdgIdEleMC[nEleMC]/I");
  ana_tree->Branch("statusEleMC",statusEleMC,"statusEleMC[nEleMC]/I");
  ana_tree->Branch("motherIDEleMC",motherIDEleMC,"motherIDEleMC[nEleMC]/I");
  ana_tree->Branch("ptEleMC",ptEleMC,"ptEleMC[nEleMC]/F");
  ana_tree->Branch("eEleMC",eEleMC,"eEleMC[nEleMC]/F");
  ana_tree->Branch("etaEleMC",etaEleMC,"etaEleMC[nEleMC]/F");
  ana_tree->Branch("phiEleMC",phiEleMC,"phiEleMC[nEleMC]/F");

  ana_tree->Branch("ptPhot", ptPhot , "ptPhot[nPhot]/F" );
  ana_tree->Branch("isGenMatchPhot", isGenMatchPhot , "isGenMatchPhot[nPhot]/I" );
  ana_tree->Branch("genMatchIndexPhot", genMatchIndexPhot , "genMatchIndexPhot[nPhot]/I" );
  ana_tree->Branch("isProbePreselPhot", isProbePreselPhot , "isProbePreselPhot[nPhot]/I" );
  ana_tree->Branch("isProbeTightPhot", isProbeTightPhot , "isProbeTightPhot[nPhot]/I" );
  ana_tree->Branch("isProbeMediumPhot", isProbeMediumPhot , "isProbeMediumPhot[nPhot]/I" );
  ana_tree->Branch("isProbeLoosePhot", isProbeLoosePhot , "isProbeLoosePhot[nPhot]/I" );
  ana_tree->Branch("mvaIDPhot", mvaIDPhot , "mvaIDPhot[nPhot]/F" );
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
  ana_tree->Branch("timePhot", timePhot, "timePhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("e4SwissCrossPhot",e4SwissCrossPhot, "e4SwissCrossPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("hasPixelSeedPhot", hasPixelSeedPhot, "hasPixelSeedPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("hasMatchedPromptElePhot", hasMatchedPromptElePhot, "hasMatchedPromptElePhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("hasMatchedConvPhot", hasMatchedConvPhot, "hasMatchedConvPhot[nPhot]/I");   //[nPhot]
  ana_tree->Branch("isEBPhot", isEBPhot, "isEBPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("isEEPhot", isEEPhot, "isEEPhot[nPhot]/O");   //[nPhot]
  ana_tree->Branch("isEBEEGapPhot", isEBEEGapPhot, "isEBEEGapPhot[nPhot]/O");   //[nPhot]
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
  ana_tree->Branch("r9Phot", r9Phot, "r9Phot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("s4RatioPhot", s4RatioPhot, "s4RatioPhot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("sigmaRRPhot", sigmaRRPhot, "sigmaRRPhot[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("pid_deltaRToTrackPhot", pid_deltaRToTrackPhot, "pid_deltaRToTrackPhot[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_isEMPhot", pid_isEM, "pid_isEM[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_isLoosePhot", pid_isLoose, "pid_isLoose[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_isTightPhot", pid_isTight, "pid_isTight[nPhot]/O");   //[nPhot]
  ana_tree->Branch("pid_jurECALPhot", pid_jurECAL, "pid_jurECAL[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_twrHCALPhot", pid_twrHCAL, "pid_twrHCAL[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_HoverE", pid_HoverE, "pid_HoverE[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrackPhot", pid_hlwTrack, "pid_hlwTrack[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrackNoDz", pid_hlwTrackNoDz, "pid_hlwTrackNoDz[nPhot]/F") ;   //[nPhot]
  ana_tree->Branch("pid_etawid", pid_etawid, "pid_etawid[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_jurECAL03", pid_jurECAL03, "pid_jurECAL03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_twrHCAL03", pid_twrHCAL03, "pid_twrHCAL03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03", pid_hlwTrack03, "pid_hlwTrack03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack0oDz", pid_hlwTrackNoDz, "pid_hlwTrackNoDz[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03NoDz", pid_hlwTrack03NoDz, "pid_hlwTrack03NoDz[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_hlwTrack03ForCiC", pid_hlwTrack03ForCiCVtx0, "pid_hlwTrack03ForCiC[nPhot]/F");
  ana_tree->Branch("pid_hlwTrackForCiC", pid_hlwTrackForCiCVtx0, "pid_hlwTrackForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged01ForCiC", pid_pfIsoCharged01ForCiCVtx0, "pid_pfIsoCharged01ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged02ForCiC", pid_pfIsoCharged02ForCiCVtx0, "pid_pfIsoCharged02ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged03ForCiC", pid_pfIsoCharged03ForCiCVtx0, "pid_pfIsoCharged03ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged04ForCiC", pid_pfIsoCharged04ForCiCVtx0, "pid_pfIsoCharged04ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged05ForCiC", pid_pfIsoCharged05ForCiCVtx0, "pid_pfIsoCharged05ForCiC[nPhot]/F");
  ana_tree->Branch("pid_pfIsoCharged06ForCiC", pid_pfIsoCharged06ForCiCVtx0, "pid_pfIsoCharged06ForCiC[nPhot]/F");
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
  ana_tree->Branch("pid_pfIsoFPRCharged03", pid_pfIsoFPRCharged03, "pid_pfIsoFPRCharged03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRNeutral03", pid_pfIsoFPRNeutral03, "pid_pfIsoFPRNeutral03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRPhoton03",  pid_pfIsoFPRPhoton03,  "pid_pfIsoFPRPhoton03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConeCharged03", pid_pfIsoFPRRandomConeCharged03, "pid_pfIsoFPRRandomConeCharged03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConeNeutral03", pid_pfIsoFPRRandomConeNeutral03, "pid_pfIsoFPRRandomConeNeutral03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConePhoton03",  pid_pfIsoFPRRandomConePhoton03,  "pid_pfIsoFPRRandomConePhoton03[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRCharged04", pid_pfIsoFPRCharged04, "pid_pfIsoFPRCharged04[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRNeutral04", pid_pfIsoFPRNeutral04, "pid_pfIsoFPRNeutral04[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRPhoton04",  pid_pfIsoFPRPhoton04,  "pid_pfIsoFPRPhoton04[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConeCharged04", pid_pfIsoFPRRandomConeCharged04, "pid_pfIsoFPRRandomConeCharged04[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConeNeutral04", pid_pfIsoFPRRandomConeNeutral04, "pid_pfIsoFPRRandomConeNeutral04[nPhot]/F");   //[nPhot]
  ana_tree->Branch("pid_pfIsoFPRRandomConePhoton04",  pid_pfIsoFPRRandomConePhoton04,  "pid_pfIsoFPRRandomConePhoton04[nPhot]/F");   //[nPhot]  
  ana_tree->Branch("nEle", &nEle, "nEle/I");
  ana_tree->Branch("isGenMatchEle", isGenMatchEle , "isGenMatchEle[nEle]/I" );
  ana_tree->Branch("genMatchIndexEle", genMatchIndexEle , "genMatchIndexEle[nEle]/I" );
  ana_tree->Branch("electron_pt", electron_pt, "electron_pt[nEle]/F");
  ana_tree->Branch("electron_eta", electron_eta, "electron_eta[nEle]/F");
  ana_tree->Branch("electron_phi", electron_phi, "electron_phi[nEle]/F");
  ana_tree->Branch("isTagTightEle", isTagTightEle , "isTagTightEle[nEle]/I" );
  ana_tree->Branch("isTagMediumEle", isTagMediumEle , "isTagMediumEle[nEle]/I" );
  ana_tree->Branch("isTagLooseEle", isTagLooseEle , "isTagLooseEle[nEle]/I" );
  ana_tree->Branch("isTrig17Mass50MatchedEle", isTrig17Mass50MatchedEle, "isTrig17Mass50MatchedEle[nEle]/I");
  ana_tree->Branch("isTrig20Mass50MatchedEle", isTrig20Mass50MatchedEle, "isTrig20Mass50MatchedEle[nEle]/I");


  // triggering paths      
  ana_tree->Branch("firedHLTNames",  &aHLTNames);

  //pfMET
  ana_tree->Branch("epfMet", &epfMet, "epfMet/F");
}
