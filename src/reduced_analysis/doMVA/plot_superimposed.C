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

void plot_superimposed(bool isEB) {

  //TFile* file_input[3];
  TFile* file_input[2];
  if (isEB)  {
    file_input[0]  = new TFile("TMVAoutput_EB.root", "READ");
    //file_input[1]  = new TFile("TMVAoutput_withRho_EB.root", "READ");
    //file_input[2]  = new TFile("TMVAoutput_withHoverE_EB.root", "READ");
    file_input[1]  = new TFile("TMVAoutput_timing_EB.root", "READ");

  }  
  else  {
    file_input[0]  = new TFile("TMVAoutput_EE.root", "READ");
    file_input[1]  = new TFile("TMVAoutput_withRho_EE.root", "READ");
    //    file_input[2]  = new TFile("TMVAoutput_withHoverE_EE.root", "READ");
  }

  //  TH1F* MVA_BDT_rejBvsS[3];
  TH1F* MVA_BDT_rejBvsS[2];

  //  for(int i=0; i<3; i++) {
  for(int i=0; i<2; i++) {
    MVA_BDT_rejBvsS[i] = ((TH1F*)file_input[i]->Get("Method_BDT/BDT/MVA_BDT_rejBvsS"));
  }

  MVA_BDT_rejBvsS[0]->SetMarkerStyle(20);
  MVA_BDT_rejBvsS[0]->SetMarkerColor(kRed);
  MVA_BDT_rejBvsS[1]->SetMarkerStyle(21);
  MVA_BDT_rejBvsS[1]->SetMarkerColor(kGreen+2);
  //  MVA_BDT_rejBvsS[2]->SetMarkerStyle(22);
  //MVA_BDT_rejBvsS[2]->SetMarkerColor(kBlue);

  TCanvas* c_MVA_BDT_rejBvsS = new TCanvas("c_MVA_BDT_rejBvsS", "", 1);
  TLegend* leg = new TLegend(0.3, 0.5, 0.6, 0.7);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);

  leg->AddEntry(MVA_BDT_rejBvsS[0], "", "p");
  //leg->AddEntry(MVA_BDT_rejBvsS[1], "with RhoAllJets", "p");
  //leg->AddEntry(MVA_BDT_rejBvsS[2], "with H/E", "p");
  leg->AddEntry(MVA_BDT_rejBvsS[1], "with timing", "p");  

  c_MVA_BDT_rejBvsS->cd();
  MVA_BDT_rejBvsS[0]->Draw("P");
  //  for(int i=1; i<3; i++){
  for(int i=1; i<2; i++){
    MVA_BDT_rejBvsS[i]->Draw("PSAME");
  }
  leg->Draw();

  if(isEB) c_MVA_BDT_rejBvsS->SaveAs("ROCsuperimposed_EB.png");
  else c_MVA_BDT_rejBvsS->SaveAs("ROCsuperimposed_EE.png");

  c_MVA_BDT_rejBvsS->Close();

}
