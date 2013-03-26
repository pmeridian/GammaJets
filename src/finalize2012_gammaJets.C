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
#include <../interface/fillPlot2012_gammaJets.h>

inline double delta_phi(double phi1, double phi2) {
  
  double dphi = TMath::Abs(phi1 - phi2);
  return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
}

vector <double> finalize2012_gammaJets(double int_exp_2012_30, double int_exp_2012_50, double int_exp_2012_75, double int_exp_2012_90, double pt1min_30=30, double pt1min_50=50, double pt1min_75=75, double pt1min_90=90, double pt1max_30=30, double pt1max_50=50, double pt1max_75=75, double pt1max_90=90, int eb = 1, int r9 = 1, string variableMC = "massgg", string variableData = "massgg", int nbin = 200, double min = 90, double max = 190, string axis = "m(#gamma#gamma)[GeV]"){
  
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
  string mcnames[16];
  mcnames[0]  = "QCD, 20-30";
  mcnames[1]  = "QCD, 30-80";
  mcnames[2]  = "QCD, 80-170";
  mcnames[3]  = "QCD, 170-250";
  mcnames[4]  = "QCD, 250-350";
  mcnames[5]  = "QCD, >350";
  mcnames[6]  = "gjet, 0-15";
  mcnames[7]  = "gjet, 15-30";
  mcnames[8]  = "gjet, 30-50";
  mcnames[9]  = "gjet, 50-80";
  mcnames[10] = "gjet, 80-120";
  mcnames[11] = "gjet, 120-170";
  mcnames[12] = "gjet, 170-300";
  // 
  mcnames[13] = "gjet, 470-800";
  mcnames[14] = "gjet, 800-1400";
  mcnames[15] = "gjet, 1400-1800";

  TFile* mc_2012[16];            // [16] = MC samples

  TString redntpDir= "/xrootdfs/cms/local/crovelli/GammaJets/reduced";

  // full 2012                                     
  TFile* data = TFile::Open(redntpDir+"/redntp.53xv2_data.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/all2012.root");
  
  // mc signal and backgrounds   
  if( int_exp_2012_30 > 0 ){
    
    // QCD samples
    mc_2012[0] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[1] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[2] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[3] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[4] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[5] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    // gjet samples 
    mc_2012[6]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-0to15_TuneZ2star_8TeV_pythia6.root");
    mc_2012[7]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-15to30_TuneZ2star_8TeV_pythia6.root");
    mc_2012[8]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-30to50_TuneZ2star_8TeV_pythia6.root");
    mc_2012[9]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-50to80_TuneZ2star_8TeV_pythia6.root");
    mc_2012[10] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-80to120_TuneZ2star_8TeV_pythia6.root");
    mc_2012[11] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-120to170_TuneZ2star_8TeV_pythia6.root");
    mc_2012[12] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-170to300_TuneZ2star_8TeV_pythia6.root");
    mc_2012[13] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-470to800_TuneZ2star_8TeV_pythia6.root");
    mc_2012[14] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-800to1400_TuneZ2star_8TeV_pythia6.root");
    mc_2012[15] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v5/merged/redntp_G_Pt-1400to1800_TuneZ2star_8TeV_pythia6.root");
  }
  
  // k factors 
  double kfactorqcd    = 1.;   
  double kfactorgamjet = 1.3;           //  chiara: still valid?

  // cross sections at 8 TeV - all from PREP
  double cross_mc[16];
  cross_mc[0]  = 288600000 * 0.0101 * kfactorqcd;         
  cross_mc[1]  = 74330000 * 0.0621 * kfactorqcd;         
  cross_mc[2]  = 1191000 * 0.1539 * kfactorqcd;         
  cross_mc[3]  = 30990 * 0.148 * kfactorqcd;         
  cross_mc[4]  = 4250 * 0.131 * kfactorqcd;         
  cross_mc[5]  = 810 * 0.11 * kfactorqcd;          
  cross_mc[6]  = 90601456 * kfactorgamjet;          
  cross_mc[7]  = 200061.7 * kfactorgamjet;          
  cross_mc[8]  = 19931.62 * kfactorgamjet;          
  cross_mc[9]  = 3322.309 * kfactorgamjet;          
  cross_mc[10] = 558.2865 * kfactorgamjet;          
  cross_mc[11] = 108.0068 * kfactorgamjet;          
  cross_mc[12] = 30.12207 * kfactorgamjet;          
  cross_mc[13] = 0.2119244 * kfactorgamjet;          
  cross_mc[14] = 0.007077847 * kfactorgamjet;          
  cross_mc[15] = 4.510327 * 0.00001 * kfactorgamjet;          

  // getting the number of original events in each sample (processed with CMSSW)
  int n_mc_2012[16];   
  for(int i=0; i<16; i++){
    n_mc_2012[i] = 0;
    if(int_exp_2012_30>0) n_mc_2012[i] = ((TH1D*)mc_2012[i]->Get("ptphotgen1"))->GetEntries();  
  }

  // setting the scaling factor to actual lumi 
  double scale_mc_2012_30[16];
  double scale_mc_2012_50[16];
  double scale_mc_2012_75[16];
  double scale_mc_2012_90[16];

  for(int i=0; i<16; i++){
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
  sprintf(name,"results_gammaJ/histo.root");
  TFile * hOutputFile = new TFile(name, "RECREATE" ) ;

  // histograms needed by the machinery
  TH1D* vardata_30 = new TH1D("vardata_30", "vardata_30", nbin,min,max);
  TH1D* vardata_50 = new TH1D("vardata_50", "vardata_50", nbin,min,max);
  TH1D* vardata_75 = new TH1D("vardata_75", "vardata_75", nbin,min,max);
  TH1D* vardata_90 = new TH1D("vardata_90", "vardata_90", nbin,min,max);

  vardata_30->Sumw2();
  vardata_50->Sumw2();
  vardata_75->Sumw2();
  vardata_90->Sumw2();

  TH1D* var_mc_2012_30[16];     // 16 = MC samples we have 
  TH1D* var_mc_2012_50[16];     // 16 = MC samples we have 
  TH1D* var_mc_2012_75[16];     // 16 = MC samples we have 
  TH1D* var_mc_2012_90[16];     // 16 = MC samples we have 

  TH1D* var_30[2];              // 2  = number of species
  TH1D* var_50[2];              // 2  = number of species
  TH1D* var_75[2];              // 2  = number of species
  TH1D* var_90[2];              // 2  = number of species

  for (int i=0; i<2; i++) {
    sprintf(name,"%s%d","var_30",i);
    var_30[i] = new TH1D(name,name,nbin,min,max);
    var_30[i]->Sumw2();          
    sprintf(name,"%s%d","var_50",i);
    var_50[i] = new TH1D(name,name,nbin,min,max);
    var_50[i]->Sumw2();          
    sprintf(name,"%s%d","var_75",i);
    var_75[i] = new TH1D(name,name,nbin,min,max);
    var_75[i]->Sumw2();          
    sprintf(name,"%s%d","var_90",i);
    var_90[i] = new TH1D(name,name,nbin,min,max);
    var_90[i]->Sumw2();          
 }

  for (int i=0; i<16; i++) {
    sprintf(name,"%s%d","var_mc_2012_30_",i);
    var_mc_2012_30[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012_30[i]->Sumw2();  
    sprintf(name,"%s%d","var_mc_2012_50_",i);
    var_mc_2012_50[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012_50[i]->Sumw2();  
    sprintf(name,"%s%d","var_mc_2012_75_",i);
    var_mc_2012_75[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012_75[i]->Sumw2();  
    sprintf(name,"%s%d","var_mc_2012_90_",i);
    var_mc_2012_90[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012_90[i]->Sumw2();  
  }




  // 1) HLT = 30
  cout << endl;
  cout << "------------------- HLT = 30 -------------------" << endl; 

  // creating the fillers and setting cuts: data
  fillPlot2012_gammaJets data_fill_30((TTree*)data->Get("AnaTree"));
  data_fill_30.Setcuts(pt1min_30,pt1max_30,eb,r9,30);  

  // analysis, data, HLT = 30 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 30" <<  endl;
  sprintf(name,"results_gammaJ/events_HLT30.root");
  data_fill_30.WriteRoot(name);
  vardata_30->Add(data_fill_30.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata_30->GetEntries() << " with HLT = 30" << std::endl;

  // creating the fillers and setting cuts: MC, HLT = 30
  fillPlot2012_gammaJets* mc_2012_fill_30[16];
  for (int i=0; i<16; i++){
    if(int_exp_2012_30>0) mc_2012_fill_30[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_30>0) mc_2012_fill_30[i]->Setcuts(pt1min_30,pt1max_30,eb,r9,30); 
    mc_2012_fill_30[i]->DoPuReweight();
  }

  // analysis, MC, HLT = 30 
  for (int i=0; i<16; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_30>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 30" <<  endl;   
      sprintf(name,"%s%s%s","results_gammaJ/events_",mcnames[i].c_str(),"_2012_HLT30.root");
      mc_2012_fill_30[i]->WriteRoot(name);             
      var_mc_2012_30[i]->Add( mc_2012_fill_30[i]->Plot(variableMC, name, nbin, min, max, i) );  
      std::cout << "Selected events on mc2012 " << name << " for HLT=30 " << var_mc_2012_30[i]->GetEntries() << std::endl;
    }
  }
  cout << endl;


  // 2) HLT = 50
  cout << endl;
  cout << "------------------- HLT = 50 -------------------" << endl; 

  // creating the fillers and setting cuts: data
  fillPlot2012_gammaJets data_fill_50((TTree*)data->Get("AnaTree"));
  data_fill_50.Setcuts(pt1min_50,pt1max_50,eb,r9,50);  

  // analysis, data, HLT = 50 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 50" <<  endl;
  sprintf(name,"results_gammaJ/events_HLT50.root");
  data_fill_50.WriteRoot(name);
  vardata_50->Add(data_fill_50.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata_50->GetEntries() << " with HLT = 50" << std::endl;

  // creating the fillers and setting cuts: MC, HLT = 50
  fillPlot2012_gammaJets* mc_2012_fill_50[16];
  for (int i=0; i<16; i++){
    if(int_exp_2012_50>0) mc_2012_fill_50[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_50>0) mc_2012_fill_50[i]->Setcuts(pt1min_50,pt1max_50,eb,r9,50); 
    mc_2012_fill_50[i]->DoPuReweight();
  }

  // analysis, MC, HLT = 50 
  for (int i=0; i<16; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_50>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 50" <<  endl;   
      sprintf(name,"%s%s%s","results_gammaJ/events_",mcnames[i].c_str(),"_2012_HLT50.root");
      mc_2012_fill_50[i]->WriteRoot(name);             
      var_mc_2012_50[i]->Add( mc_2012_fill_50[i]->Plot(variableMC, name, nbin, min, max, i) );  
      std::cout << "Selected events on mc2012 " << name << " for HLT=50 " << var_mc_2012_50[i]->GetEntries() << std::endl;
    }
  }
  cout << endl;


  // 1) HLT = 75
  cout << endl;
  cout << "------------------- HLT = 75 -------------------" << endl; 

  // creating the fillers and setting cuts: data
  fillPlot2012_gammaJets data_fill_75((TTree*)data->Get("AnaTree"));
  data_fill_75.Setcuts(pt1min_75,pt1max_75,eb,r9,75);  

  // analysis, data, HLT = 75 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 75" <<  endl;
  sprintf(name,"results_gammaJ/events_HLT75.root");
  data_fill_75.WriteRoot(name);
  vardata_75->Add(data_fill_75.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata_75->GetEntries() << " with HLT = 75" << std::endl;

  // creating the fillers and setting cuts: MC, HLT = 75
  fillPlot2012_gammaJets* mc_2012_fill_75[16];
  for (int i=0; i<16; i++){
    if(int_exp_2012_75>0) mc_2012_fill_75[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_75>0) mc_2012_fill_75[i]->Setcuts(pt1min_75,pt1max_75,eb,r9,75); 
    mc_2012_fill_75[i]->DoPuReweight();
  }

  // analysis, MC, HLT = 75 
  for (int i=0; i<16; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_75>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 75" <<  endl;   
      sprintf(name,"%s%s%s","results_gammaJ/events_",mcnames[i].c_str(),"_2012_HLT75.root");
      mc_2012_fill_75[i]->WriteRoot(name);             
      var_mc_2012_75[i]->Add( mc_2012_fill_75[i]->Plot(variableMC, name, nbin, min, max, i) );  
      std::cout << "Selected events on mc2012 " << name << " for HLT=75 " << var_mc_2012_75[i]->GetEntries() << std::endl;
    }
  }
  cout << endl;

  // 1) HLT = 90
  cout << endl;
  cout << "------------------- HLT = 90 -------------------" << endl; 

  // creating the fillers and setting cuts: data
  fillPlot2012_gammaJets data_fill_90((TTree*)data->Get("AnaTree"));
  data_fill_90.Setcuts(pt1min_90,pt1max_90,eb,r9,90);  

  // analysis, data, HLT = 90 
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events for HLT 90" <<  endl;
  sprintf(name,"results_gammaJ/events_HLT90.root");
  data_fill_90.WriteRoot(name);
  vardata_90->Add(data_fill_90.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata_90->GetEntries() << " with HLT = 90" << std::endl;

  // creating the fillers and setting cuts: MC, HLT = 90
  fillPlot2012_gammaJets* mc_2012_fill_90[16];
  for (int i=0; i<16; i++){
    if(int_exp_2012_90>0) mc_2012_fill_90[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012_90>0) mc_2012_fill_90[i]->Setcuts(pt1min_90,pt1max_90,eb,r9,90); 
    mc_2012_fill_90[i]->DoPuReweight();
  }

  // analysis, MC, HLT = 90 
  for (int i=0; i<16; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012_90>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events for HLT 90" <<  endl;   
      sprintf(name,"%s%s%s","results_gammaJ/events_",mcnames[i].c_str(),"_2012_HLT90.root");
      mc_2012_fill_90[i]->WriteRoot(name);             
      var_mc_2012_90[i]->Add( mc_2012_fill_90[i]->Plot(variableMC, name, nbin, min, max, i) );  
      std::cout << "Selected events on mc2012 " << name << " for HLT=90 " << var_mc_2012_90[i]->GetEntries() << std::endl;
    }
  }
  cout << endl;


  // scale mc to equivalent lumi for each HLT path
  for (int i=0; i<16; i++){
    if(int_exp_2012_30>0) var_mc_2012_30[i]->Scale(scale_mc_2012_30[i]);  
    if(int_exp_2012_50>0) var_mc_2012_50[i]->Scale(scale_mc_2012_50[i]);  
    if(int_exp_2012_75>0) var_mc_2012_75[i]->Scale(scale_mc_2012_75[i]);  
    if(int_exp_2012_90>0) var_mc_2012_90[i]->Scale(scale_mc_2012_90[i]);  
  }

  // counting number of events passing selection (scaled)   
  double num_mc_2012_30[16], num_uns_mc_2012_30[16]; 
  double num_mc_2012_50[16], num_uns_mc_2012_50[16]; 
  double num_mc_2012_75[16], num_uns_mc_2012_75[16]; 
  double num_mc_2012_90[16], num_uns_mc_2012_90[16]; 

  for (int i=0; i<16; i++){ 
    num_mc_2012_30[i] = 0;
    if(int_exp_2012_30>0) num_mc_2012_30[i] = var_mc_2012_30[i]->Integral();        
    num_mc_2012_50[i] = 0;
    if(int_exp_2012_50>0) num_mc_2012_50[i] = var_mc_2012_50[i]->Integral();        
    num_mc_2012_75[i] = 0;
    if(int_exp_2012_75>0) num_mc_2012_75[i] = var_mc_2012_75[i]->Integral();        
    num_mc_2012_90[i] = 0;
    if(int_exp_2012_90>0) num_mc_2012_90[i] = var_mc_2012_90[i]->Integral();        
    // 
    num_uns_mc_2012_30[i] = 0;
    if(int_exp_2012_30>0) num_uns_mc_2012_30[i] = var_mc_2012_30[i]->Integral();        
    num_uns_mc_2012_50[i] = 0;
    if(int_exp_2012_50>0) num_uns_mc_2012_50[i] = var_mc_2012_50[i]->Integral();        
    num_uns_mc_2012_75[i] = 0;
    if(int_exp_2012_75>0) num_uns_mc_2012_75[i] = var_mc_2012_75[i]->Integral();        
    num_uns_mc_2012_90[i] = 0;
    if(int_exp_2012_90>0) num_uns_mc_2012_90[i] = var_mc_2012_90[i]->Integral();        
  }

  // scale control sample
  double num_data_30 = vardata_30->Integral();
  double num_data_50 = vardata_50->Integral();
  double num_data_75 = vardata_75->Integral();
  double num_data_90 = vardata_90->Integral();

  for (int j=0; j<2; j++){   
    int offset(0);
    if(j>0) offset = 9;    // to add gamma+jets contributions up 
    for (int k=0 ; k<16-j-offset; k++){   
      if(int_exp_2012_30>0) var_30[j]->Add(var_mc_2012_30[k]);
      if(int_exp_2012_50>0) var_50[j]->Add(var_mc_2012_50[k]);
      if(int_exp_2012_75>0) var_75[j]->Add(var_mc_2012_75[k]);
      if(int_exp_2012_90>0) var_90[j]->Add(var_mc_2012_90[k]);
    }	
  }

  // final plots
  char ytitle_30[100], ytitle_50[100], ytitle_75[100], ytitle_90[100];
  sprintf(ytitle_30,"%s%d%s","N_{ev}/",int(int_exp_2012_30),"pb^{-1}");
  sprintf(ytitle_50,"%s%d%s","N_{ev}/",int(int_exp_2012_50),"pb^{-1}");
  sprintf(ytitle_75,"%s%d%s","N_{ev}/",int(int_exp_2012_75),"pb^{-1}");
  sprintf(ytitle_90,"%s%d%s","N_{ev}/",int(int_exp_2012_90),"pb^{-1}");
  for(int i=0; i<2; i++){
    var_30[i]->SetTitle("");
    var_30[i]->SetStats(0);
    var_30[i]->SetTitleOffset(1.25,"Y");
    var_30[i]->SetYTitle(ytitle_30);
    var_30[i]->SetXTitle(axis.c_str());
    var_30[i]->SetLineColor(kBlack);
    var_30[i]->SetLineWidth(2);
    //
    var_50[i]->SetTitle("");
    var_50[i]->SetStats(0);
    var_50[i]->SetTitleOffset(1.25,"Y");
    var_50[i]->SetYTitle(ytitle_50);
    var_50[i]->SetXTitle(axis.c_str());
    var_50[i]->SetLineColor(kBlack);
    var_50[i]->SetLineWidth(2);
    //
    var_75[i]->SetTitle("");
    var_75[i]->SetStats(0);
    var_75[i]->SetTitleOffset(1.25,"Y");
    var_75[i]->SetYTitle(ytitle_75);
    var_75[i]->SetXTitle(axis.c_str());
    var_75[i]->SetLineColor(kBlack);
    var_75[i]->SetLineWidth(2);
    //
    var_90[i]->SetTitle("");
    var_90[i]->SetStats(0);
    var_90[i]->SetTitleOffset(1.25,"Y");
    var_90[i]->SetYTitle(ytitle_90);
    var_90[i]->SetXTitle(axis.c_str());
    var_90[i]->SetLineColor(kBlack);
    var_90[i]->SetLineWidth(2);
  }


  // ----------------------------------------
  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  legge = leg->AddEntry(var_30[0], "gamma+jets", "f");
  legge = leg->AddEntry(var_30[1], "QCD", "f");

  // mc only plot: data vs background, HLT=30
  var_30[0]->SetFillColor(kBlue-9);
  var_30[0]->Draw("hist");
  var_30[1]->SetFillColor(kMagenta-9);
  var_30[1]->Draw("samehist");
  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-30.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-30.root");
  c0->SaveAs(name);

  // mc only plot: data vs background, HLT=50
  var_50[0]->SetFillColor(kBlue-9);
  var_50[0]->Draw("hist");
  var_50[1]->SetFillColor(kMagenta-9);
  var_50[1]->Draw("samehist");
  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-50.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-50.root");
  c0->SaveAs(name);

  // mc only plot: data vs background, HLT=75
  var_75[0]->SetFillColor(kBlue-9);
  var_75[0]->Draw("hist");
  var_75[1]->SetFillColor(kMagenta-9);
  var_75[1]->Draw("samehist");
  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-75.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-75.root");
  c0->SaveAs(name);

  // mc only plot: data vs background, HLT=90
  var_90[0]->SetFillColor(kBlue-9);
  var_90[0]->Draw("hist");
  var_90[1]->SetFillColor(kMagenta-9);
  var_90[1]->Draw("samehist");
  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-90.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_HLT-90.root");
  c0->SaveAs(name);

  // all together, mc only
  TH1D* var_all_0 = (TH1D*) var_30[0]->Clone("var_all_0");
  TH1D* var_all_1 = (TH1D*) var_30[1]->Clone("var_all_1");
  var_all_0->Add(var_50[0]);
  var_all_0->Add(var_75[0]);
  var_all_0->Add(var_90[0]);
  var_all_1->Add(var_50[1]);
  var_all_1->Add(var_75[1]);
  var_all_1->Add(var_90[1]);
  var_all_0->SetFillColor(kBlue-9);
  var_all_0->Draw("hist");
  var_all_1->SetFillColor(kMagenta-9);
  var_all_1->Draw("samehist");
  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_all.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_all.root");
  c0->SaveAs(name);  

  // ------------------------------------
  // data only plot, HLT = 30
  vardata_30->SetXTitle(axis.c_str());
  vardata_30->SetTitle("");
  vardata_30->SetStats(0);
  vardata_30->SetMarkerStyle(8);
  vardata_30->SetMarkerSize(.9);
  vardata_30->SetTitleOffset(1.25,"Y");
  vardata_30->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),"_HLT-30.png");
  c0->SaveAs(name);

  // data only plot, HLT = 50
  vardata_50->SetXTitle(axis.c_str());
  vardata_50->SetTitle("");
  vardata_50->SetStats(0);
  vardata_50->SetMarkerStyle(8);
  vardata_50->SetMarkerSize(.9);
  vardata_50->SetTitleOffset(1.25,"Y");
  vardata_50->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),"_HLT-50.png");
  c0->SaveAs(name);

  // data only plot, HLT = 75
  vardata_75->SetXTitle(axis.c_str());
  vardata_75->SetTitle("");
  vardata_75->SetStats(0);
  vardata_75->SetMarkerStyle(8);
  vardata_75->SetMarkerSize(.9);
  vardata_75->SetTitleOffset(1.25,"Y");
  vardata_75->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),"_HLT-75.png");
  c0->SaveAs(name);

  // data only plot, HLT = 90
  vardata_90->SetXTitle(axis.c_str());
  vardata_90->SetTitle("");
  vardata_90->SetStats(0);
  vardata_90->SetMarkerStyle(8);
  vardata_90->SetMarkerSize(.9);
  vardata_90->SetTitleOffset(1.25,"Y");
  vardata_90->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),"_HLT-90.png");
  c0->SaveAs(name);

  // all together
  TH1D* vardata_all = (TH1D*) vardata_30->Clone("vardata_all");
  vardata_all->Add(vardata_50);
  vardata_all->Add(vardata_75);
  vardata_all->Add(vardata_90);
  vardata_all->SetXTitle(axis.c_str());
  vardata_all->SetTitle("");
  vardata_all->SetStats(0);
  vardata_all->SetMarkerStyle(8);
  vardata_all->SetMarkerSize(.9);
  vardata_all->SetTitleOffset(1.25,"Y");
  vardata_all->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),"_all.png");
  c0->SaveAs(name);

  // -----------------------------------------------
  // data overlaid to mc
  legge = leg->AddEntry(vardata_30, "data", "p");

  double themax_30 = vardata_30->GetMaximum();
  if(var_30[0]->GetMaximum()>themax_30) themax_30 = var_30[0]->GetMaximum();
  if (themax_30>0) {  
    if ( variableData == "etaphot1" || variableData == "phiphot1" ) 
      vardata_30->SetMaximum(themax_30*2.0);
    else
      vardata_30->SetMaximum(themax_30*1.1);
    vardata_30->SetMinimum(0.000001);
  } else {
    vardata_30->SetMaximum(0.00001);
  }

  double themax_50 = vardata_50->GetMaximum();
  if(var_50[0]->GetMaximum()>themax_50) themax_50 = var_50[0]->GetMaximum();
  if (themax_50>0) {  
    if ( variableData == "etaphot1" || variableData == "phiphot1" ) 
      vardata_50->SetMaximum(themax_50*2.0);
    else
      vardata_50->SetMaximum(themax_50*1.1);
    vardata_50->SetMinimum(0.000001);
  } else {
    vardata_50->SetMaximum(0.00001);
  }

  double themax_75 = vardata_75->GetMaximum();
  if(var_75[0]->GetMaximum()>themax_75) themax_75 = var_75[0]->GetMaximum();
  if (themax_75>0) {  
    if ( variableData == "etaphot1" || variableData == "phiphot1" ) 
      vardata_75->SetMaximum(themax_75*2.0);
    else
      vardata_75->SetMaximum(themax_75*1.1);
    vardata_75->SetMinimum(0.000001);
  } else {
    vardata_75->SetMaximum(0.00001);
  }

  double themax_90 = vardata_90->GetMaximum();
  if(var_90[0]->GetMaximum()>themax_90) themax_90 = var_90[0]->GetMaximum();
  if (themax_90>0) {
    if ( variableData == "etaphot1" || variableData == "phiphot1" ) 
      vardata_90->SetMaximum(themax_90*2.0);
    else
      vardata_90->SetMaximum(themax_90*1.1);
    vardata_90->SetMinimum(0.000001);
  } else {
    vardata_90->SetMaximum(0.00001);
  }

  double themax_all = vardata_all->GetMaximum();
  if(var_all_0->GetMaximum()>themax_all) themax_all = var_all_0->GetMaximum();
  if (themax_all>0) {
    if ( variableData == "etaphot1" || variableData == "phiphot1" ) 
      vardata_all->SetMaximum(themax_all*2.0);
    else
      vardata_all->SetMaximum(themax_all*1.1);
    vardata_all->SetMinimum(0.000001);
  } else {
    vardata_all->SetMaximum(0.00001);
  }

  for(int ii=0; ii<2; ii++) var_30[ii]->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var_50[ii]->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var_75[ii]->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var_90[ii]->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var_all_0->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var_all_1->SetMinimum(0.000001);

  //
  vardata_30->Draw("pe");
  var_30[0]->Draw("samehist");
  var_30[1]->Draw("samehist");
  leg->Draw();
  vardata_30->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_30.root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_30.png");
  c0->SaveAs(name);
  //
  vardata_50->Draw("pe");
  var_50[0]->Draw("samehist");
  var_50[1]->Draw("samehist");
  leg->Draw();
  vardata_50->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_50.root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_50.png");
  c0->SaveAs(name);
  //
  vardata_75->Draw("pe");
  var_75[0]->Draw("samehist");
  var_75[1]->Draw("samehist");
  leg->Draw();
  vardata_75->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_75.root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_75.png");
  c0->SaveAs(name);
  //
  vardata_90->Draw("pe");
  var_90[0]->Draw("samehist");
  var_90[1]->Draw("samehist");
  leg->Draw();
  vardata_90->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_90.root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_90.png");
  c0->SaveAs(name);
  //
  vardata_all->Draw("pe");
  var_all_0->Draw("samehist");
  var_all_1->Draw("samehist");
  leg->Draw();
  vardata_all->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_all.root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),"_all.png");
  c0->SaveAs(name);

  // -------------------------------------------------------------------------
  sprintf(name,"results_gammaJ/yields.txt");
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
  outfile << "# events QCD, 20-30 = "       << n_mc_2012[0]  << endl;
  outfile << "# events QCD, 30-80 = "       << n_mc_2012[1]  << endl;
  outfile << "# events QCD, 80-170 = "      << n_mc_2012[2]  << endl;
  outfile << "# events QCD, 170-250 = "     << n_mc_2012[3]  << endl;
  outfile << "# events QCD, 250-350 = "     << n_mc_2012[4]  << endl;
  outfile << "# events QCD, >350 = "        << n_mc_2012[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << n_mc_2012[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << n_mc_2012[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << n_mc_2012[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << n_mc_2012[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << n_mc_2012[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << n_mc_2012[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << n_mc_2012[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << n_mc_2012[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << n_mc_2012[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << n_mc_2012[15] << endl;
  outfile << endl;
  outfile << "N of selected events, HLT = 30 (not scaled for lumi)"     << endl;  
  outfile << "########################################################" << endl;
  outfile << "# events QCD, 20-30 = "       << num_uns_mc_2012_30[0]  << endl;
  outfile << "# events QCD, 30-80 = "       << num_uns_mc_2012_30[1]  << endl;
  outfile << "# events QCD, 80-170 = "      << num_uns_mc_2012_30[2]  << endl;
  outfile << "# events QCD, 170-250 = "     << num_uns_mc_2012_30[3]  << endl;
  outfile << "# events QCD, 250-350 = "     << num_uns_mc_2012_30[4]  << endl;
  outfile << "# events QCD, >350 = "        << num_uns_mc_2012_30[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << num_uns_mc_2012_30[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << num_uns_mc_2012_30[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << num_uns_mc_2012_30[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << num_uns_mc_2012_30[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << num_uns_mc_2012_30[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << num_uns_mc_2012_30[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << num_uns_mc_2012_30[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << num_uns_mc_2012_30[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << num_uns_mc_2012_30[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << num_uns_mc_2012_30[15] << endl;
  outfile << "ndata = " << num_data_30 << endl;
  outfile << endl;
  outfile << "N of selected events, HLT = 50 (not scaled for lumi)"     << endl;  
  outfile << "########################################################" << endl;
  outfile << "# events QCD, 20-30 = "       << num_uns_mc_2012_50[0]  << endl;
  outfile << "# events QCD, 30-80 = "       << num_uns_mc_2012_50[1]  << endl;
  outfile << "# events QCD, 80-170 = "      << num_uns_mc_2012_50[2]  << endl;
  outfile << "# events QCD, 170-250 = "     << num_uns_mc_2012_50[3]  << endl;
  outfile << "# events QCD, 250-350 = "     << num_uns_mc_2012_50[4]  << endl;
  outfile << "# events QCD, >350 = "        << num_uns_mc_2012_50[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << num_uns_mc_2012_50[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << num_uns_mc_2012_50[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << num_uns_mc_2012_50[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << num_uns_mc_2012_50[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << num_uns_mc_2012_50[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << num_uns_mc_2012_50[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << num_uns_mc_2012_50[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << num_uns_mc_2012_50[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << num_uns_mc_2012_50[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << num_uns_mc_2012_50[15] << endl;
  outfile << "ndata = " << num_data_50 << endl;
  outfile << endl;
  outfile << "N of selected events, HLT = 75 (not scaled for lumi)"     << endl;  
  outfile << "########################################################" << endl;
  outfile << "# events QCD, 20-30 = "       << num_uns_mc_2012_75[0]  << endl;
  outfile << "# events QCD, 30-80 = "       << num_uns_mc_2012_75[1]  << endl;
  outfile << "# events QCD, 80-170 = "      << num_uns_mc_2012_75[2]  << endl;
  outfile << "# events QCD, 170-250 = "     << num_uns_mc_2012_75[3]  << endl;
  outfile << "# events QCD, 250-350 = "     << num_uns_mc_2012_75[4]  << endl;
  outfile << "# events QCD, >350 = "        << num_uns_mc_2012_75[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << num_uns_mc_2012_75[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << num_uns_mc_2012_75[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << num_uns_mc_2012_75[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << num_uns_mc_2012_75[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << num_uns_mc_2012_75[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << num_uns_mc_2012_75[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << num_uns_mc_2012_75[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << num_uns_mc_2012_75[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << num_uns_mc_2012_75[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << num_uns_mc_2012_75[15] << endl;
  outfile << "ndata = " << num_data_75 << endl;
  outfile << endl;
  outfile << "N of selected events, HLT = 90 (not scaled for lumi)"     << endl;  
  outfile << "########################################################" << endl;
  outfile << "# events QCD, 20-30 = "       << num_uns_mc_2012_90[0]  << endl;
  outfile << "# events QCD, 30-80 = "       << num_uns_mc_2012_90[1]  << endl;
  outfile << "# events QCD, 80-170 = "      << num_uns_mc_2012_90[2]  << endl;
  outfile << "# events QCD, 170-250 = "     << num_uns_mc_2012_90[3]  << endl;
  outfile << "# events QCD, 250-350 = "     << num_uns_mc_2012_90[4]  << endl;
  outfile << "# events QCD, >350 = "        << num_uns_mc_2012_90[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << num_uns_mc_2012_90[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << num_uns_mc_2012_90[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << num_uns_mc_2012_90[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << num_uns_mc_2012_90[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << num_uns_mc_2012_90[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << num_uns_mc_2012_90[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << num_uns_mc_2012_90[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << num_uns_mc_2012_90[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << num_uns_mc_2012_90[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << num_uns_mc_2012_90[15] << endl;
  outfile << "ndata = " << num_data_90 << endl;
  outfile << endl;

  double num_bkg_30(0), err_num_bkg_30(0);
  double num_bkg_50(0), err_num_bkg_50(0);
  double num_bkg_75(0), err_num_bkg_75(0);
  double num_bkg_90(0), err_num_bkg_90(0);
  double num_mc_total_30[16],num_uns_mc_total_30[16], n_mc_total_30[16], err_num_mc_total_30[16], err_num_uns_mc_total_30[16];
  double num_mc_total_50[16],num_uns_mc_total_50[16], n_mc_total_50[16], err_num_mc_total_50[16], err_num_uns_mc_total_50[16];
  double num_mc_total_75[16],num_uns_mc_total_75[16], n_mc_total_75[16], err_num_mc_total_75[16], err_num_uns_mc_total_75[16];
  double num_mc_total_90[16],num_uns_mc_total_90[16], n_mc_total_90[16], err_num_mc_total_90[16], err_num_uns_mc_total_90[16];
  for (int i=0; i<16; i++){
    if(i<6) num_bkg_30 += num_mc_2012_30[i];
    if(i<6) num_bkg_50 += num_mc_2012_50[i];
    if(i<6) num_bkg_75 += num_mc_2012_75[i];
    if(i<6) num_bkg_90 += num_mc_2012_90[i];
    num_mc_total_30[i] = num_mc_2012_30[i];
    num_mc_total_50[i] = num_mc_2012_50[i];
    num_mc_total_75[i] = num_mc_2012_75[i];
    num_mc_total_90[i] = num_mc_2012_90[i];
    num_uns_mc_total_30[i] = num_uns_mc_2012_30[i];
    num_uns_mc_total_50[i] = num_uns_mc_2012_50[i];
    num_uns_mc_total_75[i] = num_uns_mc_2012_75[i];
    num_uns_mc_total_90[i] = num_uns_mc_2012_90[i];

    err_num_uns_mc_total_30[i] = sqrt(num_uns_mc_total_30[i]);
    err_num_uns_mc_total_50[i] = sqrt(num_uns_mc_total_50[i]);
    err_num_uns_mc_total_75[i] = sqrt(num_uns_mc_total_75[i]);
    err_num_uns_mc_total_90[i] = sqrt(num_uns_mc_total_90[i]);
    if(num_uns_mc_total_30[i]) err_num_mc_total_30[i] = err_num_uns_mc_total_30[i] * num_mc_total_30[i]/num_uns_mc_total_30[i];
    else err_num_mc_total_30[i] = 0;

    if(num_uns_mc_total_50[i]) err_num_mc_total_50[i] = err_num_uns_mc_total_50[i] * num_mc_total_50[i]/num_uns_mc_total_50[i];
    else err_num_mc_total_50[i] = 0;

    if(num_uns_mc_total_75[i]) err_num_mc_total_75[i] = err_num_uns_mc_total_75[i] * num_mc_total_75[i]/num_uns_mc_total_75[i];
    else err_num_mc_total_75[i] = 0;

    if(num_uns_mc_total_90[i]) err_num_mc_total_90[i] = err_num_uns_mc_total_90[i] * num_mc_total_90[i]/num_uns_mc_total_90[i];
    else err_num_mc_total_90[i] = 0;

    n_mc_total_30[i] = n_mc_2012[i] * scale_mc_2012_30[i];
    n_mc_total_50[i] = n_mc_2012[i] * scale_mc_2012_50[i];
    n_mc_total_75[i] = n_mc_2012[i] * scale_mc_2012_75[i];
    n_mc_total_90[i] = n_mc_2012[i] * scale_mc_2012_90[i];
  }

  for (int i=0; i<6; i++){ 
    err_num_bkg_30 = sqrt(err_num_bkg_30*err_num_bkg_30 + err_num_mc_total_30[i]*err_num_mc_total_30[i]);
    err_num_bkg_50 = sqrt(err_num_bkg_50*err_num_bkg_50 + err_num_mc_total_50[i]*err_num_mc_total_50[i]);
    err_num_bkg_75= sqrt(err_num_bkg_75*err_num_bkg_75 + err_num_mc_total_75[i]*err_num_mc_total_75[i]);
    err_num_bkg_90 = sqrt(err_num_bkg_90*err_num_bkg_90 + err_num_mc_total_90[i]*err_num_mc_total_90[i]);
  }
  
  outfile << endl;
  outfile << "final numbers, HLT = 30" << endl;
  outfile << "nallbkg        = " << num_bkg_30 << " +/- " << err_num_bkg_30 << endl;
  outfile << "QCD, 20-30     = " << num_mc_total_30[0]  << " +/- " << err_num_mc_total_30[0]  << endl;
  outfile << "QCD, 30-80     = " << num_mc_total_30[1]  << " +/- " << err_num_mc_total_30[1]  << endl;
  outfile << "QCD, 80-170    = " << num_mc_total_30[2]  << " +/- " << err_num_mc_total_30[2]  << endl;
  outfile << "QCD, 170-250   = " << num_mc_total_30[3]  << " +/- " << err_num_mc_total_30[3]  << endl;
  outfile << "QCD, 250-350   = " << num_mc_total_30[4]  << " +/- " << err_num_mc_total_30[4]  << endl;
  outfile << "QCD, >350      = " << num_mc_total_30[5]  << " +/- " << err_num_mc_total_30[5]  << endl;
  outfile << "G+j, 0-15      = " << num_mc_total_30[6]  << " +/- " << err_num_mc_total_30[6]  << endl;
  outfile << "G+j, 15-30     = " << num_mc_total_30[7]  << " +/- " << err_num_mc_total_30[7]  << endl;
  outfile << "G+j, 30-50     = " << num_mc_total_30[8]  << " +/- " << err_num_mc_total_30[8]  << endl;
  outfile << "G+j, 50-80     = " << num_mc_total_30[9]  << " +/- " << err_num_mc_total_30[9]  << endl;
  outfile << "G+j, 80-120    = " << num_mc_total_30[10] << " +/- " << err_num_mc_total_30[10]  << endl;
  outfile << "G+j, 120-170   = " << num_mc_total_30[11] << " +/- " << err_num_mc_total_30[11]  << endl;
  outfile << "G+j, 170-300   = " << num_mc_total_30[12] << " +/- " << err_num_mc_total_30[12]  << endl;
  outfile << "G+j, 470-800   = " << num_mc_total_30[13] << " +/- " << err_num_mc_total_30[13]  << endl;
  outfile << "G+j, 800-1400  = " << num_mc_total_30[14] << " +/- " << err_num_mc_total_30[14]  << endl;
  outfile << "G+j, 1400-1800 = " << num_mc_total_30[15] << " +/- " << err_num_mc_total_30[15]  << endl;
  outfile << endl;          
  outfile << endl;
  outfile << "eff gamma+jets = "  << (num_mc_total_30[6] + num_mc_total_30[7] + num_mc_total_30[8] + num_mc_total_30[9] + num_mc_total_30[10] + num_mc_total_30[11] + num_mc_total_30[12] + num_mc_total_30[13] + num_mc_total_30[14] + num_mc_total_30[15])/(n_mc_total_30[6] + n_mc_total_30[7] + n_mc_total_30[8] + n_mc_total_30[9] + n_mc_total_30[10] + n_mc_total_30[11] + n_mc_total_30[12] + n_mc_total_30[13] + n_mc_total_30[14] + n_mc_total_30[15]) << endl;  
  
  outfile << endl;
  outfile << "final numbers, HLT = 50" << endl;
  outfile << "nallbkg        = " << num_bkg_50 << " +/- " << err_num_bkg_50 << endl;
  outfile << "QCD, 20-30     = " << num_mc_total_50[0]  << " +/- " << err_num_mc_total_50[0]  << endl;
  outfile << "QCD, 30-80     = " << num_mc_total_50[1]  << " +/- " << err_num_mc_total_50[1]  << endl;
  outfile << "QCD, 80-170    = " << num_mc_total_50[2]  << " +/- " << err_num_mc_total_50[2]  << endl;
  outfile << "QCD, 170-250   = " << num_mc_total_50[3]  << " +/- " << err_num_mc_total_50[3]  << endl;
  outfile << "QCD, 250-350   = " << num_mc_total_50[4]  << " +/- " << err_num_mc_total_50[4]  << endl;
  outfile << "QCD, >350      = " << num_mc_total_50[5]  << " +/- " << err_num_mc_total_50[5]  << endl;
  outfile << "G+j, 0-15      = " << num_mc_total_50[6]  << " +/- " << err_num_mc_total_50[6]  << endl;
  outfile << "G+j, 15-30     = " << num_mc_total_50[7]  << " +/- " << err_num_mc_total_50[7]  << endl;
  outfile << "G+j, 30-50     = " << num_mc_total_50[8]  << " +/- " << err_num_mc_total_50[8]  << endl;
  outfile << "G+j, 50-80     = " << num_mc_total_50[9]  << " +/- " << err_num_mc_total_50[9]  << endl;
  outfile << "G+j, 80-120    = " << num_mc_total_50[10] << " +/- " << err_num_mc_total_50[10]  << endl;
  outfile << "G+j, 120-170   = " << num_mc_total_50[11] << " +/- " << err_num_mc_total_50[11]  << endl;
  outfile << "G+j, 170-300   = " << num_mc_total_50[12] << " +/- " << err_num_mc_total_50[12]  << endl;
  outfile << "G+j, 470-800   = " << num_mc_total_50[13] << " +/- " << err_num_mc_total_50[13]  << endl;
  outfile << "G+j, 800-1400  = " << num_mc_total_50[14] << " +/- " << err_num_mc_total_50[14]  << endl;
  outfile << "G+j, 1400-1800 = " << num_mc_total_50[15] << " +/- " << err_num_mc_total_50[15]  << endl;
  outfile << endl;          
  outfile << endl;
  outfile << "eff gamma+jets = "  << (num_mc_total_50[6] + num_mc_total_50[7] + num_mc_total_50[8] + num_mc_total_50[9] + num_mc_total_50[10] + num_mc_total_50[11] + num_mc_total_50[12] + num_mc_total_50[13] + num_mc_total_50[14] + num_mc_total_50[15])/(n_mc_total_50[6] + n_mc_total_50[7] + n_mc_total_50[8] + n_mc_total_50[9] + n_mc_total_50[10] + n_mc_total_50[11] + n_mc_total_50[12] + n_mc_total_50[13] + n_mc_total_50[14] + n_mc_total_50[15]) << endl;  
  
  outfile << endl;
  outfile << "final numbers, HLT = 75" << endl;
  outfile << "nallbkg        = " << num_bkg_75 << " +/- " << err_num_bkg_75 << endl;
  outfile << "QCD, 20-30     = " << num_mc_total_75[0]  << " +/- " << err_num_mc_total_75[0]  << endl;
  outfile << "QCD, 30-80     = " << num_mc_total_75[1]  << " +/- " << err_num_mc_total_75[1]  << endl;
  outfile << "QCD, 80-170    = " << num_mc_total_75[2]  << " +/- " << err_num_mc_total_75[2]  << endl;
  outfile << "QCD, 170-250   = " << num_mc_total_75[3]  << " +/- " << err_num_mc_total_75[3]  << endl;
  outfile << "QCD, 250-350   = " << num_mc_total_75[4]  << " +/- " << err_num_mc_total_75[4]  << endl;
  outfile << "QCD, >350      = " << num_mc_total_75[5]  << " +/- " << err_num_mc_total_75[5]  << endl;
  outfile << "G+j, 0-15      = " << num_mc_total_75[6]  << " +/- " << err_num_mc_total_75[6]  << endl;
  outfile << "G+j, 15-30     = " << num_mc_total_75[7]  << " +/- " << err_num_mc_total_75[7]  << endl;
  outfile << "G+j, 30-50     = " << num_mc_total_75[8]  << " +/- " << err_num_mc_total_75[8]  << endl;
  outfile << "G+j, 50-80     = " << num_mc_total_75[9]  << " +/- " << err_num_mc_total_75[9]  << endl;
  outfile << "G+j, 80-120    = " << num_mc_total_75[10] << " +/- " << err_num_mc_total_75[10]  << endl;
  outfile << "G+j, 120-170   = " << num_mc_total_75[11] << " +/- " << err_num_mc_total_75[11]  << endl;
  outfile << "G+j, 170-300   = " << num_mc_total_75[12] << " +/- " << err_num_mc_total_75[12]  << endl;
  outfile << "G+j, 470-800   = " << num_mc_total_75[13] << " +/- " << err_num_mc_total_75[13]  << endl;
  outfile << "G+j, 800-1400  = " << num_mc_total_75[14] << " +/- " << err_num_mc_total_75[14]  << endl;
  outfile << "G+j, 1400-1800 = " << num_mc_total_75[15] << " +/- " << err_num_mc_total_75[15]  << endl;
  outfile << endl;          
  outfile << endl;
  outfile << "eff gamma+jets = "  << (num_mc_total_75[6] + num_mc_total_75[7] + num_mc_total_75[8] + num_mc_total_75[9] + num_mc_total_75[10] + num_mc_total_75[11] + num_mc_total_75[12] + num_mc_total_75[13] + num_mc_total_75[14] + num_mc_total_75[15])/(n_mc_total_75[6] + n_mc_total_75[7] + n_mc_total_75[8] + n_mc_total_75[9] + n_mc_total_75[10] + n_mc_total_75[11] + n_mc_total_75[12] + n_mc_total_75[13] + n_mc_total_75[14] + n_mc_total_75[15]) << endl;  
  
  outfile << endl;
  outfile << "final numbers, HLT = 90" << endl;
  outfile << "nallbkg        = " << num_bkg_90 << " +/- " << err_num_bkg_90 << endl;
  outfile << "QCD, 20-30     = " << num_mc_total_90[0]  << " +/- " << err_num_mc_total_90[0]  << endl;
  outfile << "QCD, 30-80     = " << num_mc_total_90[1]  << " +/- " << err_num_mc_total_90[1]  << endl;
  outfile << "QCD, 80-170    = " << num_mc_total_90[2]  << " +/- " << err_num_mc_total_90[2]  << endl;
  outfile << "QCD, 170-250   = " << num_mc_total_90[3]  << " +/- " << err_num_mc_total_90[3]  << endl;
  outfile << "QCD, 250-350   = " << num_mc_total_90[4]  << " +/- " << err_num_mc_total_90[4]  << endl;
  outfile << "QCD, >350      = " << num_mc_total_90[5]  << " +/- " << err_num_mc_total_90[5]  << endl;
  outfile << "G+j, 0-15      = " << num_mc_total_90[6]  << " +/- " << err_num_mc_total_90[6]  << endl;
  outfile << "G+j, 15-30     = " << num_mc_total_90[7]  << " +/- " << err_num_mc_total_90[7]  << endl;
  outfile << "G+j, 30-50     = " << num_mc_total_90[8]  << " +/- " << err_num_mc_total_90[8]  << endl;
  outfile << "G+j, 50-80     = " << num_mc_total_90[9]  << " +/- " << err_num_mc_total_90[9]  << endl;
  outfile << "G+j, 80-120    = " << num_mc_total_90[10] << " +/- " << err_num_mc_total_90[10]  << endl;
  outfile << "G+j, 120-170   = " << num_mc_total_90[11] << " +/- " << err_num_mc_total_90[11]  << endl;
  outfile << "G+j, 170-300   = " << num_mc_total_90[12] << " +/- " << err_num_mc_total_90[12]  << endl;
  outfile << "G+j, 470-800   = " << num_mc_total_90[13] << " +/- " << err_num_mc_total_90[13]  << endl;
  outfile << "G+j, 800-1400  = " << num_mc_total_90[14] << " +/- " << err_num_mc_total_90[14]  << endl;
  outfile << "G+j, 1400-1800 = " << num_mc_total_90[15] << " +/- " << err_num_mc_total_90[15]  << endl;
  outfile << endl;          
  outfile << endl;
  outfile << "eff gamma+jets = "  << (num_mc_total_90[6] + num_mc_total_90[7] + num_mc_total_90[8] + num_mc_total_90[9] + num_mc_total_90[10] + num_mc_total_90[11] + num_mc_total_90[12] + num_mc_total_90[13] + num_mc_total_90[14] + num_mc_total_90[15])/(n_mc_total_90[6] + n_mc_total_90[7] + n_mc_total_90[8] + n_mc_total_90[9] + n_mc_total_90[10] + n_mc_total_90[11] + n_mc_total_90[12] + n_mc_total_90[13] + n_mc_total_90[14] + n_mc_total_90[15]) << endl;  
  cout << endl;
  outfile << endl;
  outfile.close();
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
  
  delete data;
  
  for(int i=0; i<16; i++){
    delete mc_2012_fill_30[i];
    delete mc_2012_fill_50[i];
    delete mc_2012_fill_75[i];
    delete mc_2012_fill_90[i];
   delete mc_2012[i];
  }
  
  vector<double> values;
  
  return values;
}








