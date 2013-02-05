#include "SingleGammaMVA.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

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

using namespace std;

void finalize_giulia(double int_exp_2012);

int main() {
  
  float lumi2012=12000;  //in pb, prova 

  cout << "calling finalize_giulia" << endl;
  finalize_giulia(lumi2012);

  exit(0);
}

void finalize_giulia(double int_exp_2012) {

  TFile* mc_2012[2];
  
  mc_2012[0] = TFile::Open("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.scales-Lisbon-Hgg.singleGamma_v2/merged/redntp_GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
  mc_2012[1] = TFile::Open("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.scales-Lisbon-Hgg.singleGamma_v2/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
  
  double cross_mc[2];
  double kfactorgamjet = 1.3;

  cross_mc[0] = 0.001835 * 81930.0 * kfactorgamjet;    // gjet pt 20to40       https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/731.html  
  cross_mc[1] = 0.05387 * 8884.0 * kfactorgamjet;      // gjet pt > 40
  
  int n_mc_2012[2];
  n_mc_2012[0] = ((TH1D*)mc_2012[0]->Get("ptphotgen1"))->GetEntries(); 
  n_mc_2012[1] = ((TH1D*)mc_2012[1]->Get("ptphotgen1"))->GetEntries(); 

  string mcnames[2];
  mcnames[0] = "gjet20to40";
  mcnames[1] = "gjet40";
  
  // setting the scaling factor to actual lumi
  double scale_mc_2012[2];
  for(int i=0; i<2; i++){
    scale_mc_2012[i] = 0;
    scale_mc_2012[i] = cross_mc[i] * int_exp_2012 / n_mc_2012[i];
    
  }

  SingleGammaMVA* mc_2012_fill[2];
    
  for (int i=0; i<2; i++) {
    if(int_exp_2012>0) mc_2012_fill[i] = new SingleGammaMVA( (TTree*)mc_2012[i]->Get("AnaTree"));
  }
   

  //Pile Up reweighting ??
  
  //define histograms
    // char for output name
  char name[1000];

  TFile* output_file[2];
    
   TH1F *h_PromptPhot[2]          ;
   TH1F *h_FakePhot[2]            ;
   TH1F *h_isMatchedPhot[2]        ;
        				    
   TH1F *h_scetawid_bkg_EB[2]      ;
   TH1F *h_scphiwid_bkg_EB[2]      ;
   TH1F *h_sEtaEtaPhot_bkg_EB[2]   ;
   TH1F *h_sEtaPhiPhot_bkg_EB[2]   ;
   TH1F *h_s4RatioPhot_bkg_EB[2]   ;
   TH1F *h_r9Phot_bkg_EB[2]        ;
   TH1F *h_etascPhot_bkg_EB[2]     ;
   TH1F *h_rhoAllJets_bkg_EB[2]    ;
   TH1F *h_rr_bkg_EB[2]            ;
   TH1F *h_lambdaRatio_bkg_EB[2]   ;
        				    			     
   TH1F *h_scetawid_bkg_EE[2]      ;
   TH1F *h_scphiwid_bkg_EE[2]      ;
   TH1F *h_sEtaEtaPhot_bkg_EE[2]   ;
   TH1F *h_sEtaPhiPhot_bkg_EE[2]   ;
   TH1F *h_s4RatioPhot_bkg_EE[2]   ;
   TH1F *h_r9Phot_bkg_EE[2]        ;
   TH1F *h_etascPhot_bkg_EE[2]     ;
   TH1F *h_rhoAllJets_bkg_EE[2]    ;
   TH1F *h_rr_bkg_EE[2]            ;
   TH1F *h_lambdaRatio_bkg_EE[2]   ;
        				    
        				    
   TH1F *h_scetawid_sig_EB[2]      ;
   TH1F *h_scphiwid_sig_EB[2]      ;
   TH1F *h_sEtaEtaPhot_sig_EB[2]   ;
   TH1F *h_sEtaPhiPhot_sig_EB[2]   ;
   TH1F *h_s4RatioPhot_sig_EB[2]   ;
   TH1F *h_r9Phot_sig_EB[2]        ;
   TH1F *h_etascPhot_sig_EB[2]     ;
   TH1F *h_rhoAllJets_sig_EB[2]    ;
   TH1F *h_rr_sig_EB[2]            ;
   TH1F *h_lambdaRatio_sig_EB[2]   ;				
        	  			    
   TH1F *h_scetawid_sig_EE[2]      ;
   TH1F *h_scphiwid_sig_EE[2]      ;
   TH1F *h_sEtaEtaPhot_sig_EE[2]   ;
   TH1F *h_sEtaPhiPhot_sig_EE[2]   ;
   TH1F *h_s4RatioPhot_sig_EE[2]   ;
   TH1F *h_r9Phot_sig_EE[2]        ;
   TH1F *h_etascPhot_sig_EE[2]     ;
   TH1F *h_rhoAllJets_sig_EE[2]    ;
   TH1F *h_rr_sig_EE[2]            ;
   TH1F *h_lambdaRatio_sig_EE[2]   ;

   TH1F *plots_sig_EB[2][10], *plots_sig_EE[2][10], *plots_bkg_EB[2][10], *plots_bkg_EE[2][10];

   for(int i=0; i<2; i++){

     sprintf(name, "%s%s%s", "analysis_singlegamma_",mcnames[i].c_str(),".root") ;
     output_file[i]  = new TFile(name, "RECREATE");
     output_file[i]->cd();
     //TH1F *h_etaSC;

     // il nome dell'istogramma  deve essere diverso per diversi file!!!! 
     h_PromptPhot[i]          = new TH1F("h_PromptPhot", "", 5, -0.5, 4.5);			   
     h_FakePhot[i]            = new TH1F("h_FakePhot", "", 11, -0.5, 10.5);			   
     h_isMatchedPhot[i]       = new TH1F("h_isMatchedPhot", "", 2, 0., 2.);			   
     
     h_scetawid_bkg_EB[i]      = new TH1F("h_scetawid_bkg_EB", "", 60, 0., 0.03);	     		   
     h_scphiwid_bkg_EB[i]      = new TH1F("h_scphiwid_bkg_EB", "", 60, 0., 0.15);	     		   
     h_sEtaEtaPhot_bkg_EB[i]   = new TH1F("h_sEtaEtaPhot_bkg_EB", "", 60, 0.005, 0.015);    	   
     h_sEtaPhiPhot_bkg_EB[i]   = new TH1F("h_sEtaPhiPhot_bkg_EB", "", 60, -0.0002, 0.0002); 	   
     h_s4RatioPhot_bkg_EB[i]   = new TH1F("h_s4RatioPhot_bkg_EB", "", 60, 0., 1.);	     		   
     h_r9Phot_bkg_EB[i]        = new TH1F("h_r9Phot_bkg_EB", "", 60, 0., 1.);		     	   
     h_etascPhot_bkg_EB[i]     = new TH1F("h_etascPhot_bkg_EB", "", 60, -2.5, 2.5);  	     	   
     h_rhoAllJets_bkg_EB[i]    = new TH1F("h_rhoAllJets_bkg_EB", "", 60, 0., 60.);	     		   
     h_rr_bkg_EB[i]            = new TH1F("h_rr_bkg_EB", "", 60, 0., 50.);		     		   
     h_lambdaRatio_bkg_EB[i]   = new TH1F("h_lambdaRatio_bkg_EB", "", 60, 0., 1.);		     	   
     			      		 		  		  
     h_scetawid_bkg_EE[i]      = new TH1F("h_scetawid_bkg_EE", "", 60, 0., 0.06);	     		   
     h_scphiwid_bkg_EE[i]      = new TH1F("h_scphiwid_bkg_EE", "", 60, 0., 0.15);	     		   
     h_sEtaEtaPhot_bkg_EE[i]   = new TH1F("h_sEtaEtaPhot_bkg_EE", "", 60, 0.015, 0.035);    	   
     h_sEtaPhiPhot_bkg_EE[i]   = new TH1F("h_sEtaPhiPhot_bkg_EE", "", 60, -0.001, 0.001);   	   
     h_s4RatioPhot_bkg_EE[i]   = new TH1F("h_s4RatioPhot_bkg_EE", "", 60, 0., 1.);	     		   
     h_r9Phot_bkg_EE[i]        = new TH1F("h_r9Phot_bkg_EE", "", 60, 0., 1.);		     	   
     h_etascPhot_bkg_EE[i]     = new TH1F("h_etascPhot_bkg_EE", "", 60, -2.5, 2.5);  	     	   
     h_rhoAllJets_bkg_EE[i]    = new TH1F("h_rhoAllJets_bkg_EE", "", 60, 0., 60.);	     		   
     h_rr_bkg_EE[i]            = new TH1F("h_rr_bkg_EE", "", 60, 0., 15.);                  	   
     h_lambdaRatio_bkg_EE[i]   = new TH1F("h_lambdaRatio_bkg_EE", "", 60, 0., 1.);		     	   
     			     		  	      
     h_scetawid_sig_EB[i]      = new TH1F("h_scetawid_sig_EB", "", 60, 0., 0.03);	     		   
     h_scphiwid_sig_EB[i]      = new TH1F("h_scphiwid_sig_EB", "", 60, 0., 0.15);	     		   
     h_sEtaEtaPhot_sig_EB[i]   = new TH1F("h_sEtaEtaPhot_sig_EB", "", 60, 0.005, 0.015);    	   
     h_sEtaPhiPhot_sig_EB[i]   = new TH1F("h_sEtaPhiPhot_sig_EB", "", 60, -0.0002, 0.0002); 	   
     h_s4RatioPhot_sig_EB[i]   = new TH1F("h_s4RatioPhot_sig_EB", "", 60, 0., 1.);	     		   
     h_r9Phot_sig_EB[i]        = new TH1F("h_r9Phot_sig_EB", "", 60, 0., 1.);		     	   
     h_etascPhot_sig_EB[i]     = new TH1F("h_etascPhot_sig_EB", "", 60, -2.5, 2.5);  	     	   
     h_rhoAllJets_sig_EB[i]    = new TH1F("h_rhoAllJets_sig_EB", "", 60, 0., 60.);	     		   
     h_rr_sig_EB[i]            = new TH1F("h_rr_sig_EB", "", 60, 0., 50.);		     		   
     h_lambdaRatio_sig_EB[i]   = new TH1F("h_lambdaRatio_sig_EB", "", 60, 0., 1.);		           
     			      		 		  		  
     h_scetawid_sig_EE[i]      = new TH1F("h_scetawid_sig_EE", "", 60, 0., 0.06);	     		   
     h_scphiwid_sig_EE[i]      = new TH1F("h_scphiwid_sig_EE", "", 60, 0., 0.15);	     		   
     h_sEtaEtaPhot_sig_EE[i]   = new TH1F("h_sEtaEtaPhot_sig_EE", "", 60, 0.015, 0.035);    	   
     h_sEtaPhiPhot_sig_EE[i]   = new TH1F("h_sEtaPhiPhot_sig_EE", "", 60, -0.001, 0.001);   	   
     h_s4RatioPhot_sig_EE[i]   = new TH1F("h_s4RatioPhot_sig_EE", "", 60, 0., 1.);	     		   
     h_r9Phot_sig_EE[i]        = new TH1F("h_r9Phot_sig_EE", "", 60, 0., 1.);		     	   
     h_etascPhot_sig_EE[i]     = new TH1F("h_etascPhot_sig_EE", "", 60, -2.5, 2.5);  	     	   
     h_rhoAllJets_sig_EE[i]    = new TH1F("h_rhoAllJets_sig_EE", "", 60, 0., 60.);	     		   
     h_rr_sig_EE[i]            = new TH1F("h_rr_sig_EE", "", 60, 0., 15.);                  	   
     h_lambdaRatio_sig_EE[i]   = new TH1F("h_lambdaRatio_sig_EE", "", 60, 0., 1.);		           
 
 
     //axes
     h_PromptPhot[i]  ->GetXaxis()->SetTitle("nPromptPhot");
     h_FakePhot[i]    ->GetXaxis()->SetTitle("nFakePhot");
     h_isMatchedPhot[i]->GetXaxis()->SetTitle("isMatchedPhot");
     
     h_scetawid_bkg_EB[i]     ->GetXaxis()->SetTitle("etaWidth");
     h_scphiwid_bkg_EB[i]     ->GetXaxis()->SetTitle("phiWidth");
     h_sEtaEtaPhot_bkg_EB[i]  ->GetXaxis()->SetTitle("sEtaEta");
     h_sEtaPhiPhot_bkg_EB[i]  ->GetXaxis()->SetTitle("sEtaPhi");
     h_s4RatioPhot_bkg_EB[i]  ->GetXaxis()->SetTitle("S4");
     h_r9Phot_bkg_EB[i]       ->GetXaxis()->SetTitle("R9");
     h_etascPhot_bkg_EB[i]    ->GetXaxis()->SetTitle("etaSC");
     h_rhoAllJets_bkg_EB[i]   ->GetXaxis()->SetTitle("rhoAllJets");
     h_rr_bkg_EB[i]           ->GetXaxis()->SetTitle("preshower_sRR");
     h_lambdaRatio_bkg_EB[i]  ->GetXaxis()->SetTitle("lambdaRatio");
     
     h_scetawid_bkg_EE[i]     ->GetXaxis()->SetTitle("etaWidth");
     h_scphiwid_bkg_EE[i]     ->GetXaxis()->SetTitle("phiWidth");
     h_sEtaEtaPhot_bkg_EE[i]  ->GetXaxis()->SetTitle("sEtaEta");
     h_sEtaPhiPhot_bkg_EE[i]  ->GetXaxis()->SetTitle("sEtaPhi");
     h_s4RatioPhot_bkg_EE[i]  ->GetXaxis()->SetTitle("S4");
     h_r9Phot_bkg_EE[i]       ->GetXaxis()->SetTitle("R9");
     h_etascPhot_bkg_EE[i]    ->GetXaxis()->SetTitle("etaSC");
     h_rhoAllJets_bkg_EE[i]   ->GetXaxis()->SetTitle("rhoAllJets");
     h_rr_bkg_EE[i]           ->GetXaxis()->SetTitle("preshower_sRR");
     h_lambdaRatio_bkg_EE[i]  ->GetXaxis()->SetTitle("lambdaRatio");
     
     
     h_scetawid_sig_EB[i]     ->GetXaxis()->SetTitle("etaWidth");
     h_scphiwid_sig_EB[i]     ->GetXaxis()->SetTitle("phiWidth");
     h_sEtaEtaPhot_sig_EB[i]  ->GetXaxis()->SetTitle("sEtaEta");
     h_sEtaPhiPhot_sig_EB[i]  ->GetXaxis()->SetTitle("sEtaPhi");
     h_s4RatioPhot_sig_EB[i]  ->GetXaxis()->SetTitle("S4");
     h_r9Phot_sig_EB[i]       ->GetXaxis()->SetTitle("R9");
     h_etascPhot_sig_EB[i]    ->GetXaxis()->SetTitle("etaSC");
     h_rhoAllJets_sig_EB[i]   ->GetXaxis()->SetTitle("rhoAllJets");
     h_rr_sig_EB[i]           ->GetXaxis()->SetTitle("preshower_sRR");
     h_lambdaRatio_sig_EB[i]  ->GetXaxis()->SetTitle("lambdaRatio");
     
     h_scetawid_sig_EE[i]     ->GetXaxis()->SetTitle("etaWidth");
     h_scphiwid_sig_EE[i]     ->GetXaxis()->SetTitle("phiWidth");
     h_sEtaEtaPhot_sig_EE[i]  ->GetXaxis()->SetTitle("sEtaEta");
     h_sEtaPhiPhot_sig_EE[i]  ->GetXaxis()->SetTitle("sEtaPhi");
     h_s4RatioPhot_sig_EE[i]  ->GetXaxis()->SetTitle("S4");
     h_r9Phot_sig_EE[i]       ->GetXaxis()->SetTitle("R9");
     h_etascPhot_sig_EE[i]    ->GetXaxis()->SetTitle("etaSC");
     h_rhoAllJets_sig_EE[i]   ->GetXaxis()->SetTitle("rhoAllJets");
     h_rr_sig_EE[i]           ->GetXaxis()->SetTitle("preshower_sRR");
     h_lambdaRatio_sig_EE[i]  ->GetXaxis()->SetTitle("lambdaRatio");

     plots_sig_EB[i][0] = h_scetawid_sig_EB[i]   ;
     plots_sig_EB[i][1] = h_scphiwid_sig_EB[i]   ;
     plots_sig_EB[i][2] = h_sEtaEtaPhot_sig_EB[i];
     plots_sig_EB[i][3] = h_sEtaPhiPhot_sig_EB[i];
     plots_sig_EB[i][4] = h_s4RatioPhot_sig_EB[i];
     plots_sig_EB[i][5] = h_r9Phot_sig_EB[i]     ;
     plots_sig_EB[i][6] = h_etascPhot_sig_EB[i]  ;
     plots_sig_EB[i][7] = h_rhoAllJets_sig_EB[i] ;
     plots_sig_EB[i][8] = h_rr_sig_EB[i]         ;
     plots_sig_EB[i][9] = h_lambdaRatio_sig_EB[i];
     		       		    
     plots_sig_EE[i][0] = h_scetawid_sig_EE[i]   ;
     plots_sig_EE[i][1] = h_scphiwid_sig_EE[i]   ;
     plots_sig_EE[i][2] = h_sEtaEtaPhot_sig_EE[i];
     plots_sig_EE[i][3] = h_sEtaPhiPhot_sig_EE[i];
     plots_sig_EE[i][4] = h_s4RatioPhot_sig_EE[i];
     plots_sig_EE[i][5] = h_r9Phot_sig_EE[i]     ;
     plots_sig_EE[i][6] = h_etascPhot_sig_EE[i]  ;
     plots_sig_EE[i][7] = h_rhoAllJets_sig_EE[i] ;
     plots_sig_EE[i][8] = h_rr_sig_EE[i]         ;
     plots_sig_EE[i][9] = h_lambdaRatio_sig_EE[i];
	       	       			  
     plots_bkg_EB[i][0] = h_scetawid_bkg_EB[i]   ;
     plots_bkg_EB[i][1] = h_scphiwid_bkg_EB[i]   ;
     plots_bkg_EB[i][2] = h_sEtaEtaPhot_bkg_EB[i];
     plots_bkg_EB[i][3] = h_sEtaPhiPhot_bkg_EB[i];
     plots_bkg_EB[i][4] = h_s4RatioPhot_bkg_EB[i];
     plots_bkg_EB[i][5] = h_r9Phot_bkg_EB[i]     ;
     plots_bkg_EB[i][6] = h_etascPhot_bkg_EB[i]  ;
     plots_bkg_EB[i][7] = h_rhoAllJets_bkg_EB[i] ;
     plots_bkg_EB[i][8] = h_rr_bkg_EB[i]         ;
     plots_bkg_EB[i][9] = h_lambdaRatio_bkg_EB[i];
     		       		    
     plots_bkg_EE[i][0] = h_scetawid_bkg_EE[i]   ;
     plots_bkg_EE[i][1] = h_scphiwid_bkg_EE[i]   ;
     plots_bkg_EE[i][2] = h_sEtaEtaPhot_bkg_EE[i];
     plots_bkg_EE[i][3] = h_sEtaPhiPhot_bkg_EE[i];
     plots_bkg_EE[i][4] = h_s4RatioPhot_bkg_EE[i];
     plots_bkg_EE[i][5] = h_r9Phot_bkg_EE[i]     ;
     plots_bkg_EE[i][6] = h_etascPhot_bkg_EE[i]  ;
     plots_bkg_EE[i][7] = h_rhoAllJets_bkg_EE[i] ;
     plots_bkg_EE[i][8] = h_rr_bkg_EE[i]         ;
     plots_bkg_EE[i][9] = h_lambdaRatio_bkg_EE[i];


     
   }
  

  //filling histograms
  std::cout << " ++++++++++++++ MC ++++++++++++++++" << std::endl;
  //  char name[100];
  for (int i=0; i<2; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events" <<  endl;  
    if(int_exp_2012>0) {
      mc_2012_fill[i]->Loop(plots_sig_EB[i], plots_sig_EE[i], plots_bkg_EB[i], plots_bkg_EE[i], h_isMatchedPhot[i], h_PromptPhot[i], h_FakePhot[i]);
    }
    
  }
  
  // scale mc to equivalent lumi 
  for (int i_file=0; i_file<2; i_file++){
    for (int j_plot=0; j_plot<10; j_plot++){
      if(int_exp_2012>0) {
	plots_sig_EB[i_file][j_plot]->Scale(scale_mc_2012[i_file]);  
	plots_sig_EE[i_file][j_plot]->Scale(scale_mc_2012[i_file]);  
	plots_bkg_EB[i_file][j_plot]->Scale(scale_mc_2012[i_file]);  
	plots_bkg_EE[i_file][j_plot]->Scale(scale_mc_2012[i_file]);
      }
    }
    if(int_exp_2012>0) {
      h_PromptPhot[i_file]  ->Scale(scale_mc_2012[i_file]);
      h_FakePhot[i_file]    ->Scale(scale_mc_2012[i_file]);  
      h_isMatchedPhot[i_file]->Scale(scale_mc_2012[i_file]);
    }
  }
 

  //sum etaSC barrel + endcap
  for (int i_file=0; i_file<2; i_file++){
    output_file[i_file]->cd();
    TH1F *h_etaSC_sig,  *h_etaSC_bkg;
    h_etaSC_sig = (TH1F*)plots_sig_EB[i_file][6]->Clone("h_etaSC_sig");
    h_etaSC_sig->SetTitle("h_etaSC_sig");
    h_etaSC_sig->Add(plots_sig_EE[i_file][6]);

    h_etaSC_bkg = (TH1F*)plots_bkg_EB[i_file][6]->Clone("h_etaSC_bkg");
    h_etaSC_bkg->SetTitle("h_etaSC_bkg");
    h_etaSC_bkg->Add(plots_bkg_EE[i_file][6]);

  }

  
  for (int i_file=0; i_file<2; i_file++){
    output_file[i_file]->Write();
    output_file[i_file]->Close();  
  }
  
}
