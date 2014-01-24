#define turnOnPlots_cxx
#include "turnOnPlots.h"
#include <TH2.h>
#include <TGraphAsymmErrors.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void turnOnPlots::Loop()
{
  if (fChain == 0) return;

  gStyle->SetOptStat(0);

  // histos                                                                                                    
  TH1F *Hden30_EB  = new TH1F("Hden30_EB", "Hden30_EB", 40,20.,60.);
  TH1F *Hden50_EB  = new TH1F("Hden50_EB", "Hden50_EB", 40,40.,80.);
  TH1F *Hden75_EB  = new TH1F("Hden75_EB", "Hden75_EB", 40,70.,110.);
  TH1F *Hden90_EB  = new TH1F("Hden90_EB", "Hden90_EB", 40,85.,125.);
  TH1F *Hden135_EB = new TH1F("Hden135_EB","Hden135_EB",40,115.,185.);  
  TH1F *Hden150_EB = new TH1F("Hden150_EB","Hden150_EB",40,120.,200.);
  //                                                                                                           
  TH1F *Hnum30_EB  = new TH1F("Hnum30_EB", "Hnum30_EB", 40,20.,60.);
  TH1F *Hnum50_EB  = new TH1F("Hnum50_EB", "Hnum50_EB", 40,40.,80.);
  TH1F *Hnum75_EB  = new TH1F("Hnum75_EB", "Hnum75_EB", 40,70.,110.);
  TH1F *Hnum90_EB  = new TH1F("Hnum90_EB", "Hnum90_EB", 40,85.,125.);
  TH1F *Hnum135_EB = new TH1F("Hnum135_EB","Hnum135_EB",40,115.,185.);  
  TH1F *Hnum150_EB = new TH1F("Hnum150_EB","Hnum150_EB",40,120.,200.);   
  //                                                                                                           
  TH1F *Hden30_EE  = new TH1F("Hden30_EE", "Hden30_EE", 40,20.,60.);
  TH1F *Hden50_EE  = new TH1F("Hden50_EE", "Hden50_EE", 40,40.,80.);
  TH1F *Hden75_EE  = new TH1F("Hden75_EE", "Hden75_EE", 40,70.,110.);
  TH1F *Hden90_EE  = new TH1F("Hden90_EE", "Hden90_EE", 40,85.,125.);
  TH1F *Hden135_EE = new TH1F("Hden135_EE","Hden135_EE",40,115.,185.);  
  TH1F *Hden150_EE = new TH1F("Hden150_EE","Hden150_EE",40,120.,200.);   
  //                                                                                                           
  TH1F *Hnum30_EE  = new TH1F("Hnum30_EE", "Hnum30_EE", 40,20.,60.);
  TH1F *Hnum50_EE  = new TH1F("Hnum50_EE", "Hnum50_EE", 40,40.,80.);
  TH1F *Hnum75_EE  = new TH1F("Hnum75_EE", "Hnum75_EE", 40,70.,110.);
  TH1F *Hnum90_EE  = new TH1F("Hnum90_EE", "Hnum90_EE", 40,85.,125.);
  TH1F *Hnum135_EE = new TH1F("Hnum135_EE","Hnum135_EE",40,115.,185.);  
  TH1F *Hnum150_EE = new TH1F("Hnum150_EE","Hnum150_EE",40,120.,200.);   

  // for errors                                                                                                
  Hden30_EB  -> Sumw2();
  Hden50_EB  -> Sumw2();
  Hden75_EB  -> Sumw2();
  Hden90_EB  -> Sumw2();
  Hden135_EB -> Sumw2();
  Hden150_EB -> Sumw2();
  //                                                                                                           
  Hnum30_EB  -> Sumw2();
  Hnum50_EB  -> Sumw2();
  Hnum75_EB  -> Sumw2();
  Hnum90_EB  -> Sumw2();
  Hnum135_EB -> Sumw2();
  Hnum150_EB -> Sumw2();
  //                                                                                                           
  Hden30_EE  -> Sumw2();
  Hden50_EE  -> Sumw2();
  Hden75_EE  -> Sumw2();
  Hden90_EE  -> Sumw2();
  Hden135_EE -> Sumw2();
  Hden150_EE -> Sumw2();
  //                                                                                                           
  Hnum30_EE  -> Sumw2();
  Hnum50_EE  -> Sumw2();
  Hnum75_EE  -> Sumw2();
  Hnum90_EE  -> Sumw2();
  Hnum135_EE -> Sumw2();
  Hnum150_EE -> Sumw2();

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // denominator: fully selected reco photons matching the HLT candidate for the path before the one under study
    // numerator: denominator + ptOnlineGamma passing the pTcut of the path under study

    // path 30, using path20
    //if (passHLT20 && hltmatchGamma20) {
    //  if (fabs(etaGamma20)<1.5) {
    // Hden30_EB -> Fill(ptGamma20);
    //	if (ptOnlineGamma20>30) Hnum30_EB -> Fill(ptGamma20)
    //      } else {
    // Hden30_EE -> Fill(ptGamma20);
    // if (ptOnlineGamma20>30) Hnum30_EE -> Fill(ptGamma20);
    // }
    // }

    // path 50, using path30
    if (passHLT30 && hltmatchGamma30) {
      if (fabs(etaGamma30)<1.5) {
	Hden50_EB -> Fill(ptGamma30);
	if (ptOnlineGamma30>50) Hnum50_EB -> Fill(ptGamma30);
      } else {
	Hden50_EE -> Fill(ptGamma30);
	if (ptOnlineGamma30>50) Hnum50_EE -> Fill(ptGamma30);
      }
    }

    // path 75, using path50
    if (passHLT50 && hltmatchGamma50) {
      if (fabs(etaGamma50)<1.5) {
	Hden75_EB -> Fill(ptGamma50);
	if (ptOnlineGamma50>75) Hnum75_EB -> Fill(ptGamma50);
      } else {
	Hden75_EE -> Fill(ptGamma50);
	if (ptOnlineGamma50>75) Hnum75_EE -> Fill(ptGamma50);
      }
    }

    // path 90, using path75
    if (passHLT75 && hltmatchGamma75) {
      if (fabs(etaGamma75)<1.5) {
	Hden90_EB -> Fill(ptGamma75);
	if (ptOnlineGamma75>90) Hnum90_EB -> Fill(ptGamma75);
      } else {
	Hden90_EE -> Fill(ptGamma75);
	if (ptOnlineGamma75>90) Hnum90_EE -> Fill(ptGamma75);
      }
    }

    // path 135, using path90
    if (passHLT90 && hltmatchGamma90) {
      if (fabs(etaGamma90)<1.5) {
	Hden135_EB -> Fill(ptGamma90);
	if (ptOnlineGamma90>135) Hnum135_EB -> Fill(ptGamma90);
      } else {
	Hden135_EE -> Fill(ptGamma90);
	if (ptOnlineGamma90>135) Hnum135_EE -> Fill(ptGamma90);
      }
    }

    // path 150, using path90 (we don't have infos for 135)
    if (passHLT90 && hltmatchGamma90) {
      if (fabs(etaGamma90)<1.5) {
	Hden150_EB -> Fill(ptGamma90);
	if (ptOnlineGamma90>150) Hnum150_EB -> Fill(ptGamma90);
      } else {
	Hden150_EE -> Fill(ptGamma90);
	if (ptOnlineGamma90>150) Hnum150_EE -> Fill(ptGamma90);
      }
    }

  } // loop over entries
  

  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 30                                                                               
  TGraphAsymmErrors *Heff30_EB = new TGraphAsymmErrors(Hnum30_EB,Hden30_EB);
  TGraphAsymmErrors *Heff30_EE = new TGraphAsymmErrors(Hnum30_EE,Hden30_EE);
  Heff30_EB  -> SetLineWidth(2); Heff30_EB  -> SetLineColor(1);
  Heff30_EE  -> SetLineWidth(2); Heff30_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_30_EB = new TH2F("myH2_30_EB","myH2_30_EB",100,20.,50.,100,0.,1.2);
  TH2F *myH2_30_EE = new TH2F("myH2_30_EE","myH2_30_EE",100,20.,50.,100,0.,1.2);
  myH2_30_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_30_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_30_EB -> SetTitle("HLT_Photon30_CaloIdVL, barrel");
  myH2_30_EE -> SetTitle("HLT_Photon30_CaloIdVL, endcap");

  TCanvas c30("c30","c30",1);
  c30.Divide(2,1);
  c30.cd(1); myH2_30_EB->Draw(); Heff30_EB->Draw("pEsame");
  c30.cd(2); myH2_30_EE->Draw(); Heff30_EE->Draw("pEsame");
  c30.SaveAs("turnon30.root");

  TCanvas c30a("c30a","c30a",1);
  myH2_30_EB->Draw(); Heff30_EB->Draw("pEsame");
  c30a.SaveAs("turnon30_EB.root");
  c30a.SaveAs("turnon30_EB.png");

  TCanvas c30b("c30b","c30b",1);
  myH2_30_EE->Draw(); Heff30_EE->Draw("pEsame");
  c30b.SaveAs("turnon30_EE.root");
  c30b.SaveAs("turnon30_EE.png");

  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 50                                                                               
  TGraphAsymmErrors *Heff50_EB = new TGraphAsymmErrors(Hnum50_EB,Hden50_EB);
  TGraphAsymmErrors *Heff50_EE = new TGraphAsymmErrors(Hnum50_EE,Hden50_EE);
  Heff50_EB  -> SetLineWidth(2); Heff50_EB  -> SetLineColor(1);
  Heff50_EE  -> SetLineWidth(2); Heff50_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_50_EB = new TH2F("myH2_50_EB","myH2_50_EB",100,40.,70.,100,0.,1.2);
  TH2F *myH2_50_EE = new TH2F("myH2_50_EE","myH2_50_EE",100,40.,70.,100,0.,1.2);
  myH2_50_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_50_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_50_EB -> SetTitle("HLT_Photon50_CaloIdVL, barrel");
  myH2_50_EE -> SetTitle("HLT_Photon50_CaloIdVL, endcap");

  TCanvas c50("c50","c50",1);
  c50.Divide(2,1);
  c50.cd(1); myH2_50_EB->Draw(); Heff50_EB->Draw("pEsame");
  c50.cd(2); myH2_50_EE->Draw(); Heff50_EE->Draw("pEsame");
  c50.SaveAs("turnon50.root");

  TCanvas c50a("c50a","c50a",1);
  myH2_50_EB->Draw(); Heff50_EB->Draw("pEsame");
  c50a.SaveAs("turnon50_EB.root");
  c50a.SaveAs("turnon50_EB.png");

  TCanvas c50b("c50b","c50b",1);
  myH2_50_EE->Draw(); Heff50_EE->Draw("pEsame");
  c50b.SaveAs("turnon50_EE.root");
  c50b.SaveAs("turnon50_EE.png");


  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 75                                                                               
  TGraphAsymmErrors *Heff75_EB = new TGraphAsymmErrors(Hnum75_EB,Hden75_EB);
  TGraphAsymmErrors *Heff75_EE = new TGraphAsymmErrors(Hnum75_EE,Hden75_EE);
  Heff75_EB  -> SetLineWidth(2); Heff75_EB  -> SetLineColor(1);
  Heff75_EE  -> SetLineWidth(2); Heff75_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_75_EB = new TH2F("myH2_75_EB","myH2_75_EB",100,70.,100.,100,0.,1.2);
  TH2F *myH2_75_EE = new TH2F("myH2_75_EE","myH2_75_EE",100,70.,100.,100,0.,1.2);
  myH2_75_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_75_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_75_EB -> SetTitle("HLT_Photon75_CaloIdVL, barrel");
  myH2_75_EE -> SetTitle("HLT_Photon75_CaloIdVL, endcap");

  TCanvas c75("c75","c75",1);
  c75.Divide(2,1);
  c75.cd(1); myH2_75_EB->Draw(); Heff75_EB->Draw("pEsame");
  c75.cd(2); myH2_75_EE->Draw(); Heff75_EE->Draw("pEsame");
  c75.SaveAs("turnon75.root");

  TCanvas c75a("c75a","c75a",1);
  myH2_75_EB->Draw(); Heff75_EB->Draw("pEsame");
  c75a.SaveAs("turnon75_EB.root");
  c75a.SaveAs("turnon75_EB.png");

  TCanvas c75b("c75b","c75b",1);
  myH2_75_EE->Draw(); Heff75_EE->Draw("pEsame");
  c75b.SaveAs("turnon75_EE.root");
  c75b.SaveAs("turnon75_EE.png");

  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 90                                                                               
  TGraphAsymmErrors *Heff90_EB = new TGraphAsymmErrors(Hnum90_EB,Hden90_EB);
  TGraphAsymmErrors *Heff90_EE = new TGraphAsymmErrors(Hnum90_EE,Hden90_EE);
  Heff90_EB  -> SetLineWidth(2); Heff90_EB  -> SetLineColor(1);
  Heff90_EE  -> SetLineWidth(2); Heff90_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_90_EB = new TH2F("myH2_90_EB","myH2_90_EB",100,85.,120.,100,0.,1.2);
  TH2F *myH2_90_EE = new TH2F("myH2_90_EE","myH2_90_EE",100,85.,120.,100,0.,1.2);
  myH2_90_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_90_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_90_EB -> SetTitle("HLT_Photon90_CaloIdVL, barrel");
  myH2_90_EE -> SetTitle("HLT_Photon90_CaloIdVL, endcap");

  TCanvas c90("c90","c90",1);
  c90.Divide(2,1);
  c90.cd(1); myH2_90_EB->Draw(); Heff90_EB->Draw("pEsame");
  c90.cd(2); myH2_90_EE->Draw(); Heff90_EE->Draw("pEsame");
  c90.SaveAs("turnon90.root");

  TCanvas c90a("c90a","c90a",1);
  myH2_90_EB->Draw(); Heff90_EB->Draw("pEsame");
  c90a.SaveAs("turnon90_EB.root");
  c90a.SaveAs("turnon90_EB.png");

  TCanvas c90b("c90b","c90b",1);
  myH2_90_EE->Draw(); Heff90_EE->Draw("pEsame");
  c90b.SaveAs("turnon90_EE.root");
  c90b.SaveAs("turnon90_EE.png");

  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 135                                                                               
  TGraphAsymmErrors *Heff135_EB = new TGraphAsymmErrors(Hnum135_EB,Hden135_EB);
  TGraphAsymmErrors *Heff135_EE = new TGraphAsymmErrors(Hnum135_EE,Hden135_EE);
  Heff135_EB  -> SetLineWidth(2); Heff135_EB  -> SetLineColor(1);
  Heff135_EE  -> SetLineWidth(2); Heff135_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_135_EB = new TH2F("myH2_135_EB","myH2_135_EB",100,115.,185.,100,0.,1.2); 
  TH2F *myH2_135_EE = new TH2F("myH2_135_EE","myH2_135_EE",100,115.,185.,100,0.,1.2); 
  myH2_135_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_135_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_135_EB -> SetTitle("HLT_Photon135, barrel");
  myH2_135_EE -> SetTitle("HLT_Photon135, endcap");

  TCanvas c135("c135","c135",1);
  c135.Divide(2,1);
  c135.cd(1); myH2_135_EB->Draw(); Heff135_EB->Draw("pEsame");
  c135.cd(2); myH2_135_EE->Draw(); Heff135_EE->Draw("pEsame");
  c135.SaveAs("turnon135.root");

  TCanvas c135a("c135a","c135a",1);
  myH2_135_EB->Draw(); Heff135_EB->Draw("pEsame");
  c135a.SaveAs("turnon135_EB.root");
  c135a.SaveAs("turnon135_EB.png");

  TCanvas c135b("c135b","c135b",1);
  myH2_135_EE->Draw(); Heff135_EE->Draw("pEsame");
  c135b.SaveAs("turnon135_EE.root");
  c135b.SaveAs("turnon135_EE.png");

  // ---------------------------------------------------------------------------
  // efficiency plots, HLT pT 150                                                                               
  TGraphAsymmErrors *Heff150_EB = new TGraphAsymmErrors(Hnum150_EB,Hden150_EB);
  TGraphAsymmErrors *Heff150_EE = new TGraphAsymmErrors(Hnum150_EE,Hden150_EE);
  Heff150_EB  -> SetLineWidth(2); Heff150_EB  -> SetLineColor(1);
  Heff150_EE  -> SetLineWidth(2); Heff150_EE  -> SetLineColor(1);
  cout << endl;

  TH2F *myH2_150_EB = new TH2F("myH2_150_EB","myH2_150_EB",100,120.,200.,100,0.,1.2);   
  TH2F *myH2_150_EE = new TH2F("myH2_150_EE","myH2_150_EE",100,120.,200.,100,0.,1.2);   
  myH2_150_EB -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_150_EE -> GetXaxis()->SetTitle("reco photon p_{T} [GeV]");
  myH2_150_EB -> SetTitle("HLT_Photon150, barrel");
  myH2_150_EE -> SetTitle("HLT_Photon150, endcap");

  TCanvas c150("c150","c150",1);
  c150.Divide(2,1);
  c150.cd(1); myH2_150_EB->Draw(); Heff150_EB->Draw("pEsame");
  c150.cd(2); myH2_150_EE->Draw(); Heff150_EE->Draw("pEsame");
  c150.SaveAs("turnon150.root");

  TCanvas c150a("c150a","c150a",1);
  myH2_150_EB->Draw(); Heff150_EB->Draw("pEsame");
  c150a.SaveAs("turnon150_EB.root");
  c150a.SaveAs("turnon150_EB.png");

  TCanvas c150b("c150b","c150b",1);
  myH2_150_EE->Draw(); Heff150_EE->Draw("pEsame");
  c150b.SaveAs("turnon150_EE.root");
  c150b.SaveAs("turnon150_EE.png");
}
