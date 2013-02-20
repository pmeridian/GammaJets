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
  TFile* data = TFile::Open(redntpDir+"/redntp.53xv2_data.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/all2012.root");
  
  // mc signal and backgrounds   
  if(int_exp_2012>0){
    
    // QCD samples
    mc_2012[0] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[1] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[2] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[3] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[4] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    mc_2012[5] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_QCD_Pt_350_EMEnriched_TuneZ2star_8TeV_pythia6.root");
    // gjet samples 
    mc_2012[6]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-0to15_TuneZ2star_8TeV_pythia6.root");
    mc_2012[7]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-15to30_TuneZ2star_8TeV_pythia6.root");
    mc_2012[8]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-30to50_TuneZ2star_8TeV_pythia6.root");
    mc_2012[9]  = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-50to80_TuneZ2star_8TeV_pythia6.root");
    mc_2012[10] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-80to120_TuneZ2star_8TeV_pythia6.root");
    mc_2012[11] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-120to170_TuneZ2star_8TeV_pythia6.root");
    mc_2012[12] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-170to300_TuneZ2star_8TeV_pythia6.root");
    mc_2012[13] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-470to800_TuneZ2star_8TeV_pythia6.root");
    mc_2012[14] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-800to1400_TuneZ2star_8TeV_pythia6.root");
    mc_2012[15] = TFile::Open(redntpDir+"/redntp.53xv2.cicpfloose.noCorrections.GammaJets_newNtuples_v1/merged/redntp_G_Pt-1400to1800_TuneZ2star_8TeV_pythia6.root");
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
    if(int_exp_2012>0) n_mc_2012[i] = ((TH1D*)mc_2012[i]->Get("ptphotgen1"))->GetEntries();  
  }

  // setting the scaling factor to actual lumi 
  double scale_mc_2012[16];
  for(int i=0; i<16; i++){
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

  TH1D* var_mc_2012[16];     // 16 = MC samples we have 
  TH1D* var[2];              // 2  = number of species

  for (int i=0; i<2; i++) {
    sprintf(name,"%s%d","var",i);
    var[i] = new TH1D(name,name,nbin,min,max);
    var[i]->Sumw2();          
  }

  for (int i=0; i<16; i++) {
    sprintf(name,"%s%d","var_mc_2012_",i);
    var_mc_2012[i] = new TH1D(name,name,nbin,min,max);
    var_mc_2012[i]->Sumw2();  
  }

  // creating the fillers and setting cuts
  fillPlot2012_gammaJets data_fill((TTree*)data->Get("AnaTree"));
  data_fill.Setcuts(pt1,eb,r9);  
  
  fillPlot2012_gammaJets* mc_2012_fill[16];
  for (int i=0; i<16; i++){
    if(int_exp_2012>0) mc_2012_fill[i] = new fillPlot2012_gammaJets((TTree*)mc_2012[i]->Get("AnaTree"));   
    if(int_exp_2012>0) mc_2012_fill[i]->Setcuts(pt1,eb,r9);
    mc_2012_fill[i]->DoPuReweight();
  }

  // filling histograms
  std::cout << " ++++++++++++++ DATA ++++++++++++++++" << std::endl;
  cout << "running over " << ((TTree*)data->Get("AnaTree"))->GetEntries("") << " data events" <<  endl;
  sprintf(name,"results_gammaJ/events.txt");
  data_fill.Writetxt(name);
  sprintf(name,"results_gammaJ/events.root");
  data_fill.WriteRoot(name);

  vardata->Add(data_fill.Plot(variableData,"data", nbin, min, max, 100)); 
  std::cout << "Selected events on data " << vardata->GetEntries() << std::endl;

  std::cout << " ++++++++++++++ MC ++++++++++++++++" << std::endl;
  for (int i=0; i<16; i++){ 
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
  for (int i=0; i<16; i++){
    if(int_exp_2012>0) var_mc_2012[i]->Scale(scale_mc_2012[i]);  
  }

  // counting number of events passing selection (scaled)   
  double num_mc_2012[16];     
  double num_uns_mc_2012[16]; 

  for (int i=0; i<16; i++){ 
    num_mc_2012[i] = 0;
    if(int_exp_2012>0) num_mc_2012[i] = var_mc_2012[i]->Integral();        
    // 
    num_uns_mc_2012[i] = 0;
    if(int_exp_2012>0) num_uns_mc_2012[i] = var_mc_2012[i]->GetEntries();  
  }

  // scale control sample
  double num_data = vardata->Integral();

  for (int j=0; j<2; j++){   
    int offset(0);
    if(j>0) offset = 9;    // to add gamma+jets contributions up 
    for (int k=0 ; k<16-j-offset; k++){   
      if(int_exp_2012>0) var[j]->Add(var_mc_2012[k]);
    }	
  }

  // final plots
  char ytitle[100];
  sprintf(ytitle,"%s%d%s","N_{ev}/",int(int_exp_2012),"pb^{-1}");
  for(int i=0; i<2; i++){
    var[i]->SetTitle("");
    var[i]->SetStats(0);
    var[i]->SetTitleOffset(1.25,"Y");
    var[i]->SetYTitle(ytitle);
    var[i]->SetXTitle(axis.c_str());
    var[i]->SetLineColor(kBlack);
    var[i]->SetLineWidth(2);
  }

  TLegendEntry *legge;
  TLegend *leg;
  leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  legge = leg->AddEntry(var[0], "gamma+jets", "f");
  legge = leg->AddEntry(var[1], "QCD", "f");

  // mc only plot: data vs background
  var[0]->SetFillColor(kBlue-9);
  var[0]->Draw("samehist");
  var[1]->SetFillColor(kMagenta-9);
  var[1]->Draw("samehist");

  leg->Draw();
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),".png");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/mc_",variableData.c_str(),".root");
  c0->SaveAs(name);

  // data only plot
  vardata->SetXTitle(axis.c_str());
  vardata->SetTitle("");
  vardata->SetStats(0);
  vardata->SetMarkerStyle(8);
  vardata->SetMarkerSize(.9);
  vardata->SetTitleOffset(1.25,"Y");
  vardata->Draw("pe");
  sprintf(name,"%s%s%s","results_gammaJ/data_",variableData.c_str(),".png");
  c0->SaveAs(name);

  // data overlaid to mc
  legge  = leg->AddEntry(vardata,  "data", "p");

  double themax =   vardata->GetMaximum();
  if(var[0]->GetMaximum()>themax) themax = var[0]->GetMaximum();
  if (
      variableData == "etaphot1" || variableData == "phiphot1" 
      )
    vardata->SetMaximum(themax*2.0);
  else
    vardata->SetMaximum(themax*1.1);
  
  vardata->SetMinimum(0.000001);
  for(int ii=0; ii<2; ii++) var[ii]->SetMinimum(0.000001);
  var[0]->Draw("samehist");
  var[1]->Draw("samehist");
  leg->Draw();
  vardata->Draw("pesame");
  gPad->RedrawAxis();
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),".root");
  c0->SaveAs(name);
  sprintf(name,"%s%s%s","results_gammaJ/data-mc_",variableData.c_str(),".png");
  c0->SaveAs(name);

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
  outfile << "# events QCD, 20-30 = "   << n_mc_2012[0]  << endl;
  outfile << "# events QCD, 30-80 = "   << n_mc_2012[1]  << endl;
  outfile << "# events QCD, 80-170 = "  << n_mc_2012[2]  << endl;
  outfile << "# events QCD, 170-250 = " << n_mc_2012[3]  << endl;
  outfile << "# events QCD, 250-350 = " << n_mc_2012[4]  << endl;
  outfile << "# events QCD, >350 = "    << n_mc_2012[5]  << endl;
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
  outfile << "N of selected events (not scaled for lumi)" << endl;  
  outfile << "##########################################" << endl;
  outfile << "# events QCD, 20-30 = "   << num_uns_mc_2012[0]  << endl;
  outfile << "# events QCD, 30-80 = "   << num_uns_mc_2012[1]  << endl;
  outfile << "# events QCD, 80-170 = "  << num_uns_mc_2012[2]  << endl;
  outfile << "# events QCD, 170-250 = " << num_uns_mc_2012[3]  << endl;
  outfile << "# events QCD, 250-350 = " << num_uns_mc_2012[4]  << endl;
  outfile << "# events QCD, >350 = "    << num_uns_mc_2012[5]  << endl;
  outfile << "# events g+jet, 0-15 = "      << num_uns_mc_2012[6]  << endl;
  outfile << "# events g+jet, 15-30 = "     << num_uns_mc_2012[7]  << endl;
  outfile << "# events g+jet, 30-50 = "     << num_uns_mc_2012[8]  << endl;
  outfile << "# events g+jet, 50-80 = "     << num_uns_mc_2012[9]  << endl;
  outfile << "# events g+jet, 80-120 = "    << num_uns_mc_2012[10] << endl;
  outfile << "# events g+jet, 120-170 = "   << num_uns_mc_2012[11] << endl;
  outfile << "# events g+jet, 170-300 = "   << num_uns_mc_2012[12] << endl;
  outfile << "# events g+jet, 470-800 = "   << num_uns_mc_2012[13] << endl;
  outfile << "# events g+jet, 800-1400 = "  << num_uns_mc_2012[14] << endl;
  outfile << "# events g+jet, 1400-1800 = " << num_uns_mc_2012[15] << endl;
  outfile << endl;
  outfile << "####################################" << endl;
  outfile << "N of selected events and eff." << endl;
  outfile << "####################################" << endl; 
  outfile << "ndata = " << num_data << endl;
  outfile << endl;

  double num_bkg(0), err_num_bkg(0);
  double num_mc_total[16],num_uns_mc_total[16], n_mc_total[16];
  double err_num_mc_total[16],err_num_uns_mc_total[16];
  for (int i=0; i<16; i++){
    if(i<6){  
      num_bkg += num_mc_2012[i];
    }
    num_mc_total[i] = num_mc_2012[i];
    num_uns_mc_total[i] = num_uns_mc_2012[i];
    err_num_uns_mc_total[i] = sqrt(num_uns_mc_total[i]);
    if(num_uns_mc_total[i]) err_num_mc_total[i] = err_num_uns_mc_total[i] * num_mc_total[i]/num_uns_mc_total[i];
    else err_num_mc_total[i] = 0;
    n_mc_total[i] = n_mc_2012[i] * scale_mc_2012[i];
  }
  for (int i=0; i<6; i++){ 
    err_num_bkg = sqrt(err_num_bkg*err_num_bkg + err_num_mc_total[i]*err_num_mc_total[i]);
  }
  
  outfile << "nallbkg        = " << num_bkg << " +/- " << err_num_bkg << endl;
  outfile << "QCD, 20-30     = " << num_mc_total[0]  << " +/- " << err_num_mc_total[0]  << endl;
  outfile << "QCD, 30-80     = " << num_mc_total[1]  << " +/- " << err_num_mc_total[1]  << endl;
  outfile << "QCD, 80-170    = " << num_mc_total[2]  << " +/- " << err_num_mc_total[2]  << endl;
  outfile << "QCD, 170-250   = " << num_mc_total[3]  << " +/- " << err_num_mc_total[3]  << endl;
  outfile << "QCD, 250-350   = " << num_mc_total[4]  << " +/- " << err_num_mc_total[4]  << endl;
  outfile << "QCD, >350      = " << num_mc_total[5]  << " +/- " << err_num_mc_total[5]  << endl;
  outfile << "G+j, 0-15      = " << num_mc_total[6]  << " +/- " << err_num_mc_total[6]  << endl;
  outfile << "G+j, 15-30     = " << num_mc_total[7]  << " +/- " << err_num_mc_total[7]  << endl;
  outfile << "G+j, 30-50     = " << num_mc_total[8]  << " +/- " << err_num_mc_total[8]  << endl;
  outfile << "G+j, 50-80     = " << num_mc_total[9]  << " +/- " << err_num_mc_total[9]  << endl;
  outfile << "G+j, 80-120    = " << num_mc_total[10] << " +/- " << err_num_mc_total[10]  << endl;
  outfile << "G+j, 120-170   = " << num_mc_total[11] << " +/- " << err_num_mc_total[11]  << endl;
  outfile << "G+j, 170-300   = " << num_mc_total[12] << " +/- " << err_num_mc_total[12]  << endl;
  outfile << "G+j, 470-800   = " << num_mc_total[13] << " +/- " << err_num_mc_total[13]  << endl;
  outfile << "G+j, 800-1400  = " << num_mc_total[14] << " +/- " << err_num_mc_total[14]  << endl;
  outfile << "G+j, 1400-1800 = " << num_mc_total[15] << " +/- " << err_num_mc_total[15]  << endl;
  outfile << endl;          
  outfile << endl;
  outfile << "eff gamma+jets = "  << (num_mc_total[6] + num_mc_total[7] + num_mc_total[8] + num_mc_total[9] + num_mc_total[10] + num_mc_total[11] + num_mc_total[12] + num_mc_total[13] + num_mc_total[14] + num_mc_total[15])/(n_mc_total[6] + n_mc_total[7] + n_mc_total[8] + n_mc_total[9] + n_mc_total[10] + n_mc_total[11] + n_mc_total[12] + n_mc_total[13] + n_mc_total[14] + n_mc_total[15]) << endl;  
  
  outfile << "eff QCD 1  = " << num_mc_total[0] / n_mc_total[0]   << endl;
  outfile << "eff QCD 2  = " << num_mc_total[1] / n_mc_total[1]   << endl;
  outfile << "eff QCD 3  = " << num_mc_total[2] / n_mc_total[2]   << endl;
  outfile << "eff QCD 4  = " << num_mc_total[3] / n_mc_total[3]   << endl;
  outfile << "eff QCD 5  = " << num_mc_total[4] / n_mc_total[4]   << endl;
  outfile << "eff QCD 6  = " << num_mc_total[5] / n_mc_total[5]   << endl;
  outfile << "eff G+j 1  = " << num_mc_total[6] / n_mc_total[6]   << endl;
  outfile << "eff G+j 2  = " << num_mc_total[7] / n_mc_total[7]   << endl;
  outfile << "eff G+j 3  = " << num_mc_total[8] / n_mc_total[8]   << endl;
  outfile << "eff G+j 4  = " << num_mc_total[9] / n_mc_total[9]   << endl;
  outfile << "eff G+j 5  = " << num_mc_total[10] / n_mc_total[10] << endl;
  outfile << "eff G+j 6  = " << num_mc_total[11] / n_mc_total[11] << endl;
  outfile << "eff G+j 7  = " << num_mc_total[12] / n_mc_total[12] << endl;
  outfile << "eff G+j 8  = " << num_mc_total[13] / n_mc_total[13] << endl;
  outfile << "eff G+j 9  = " << num_mc_total[14] / n_mc_total[14] << endl;
  outfile << "eff G+j 10 = " << num_mc_total[15] / n_mc_total[15] << endl;
  outfile << endl;
  outfile.close();
  
  hOutputFile->Write() ;
  hOutputFile->Close() ;
  hOutputFile->Delete();
  
  delete data;
  
  for(int i=0; i<16; i++){
    delete mc_2012_fill[i];
    delete mc_2012[i];
  }
  
  vector<double> values;
  
  return values;
}








