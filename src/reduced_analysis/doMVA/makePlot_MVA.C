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

void makePlot(bool isEB) {

  TFile* file_input;
  if (isEB)  {
    file_input  = new TFile("TMVAoutput_withRho_EB.root", "READ");
  }  
  else  {
    file_input  = new TFile("TMVAoutput_withRho_EE.root", "READ"); 
  }

  TH1F *MVA_BDT_S_Test, *MVA_BDT_B_Test, *MVA_BDT_S_Train, *MVA_BDT_B_Train;
  TH1F *MVA_BDT_rejBvsS;
  TH2F *CorrelationMatrixS, *CorrelationMatrixB;

  MVA_BDT_S_Test = ((TH1F*)file_input->Get("Method_BDT/BDT/MVA_BDT_S"));
  MVA_BDT_B_Test = ((TH1F*)file_input->Get("Method_BDT/BDT/MVA_BDT_B"));
  MVA_BDT_S_Train = ((TH1F*)file_input->Get("Method_BDT/BDT/MVA_BDT_Train_S"));
  MVA_BDT_B_Train = ((TH1F*)file_input->Get("Method_BDT/BDT/MVA_BDT_Train_B"));

  MVA_BDT_rejBvsS = ((TH1F*)file_input->Get("Method_BDT/BDT/MVA_BDT_rejBvsS"));
  
  CorrelationMatrixS = ((TH2F*)file_input->Get("CorrelationMatrixS"));
  CorrelationMatrixB = ((TH2F*)file_input->Get("CorrelationMatrixB"));

  MVA_BDT_S_Test->SetLineColor(kAzure+1);
  MVA_BDT_S_Test->SetFillColor(kAzure+6);
  MVA_BDT_S_Test->SetFillStyle(3001);
  MVA_BDT_B_Test->SetLineColor(kRed);
  MVA_BDT_B_Test->SetFillColor(kRed);
  MVA_BDT_B_Test->SetFillStyle(3005);

  MVA_BDT_S_Train->SetMarkerColor(kBlue);
  MVA_BDT_B_Train->SetMarkerColor(kRed);

  MVA_BDT_S_Test->GetXaxis()->SetTitle("BDT");

  TCanvas* c_BDT = new TCanvas("c_BDT", "", 1);
  TLegend* leg = new TLegend(0.25, 0.7, 0.55, 0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(MVA_BDT_S_Test, "MVA_BDT_S_Test", "f");
  leg->AddEntry(MVA_BDT_B_Test, "MVA_BDT_B_Test", "f");
  leg->AddEntry(MVA_BDT_S_Train, "MVA_BDT_S_Train", "p");
  leg->AddEntry(MVA_BDT_B_Train, "MVA_BDT_B_Train", "p");
  
  c_BDT->cd();
  
  MVA_BDT_S_Test->Draw("HIST");
  MVA_BDT_B_Test->Draw("HISTSAME");
  MVA_BDT_S_Train->Draw("PSAME");
  MVA_BDT_B_Train->Draw("PSAME");
  leg->Draw();
  
  if(isEB)  c_BDT->SaveAs("MVA_BDT_withRho_EB.png");
  else  c_BDT->SaveAs("MVA_BDT_withRho_EE.png");
  
  c_BDT->Close();

  TCanvas* c_correlation_S = new TCanvas("c_correlation_S", "", 1);
  TCanvas* c_correlation_B = new TCanvas("c_correlation_B", "", 1);

  c_correlation_S->cd();
  CorrelationMatrixS->Draw("colz");
  if(isEB)   c_correlation_S->SaveAs("correlationS_withRho_EB.png");
  else c_correlation_S->SaveAs("correlationS_withRho_EE.png");
  c_correlation_S->Close();

  c_correlation_B->cd();
  CorrelationMatrixB->Draw("colz");
  if(isEB) c_correlation_B->SaveAs("correlationB_withRho_EB.png");
  else  c_correlation_B->SaveAs("correlationB_withRho_EE.png");
  c_correlation_B->Close();
  
  TCanvas* c_BDT_rejBvsS = new TCanvas("c_BDT_rejBvsS", "", 1);

  c_BDT_rejBvsS->cd();
  MVA_BDT_rejBvsS->Draw("P");
  if(isEB) c_BDT_rejBvsS->SaveAs("ROCcurve_withRho_EB.png");
  else c_BDT_rejBvsS->SaveAs("ROCcurve_withRho_EE.png");
  c_BDT_rejBvsS->Close();

}
