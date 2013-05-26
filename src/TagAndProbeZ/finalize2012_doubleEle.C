#include <TTree.h>
#include <TFile.h>
#include <TLegend.h>
#include <TF1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <TLorentzVector.h>
#include <fillPlot2012_doubleEle.h>

inline double delta_phi(double phi1, double phi2) {
  
  double dphi = TMath::Abs(phi1 - phi2);
  return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
}

vector <double> finalize2012_doubleEle(double int_exp_2012_30, double int_exp_2012_50, double int_exp_2012_75, double int_exp_2012_90, double pt1min_30=30, double pt1min_50=50, double pt1min_75=75, double pt1min_90=90, double pt1max_30=30, double pt1max_50=50, double pt1max_75=75, double pt1max_90=90, int eb = 1, int r9 = 1){
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111111);  
  gStyle->SetOptFit(111110); 
  gStyle->SetOptFile(1); 
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(.3);
  gStyle->SetMarkerColor(1);
  
  TCanvas* c0 = new TCanvas("c0"," ",200,10,500,500);
  c0->Clear();
  
  // input files
  string mcnames[1];
  mcnames[0]  = "DrellYan, M=50";

  TFile* mc_2012[1];            // [16] = MC samples

  TString redntpDir= "/xrootdfs/cms/local/gdimperi/Higgs/reduced";

  // full 2012                                     
  TFile* data = TFile::Open(redntpDir+"/redntp.53xv3_data.cicpfloose..DrellYan_v1/merged/redntp_DoubleElectron_Run2012A.root");

  // mc signal and backgrounds   
  if( int_exp_2012_30 > 0 ){
    
    // Drell Yan samples
    mc_2012[0] = TFile::Open(redntpDir+"/redntp.53xv2_extra.cicpfloose..DrellYan_v1/redntp_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1_00.root");

  }
  
  // k factors 
  double kfactor    = 1.;   


  // cross sections at 8 TeV - all from PREP
  double cross_mc[1];
  cross_mc[0]  = 1 * 1 * kfactor;         
  
 

  // getting the number of original events in each sample (processed with CMSSW)
  int n_mc_2012[1];   
  for(int i=0; i<1; i++){
    n_mc_2012[i] = 0;
    if(int_exp_2012_30>0) n_mc_2012[i] = 1.;  
  }

  // setting the scaling factor to actual lumi 
  double scale_mc_2012_30[1];
  double scale_mc_2012_50[1];
  double scale_mc_2012_75[1];
  double scale_mc_2012_90[1];

  for(int i=0; i<1; i++){
    scale_mc_2012_30[i] = 0; 
    scale_mc_2012_50[i] = 0; 
    scale_mc_2012_75[i] = 0; 
    scale_mc_2012_90[i] = 0; 
    if(int_exp_2012_30>0) scale_mc_2012_30[i] = cross_mc[i] * int_exp_2012_30 / n_mc_2012[i];
    if(int_exp_2012_50>0) scale_mc_2012_50[i] = cross_mc[i] * int_exp_2012_50 / n_mc_2012[i];
    if(int_exp_2012_75>0) scale_mc_2012_75[i] = cross_mc[i] * int_exp_2012_75 / n_mc_2012[i];
    if(int_exp_2012_90>0) scale_mc_2012_90[i] = cross_mc[i] * int_exp_2012_90 / n_mc_2012[i];
  }

  // char for output name
  char name[1000];
  
  // output root file
  sprintf(name,"results_doubleEle/histo.root");
  TFile * hOutputFile = new TFile(name, "RECREATE" ) ;

  // histograms needed by the machinery
  TH1D* vardata_30_EB[11];
  TH1D* vardata_50_EB[11];
  TH1D* vardata_75_EB[11];
  TH1D* vardata_90_EB[11];

  TH1D* vardata_30_EE[12];
  TH1D* vardata_50_EE[12];
  TH1D* vardata_75_EE[12];
  TH1D* vardata_90_EE[12];

  //barrel
  vardata_30_EB[0] = new TH1D("hdata_ptPhot_30_EB","", 120, 0., 180.);
  vardata_30_EB[1] = new TH1D("hdata_etascPhot_30_EB","", 120, -2.5, 2.5);
  vardata_30_EB[2] = new TH1D("hdata_sEtaEta_30_EB","", 120, 0.005, 0.015);
  vardata_30_EB[3] = new TH1D("hdata_sEtaPhi_30_EB","", 120, -0.0002, 0.0002);
  vardata_30_EB[4] = new TH1D("hdata_scetawid_30_EB","", 120, 0., 0.03);
  vardata_30_EB[5] = new TH1D("hdata_scphiwid_30_EB","", 120, 0., 0.15);
  vardata_30_EB[6] = new TH1D("hdata_r9_30_EB","", 120, 0., 1.);
  vardata_30_EB[7] = new TH1D("hdata_s4_30_EB","", 120, 0., 1.);
  vardata_30_EB[8] = new TH1D("hdata_HoverE_30_EB","", 120, 0., 0.5);
  vardata_30_EB[9] = new TH1D("hdata_rho_30_EB","", 120, 0., 60.);
  vardata_30_EB[10] = new TH1D("hdata_BDToutput_30_EB","", 120, -1., 1.);

  vardata_50_EB[0] = new TH1D("hdata_ptPhot_50_EB","", 120, 0., 180.);
  vardata_50_EB[1] = new TH1D("hdata_etascPhot_50_EB","", 120, -2.5, 2.5);
  vardata_50_EB[2] = new TH1D("hdata_sEtaEta_50_EB","", 120, 0.005, 0.015);
  vardata_50_EB[3] = new TH1D("hdata_sEtaPhi_50_EB","", 120, -0.0002, 0.0002);
  vardata_50_EB[4] = new TH1D("hdata_scetawid_50_EB","", 120, 0., 0.03);
  vardata_50_EB[5] = new TH1D("hdata_scphiwid_50_EB","", 120, 0., 0.15);
  vardata_50_EB[6] = new TH1D("hdata_r9_50_EB","", 120, 0., 1.);
  vardata_50_EB[7] = new TH1D("hdata_s4_50_EB","", 120, 0., 1.);
  vardata_50_EB[8] = new TH1D("hdata_HoverE_50_EB","", 120, 0., 0.5);
  vardata_50_EB[9] = new TH1D("hdata_rho_50_EB","", 120, 0., 60.);
  vardata_50_EB[10] = new TH1D("hdata_BDToutput_50_EB","", 120, -1., 1.);

  vardata_75_EB[0] = new TH1D("hdata_ptPhot_75_EB","", 120, 0., 180.);
  vardata_75_EB[1] = new TH1D("hdata_etascPhot_75_EB","", 120, -2.5, 2.5);
  vardata_75_EB[2] = new TH1D("hdata_sEtaEta_75_EB","", 120, 0.005, 0.015);
  vardata_75_EB[3] = new TH1D("hdata_sEtaPhi_75_EB","", 120, -0.0002, 0.0002);
  vardata_75_EB[4] = new TH1D("hdata_scetawid_75_EB","", 120, 0., 0.03);
  vardata_75_EB[5] = new TH1D("hdata_scphiwid_75_EB","", 120, 0., 0.15);
  vardata_75_EB[6] = new TH1D("hdata_r9_75_EB","", 120, 0., 1.);
  vardata_75_EB[7] = new TH1D("hdata_s4_75_EB","", 120, 0., 1.);
  vardata_75_EB[8] = new TH1D("hdata_HoverE_75_EB","", 120, 0., 0.5);
  vardata_75_EB[9] = new TH1D("hdata_rho_75_EB","", 120, 0., 60.);
  vardata_75_EB[10] = new TH1D("hdata_BDToutput_75_EB","", 120, -1., 1.);

  vardata_90_EB[0] = new TH1D("hdata_ptPhot_90_EB","", 120, 0., 180.);
  vardata_90_EB[1] = new TH1D("hdata_etascPhot_90_EB","", 120, -2.5, 2.5);
  vardata_90_EB[2] = new TH1D("hdata_sEtaEta_90_EB","", 120, 0.005, 0.015);
  vardata_90_EB[3] = new TH1D("hdata_sEtaPhi_90_EB","", 120, -0.0002, 0.0002);
  vardata_90_EB[4] = new TH1D("hdata_scetawid_90_EB","", 120, 0., 0.03);
  vardata_90_EB[5] = new TH1D("hdata_scphiwid_90_EB","", 120, 0., 0.15);
  vardata_90_EB[6] = new TH1D("hdata_r9_90_EB","", 120, 0., 1.);
  vardata_90_EB[7] = new TH1D("hdata_s4_90_EB","", 120, 0., 1.);
  vardata_90_EB[8] = new TH1D("hdata_HoverE_90_EB","", 120, 0., 0.5);
  vardata_90_EB[9] = new TH1D("hdata_rho_90_EB","", 120, 0., 60.);
  vardata_90_EB[10] = new TH1D("hdata_BDToutput_90_EB","", 120, -1., 1.);
  
  //endcap
  vardata_30_EE[0] = new TH1D("hdata_ptPhot_30_EE","", 120, 0., 180.);
  vardata_30_EE[1] = new TH1D("hdata_etascPhot_30_EE","", 120, -2.5, 2.5);
  vardata_30_EE[2] = new TH1D("hdata_sEtaEta_30_EE","", 120, 0.01, 0.04);
  vardata_30_EE[3] = new TH1D("hdata_sEtaPhi_30_EE","", 120, -0.01, 0.01);
  vardata_30_EE[4] = new TH1D("hdata_scetawid_30_EE","", 120, 0., 0.06);
  vardata_30_EE[5] = new TH1D("hdata_scphiwid_30_EE","", 120, 0., 0.15);
  vardata_30_EE[6] = new TH1D("hdata_r9_30_EE","", 120, 0., 1.);
  vardata_30_EE[7] = new TH1D("hdata_s4_30_EE","", 120, 0., 1.);
  vardata_30_EE[8] = new TH1D("hdata_HoverE_30_EE","", 120, 0., 0.5);
  vardata_30_EE[9] = new TH1D("hdata_rho_30_EE","", 120, 0., 60.);
  vardata_30_EE[10] = new TH1D("hdata_BDToutput_30_EE","", 120, -1., 1.);
  vardata_30_EE[11] = new TH1D("hdata_sigmaRR_30_EE","", 120, 0., 15.);

  vardata_50_EE[0] = new TH1D("hdata_ptPhot_50_EE","", 120, 0., 180.);
  vardata_50_EE[1] = new TH1D("hdata_etascPhot_50_EE","", 120, -2.5, 2.5);
  vardata_50_EE[2] = new TH1D("hdata_sEtaEta_50_EE","", 120, 0.01, 0.04);
  vardata_50_EE[3] = new TH1D("hdata_sEtaPhi_50_EE","", 120, -0.01, 0.01);
  vardata_50_EE[4] = new TH1D("hdata_scetawid_50_EE","", 120, 0., 0.06);
  vardata_50_EE[5] = new TH1D("hdata_scphiwid_50_EE","", 120, 0., 0.15);
  vardata_50_EE[6] = new TH1D("hdata_r9_50_EE","", 120, 0., 1.);
  vardata_50_EE[7] = new TH1D("hdata_s4_50_EE","", 120, 0., 1.);
  vardata_50_EE[8] = new TH1D("hdata_HoverE_50_EE","", 120, 0., 0.5);
  vardata_50_EE[9] = new TH1D("hdata_rho_50_EE","", 120, 0., 60.);
  vardata_50_EE[10] = new TH1D("hdata_BDToutput_50_EE","", 120, -1., 1.);
  vardata_50_EE[11] = new TH1D("hdata_sigmaRR_50_EE","", 120, 0., 15.);

  vardata_75_EE[0] = new TH1D("hdata_ptPhot_75_EE","", 120, 0., 180.);
  vardata_75_EE[1] = new TH1D("hdata_etascPhot_75_EE","", 120, -2.5, 2.5);
  vardata_75_EE[2] = new TH1D("hdata_sEtaEta_75_EE","", 120, 0.01, 0.04);
  vardata_75_EE[3] = new TH1D("hdata_sEtaPhi_75_EE","", 120, -0.01, 0.01);
  vardata_75_EE[4] = new TH1D("hdata_scetawid_75_EE","", 120, 0., 0.06);
  vardata_75_EE[5] = new TH1D("hdata_scphiwid_75_EE","", 120, 0., 0.15);
  vardata_75_EE[6] = new TH1D("hdata_r9_75_EE","", 120, 0., 1.);
  vardata_75_EE[7] = new TH1D("hdata_s4_75_EE","", 120, 0., 1.);
  vardata_75_EE[8] = new TH1D("hdata_HoverE_75_EE","", 120, 0., 0.5);
  vardata_75_EE[9] = new TH1D("hdata_rho_75_EE","", 120, 0., 60.);
  vardata_75_EE[10] = new TH1D("hdata_BDToutput_75_EE","", 120, -1., 1.);
  vardata_75_EE[11] = new TH1D("hdata_sigmaRR_75_EE","", 120, 0., 15.);

  vardata_90_EE[0] = new TH1D("hdata_ptPhot_90_EE","", 120, 0., 180.);
  vardata_90_EE[1] = new TH1D("hdata_etascPhot_90_EE","", 120, -2.5, 2.5);
  vardata_90_EE[2] = new TH1D("hdata_sEtaEta_90_EE","", 120, 0.01, 0.04);
  vardata_90_EE[3] = new TH1D("hdata_sEtaPhi_90_EE","", 120, -0.01, 0.01);
  vardata_90_EE[4] = new TH1D("hdata_scetawid_90_EE","", 120, 0., 0.06);
  vardata_90_EE[5] = new TH1D("hdata_scphiwid_90_EE","", 120, 0., 0.15);
  vardata_90_EE[6] = new TH1D("hdata_r9_90_EE","", 120, 0., 1.);
  vardata_90_EE[7] = new TH1D("hdata_s4_90_EE","", 120, 0., 1.);
  vardata_90_EE[8] = new TH1D("hdata_HoverE_90_EE","", 120, 0., 0.5);
  vardata_90_EE[9] = new TH1D("hdata_rho_90_EE","", 120, 0., 60.);
  vardata_90_EE[10] = new TH1D("hdata_BDToutput_90_EE","", 120, -1., 1.);
  vardata_90_EE[11] = new TH1D("hdata_sigmaRR_90_EE","", 120, 0., 15.);

  cout << "defined histograms" << endl;

  string variable[12];
  variable[0] = "ptPhot";  
  variable[1] = "etascPhot";  
  variable[2] = "sEtaEta";  
  variable[3] = "sEtaPhi";  
  variable[4] = "scetawid";  
  variable[5] = "scphiwid";  
  variable[6] = "r9";  
  variable[7] = "s4";  
  variable[8] = "HoverE";
  variable[9] = "rho";    
  variable[10] = "BDT_output";  
  variable[11] = "sigmaRR";  

  
  for(int i=0; i<11; i++) {
    vardata_30_EB[i]->Sumw2();
    vardata_50_EB[i]->Sumw2();
    vardata_75_EB[i]->Sumw2();
    vardata_90_EB[i]->Sumw2();
  }
  for(int i=0; i<12; i++) {
    vardata_30_EE[i]->Sumw2();
    vardata_50_EE[i]->Sumw2();
    vardata_75_EE[i]->Sumw2();
    vardata_90_EE[i]->Sumw2();
  }
  
  cout << "sumw2 data" << endl;
  
  TH1D* var_mc_2012_30_EB[1][11];   
  TH1D* var_mc_2012_50_EB[1][11];   
  TH1D* var_mc_2012_75_EB[1][11];   
  TH1D* var_mc_2012_90_EB[1][11];
   
  TH1D* var_mc_2012_30_EE[1][12];   
  TH1D* var_mc_2012_50_EE[1][12];   
  TH1D* var_mc_2012_75_EE[1][12];   
  TH1D* var_mc_2012_90_EE[1][12];

  var_mc_2012_30_EB[0][0] = new TH1D("h_ptPhot_30_EB","", 120, 0., 180.);
  var_mc_2012_30_EB[0][1] = new TH1D("h_etascPhot_30_EB","", 120, -2.5, 2.5);
  var_mc_2012_30_EB[0][2] = new TH1D("h_sEtaEta_30_EB","", 120, 0.005, 0.015);
  var_mc_2012_30_EB[0][3] = new TH1D("h_sEtaPhi_30_EB","", 120, -0.0002, 0.0002);
  var_mc_2012_30_EB[0][4] = new TH1D("h_scetawid_30_EB","", 120, 0., 0.03);
  var_mc_2012_30_EB[0][5] = new TH1D("h_scphiwid_30_EB","", 120, 0., 0.15);
  var_mc_2012_30_EB[0][6] = new TH1D("h_r9_30_EB","", 120, 0., 1.);
  var_mc_2012_30_EB[0][7] = new TH1D("h_s4_30_EB","", 120, 0., 1.);
  var_mc_2012_30_EB[0][8] = new TH1D("h_HoverE_30_EB","", 120, 0., 0.5);
  var_mc_2012_30_EB[0][9] = new TH1D("h_rho_30_EB","", 120, 0., 60.);
  var_mc_2012_30_EB[0][10] = new TH1D("h_BDToutput_30_EB","", 120, -1., 1.);

  var_mc_2012_50_EB[0][0] = new TH1D("h_ptPhot_50_EB","", 120, 0., 180.);
  var_mc_2012_50_EB[0][1] = new TH1D("h_etascPhot_50_EB","", 120, -2.5, 2.5);
  var_mc_2012_50_EB[0][2] = new TH1D("h_sEtaEta_50_EB","", 120, 0.005, 0.015);
  var_mc_2012_50_EB[0][3] = new TH1D("h_sEtaPhi_50_EB","", 120, -0.0002, 0.0002);
  var_mc_2012_50_EB[0][4] = new TH1D("h_scetawid_50_EB","", 120, 0., 0.03);
  var_mc_2012_50_EB[0][5] = new TH1D("h_scphiwid_50_EB","", 120, 0., 0.15);
  var_mc_2012_50_EB[0][6] = new TH1D("h_r9_50_EB","", 120, 0., 1.);
  var_mc_2012_50_EB[0][7] = new TH1D("h_s4_50_EB","", 120, 0., 1.);
  var_mc_2012_50_EB[0][8] = new TH1D("h_HoverE_50_EB","", 120, 0., 0.5);
  var_mc_2012_50_EB[0][9] = new TH1D("h_rho_50_EB","", 120, 0., 60.);
  var_mc_2012_50_EB[0][10] = new TH1D("h_BDToutput_50_EB","", 120, -1., 1.);

  var_mc_2012_75_EB[0][0] = new TH1D("h_ptPhot_75_EB","", 120, 0., 180.);
  var_mc_2012_75_EB[0][1] = new TH1D("h_etascPhot_75_EB","", 120, -2.5, 2.5);
  var_mc_2012_75_EB[0][2] = new TH1D("h_sEtaEta_75_EB","", 120, 0.005, 0.015);
  var_mc_2012_75_EB[0][3] = new TH1D("h_sEtaPhi_75_EB","", 120, -0.0002, 0.0002);
  var_mc_2012_75_EB[0][4] = new TH1D("h_scetawid_75_EB","", 120, 0., 0.03);
  var_mc_2012_75_EB[0][5] = new TH1D("h_scphiwid_75_EB","", 120, 0., 0.15);
  var_mc_2012_75_EB[0][6] = new TH1D("h_r9_75_EB","", 120, 0., 1.);
  var_mc_2012_75_EB[0][7] = new TH1D("h_s4_75_EB","", 120, 0., 1.);
  var_mc_2012_75_EB[0][8] = new TH1D("h_HoverE_75_EB","", 120, 0., 0.5);
  var_mc_2012_75_EB[0][9] = new TH1D("h_rho_75_EB","", 120, 0., 60.);
  var_mc_2012_75_EB[0][10] = new TH1D("h_BDToutput_75_EB","", 120, -1., 1.);

  var_mc_2012_90_EB[0][0] = new TH1D("h_ptPhot_90_EB","", 120, 0., 180.);
  var_mc_2012_90_EB[0][1] = new TH1D("h_etascPhot_90_EB","", 120, -2.5, 2.5);
  var_mc_2012_90_EB[0][2] = new TH1D("h_sEtaEta_90_EB","", 120, 0.005, 0.015);
  var_mc_2012_90_EB[0][3] = new TH1D("h_sEtaPhi_90_EB","", 120, -0.0002, 0.0002);
  var_mc_2012_90_EB[0][4] = new TH1D("h_scetawid_90_EB","", 120, 0., 0.03);
  var_mc_2012_90_EB[0][5] = new TH1D("h_scphiwid_90_EB","", 120, 0., 0.15);
  var_mc_2012_90_EB[0][6] = new TH1D("h_r9_90_EB","", 120, 0., 1.);
  var_mc_2012_90_EB[0][7] = new TH1D("h_s4_90_EB","", 120, 0., 1.);
  var_mc_2012_90_EB[0][8] = new TH1D("h_HoverE_90_EB","", 120, 0., 0.5);
  var_mc_2012_90_EB[0][9] = new TH1D("h_rho_90_EB","", 120, 0., 60.);
  var_mc_2012_90_EB[0][10] = new TH1D("h_BDToutput_90_EB","", 120, -1., 1.);
  
  //endcap
  var_mc_2012_30_EE[0][0] = new TH1D("h_ptPhot_30_EE","", 120, 0., 180.);
  var_mc_2012_30_EE[0][1] = new TH1D("h_etascPhot_30_EE","", 120, -2.5, 2.5);
  var_mc_2012_30_EE[0][2] = new TH1D("h_sEtaEta_30_EE","", 120, 0.01, 0.04);
  var_mc_2012_30_EE[0][3] = new TH1D("h_sEtaPhi_30_EE","", 120, -0.01, 0.01);
  var_mc_2012_30_EE[0][4] = new TH1D("h_scetawid_30_EE","", 120, 0., 0.06);
  var_mc_2012_30_EE[0][5] = new TH1D("h_scphiwid_30_EE","", 120, 0., 0.15);
  var_mc_2012_30_EE[0][6] = new TH1D("h_r9_30_EE","", 120, 0., 1.);
  var_mc_2012_30_EE[0][7] = new TH1D("h_s4_30_EE","", 120, 0., 1.);
  var_mc_2012_30_EE[0][8] = new TH1D("h_HoverE_30_EE","", 120, 0., 0.5);
  var_mc_2012_30_EE[0][9] = new TH1D("h_rho_30_EE","", 120, 0., 60.);
  var_mc_2012_30_EE[0][10] = new TH1D("h_BDToutput_30_EE","", 120, -1., 1.);
  var_mc_2012_30_EE[0][11] = new TH1D("h_sigmaRR_30_EE","", 120, 0., 15.);

  var_mc_2012_50_EE[0][0] = new TH1D("h_ptPhot_50_EE","", 120, 0., 180.);
  var_mc_2012_50_EE[0][1] = new TH1D("h_etascPhot_50_EE","", 120, -2.5, 2.5);
  var_mc_2012_50_EE[0][2] = new TH1D("h_sEtaEta_50_EE","", 120, 0.01, 0.04);
  var_mc_2012_50_EE[0][3] = new TH1D("h_sEtaPhi_50_EE","", 120, -0.01, 0.01);
  var_mc_2012_50_EE[0][4] = new TH1D("h_scetawid_50_EE","", 120, 0., 0.06);
  var_mc_2012_50_EE[0][5] = new TH1D("h_scphiwid_50_EE","", 120, 0., 0.15);
  var_mc_2012_50_EE[0][6] = new TH1D("h_r9_50_EE","", 120, 0., 1.);
  var_mc_2012_50_EE[0][7] = new TH1D("h_s4_50_EE","", 120, 0., 1.);
  var_mc_2012_50_EE[0][8] = new TH1D("h_HoverE_50_EE","", 120, 0., 0.5);
  var_mc_2012_50_EE[0][9] = new TH1D("h_rho_50_EE","", 120, 0., 60.);
  var_mc_2012_50_EE[0][10] = new TH1D("h_BDToutput_50_EE","", 120, -1., 1.);
  var_mc_2012_50_EE[0][11] = new TH1D("h_sigmaRR_50_EE","", 120, 0., 15.);

  var_mc_2012_75_EE[0][0] = new TH1D("h_ptPhot_75_EE","", 120, 0., 180.);
  var_mc_2012_75_EE[0][1] = new TH1D("h_etascPhot_75_EE","", 120, -2.5, 2.5);
  var_mc_2012_75_EE[0][2] = new TH1D("h_sEtaEta_75_EE","", 120, 0.01, 0.04);
  var_mc_2012_75_EE[0][3] = new TH1D("h_sEtaPhi_75_EE","", 120, -0.01, 0.01);
  var_mc_2012_75_EE[0][4] = new TH1D("h_scetawid_75_EE","", 120, 0., 0.06);
  var_mc_2012_75_EE[0][5] = new TH1D("h_scphiwid_75_EE","", 120, 0., 0.15);
  var_mc_2012_75_EE[0][6] = new TH1D("h_r9_75_EE","", 120, 0., 1.);
  var_mc_2012_75_EE[0][7] = new TH1D("h_s4_75_EE","", 120, 0., 1.);
  var_mc_2012_75_EE[0][8] = new TH1D("h_HoverE_75_EE","", 120, 0., 0.5);
  var_mc_2012_75_EE[0][9] = new TH1D("h_rho_75_EE","", 120, 0., 60.);
  var_mc_2012_75_EE[0][10] = new TH1D("h_BDToutput_75_EE","", 120, -1., 1.);
  var_mc_2012_75_EE[0][11] = new TH1D("h_sigmaRR_75_EE","", 120, 0., 15.);

  var_mc_2012_90_EE[0][0] = new TH1D("h_ptPhot_90_EE","", 120, 0., 180.);
  var_mc_2012_90_EE[0][1] = new TH1D("h_etascPhot_90_EE","", 120, -2.5, 2.5);
  var_mc_2012_90_EE[0][2] = new TH1D("h_sEtaEta_90_EE","", 120, 0.01, 0.04);
  var_mc_2012_90_EE[0][3] = new TH1D("h_sEtaPhi_90_EE","", 120, -0.01, 0.01);
  var_mc_2012_90_EE[0][4] = new TH1D("h_scetawid_90_EE","", 120, 0., 0.06);
  var_mc_2012_90_EE[0][5] = new TH1D("h_scphiwid_90_EE","", 120, 0., 0.15);
  var_mc_2012_90_EE[0][6] = new TH1D("h_r9_90_EE","", 120, 0., 1.);
  var_mc_2012_90_EE[0][7] = new TH1D("h_s4_90_EE","", 120, 0., 1.);
  var_mc_2012_90_EE[0][8] = new TH1D("h_HoverE_90_EE","", 120, 0., 0.5);
  var_mc_2012_90_EE[0][9] = new TH1D("h_rho_90_EE","", 120, 0., 60.);
  var_mc_2012_90_EE[0][10] = new TH1D("h_BDToutput_90_EE","", 120, -1., 1.);
  var_mc_2012_90_EE[0][11] = new TH1D("h_sigmaRR_90_EE","", 120, 0., 15.);
   
  cout << "definition of histograms" << endl;



  for (int i=0; i<11; i++) {
    var_mc_2012_30_EB[0][i]->Sumw2();
    var_mc_2012_50_EB[0][i]->Sumw2();
    var_mc_2012_75_EB[0][i]->Sumw2();
    var_mc_2012_90_EB[0][i]->Sumw2();
  }
  for (int i=0; i<12; i++) {
    var_mc_2012_30_EE[0][i]->Sumw2();
    var_mc_2012_50_EE[0][i]->Sumw2();
    var_mc_2012_75_EE[0][i]->Sumw2();
    var_mc_2012_90_EE[0][i]->Sumw2();
  }


  cout <<  "------------------------- all ------------------" << endl;
  cout <<   endl;

  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "                         DATA                                 +" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  cout << "------------------- HLT = 30 -------------------" << endl; 
  // creating the fillers and setting cuts: data
  fillPlot2012_doubleEle data_fill_30((TTree*)data->Get("AnaTree"));
  data_fill_30.Setcuts(pt1min_30,pt1max_30,eb,r9,30);  

  // analysis, data, HLT = 30 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 30" <<  endl;
  sprintf(name,"results_doubleEle/events_HLT30.root");
  data_fill_30.WriteRoot(name);
  data_fill_30.Plot(vardata_30_EB, vardata_30_EE,  100); 
  
  std::cout << "Selected events on data EB " << vardata_30_EB[0]->GetEntries() << " with HLT = 30" << std::endl;
  std::cout << "Selected events on data EE " << vardata_30_EE[0]->GetEntries() << " with HLT = 30" << std::endl;

  cout << "------------------- HLT = 50 -------------------" << endl; 
  // creating the fillers and setting cuts: data
  fillPlot2012_doubleEle data_fill_50((TTree*)data->Get("AnaTree"));
  data_fill_50.Setcuts(pt1min_50,pt1max_50,eb,r9,50);  

  // analysis, data, HLT = 50 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 50" <<  endl;
  sprintf(name,"results_doubleEle/events_HLT50.root");
  data_fill_50.WriteRoot(name);
  data_fill_50.Plot(vardata_50_EB, vardata_50_EE,  100); 
  
  std::cout << "Selected events on data EB " << vardata_50_EB[0]->GetEntries() << " with HLT = 50" << std::endl;
  std::cout << "Selected events on data EE " << vardata_50_EE[0]->GetEntries() << " with HLT = 50" << std::endl;

  cout << "------------------- HLT = 75 -------------------" << endl; 
  // creating the fillers and setting cuts: data
  fillPlot2012_doubleEle data_fill_75((TTree*)data->Get("AnaTree"));
  data_fill_75.Setcuts(pt1min_75,pt1max_75,eb,r9,75);  

  // analysis, data, HLT = 75 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 75" <<  endl;
  sprintf(name,"results_doubleEle/events_HLT75.root");
  data_fill_75.WriteRoot(name);
  data_fill_75.Plot(vardata_75_EB, vardata_75_EE,  100); 
  
  std::cout << "Selected events on data EB " << vardata_75_EB[0]->GetEntries() << " with HLT = 75" << std::endl;
  std::cout << "Selected events on data EE " << vardata_75_EE[0]->GetEntries() << " with HLT = 75" << std::endl;

  cout << "------------------- HLT = 90 -------------------" << endl; 
  // creating the fillers and setting cuts: data
  fillPlot2012_doubleEle data_fill_90((TTree*)data->Get("AnaTree"));
  data_fill_90.Setcuts(pt1min_90,pt1max_90,eb,r9,90);  

  // analysis, data, HLT = 90 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 90" <<  endl;
  sprintf(name,"results_doubleEle/events_HLT90.root");
  data_fill_90.WriteRoot(name);
  data_fill_90.Plot(vardata_90_EB, vardata_90_EE,  100); 
  
  std::cout << "Selected events on data EB " << vardata_90_EB[0]->GetEntries() << " with HLT = 90" << std::endl;
  std::cout << "Selected events on data EE " << vardata_90_EE[0]->GetEntries() << " with HLT = 90" << std::endl;

  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "                           MC                                 +" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;
  // 1) HLT = 30
  cout << endl;
  cout << "------------------- HLT = 30 -------------------" << endl; 

  // analysis, MC, HLT = 30 
  // creating the fillers and setting cuts: MC, HLT = 30
  fillPlot2012_doubleEle* mc_2012_fill_30[1];
  for (int i=0; i<1; i++){
    if(int_exp_2012_30>0) mc_2012_fill_30[i] = new fillPlot2012_doubleEle((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_30>0) mc_2012_fill_30[i]->Setcuts(pt1min_30,pt1max_30,eb,r9,30); 
    mc_2012_fill_30[i]->DoPuReweight();
  }

  for (int i=0; i<1; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_30>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 30" <<  endl;   
      sprintf(name,"%s%s%s","results_doubleEle/events_",mcnames[i].c_str(),"_2012_HLT30.root");
      mc_2012_fill_30[i]->WriteRoot(name);
      cout << "calling plot" << endl;             
      mc_2012_fill_30[i]->Plot(var_mc_2012_30_EB[0], var_mc_2012_30_EE[0], i) ;  
    }
  }

  std::cout << "Selected events on mc2012_EB " << name << " for HLT=30 " << var_mc_2012_30_EB[0][0]->GetEntries() << std::endl;
  std::cout << "Selected events on mc2012_EE " << name << " for HLT=30 " << var_mc_2012_30_EE[0][0]->GetEntries() << std::endl;
  cout << endl;

  cout << "------------------- HLT = 50 -------------------" << endl; 

  // analysis, MC, HLT = 50 
  // creating the fillers and setting cuts: MC, HLT = 50
  fillPlot2012_doubleEle* mc_2012_fill_50[1];
  for (int i=0; i<1; i++){
    if(int_exp_2012_50>0) mc_2012_fill_50[i] = new fillPlot2012_doubleEle((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_50>0) mc_2012_fill_50[i]->Setcuts(pt1min_50,pt1max_50,eb,r9,50); 
    mc_2012_fill_50[i]->DoPuReweight();
  }

  for (int i=0; i<1; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_50>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 50" <<  endl;   
      sprintf(name,"%s%s%s","results_doubleEle/events_",mcnames[i].c_str(),"_2012_HLT50.root");
      mc_2012_fill_50[i]->WriteRoot(name);
      cout << "calling plot" << endl;             
      mc_2012_fill_50[i]->Plot(var_mc_2012_50_EB[0], var_mc_2012_50_EE[0], i) ;  
    }
  }

  std::cout << "Selected events on mc2012_EB " << name << " for HLT=50 " << var_mc_2012_50_EB[0][0]->GetEntries() << std::endl;
  std::cout << "Selected events on mc2012_EE " << name << " for HLT=50 " << var_mc_2012_50_EE[0][0]->GetEntries() << std::endl;
  cout << endl;

  cout << "------------------- HLT = 75 -------------------" << endl; 

  // analysis, MC, HLT = 75 
  // creating the fillers and setting cuts: MC, HLT = 75
  fillPlot2012_doubleEle* mc_2012_fill_75[1];
  for (int i=0; i<1; i++){
    if(int_exp_2012_75>0) mc_2012_fill_75[i] = new fillPlot2012_doubleEle((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_75>0) mc_2012_fill_75[i]->Setcuts(pt1min_75,pt1max_75,eb,r9,75); 
    mc_2012_fill_75[i]->DoPuReweight();
  }

  for (int i=0; i<1; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_75>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 75" <<  endl;   
      sprintf(name,"%s%s%s","results_doubleEle/events_",mcnames[i].c_str(),"_2012_HLT75.root");
      mc_2012_fill_75[i]->WriteRoot(name);
      cout << "calling plot" << endl;             
      mc_2012_fill_75[i]->Plot(var_mc_2012_75_EB[0], var_mc_2012_75_EE[0], i) ;  
    }
  }

  std::cout << "Selected events on mc2012_EB " << name << " for HLT=75 " << var_mc_2012_75_EB[0][0]->GetEntries() << std::endl;
  std::cout << "Selected events on mc2012_EE " << name << " for HLT=75 " << var_mc_2012_75_EE[0][0]->GetEntries() << std::endl;
  cout << endl;

  cout << "------------------- HLT = 90 -------------------" << endl; 

  // analysis, MC, HLT = 90 
  // creating the fillers and setting cuts: MC, HLT = 90
  fillPlot2012_doubleEle* mc_2012_fill_90[1];
  for (int i=0; i<1; i++){
    if(int_exp_2012_90>0) mc_2012_fill_90[i] = new fillPlot2012_doubleEle((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_90>0) mc_2012_fill_90[i]->Setcuts(pt1min_90,pt1max_90,eb,r9,90); 
    mc_2012_fill_90[i]->DoPuReweight();
  }

  for (int i=0; i<1; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_90>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 90" <<  endl;   
      sprintf(name,"%s%s%s","results_doubleEle/events_",mcnames[i].c_str(),"_2012_HLT90.root");
      mc_2012_fill_90[i]->WriteRoot(name);
      cout << "calling plot" << endl;             
      mc_2012_fill_90[i]->Plot(var_mc_2012_90_EB[0], var_mc_2012_90_EE[0], i) ;  
    }
  }

  std::cout << "Selected events on mc2012_EB " << name << " for HLT=90 " << var_mc_2012_90_EB[0][0]->GetEntries() << std::endl;
  std::cout << "Selected events on mc2012_EE " << name << " for HLT=90 " << var_mc_2012_90_EE[0][0]->GetEntries() << std::endl;
  cout << endl;
  cout << endl;

  cout << "scaling histograms" << endl;
  //scale to 1

  for (int i=0; i<11; i++){
    if((double)var_mc_2012_30_EB[0][i]->Integral()>0) var_mc_2012_30_EB[0][i]->Scale(1./(double)var_mc_2012_30_EB[0][i]->Integral());  
    if((double)var_mc_2012_50_EB[0][i]->Integral()>0) var_mc_2012_50_EB[0][i]->Scale(1./(double)var_mc_2012_50_EB[0][i]->Integral());  
    if((double)var_mc_2012_75_EB[0][i]->Integral()>0) var_mc_2012_75_EB[0][i]->Scale(1./(double)var_mc_2012_75_EB[0][i]->Integral());  
    if((double)var_mc_2012_90_EB[0][i]->Integral()>0) var_mc_2012_90_EB[0][i]->Scale(1./(double)var_mc_2012_90_EB[0][i]->Integral());  
  
    if((double)vardata_30_EB[i]->Integral()>0) vardata_30_EB[i]->Scale(1./(double)vardata_30_EB[i]->Integral());  
    if((double)vardata_50_EB[i]->Integral()>0) vardata_50_EB[i]->Scale(1./(double)vardata_50_EB[i]->Integral());  
    if((double)vardata_75_EB[i]->Integral()>0) vardata_75_EB[i]->Scale(1./(double)vardata_75_EB[i]->Integral());  
    if((double)vardata_90_EB[i]->Integral()>0) vardata_90_EB[i]->Scale(1./(double)vardata_90_EB[i]->Integral());  
  }  
  cout << "scaled barrel " << endl;
  for (int i=0; i<12; i++){
    if((double)var_mc_2012_30_EE[0][i]->Integral()>0) var_mc_2012_30_EE[0][i]->Scale(1./(double)var_mc_2012_30_EE[0][i]->Integral());  
    if((double)var_mc_2012_50_EE[0][i]->Integral()>0) var_mc_2012_50_EE[0][i]->Scale(1./(double)var_mc_2012_50_EE[0][i]->Integral());  
    if((double)var_mc_2012_75_EE[0][i]->Integral()>0) var_mc_2012_75_EE[0][i]->Scale(1./(double)var_mc_2012_75_EE[0][i]->Integral());  
    if((double)var_mc_2012_90_EE[0][i]->Integral()>0) var_mc_2012_90_EE[0][i]->Scale(1./(double)var_mc_2012_90_EE[0][i]->Integral());  
  
    if((double)vardata_30_EE[i]->Integral()>0) vardata_30_EE[i]->Scale(1./(double)vardata_30_EE[i]->Integral());  
    if((double)vardata_50_EE[i]->Integral()>0) vardata_50_EE[i]->Scale(1./(double)vardata_50_EE[i]->Integral());  
    if((double)vardata_75_EE[i]->Integral()>0) vardata_75_EE[i]->Scale(1./(double)vardata_75_EE[i]->Integral());  
    if((double)vardata_90_EE[i]->Integral()>0) vardata_90_EE[i]->Scale(1./(double)vardata_90_EE[i]->Integral());  
  }  
  cout << "scaled endcap " << endl;


  cout << "colors of histograms" << endl;
  for(int i=0; i<11; i++){
    var_mc_2012_30_EB[0][i]->SetTitle("");
    var_mc_2012_30_EB[0][i]->SetStats(0);
    var_mc_2012_30_EB[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_30_EB[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(), "_30_EB");
    var_mc_2012_30_EB[0][i]->SetXTitle(name);
    var_mc_2012_30_EB[0][i]->SetLineColor(kBlack);
    var_mc_2012_30_EB[0][i]->SetLineWidth(2);

    var_mc_2012_50_EB[0][i]->SetTitle("");
    var_mc_2012_50_EB[0][i]->SetStats(0);
    var_mc_2012_50_EB[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_50_EB[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(), "_50_EB");
    var_mc_2012_50_EB[0][i]->SetXTitle(name);
    var_mc_2012_50_EB[0][i]->SetLineColor(kBlack);
    var_mc_2012_50_EB[0][i]->SetLineWidth(2);
  
    var_mc_2012_75_EB[0][i]->SetTitle("");
    var_mc_2012_75_EB[0][i]->SetStats(0);
    var_mc_2012_75_EB[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_75_EB[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(), "_75_EB");
    var_mc_2012_75_EB[0][i]->SetXTitle(name);
    var_mc_2012_75_EB[0][i]->SetLineColor(kBlack);
    var_mc_2012_75_EB[0][i]->SetLineWidth(2);

    var_mc_2012_90_EB[0][i]->SetTitle("");
    var_mc_2012_90_EB[0][i]->SetStats(0);
    var_mc_2012_90_EB[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_90_EB[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(), "_90_EB");
    var_mc_2012_90_EB[0][i]->SetXTitle(name);
    var_mc_2012_90_EB[0][i]->SetLineColor(kBlack);
    var_mc_2012_90_EB[0][i]->SetLineWidth(2);

  }
  for(int i=0; i<12; i++){
    var_mc_2012_30_EE[0][i]->SetTitle("");
    var_mc_2012_30_EE[0][i]->SetStats(0);
    var_mc_2012_30_EE[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_30_EE[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(),"_30_EE");
    var_mc_2012_30_EE[0][i]->SetXTitle(name);
    var_mc_2012_30_EE[0][i]->SetLineColor(kBlack);
    var_mc_2012_30_EE[0][i]->SetLineWidth(2);

    var_mc_2012_50_EE[0][i]->SetTitle("");
    var_mc_2012_50_EE[0][i]->SetStats(0);
    var_mc_2012_50_EE[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_50_EE[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(),"_50_EE");
    var_mc_2012_50_EE[0][i]->SetXTitle(name);
    var_mc_2012_50_EE[0][i]->SetLineColor(kBlack);
    var_mc_2012_50_EE[0][i]->SetLineWidth(2);

    var_mc_2012_75_EE[0][i]->SetTitle("");
    var_mc_2012_75_EE[0][i]->SetStats(0);
    var_mc_2012_75_EE[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_75_EE[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(),"_75_EE");
    var_mc_2012_75_EE[0][i]->SetXTitle(name);
    var_mc_2012_75_EE[0][i]->SetLineColor(kBlack);
    var_mc_2012_75_EE[0][i]->SetLineWidth(2);

    var_mc_2012_90_EE[0][i]->SetTitle("");
    var_mc_2012_90_EE[0][i]->SetStats(0);
    var_mc_2012_90_EE[0][i]->SetTitleOffset(1.25,"Y");
    var_mc_2012_90_EE[0][i]->SetYTitle("arb. units");
    sprintf(name, "%s%s", (variable[i]).c_str(),"_90_EE");
    var_mc_2012_90_EE[0][i]->SetXTitle(name);
    var_mc_2012_90_EE[0][i]->SetLineColor(kBlack);
    var_mc_2012_90_EE[0][i]->SetLineWidth(2);

  }

  cout << "legend" << endl;
  // ----------------------------------------
  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  legge = leg->AddEntry(var_mc_2012_30_EB[0][0], "Drell Yan M50", "f");
  //legge = leg->AddEntry(var_30[1], "QCD", "f");


  cout << "draw and save plots" << endl;
  // mc only plot: data vs background, HLT=30
  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_30_EB[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_30_EB[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-30_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-30_EB.root");
    c0->SaveAs(name);
  }
  
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_30_EE[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_30_EE[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-30_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-30_EE.root");
    c0->SaveAs(name);
  }

  // mc only plot: data vs background, HLT=50
  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_50_EB[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_50_EB[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-50_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-50_EB.root");
    c0->SaveAs(name);
  }
  
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_50_EE[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_50_EE[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-50_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-50_EE.root");
    c0->SaveAs(name);
  }


  // mc only plot: data vs background, HLT=75
  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_75_EB[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_75_EB[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-75_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-75_EB.root");
    c0->SaveAs(name);
  }
  
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_75_EE[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_75_EE[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-75_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-75_EE.root");
    c0->SaveAs(name);
  }

  // mc only plot: data vs background, HLT=90
  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_90_EB[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_90_EB[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-90_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-90_EB.root");
    c0->SaveAs(name);
  }
  
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    var_mc_2012_90_EE[0][i]->SetFillColor(kBlue-9);
    var_mc_2012_90_EE[0][i]->Draw("hist");
    leg->Draw();
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-90_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/mc_",(variable[i]).c_str(),"_HLT-90_EE.root");
    c0->SaveAs(name);
  }

  // ------------------------------------
  // data only plot, HLT = 30
  for(int i=0;i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_30_EB[i]->SetXTitle(variable[i].c_str());
    vardata_30_EB[i]->SetTitle("");
    vardata_30_EB[i]->SetStats(0);
    vardata_30_EB[i]->SetMarkerStyle(8);
    vardata_30_EB[i]->SetMarkerSize(.9);
    vardata_30_EB[i]->SetTitleOffset(1.25,"Y");
    vardata_30_EB[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-30_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-30_EB.root");
    c0->SaveAs(name);
  }
  for(int i=0;i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_30_EE[i]->SetXTitle(variable[i].c_str());
    vardata_30_EE[i]->SetTitle("");
    vardata_30_EE[i]->SetStats(0);
    vardata_30_EE[i]->SetMarkerStyle(8);
    vardata_30_EE[i]->SetMarkerSize(.9);
    vardata_30_EE[i]->SetTitleOffset(1.25,"Y");
    vardata_30_EE[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-30_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-30_EE.root");
    c0->SaveAs(name);
  }
  for(int i=0;i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_50_EB[i]->SetXTitle(variable[i].c_str());
    vardata_50_EB[i]->SetTitle("");
    vardata_50_EB[i]->SetStats(0);
    vardata_50_EB[i]->SetMarkerStyle(8);
    vardata_50_EB[i]->SetMarkerSize(.9);
    vardata_50_EB[i]->SetTitleOffset(1.25,"Y");
    vardata_50_EB[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-50_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-50_EB.root");
    c0->SaveAs(name);
  }
  for(int i=0;i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_50_EE[i]->SetXTitle(variable[i].c_str());
    vardata_50_EE[i]->SetTitle("");
    vardata_50_EE[i]->SetStats(0);
    vardata_50_EE[i]->SetMarkerStyle(8);
    vardata_50_EE[i]->SetMarkerSize(.9);
    vardata_50_EE[i]->SetTitleOffset(1.25,"Y");
    vardata_50_EE[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-50_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-50_EE.root");
    c0->SaveAs(name);
  }
  
  for(int i=0;i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_75_EB[i]->SetXTitle(variable[i].c_str());
    vardata_75_EB[i]->SetTitle("");
    vardata_75_EB[i]->SetStats(0);
    vardata_75_EB[i]->SetMarkerStyle(8);
    vardata_75_EB[i]->SetMarkerSize(.9);
    vardata_75_EB[i]->SetTitleOffset(1.25,"Y");
    vardata_75_EB[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-75_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-75_EB.root");
    c0->SaveAs(name);
  }
  for(int i=0;i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_75_EE[i]->SetXTitle(variable[i].c_str());
    vardata_75_EE[i]->SetTitle("");
    vardata_75_EE[i]->SetStats(0);
    vardata_75_EE[i]->SetMarkerStyle(8);
    vardata_75_EE[i]->SetMarkerSize(.9);
    vardata_75_EE[i]->SetTitleOffset(1.25,"Y");
    vardata_75_EE[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-75_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-75_EE.root");
    c0->SaveAs(name);
  }
  
  for(int i=0;i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_90_EB[i]->SetXTitle(variable[i].c_str());
    vardata_90_EB[i]->SetTitle("");
    vardata_90_EB[i]->SetStats(0);
    vardata_90_EB[i]->SetMarkerStyle(8);
    vardata_90_EB[i]->SetMarkerSize(.9);
    vardata_90_EB[i]->SetTitleOffset(1.25,"Y");
    vardata_90_EB[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-90_EB.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-90_EB.root");
    c0->SaveAs(name);
  }
  for(int i=0;i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_90_EE[i]->SetXTitle(variable[i].c_str());
    vardata_90_EE[i]->SetTitle("");
    vardata_90_EE[i]->SetStats(0);
    vardata_90_EE[i]->SetMarkerStyle(8);
    vardata_90_EE[i]->SetMarkerSize(.9);
    vardata_90_EE[i]->SetTitleOffset(1.25,"Y");
    vardata_90_EE[i]->Draw("pe");
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-90_EE.png");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data_",(variable[i]).c_str(),"_HLT-90_EE.root");
    c0->SaveAs(name);
  }
  
  // -----------------------------------------------
  // data overlaid to mc
  legge = leg->AddEntry(vardata_30_EB[0], "data", "p");

  //
  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_30_EB[i]->Draw("pe");
    var_mc_2012_30_EB[0][i]->Draw("samehist");
    leg->Draw();
    vardata_30_EB[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_30_EB.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_30_EB.png");
    c0->SaveAs(name);
  }
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_30_EE[i]->Draw("pe");
    var_mc_2012_30_EE[0][i]->Draw("samehist");
    leg->Draw();
    vardata_30_EE[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_30_EE.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_30_EE.png");
    c0->SaveAs(name);
  }

  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_50_EB[i]->Draw("pe");
    var_mc_2012_50_EB[0][i]->Draw("samehist");
    leg->Draw();
    vardata_50_EB[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_50_EB.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_50_EB.png");
    c0->SaveAs(name);
  }
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_50_EE[i]->Draw("pe");
    var_mc_2012_50_EE[0][i]->Draw("samehist");
    leg->Draw();
    vardata_50_EE[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_50_EE.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_50_EE.png");
    c0->SaveAs(name);
  }

  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_75_EB[i]->Draw("pe");
    var_mc_2012_75_EB[0][i]->Draw("samehist");
    leg->Draw();
    vardata_75_EB[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_75_EB.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_75_EB.png");
    c0->SaveAs(name);
  }
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_75_EE[i]->Draw("pe");
    var_mc_2012_75_EE[0][i]->Draw("samehist");
    leg->Draw();
    vardata_75_EE[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_75_EE.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_75_EE.png");
    c0->SaveAs(name);
  }

  for(int i=0; i<11; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_90_EB[i]->Draw("pe");
    var_mc_2012_90_EB[0][i]->Draw("samehist");
    leg->Draw();
    vardata_90_EB[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_90_EB.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_90_EB.png");
    c0->SaveAs(name);
  }
  for(int i=0; i<12; i++){
    if(i==8) c0->SetLogy();
    if(i==9) c0->SetLogy(0);
    vardata_90_EE[i]->Draw("pe");
    var_mc_2012_90_EE[0][i]->Draw("samehist");
    leg->Draw();
    vardata_90_EE[i]->Draw("pesame");
    gPad->RedrawAxis();
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_90_EE.root");
    c0->SaveAs(name);
    sprintf(name,"%s%s%s","results_doubleEle/data-mc_",variable[i].c_str(),"_90_EE.png");
    c0->SaveAs(name);
  }



  // -------------------------------------------------------------------------
  sprintf(name,"results_doubleEle/yields.txt");
  ofstream outfile(name);  
  outfile << "####################################" << endl;
  outfile << "CUTS " << endl;
  outfile << "####################################" << endl;
  outfile << "ptphot1, HLT = 30 : " << pt1min_30 << " - " << pt1max_30 << endl;
  outfile << "ptphot1, HLT = 50 : " << pt1min_50 << " - " << pt1max_50 << endl; 
  outfile << "ptphot1, HLT = 75 : " << pt1min_75 << " - " << pt1max_75 << endl; 
  outfile << "ptphot1, HLT = 90 : " << pt1min_90 << " - " << pt1max_90 << endl; 
  outfile << "ebcat : " << eb << endl;
  outfile << "r9cat : " << r9 << endl;
  outfile << endl;
  outfile << "####################################" << endl;
  outfile << "N of generated events" << endl;
  outfile << "####################################" << endl;
  outfile << "# events Drell Yan, 50 = "       << n_mc_2012[0]  << endl;
  outfile << endl;

  outfile.close();
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
  
  delete data;
  
  for(int i=0; i<1; i++){
    delete mc_2012_fill_30[i];
    delete mc_2012_fill_50[i];
    delete mc_2012_fill_75[i];
    delete mc_2012_fill_90[i];
    
  }
  
  vector<double> values;
  
  return values;
}








