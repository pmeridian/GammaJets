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

vector <double> finalize2012_gammaJets(double int_exp_2012, double pt1=50, int eb = 1, int r9 = 1, string variableMC = "massgg", string variableData = "massgg", int nbin = 200, double min = 90, double max = 190, string axis = "m(#gamma#gamma)[GeV]"){
  
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
  string mcnames[20];
  mcnames[0]  = "box, 10-25";
  mcnames[1]  = "box, 25-250";
  mcnames[2]  = "box, >250";
  mcnames[3]  = "diphoton";
  mcnames[4]  = "qcdpt>40";
  mcnames[5]  = "qcd30<pt<40";
  mcnames[6]  = "dy";
  mcnames[7]  = "WlnuG";
  mcnames[8]  = "ZllG";
  mcnames[9]  = "ggWminus";
  mcnames[10] = "ggWplus";
  mcnames[11] = "ggZ";
  mcnames[12] = "ggtt";
  mcnames[13] = "ttjets";
  mcnames[14] = "Wjets";
  mcnames[15] = "WW";
  mcnames[16] = "WZ";
  mcnames[17] = "ZZ";
  mcnames[18] = "gjet, 20-40";
  mcnames[19] = "gjet, >40";

  TFile* mc_2012[20];            // [26] = MC samples

  TString redntpDir= "/xrootdfs/cms/local/crovelli/GammaJets/reduced";

  // full 2012                                     
  // TFile* data = TFile::Open(redntpDir+"/redntp.53xv1_data_lisbon.provaGammaJets_v1/merged/redntp_Photon-Run2012A-13Jul2012-v1.root");

  // mc signal and backgrounds   
  if(int_exp_2012>0){
    
    // box samples                                                                                              
    mc_2012[0] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_DiPhotonBox_Pt-10To25_8TeV-pythia6.root");
    mc_2012[1] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_DiPhotonBox_Pt-25To250_8TeV-pythia6.root");
    mc_2012[2] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_DiPhotonBox_Pt-250ToInf_8TeV-pythia6.root");

    // diphoton jets samples 
    mc_2012[3] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_DiPhotonJets_8TeV-madgraph-tarball-v2.root");

    // qcd
    mc_2012[4] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6.root");
    mc_2012[5] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6.root");

    // drell yan samples 
    mc_2012[6] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root");

    // W+gamma, W->lnu 
    mc_2012[7] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WGToLNuG_TuneZ2star_8TeV-madgraph-tauola.root");

    // Z+gamma, Z->ll
    mc_2012[8]  = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_ZG_Inclusive_8TeV-madgraph.root");

    // W-gg                
    mc_2012[9]  = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WmGG_cmkuo.root");
    // W+ gg               
    mc_2012[10] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WpGG-cmkuo.root");
    // Zgg                 
    mc_2012[11] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_ZGG-cmkuo.root");
    // ttgg                
    mc_2012[12] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_TTbarGG_0Jet_S1-cmkuo.root");

    // TTjets                                                                                              
    mc_2012[13] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_TTJets_TuneZ2star_8TeV-madgraph-tauola.root");
    // Wjets                                                                                                      
    mc_2012[14] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WJetsToLNu_TuneZ2Star_8TeV-madgraph.root");

    // WW                                                                                                                
    mc_2012[15] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WW_TuneZ2star_8TeV_pythia6_tauola.root");
    // WZ                                                                                                                
    mc_2012[16] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_WZ_TuneZ2star_8TeV_pythia6_tauola.root");
    // ZZ
    mc_2012[17] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_ZZ_TuneZ2star_8TeV_pythia6_tauola.root");

    // gjet samples 
    mc_2012[18] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6.root");
    mc_2012[19] = TFile::Open(redntpDir+"/redntp.52xv5_lisbon.provaGammaJets_v1/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6.root");
  }
  
  // k factors - same scale factors for 7 TeV and 8 TeV
  double kfactordiphot = 1.3;                // for prompt and box 
  double kfactordiphotmadgraph = 1.15;       // for madgraph di-jets
  double kfactorgamjet = 1.3;
  double kfactordy = 1.15;
  double kfactor1 = 1;

  // cross sections at 8 TeV and scaling
  double cross_mc[20];
  cross_mc[0]  = 424.8 * kfactordiphot;                 // box                       https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/731.html
  cross_mc[1]  = 15.54 * kfactordiphot;                 // box                          "
  cross_mc[2]  = 0.0011805 * kfactordiphot;             // box                          "
  cross_mc[3]  = 81. * kfactordiphotmadgraph;           // madgraph                     "
  cross_mc[4]  = 0.000235 * 5.195e+07 * kfactor1;       // qcd pt>40                    "
  cross_mc[5]  = 0.002175 * 2.365e+07 * kfactor1;       // qcd 30<pt<40                 " 
  cross_mc[6]  = 2950. * kfactordy;                     // drell yan                    "          
  cross_mc[7]  = 322.356 * kfactor1;       // Wgamma, W->lnu - da AN FP    (461.6 secondo prep) 
  cross_mc[8]  = 181.338 * kfactor1;       // Zgamma, inclusive - da AN FP (132.6 secondo prep)
  cross_mc[9]  = 0.0504 * kfactor1;        // W-gg  - da AN FP
  cross_mc[10] = 0.0667 * kfactor1;        // W+gg  - da AN FP
  cross_mc[11] = 0.068 * kfactor1;         // Z+gg  - da AN FP
  cross_mc[12] = 0.001316 * kfactor1;      // tt+gg - da AN FP
  cross_mc[13] = 225.197 * kfactor1;       // tt+jets; da twiki https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat8TeV?skin=drupal   
  cross_mc[14] = 37509. * kfactor1;        // W+jets; da spreadsheet di HWW
  cross_mc[15] = 57.07 * kfactor1;         // WW; da spreadsheet di HWW
  cross_mc[16] = 22.45 * kfactor1;         // WZ; da spreadsheet di HWW
  cross_mc[17] = 9.03 * kfactor1;          // ZZ; da spreadsheet di HWW
  cross_mc[18] = 0.001835 * 81930.0 * kfactorgamjet;    // gjet                      https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/731.html  
  cross_mc[19] = 0.05387 * 8884.0 * kfactorgamjet;      // gjet                      "

  // getting the number of original events in each sample (processed with CMSSW)
  int n_mc_2012[20];   
  for(int i=0; i<20; i++){
    n_mc_2012[i] = 0;
    if(int_exp_2012>0) n_mc_2012[i] = ((TH1D*)mc_2012[i]->Get("ptphotgen1"))->GetEntries();  
  }

  // setting the scaling factor to actual lumi 
  double scale_mc_2012[20];
  for(int i=0; i<20; i++){
    scale_mc_2012[i] = 0; 
    if(int_exp_2012>0) { 
      scale_mc_2012[i] = cross_mc[i] * int_exp_2012 / n_mc_2012[i];
    }
  }

  // char for output name
  char name[1000];
  
  // output root file
  sprintf(name,"results_gammaJ/histo.root");
  TFile * hOutputFile = new TFile(name, "RECREATE" ) ;

  // histograms needed by the machinery
  TH1D* vardata   = new TH1D("vardata",  "vardata",  nbin,min,max);
  vardata->Sumw2();

  TH1D* var_mc_2012[20];     // 20 = MC samples we have 
  TH1D* var[9];              // 9  = number of species
  TH1D* var2[2];             // 2  = signal and backgrounds

  for (int i=0; i<9; i++) {
    sprintf(name,"%s%d","var",i);
    var[i] = new TH1D(name,name,nbin,min,max);
    var[i]->Sumw2();          
  }

  for (int i=0; i<2; i++) {
    sprintf(name,"%s%d","var",i);
    var2[i] = new TH1D(name,name,nbin,min,max);
    var2[i]->Sumw2();          
  }

  for (int i=0; i<20; i++) {
    sprintf(name,"%s%d","var_mc_2012_",i);
    var_mc_2012[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012[i]->Sumw2();  
  }

  // creating the fillers and setting cuts
  // fillPlot2012_gammaJets data_fill((TTree*)data->Get("AnaTree"));
  // data_fill.Setcuts(pt1,eb,r9);  
  
  fillPlot2012_gammaJets* mc_2012_fill[20];
  for (int i=0; i<20; i++){
    if(int_exp_2012>0) mc_2012_fill[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012>0) mc_2012_fill[i]->Setcuts(pt1,eb,r9);
    
    mc_2012_fill[i]->DoPuReweight();
  }

  // filling histograms
  /*
  std::cout << " ++++++++++++++ DATA ++++++++++++++++" << std::endl;
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events" <<  endl;
  sprintf(name,"results_gammaJ/events.txt");
  data_fill.Writetxt(name);
  sprintf(name,"results_gammaJ/events.root");
  data_fill.WriteRoot(name);

  vardata->Add(data_fill.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata->GetEntries() << std::endl;
  */

  std::cout << " ++++++++++++++ MC ++++++++++++++++" << std::endl;
  for (int i=0; i<20; i++){ 
    sprintf(name,"%s%s",mcnames[i].c_str()," 2012");
    if(int_exp_2012>0) {
      cout << "running over " << ((TTree*)mc_2012[i]->Get("AnaTree"))->GetEntries("") << " " << name << " events" <<  endl;   
      sprintf(name,"%s%s%s","results_gammaJ/events_",mcnames[i].c_str(),"_2012.root");
      mc_2012_fill[i]->WriteRoot(name);             
      var_mc_2012[i]->Add( mc_2012_fill[i]->Plot(variableMC, name, nbin, min, max, i) );  
      std::cout << "Selected events on mc2012 " << name << " " << var_mc_2012[i]->GetEntries() << std::endl;
    }
  }

  // scale mc to equivalent lumi
  for (int i=0; i<20; i++){
    if(int_exp_2012>0) var_mc_2012[i]->Scale(scale_mc_2012[i]);  
  }

  // counting number of events passing selection (scaled)   
  double num_mc_2012[20];     
  double num_uns_mc_2012[20]; 

  for (int i=0; i<20; i++){ 
    num_mc_2012[i] = 0;
    if(int_exp_2012>0) num_mc_2012[i] = var_mc_2012[i]->Integral();        
    // 
    num_uns_mc_2012[i] = 0;
    if(int_exp_2012>0) num_uns_mc_2012[i] = var_mc_2012[i]->GetEntries();  
  }

  // scale control sample
  // double num_data = vardata->Integral();

  for (int j=0; j<9; j++){   
    int offset(0);
    if(j>0) offset = 1;    // to add gamma+jets contributions up 
    if(j>1) offset = 3;    // to add dibosons contribuions up
    if(j>2) offset = 4;    // to add Wj+ttj contribuions up
    if(j>3) offset = 7;    // to add Wgg,Zgg,ttgg contributions up  
    if(j>7) offset = 8;    // to add QCD contributions up  
    for (int k=0 ; k<20-j-offset; k++){   
      if(int_exp_2012>0) var[j]->Add(var_mc_2012[k]);
    }	
  }

  for (int j=0; j<2; j++){   
    int offset(0);
    if(j>0) offset = 1;    // to add gamma+jets contributions up 
    for (int k=0 ; k<20-j-offset; k++){   
      if(int_exp_2012>0) var2[j]->Add(var_mc_2012[k]);
    }	
  }

  // final plots
  char ytitle[100];
  sprintf(ytitle,"%s%d%s","N_{ev}/",int(int_exp_2012),"pb^{-1}");
  for(int i=0; i<9; i++){
    var[i]->SetTitle("");
    var[i]->SetStats(0);
    var[i]->SetTitleOffset(1.25,"Y");
    var[i]->SetYTitle(ytitle);
    var[i]->SetXTitle(axis.c_str());
    var[i]->SetLineColor(kBlack);
    var[i]->SetLineWidth(2);
  }
  for(int i=0; i<2; i++){
    var2[i]->SetTitle("");
    var2[i]->SetStats(0);
    var2[i]->SetTitleOffset(1.25,"Y");
    var2[i]->SetYTitle(ytitle);
    var2[i]->SetXTitle(axis.c_str());
    var2[i]->SetLineColor(kBlack);
    var2[i]->SetLineWidth(2);
  }


  
  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  legge = leg->AddEntry(var[0], "gamma+jets", "f");
  legge = leg->AddEntry(var[1], "VV", "f");
  legge = leg->AddEntry(var[2], "Wjets,ttjets", "f");
  legge = leg->AddEntry(var[3], "W,Z,ttgg", "f");
  legge = leg->AddEntry(var[4], "Zgamma", "f");
  legge = leg->AddEntry(var[5], "Wgamma", "f");  
  legge = leg->AddEntry(var[6], "DY", "f");
  legge = leg->AddEntry(var[7], "QCD", "f");
  legge = leg->AddEntry(var[8], "di-gamma", "f");

  // mc only plot: data vs background
  var[0]->SetFillColor(kYellow);
  var[0]->Draw("hist");
  var[1]->SetFillColor(6);
  var[1]->Draw("samehist");
  var[2]->SetFillColor(2);
  var[2]->Draw("samehist");
  var[3]->SetFillColor(38);
  var[3]->Draw("samehist");
  var[4]->SetFillColor(46);
  var[4]->Draw("samehist");
  var[5]->SetFillColor(16);
  var[5]->Draw("samehist");
  var[6]->SetFillColor(4);
  var[6]->Draw("samehist");
  var[7]->SetFillColor(3);   
  var[7]->Draw("samehist");
  var[8]->SetFillColor(64);  
  var[8]->Draw("samehist");

  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),".png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),".root");
  c0->SaveAs(name);

  // mc only plot (2 classes only): data vs background
  TLegendEntry *legge2;
  TLegend *leg2;
  leg2 = new TLegend(0.6,0.6,0.85,0.85);
  leg2->SetFillStyle(0); leg2->SetBorderSize(0); leg2->SetTextSize(0.05);
  leg2->SetFillColor(0);
  legge2 = leg2->AddEntry(var2[0], "gamma+jets",      "f");
  legge2 = leg2->AddEntry(var2[1], "all backgrounds", "f");
  
  var2[0]->SetFillColor(kYellow);
  var2[0]->Draw("hist");
  var2[1]->SetFillColor(kGreen);
  var2[1]->Draw("samehist");

  leg2->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_signalBackOnly.png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),"_signalBackOnly.root");
  c0->SaveAs(name);


  // data only plot
  /*
  vardata->SetXTitle(axis.c_str());
  vardata->SetTitle("");
  vardata->SetStats(0);
  vardata->SetMarkerStyle(8);
  vardata->SetMarkerSize(.9);
  vardata->SetTitleOffset(1.25,"Y");
  vardata->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),".png");
  c0->SaveAs(name);
  */

  // data overlaid to mc
  legge  = leg->AddEntry(vardata,  "data", "p");
  legge2 = leg2->AddEntry(vardata, "data", "p");

  /*
  double themax =   vardata->GetMaximum();
  if(var[0]->GetMaximum()>themax) themax = var[0]->GetMaximum();
  if (
      variableData == "etaphot1" || variableData == "phiphot1" 
      )
    vardata->SetMaximum(themax*2.0);
  else
    vardata->SetMaximum(themax*1.1);
  
  vardata->SetMinimum(0.000001);
  for(int ii=0; ii<9; ii++) var[ii]->SetMinimum(0.000001);
  var[0]->Draw("samehist");
  var[1]->Draw("samehist");
  var[2]->Draw("samehist");
  var[3]->Draw("samehist");
  var[4]->Draw("samehist");
  var[5]->Draw("samehist");
  var[6]->Draw("samehist");
  var[7]->Draw("samehist");
  var[8]->Draw("samehist");
  leg->Draw();
  vardata->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),".root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),".png");
  c0->SaveAs(name);

  gPad->RedrawAxis();
  TLegendEntry *legge2;
  TLegend *leg2;
  leg2 = new TLegend(0.6,0.65,0.9,0.85);
  leg2->SetFillStyle(0); leg2->SetBorderSize(0); leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  legge2 = leg2->AddEntry(vardata, "default sel.", "p");
  leg2->Draw();
  c0->SaveAs(name);
  */

  sprintf(name,"results_gammaJ/yields.txt");
  ofstream outfile(name);  
  outfile << "####################################" << endl;
  outfile << "CUTS " << endl;
  outfile << "####################################" << endl;
  outfile << "ptphot1 : " << pt1 << endl;
  outfile << "ebcat : " << eb << endl;
  outfile << "r9cat : " << r9 << endl;
  outfile << endl;
  outfile << "####################################" << endl;
  outfile << "N of generated events" << endl;
  outfile << "####################################" << endl;
  outfile << "# events box_2012, 10-25 =     "    << n_mc_2012[0]  << endl;
  outfile << "# events box_2012, 25-250 =    "    << n_mc_2012[1]  << endl;
  outfile << "# events box_2012, >250 =      "    << n_mc_2012[2]  << endl;
  outfile << "# events diphotjet_2012, 10-25 = "  << n_mc_2012[3]  << endl;
  outfile << "# events qcd_2012 =       "         << n_mc_2012[4]  << endl;
  outfile << "# events qcd2_2012 =      "         << n_mc_2012[5]  << endl;
  outfile << "# events dy_2012 =        "         << n_mc_2012[6]  << endl;
  outfile << "# events wgamma_ele_2012 = "        << n_mc_2012[7]  << endl;
  outfile << "# events zgamma_ele_2012 = "        << n_mc_2012[8]  << endl;
  outfile << "# events ggWminus_2012 = "          << n_mc_2012[9]  << endl;
  outfile << "# events ggWplus_2012 = "           << n_mc_2012[10] << endl;
  outfile << "# events ggZ_2012 = "               << n_mc_2012[11] << endl;
  outfile << "# events ggtt_2012 = "              << n_mc_2012[12] << endl;
  outfile << "# events ttjets_2012 = "            << n_mc_2012[13] << endl;
  outfile << "# events Wjets_2012 = "             << n_mc_2012[14] << endl;
  outfile << "# events WW_2012 = "                << n_mc_2012[15] << endl;
  outfile << "# events WZ_2012 = "                << n_mc_2012[16] << endl;
  outfile << "# events ZZ_2012 = "                << n_mc_2012[17] << endl;
  outfile << "# events gjet_2012, 20-40 =      "  << n_mc_2012[18] << endl;
  outfile << "# events gjet_2012, >40 =      "    << n_mc_2012[19] << endl;

  outfile << endl;
  outfile << "N of selected events (not scaled for lumi)" << endl;  
  outfile << "##########################################" << endl;
  outfile << "# events box_2012, 10-25 =     " << num_uns_mc_2012[0]  << endl;
  outfile << "# events box_2012, 25-250 =    " << num_uns_mc_2012[1]  << endl;
  outfile << "# events box_2012, >250 =      " << num_uns_mc_2012[2]  << endl;
  outfile << "# events diphotjet =           " << num_uns_mc_2012[3] << endl;
  outfile << "# events qcd_2012 =            " << num_uns_mc_2012[4] << endl;
  outfile << "# events qcd2_2012 =           " << num_uns_mc_2012[5] << endl;
  outfile << "# events dy_2012 =             " << num_uns_mc_2012[6]  << endl;
  outfile << "# events wgamma_ele_2012 = " << num_uns_mc_2012[7]  << endl;
  outfile << "# events zgamma_ele_2012 = " << num_uns_mc_2012[8]  << endl;
  outfile << "# events ggWminus_2012 = "   << num_uns_mc_2012[9]  << endl;
  outfile << "# events ggWplus_2012 = "    << num_uns_mc_2012[10] << endl;
  outfile << "# events ggZ_2012 = "        << num_uns_mc_2012[11] << endl;
  outfile << "# events ggtt_2012 = "       << num_uns_mc_2012[12] << endl;
  outfile << "# events ttjets_2012 = "     << num_uns_mc_2012[13] << endl;
  outfile << "# events Wjets_2012 = "      << num_uns_mc_2012[14] << endl;
  outfile << "# events WW_2012 = "         << num_uns_mc_2012[15] << endl;
  outfile << "# events WZ_2012 = "         << num_uns_mc_2012[16] << endl;
  outfile << "# events ZZ_2012 = "         << num_uns_mc_2012[17] << endl;
  outfile << "# events gjet_2012, 20-40 =  " << num_uns_mc_2012[18] << endl;
  outfile << "# events gjet_2012, >40 =    " << num_uns_mc_2012[19] << endl;
  outfile << endl;
  outfile << "####################################" << endl;
  outfile << "N of selected events and eff." << endl;
  outfile << "####################################" << endl; 
  // outfile << "ndata      = " << num_data << endl;
  outfile << endl;

  double num_bkg(0), err_num_bkg(0);
  double num_mc_total[20],num_uns_mc_total[20], n_mc_total[20];
  double err_num_mc_total[20],err_num_uns_mc_total[20];
  for (int i=0; i<20; i++){
    if(i<18){  
      num_bkg += num_mc_2012[i];
    }
    num_mc_total[i] = num_mc_2012[i];
    num_uns_mc_total[i] = num_uns_mc_2012[i];
    err_num_uns_mc_total[i] = sqrt(num_uns_mc_total[i]);
    if(num_uns_mc_total[i]) err_num_mc_total[i] = err_num_uns_mc_total[i] * num_mc_total[i]/num_uns_mc_total[i];
    else err_num_mc_total[i] = 0;
    n_mc_total[i] = n_mc_2012[i] * scale_mc_2012[i];
  }
  for (int i=0; i<18; i++){ 
    err_num_bkg = sqrt(err_num_bkg*err_num_bkg + err_num_mc_total[i]*err_num_mc_total[i]);
  }
  
  outfile << "nallbkg      = " << num_bkg << " +/- " << err_num_bkg << endl;
  outfile << "nbox,10-25   = " << num_mc_total[0]  << " +/- " << err_num_mc_total[0]  << endl;
  outfile << "nbox,25-250  = " << num_mc_total[1]  << " +/- " << err_num_mc_total[1]  << endl;
  outfile << "nbox,>250    = " << num_mc_total[2]  << " +/- " << err_num_mc_total[2]  << endl;
  outfile << "ndiphot      = " << num_mc_total[3]  << " +/- " << err_num_mc_total[3]  << endl;
  outfile << "nqcd40       = " << num_mc_total[4]  << " +/- " << err_num_mc_total[4]  << endl;
  outfile << "nqcd30-40    = " << num_mc_total[5]  << " +/- " << err_num_mc_total[5]  << endl;
  outfile << "ndy          = " << num_mc_total[6]  << " +/- " << err_num_mc_total[6]  << endl;
  outfile << "nwg-ele      = " << num_mc_total[7]  << " +/- " << err_num_mc_total[7]  << endl;
  outfile << "nzg-ele      = " << num_mc_total[8]  << " +/- " << err_num_mc_total[8]  << endl;
  outfile << "nggWminus    = " << num_mc_total[9]  << " +/- " << err_num_mc_total[9]  << endl;
  outfile << "nggWplus     = " << num_mc_total[10] << " +/- " << err_num_mc_total[10] << endl;
  outfile << "nggZ         = " << num_mc_total[11] << " +/- " << err_num_mc_total[11] << endl;
  outfile << "nggtt        = " << num_mc_total[12] << " +/- " << err_num_mc_total[12] << endl;
  outfile << "nttjets      = " << num_mc_total[13] << " +/- " << err_num_mc_total[13] << endl;
  outfile << "nWjets       = " << num_mc_total[14] << " +/- " << err_num_mc_total[14] << endl;
  outfile << "nWW          = " << num_mc_total[15] << " +/- " << err_num_mc_total[15] << endl;
  outfile << "nWZ          = " << num_mc_total[16] << " +/- " << err_num_mc_total[16] << endl;
  outfile << "nZZ          = " << num_mc_total[17] << " +/- " << err_num_mc_total[17] << endl;
  outfile << "ngjet,20-40  = " << num_mc_total[18] << " +/- " << err_num_mc_total[18] << endl;
  outfile << "ngjet,>40    = " << num_mc_total[19] << " +/- " << err_num_mc_total[19] << endl;
  outfile << endl;          
  outfile << "eff gamma+jets = "  << (num_mc_total[18] + num_mc_total[19])/ (n_mc_total[18] + n_mc_total[19]) << endl;
  
  outfile << "eff nbox 1     = " << num_mc_total[0] / n_mc_total[0]   << endl;
  outfile << "eff nbox 2     = " << num_mc_total[1] / n_mc_total[1]   << endl;
  outfile << "eff nbox 3     = " << num_mc_total[2] / n_mc_total[2]   << endl;
  outfile << "eff ndiphot    = " << num_mc_total[3] / n_mc_total[3]   << endl;
  outfile << "eff nqcd      = "  << num_mc_total[4] / n_mc_total[4]   << endl;
  outfile << "eff nqcd30-40 = "  << num_mc_total[5] / n_mc_total[5]   << endl;
  outfile << "eff ndy        = " << num_mc_total[6] / n_mc_total[6]   << endl;
  outfile << "eff wgamma-ele = " << num_mc_total[7] / n_mc_total[7]   << endl;
  outfile << "eff zgamma-ele = " << num_mc_total[8] / n_mc_total[8]   << endl;
  outfile << "eff ggWminus = "   << num_mc_total[9] / n_mc_total[9]   << endl;    
  outfile << "eff ggWplus  = "   << num_mc_total[10] / n_mc_total[10] << endl;    
  outfile << "eff ggZ  = "       << num_mc_total[11] / n_mc_total[11] << endl;    
  outfile << "eff ggtt  = "      << num_mc_total[12] / n_mc_total[12] << endl;    
  outfile << "eff ttjets  = "    << num_mc_total[13] / n_mc_total[13] << endl;    
  outfile << "eff Wjets  = "     << num_mc_total[14] / n_mc_total[14] << endl;    
  outfile << "eff WW = "         << num_mc_total[15] / n_mc_total[15] << endl;    
  outfile << "eff WZ = "         << num_mc_total[16] / n_mc_total[16] << endl;    
  outfile << "eff ZZ = "         << num_mc_total[17] / n_mc_total[17] << endl;    
  outfile << "eff ngjet 1    = " << num_mc_total[18] / n_mc_total[18] << endl;
  outfile << "eff ngjet 2    = " << num_mc_total[19] / n_mc_total[19] << endl;
  
  outfile << endl;
  outfile.close();
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
  
  // delete data;
  
  for(int i=0; i<20; i++){
    delete mc_2012_fill[i];
    delete mc_2012[i];
  }
  
  vector<double> values;
  
  return values;
}








