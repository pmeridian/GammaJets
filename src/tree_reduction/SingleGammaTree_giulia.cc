#include "SingleGammaTree_giulia.h"
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


SingleGammaTree_giulia::SingleGammaTree_giulia(TTree *tree, const TString& outname) : tree_reader_V8(tree), jsonFile(0) //, scaleCorrections_(0)
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

SingleGammaTree_giulia::~SingleGammaTree_giulia() {
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
}

vector<int> SingleGammaTree_giulia::firstones(Float_t *vec, vector<bool> *asso, int number){
  
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




void SingleGammaTree_giulia::Loop() {


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
  float ptPhot_presel[10];
  float ePhot_presel[10];
  float phiPhot_presel[10];
  float etaPhot_presel[10];

  float deltaRGenReco[10];
  float deltaRGenReco_EB_nopresel[10], deltaRGenReco_EE_nopresel[10];
  float eTrue_EB_nopresel[10], eTrue_EE_nopresel[10];
  float eReco_EB_matched[10], eReco_EE_matched[10];

  int isMatchedPhot[10];

  float pid_scetawid_presel[10];
  float pid_scphiwid_presel[10]; 
  float sEtaEtaPhot_presel[10];
  float sEtaPhiPhot_presel[10];
  float s4RatioPhot_presel[10];
  float r9Phot_presel[10];
  float etascPhot_presel[10];


  float rr_presel[10];

  //photon id
  float pid_lambdaRatio_presel[10];
  float pid_HoverE_presel[10];

  float pid_jurECAL03_presel[10];
  float pid_twrHCAL03_presel[10];
  float pid_hlwTrack03_presel[10];

  float pid_jurECAL04_presel[10];
  float pid_twrHCAL04_presel[10];
  float pid_hlwTrack04_presel[10];

  float pid_pfIsoCharged01ForCiC_presel[10];
  float pid_pfIsoCharged02ForCiC_presel[10];
  float pid_pfIsoCharged03ForCiC_presel[10];
  float pid_pfIsoCharged04ForCiC_presel[10];
  float pid_pfIsoCharged05ForCiC_presel[10];
  float pid_pfIsoCharged06ForCiC_presel[10];

  float pid_pfIsoPhotons01ForCiC_presel[10];
  float pid_pfIsoPhotons02ForCiC_presel[10];
  float pid_pfIsoPhotons03ForCiC_presel[10];
  float pid_pfIsoPhotons04ForCiC_presel[10];
  float pid_pfIsoPhotons05ForCiC_presel[10];
  float pid_pfIsoPhotons06ForCiC_presel[10];
  
  float pid_pfIsoNeutrals01ForCiC_presel[10];
  float pid_pfIsoNeutrals02ForCiC_presel[10];
  float pid_pfIsoNeutrals03ForCiC_presel[10];
  float pid_pfIsoNeutrals04ForCiC_presel[10];
  float pid_pfIsoNeutrals05ForCiC_presel[10];
  float pid_pfIsoNeutrals06ForCiC_presel[10];
  

  
  ana_tree = new TTree ("AnaTree","Reduced tree for final analysis");
  //ana_tree = new TTree ("AnaTree","Reduced tree for final analysis, 2") ;
  // general
  
  ana_tree->Branch("run",&runRN,"run/I");
  ana_tree->Branch("event",&eventRN,"event/I");
  ana_tree->Branch("lumi",&lumi,"lumi/I");
  ana_tree->Branch("nvtx",&nvtx,"nvtx/F");

  ana_tree->Branch("npu",&npu,"npu/I");
  ana_tree->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree->Branch("xsection",&xsection,"xsection/F");
  ana_tree->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree->Branch("SampleID",&SampleID,"SampleID/I");
  ana_tree->Branch("pu_weight",&pu_weight,"pu_weight/F");
  
  // photons
  ana_tree->Branch("nPhot_gen",&nPhot_gen,"nPhot_gen/I");
  ana_tree->Branch("nPhot_presel",&nPhot_presel,"nPhot_presel/I");
  ana_tree->Branch("ptPhot_presel",ptPhot_presel,"ptPhot_presel[nPhot_presel]/F");
  ana_tree->Branch("ePhot_presel",ePhot_presel,"ePhot_presel[nPhot_presel]/F");
  ana_tree->Branch("etascPhot_presel  ",etascPhot_presel  ,"etascPhot_presel[nPhot_presel]/F");


  ana_tree->Branch("etaPhot_presel",etaPhot_presel,"etaPhot[nPhot_presel]/F");
  ana_tree->Branch("phiPhot_presel",phiPhot_presel,"phiPhot[nPhot_presel]/F");

  ana_tree->Branch("pid_jurECAL03_presel",pid_jurECAL03_presel,"pid_jurECAL03_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_twrHCAL03_presel",pid_twrHCAL03_presel,"pid_twrHCAL03_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_hlwTrack03_presel",pid_hlwTrack03_presel,"pid_hlwTrack03_presel[nPhot_presel]/F");						
		   																			
  ana_tree->Branch("pid_jurECAL04_presel",pid_jurECAL04_presel,"pid_jurECAL04_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_twrHCAL04_presel",pid_twrHCAL04_presel,"pid_twrHCAL04_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_hlwTrack04_presel",pid_hlwTrack04_presel,"pid_hlwTrack04_presel[nPhot_presel]/F");						
		   																			
  ana_tree->Branch("pid_pfIsoCharged01ForCiC_presel",pid_pfIsoCharged01ForCiC_presel,"pid_pfIsoCharged01ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoCharged02ForCiC_presel",pid_pfIsoCharged02ForCiC_presel,"pid_pfIsoCharged02ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoCharged03ForCiC_presel",pid_pfIsoCharged03ForCiC_presel,"pid_pfIsoCharged03ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoCharged04ForCiC_presel",pid_pfIsoCharged04ForCiC_presel,"pid_pfIsoCharged04ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoCharged05ForCiC_presel",pid_pfIsoCharged05ForCiC_presel,"pid_pfIsoCharged05ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoCharged06ForCiC_presel",pid_pfIsoCharged06ForCiC_presel,"pid_pfIsoCharged06ForCiC_presel[nPhot_presel]/F");		
		    				    		    											
  ana_tree->Branch("pid_pfIsoPhotons01ForCiC_presel",pid_pfIsoPhotons01ForCiC_presel,"pid_pfIsoPhotons01ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoPhotons02ForCiC_presel",pid_pfIsoPhotons02ForCiC_presel,"pid_pfIsoPhotons02ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoPhotons03ForCiC_presel",pid_pfIsoPhotons03ForCiC_presel,"pid_pfIsoPhotons03ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoPhotons04ForCiC_presel",pid_pfIsoPhotons04ForCiC_presel,"pid_pfIsoPhotons04ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoPhotons05ForCiC_presel",pid_pfIsoPhotons05ForCiC_presel,"pid_pfIsoPhotons05ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoPhotons06ForCiC_presel",pid_pfIsoPhotons06ForCiC_presel,"pid_pfIsoPhotons06ForCiC_presel[nPhot_presel]/F");		
		    				    		    											
  ana_tree->Branch("pid_pfIsoNeutrals01ForCiC_presel",pid_pfIsoNeutrals01ForCiC_presel,"pid_pfIsoNeutrals01ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoNeutrals02ForCiC_presel",pid_pfIsoNeutrals02ForCiC_presel,"pid_pfIsoNeutrals02ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoNeutrals03ForCiC_presel",pid_pfIsoNeutrals03ForCiC_presel,"pid_pfIsoNeutrals03ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoNeutrals04ForCiC_presel",pid_pfIsoNeutrals04ForCiC_presel,"pid_pfIsoNeutrals04ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoNeutrals05ForCiC_presel",pid_pfIsoNeutrals05ForCiC_presel,"pid_pfIsoNeutrals05ForCiC_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoNeutrals06ForCiC_presel",pid_pfIsoNeutrals06ForCiC_presel,"pid_pfIsoNeutrals06ForCiC_presel[nPhot_presel]/F");		
		   																			
  ana_tree->Branch("pid_scetawid_presel",pid_scetawid_presel,"pid_scetawid_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_scphiwid_presel",pid_scphiwid_presel,"pid_scphiwid_presel[nPhot_presel]/F");							
  ana_tree->Branch("pid_lambdaRatio_presel",pid_lambdaRatio_presel,"pid_lambdaRatio_presel[nPhot_presel]/F");						
  ana_tree->Branch("pid_HoverE_presel",pid_HoverE_presel,"pid_HoverE_presel[nPhot_presel]/F");								
  																			
		   																			
  ana_tree->Branch("sEtaEtaPhot_presel",sEtaEtaPhot_presel,"sEtaEtaPhot_presel[nPhot_presel]/F");							
  ana_tree->Branch("sEtaPhiPhot_presel",sEtaPhiPhot_presel,"sEtaPhiPhot_presel[nPhot_presel]/F");							
  ana_tree->Branch("s4RatioPhot_presel",s4RatioPhot_presel,"s4RatrioPhot_presel[nPhot_presel]/F"); //new						
  ana_tree->Branch("r9Phot_presel",r9Phot_presel,"r9Phot_presel[nPhot_presel]/F"); //new								
  ana_tree->Branch("rhoAllJets",&rhoAllJets,"rhoAllJets/F");												
  ana_tree->Branch("rhoPF",&rhoPF,"rhoPF/F");														
		   																			
  ana_tree->Branch("rr_presel",rr_presel,"rr_presel[nPhot_presel]/F"); //new                                                                            


  ana_tree->Branch("isMatchedPhot", isMatchedPhot, "isMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("deltaRGenReco", deltaRGenReco, "deltaRGenReco[nPhot_gen]/F"  );

  ana_tree->Branch("deltaRGenReco_EB_nopresel", deltaRGenReco_EB_nopresel, "deltaRGenReco_EB_nopresel[nPhot_gen]/F"  );
  ana_tree->Branch("deltaRGenReco_EE_nopresel", deltaRGenReco_EE_nopresel, "deltaRGenReco_EE_nopresel[nPhot_gen]/F"  );
  ana_tree->Branch("eTrue_EB_nopresel", eTrue_EB_nopresel, "eTrue_EB_nopresel[nPhot_gen]/F"  );
  ana_tree->Branch("eTrue_EE_nopresel", eTrue_EE_nopresel, "eTrue_EE_nopresel[nPhot_gen]/F"  );
  ana_tree->Branch("eReco_EB_matched", eReco_EB_matched, "eReco_EB_matched[nPhot_gen]/F"  );
  ana_tree->Branch("eReco_EE_matched", eReco_EE_matched, "eReco_EE_matched[nPhot_gen]/F"  );


  // triggering paths                                                                                                                 
  ana_tree->Branch("firedHLTNames",  &aHLTNames);

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
    vector<TVector3> genPhot, recoPhot, recoPhot_nopresel;
    TVector3 gen, reco, reco_nopresel;
       
    /// init of mc related variables
        
    for(int i=0; i<nMC; i++) {
      
      if((pdgIdMC[i] == 22 && statusMC[i] == 3)
	 || (pdgIdMC[i] == 22 && statusMC[i] == 1 && (TMath::Abs(pdgIdMC[motherIDMC[i]])<=10 ) )
	 ){

	photassocMC.push_back(1);	
	
	nGenPhot++;
	gen.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	genPhot.push_back(gen);
      }
      else	photassocMC.push_back(0);
         
      /// if there are photons coming not from a photon or a higgs
      //if(pdgIdMC[i] == 22 && statusMC[i] == 1 && TMath::Abs(pdgIdMC[motherIDMC[i]])<21) nGenPhot++;

    }
    nPhot_gen = nGenPhot;
    //    if (nGenPhot != 1) cout << "nGenPhot:  " << nGenPhot << endl; 



    //matching efficiency (before preselection)
    vector<float> deltaR_gen_reco_nopresel_EB, deltaR_gen_reco_nopresel_EE;
    vector<int> i_reco_nopresel_matched_EB, i_reco_nopresel_matched_EE;
    vector<float> vec_eTrue_nopresel_EB, vec_eTrue_nopresel_EE;
    vector<float> vec_eReco_matched_EB, vec_eReco_matched_EE;

    float deltaRmin_nopresel_EB, deltaRmin_nopresel_EE;
    int i_nPhot_nopresel_matched_EB, i_nPhot_nopresel_matched_EE;
    float eTrue_nopresel_EB, eTrue_nopresel_EE;
    float eReco_matched_EB, eReco_matched_EE;
    TVector3 reco_nopresel_EB, reco_nopresel_EE, gen_presel;


    for (int i=0; i<nMC; i++) {
      deltaRmin_nopresel_EB = 0.3;
      deltaRmin_nopresel_EE = 0.3;
      i_nPhot_nopresel_matched_EB = -1;
      i_nPhot_nopresel_matched_EE = -1;
  
      if(photassocMC[i] && ptMC[i]>30 && TMath::Abs(etaMC[i])<1.4442) {
	gen_presel.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	for(int j=0; j<nPhot; j++){
	  reco_nopresel_EB.SetPtEtaPhi(ptPhot[j],etaPhot[j],phiPhot[j]);
	  if(gen_presel.DeltaR(reco_nopresel_EB) < deltaRmin_nopresel_EB) {
	    deltaRmin_nopresel_EB = gen_presel.DeltaR(reco_nopresel_EB);
	    i_nPhot_nopresel_matched_EB = j;
	    eTrue_nopresel_EB = eMC[i];
	    eReco_matched_EB = ePhot[j];
	  }
	}
	
	deltaR_gen_reco_nopresel_EB.push_back(deltaRmin_nopresel_EB);
	i_reco_nopresel_matched_EB.push_back(i_nPhot_nopresel_matched_EB);
	//etasc_reco_nopresel_EB.pushback(etascPhot[i_nPhot_nopresel_matched_EB]);
	vec_eTrue_nopresel_EB.push_back(eTrue_nopresel_EB);
	vec_eReco_matched_EB.push_back(eReco_matched_EB);
      }
    
      else if(photassocMC[i] && ptMC[i]>30 && TMath::Abs(etaMC[i])>1.566 && TMath::Abs(etaMC[i])<2.5 ) {
	gen_presel.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	for(int j=0; j<nPhot; j++){
	  reco_nopresel_EE.SetPtEtaPhi(ptPhot[j],etaPhot[j],phiPhot[j]);
	  if(gen_presel.DeltaR(reco_nopresel_EE) < deltaRmin_nopresel_EE) {
	    deltaRmin_nopresel_EE = gen_presel.DeltaR(reco_nopresel_EE);
	    i_nPhot_nopresel_matched_EE = j;
	    eTrue_nopresel_EE = eMC[i];
	    eReco_matched_EE = ePhot[j];
	  }
	}
	
	deltaR_gen_reco_nopresel_EE.push_back(deltaRmin_nopresel_EE);
	i_reco_nopresel_matched_EE.push_back(i_nPhot_nopresel_matched_EE);
	//	etasc_reco_nopresel_EE.pushback(etascPhot[i_nPhot_nopresel_matched_EE]);
	vec_eTrue_nopresel_EE.push_back(eTrue_nopresel_EE);
	vec_eReco_matched_EE.push_back(eReco_matched_EE);
      }
    }

    for (int i=0; i<nGenPhot; i++) {
      deltaRGenReco_EB_nopresel[i] = -999.;
      deltaRGenReco_EE_nopresel[i] = -999.;
      eTrue_EB_nopresel[i] = -999.;
      eTrue_EE_nopresel[i] = -999.;
      eReco_EB_matched[i] = -999.;
      eReco_EE_matched[i] = -999.;
    }

    for (int i=0; i<deltaR_gen_reco_nopresel_EB.size(); i++) {
      deltaRGenReco_EB_nopresel[i] = deltaR_gen_reco_nopresel_EB[i];
      eTrue_EB_nopresel[i] =  vec_eTrue_nopresel_EB[i];
      eReco_EB_matched[i] = vec_eReco_matched_EB[i];
    }

    for (int i=0; i<deltaR_gen_reco_nopresel_EE.size(); i++) {
      deltaRGenReco_EE_nopresel[i] = deltaR_gen_reco_nopresel_EE[i];
      eTrue_EE_nopresel[i] =  vec_eTrue_nopresel_EE[i];
      eReco_EE_matched[i] = vec_eReco_matched_EE[i];
    }

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

      vector<float> deltaR_gen_reco;
      vector<int> i_reco_matched;


      for(int i=0; i<nMC; i++){
	float deltaRmin(0.3);
	int i_nPhot_matched(-1);
	if(photassocMC[i]) {
	  gen.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	  for (int j=0; j<nPhot_presel; j++){
	    if(gen.DeltaR(recoPhot[j]) < deltaRmin) {
	      deltaRmin = gen.DeltaR(recoPhot[j]);
	      i_nPhot_matched = j;   
	    }
	  }

	  
	  deltaR_gen_reco.push_back(deltaRmin);
	  i_reco_matched.push_back(i_nPhot_matched);
	  
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
	if (i_reco_matched[i]>=0 ) isMatchedPhot[i_reco_matched[i]] = 1;
	deltaRGenReco[i] = deltaR_gen_reco[i];
      }
      // various
      nvtx = nvertex;
      runRN = run;
      eventRN = event;
      lumi = lbn;
      
      ana_tree->Fill();
    }
   
    delete aHLTNames;
  }
  ptphotgen1.Write();
  ana_tree->Write();

}

bool SingleGammaTree_giulia::PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) {

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

  /*
      
  if (val_hoe             >= mitCuts_hoe[photon_category]         ) return false;                                           
  if (val_sieie           >= mitCuts_sieie[photon_category]       ) return false;
  if (val_ecaliso         >= mitCuts_ecaliso[photon_category]     ) return false;
  if (val_hcaliso         >= mitCuts_hcaliso[photon_category]     ) return false;                                           
  if (val_trkiso          >= mitCuts_trkiso[photon_category]      ) return false;
  */
  if ((!val_pho_isconv && electronVeto) ) return false; // Electron Rejection based Conversion Safe Veto

  //if (val_pfiso02 >= mitCuts_pfiso[photon_category]) return false;            
  
  return true;
}


void SingleGammaTree_giulia::SetPuWeights(std::string puWeightFile)
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

void SingleGammaTree_giulia::ClusterShape(Int_t* iPhoton, Float_t* tmva_photonid_sieie, Float_t* tmva_photonid_etawidth, Float_t* tmva_photonid_phiwidth, Float_t* tmva_photonid_r9, Float_t* tmva_photonid_s4ratio)
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


