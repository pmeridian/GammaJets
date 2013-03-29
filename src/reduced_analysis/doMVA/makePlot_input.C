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

void makePlot_input() {

  TFile* fileinput[2];
  std::cout<<"flag1"<<std::endl;
  fileinput[0]  = new TFile("TMVAoutput_EB_chi2.root", "READ");
  fileinput[1]  = new TFile("TMVAoutput_EB_chi2.root", "READ"); 
  std::cout<<"flag1"<<std::endl;
  TH1F *h_etascPhot_S[2], *h_ptPhot_S[2],  *h_sEtaEta_S[2], *h_sEtaPhi_S[2], *h_etaWidth_S[2], *h_phiWidth_S[2], *h_r9_S[2], *h_s4_S[2], *h_chi2_S[2];
  TH1F *h_etascPhot_B[2], *h_ptPhot_B[2],  *h_sEtaEta_B[2], *h_sEtaPhi_B[2], *h_etaWidth_B[2], *h_phiWidth_B[2], *h_r9_B[2], *h_s4_B[2],  *h_chi2_B[2];
  TH1F *h_rrPreshower_S,  *h_rrPreshower_B;
  //  TCanvas*  c_etascPhot[2], c_ptPhot[2], c_sEtaEta[2], c_sEtaPhi[2], c_etaWidth[2], c_phiWidth[2], c_r9[2], c_s4[2];       

  /*  h_rrPreshower_S = ((TH1F*)fileinput[1]->Get("InputVariables_Id/rr_presel__Signal_Id"));
  h_rrPreshower_B = ((TH1F*)fileinput[1]->Get("InputVariables_Id/rr_presel__Background_Id"));

  h_rrPreshower_S    ->SetLineColor(kAzure+1); 
  h_rrPreshower_S    ->SetFillColor(kAzure+6); 
  h_rrPreshower_S    ->SetFillStyle(3001); 
  h_rrPreshower_B    ->SetLineColor(kRed); 
  h_rrPreshower_B    ->SetFillColor(kRed); 
  h_rrPreshower_B    ->SetFillStyle(3004); */
  std::cout<<"flag1"<<std::endl;
  for (int i=0; i<2; i++){
    h_etascPhot_S[i] =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/etascPhot_presel__Signal_Id"));
    h_ptPhot_S[i]    =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/ptPhot_presel__Signal_Id"));
    h_sEtaEta_S[i]   =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/sEtaEtaPhot_presel__Signal_Id"));
    h_sEtaPhi_S[i]   =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/sEtaPhiPhot_presel__Signal_Id"));
    h_etaWidth_S[i]  =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/pid_scetawid_presel__Signal_Id"));
    h_phiWidth_S[i]  =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/pid_scphiwid_presel__Signal_Id"));
    h_r9_S[i]        =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/r9Phot_presel__Signal_Id"));
    h_s4_S[i]        =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/s4RatioPhot_presel__Signal_Id"));
    std::cout<<"flag2"<<std::endl;
    h_chi2_S[i]      =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/chi2timePhot_presel_D_chi2NDFtimePhot_presel__Signal_Id"));


    h_etascPhot_B[i]  =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/etascPhot_presel__Background_Id"));
    h_ptPhot_B[i]     =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/ptPhot_presel__Background_Id"));
    h_sEtaEta_B[i]    =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/sEtaEtaPhot_presel__Background_Id"));
    h_sEtaPhi_B[i]    =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/sEtaPhiPhot_presel__Background_Id"));
    h_etaWidth_B[i]   =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/pid_scetawid_presel__Background_Id"));
    h_phiWidth_B[i]   =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/pid_scphiwid_presel__Background_Id"));
    h_r9_B[i]         =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/r9Phot_presel__Background_Id"));
    h_s4_B[i]         =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/s4RatioPhot_presel__Background_Id"));
    h_chi2_B[i]      =  ((TH1F*)fileinput[i]->Get("InputVariables_Id/chi2timePhot_presel_D_chi2NDFtimePhot_presel__Background_Id"));
    
    h_etascPhot_S[i]   ->SetLineColor(kAzure+1);
    h_ptPhot_S[i]      ->SetLineColor(kAzure+1);
    h_sEtaEta_S[i]     ->SetLineColor(kAzure+1);
    h_sEtaPhi_S[i]     ->SetLineColor(kAzure+1);
    h_etaWidth_S[i]    ->SetLineColor(kAzure+1);
    h_phiWidth_S[i]    ->SetLineColor(kAzure+1);
    h_r9_S[i]          ->SetLineColor(kAzure+1);
    h_s4_S[i]          ->SetLineColor(kAzure+1);
    h_chi2_S[i]         ->SetLineColor(kAzure+1);

    
    h_etascPhot_S[i]   ->SetFillColor(kAzure+6);
    h_ptPhot_S[i]      ->SetFillColor(kAzure+6);
    h_sEtaEta_S[i]     ->SetFillColor(kAzure+6);
    h_sEtaPhi_S[i]     ->SetFillColor(kAzure+6);
    h_etaWidth_S[i]    ->SetFillColor(kAzure+6);
    h_phiWidth_S[i]    ->SetFillColor(kAzure+6);
    h_r9_S[i]          ->SetFillColor(kAzure+6);
    h_s4_S[i]          ->SetFillColor(kAzure+6);
    h_chi2_S[i]        ->SetFillColor(kAzure+6);
    
    h_etascPhot_S[i]    ->SetFillStyle(3001);
    h_ptPhot_S[i]       ->SetFillStyle(3001);
    h_sEtaEta_S[i]      ->SetFillStyle(3001);
    h_sEtaPhi_S[i]      ->SetFillStyle(3001);
    h_etaWidth_S[i]     ->SetFillStyle(3001);
    h_phiWidth_S[i]     ->SetFillStyle(3001);
    h_r9_S[i]           ->SetFillStyle(3001);
    h_s4_S[i]           ->SetFillStyle(3001);
    h_chi2_S[i]           ->SetFillStyle(3001);
    
    
    h_etascPhot_B[i]   ->SetLineColor(kRed);
    h_ptPhot_B[i]      ->SetLineColor(kRed);
    h_sEtaEta_B[i]     ->SetLineColor(kRed);
    h_sEtaPhi_B[i]     ->SetLineColor(kRed);
    h_etaWidth_B[i]    ->SetLineColor(kRed);
    h_phiWidth_B[i]    ->SetLineColor(kRed);
    h_r9_B[i]          ->SetLineColor(kRed);
    h_s4_B[i]          ->SetLineColor(kRed);
    h_chi2_B[i]        ->SetLineColor(kRed);
    
    
    h_etascPhot_B[i]  ->SetFillColor(kRed);
    h_ptPhot_B[i]     ->SetFillColor(kRed);
    h_sEtaEta_B[i]    ->SetFillColor(kRed);
    h_sEtaPhi_B[i]    ->SetFillColor(kRed);
    h_etaWidth_B[i]   ->SetFillColor(kRed);
    h_phiWidth_B[i]   ->SetFillColor(kRed);
    h_r9_B[i]         ->SetFillColor(kRed);
    h_s4_B[i]         ->SetFillColor(kRed);
    h_chi2_B[i]       ->SetFillColor(kRed);
    
    
    h_etascPhot_B[i]  ->SetFillStyle(3004);
    h_ptPhot_B[i]     ->SetFillStyle(3004);
    h_sEtaEta_B[i]    ->SetFillStyle(3004);
    h_sEtaPhi_B[i]    ->SetFillStyle(3004);
    h_etaWidth_B[i]   ->SetFillStyle(3004);
    h_phiWidth_B[i]   ->SetFillStyle(3004);
    h_r9_B[i]         ->SetFillStyle(3004);
    h_s4_B[i]         ->SetFillStyle(3004);
    h_chi2_B[i]       ->SetFillStyle(3004);
    
  }


  std::cout<<"flag"<<std::endl;
  //normalization
  float integral(1);
  for(int i=0; i<2; i++) {
    integral = h_etascPhot_B[i] -> Integral();
    if (integral) h_etascPhot_B[i]->Scale(1./integral);
    integral = h_ptPhot_B[i]     -> Integral();
    if(integral) h_ptPhot_B[i]->Scale(1./integral);
    integral = h_sEtaEta_B[i]    -> Integral();
    if(integral) h_sEtaEta_B[i]->Scale(1./integral);
    integral = h_sEtaPhi_B[i]    -> Integral();
    if(integral) h_sEtaPhi_B[i] ->Scale(1./integral);
    integral = h_etaWidth_B[i]   -> Integral();
    if(integral) h_etaWidth_B[i]->Scale(1./integral);
    integral = h_phiWidth_B[i]   -> Integral();
    if(integral) h_phiWidth_B[i]->Scale(1./integral);
    integral = h_r9_B[i]         -> Integral();
    if(integral) h_r9_B[i] ->Scale(1./integral);
    integral = h_s4_B[i]         -> Integral();
    if(integral) h_s4_B[i]->Scale(1./integral);
    integral = h_chi2_B[i]         -> Integral();
    if(integral) h_chi2_B[i]->Scale(1./integral);
 
    integral = h_etascPhot_S[i] -> Integral();
    if (integral) h_etascPhot_S[i]->Scale(1./integral);
    integral = h_ptPhot_S[i]     -> Integral();
    if(integral) h_ptPhot_S[i]->Scale(1./integral);
    integral = h_sEtaEta_S[i]    -> Integral();
    if(integral) h_sEtaEta_S[i]->Scale(1./integral);
    integral = h_sEtaPhi_S[i]    -> Integral();
    if(integral) h_sEtaPhi_S[i] ->Scale(1./integral);
    integral = h_etaWidth_S[i]   -> Integral();
    if(integral) h_etaWidth_S[i]->Scale(1./integral);
    integral = h_phiWidth_S[i]   -> Integral();
    if(integral) h_phiWidth_S[i]->Scale(1./integral);
    integral = h_r9_S[i]         -> Integral();
    if(integral) h_r9_S[i] ->Scale(1./integral);
    integral = h_s4_S[i]         -> Integral();
    if(integral) h_s4_S[i]->Scale(1./integral);
    integral = h_chi2_S[i]         -> Integral();
    if(integral) h_chi2_S[i]->Scale(1./integral);

 }
  


  //range
  vector<double> maxbin0_EB, maxbin1_EB, maxbin2_EB, maxbin3_EB, maxbin4_EB, maxbin5_EB, maxbin6_EB, maxbin7_EB, maxbin8_EB, maxbin9_EB, maxbin10_EB;
  vector<double> maxbin0_EE, maxbin1_EE, maxbin2_EE, maxbin3_EE, maxbin4_EE, maxbin5_EE, maxbin6_EE, maxbin7_EE, maxbin8_EE, maxbin9_EE, maxbin10_EE;


  maxbin0_EB.push_back(h_etascPhot_S[0]->GetMaximum());
  maxbin0_EB.push_back(h_etascPhot_B[0]->GetMaximum());
  maxbin1_EB.push_back(h_ptPhot_S[0]    ->GetMaximum());
  maxbin1_EB.push_back(h_ptPhot_B[0]    ->GetMaximum());
  maxbin2_EB.push_back(h_sEtaEta_S[0]   ->GetMaximum());
  maxbin2_EB.push_back(h_sEtaEta_B[0]   ->GetMaximum());
  maxbin3_EB.push_back(h_sEtaPhi_S[0]   ->GetMaximum());
  maxbin3_EB.push_back(h_sEtaPhi_B[0]   ->GetMaximum());
  maxbin4_EB.push_back(h_etaWidth_S[0]  ->GetMaximum());
  maxbin4_EB.push_back(h_etaWidth_B[0]  ->GetMaximum());
  maxbin5_EB.push_back(h_phiWidth_S[0]  ->GetMaximum());
  maxbin5_EB.push_back(h_phiWidth_B[0]  ->GetMaximum());
  maxbin6_EB.push_back(h_r9_S[0]        ->GetMaximum());
  maxbin6_EB.push_back(h_r9_B[0]        ->GetMaximum());
  maxbin7_EB.push_back(h_s4_S[0]        ->GetMaximum());
  maxbin7_EB.push_back(h_s4_B[0]        ->GetMaximum());
  maxbin8_EB.push_back(h_chi2_S[0]        ->GetMaximum());
  maxbin8_EB.push_back(h_chi2_B[0]        ->GetMaximum());

  
  maxbin0_EE.push_back(h_etascPhot_S[1]->GetMaximum());
  maxbin0_EE.push_back(h_etascPhot_B[1]->GetMaximum());
  maxbin1_EE.push_back(h_ptPhot_S[1]    ->GetMaximum());
  maxbin1_EE.push_back(h_ptPhot_B[1]    ->GetMaximum());
  maxbin2_EE.push_back(h_sEtaEta_S[1]   ->GetMaximum());
  maxbin2_EE.push_back(h_sEtaEta_B[1]   ->GetMaximum());
  maxbin3_EE.push_back(h_sEtaPhi_S[1]   ->GetMaximum());
  maxbin3_EE.push_back(h_sEtaPhi_B[1]   ->GetMaximum());
  maxbin4_EE.push_back(h_etaWidth_S[1]  ->GetMaximum());
  maxbin4_EE.push_back(h_etaWidth_B[1]  ->GetMaximum());
  maxbin5_EE.push_back(h_phiWidth_S[1]  ->GetMaximum());
  maxbin5_EE.push_back(h_phiWidth_B[1]  ->GetMaximum());
  maxbin6_EE.push_back(h_r9_S[1]        ->GetMaximum());
  maxbin6_EE.push_back(h_r9_B[1]        ->GetMaximum());
  maxbin7_EE.push_back(h_s4_S[1]        ->GetMaximum());
  maxbin7_EE.push_back(h_s4_B[1]        ->GetMaximum());
  maxbin8_EE.push_back(h_chi2_S[1]        ->GetMaximum());
  maxbin8_EE.push_back(h_chi2_B[1]        ->GetMaximum());
  

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
  /*  std::sort( maxbin9_EB.begin(),	      maxbin9_EB.end());	  	     
  double yRange9_EB 	= maxbin9_EB.back() + 0.1*maxbin9_EB.back();
  */		    				    
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
  /*std::sort( maxbin9_EE.begin(),	      maxbin9_EE.end());	  	     
   double yRange9_EE 	= maxbin9_EE.back() + 0.1*maxbin9_EE.back();
  */		    				    
   

  h_etascPhot_S[0]  ->SetMaximum(yRange0_EB);
  h_ptPhot_S[0]     ->SetMaximum(yRange1_EB);
  h_sEtaEta_S[0]    ->SetMaximum(yRange2_EB);
  h_sEtaPhi_S[0]    ->SetMaximum(yRange3_EB);
  h_etaWidth_S[0]   ->SetMaximum(yRange4_EB);
  h_phiWidth_S[0]   ->SetMaximum(yRange5_EB);
  h_r9_S[0]         ->SetMaximum(yRange6_EB);
  h_s4_S[0]         ->SetMaximum(yRange7_EB);
  h_chi2_S[0]       ->SetMaximum(yRange8_EB);

  h_etascPhot_S[1]  ->SetMaximum(yRange0_EE);
  h_ptPhot_S[1]     ->SetMaximum(yRange1_EE);
  h_sEtaEta_S[1]    ->SetMaximum(yRange2_EE);
  h_sEtaPhi_S[1]    ->SetMaximum(yRange3_EE);
  h_etaWidth_S[1]   ->SetMaximum(yRange4_EE);
  h_phiWidth_S[1]   ->SetMaximum(yRange5_EE);
  h_r9_S[1]         ->SetMaximum(yRange6_EE);
  h_s4_S[1]         ->SetMaximum(yRange7_EE);
  h_chi2_S[1]       ->SetMaximum(yRange8_EE);


  TCanvas* c_etascPhot_EB = new TCanvas("c_etascPhot_EB", "", 1);
  TCanvas* c_ptPhot_EB    = new TCanvas("c_ptPhot_EB", "", 1);
  TCanvas* c_sEtaEta_EB   = new TCanvas("c_sEtaEta_EB", "", 1);
  TCanvas* c_sEtaPhi_EB   = new TCanvas("c_sEtaPhi_EB", "", 1);
  TCanvas* c_etaWidth_EB  = new TCanvas("c_etaWidth_EB", "", 1);
  TCanvas* c_phiWidth_EB  = new TCanvas("c_phiWidth_EB", "", 1);
  TCanvas* c_r9_EB        = new TCanvas("c_r9_EB", "", 1);
  TCanvas* c_s4_EB        = new TCanvas("c_s4_EB", "", 1);
  TCanvas* c_chi2_EB        = new TCanvas("c_chi2_EB", "", 1);

  TCanvas* c_etascPhot_EE = new TCanvas("c_etascPhot_EE", "", 1);
  TCanvas* c_ptPhot_EE    = new TCanvas("c_ptPhot_EE", "", 1);
  TCanvas* c_sEtaEta_EE   = new TCanvas("c_sEtaEta_EE", "", 1);
  TCanvas* c_sEtaPhi_EE   = new TCanvas("c_sEtaPhi_EE", "", 1);
  TCanvas* c_etaWidth_EE  = new TCanvas("c_etaWidth_EE", "", 1);
  TCanvas* c_phiWidth_EE  = new TCanvas("c_phiWidth_EE", "", 1);
  TCanvas* c_r9_EE        = new TCanvas("c_r9_EE", "", 1);
  TCanvas* c_s4_EE        = new TCanvas("c_s4_EE", "", 1);
  TCanvas* c_chi2_EE        = new TCanvas("c_chi2_EE", "", 1);
  TCanvas* c_rrPreshower  = new TCanvas("c_rrPreshower", "", 1);

  c_etascPhot_EB->cd();
  h_etascPhot_S[0]->DrawNormalized();
  h_etascPhot_B[0]->DrawNormalized("same");
  c_etascPhot_EB->SaveAs("plot_input/c_etascPhot_EB.png");
  c_etascPhot_EB->Close();

  c_ptPhot_EB->cd();
  h_ptPhot_S[0]->DrawNormalized();
  h_ptPhot_B[0]->DrawNormalized("same");
  c_ptPhot_EB->SaveAs("plot_input/c_ptPhot_EB.png");
  c_ptPhot_EB->Close();

  c_sEtaEta_EB->cd();
  h_sEtaEta_S[0]->DrawNormalized();
  h_sEtaEta_B[0]->DrawNormalized("same");
  c_sEtaEta_EB->SaveAs("plot_input/c_sEtaEta_EB.png");
  c_sEtaEta_EB->Close();

  c_sEtaPhi_EB->cd();
  h_sEtaPhi_S[0]->DrawNormalized();
  h_sEtaPhi_B[0]->DrawNormalized("same");
  c_sEtaPhi_EB->SaveAs("plot_input/c_sEtaPhi_EB.png");
  c_sEtaPhi_EB->Close();

  c_etaWidth_EB->cd();
  h_etaWidth_S[0]->DrawNormalized();
  h_etaWidth_B[0]->DrawNormalized("same");
  c_etaWidth_EB->SaveAs("plot_input/c_etaWidth_EB.png");
  c_etaWidth_EB->Close();

  c_phiWidth_EB->cd();
  h_phiWidth_S[0]->DrawNormalized();
  h_phiWidth_B[0]->DrawNormalized("same");
  c_phiWidth_EB->SaveAs("plot_input/c_phiWidth_EB.png");
  c_phiWidth_EB->Close();

  c_r9_EB->cd();
  h_r9_S[0]->DrawNormalized();
  h_r9_B[0]->DrawNormalized("same");
  c_r9_EB->SaveAs("plot_input/c_r9_EB.png");
  c_r9_EB->Close();

  c_s4_EB->cd();
  h_s4_S[0]->DrawNormalized();
  h_s4_B[0]->DrawNormalized("same");
  c_s4_EB->SaveAs("plot_input/c_s4_EB.png");
  c_s4_EB->Close();


  c_chi2_EB->cd();
  h_chi2_S[0]->DrawNormalized();
  h_chi2_B[0]->DrawNormalized("same");
  c_chi2_EB->SaveAs("plot_input/c_chi2_EB.png");
  c_chi2_EB->Close();


  c_etascPhot_EE->cd();
  h_etascPhot_S[1]->DrawNormalized();
  h_etascPhot_B[1]->DrawNormalized("same");
  c_etascPhot_EE->SaveAs("plot_input/c_etascPhot_EE.png");
  c_etascPhot_EE->Close();

  c_ptPhot_EE->cd();
  h_ptPhot_S[1]->DrawNormalized();
  h_ptPhot_B[1]->DrawNormalized("same");
  c_ptPhot_EE->SaveAs("plot_input/c_ptPhot_EE.png");
  c_ptPhot_EE->Close();

  c_sEtaEta_EE->cd();
  h_sEtaEta_S[1]->DrawNormalized();
  h_sEtaEta_B[1]->DrawNormalized("same");
  c_sEtaEta_EE->SaveAs("plot_input/c_sEtaEta_EE.png");
  c_sEtaEta_EE->Close();

  c_sEtaPhi_EE->cd();
  h_sEtaPhi_S[1]->DrawNormalized();
  h_sEtaPhi_B[1]->DrawNormalized("same");
  c_sEtaPhi_EE->SaveAs("plot_input/c_sEtaPhi_EE.png");
  c_sEtaPhi_EE->Close();

  c_etaWidth_EE->cd();
  h_etaWidth_S[1]->DrawNormalized();
  h_etaWidth_B[1]->DrawNormalized("same");
  c_etaWidth_EE->SaveAs("plot_input/c_etaWidth_EE.png");
  c_etaWidth_EE->Close();

  c_phiWidth_EE->cd();
  h_phiWidth_S[1]->DrawNormalized();
  h_phiWidth_B[1]->DrawNormalized("same");
  c_phiWidth_EE->SaveAs("plot_input/c_phiWidth_EE.png");
  c_phiWidth_EE->Close();

  c_r9_EE->cd();
  h_r9_S[1]->DrawNormalized();
  h_r9_B[1]->DrawNormalized("same");
  c_r9_EE->SaveAs("plot_input/c_r9_EE.png");
  c_r9_EE->Close();

  c_s4_EE->cd();
  h_s4_S[1]->DrawNormalized();
  h_s4_B[1]->DrawNormalized("same");
  c_s4_EE->SaveAs("plot_input/c_s4_EE.png");
  c_s4_EE->Close();

  /*  c_rrPreshower->cd();
  h_rrPreshower_S->DrawNormalized();
  h_rrPreshower_B->DrawNormalized("same");
  c_rrPreshower->SaveAs("plot_input/c_rrPreshower.png");
  c_rrPreshower->Close();
  */

  //canvas with legend
  /*  TCanvas* c_legend = new TCanvas("c_legend", "", 1);
  TLegend* leg = new TLegend(0.2, 0.2, 0.7, 0.5 );
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  
  leg->AddEntry(h_rrPreshower_S, "signal (matched)", "f");
  leg->AddEntry(h_rrPreshower_B, "background (unmatched)", "f");
  c_legend->cd();
  leg->Draw();
  c_legend->SaveAs("plot_input/legend.png");
  c_legend->Close();*/

}
