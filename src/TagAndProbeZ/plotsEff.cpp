#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLegend.h"
#include <iostream>

void plotsEff() {
  
  // -------------------------------------
  // hardcoded: efficiency on data
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.958273; 
  dataEffPtEB[1] = 0.976137;
  dataEffPtEB[2] = 0.983786;
  dataEffPtEB[3] = 0.988693; 

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.00123849;
  dataErrPtEB[1] = 0.000265797;
  dataErrPtEB[2] = 0.00018067;
  dataErrPtEB[3] = 0.000235874;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.960188;
  dataEffPtEE[1] = 0.977903;
  dataEffPtEE[2] = 0.987079;
  dataEffPtEE[3] = 0.993108;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.00112677;
  dataErrPtEE[1] = 0.00039788;
  dataErrPtEE[2] = 0.00659875;
  dataErrPtEE[3] = 0.000379205;


  // -------------------------------------
  // hardcoded: efficiency on mc
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.960261;
  mcEffPtEB[1] = 0.978493;
  mcEffPtEB[2] = 0.986679;
  mcEffPtEB[3] = 0.990685;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.000545127;
  mcErrPtEB[1] = 0.000257207;
  mcErrPtEB[2] = 0.000179208;
  mcErrPtEB[3] = 0.000298668;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.952608;
  mcEffPtEE[1] = 0.973922;
  mcEffPtEE[2] = 0.9845;
  mcEffPtEE[3] = 0.990536;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.00103929;
  mcErrPtEE[1] = 0.000221474;
  mcErrPtEE[2] = 0.00790882;
  mcErrPtEE[3] = 0.000445383;


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
  DataEffVsPt_barrel->SetTitle("data");
  DataEffVsPt_barrel->GetXaxis()->SetTitle("probe pT [GeV]");

  DataEffVsPt_endcap->SetLineColor(4);
  DataEffVsPt_endcap->SetMarkerColor(4);
  DataEffVsPt_endcap->SetMarkerStyle(20);
  DataEffVsPt_endcap->SetMarkerSize(0.9);
  DataEffVsPt_endcap->SetTitle("data");
  DataEffVsPt_endcap->GetXaxis()->SetTitle("probe pT [GeV]");


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
  McEffVsPt_barrel->SetTitle("mc");
  McEffVsPt_barrel->GetXaxis()->SetTitle("probe pT [GeV]");

  McEffVsPt_endcap->SetMarkerColor(2);
  McEffVsPt_endcap->SetLineColor(2);
  McEffVsPt_endcap->SetMarkerStyle(21);
  McEffVsPt_endcap->SetMarkerSize(0.9);
  McEffVsPt_endcap->SetTitle("mc");
  McEffVsPt_endcap->GetXaxis()->SetTitle("probe pT [GeV]");


  // plots
  gStyle->SetOptStat(0);

  TLegend *leg;
  leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(DataEffVsPt_endcap, "data", "l");
  leg->AddEntry(McEffVsPt_endcap,   "MC",   "l");

  TCanvas myC1("c1", "c1", 1);
  DataEffMap->Draw("colz");
  DataEffMap->Draw("textsame");
  myC1.SaveAs("dataMap.png");

  TCanvas myC1b("c1b", "c1b", 1);
  MCEffMap->Draw("colz");
  MCEffMap->Draw("textsame");
  myC1b.SaveAs("mcMap.png");

  TCanvas myC2("c2", "c2", 1);
  DataEffVsPt_barrel->SetMinimum(0.9);
  DataEffVsPt_barrel->Draw();
  myC2.SaveAs("dataEffVsPt_barrel.png");

  TCanvas myC3("c3", "c3", 1);
  DataEffVsPt_endcap->SetMinimum(0.9);
  DataEffVsPt_endcap->Draw();
  myC3.SaveAs("dataEffVsPt_endcap.png");

  TCanvas myC4("c4", "c4", 1);
  McEffVsPt_barrel->SetMinimum(0.9);
  McEffVsPt_barrel->Draw();
  myC4.SaveAs("mcEffVsPt_barrel.png");

  TCanvas myC5("c5", "c5", 1);
  McEffVsPt_endcap->SetMinimum(0.9);
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




