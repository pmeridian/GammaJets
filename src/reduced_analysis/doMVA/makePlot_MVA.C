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
#include <TPaveText.h>
#include <TLegend.h>


std::string get_sqrtText() {

   char label_sqrt_text[150];
  
    sprintf( label_sqrt_text, "#sqrt{s} = 8 TeV");
    std::string returnString(label_sqrt_text);

  return returnString;

}


TPaveText* get_labelCMS( int legendQuadrant = 0 , std::string year="2011", bool sim=false, std::string run = "ALL") {

  if( legendQuadrant!=0 && legendQuadrant!=1 && legendQuadrant!=2 && legendQuadrant!=3 ) {
    std::cout << "WARNING! Legend quadrant '" << legendQuadrant << "' not yet implemented for CMS label. Using 2." << std::endl;
    legendQuadrant = 2;
  }

  float x1, y1, x2, y2;
  if( legendQuadrant==1 ) {
    x1 = 0.63;
    y1 = 0.83;
    x2 = 0.8;
    y2 = 0.87;
  } else if( legendQuadrant==2 ) {
    x1 =  0.25;
    y1 = 0.83;
    x2 =  0.42;
    y2 = 0.87;
  } else if( legendQuadrant==3 ) {
    x1 = 0.25;
    y1 = 0.2;
    x2 = 0.42;
    y2 = 0.24;
  } else if( legendQuadrant==0 ) {
    x1 = 0.175;
    y1 = 0.953;
    x2 = 0.6;
    y2 = 0.975;
  }

  
  TPaveText* cmslabel = new TPaveText( x1, y1, x2, y2, "brNDC" );
  cmslabel->SetFillColor(kWhite);
  cmslabel->SetTextSize(0.038);
  if( legendQuadrant==0 ) cmslabel->SetTextAlign(11);
  cmslabel->SetTextSize(0.038);
  cmslabel->SetTextFont(42);
 
    std::string leftText;
   
    if(year == "2010")  leftText = "CMS Preliminary 2010, 34 pb^{-1}";
    if (sim)  leftText = "CMS Simulation"; //cwr ->remove 2011
    else {
      if(year == "2011" && run == "RUN2011A")  leftText = "CMS Preliminary RUN2011A 2.034 fb^{-1}";
      if(year == "2011" && run == "RUN2011B")  leftText = "CMS Preliminary 2011, 2.516 fb^{-1}";
      if(year == "2011" && run == "ALL")  leftText = "CMS 4.9 fb^{-1}"; //cwr ->remove 2011
      if(year == "none" && run == "ALL")  leftText = "CMS Data"; //cwr ->remove 2011
      if(year == "May2011")leftText = "CMS Preliminary 2011, 858.4 pb^{-1}";

    }
    cmslabel->AddText(leftText.c_str());
    return cmslabel;

}




TPaveText* get_labelSqrt( int legendQuadrant ) {

  if( legendQuadrant!=0 && legendQuadrant!=1 && legendQuadrant!=2 && legendQuadrant!=3 ) {
    std::cout << "WARNING! Legend quadrant '" << legendQuadrant << "' not yet implemented for Sqrt label. Using 2." << std::endl;
    legendQuadrant = 2;
  }


  float x1, y1, x2, y2;
  if( legendQuadrant==1 ) {
    x1 = 0.63;
    y1 = 0.78;
    x2 = 0.8;
    y2 = 0.82;
  } else if( legendQuadrant==2 ) {
    x1 = 0.25;
    y1 = 0.78;
    x2 = 0.42;
    y2 = 0.82;
  } else if( legendQuadrant==3 ) {
    x1 = 0.25;
    y1 = 0.16;
    x2 = 0.42;
    y2 = 0.2;
  } else if( legendQuadrant==0 ) {
    x1 = 0.65;
    y1 = 0.953;
    x2 = 0.87;
    y2 = 0.975;
  }


  TPaveText* label_sqrt = new TPaveText(x1,y1,x2,y2, "brNDC");
  label_sqrt->SetFillColor(kWhite);
  label_sqrt->SetTextSize(0.038);
  label_sqrt->SetTextFont(42);
  label_sqrt->SetTextAlign(31); // align right
  label_sqrt->AddText("#sqrt{s} = 7 TeV");
  return label_sqrt;

}

TH1F* makeRocStandard(bool isEB) {

  TFile* file_input;
  if (isEB)  {
    file_input  = new TFile("TMVAoutput_EB_standard.root", "READ");
  }  
  else  {
    file_input  = new TFile("TMVAoutput_EE.root", "READ"); 
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
  
  if(isEB)  c_BDT->SaveAs("img/MVA_BDT_EB.png");
  else  c_BDT->SaveAs("img/MVA_BDT_EE.png");
  
  c_BDT->Close();

  TCanvas* c_correlation_S = new TCanvas("c_correlation_S", "", 1);
  TCanvas* c_correlation_B = new TCanvas("c_correlation_B", "", 1);

  c_correlation_S->cd();
  CorrelationMatrixS->Draw("colz");
  if(isEB)   c_correlation_S->SaveAs("img/correlationS_EB.png");
  else c_correlation_S->SaveAs("img/correlationS_EE.png");
  c_correlation_S->Close();

  c_correlation_B->cd();
  CorrelationMatrixB->Draw("colz");
  if(isEB) c_correlation_B->SaveAs("img/correlationB_EB.png");
  else  c_correlation_B->SaveAs("img/correlationB_EE.png");
  c_correlation_B->Close();
  
  TCanvas* c_BDT_rejBvsS = new TCanvas("c_BDT_rejBvsS", "", 1);

  c_BDT_rejBvsS->cd();
  MVA_BDT_rejBvsS->Draw("P");
  if(isEB) c_BDT_rejBvsS->SaveAs("img/ROCcurve_EB.png");
  else c_BDT_rejBvsS->SaveAs("img/ROCcurve_EE.png");
  c_BDT_rejBvsS->Close();



  return MVA_BDT_rejBvsS;
}








TH1F* makeRocChi(bool isEB) {

  TFile* file_input;
  if (isEB)  {
    file_input  = new TFile("TMVAoutput_EB_chi2.root", "READ");
  }  
  else  {
    file_input  = new TFile("TMVAoutput_EE_chi2.root", "READ"); 
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
  
  if(isEB)  c_BDT->SaveAs("img/MVA_BDT_EB_chi.png");
  else  c_BDT->SaveAs("img/MVA_BDT_EE_chi.png");
  
  c_BDT->Close();

  TCanvas* c_correlation_S = new TCanvas("c_correlation_S", "", 1);
  TCanvas* c_correlation_B = new TCanvas("c_correlation_B", "", 1);

  c_correlation_S->cd();
  CorrelationMatrixS->Draw("colz");
  if(isEB)   c_correlation_S->SaveAs("img/correlationS_EB_chi.png");
  else c_correlation_S->SaveAs("img/correlationS_EE_chi.png");
  c_correlation_S->Close();

  c_correlation_B->cd();
  CorrelationMatrixB->Draw("colz");
  if(isEB) c_correlation_B->SaveAs("img/correlationB_EB_chi.png");
  else  c_correlation_B->SaveAs("img/correlationB_EE_chi.png");
  c_correlation_B->Close();
  
  TCanvas* c_BDT_rejBvsS = new TCanvas("c_BDT_rejBvsS", "", 1);

  c_BDT_rejBvsS->cd();
  MVA_BDT_rejBvsS->Draw("P");
  if(isEB) c_BDT_rejBvsS->SaveAs("img/ROCcurve_EB_chi.png");
  else c_BDT_rejBvsS->SaveAs("img/ROCcurve_EE_chi.png");
  c_BDT_rejBvsS->Close();



  return MVA_BDT_rejBvsS;
}



void makeRocSuperimposed(){

  TH1F* rocStandard = makeRocStandard(true);
  TH1F* rocChi = makeRocChi(true);

  rocStandard ->SetLineColor(kRed);
  rocChi ->SetLineColor(kBlue);

  TLegend* leg = new TLegend(0.2, 0.3, 0.4, 0.5);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(rocStandard, "Standard MVA", "L");
  leg->AddEntry(rocChi, "With #chi^2_{time}", "L");

  TPaveText* label_cms_mc = get_labelCMS(0, "2012", true, "ALL");
  TPaveText* label_sqrt = get_labelSqrt(0);

  TCanvas* c = new TCanvas("c", "", 1);
  c->cd();
  rocStandard -> Draw("hist");
  rocChi -> Draw("histsame");
  leg->Draw("same");
  label_cms_mc->Draw("same");
  label_sqrt->Draw("same");
  c->SaveAs("img/RocSuperimposed.png");
}
