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


SingleGammaTree_giulia::SingleGammaTree_giulia(TTree *tree, const TString& outname) : tree_reader_V9(tree), jsonFile(0) //, scaleCorrections_(0)
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

  float deltaRMatch_gen[10];
  float iRecoPhotMatch_gen[10];
  float ptTrueMatch_gen[10];
  float ptRecoMatch_gen[10];
  float etaMatch_gen[10];
  float phiMatch_gen[10];

  float iso02_gen[10];
  float iso03_gen[10];
  float iso04_gen[10];
  float iso05_gen[10];

  float ptPhot_presel[10];
  float ePhot_presel[10];
  float phiPhot_presel[10];
  float etaPhot_presel[10];


  int isMatchedPhot[10];
  int iMatchedPhot[10];
  int isTrig20CaloVLMatchedPhot[10];
  int isTrig30CaloVLMatchedPhot[10];
  int isTrig50CaloVLMatchedPhot[10];
  int isTrig75CaloVLMatchedPhot[10];
  int isTrig90CaloVLMatchedPhot[10];

  float hltCandPt20CaloVLPhot[10];
  float hltCandPt30CaloVLPhot[10];
  float hltCandPt50CaloVLPhot[10];
  float hltCandPt75CaloVLPhot[10];
  float hltCandPt90CaloVLPhot[10];

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


  float pid_pfIsoFPRCharged03_presel[10];
  float pid_pfIsoFPRNeutral03_presel[10];
  float pid_pfIsoFPRPhoton03_presel[10];
  float pid_pfIsoFPRRandomConeCharged03_presel[10];
  float pid_pfIsoFPRRandomConeNeutral03_presel[10];
  float pid_pfIsoFPRRandomConePhoton03_presel[10];
  float pid_pfIsoFPRCharged04_presel[10];
  float pid_pfIsoFPRNeutral04_presel[10];
  float pid_pfIsoFPRPhoton04_presel[10];
  float pid_pfIsoFPRRandomConeCharged04_presel[10];
  float pid_pfIsoFPRRandomConeNeutral04_presel[10];
  float pid_pfIsoFPRRandomConePhoton04_presel[10];
  //Photon Trigger Objects



  ana_tree = new TTree ("AnaTree","Reduced tree for final analysis");
  //ana_tree = new TTree ("AnaTree","Reduced tree for final analysis, 2") ;
  // general
  
  ana_tree->Branch("run",&runRN,"run/I");
  ana_tree->Branch("event",&eventRN,"event/I");
  ana_tree->Branch("lumi",&lumi,"lumi/I");
  ana_tree->Branch("nvtx",&nvtx,"nvtx/F");

  ana_tree->Branch("LOGamma",    &LOGamma,    "LOGamma/I");
  ana_tree->Branch("ISRGamma",   &ISRGamma,   "ISRGamma/I");
  ana_tree->Branch("FSRGamma",   &FSRGamma,   "FSRGamma/I");

  ana_tree->Branch("npu",&npu,"npu/I");
  ana_tree->Branch("NtotEvents",&NtotEvents,"NtotEvents/I");
  ana_tree->Branch("xsection",&xsection,"xsection/F");
  ana_tree->Branch("EquivLumi",&EquivLumi,"EquivLumi/F");
  ana_tree->Branch("SampleID",&SampleID,"SampleID/I");
  ana_tree->Branch("pu_weight",&pu_weight,"pu_weight/F");
  // 
  ana_tree->Branch("pu_weight30",&pu_weight30,"pu_weight30/F");
  ana_tree->Branch("pu_weight50",&pu_weight50,"pu_weight50/F");
  ana_tree->Branch("pu_weight75",&pu_weight75,"pu_weight75/F");
  ana_tree->Branch("pu_weight90",&pu_weight90,"pu_weight90/F");
  ana_tree->Branch("pu_weight135",&pu_weight135,"pu_weight135/F");
  ana_tree->Branch("pu_weight150",&pu_weight150,"pu_weight150/F");
  
  // photons
  ana_tree->Branch("nPhot_gen",&nPhot_gen,"nPhot_gen/I");
  ana_tree->Branch("deltaRMatch_gen", deltaRMatch_gen, "deltaRMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("ptTrueMatch_gen", ptTrueMatch_gen, "ptTrueMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("etaMatch_gen", etaMatch_gen, "etaMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("phiMatch_gen", phiMatch_gen, "phiMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("ptRecoMatch_gen", ptRecoMatch_gen, "ptRecoMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("iRecoPhotMatch_gen", iRecoPhotMatch_gen, "iRecoPhotMatch_gen[nPhot_gen]/F"  );
  ana_tree->Branch("iso02_gen", iso02_gen, "iso02_gen[nPhot_gen]/F"  );
  ana_tree->Branch("iso03_gen", iso03_gen, "iso03_gen[nPhot_gen]/F"  );
  ana_tree->Branch("iso04_gen", iso04_gen, "iso04_gen[nPhot_gen]/F"  );
  ana_tree->Branch("iso05_gen", iso05_gen, "iso05_gen[nPhot_gen]/F"  );

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
		   																	
  ana_tree->Branch("pid_pfIsoFPRCharged03_presel",pid_pfIsoFPRCharged03_presel,"pid_pfIsoFPRCharged03_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRNeutral03_presel",pid_pfIsoFPRNeutral03_presel,"pid_pfIsoFPRNeutral03_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRPhoton03_presel",pid_pfIsoFPRPhoton03_presel,"pid_pfIsoFPRPhoton03_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConeCharged03_presel",pid_pfIsoFPRRandomConeCharged03_presel,"pid_pfIsoFPRRandomConeCharged03_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConeNeutral03_presel",pid_pfIsoFPRRandomConeNeutral03_presel,"pid_pfIsoFPRRandomConeNeutral03_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConePhoton03_presel",pid_pfIsoFPRRandomConePhoton03_presel,"pid_pfIsoFPRRandomConePhoton03_presel[nPhot_presel]/F");		

  ana_tree->Branch("pid_pfIsoFPRCharged04_presel",pid_pfIsoFPRCharged04_presel,"pid_pfIsoFPRCharged04_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRNeutral04_presel",pid_pfIsoFPRNeutral04_presel,"pid_pfIsoFPRNeutral04_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRPhoton04_presel",pid_pfIsoFPRPhoton04_presel,"pid_pfIsoFPRPhoton04_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConeCharged04_presel",pid_pfIsoFPRRandomConeCharged04_presel,"pid_pfIsoFPRRandomConeCharged04_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConeNeutral04_presel",pid_pfIsoFPRRandomConeNeutral04_presel,"pid_pfIsoFPRRandomConeNeutral04_presel[nPhot_presel]/F");		
  ana_tree->Branch("pid_pfIsoFPRRandomConePhoton04_presel",pid_pfIsoFPRRandomConePhoton04_presel,"pid_pfIsoFPRRandomConePhoton04_presel[nPhot_presel]/F");		
		
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
  ana_tree->Branch("iMatchedPhot", iMatchedPhot, "iMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("isTrig20CaloVLMatchedPhot", isTrig20CaloVLMatchedPhot, "isTrig20CaloVLMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("isTrig30CaloVLMatchedPhot", isTrig30CaloVLMatchedPhot, "isTrig30CaloVLMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("isTrig50CaloVLMatchedPhot", isTrig50CaloVLMatchedPhot, "isTrig50CaloVLMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("isTrig75CaloVLMatchedPhot", isTrig75CaloVLMatchedPhot, "isTrig75CaloVLMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("isTrig90CaloVLMatchedPhot", isTrig90CaloVLMatchedPhot, "isTrig90CaloVLMatchedPhot[nPhot_presel]/I"  );
  ana_tree->Branch("hltCandPt20CaloVLPhot", hltCandPt20CaloVLPhot, "hltCandPt20CaloVLPhot[nPhot_presel]/F"  );  
  ana_tree->Branch("hltCandPt30CaloVLPhot", hltCandPt30CaloVLPhot, "hltCandPt30CaloVLPhot[nPhot_presel]/F"  );  
  ana_tree->Branch("hltCandPt50CaloVLPhot", hltCandPt50CaloVLPhot, "hltCandPt50CaloVLPhot[nPhot_presel]/F"  );  
  ana_tree->Branch("hltCandPt75CaloVLPhot", hltCandPt75CaloVLPhot, "hltCandPt75CaloVLPhot[nPhot_presel]/F"  );  
  ana_tree->Branch("hltCandPt90CaloVLPhot", hltCandPt90CaloVLPhot, "hltCandPt90CaloVLPhot[nPhot_presel]/F"  );  

  // vertex
  ana_tree->Branch("vtxId",   &vtxId,   "vtxId/I");

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
    //    vector<TVector3> genPhot, recoPhot;
    //, recoPhot_nopresel;
    //    TVector3 gen, reco, reco_nopresel;

    /// init of mc related variables
    for(int i=0; i<nMC; i++) {
      
      if((pdgIdMC[i] == 22 && statusMC[i] == 3) //photon in the diagram
	 || (pdgIdMC[i] == 22 && statusMC[i] == 1 && (TMath::Abs(pdgIdMC[motherIDMC[i]])<=10 ) ) //photon coming from a quark
	 )
	{
	  
	  photassocMC.push_back(1);	
	  ptTrueMatch_gen[nGenPhot] =   ptMC[i];
	  etaMatch_gen[nGenPhot] =   etaMC[i];
	  phiMatch_gen[nGenPhot] =   phiMC[i];

	  iso02_gen[nGenPhot]=isoParticleChargedDR02MC[i]+isoParticleEMNeutralDR02MC[i]+isoParticleHADNeutralDR02MC[i];
	  iso03_gen[nGenPhot]=isoParticleChargedDR03MC[i]+isoParticleEMNeutralDR03MC[i]+isoParticleHADNeutralDR03MC[i];
	  iso04_gen[nGenPhot]=isoParticleChargedDR04MC[i]+isoParticleEMNeutralDR04MC[i]+isoParticleHADNeutralDR04MC[i];
	  iso05_gen[nGenPhot]=isoParticleChargedDR05MC[i]+isoParticleEMNeutralDR05MC[i]+isoParticleHADNeutralDR05MC[i];

	  TVector3 gen;
	  gen.SetPtEtaPhi(ptMC[i], etaMC[i], phiMC[i]);
	  float deltaRmin = 0.3;
	  int i_nPhot=-1;
	  for(int j=0; j<nPhot; j++)
	    {
	      TVector3 reco;
	      reco.SetPtEtaPhi(ptPhot[j],etaPhot[j],phiPhot[j]);
	      if(gen.DeltaR(reco) < deltaRmin) 
		{
		  deltaRmin = gen.DeltaR(reco);
		  i_nPhot = j;
		}
	    }
	  
	  if (i_nPhot>-1)
	    {
	      deltaRMatch_gen[nGenPhot] = deltaRmin;
	      ptRecoMatch_gen[nGenPhot] = ptPhot[i_nPhot];
	      iRecoPhotMatch_gen[nGenPhot] = i_nPhot;
	    }
	  else
	    {
	      deltaRMatch_gen[nGenPhot] = -999.;
	      ptRecoMatch_gen[nGenPhot] = -999.;
	      iRecoPhotMatch_gen[nGenPhot] = -999;
	    }
	  nGenPhot++;
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

    // for dedicated HLT selections
    if(npu<MAX_PU_REWEIGHT && nMC>0) {

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

      if(puweights135_.size()>0) 
	pu_weight135 = puweights135_[npu];  
      else 
	pu_weight135 = 1.;

      if(puweights150_.size()>0) 
	pu_weight150 = puweights150_[npu];  
      else 
	pu_weight150 = 1.;
    }

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
      
      if( ! (ptPhot[i] > 30 //eT threshold  
	     && PhotonMITPreSelection(i,0,1)  //isolation (trigger level)    
	     && ((TMath::Abs(etascPhot[i]) < 1.4442) || (TMath::Abs(etascPhot[i]) > 1.566 && TMath::Abs(etascPhot[i]) < 2.5)) ) )//ECAL
	{ 
	  preselPhot.push_back(0);
	  continue;
	}	  
    
      preselPhot.push_back(1);
      
      float rr2=0;
      if (isEEPhot)
	rr2=pid_esXwidth[i]*pid_esXwidth[i]+pid_esYwidth[i]*pid_esYwidth[i];
      float r9phot = E9Phot[i] / escRawPhot[i];
      float s4phot = E4Phot[i] / E25Phot[i];
      
      //cout << "setaeta before: " << pid_etawid[i] << "  " << endl;    
      ClusterShape(&i, &pid_etawid[i], &pid_scetawid[i], &pid_scphiwid[i], &r9phot, &s4phot);
      //cout << "setaeta after: " << pid_etawid[i] << "  " << endl << endl;    
      
      ptPhot_presel[countPreselPhot] = ptPhot[i];
      ePhot_presel[countPreselPhot] = ePhot[i];
      etaPhot_presel[countPreselPhot] = etaPhot[i];
      phiPhot_presel[countPreselPhot] = phiPhot[i];
      //MVA variables
      pid_scetawid_presel[countPreselPhot] = pid_scetawid[i];
      pid_scphiwid_presel[countPreselPhot] = pid_scphiwid[i];
      sEtaEtaPhot_presel[countPreselPhot] = pid_etawid[i];
      sEtaPhiPhot_presel[countPreselPhot] = sEtaPhiPhot[i];
      
      s4RatioPhot_presel[countPreselPhot] = s4phot; 
      r9Phot_presel[countPreselPhot] = r9phot;
      etascPhot_presel[countPreselPhot] = etascPhot[i];
      
      rr_presel[countPreselPhot] = sqrt(rr2);
      
      pid_lambdaRatio_presel[countPreselPhot] = pid_lambdaRatio[i]; 
      pid_HoverE_presel[countPreselPhot] = pid_HoverE[i];
      
      //if (TMath::Abs(etasc[countPreselPhot])>1.566) cout << "pt[" << i <<"] = " << pt[i] << "    etasc[" << i << "] = " << etasc[countPreselPhot] << endl;
      //iso variables

      pid_jurECAL03_presel[countPreselPhot] = pid_jurECAL03[i];
      pid_twrHCAL03_presel[countPreselPhot] = pid_twrHCAL03[i];
      pid_hlwTrack03_presel[countPreselPhot]= pid_hlwTrack03[i];
      pid_jurECAL04_presel[countPreselPhot] = pid_jurECAL[i];
      pid_twrHCAL04_presel[countPreselPhot] = pid_twrHCAL[i];
      pid_hlwTrack04_presel[countPreselPhot]= pid_hlwTrack[i];


      pid_pfIsoPhotons01ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons01ForCiC[i];	   
      pid_pfIsoPhotons02ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons02ForCiC[i];	   
      pid_pfIsoPhotons03ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons03ForCiC[i]; 	   
      pid_pfIsoPhotons04ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons04ForCiC[i];	   
      pid_pfIsoPhotons05ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons05ForCiC[i];	   
      pid_pfIsoPhotons06ForCiC_presel[countPreselPhot] = pid_pfIsoPhotons06ForCiC[i]; 	   
      pid_pfIsoNeutrals01ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals01ForCiC[i] ;	   
      pid_pfIsoNeutrals02ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals02ForCiC[i] ;	   
      pid_pfIsoNeutrals03ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals03ForCiC[i] ;	   
      pid_pfIsoNeutrals04ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals04ForCiC[i] ;	   
      pid_pfIsoNeutrals05ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals05ForCiC[i] ;	   
      pid_pfIsoNeutrals06ForCiC_presel[countPreselPhot] =pid_pfIsoNeutrals06ForCiC[i] ;	   
      
      pid_pfIsoCharged01ForCiC_presel[countPreselPhot] = pid_pfIsoCharged01ForCiC[i][0];
      pid_pfIsoCharged02ForCiC_presel[countPreselPhot] = pid_pfIsoCharged02ForCiC[i][0];
      pid_pfIsoCharged03ForCiC_presel[countPreselPhot] = pid_pfIsoCharged03ForCiC[i][0];
      pid_pfIsoCharged04ForCiC_presel[countPreselPhot] = pid_pfIsoCharged04ForCiC[i][0];
      pid_pfIsoCharged05ForCiC_presel[countPreselPhot] = pid_pfIsoCharged05ForCiC[i][0];
      pid_pfIsoCharged06ForCiC_presel[countPreselPhot] = pid_pfIsoCharged06ForCiC[i][0];

      pid_pfIsoFPRCharged03_presel[countPreselPhot] = pid_pfIsoFPRCharged03[i];
      pid_pfIsoFPRNeutral03_presel[countPreselPhot] = pid_pfIsoFPRNeutral03[i];
      pid_pfIsoFPRPhoton03_presel[countPreselPhot] = pid_pfIsoFPRPhoton03[i];

      pid_pfIsoFPRRandomConeCharged03_presel[countPreselPhot] = pid_pfIsoFPRRandomConeCharged03[i];
      pid_pfIsoFPRRandomConeNeutral03_presel[countPreselPhot] = pid_pfIsoFPRRandomConeNeutral03[i];
      pid_pfIsoFPRRandomConePhoton03_presel[countPreselPhot] = pid_pfIsoFPRRandomConePhoton03[i];

      pid_pfIsoFPRCharged04_presel[countPreselPhot] = pid_pfIsoFPRCharged04[i];
      pid_pfIsoFPRNeutral04_presel[countPreselPhot] = pid_pfIsoFPRNeutral04[i];
      pid_pfIsoFPRPhoton04_presel[countPreselPhot] = pid_pfIsoFPRPhoton04[i];

      pid_pfIsoFPRRandomConeCharged04_presel[countPreselPhot] = pid_pfIsoFPRRandomConeCharged04[i];
      pid_pfIsoFPRRandomConeNeutral04_presel[countPreselPhot] = pid_pfIsoFPRRandomConeNeutral04[i];
      pid_pfIsoFPRRandomConePhoton04_presel[countPreselPhot] = pid_pfIsoFPRRandomConePhoton04[i];

      isMatchedPhot[countPreselPhot] = 0;
      iMatchedPhot[countPreselPhot] = -1;
      
      for(int igen=0; igen<nPhot_gen; igen++) {
	if (iRecoPhotMatch_gen[igen]==i ) 
	  {
	    isMatchedPhot[countPreselPhot] = 1;
	    iMatchedPhot[countPreselPhot] = igen;
	  }	
      }


   TVector3 reco;
   reco.SetPtEtaPhi(ptPhot[i], etaPhot[i], phiPhot[i]);
   float deltaRmin = 0.3;
   float hltPtDRmin = -999.;    
   int i_nPhot=-1;
   for(int j=0; j<trg20_phoIDCaloVL_n; j++)
     {
       TVector3 trig;
       if (trg20_phoIDCaloVL_et[j]<=0 || TMath::Abs(trg20_phoIDCaloVL_eta[j])>2.5 || TMath::Abs(trg20_phoIDCaloVL_phi[j])>TMath::Pi() )
	 continue;
       trig.SetPtEtaPhi(trg20_phoIDCaloVL_et[j],trg20_phoIDCaloVL_eta[j],trg20_phoIDCaloVL_phi[j]);
       if(reco.DeltaR(trig) < deltaRmin) 
	 {
	   
	   deltaRmin = reco.DeltaR(trig);
	   hltPtDRmin = trg20_phoIDCaloVL_et[j];
	   i_nPhot = j;
	 }
     }
   
   if (i_nPhot>-1) {
     isTrig20CaloVLMatchedPhot[countPreselPhot]=1;
     hltCandPt20CaloVLPhot[countPreselPhot]=hltPtDRmin;
   } else {
     isTrig20CaloVLMatchedPhot[countPreselPhot]=0;
     hltCandPt20CaloVLPhot[countPreselPhot]=-999.;
   }     

     deltaRmin = 0.3;
     hltPtDRmin = -999.;
     i_nPhot=-1;
     for(int j=0; j<trg30_phoIDCaloVL_n; j++)
       {
         TVector3 trig;
 	if (trg30_phoIDCaloVL_et[j]<=0 || TMath::Abs(trg30_phoIDCaloVL_eta[j])>2.5 || TMath::Abs(trg30_phoIDCaloVL_phi[j])>TMath::Pi() )
 	  continue;
         trig.SetPtEtaPhi(trg30_phoIDCaloVL_et[j],trg30_phoIDCaloVL_eta[j],trg30_phoIDCaloVL_phi[j]);
         if(reco.DeltaR(trig) < deltaRmin) 
  	 {
  	   deltaRmin = reco.DeltaR(trig);
	   hltPtDRmin = trg30_phoIDCaloVL_et[j];
  	   i_nPhot = j;
  	 }
       }

     if (i_nPhot>-1) {
       isTrig30CaloVLMatchedPhot[countPreselPhot]=1;
       hltCandPt30CaloVLPhot[countPreselPhot]=hltPtDRmin;
     } else {
       isTrig30CaloVLMatchedPhot[countPreselPhot]=0;
       hltCandPt30CaloVLPhot[countPreselPhot]=-999.;
     }

     deltaRmin = 0.3;
     hltPtDRmin = -999.;
     i_nPhot=-1;
     for(int j=0; j<trg50_phoIDCaloVL_n; j++)
       {
         TVector3 trig;
 	if (trg50_phoIDCaloVL_et[j]<=0 || TMath::Abs(trg50_phoIDCaloVL_eta[j])>2.5 || TMath::Abs(trg50_phoIDCaloVL_phi[j])>TMath::Pi())
 	  continue;
         trig.SetPtEtaPhi(trg50_phoIDCaloVL_et[j],trg50_phoIDCaloVL_eta[j],trg50_phoIDCaloVL_phi[j]);
         if(reco.DeltaR(trig) < deltaRmin) 
  	 {
  	   deltaRmin = reco.DeltaR(trig);
	   hltPtDRmin = trg50_phoIDCaloVL_et[j];
  	   i_nPhot = j;
  	 }
       }

     if (i_nPhot>-1) {
       isTrig50CaloVLMatchedPhot[countPreselPhot]=1;
       hltCandPt50CaloVLPhot[countPreselPhot]=hltPtDRmin;
     } else {
       isTrig50CaloVLMatchedPhot[countPreselPhot]=0;
       hltCandPt50CaloVLPhot[countPreselPhot]=-999.;
     }

     deltaRmin = 0.3;
     hltPtDRmin = -999.;
     i_nPhot=-1;
     for(int j=0; j<trg75_phoIDCaloVL_n; j++)
       {
         TVector3 trig;
 	if (trg75_phoIDCaloVL_et[j]<=0 || TMath::Abs(trg75_phoIDCaloVL_eta[j])>2.5 || TMath::Abs(trg75_phoIDCaloVL_phi[j])>TMath::Pi())
 	  continue;
         trig.SetPtEtaPhi(trg75_phoIDCaloVL_et[j],trg75_phoIDCaloVL_eta[j],trg75_phoIDCaloVL_phi[j]);
         if(reco.DeltaR(trig) < deltaRmin) 
  	 {
  	   deltaRmin = reco.DeltaR(trig);
	   hltPtDRmin = trg75_phoIDCaloVL_et[j];
  	   i_nPhot = j;
  	 }
       }

     if (i_nPhot>-1) {
       isTrig75CaloVLMatchedPhot[countPreselPhot]=1;
       hltCandPt75CaloVLPhot[countPreselPhot]=hltPtDRmin;
     } else {
       isTrig75CaloVLMatchedPhot[countPreselPhot]=0;
       hltCandPt75CaloVLPhot[countPreselPhot]=-999.;
     }

      deltaRmin = 0.3;
      hltPtDRmin = -999.;
      i_nPhot=-1;
      for(int j=0; j<trg90_phoIDCaloVL_n; j++)
        {
          TVector3 trig;
 	 //	 std::cout << j << "," << trg90_phoIDCaloVL_et[j] << "," << trg90_phoIDCaloVL_eta[j] << "," << trg90_phoIDCaloVL_phi[j] << std::endl;
  	if (trg90_phoIDCaloVL_et[j]<=0 || TMath::Abs(trg90_phoIDCaloVL_eta[j])>2.5 || TMath::Abs(trg90_phoIDCaloVL_phi[j])>TMath::Pi())
  	  continue;
          trig.SetPtEtaPhi(trg90_phoIDCaloVL_et[j],trg90_phoIDCaloVL_eta[j],trg90_phoIDCaloVL_phi[j]);
          if(reco.DeltaR(trig) < deltaRmin) 
   	 {
   	   deltaRmin = reco.DeltaR(trig);
	   hltPtDRmin = trg90_phoIDCaloVL_et[j];
   	   i_nPhot = j;
   	 }
        }

      if (i_nPhot>-1) {
        isTrig90CaloVLMatchedPhot[countPreselPhot]=1;
	hltCandPt90CaloVLPhot[countPreselPhot]=hltPtDRmin;
      } else {
        isTrig90CaloVLMatchedPhot[countPreselPhot]=0;
	hltCandPt90CaloVLPhot[countPreselPhot]=-999.;
      }
      countPreselPhot++;
	 
    }

    nPhot_presel= countPreselPhot;

    // various
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
    
    ana_tree->Fill();
  
    delete aHLTNames;
  }
  ptphotgen1.Write();
  ana_tree->Write();
}

bool SingleGammaTree_giulia::PhotonMITPreSelection( int photon_index, int vertex_index, bool electronVeto) {

  int photon_category = PhotonCategory(photon_index);

//   float mitCuts_hoe[4]                 = {0.082,0.075,0.075,0.075};                                        
//   float mitCuts_sieie[4]               = {0.014,0.014,0.034,0.034};                                        

  float mitCuts_hoe[4]                 = {0.075,0.075,0.075,0.075};                                        
  float mitCuts_sieie[4]               = {0.014,0.014,0.034,0.034};                                        

//   float mitCuts_ecaliso[4]             = {50,4,50,4};                                                      
//   float mitCuts_hcaliso[4]             = {50,4,50,4};                                                      
//   float mitCuts_trkiso[4]              = {50,4,50,4};

  //Applyling looser preselection for nonISO triggers
  float mitCuts_ecaliso[4]             = {50,50,50,50};                                                      
  float mitCuts_hcaliso[4]             = {50,50,50,50};                                                      
  float mitCuts_trkiso[4]              = {50,50,50,50};                                                      
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

// leave the main pu weight as it is. Add this new one for dedicated HLT patsh 
void SingleGammaTree_giulia::SetPuWeightsHLT(std::string puWeightFileHLT, int hltThresh)
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
    if (hltThresh==135) puweights135_.push_back(weight);  
    if (hltThresh==150) puweights150_.push_back(weight);  
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

int SingleGammaTree_giulia::countLOGenGamma(){
  
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

int SingleGammaTree_giulia::countISRGenGamma(){
  
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

int SingleGammaTree_giulia::countFSRGenGamma(){
  
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
