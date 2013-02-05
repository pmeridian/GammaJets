#include <TTree.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <TLorentzVector.h>
#include <TAttLine.h>
#include <TAttFill.h>
#include <THStack.h>

void makePlot() {

  TFile* file_input[2];
  file_input[0] = new TFile("analysis_singlegamma_gjet20to40.root", "READ");
  file_input[1] = new TFile("analysis_singlegamma_gjet40.root", "READ");
  
  TFile* file_output = new TFile("plots_MVAvar.root", "RECREATE");

  TH1F* h_etaSC_sig   ;    
  TH1F* h_etaSC_bkg   ;    

  TH1F* h_scetawid_sig_EB    ;
  TH1F* h_scphiwid_sig_EB    ;
  TH1F* h_sEtaEtaPhot_sig_EB ;  
  TH1F* h_sEtaPhiPhot_sig_EB ;  
  TH1F* h_s4RatioPhot_sig_EB ;  
  TH1F* h_r9Phot_sig_EB      ;
  TH1F* h_etascPhot_sig_EB   ;
  TH1F* h_rhoAllJets_sig_EB  ; 
  TH1F* h_rr_sig_EB          ;
  TH1F* h_lambdaRatio_sig_EB ;
  
  TH1F* h_scetawid_sig_EE    ;
  TH1F* h_scphiwid_sig_EE    ;
  TH1F* h_sEtaEtaPhot_sig_EE ;  
  TH1F* h_sEtaPhiPhot_sig_EE ;  
  TH1F* h_s4RatioPhot_sig_EE ;  
  TH1F* h_r9Phot_sig_EE      ;
  TH1F* h_etascPhot_sig_EE   ;
  TH1F* h_rhoAllJets_sig_EE  ; 
  TH1F* h_rr_sig_EE          ;
  TH1F* h_lambdaRatio_sig_EE ;  

  TH1F* h_scetawid_bkg_EB     ;  
  TH1F* h_scphiwid_bkg_EB     ;  
  TH1F* h_sEtaEtaPhot_bkg_EB  ;     
  TH1F* h_sEtaPhiPhot_bkg_EB  ;     
  TH1F* h_s4RatioPhot_bkg_EB  ;     
  TH1F* h_r9Phot_bkg_EB       ;
  TH1F* h_etascPhot_bkg_EB    ;   
  TH1F* h_rhoAllJets_bkg_EB   ;    
  TH1F* h_rr_bkg_EB           ;
  TH1F* h_lambdaRatio_bkg_EB  ;  

  TH1F* h_scetawid_bkg_EE     ;  
  TH1F* h_scphiwid_bkg_EE     ;  
  TH1F* h_sEtaEtaPhot_bkg_EE  ;     
  TH1F* h_sEtaPhiPhot_bkg_EE  ;     
  TH1F* h_s4RatioPhot_bkg_EE  ;     
  TH1F* h_r9Phot_bkg_EE       ;
  TH1F* h_etascPhot_bkg_EE    ;   
  TH1F* h_rhoAllJets_bkg_EE   ;    
  TH1F* h_rr_bkg_EE           ;
  TH1F* h_lambdaRatio_bkg_EE  ;    

  file_output->cd();
    

  h_etaSC_sig     = ((TH1F*)file_input[0]->Get("h_etaSC_sig"));      
  h_etaSC_bkg     = ((TH1F*)file_input[0]->Get("h_etaSC_bkg"));      

  h_scetawid_sig_EB         = ((TH1F*)file_input[0]->Get("h_scetawid_sig_EB"));      
  h_scphiwid_sig_EB         = ((TH1F*)file_input[0]->Get("h_scphiwid_sig_EB"));      
  h_sEtaEtaPhot_sig_EB      = ((TH1F*)file_input[0]->Get("h_sEtaEtaPhot_sig_EB"));   
  h_sEtaPhiPhot_sig_EB      = ((TH1F*)file_input[0]->Get("h_sEtaPhiPhot_sig_EB"));   
  h_s4RatioPhot_sig_EB      = ((TH1F*)file_input[0]->Get("h_s4RatioPhot_sig_EB"));   
  h_r9Phot_sig_EB           = ((TH1F*)file_input[0]->Get("h_r9Phot_sig_EB"));        
  h_etascPhot_sig_EB        = ((TH1F*)file_input[0]->Get("h_etascPhot_sig_EB"));     
  h_rhoAllJets_sig_EB       = ((TH1F*)file_input[0]->Get("h_rhoAllJets_sig_EB"));    
  h_rr_sig_EB               = ((TH1F*)file_input[0]->Get("h_rr_sig_EB"));            
  h_lambdaRatio_sig_EB      = ((TH1F*)file_input[0]->Get("h_lambdaRatio_sig_EB"));               
 		      
  h_scetawid_sig_EE         = ((TH1F*)file_input[0]->Get("h_scetawid_sig_EE"));      
  h_scphiwid_sig_EE         = ((TH1F*)file_input[0]->Get("h_scphiwid_sig_EE"));      
  h_sEtaEtaPhot_sig_EE      = ((TH1F*)file_input[0]->Get("h_sEtaEtaPhot_sig_EE"));   
  h_sEtaPhiPhot_sig_EE      = ((TH1F*)file_input[0]->Get("h_sEtaPhiPhot_sig_EE"));   
  h_s4RatioPhot_sig_EE      = ((TH1F*)file_input[0]->Get("h_s4RatioPhot_sig_EE"));   
  h_r9Phot_sig_EE           = ((TH1F*)file_input[0]->Get("h_r9Phot_sig_EE"));        
  h_etascPhot_sig_EE        = ((TH1F*)file_input[0]->Get("h_etascPhot_sig_EE"));     
  h_rhoAllJets_sig_EE       = ((TH1F*)file_input[0]->Get("h_rhoAllJets_sig_EE"));    
  h_rr_sig_EE               = ((TH1F*)file_input[0]->Get("h_rr_sig_EE"));            
  h_lambdaRatio_sig_EE      = ((TH1F*)file_input[0]->Get("h_lambdaRatio_sig_EE"));                
   		      
  h_scetawid_bkg_EB       = ((TH1F*)file_input[0]->Get("h_scetawid_bkg_EB"));   
  h_scphiwid_bkg_EB       = ((TH1F*)file_input[0]->Get("h_scphiwid_bkg_EB"));   
  h_sEtaEtaPhot_bkg_EB    = ((TH1F*)file_input[0]->Get("h_sEtaEtaPhot_bkg_EB"));
  h_sEtaPhiPhot_bkg_EB    = ((TH1F*)file_input[0]->Get("h_sEtaPhiPhot_bkg_EB"));
  h_s4RatioPhot_bkg_EB    = ((TH1F*)file_input[0]->Get("h_s4RatioPhot_bkg_EB"));
  h_r9Phot_bkg_EB         = ((TH1F*)file_input[0]->Get("h_r9Phot_bkg_EB"));     
  h_etascPhot_bkg_EB      = ((TH1F*)file_input[0]->Get("h_etascPhot_bkg_EB"));  
  h_rhoAllJets_bkg_EB     = ((TH1F*)file_input[0]->Get("h_rhoAllJets_bkg_EB")); 
  h_rr_bkg_EB             = ((TH1F*)file_input[0]->Get("h_rr_bkg_EB"));         
  h_lambdaRatio_bkg_EB    = ((TH1F*)file_input[0]->Get("h_lambdaRatio_bkg_EB"));                  
 		      
  h_scetawid_bkg_EE       = ((TH1F*)file_input[0]->Get("h_scetawid_bkg_EE"));   
  h_scphiwid_bkg_EE       = ((TH1F*)file_input[0]->Get("h_scphiwid_bkg_EE"));   
  h_sEtaEtaPhot_bkg_EE    = ((TH1F*)file_input[0]->Get("h_sEtaEtaPhot_bkg_EE"));
  h_sEtaPhiPhot_bkg_EE    = ((TH1F*)file_input[0]->Get("h_sEtaPhiPhot_bkg_EE"));
  h_s4RatioPhot_bkg_EE    = ((TH1F*)file_input[0]->Get("h_s4RatioPhot_bkg_EE"));
  h_r9Phot_bkg_EE         = ((TH1F*)file_input[0]->Get("h_r9Phot_bkg_EE"));     
  h_etascPhot_bkg_EE      = ((TH1F*)file_input[0]->Get("h_etascPhot_bkg_EE"));  
  h_rhoAllJets_bkg_EE     = ((TH1F*)file_input[0]->Get("h_rhoAllJets_bkg_EE")); 
  h_rr_bkg_EE             = ((TH1F*)file_input[0]->Get("h_rr_bkg_EE"));         
  h_lambdaRatio_bkg_EE    = ((TH1F*)file_input[0]->Get("h_lambdaRatio_bkg_EE"));               

  for (int i=1; i<2; i++) {
        
    h_etaSC_sig    ->Add((TH1F*)file_input[i]->Get("h_etaSC_sig"));    
    h_etaSC_bkg    ->Add((TH1F*)file_input[i]->Get("h_etaSC_bkg"));    

    h_scetawid_sig_EB    ->Add((TH1F*)file_input[i]->Get("h_scetawid_sig_EB"));    
    h_scphiwid_sig_EB    ->Add((TH1F*)file_input[i]->Get("h_scphiwid_sig_EB"));    
    h_sEtaEtaPhot_sig_EB ->Add((TH1F*)file_input[i]->Get("h_sEtaEtaPhot_sig_EB")); 
    h_sEtaPhiPhot_sig_EB ->Add((TH1F*)file_input[i]->Get("h_sEtaPhiPhot_sig_EB")); 
    h_s4RatioPhot_sig_EB ->Add((TH1F*)file_input[i]->Get("h_s4RatioPhot_sig_EB")); 
    h_r9Phot_sig_EB      ->Add((TH1F*)file_input[i]->Get("h_r9Phot_sig_EB"));      
    h_etascPhot_sig_EB   ->Add((TH1F*)file_input[i]->Get("h_etascPhot_sig_EB"));   
    h_rhoAllJets_sig_EB  ->Add((TH1F*)file_input[i]->Get("h_rhoAllJets_sig_EB"));  
    h_rr_sig_EB          ->Add((TH1F*)file_input[i]->Get("h_rr_sig_EB"));          
    h_lambdaRatio_sig_EB ->Add((TH1F*)file_input[i]->Get("h_lambdaRatio_sig_EB"));               
      		      	    										
    h_scetawid_sig_EE    ->Add((TH1F*)file_input[i]->Get("h_scetawid_sig_EE"));    
    h_scphiwid_sig_EE    ->Add((TH1F*)file_input[i]->Get("h_scphiwid_sig_EE"));    
    h_sEtaEtaPhot_sig_EE ->Add((TH1F*)file_input[i]->Get("h_sEtaEtaPhot_sig_EE")); 
    h_sEtaPhiPhot_sig_EE ->Add((TH1F*)file_input[i]->Get("h_sEtaPhiPhot_sig_EE")); 
    h_s4RatioPhot_sig_EE ->Add((TH1F*)file_input[i]->Get("h_s4RatioPhot_sig_EE")); 
    h_r9Phot_sig_EE      ->Add((TH1F*)file_input[i]->Get("h_r9Phot_sig_EE"));      
    h_etascPhot_sig_EE   ->Add((TH1F*)file_input[i]->Get("h_etascPhot_sig_EE"));   
    h_rhoAllJets_sig_EE  ->Add((TH1F*)file_input[i]->Get("h_rhoAllJets_sig_EE"));  
    h_rr_sig_EE          ->Add((TH1F*)file_input[i]->Get("h_rr_sig_EE"));          
    h_lambdaRatio_sig_EE ->Add((TH1F*)file_input[i]->Get("h_lambdaRatio_sig_EE"));               
      		      	    									
    h_scetawid_bkg_EB    ->Add((TH1F*)file_input[i]->Get("h_scetawid_bkg_EB"));   	
    h_scphiwid_bkg_EB    ->Add((TH1F*)file_input[i]->Get("h_scphiwid_bkg_EB"));   	
    h_sEtaEtaPhot_bkg_EB ->Add((TH1F*)file_input[i]->Get("h_sEtaEtaPhot_bkg_EB"));	
    h_sEtaPhiPhot_bkg_EB ->Add((TH1F*)file_input[i]->Get("h_sEtaPhiPhot_bkg_EB"));	
    h_s4RatioPhot_bkg_EB ->Add((TH1F*)file_input[i]->Get("h_s4RatioPhot_bkg_EB"));	
    h_r9Phot_bkg_EB      ->Add((TH1F*)file_input[i]->Get("h_r9Phot_bkg_EB"));     	
    h_etascPhot_bkg_EB   ->Add((TH1F*)file_input[i]->Get("h_etascPhot_bkg_EB"));  	
    h_rhoAllJets_bkg_EB  ->Add((TH1F*)file_input[i]->Get("h_rhoAllJets_bkg_EB")); 	
    h_rr_bkg_EB          ->Add((TH1F*)file_input[i]->Get("h_rr_bkg_EB"));         	
    h_lambdaRatio_bkg_EB ->Add((TH1F*)file_input[i]->Get("h_lambdaRatio_bkg_EB"));                     			
    										
    h_scetawid_bkg_EE    ->Add((TH1F*)file_input[i]->Get("h_scetawid_bkg_EE"));   	
    h_scphiwid_bkg_EE    ->Add((TH1F*)file_input[i]->Get("h_scphiwid_bkg_EE"));   	
    h_sEtaEtaPhot_bkg_EE ->Add((TH1F*)file_input[i]->Get("h_sEtaEtaPhot_bkg_EE"));	
    h_sEtaPhiPhot_bkg_EE ->Add((TH1F*)file_input[i]->Get("h_sEtaPhiPhot_bkg_EE"));	
    h_s4RatioPhot_bkg_EE ->Add((TH1F*)file_input[i]->Get("h_s4RatioPhot_bkg_EE"));	
    h_r9Phot_bkg_EE      ->Add((TH1F*)file_input[i]->Get("h_r9Phot_bkg_EE"));     	
    h_etascPhot_bkg_EE   ->Add((TH1F*)file_input[i]->Get("h_etascPhot_bkg_EE"));  	
    h_rhoAllJets_bkg_EE  ->Add((TH1F*)file_input[i]->Get("h_rhoAllJets_bkg_EE")); 	
    h_rr_bkg_EE          ->Add((TH1F*)file_input[i]->Get("h_rr_bkg_EE"));          
    h_lambdaRatio_bkg_EE ->Add((TH1F*)file_input[i]->Get("h_lambdaRatio_bkg_EE"));               

  }
  
  
  //normalize to 1
  double integral = 0.;

  integral = h_etaSC_sig->Integral();
  if (integral !=0) h_etaSC_sig->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_etaSC_bkg->Integral();
  if (integral !=0) h_etaSC_bkg->Scale(1./integral);
  else cout << "empty integral!" << endl; 

  //barrel
  integral = h_scetawid_sig_EB->Integral();
  if (integral !=0) h_scetawid_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_scphiwid_sig_EB->Integral();
  if (integral !=0) h_scphiwid_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaEtaPhot_sig_EB->Integral();
  if (integral !=0) h_sEtaEtaPhot_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaPhiPhot_sig_EB->Integral();
  if (integral !=0) h_sEtaPhiPhot_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
    integral = h_s4RatioPhot_sig_EB->Integral();
  if (integral !=0) h_s4RatioPhot_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_r9Phot_sig_EB->Integral();
  if (integral !=0) h_r9Phot_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_etascPhot_sig_EB->Integral();
  if (integral !=0) h_etascPhot_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rhoAllJets_sig_EB->Integral();
  if (integral !=0) h_rhoAllJets_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rr_sig_EB->Integral();
  if (integral !=0) h_rr_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_lambdaRatio_sig_EB->Integral();
  if (integral !=0) h_lambdaRatio_sig_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 


  integral = h_scetawid_bkg_EB->Integral();
  if (integral !=0) h_scetawid_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_scphiwid_bkg_EB->Integral();
  if (integral !=0) h_scphiwid_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaEtaPhot_bkg_EB->Integral();
  if (integral !=0) h_sEtaEtaPhot_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaPhiPhot_bkg_EB->Integral();
  if (integral !=0) h_sEtaPhiPhot_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_s4RatioPhot_bkg_EB->Integral();
  if (integral !=0) h_s4RatioPhot_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_r9Phot_bkg_EB->Integral();
  if (integral !=0) h_r9Phot_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_etascPhot_bkg_EB->Integral();
  if (integral !=0) h_etascPhot_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rhoAllJets_bkg_EB->Integral();
  if (integral !=0) h_rhoAllJets_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rr_bkg_EB->Integral();
  if (integral !=0) h_rr_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_lambdaRatio_bkg_EB->Integral();
  if (integral !=0) h_lambdaRatio_bkg_EB->Scale(1./integral);
  else cout << "empty integral!" << endl; 


  //endcap
  integral = h_scetawid_sig_EE->Integral();
  if (integral !=0) h_scetawid_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_scphiwid_sig_EE->Integral();
  if (integral !=0) h_scphiwid_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaEtaPhot_sig_EE->Integral();
  if (integral !=0) h_sEtaEtaPhot_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaPhiPhot_sig_EE->Integral();
  if (integral !=0) h_sEtaPhiPhot_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
    integral = h_s4RatioPhot_sig_EE->Integral();
  if (integral !=0) h_s4RatioPhot_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_r9Phot_sig_EE->Integral();
  if (integral !=0) h_r9Phot_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_etascPhot_sig_EE->Integral();
  if (integral !=0) h_etascPhot_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rhoAllJets_sig_EE->Integral();
  if (integral !=0) h_rhoAllJets_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rr_sig_EE->Integral();
  if (integral !=0) h_rr_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_lambdaRatio_sig_EE->Integral();
  if (integral !=0) h_lambdaRatio_sig_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 


  integral = h_scetawid_bkg_EE->Integral();
  if (integral !=0) h_scetawid_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_scphiwid_bkg_EE->Integral();
  if (integral !=0) h_scphiwid_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaEtaPhot_bkg_EE->Integral();
  if (integral !=0) h_sEtaEtaPhot_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_sEtaPhiPhot_bkg_EE->Integral();
  if (integral !=0) h_sEtaPhiPhot_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_s4RatioPhot_bkg_EE->Integral();
  if (integral !=0) h_s4RatioPhot_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_r9Phot_bkg_EE->Integral();
  if (integral !=0) h_r9Phot_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_etascPhot_bkg_EE->Integral();
  if (integral !=0) h_etascPhot_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rhoAllJets_bkg_EE->Integral();
  if (integral !=0) h_rhoAllJets_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_rr_bkg_EE->Integral();
  if (integral !=0) h_rr_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 
  integral = h_lambdaRatio_bkg_EE->Integral();
  if (integral !=0) h_lambdaRatio_bkg_EE->Scale(1./integral);
  else cout << "empty integral!" << endl; 

  //////////////

  //plot style

  h_etaSC_sig         ->SetLineColor(kAzure+1);
  h_scetawid_sig_EB   ->SetLineColor(kAzure+1);
  h_scphiwid_sig_EB   ->SetLineColor(kAzure+1);
  h_sEtaEtaPhot_sig_EB->SetLineColor(kAzure+1);
  h_sEtaPhiPhot_sig_EB->SetLineColor(kAzure+1);
  h_s4RatioPhot_sig_EB->SetLineColor(kAzure+1);
  h_r9Phot_sig_EB     ->SetLineColor(kAzure+1);
  h_etascPhot_sig_EB  ->SetLineColor(kAzure+1);
  h_rhoAllJets_sig_EB ->SetLineColor(kAzure+1);
  h_rr_sig_EB         ->SetLineColor(kAzure+1);
  h_lambdaRatio_sig_EB->SetLineColor(kAzure+1);  

  h_etaSC_sig         ->SetFillColor(kAzure+6);
  h_scetawid_sig_EB   ->SetFillColor(kAzure+6);
  h_scphiwid_sig_EB   ->SetFillColor(kAzure+6);
  h_sEtaEtaPhot_sig_EB->SetFillColor(kAzure+6);
  h_sEtaPhiPhot_sig_EB->SetFillColor(kAzure+6);
  h_s4RatioPhot_sig_EB->SetFillColor(kAzure+6);
  h_r9Phot_sig_EB     ->SetFillColor(kAzure+6);
  h_etascPhot_sig_EB  ->SetFillColor(kAzure+6);
  h_rhoAllJets_sig_EB ->SetFillColor(kAzure+6);
  h_rr_sig_EB         ->SetFillColor(kAzure+6);
  h_lambdaRatio_sig_EB->SetFillColor(kAzure+6);    

  h_etaSC_sig         ->SetFillStyle(3001);
  h_scetawid_sig_EB   ->SetFillStyle(3001);
  h_scphiwid_sig_EB   ->SetFillStyle(3001);
  h_sEtaEtaPhot_sig_EB->SetFillStyle(3001);
  h_sEtaPhiPhot_sig_EB->SetFillStyle(3001);
  h_s4RatioPhot_sig_EB->SetFillStyle(3001);
  h_r9Phot_sig_EB     ->SetFillStyle(3001);
  h_etascPhot_sig_EB  ->SetFillStyle(3001);
  h_rhoAllJets_sig_EB ->SetFillStyle(3001);
  h_rr_sig_EB         ->SetFillStyle(3001);
  h_lambdaRatio_sig_EB->SetFillStyle(3001);  

  h_etaSC_bkg         ->SetLineColor(kRed);
  h_scetawid_bkg_EB   ->SetLineColor(kRed);
  h_scphiwid_bkg_EB   ->SetLineColor(kRed);
  h_sEtaEtaPhot_bkg_EB->SetLineColor(kRed);
  h_sEtaPhiPhot_bkg_EB->SetLineColor(kRed);
  h_s4RatioPhot_bkg_EB->SetLineColor(kRed);
  h_r9Phot_bkg_EB     ->SetLineColor(kRed);
  h_etascPhot_bkg_EB  ->SetLineColor(kRed);
  h_rhoAllJets_bkg_EB ->SetLineColor(kRed);
  h_rr_bkg_EB         ->SetLineColor(kRed);
  h_lambdaRatio_bkg_EB->SetLineColor(kRed);    

  h_etaSC_bkg         ->SetFillColor(kRed);
  h_scetawid_bkg_EB   ->SetFillColor(kRed);
  h_scphiwid_bkg_EB   ->SetFillColor(kRed);
  h_sEtaEtaPhot_bkg_EB->SetFillColor(kRed);
  h_sEtaPhiPhot_bkg_EB->SetFillColor(kRed);
  h_s4RatioPhot_bkg_EB->SetFillColor(kRed);
  h_r9Phot_bkg_EB     ->SetFillColor(kRed);
  h_etascPhot_bkg_EB  ->SetFillColor(kRed);
  h_rhoAllJets_bkg_EB ->SetFillColor(kRed);
  h_rr_bkg_EB         ->SetFillColor(kRed);
  h_lambdaRatio_bkg_EB->SetFillColor(kRed);    

  h_etaSC_bkg         ->SetFillStyle(3005);
  h_scetawid_bkg_EB   ->SetFillStyle(3005);
  h_scphiwid_bkg_EB   ->SetFillStyle(3005);
  h_sEtaEtaPhot_bkg_EB->SetFillStyle(3005);
  h_sEtaPhiPhot_bkg_EB->SetFillStyle(3005);
  h_s4RatioPhot_bkg_EB->SetFillStyle(3005);
  h_r9Phot_bkg_EB     ->SetFillStyle(3005);
  h_etascPhot_bkg_EB  ->SetFillStyle(3005);
  h_rhoAllJets_bkg_EB ->SetFillStyle(3005);
  h_rr_bkg_EB         ->SetFillStyle(3005);
  h_lambdaRatio_bkg_EB->SetFillStyle(3005);  

  h_scetawid_sig_EE   ->SetLineColor(kAzure+1);
  h_scphiwid_sig_EE   ->SetLineColor(kAzure+1);
  h_sEtaEtaPhot_sig_EE->SetLineColor(kAzure+1);
  h_sEtaPhiPhot_sig_EE->SetLineColor(kAzure+1);
  h_s4RatioPhot_sig_EE->SetLineColor(kAzure+1);
  h_r9Phot_sig_EE     ->SetLineColor(kAzure+1);
  h_etascPhot_sig_EE  ->SetLineColor(kAzure+1);
  h_rhoAllJets_sig_EE ->SetLineColor(kAzure+1);
  h_rr_sig_EE         ->SetLineColor(kAzure+1);
  h_lambdaRatio_sig_EE->SetLineColor(kAzure+1);    

  h_scetawid_sig_EE   ->SetFillColor(kAzure+6);
  h_scphiwid_sig_EE   ->SetFillColor(kAzure+6);
  h_sEtaEtaPhot_sig_EE->SetFillColor(kAzure+6);
  h_sEtaPhiPhot_sig_EE->SetFillColor(kAzure+6);
  h_s4RatioPhot_sig_EE->SetFillColor(kAzure+6);
  h_r9Phot_sig_EE     ->SetFillColor(kAzure+6);
  h_etascPhot_sig_EE  ->SetFillColor(kAzure+6);
  h_rhoAllJets_sig_EE ->SetFillColor(kAzure+6);
  h_rr_sig_EE         ->SetFillColor(kAzure+6);
  h_lambdaRatio_sig_EE->SetFillColor(kAzure+6);    

  h_scetawid_sig_EE   ->SetFillStyle(3001);
  h_scphiwid_sig_EE   ->SetFillStyle(3001);
  h_sEtaEtaPhot_sig_EE->SetFillStyle(3001);
  h_sEtaPhiPhot_sig_EE->SetFillStyle(3001);
  h_s4RatioPhot_sig_EE->SetFillStyle(3001);
  h_r9Phot_sig_EE     ->SetFillStyle(3001);
  h_etascPhot_sig_EE  ->SetFillStyle(3001);
  h_rhoAllJets_sig_EE ->SetFillStyle(3001);
  h_rr_sig_EE         ->SetFillStyle(3001);
  h_lambdaRatio_sig_EE->SetFillStyle(3001);  

  h_scetawid_bkg_EE   ->SetLineColor(kRed);
  h_scphiwid_bkg_EE   ->SetLineColor(kRed);
  h_sEtaEtaPhot_bkg_EE->SetLineColor(kRed);
  h_sEtaPhiPhot_bkg_EE->SetLineColor(kRed);
  h_s4RatioPhot_bkg_EE->SetLineColor(kRed);
  h_r9Phot_bkg_EE     ->SetLineColor(kRed);
  h_etascPhot_bkg_EE  ->SetLineColor(kRed);
  h_rhoAllJets_bkg_EE ->SetLineColor(kRed);
  h_rr_bkg_EE         ->SetLineColor(kRed);
  h_lambdaRatio_bkg_EE->SetLineColor(kRed);    

  h_scetawid_bkg_EE   ->SetFillColor(kRed);
  h_scphiwid_bkg_EE   ->SetFillColor(kRed);
  h_sEtaEtaPhot_bkg_EE->SetFillColor(kRed);
  h_sEtaPhiPhot_bkg_EE->SetFillColor(kRed);
  h_s4RatioPhot_bkg_EE->SetFillColor(kRed);
  h_r9Phot_bkg_EE     ->SetFillColor(kRed);
  h_etascPhot_bkg_EE  ->SetFillColor(kRed);
  h_rhoAllJets_bkg_EE ->SetFillColor(kRed);
  h_rr_bkg_EE         ->SetFillColor(kRed);
  h_lambdaRatio_bkg_EE->SetFillColor(kRed);    

  h_scetawid_bkg_EE   ->SetFillStyle(3005);
  h_scphiwid_bkg_EE   ->SetFillStyle(3005);
  h_sEtaEtaPhot_bkg_EE->SetFillStyle(3005);
  h_sEtaPhiPhot_bkg_EE->SetFillStyle(3005);
  h_s4RatioPhot_bkg_EE->SetFillStyle(3005);
  h_r9Phot_bkg_EE     ->SetFillStyle(3005);
  h_etascPhot_bkg_EE  ->SetFillStyle(3005);
  h_rhoAllJets_bkg_EE ->SetFillStyle(3005);
  h_rr_bkg_EE         ->SetFillStyle(3005);
  h_lambdaRatio_bkg_EE->SetFillStyle(3005);    

  //range
  vector<double> maxbin0_EB, maxbin1_EB, maxbin2_EB, maxbin3_EB, maxbin4_EB, maxbin5_EB, maxbin6_EB, maxbin7_EB, maxbin8_EB, maxbin9_EB;
  vector<double> maxbin0_EE, maxbin1_EE, maxbin2_EE, maxbin3_EE, maxbin4_EE, maxbin5_EE, maxbin6_EE, maxbin7_EE, maxbin8_EE, maxbin9_EE;
  vector<double> maxbin_etasc;

  maxbin_etasc.push_back(h_etaSC_bkg   ->GetMaximum());
  maxbin_etasc.push_back(h_etaSC_sig   ->GetMaximum());

  maxbin0_EB.push_back(h_scetawid_bkg_EB   ->GetMaximum());
  maxbin0_EB.push_back(h_scetawid_sig_EB   ->GetMaximum());
  maxbin1_EB.push_back(h_scphiwid_bkg_EB   ->GetMaximum());
  maxbin1_EB.push_back(h_scphiwid_sig_EB   ->GetMaximum());
  maxbin2_EB.push_back(h_sEtaEtaPhot_bkg_EB->GetMaximum());
  maxbin2_EB.push_back(h_sEtaEtaPhot_sig_EB->GetMaximum());
  maxbin3_EB.push_back(h_sEtaPhiPhot_bkg_EB->GetMaximum());
  maxbin3_EB.push_back(h_sEtaPhiPhot_sig_EB->GetMaximum());
  maxbin4_EB.push_back(h_s4RatioPhot_bkg_EB->GetMaximum());
  maxbin4_EB.push_back(h_s4RatioPhot_sig_EB->GetMaximum());
  maxbin5_EB.push_back(h_r9Phot_bkg_EB     ->GetMaximum());
  maxbin5_EB.push_back(h_r9Phot_sig_EB     ->GetMaximum());
  maxbin6_EB.push_back(h_etascPhot_bkg_EB  ->GetMaximum());
  maxbin6_EB.push_back(h_etascPhot_sig_EB  ->GetMaximum());
  maxbin7_EB.push_back(h_rhoAllJets_bkg_EB ->GetMaximum());
  maxbin7_EB.push_back(h_rhoAllJets_sig_EB ->GetMaximum());
  maxbin8_EB.push_back(h_rr_bkg_EB         ->GetMaximum());
  maxbin8_EB.push_back(h_rr_sig_EB         ->GetMaximum());
  maxbin9_EB.push_back(h_lambdaRatio_sig_EB->GetMaximum());
  maxbin9_EB.push_back(h_lambdaRatio_bkg_EB->GetMaximum());

  maxbin0_EE.push_back(h_scetawid_bkg_EE   ->GetMaximum());
  maxbin0_EE.push_back(h_scetawid_sig_EE   ->GetMaximum());
  maxbin1_EE.push_back(h_scphiwid_bkg_EE   ->GetMaximum());
  maxbin1_EE.push_back(h_scphiwid_sig_EE   ->GetMaximum());
  maxbin2_EE.push_back(h_sEtaEtaPhot_bkg_EE->GetMaximum());
  maxbin2_EE.push_back(h_sEtaEtaPhot_sig_EE->GetMaximum());
  maxbin3_EE.push_back(h_sEtaPhiPhot_bkg_EE->GetMaximum());
  maxbin3_EE.push_back(h_sEtaPhiPhot_sig_EE->GetMaximum());
  maxbin4_EE.push_back(h_s4RatioPhot_bkg_EE->GetMaximum());
  maxbin4_EE.push_back(h_s4RatioPhot_sig_EE->GetMaximum());
  maxbin5_EE.push_back(h_r9Phot_bkg_EE     ->GetMaximum());
  maxbin5_EE.push_back(h_r9Phot_sig_EE     ->GetMaximum());
  maxbin6_EE.push_back(h_etascPhot_bkg_EE  ->GetMaximum());
  maxbin6_EE.push_back(h_etascPhot_sig_EE  ->GetMaximum());
  maxbin7_EE.push_back(h_rhoAllJets_bkg_EE ->GetMaximum());
  maxbin7_EE.push_back(h_rhoAllJets_sig_EE ->GetMaximum());
  maxbin8_EE.push_back(h_rr_bkg_EE         ->GetMaximum());
  maxbin8_EE.push_back(h_rr_sig_EE         ->GetMaximum());
  maxbin9_EE.push_back(h_lambdaRatio_sig_EE->GetMaximum());
  maxbin9_EE.push_back(h_lambdaRatio_bkg_EE->GetMaximum());
  

  std::sort( maxbin_etasc.begin(),              maxbin_etasc.end());
  double yRange_etasc     = maxbin_etasc.back() + 0.1*maxbin_etasc.back();

  std::sort( maxbin0_EB.begin(),              maxbin0_EB.end());
  double yRange0_EB     = maxbin0_EB.back() + 0.1*maxbin0_EB.back();
  std::sort( maxbin1_EB.begin(),	      maxbin1_EB.end());	  	     
  double yRange1_EB    	= maxbin1_EB.back() + 0.1*maxbin1_EB.back();
  std::sort( maxbin2_EB.begin(),	      maxbin2_EB.end());	  	     
  double yRange2_EB    	= maxbin2_EB.back() + 0.1*maxbin2_EB.back();
  std::sort( maxbin3_EB.begin(),	      maxbin3_EB.end());	  	     
  double yRange3_EB    	= maxbin3_EB.back() + 0.1*maxbin3_EB.back();
  std::sort( maxbin4_EB.begin(),	      maxbin4_EB.end());	  	     
  double yRange4_EB    	= maxbin4_EB.back() + 0.1*maxbin4_EB.back();
  std::sort( maxbin5_EB.begin(),	      maxbin5_EB.end());	  	     
  double yRange5_EB    	= maxbin5_EB.back() + 0.1*maxbin5_EB.back();
  std::sort( maxbin6_EB.begin(),	      maxbin6_EB.end());	  	     
  double yRange6_EB    	= maxbin6_EB.back() + 0.1*maxbin6_EB.back();
  std::sort( maxbin7_EB.begin(),	      maxbin7_EB.end());	  	     
  double yRange7_EB    	= maxbin7_EB.back() + 0.1*maxbin7_EB.back();
  std::sort( maxbin8_EB.begin(),	      maxbin8_EB.end());	  	     
  double yRange8_EB 	= maxbin8_EB.back() + 0.1*maxbin8_EB.back();
  std::sort( maxbin9_EB.begin(),	      maxbin9_EB.end());	  	     
  double yRange9_EB 	= maxbin9_EB.back() + 0.1*maxbin9_EB.back();
			    				    
  std::sort( maxbin0_EE.begin(),              maxbin0_EE.end());
  double yRange0_EE     = maxbin0_EE.back() + 0.1*maxbin0_EE.back();
  std::sort( maxbin1_EE.begin(),	      maxbin1_EE.end());	  	     
  double yRange1_EE    	= maxbin1_EE.back() + 0.1*maxbin1_EE.back();
  std::sort( maxbin2_EE.begin(),	      maxbin2_EE.end());	  	     
  double yRange2_EE    	= maxbin2_EE.back() + 0.1*maxbin2_EE.back();
  std::sort( maxbin3_EE.begin(),	      maxbin3_EE.end());	  	     
  double yRange3_EE    	= maxbin3_EE.back() + 0.1*maxbin3_EE.back();
  std::sort( maxbin4_EE.begin(),	      maxbin4_EE.end());	  	     
  double yRange4_EE    	= maxbin4_EE.back() + 0.1*maxbin4_EE.back();
  std::sort( maxbin5_EE.begin(),	      maxbin5_EE.end());	  	     
  double yRange5_EE    	= maxbin5_EE.back() + 0.1*maxbin5_EE.back();
  std::sort( maxbin6_EE.begin(),	      maxbin6_EE.end());	  	     
  double yRange6_EE    	= maxbin6_EE.back() + 0.1*maxbin6_EE.back();
  std::sort( maxbin7_EE.begin(),	      maxbin7_EE.end());	  	     
  double yRange7_EE    	= maxbin7_EE.back() + 0.1*maxbin7_EE.back();
  std::sort( maxbin8_EE.begin(),	      maxbin8_EE.end());	  	     
  double yRange8_EE 	= maxbin8_EE.back() + 0.1*maxbin8_EE.back();
  std::sort( maxbin9_EE.begin(),	      maxbin9_EE.end());	  	     
  double yRange9_EE 	= maxbin9_EE.back() + 0.1*maxbin9_EE.back();
			    				    

  h_etaSC_sig   ->SetMaximum(yRange_etasc);

  h_scetawid_sig_EB   ->SetMaximum(yRange0_EB);
  h_scphiwid_sig_EB   ->SetMaximum(yRange1_EB);
  h_sEtaEtaPhot_sig_EB->SetMaximum(yRange2_EB);
  h_sEtaPhiPhot_sig_EB->SetMaximum(yRange3_EB);
  h_s4RatioPhot_sig_EB->SetMaximum(yRange4_EB);
  h_r9Phot_sig_EB     ->SetMaximum(yRange5_EB);
  h_etascPhot_sig_EB  ->SetMaximum(yRange6_EB);
  h_rhoAllJets_sig_EB ->SetMaximum(yRange7_EB);
  h_rr_sig_EB         ->SetMaximum(yRange8_EB);
  h_lambdaRatio_sig_EB->SetMaximum(yRange9_EB);

  h_scetawid_sig_EE   ->SetMaximum(yRange0_EE);
  h_scphiwid_sig_EE   ->SetMaximum(yRange1_EE);
  h_sEtaEtaPhot_sig_EE->SetMaximum(yRange2_EE);
  h_sEtaPhiPhot_sig_EE->SetMaximum(yRange3_EE);
  h_s4RatioPhot_sig_EE->SetMaximum(yRange4_EE);
  h_r9Phot_sig_EE     ->SetMaximum(yRange5_EE);
  h_etascPhot_sig_EE  ->SetMaximum(yRange6_EE);
  h_rhoAllJets_sig_EE ->SetMaximum(yRange7_EE);
  h_rr_sig_EE         ->SetMaximum(yRange8_EE);
  h_lambdaRatio_sig_EE->SetMaximum(yRange9_EE);

  /*
  h_scetawid_sig_EB   ->Write();
  h_scphiwid_sig_EB   ->Write();
  h_sEtaEtaPhot_sig_EB->Write();
  h_sEtaPhiPhot_sig_EB->Write();
  h_s4RatioPhot_sig_EB->Write();
  h_r9Phot_sig_EB     ->Write();
  h_etascPhot_sig_EB  ->Write();
  h_rhoAllJets_sig_EB ->Write();
  h_rr_sig_EB         ->Write();


  h_scetawid_bkg_EB   ->Write();
  h_scphiwid_bkg_EB   ->Write();
  h_sEtaEtaPhot_bkg_EB->Write();
  h_sEtaPhiPhot_bkg_EB->Write();
  h_s4RatioPhot_bkg_EB->Write();
  h_r9Phot_bkg_EB     ->Write();
  h_etascPhot_bkg_EB  ->Write();
  h_rhoAllJets_bkg_EB ->Write();
  h_rr_bkg_EB         ->Write();


  h_scetawid_sig_EE   ->Write();
  h_scphiwid_sig_EE   ->Write();
  h_sEtaEtaPhot_sig_EE->Write();
  h_sEtaPhiPhot_sig_EE->Write();
  h_s4RatioPhot_sig_EE->Write();
  h_r9Phot_sig_EE     ->Write();
  h_etascPhot_sig_EE  ->Write();
  h_rhoAllJets_sig_EE ->Write();
  h_rr_sig_EE         ->Write();


  h_scetawid_bkg_EE   ->Write();
  h_scphiwid_bkg_EE   ->Write();
  h_sEtaEtaPhot_bkg_EE->Write();
  h_sEtaPhiPhot_bkg_EE->Write();
  h_s4RatioPhot_bkg_EE->Write();
  h_r9Phot_bkg_EE     ->Write();
  h_etascPhot_bkg_EE  ->Write();
  h_rhoAllJets_bkg_EE ->Write();
  h_rr_bkg_EE         ->Write();
  */

  TCanvas* c_etaSC    = new TCanvas("c_etaSC", "", 1);

  TCanvas* c_scetawid_EB    = new TCanvas("c_scetawid_EB", "", 1);
  TCanvas* c_scphiwid_EB    = new TCanvas("c_scphiwid_EB", "", 1);
  TCanvas* c_sEtaEtaPhot_EB = new TCanvas("c_sEtaEtaPhot_EB", "", 1);
  TCanvas* c_sEtaPhiPhot_EB = new TCanvas("c_sEtaPhiPhot_EB", "", 1);
  TCanvas* c_s4RatioPhot_EB = new TCanvas("c_s4RatioPhot_EB", "", 1);
  TCanvas* c_r9Phot_EB      = new TCanvas("c_r9Phot_EB", "", 1);
  TCanvas* c_etascPhot_EB   = new TCanvas("c_etascPhot_EB", "", 1);
  TCanvas* c_rhoAllJets_EB  = new TCanvas("c_rhoAllJets_EB", "", 1);
  TCanvas* c_rr_EB          = new TCanvas("c_rr_EB", "", 1);
  TCanvas* c_lambdaRatio_EB  = new TCanvas("c_lambdaRatio_EB", "", 1);

  TCanvas* c_scetawid_EE    = new TCanvas("c_scetawid_EE", "", 1);
  TCanvas* c_scphiwid_EE    = new TCanvas("c_scphiwid_EE", "", 1);
  TCanvas* c_sEtaEtaPhot_EE = new TCanvas("c_sEtaEtaPhot_EE", "", 1);
  TCanvas* c_sEtaPhiPhot_EE = new TCanvas("c_sEtaPhiPhot_EE", "", 1);
  TCanvas* c_s4RatioPhot_EE = new TCanvas("c_s4RatioPhot_EE", "", 1);
  TCanvas* c_r9Phot_EE      = new TCanvas("c_r9Phot_EE", "", 1);
  TCanvas* c_etascPhot_EE   = new TCanvas("c_etascPhot_EE", "", 1);
  TCanvas* c_rhoAllJets_EE  = new TCanvas("c_rhoAllJets_EE", "", 1);
  TCanvas* c_rr_EE          = new TCanvas("c_rr_EE", "", 1);
  TCanvas* c_lambdaRatio_EE  = new TCanvas("c_lambdaRatio_EE", "", 1);
    
  //legend
  TLegend* leg = new TLegend(0.5, 0.7, 0.85, 0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  //  leg->SetTextSize(0.03)
  leg->AddEntry(h_rr_sig_EB, "signal (#gamma matched)", "f" );
  leg->AddEntry(h_rr_bkg_EB, "background (#gamma unmatched)", "f" );
  


  string dir = "plots_MVAvar";

  c_etaSC->cd();
  h_etaSC_sig->Draw();
  h_etaSC_bkg->Draw("same");
  //leg->Draw();
  c_etaSC->Write();
  c_etaSC->SaveAs((dir+"/c_etaSC.png").c_str());
      
  //write output
  c_scetawid_EB->cd();
  h_scetawid_sig_EB->Draw();
  h_scetawid_bkg_EB->Draw("same");
  //leg->Draw();
  c_scetawid_EB->Write();
  c_scetawid_EB->SaveAs((dir+"/c_scetawid_EB.png").c_str());

  c_scphiwid_EB->cd();
  h_scphiwid_sig_EB->Draw();
  h_scphiwid_bkg_EB->Draw("same");
  //leg->Draw();  
  c_scphiwid_EB->Write();
  c_scphiwid_EB->SaveAs((dir+"/c_scphiwid_EB.png").c_str());

  c_sEtaEtaPhot_EB->cd();
  h_sEtaEtaPhot_sig_EB->Draw();
  h_sEtaEtaPhot_bkg_EB->Draw("same");
  //leg->Draw();
  c_sEtaEtaPhot_EB->Write();
  c_sEtaEtaPhot_EB->SaveAs((dir+"/c_sEtaEtaPhot_EB.png").c_str());

  
  c_sEtaPhiPhot_EB->cd();
  h_sEtaPhiPhot_sig_EB->Draw();
  h_sEtaPhiPhot_bkg_EB->Draw("same");
  //leg->Draw();
  c_sEtaPhiPhot_EB->Write();
  c_sEtaPhiPhot_EB->SaveAs((dir+"/c_sEtaPhiPhot_EB.png").c_str());

  
  c_s4RatioPhot_EB->cd();
  h_s4RatioPhot_sig_EB->Draw();
  h_s4RatioPhot_bkg_EB->Draw("same");
  //leg->Draw();
  c_s4RatioPhot_EB->Write();
  c_s4RatioPhot_EB->SaveAs((dir+"/c_s4RatioPhot_EB.png").c_str());

  c_r9Phot_EB->cd();
  h_r9Phot_sig_EB->Draw();
  h_r9Phot_bkg_EB->Draw("same");
  //leg->Draw();
  c_r9Phot_EB->Write();
  c_r9Phot_EB->SaveAs((dir+"/c_r9Phot_EB.png").c_str());


  c_etascPhot_EB->cd();
  h_etascPhot_sig_EB->Draw();
  h_etascPhot_bkg_EB->Draw("same");
  //leg->Draw();
  c_etascPhot_EB->Write();
  c_etascPhot_EB->SaveAs((dir+"/c_etascPhot_EB.png").c_str());

  c_rhoAllJets_EB->cd();
  h_rhoAllJets_sig_EB->Draw();
  h_rhoAllJets_bkg_EB->Draw("same");
  //leg->Draw();
  c_rhoAllJets_EB->Write();
  c_rhoAllJets_EB->SaveAs((dir+"/c_rhoAllJets_EB.png").c_str());

  c_rr_EB->cd();
  h_rr_sig_EB->Draw();
  h_rr_bkg_EB->Draw("same");
  //leg->Draw();
  c_rr_EB->Write();
  c_rr_EB->SaveAs((dir+"/c_rr_EB.png").c_str());

  c_lambdaRatio_EB->cd();
  h_lambdaRatio_sig_EB->Draw();
  h_lambdaRatio_bkg_EB->Draw("same");
  //leg->Draw();
  c_lambdaRatio_EB->Write();
  c_lambdaRatio_EB->SaveAs((dir+"/c_lambdaRatio_EB.png").c_str());


  c_scetawid_EE->cd();
  h_scetawid_sig_EE->Draw();
  h_scetawid_bkg_EE->Draw("same");
  //leg->Draw();
  c_scetawid_EE->Write();
  c_scetawid_EE->SaveAs((dir+"/c_scetawid_EE.png").c_str());


  c_scphiwid_EE->cd();
  h_scphiwid_sig_EE->Draw();
  h_scphiwid_bkg_EE->Draw("same");
  //leg->Draw();  
  c_scphiwid_EE->Write();
  c_scphiwid_EE->SaveAs((dir+"/c_scphiwid_EE.png").c_str());

  c_sEtaEtaPhot_EE->cd();
  h_sEtaEtaPhot_sig_EE->Draw();
  h_sEtaEtaPhot_bkg_EE->Draw("same");
  //leg->Draw();
  c_sEtaEtaPhot_EE->Write();
  c_sEtaEtaPhot_EE->SaveAs((dir+"/c_sEtaEtaPhot_EE.png").c_str());

  
  c_sEtaPhiPhot_EE->cd();
  h_sEtaPhiPhot_sig_EE->Draw();
  h_sEtaPhiPhot_bkg_EE->Draw("same");
  //leg->Draw();
  c_sEtaPhiPhot_EE->Write();
  c_sEtaPhiPhot_EE->SaveAs((dir+"/c_sEtaPhiPhot_EE.png").c_str());

  
  c_s4RatioPhot_EE->cd();
  h_s4RatioPhot_sig_EE->Draw();
  h_s4RatioPhot_bkg_EE->Draw("same");
  //leg->Draw();
  c_s4RatioPhot_EE->Write();
  c_s4RatioPhot_EE->SaveAs((dir+"/c_s4RatioPhot_EE.png").c_str());

  c_r9Phot_EE->cd();
  h_r9Phot_sig_EE->Draw();
  h_r9Phot_bkg_EE->Draw("same");
  //leg->Draw();
  c_r9Phot_EE->Write();
  c_r9Phot_EE->SaveAs((dir+"/c_r9Phot_EE.png").c_str());


  c_etascPhot_EE->cd();
  h_etascPhot_sig_EE->Draw();
  h_etascPhot_bkg_EE->Draw("same");
  //leg->Draw();
  c_etascPhot_EE->Write();
  c_etascPhot_EE->SaveAs((dir+"/c_etascPhot_EE.png").c_str());

  c_rhoAllJets_EE->cd();
  h_rhoAllJets_sig_EE->Draw();
  h_rhoAllJets_bkg_EE->Draw("same");
  //leg->Draw();
  c_rhoAllJets_EE->Write();
  c_rhoAllJets_EE->SaveAs((dir+"/c_rhoAllJets_EE.png").c_str());

  c_rr_EE->cd();
  h_rr_sig_EE->Draw();
  h_rr_bkg_EE->Draw("same");
  //leg->Draw();
  c_rr_EE->Write();
  c_rr_EE->SaveAs((dir+"/c_rr_EE.png").c_str());

  c_lambdaRatio_EE->cd();
  h_lambdaRatio_sig_EE->Draw();
  h_lambdaRatio_bkg_EE->Draw("same");
  //leg->Draw();
  c_lambdaRatio_EE->Write();
  c_lambdaRatio_EE->SaveAs((dir+"/c_lambdaRatio_EE.png").c_str());


  c_rr_EB->Close();
  c_rhoAllJets_EB->Close();
  c_etascPhot_EB->Close();
  c_r9Phot_EB->Close();
  c_s4RatioPhot_EB->Close();
  c_sEtaEtaPhot_EB->Close();
  c_scetawid_EB->Close();
  c_scphiwid_EB->Close();
  c_sEtaPhiPhot_EB->Close();
  c_lambdaRatio_EB->Close();

  c_rr_EE->Close();
  c_rhoAllJets_EE->Close();
  c_etascPhot_EE->Close();
  c_r9Phot_EE->Close();
  c_s4RatioPhot_EE->Close();
  c_sEtaEtaPhot_EE->Close();
  c_scetawid_EE->Close();
  c_scphiwid_EE->Close();
  c_sEtaPhiPhot_EE->Close();
  c_lambdaRatio_EE->Close();

  file_output->Close();

}
