#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>

void plotsEff() {
  
  // -------------------------------------
  // hardcoded: efficiency on data (95%)
  /*
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.788216;
  dataEffPtEB[1] = 0.868873;
  dataEffPtEB[2] = 0.909119;
  dataEffPtEB[3] = 0.937142;

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.0022248;
  dataErrPtEB[1] = 0.00557281;
  dataErrPtEB[2] = 0.000410552;
  dataErrPtEB[3] = 0.0317504;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.667278;
  dataEffPtEE[1] = 0.789731;
  dataEffPtEE[2] = 0.861867;
  dataEffPtEE[3] = 0.91869;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.00288854;
  dataErrPtEE[1] = 0.00113707;
  dataErrPtEE[2] = 0.0008856;
  dataErrPtEE[3] = 0.00125012;
  */

  // hardcoded: efficiency on data (90%)
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.6809;
  dataEffPtEB[1] = 0.774901;
  dataEffPtEB[2] = 0.826641;
  dataEffPtEB[3] = 0.87309;

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.002289;
  dataErrPtEB[1] = 0.0006833;
  dataErrPtEB[2] = 0.085946;
  dataErrPtEB[3] = 0.0004758;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.547962;
  dataEffPtEE[1] = 0.670435;
  dataEffPtEE[2] = 0.753952;
  dataEffPtEE[3] = 0.83594;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.003029;
  dataErrPtEE[1] = 0.0012858;
  dataErrPtEE[2] = 0.001035;
  dataErrPtEE[3] = 0.001670;

  // -------------------------------------
  // hardcoded: efficiency on mc (95%)
  /*
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.806962;
  mcEffPtEB[1] = 0.884942;
  mcEffPtEB[2] = 0.921844;
  mcEffPtEB[3] = 0.946614;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.00183663;
  mcErrPtEB[1] = 0.000726529;
  mcErrPtEB[2] = 0.0005429;
  mcErrPtEB[3] = 0.0008690;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.740969;
  mcEffPtEE[1] = 0.86685;
  mcEffPtEE[2] = 0.924042;
  mcEffPtEE[3] = 0.961009;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.00258916;
  mcErrPtEE[1] = 0.00123024;
  mcErrPtEE[2] = 0.000874;
  mcErrPtEE[3] = 0.00113995;
  */

  // hardcoded: efficiency on mc (90%)
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.70395;
  mcEffPtEB[1] = 0.796202;
  mcEffPtEB[2] = 0.845931;
  mcEffPtEB[3] = 0.886863;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.00204;
  mcErrPtEB[1] = 0.000917;
  mcErrPtEB[2] = 0.000730;
  mcErrPtEB[3] = 0.00119625;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.626057;
  mcEffPtEE[1] = 0.770266;
  mcEffPtEE[2] = 0.846824;
  mcEffPtEE[3] = 0.909447;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.002778;
  mcErrPtEE[1] = 0.001529;
  mcErrPtEE[2] = 0.07719;
  mcErrPtEE[3] = 0.001755;

  // -------------------------------------
  // hardcoded: efficiency on MC (90%), high R9 (nome misleading...)
  /*
  Float_t dataEffPtEB[4];
  dataEffPtEB[0] = 0.933638;
  dataEffPtEB[1] = 0.954063;
  dataEffPtEB[2] = 0.964888;
  dataEffPtEB[3] = 0.97694;

  Float_t dataErrPtEB[4];
  dataErrPtEB[0] = 0.002329;
  dataErrPtEB[1] = 0.0009391;
  dataErrPtEB[2] = 0.0006698;
  dataErrPtEB[3] = 0.0120207;
  
  Float_t dataEffPtEE[4];
  dataEffPtEE[0] = 0.930876;
  dataEffPtEE[1] = 0.96969;
  dataEffPtEE[2] = 0.980841;
  dataEffPtEE[3] = 0.987945;

  Float_t dataErrPtEE[4];
  dataErrPtEE[0] = 0.002852;
  dataErrPtEE[1] = 0.001196;
  dataErrPtEE[2] = 0.0007996;
  dataErrPtEE[3] = 0.00111779;
  */

  // hardcoded: efficiency on MC (90%), low R9 (nome misleading...)
  /*
  Float_t mcEffPtEB[4];
  mcEffPtEB[0] = 0.64763;
  mcEffPtEB[1] = 0.741015;
  mcEffPtEB[2] = 0.792764;
  mcEffPtEB[3] = 0.835521;

  Float_t mcErrPtEB[4];
  mcErrPtEB[0] = 0.002352;
  mcErrPtEB[1] = 0.001158;
  mcErrPtEB[2] = 0.000986;
  mcErrPtEB[3] = 0.001738;
  
  Float_t mcEffPtEE[4];
  mcEffPtEE[0] = 0.540286;
  mcEffPtEE[1] = 0.694782;
  mcEffPtEE[2] = 0.783672;
  mcEffPtEE[3] = 0.861586;

  Float_t mcErrPtEE[4];
  mcErrPtEE[0] = 0.23148;
  mcErrPtEE[1] = 0.001958;
  mcErrPtEE[2] = 0.001649;
  mcErrPtEE[3] = 0.002647;
  */

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




