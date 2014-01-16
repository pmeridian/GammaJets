#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>

void plotsEff() {

  /*
  // hardcoded: efficiency on data, mva 005 - no R9 weights
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.787321;
  dataEffPtEB[1] = 0.865828;
  dataEffPtEB[2] = 0.907563;
  dataEffPtEB[3] = 0.934763;

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.00147372;
  dataErrPtEB[1] = 0.000507673;
  dataErrPtEB[2] = 0.000371044;
  dataErrPtEB[3] = 0.00104934;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.717205;
  dataEffPtEE[1] = 0.833808;
  dataEffPtEE[2] = 0.902595;
  dataEffPtEE[3] = 0.947531;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.00215698;
  dataErrPtEE[1] = 0.000966102;
  dataErrPtEE[2] = 0.00031378;
  dataErrPtEE[3] = 0.000974099;
  */

  // hardcoded: efficiency on data, mva 005 - with R9 weights
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.851094;
  dataEffPtEB[1] = 0.911409;
  dataEffPtEB[2] = 0.942177;
  dataEffPtEB[3] = 0.960729;

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.000877588;
  dataErrPtEB[1] = 0.000284711;
  dataErrPtEB[2] = 0.000193678;
  dataErrPtEB[3] = 0.000351052;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.823633;
  dataEffPtEE[1] = 0.904294;
  dataEffPtEE[2] = 0.945122;
  dataEffPtEE[3] = 0.972123;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.00137336;
  dataErrPtEE[1] = 0.000541285;
  dataErrPtEE[2] = 0.000332841;
  dataErrPtEE[3] = 0.000471213;

  /*
  // hardcoded: efficiency on mc, mva 005  - no R9weights
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.809073;
  mcEffPtEB[1] = 0.884915;
  mcEffPtEB[2] = 0.921544;
  mcEffPtEB[3] = 0.944102;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.00107234;
  mcErrPtEB[1] = 0.000362482;
  mcErrPtEB[2] = 0.000269083;
  mcErrPtEB[3] = 0.000583753;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.745734;
  mcEffPtEE[1] = 0.869638;
  mcEffPtEE[2] = 0.92426;
  mcEffPtEE[3] = 0.957486;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.00181754;
  mcErrPtEE[1] = 0.000661643;
  mcErrPtEE[2] = 0.0000115311;
  mcErrPtEE[3] = 0.000633697;
  */

  // hardcoded: efficiency on mc, mva 005  - with R9weights
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.869367;
  mcEffPtEB[1] = 0.925948;
  mcEffPtEB[2] = 0.951753;
  mcEffPtEB[3] = 0.967678;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.000681269;
  mcErrPtEB[1] = 0.000197075;
  mcErrPtEB[2] = 0.000132988;
  mcErrPtEB[3] = 0.000269974;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.843007;
  mcEffPtEE[1] = 0.926918;
  mcEffPtEE[2] = 0.958852;
  mcEffPtEE[3] = 0.977944;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.00111903;
  mcErrPtEE[1] = 0.00017719;
  mcErrPtEE[2] = 0.000208054;
  mcErrPtEE[3] = 0.0111678;


  // -------------------------------------
  // histograms: 2D plots
  Float_t LowerEta[3];
  LowerEta[0]=0.0;
  LowerEta[1]=1.5;
  LowerEta[2]=2.5;

  Float_t LowerPt[5];
  LowerPt[0]=20.0;
  LowerPt[1]=30.0;
  LowerPt[2]=40.0;
  LowerPt[3]=50.0;
  LowerPt[4]=200.0;

  TH2F *DataEffMap = new TH2F( "DataEffMap",  "data efficiency map", 2, LowerEta, 4, LowerPt);
  TH2F *MCEffMap   = new TH2F( "MCEffMap",    "MC efficiency map",   2, LowerEta, 4, LowerPt);
  
  for (int jj=1; jj<5; jj++) {
    int theindex = jj-1;
    DataEffMap->SetBinContent(1,jj,dataEffPtEB[theindex]);
    DataEffMap->SetBinContent(2,jj,dataEffPtEE[theindex]);
    DataEffMap->SetBinError(1,jj,dataErrPtEB[theindex]);
    DataEffMap->SetBinError(2,jj,dataErrPtEE[theindex]);

    MCEffMap->SetBinContent(1,jj,mcEffPtEB[theindex]);
    MCEffMap->SetBinContent(2,jj,mcEffPtEE[theindex]);
    MCEffMap->SetBinError(1,jj,mcErrPtEB[theindex]);
    MCEffMap->SetBinError(2,jj,mcErrPtEE[theindex]);
  }

  DataEffMap->SetTitle("data");
  DataEffMap->GetXaxis()->SetTitle("probe #eta");
  DataEffMap->GetYaxis()->SetTitle("probe pT [GeV]");

  MCEffMap->SetTitle("MC");
  MCEffMap->GetXaxis()->SetTitle("probe #eta");
  MCEffMap->GetYaxis()->SetTitle("probe pT [GeV]");
  

  // -------------------------------------
  // data: eff vs pT
  TH1F *DataEffVsPt_barrel = new TH1F( "DataEffVsPt_barrel" , "DataEffVsPt_barrel", 4, LowerPt);
  TH1F *DataEffVsPt_endcap = new TH1F( "DataEffVsPt_endcap" , "DataEffVsPt_endcap", 4, LowerPt);
  for (int jj=1; jj<5; jj++) {
    int theindex = jj-1;
    DataEffVsPt_barrel->SetBinContent(jj,dataEffPtEB[theindex]);
    DataEffVsPt_barrel->SetBinError(jj,dataErrPtEB[theindex]);
    DataEffVsPt_endcap->SetBinContent(jj,dataEffPtEE[theindex]);
    DataEffVsPt_endcap->SetBinError(jj,dataErrPtEE[theindex]);
  }
  DataEffVsPt_barrel->SetMarkerColor(4);
  DataEffVsPt_barrel->SetLineColor(4);
  DataEffVsPt_barrel->SetMarkerStyle(20);
  DataEffVsPt_barrel->SetMarkerSize(0.9);
  DataEffVsPt_barrel->GetXaxis()->SetTitle("probe pT [GeV]");
  DataEffVsPt_barrel->SetTitle("photonID efficiency");

  DataEffVsPt_endcap->SetLineColor(4);
  DataEffVsPt_endcap->SetMarkerColor(4);
  DataEffVsPt_endcap->SetMarkerStyle(20);
  DataEffVsPt_endcap->SetMarkerSize(0.9);
  DataEffVsPt_endcap->GetXaxis()->SetTitle("probe pT [GeV]");
  DataEffVsPt_endcap->SetTitle("photonID efficiency");


  // ---------------------------------------
  // mc: eff vs pT
  TH1F *McEffVsPt_barrel = new TH1F( "McEffVsPt_barrel" , "McEffVsPt_barrel", 4, LowerPt);
  TH1F *McEffVsPt_endcap = new TH1F( "McEffVsPt_endcap" , "McEffVsPt_endcap", 4, LowerPt);
  for (int jj=1; jj<5; jj++) {
    int theindex = jj-1;
    McEffVsPt_barrel->SetBinContent(jj,mcEffPtEB[theindex]);
    McEffVsPt_barrel->SetBinError(jj,mcErrPtEB[theindex]);
    McEffVsPt_endcap->SetBinContent(jj,mcEffPtEE[theindex]);
    McEffVsPt_endcap->SetBinError(jj,mcErrPtEE[theindex]);
  }
  McEffVsPt_barrel->SetMarkerColor(2);
  McEffVsPt_barrel->SetLineColor(2);
  McEffVsPt_barrel->SetMarkerStyle(21);
  McEffVsPt_barrel->SetMarkerSize(0.9);
  McEffVsPt_barrel->SetTitle("photonID efficiency");
  McEffVsPt_barrel->GetXaxis()->SetTitle("probe pT [GeV]");

  McEffVsPt_endcap->SetMarkerColor(2);
  McEffVsPt_endcap->SetLineColor(2);
  McEffVsPt_endcap->SetMarkerStyle(21);
  McEffVsPt_endcap->SetMarkerSize(0.9);
  McEffVsPt_endcap->SetTitle("photonID efficiency");
  McEffVsPt_endcap->GetXaxis()->SetTitle("probe pT [GeV]");


  // plots
  gStyle->SetOptStat(0);

  TLegend *leg;
  leg = new TLegend(0.4,0.4,0.65,0.65);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  // leg->AddEntry(DataEffVsPt_endcap, "MC, highR9", "lp");
  // leg->AddEntry(McEffVsPt_endcap,   "MC, low R9", "lp");
  leg->AddEntry(DataEffVsPt_endcap, "data", "lp");
  leg->AddEntry(McEffVsPt_endcap,   "MC",   "lp");

  TCanvas myC1("c1", "c1", 1);
  DataEffMap->Draw("colz");
  DataEffMap->Draw("textsame");
  myC1.SaveAs("dataMap.png");

  TCanvas myC1b("c1b", "c1b", 1);
  MCEffMap->Draw("colz");
  MCEffMap->Draw("textsame");
  myC1b.SaveAs("mcMap.png");

  TCanvas myC2("c2", "c2", 1);
  DataEffVsPt_barrel->SetMinimum(0.5);
  DataEffVsPt_barrel->SetMaximum(1.);
  DataEffVsPt_barrel->Draw();
  myC2.SaveAs("dataEffVsPt_barrel.png");

  TCanvas myC3("c3", "c3", 1);
  DataEffVsPt_endcap->SetMinimum(0.5);
  DataEffVsPt_endcap->SetMaximum(1.);
  DataEffVsPt_endcap->Draw();
  myC3.SaveAs("dataEffVsPt_endcap.png");

  TCanvas myC4("c4", "c4", 1);
  McEffVsPt_barrel->SetMinimum(0.5);
  McEffVsPt_barrel->SetMaximum(1.);
  McEffVsPt_barrel->Draw();
  myC4.SaveAs("mcEffVsPt_barrel.png");

  TCanvas myC5("c5", "c5", 1);
  McEffVsPt_endcap->SetMinimum(0.5);
  McEffVsPt_endcap->SetMaximum(1.);
  McEffVsPt_endcap->Draw();
  myC5.SaveAs("mcEffVsPt_endcap.png");

  TCanvas myC6("c6", "c6", 1);
  DataEffVsPt_barrel->Draw();
  McEffVsPt_barrel->Draw("same");
  leg->Draw();
  myC6.SaveAs("compEffVsPt_barrel.png");

  TCanvas myC7("c7", "c7", 1);
  DataEffVsPt_endcap->Draw();
  McEffVsPt_endcap->Draw("same");
  leg->Draw();
  myC7.SaveAs("compEffVsPt_endcap.png");
}




