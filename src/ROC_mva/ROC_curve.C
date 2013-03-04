#define ROC_curve_cxx
#include "ROC_curve.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <TLorentzVector.h>
#include <TAttLine.h>
#include <TAttFill.h>
#include <THStack.h>
#include <TColor.h>
#include <TGraph.h>
#include <TPaveStats.h>
//#include <ScaleAndAddHisto.C>
#include <MyEvaluateMVA.h>

void ROC_curve::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L ROC_curve.C
//      Root > ROC_curve t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void ROC_curve::CreateROC(string var, Int_t npoints, Double_t xmin, Double_t xmax)
{
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  TH1F* hist_sig_barrel = new TH1F("sig_barrel", "sig_barrel", npoints, xmin, xmax);
  TH1F* hist_bg_barrel  = new TH1F("bg_barrel", "bg_barrel", npoints, xmin, xmax);
				
  TH1F* hist_sig_endcap = new TH1F("sig_endcap", "sig_endcap", npoints, xmin, xmax);
  TH1F* hist_bg_endcap  = new TH1F("bg_endcap", "bg_endcap", npoints, xmin, xmax);

  MyEvaluateMVA* a = new MyEvaluateMVA();
  a->SetEBWeights("/afs/cern.ch/work/v/vtavolar/TesiMagistrale/CMSSW_5_2_3/src/GammaJets/src/ROC_mva/weightsEB/TMVAClassification_BDT.weights.xml");
  a->SetEEWeights("/afs/cern.ch/work/v/vtavolar/TesiMagistrale/CMSSW_5_2_3/src/GammaJets/src/ROC_mva/weightsEE/TMVAClassification_BDT.weights.xml");
  a->SetAllMVA();

  float var_for_mva[9]={0};

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    for(Int_t k=0; k<nPhot_presel; k++){
      if(fabs(etascPhot_presel[k])<1.442){
	if(isMatchedPhot[k]==1){
	  hist_sig_barrel->Fill(ReturnValue(var, k, &var_for_mva, a));
	}
	if(isMatchedPhot[k]==0){
	  hist_bg_barrel->Fill(ReturnValue(var, k, &var_for_mva, a));
	}
      }
      if(fabs(etascPhot_presel[k])>1.566 && fabs(etascPhot_presel[k])<2.5){
	if(isMatchedPhot[k]==1){
	  hist_sig_endcap->Fill(ReturnValue(var, k, &var_for_mva, a));
	}
	if(isMatchedPhot[k]==0){
	  hist_bg_endcap->Fill(ReturnValue(var, k, &var_for_mva, a));
	}
      }
    }
    // if (Cut(ientry) < 0) continue;
  }


  cout<<"barrel"<<hist_sig_barrel->GetEntries()<<" sig "<<hist_bg_barrel->GetEntries()<<" bg"<<endl;
  cout<<"endcaps"<<hist_sig_endcap->GetEntries()<<" sig "<<hist_bg_endcap->GetEntries()<<" bg"<<endl;
  
  Int_t Nbins_sig_barrel = 0, Nbins_bg_barrel = 0, Nbins_sig_endcap = 0, Nbins_bg_endcap = 0;
  Nbins_sig_barrel = hist_sig_barrel->GetNbinsX() - 2;//number of bins - undeflow&overflow bins
  Nbins_bg_barrel  = hist_bg_barrel->GetNbinsX() - 2;
  Nbins_sig_endcap = hist_sig_endcap->GetNbinsX() - 2;
  Nbins_bg_endcap  = hist_bg_endcap->GetNbinsX() - 2; 

  Double_t denominator_sig_barrel = 0., denominator_bg_barrel = 0., denominator_sig_endcap = 0., denominator_bg_endcap = 0.;
  denominator_sig_barrel = hist_sig_barrel->Integral(0, Nbins_sig_barrel + 1);
  denominator_bg_barrel  = hist_bg_barrel->Integral(0, Nbins_bg_barrel + 1);
  denominator_sig_endcap = hist_sig_endcap->Integral(0, Nbins_sig_endcap + 1);
  denominator_bg_endcap  = hist_bg_endcap->Integral(0, Nbins_bg_endcap + 1);
  
  Double_t eff_sig_barrel[npoints]; //eff for signal of cut on ptPhot. Prova ad usa new per allocare dinam la memoria poter inizializzare a 0
  Double_t eff_bg_barrel[npoints]; //what about initialization?
  
  Double_t eff_sig_endcap[npoints];
  Double_t eff_bg_endcap[npoints]; 

  for(Int_t i=0; i<npoints; i++){
    eff_sig_barrel[i] = hist_sig_barrel->Integral(i+1, Nbins_sig_barrel + 1)/denominator_sig_barrel;
    eff_bg_barrel[i]  = 1 - hist_bg_barrel->Integral(i+1, Nbins_bg_barrel + 1)/denominator_bg_barrel; //actually 1 - eff, ready for ROC curve
    eff_sig_endcap[i] = hist_sig_endcap->Integral(i+1, Nbins_sig_endcap + 1)/denominator_sig_endcap;
    eff_bg_endcap[i]  = 1 - hist_bg_endcap->Integral(i+1, Nbins_sig_endcap + 1)/denominator_bg_endcap;
  }

  for(Int_t i=0; i<npoints; i++){
    cout<<eff_sig_endcap[i]<<" "<<eff_bg_endcap[i]<<endl;  
  }
  
  TGraph* graph_ROC_barrel = new TGraph(npoints, eff_sig_barrel, eff_bg_barrel);
  TCanvas* canvas_ROC_barrel = new TCanvas("canvas_ROC_barrel", "", 1);                 
  TGraph* graph_ROC_endcap = new TGraph(npoints, eff_sig_endcap, eff_bg_endcap);
  TCanvas* canvas_ROC_endcap = new TCanvas("canvas_ROC_endcap", "", 1);                 
  
  TFile* file_output = new TFile(("/afs/cern.ch/work/v/vtavolar/TesiMagistrale/CMSSW_5_2_3/src/GammaJets/src/ROC_mva/graph_ROC_"+var+".root").c_str(),"RECREATE");
  file_output->cd();

  hist_sig_barrel ->Write();
  hist_bg_barrel  ->Write();
			
  hist_sig_endcap ->Write();
  hist_bg_endcap  ->Write();
  
  string dir = "graphs";
  
  ostringstream ostr;
  ostr << npoints; 
  string str_npoints = ostr.str();
  
  ostr.str("");
  ostr.clear();
  ostr << xmin;
  string str_xmin = ostr.str();
  
  ostr.str("");
  ostr.clear();
  ostr.flush();
  ostr << xmax;
  string str_xmax = ostr.str();
  
  
  canvas_ROC_barrel->cd();
  TPaveText *pt = new TPaveText(.05,.05,.45,.30);
  pt->AddText((str_npoints+" equidistant points from").c_str());
  pt->AddText((var+">"+str_xmin+" to "+var+">"+str_xmax).c_str());


  graph_ROC_barrel->SetTitle(("ROC curve for cut on "+var+", BARREL").c_str());	
  graph_ROC_barrel->GetXaxis()->SetTitle("#epsilon_{sig}");	
  graph_ROC_barrel->GetXaxis()->SetLimits(0., 1.1);	
  graph_ROC_barrel->GetYaxis()->SetTitle("1 - #epsilon_{bg}");	
  graph_ROC_barrel->GetYaxis()->SetRangeUser(0., 1.1);	
  graph_ROC_barrel->Draw("A*");
  pt->Draw();
  canvas_ROC_barrel->Write();
  canvas_ROC_barrel->SaveAs((dir+"/graph_ROC_"+var+"_barrel.png").c_str());

  canvas_ROC_endcap->cd();
  graph_ROC_endcap->SetTitle(("ROC curve for cut on "+var+", ENDCAP").c_str());	
  graph_ROC_endcap->GetXaxis()->SetTitle("#epsilon_{sig}");	
  graph_ROC_endcap->GetXaxis()->SetLimits(0., 1.1);	
  graph_ROC_endcap->GetYaxis()->SetTitle("1 - #epsilon_{bg}");	
  graph_ROC_endcap->GetYaxis()->SetRangeUser(0., 1.1);
  graph_ROC_endcap->Draw("A*");
  pt->Draw();
  canvas_ROC_endcap->Write();
  canvas_ROC_endcap->SaveAs((dir+"/graph_ROC_"+var+"_endcap.png").c_str());
  
  canvas_ROC_barrel->Close();
  canvas_ROC_endcap->Close();
  
}



Double_t ROC_curve::ReturnValue(string var, Int_t index, float (*varForMva)[9], MyEvaluateMVA* t){
  if(var.compare("ptPhot_presel")==0){
    return ptPhot_presel[index];
  }
  else if(var.compare("etascPhot_presel")==0){
    return etascPhot_presel[index];
  }
  else if(var.compare("sEtaEtaPhot_presel")==0){
    return sEtaEtaPhot_presel[index];
  }
  else if(var.compare("sEtaPhiPhot_presel")==0){
    return sEtaPhiPhot_presel[index];
  }
  else if(var.compare("pid_scetawid_presel")==0){
    return pid_scetawid_presel[index];
  }
  else if(var.compare("pid_scphiwid_presel")==0){
    return pid_scphiwid_presel[index];
  }
  else if(var.compare("s4RatioPhot_presel")==0){
    return s4RatioPhot_presel[index];
  }
  else if(var.compare("r9Phot_presel")==0){
    return r9Phot_presel[index];
  }
  else if(var.compare("rr_presel")==0){
    return rr_presel[index];
  }
  else if(var.compare("mva")==0){
    (*varForMva)[0] = pid_scetawid_presel[index];
    (*varForMva)[1] = pid_scphiwid_presel[index];
    (*varForMva)[2] = sEtaEtaPhot_presel[index];
    (*varForMva)[3] = sEtaPhiPhot_presel[index];
    (*varForMva)[4] = s4RatioPhot_presel[index];
    (*varForMva)[5] = r9Phot_presel[index];
    (*varForMva)[6] = ptPhot_presel[index];
    (*varForMva)[7] = etascPhot_presel[index];
    (*varForMva)[8] = rr_presel[index];
    return (Double_t) (t->ComputeMVAValue(varForMva));
  }
  else{
    return -9999999;
  }
}
