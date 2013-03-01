#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TAxis.h>
#include <TString.h>
#include "TObjString.h"
#include "TSystem.h"


#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Config.h"
#endif


using namespace std;

void doTMVA_giulia(bool isEB, bool isPtEtaWeight, int nTrees, int depthMax);

int main(int argc, char* argv[]) {

  if(argc < 2 || argc > 4 ) {
    cout << "Usage: ./tmp/runTMVA.cc bool isEB nTrees depthMax \n" 
	 << "argv[1] =  isEB (1 = barrel,     0 = endcaps)\n"
	 << "argv[2] =  nTrees\n"
	 << "argv[3] =  depthMax\n"
	 << endl;
   
    exit(-1);
  }
  else {
    cout << "sto per chiamare doTMVA" << endl;
    bool isEB = atoi(argv[1]);
    int nTrees = atoi(argv[2]);
    int depthMax = atoi(argv[3]);
    
    cout << "isEB = " << isEB << "   nTrees =  " << nTrees << "    depthMax = " << depthMax << endl; 

    doTMVA_giulia(isEB, 0, nTrees, depthMax); 
  
    exit(0);
  }
}


void doTMVA_giulia( bool isEB, bool isPtEtaWeight, int nTrees, int depthMax)
{
   // This loads the library
   TMVA::Tools::Instance();
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start doTMVA_giulia" << std::endl;

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   std::string region;
   if(isEB) region = "_EB";
   else   region = "_EE";
   

   TString outfileName( ("/afs/cern.ch/work/g/gdimperi/CMSSW_5_2_3/src/GammaJets/src/reduced_analysis/doMVA/TMVAoutput"+region+".root").c_str() );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   cout << "file output is: " << outfileName;

   (TMVA::gConfig().GetIONames()).fWeightFileDir = ("/afs/cern.ch/work/g/gdimperi/CMSSW_5_2_3/src/GammaJets/src/reduced_analysis/doMVA/weights"+region).c_str();
   

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   
   if(isEB){		   
     
     factory->AddVariable("pid_scetawid_presel","pid_scetawid_presel","", 'F');	
     factory->AddVariable("pid_scphiwid_presel","pid_scphiwid_presel","", 'F');	
     factory->AddVariable("sEtaEtaPhot_presel","sEtaEtaPhot_presel","", 'F');	
     factory->AddVariable("sEtaPhiPhot_presel","sEtaPhiPhot_presel","", 'F');		
     factory->AddVariable("s4RatioPhot_presel","s4RatioPhot_presel","", 'F');
     factory->AddVariable("r9Phot_presel","r9Phot_presel","", 'F'); 
     factory->AddVariable("ptPhot_presel","ptPhot_presel","", 'F'); 
     factory->AddVariable("etascPhot_presel","etascPhot_presel","", 'F'); 

       
   } else {
     factory->AddVariable("pid_scetawid_presel","pid_scetawid_presel","", 'F');	
     factory->AddVariable("pid_scphiwid_presel","pid_scphiwid_presel","", 'F');	
     factory->AddVariable("sEtaEtaPhot_presel","sEtaEtaPhot_presel","", 'F');	
     factory->AddVariable("sEtaPhiPhot_presel","sEtaPhiPhot_presel","", 'F');		
     factory->AddVariable("s4RatioPhot_presel","s4RatioPhot_presel","", 'F');
     factory->AddVariable("r9Phot_presel","r9Phot_presel","", 'F'); 
     factory->AddVariable("ptPhot_presel","ptPhot_presel","", 'F'); 
     factory->AddVariable("etascPhot_presel","etascPhot_presel","", 'F'); 


     factory->AddVariable("rr_presel","rr_presel","", 'F'); //new
   }
   

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables

   factory->AddSpectator( "nPhot_presel", "nPhot_presel", "", 'F' );
   factory->AddSpectator( "isMatchedPhot", "isMatchedPhot", "", 'F' );
   //factory->AddSpectator( "eventWeight", "eventWeight", "", 'F' );
   //factory->AddSpectator( "pt_eta_weightPhot", "pt_eta_weightPhot", "", 'F' );
   

   
   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   
   //TString fname = "TMVAinput.root";
   /*
     if (gSystem->AccessPathName( fname )) {
     std::cout << "ERROR: input file not found! ABORT" << std::endl;
      return;
   }
   */

   TTree *Str[2], *Ste[2];
   double cross_mc[2];
   double kfactorgamjet = 1.3;
   
   TFile* mc_2012[2];
   
   //mc_2012[0] = TFile::Open("root://pccmsrm27.cern.ch//xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.scales-Lisbon-Hgg.singleGamma_v2_forMVA/merged/redntp_GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
   //mc_2012[1] = TFile::Open("root://pccmsrm27.cern.ch//xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.scales-Lisbon-Hgg.singleGamma_v2_forMVA/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
   
   mc_2012[0] = TFile::Open("/afs/cern.ch/work/g/gdimperi/CMSSW_5_2_3/src/GammaJets/src/reduced_analysis/inputfiles/redntp_GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
   mc_2012[1] = TFile::Open("/afs/cern.ch/work/g/gdimperi/CMSSW_5_2_3/src/GammaJets/src/reduced_analysis/inputfiles/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");

   cross_mc[0] = 0.001835 * 81930.0 * kfactorgamjet;    // gjet pt 20to40       https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/731.html  
   cross_mc[1] = 0.05387 * 8884.0 * kfactorgamjet;      // gjet pt > 40
   
   double n_mc_2012[2];
   n_mc_2012[0] = ((TH1D*)mc_2012[0]->Get("ptphotgen1"))->GetEntries(); 
   n_mc_2012[1] = ((TH1D*)mc_2012[1]->Get("ptphotgen1"))->GetEntries(); 

   // global event weights per tree (see below for setting event-wise weights)
   float int_exp_2012 = 12000.; 
   double scale_mc_2012[2];
   for(int i=0; i<2; i++){
     scale_mc_2012[i] = 0;
     scale_mc_2012[i] = cross_mc[i] * int_exp_2012 / n_mc_2012[i];
   }


   for (int i=0; i<2; i++){
     
     std::cout << "--- TMVAClassification       : Using input file: " << mc_2012[i]->GetName() << std::endl;
     
     // --- Register the training and test trees
     
     Str[i] = ((TTree*)mc_2012[i]->Get("AnaTree_train"));  //Training  tree (Sig & Bkg)
     Ste[i] = ((TTree*)mc_2012[i]->Get("AnaTree_test"));  //Training tree
     

     std::cout<<"******************************"<<std::endl;
     std::cout<<" Signal training:"<<std::endl; 
     std::cout<<" Signal testing: "<<std::endl; 
     std::cout<<"******************************"<<std::endl;
     
     //factory->SetWeightExpression( "eventWeight");   
     // You can add an arbitrary number of signal or background trees
     factory->AddSignalTree    ( Str[i], scale_mc_2012[i], "Training");
     factory->AddSignalTree    ( Ste[i], scale_mc_2012[i], "Test");
     
     factory->AddBackgroundTree    ( Str[i], scale_mc_2012[i], "Training");
     factory->AddBackgroundTree    ( Ste[i], scale_mc_2012[i], "Test");
     
     // set weights for each photon
     // factory->SetWeightExpression("pt_eta_weightPhot");

     
   } 

   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts;
   TCut mycutb;
   
   if(isEB){
     
     mycuts = "abs(etascPhot_presel)<1.4442&& isMatchedPhot==1"; 
     mycutb = "abs(etascPhot_presel)<1.4442&& isMatchedPhot==0";
     
   }else{
     
     mycuts = "abs(etascPhot_presel)>1.566 && abs(etascPhot_presel)<2.5&& isMatchedPhot==1"; 
     mycutb = "abs(etascPhot_presel)>1.566 && abs(etascPhot_presel)<2.5&& isMatchedPhot==0"; 
     
   }
 
    
   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );

   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:NormMode=None:!V" );

   // ---- Book MVA methods
   //

  
   
   // Boosted Decision Trees
   // factory->BookMethod( TMVA::Types::kBDT, "BDTG",
   // "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5" );
   /*
   char ntrees[5];
   sprintf(ntrees, "%d", nTrees);
   char depth[5];
   sprintf(depth, "%d", depthMax);*/
   char parameters[100];
   sprintf(parameters, "%s%d%s%d%s", "!H:!V:NTrees=", nTrees, ":nEventsMin=100:MaxDepth=", depthMax, ":BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=100:PruneMethod=NoPruning");
   //sprintf(parameters, "!H:!V:NTrees=%s:nEventsMin=100:MaxDepth=%s:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=100:PruneMethod=NoPruning", nTrees, depthMax);

   factory->BookMethod( TMVA::Types::kBDT, "BDT", parameters);
			//"!H:!V:NTrees=400:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );


   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}
