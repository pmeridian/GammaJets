#include "TFile.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TTree.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TStyle.h"

#include "iostream"

void calculate_weights(){

  gStyle->SetOptStat(0);

  // input: v6
  TChain mc("finalTree");
  mc.Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/G_Pt*root");
  mc.Add("/cmsrm/pc24/crovelli/GammaJets/ridottissime/QCDEM*root");

  // output
  std::string outputDir = "histo_v6/genIso/isoWeight/";
  TFile* outputFile = new TFile((outputDir+"isoWeights.root").c_str(), "RECREATE");
  outputFile->cd();

  // histos
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EB    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EB"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EB = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EB", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EE    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EE"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EE = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EE", "", 60, -5., 15.);

  TH1F* combPfIsoFPR03Phot_matched_passMVA_EB    = new TH1F("combPfIsoFPR03Phot_matched_passMVA_EB"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_matched_notPassMVA_EB = new TH1F("combPfIsoFPR03Phot_matched_notPassMVA_EB", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_matched_passMVA_EE    = new TH1F("combPfIsoFPR03Phot_matched_passMVA_EE"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_matched_notPassMVA_EE = new TH1F("combPfIsoFPR03Phot_matched_notPassMVA_EE", "", 60, -5., 15.);

  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65", "", 60, -5., 15.);
									   
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90", "", 60, -5., 15.);
									   
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105", "", 60, -5., 15.);
									   
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105", "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105    = new TH1F("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105"   , "", 60, -5., 15.);
  TH1F* combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105 = new TH1F("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105", "", 60, -5., 15.);

  // errors
  combPfIsoFPR03Phot_notMatched_passMVA_EB    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB -> Sumw2();
  combPfIsoFPR03Phot_notMatched_passMVA_EE    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE -> Sumw2();

  combPfIsoFPR03Phot_matched_passMVA_EB    -> Sumw2();
  combPfIsoFPR03Phot_matched_notPassMVA_EB -> Sumw2();
  combPfIsoFPR03Phot_matched_passMVA_EE    -> Sumw2();
  combPfIsoFPR03Phot_matched_notPassMVA_EE -> Sumw2();

  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65 -> Sumw2();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65 -> Sumw2();
  
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90 -> Sumw2();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90 -> Sumw2();
  
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105 -> Sumw2();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105 -> Sumw2();
  
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105 -> Sumw2();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105    -> Sumw2();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105 -> Sumw2();

  // WP95
  std::string passMVA_EB, notPassMVA_EB, passMVA_EE, notPassMVA_EE;
  passMVA_EB    = "(weight>0 && weight<15000) && (TMath::Abs(etaPhot)<1.4442) && (mvaIdPhot<1. && mvaIdPhot>0.766479)";
  notPassMVA_EB = "(weight>0 && weight<15000) && (TMath::Abs(etaPhot)<1.4442) && (mvaIdPhot>-1. && mvaIdPhot<0.766479)";
  passMVA_EE    = "(weight>0 && weight<15000) && (TMath::Abs(etaPhot)>1.479 && TMath::Abs(etaPhot)<2.5) && (mvaIdPhot<1. && mvaIdPhot>0.601807)";
  notPassMVA_EE = "(weight>0 && weight<15000) && (TMath::Abs(etaPhot)>1.479 && TMath::Abs(etaPhot)<2.5) && (mvaIdPhot>-1. && mvaIdPhot<0.601807)";

  // inclusive
  cout << "now projecting inclusive" << endl;
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EB",    "combinedPfIsoFPR03Phot", ("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EB", "combinedPfIsoFPR03Phot", ("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EE",    "combinedPfIsoFPR03Phot", ("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EE", "combinedPfIsoFPR03Phot", ("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+")*weight").c_str());

  cout << "now projecting inclusive signal gammas" << endl;
  mc.Project("combPfIsoFPR03Phot_matched_passMVA_EB",    "combinedPfIsoFPR03Phot", ("((isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_matched_notPassMVA_EB", "combinedPfIsoFPR03Phot", ("((isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_matched_passMVA_EE",    "combinedPfIsoFPR03Phot", ("((isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_matched_notPassMVA_EE", "combinedPfIsoFPR03Phot", ("((isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+")*weight").c_str());
	   
  // pt40_65
  cout << "now projecting 40-65" << endl;
  std::string pt = "(ptPhot>40. && ptPhot<65.)"; 
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+" && " +pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+" && "+pt+")*weight").c_str());
	  
  //pt65_90
  cout << "now projecting 65-90" << endl;
  pt = "(ptPhot>65. && ptPhot<90.)"; 
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+" && "+pt+")*weight").c_str());
	  
  //pt90_105
  cout << "now projecting 90-105" << endl;
  pt = "(ptPhot>90. && ptPhot<105.)"; 
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+" && "+pt+")*weight").c_str());

  //pt105
  cout << "now projecting 105" << endl;
  pt = "(ptPhot>105.)"; 
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EB+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105",   "combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+passMVA_EE+" && "+pt+")*weight").c_str());
  mc.Project("combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105","combinedPfIsoFPR03Phot",("(!(isMatchedPhot && iso03_gen<1.7175) && "+notPassMVA_EE+" && "+pt+")*weight").c_str());

  cout << "done with the projections" << endl;

  // normalize histos
  float integral;
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EB	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EB		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EB->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EE	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EE		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EE->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE		->Scale(1./integral);

  integral = combPfIsoFPR03Phot_matched_passMVA_EB    ->Integral();
  combPfIsoFPR03Phot_matched_passMVA_EB		      ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_matched_notPassMVA_EB ->Integral();
  combPfIsoFPR03Phot_matched_notPassMVA_EB	      ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_matched_passMVA_EE    ->Integral();
  combPfIsoFPR03Phot_matched_passMVA_EE		      ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_matched_notPassMVA_EE ->Integral();
  combPfIsoFPR03Phot_matched_notPassMVA_EE	      ->Scale(1./integral);

  integral = combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65		->Scale(1./integral);

  integral = combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90		->Scale(1./integral);

  integral = combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105	 ->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105		 ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105		 ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105	 ->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105		 ->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105		 ->Scale(1./integral);

  integral = combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105	->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105	->Integral();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105		->Scale(1./integral);
  integral = combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105	->Integral();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105		->Scale(1./integral);

  // saving in the output file
  combPfIsoFPR03Phot_notMatched_passMVA_EB	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB	->Write();
  combPfIsoFPR03Phot_notMatched_passMVA_EE	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE	->Write();

  combPfIsoFPR03Phot_matched_passMVA_EB    ->Write();
  combPfIsoFPR03Phot_matched_notPassMVA_EB ->Write();
  combPfIsoFPR03Phot_matched_passMVA_EE	   ->Write();
  combPfIsoFPR03Phot_matched_notPassMVA_EE ->Write();

  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65	->Write();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65	->Write();

  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90	->Write();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90	->Write();

  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105	->Write();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105	->Write();

  combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105	->Write();
  combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105	->Write();
  combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105	->Write();

  cout << "done with first step. Moving to the weights" << endl;

  // now computing the weights
  TH1F* h_isoWeight_EB = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EB->Clone("h_isoWeight_EB");
  h_isoWeight_EB->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EB);
  TH1F* h_isoWeight_EE = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EE->Clone("h_isoWeight_EE");
  h_isoWeight_EE->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EE);

  TH1F* h_isoWeight_EB_pt40_65 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EB_pt40_65->Clone("h_isoWeight_EB_pt40_65");
  h_isoWeight_EB_pt40_65->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt40_65);
  TH1F* h_isoWeight_EE_pt40_65 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EE_pt40_65->Clone("h_isoWeight_EE_pt40_65");
  h_isoWeight_EE_pt40_65->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt40_65);

  TH1F* h_isoWeight_EB_pt65_90 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EB_pt65_90->Clone("h_isoWeight_EB_pt65_90");
  h_isoWeight_EB_pt65_90->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt65_90);
  TH1F* h_isoWeight_EE_pt65_90 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EE_pt65_90->Clone("h_isoWeight_EE_pt65_90");
  h_isoWeight_EE_pt65_90->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt65_90);

  TH1F* h_isoWeight_EB_pt90_105 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EB_pt90_105->Clone("h_isoWeight_EB_pt90_105");
  h_isoWeight_EB_pt90_105->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt90_105);
  TH1F* h_isoWeight_EE_pt90_105 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EE_pt90_105->Clone("h_isoWeight_EE_pt90_105");
  h_isoWeight_EE_pt90_105->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt90_105);

  TH1F* h_isoWeight_EB_pt105 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EB_pt105->Clone("h_isoWeight_EB_pt105");
  h_isoWeight_EB_pt105->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EB_pt105);
  TH1F* h_isoWeight_EE_pt105 = (TH1F*)combPfIsoFPR03Phot_notMatched_passMVA_EE_pt105->Clone("h_isoWeight_EE_pt105");
  h_isoWeight_EE_pt105->Divide(combPfIsoFPR03Phot_notMatched_notPassMVA_EE_pt105);

  // weights histos
  h_isoWeight_EB->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EE->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EB->GetYaxis()->SetTitle("weight");
  h_isoWeight_EE->GetYaxis()->SetTitle("weight");

  h_isoWeight_EB->SetMarkerSize(0.8);
  h_isoWeight_EE->SetMarkerSize(0.8);
  h_isoWeight_EB->SetMarkerSize(0.8);
  h_isoWeight_EE->SetMarkerSize(0.8);

  h_isoWeight_EB->SetLineWidth(1);
  h_isoWeight_EE->SetLineWidth(1);
  h_isoWeight_EB->SetLineWidth(1);
  h_isoWeight_EE->SetLineWidth(1);

  h_isoWeight_EB->GetYaxis()->SetRangeUser(-0.5,5.);
  h_isoWeight_EE->GetYaxis()->SetRangeUser(-0.5,5.);
  
  //pt40_65
  h_isoWeight_EB_pt40_65->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EE_pt40_65->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EB_pt40_65->GetYaxis()->SetTitle("weight");
  h_isoWeight_EE_pt40_65->GetYaxis()->SetTitle("weight");

  h_isoWeight_EB_pt40_65->SetMarkerSize(0.8);
  h_isoWeight_EE_pt40_65->SetMarkerSize(0.8);
  h_isoWeight_EB_pt40_65->SetMarkerSize(0.8);
  h_isoWeight_EE_pt40_65->SetMarkerSize(0.8);

  h_isoWeight_EB_pt40_65->SetLineWidth(1);
  h_isoWeight_EE_pt40_65->SetLineWidth(1);
  h_isoWeight_EB_pt40_65->SetLineWidth(1);
  h_isoWeight_EE_pt40_65->SetLineWidth(1);

  h_isoWeight_EB_pt40_65->GetYaxis()->SetRangeUser(-0.5,5.);
  h_isoWeight_EE_pt40_65->GetYaxis()->SetRangeUser(-0.5,5.);

  //pt65_90
  h_isoWeight_EB_pt65_90->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EE_pt65_90->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EB_pt65_90->GetYaxis()->SetTitle("weight");
  h_isoWeight_EE_pt65_90->GetYaxis()->SetTitle("weight");

  h_isoWeight_EB_pt65_90->SetMarkerSize(0.8);
  h_isoWeight_EE_pt65_90->SetMarkerSize(0.8);
  h_isoWeight_EB_pt65_90->SetMarkerSize(0.8);
  h_isoWeight_EE_pt65_90->SetMarkerSize(0.8);

  h_isoWeight_EB_pt65_90->SetLineWidth(1);
  h_isoWeight_EE_pt65_90->SetLineWidth(1);
  h_isoWeight_EB_pt65_90->SetLineWidth(1);
  h_isoWeight_EE_pt65_90->SetLineWidth(1);

  h_isoWeight_EB_pt65_90->GetYaxis()->SetRangeUser(-0.5,5.);
  h_isoWeight_EE_pt65_90->GetYaxis()->SetRangeUser(-0.5,5.);

  //pt90_105
  h_isoWeight_EB_pt90_105->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EE_pt90_105->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EB_pt90_105->GetYaxis()->SetTitle("weight");
  h_isoWeight_EE_pt90_105->GetYaxis()->SetTitle("weight");

  h_isoWeight_EB_pt90_105->SetMarkerSize(0.8);
  h_isoWeight_EE_pt90_105->SetMarkerSize(0.8);
  h_isoWeight_EB_pt90_105->SetMarkerSize(0.8);
  h_isoWeight_EE_pt90_105->SetMarkerSize(0.8);

  h_isoWeight_EB_pt90_105->SetLineWidth(1);
  h_isoWeight_EE_pt90_105->SetLineWidth(1);
  h_isoWeight_EB_pt90_105->SetLineWidth(1);
  h_isoWeight_EE_pt90_105->SetLineWidth(1);

  h_isoWeight_EB_pt90_105->GetYaxis()->SetRangeUser(-0.5,5.);
  h_isoWeight_EE_pt90_105->GetYaxis()->SetRangeUser(-0.5,5.);

  //pt105
  h_isoWeight_EB_pt105->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EE_pt105->GetXaxis()->SetTitle("combinedPfIsoFPR03");
  h_isoWeight_EB_pt105->GetYaxis()->SetTitle("weight");
  h_isoWeight_EE_pt105->GetYaxis()->SetTitle("weight");

  h_isoWeight_EB_pt105->SetMarkerSize(0.8);
  h_isoWeight_EE_pt105->SetMarkerSize(0.8);
  h_isoWeight_EB_pt105->SetMarkerSize(0.8);
  h_isoWeight_EE_pt105->SetMarkerSize(0.8);

  h_isoWeight_EB_pt105->SetLineWidth(1);
  h_isoWeight_EE_pt105->SetLineWidth(1);
  h_isoWeight_EB_pt105->SetLineWidth(1);
  h_isoWeight_EE_pt105->SetLineWidth(1);

  h_isoWeight_EB_pt105->GetYaxis()->SetRangeUser(-0.5,5.);
  h_isoWeight_EE_pt105->GetYaxis()->SetRangeUser(-0.5,5.);


  // plots
  TLegend* leg=new TLegend(0.5,0.6,0.85, 0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(h_isoWeight_EB_pt40_65, "40 < p_{T}(#gamma) < 65 GeV", "p");
  leg->AddEntry(h_isoWeight_EB_pt65_90, "65 < p_{T}(#gamma) < 90 GeV", "p");
  leg->AddEntry(h_isoWeight_EB_pt90_105,"90 < p_{T}(#gamma) < 105 GeV", "p");
  leg->AddEntry(h_isoWeight_EB_pt105,   "p_{T}(#gamma) > 105 GeV", "p");

  TCanvas* c1 = new TCanvas("c1", "", 1);
  c1->cd();
  h_isoWeight_EB->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EB.png").c_str());
  c1->Clear();
  
  h_isoWeight_EE->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EE.png").c_str());
  c1->Clear();  

  h_isoWeight_EB->Write();
  h_isoWeight_EE->Write();

  //pt40_65
  h_isoWeight_EB_pt40_65->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EB_pt40_65.png").c_str());
  c1->Clear();
  
  h_isoWeight_EE_pt40_65->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EE_pt40_65.png").c_str());
  c1->Clear();
  
  h_isoWeight_EB_pt40_65->Write();
  h_isoWeight_EE_pt40_65->Write();
 
  //pt65_90
  h_isoWeight_EB_pt65_90->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EB_pt65_90.png").c_str());
  c1->Clear();
  
  h_isoWeight_EE_pt65_90->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EE_pt65_90.png").c_str());
  c1->Clear();
  
  h_isoWeight_EB_pt65_90->Write();
  h_isoWeight_EE_pt65_90->Write();


  //pt90_105
  h_isoWeight_EB_pt90_105->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EB_pt90_105.png").c_str());
  c1->Clear();
  
  h_isoWeight_EE_pt90_105->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EE_pt90_105.png").c_str());
  c1->Clear();
  
  h_isoWeight_EB_pt90_105->Write();
  h_isoWeight_EE_pt90_105->Write();


  //pt105
  h_isoWeight_EB_pt105->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EB_pt105.png").c_str());
  c1->Clear();
  
  h_isoWeight_EE_pt105->Draw("PE1");
  c1->SaveAs((outputDir+"isoWeights_EE_pt105.png").c_str());
  c1->Clear();
  
  h_isoWeight_EB_pt105->Write();
  h_isoWeight_EE_pt105->Write();

  // superimposed, EB
  h_isoWeight_EB_pt40_65  ->SetMarkerSize(0.8);
  h_isoWeight_EB_pt65_90  ->SetMarkerSize(0.8);
  h_isoWeight_EB_pt90_105 ->SetMarkerSize(0.8);
  h_isoWeight_EB_pt105    ->SetMarkerSize(0.8);

  h_isoWeight_EB_pt40_65  ->SetMarkerColor(kBlue);
  h_isoWeight_EB_pt65_90  ->SetMarkerColor(kCyan);
  h_isoWeight_EB_pt90_105 ->SetMarkerColor(kGreen);
  h_isoWeight_EB_pt105    ->SetMarkerColor(kViolet);

  h_isoWeight_EB_pt40_65  ->SetMarkerStyle(20);
  h_isoWeight_EB_pt65_90  ->SetMarkerStyle(22);
  h_isoWeight_EB_pt90_105 ->SetMarkerStyle(23);
  h_isoWeight_EB_pt105    ->SetMarkerStyle(23);

  h_isoWeight_EB_pt40_65  ->Draw("PE1");
  h_isoWeight_EB_pt65_90  ->Draw("PE1SAME");
  h_isoWeight_EB_pt90_105 ->Draw("PE1SAME");
  h_isoWeight_EB_pt105    ->Draw("PE1SAME");
  leg->Draw();
  c1->SaveAs((outputDir+"isoWeights_EB_all.png").c_str());
  c1->Clear();

  // superimposed, EE
  h_isoWeight_EE_pt40_65  ->SetMarkerSize(0.8);
  h_isoWeight_EE_pt65_90  ->SetMarkerSize(0.8);
  h_isoWeight_EE_pt90_105 ->SetMarkerSize(0.8);
  h_isoWeight_EE_pt105    ->SetMarkerSize(0.8);

  h_isoWeight_EE_pt40_65  ->SetMarkerColor(kBlue);
  h_isoWeight_EE_pt65_90  ->SetMarkerColor(kCyan);
  h_isoWeight_EE_pt90_105 ->SetMarkerColor(kGreen);
  h_isoWeight_EE_pt105    ->SetMarkerColor(kViolet);

  h_isoWeight_EE_pt40_65  ->SetMarkerStyle(20);
  h_isoWeight_EE_pt65_90  ->SetMarkerStyle(22);
  h_isoWeight_EE_pt90_105 ->SetMarkerStyle(23);
  h_isoWeight_EE_pt105    ->SetMarkerStyle(23);

  h_isoWeight_EE_pt40_65  ->Draw("PE1");
  h_isoWeight_EE_pt65_90  ->Draw("PE1SAME");
  h_isoWeight_EE_pt90_105 ->Draw("PE1SAME");
  h_isoWeight_EE_pt105    ->Draw("PE1SAME");
  leg->Draw();
  c1->SaveAs((outputDir+"isoWeights_EE_all.png").c_str());


  // some basic checks
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB->SetLineColor(6);
  combPfIsoFPR03Phot_notMatched_passMVA_EB->SetLineColor(3);
  TLegend* leg2=new TLegend(0.5,0.6,0.85, 0.8);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->AddEntry(combPfIsoFPR03Phot_notMatched_notPassMVA_EB, "not matched, Bregion", "l");
  leg2->AddEntry(combPfIsoFPR03Phot_notMatched_passMVA_EB, "not matched, Sregion", "l");
  combPfIsoFPR03Phot_notMatched_passMVA_EB->DrawNormalized("hist");
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB->DrawNormalized("histsame");
  leg2->Draw();
  c1->SaveAs((outputDir+"fotoniDiFondo_cheNONPassanoMVA_chePassanoMVA.png").c_str());
  c1->Clear();

  combPfIsoFPR03Phot_notMatched_passMVA_EB->SetLineColor(4);
  combPfIsoFPR03Phot_matched_passMVA_EB->SetLineColor(2);
  TLegend* leg3=new TLegend(0.5,0.6,0.85, 0.8);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(0);
  leg3->AddEntry(combPfIsoFPR03Phot_notMatched_passMVA_EB, "not matched, Sregion", "l");
  leg3->AddEntry(combPfIsoFPR03Phot_matched_passMVA_EB, "matched, Sregion", "l");
  combPfIsoFPR03Phot_matched_passMVA_EB->DrawNormalized("hist");
  combPfIsoFPR03Phot_notMatched_passMVA_EB->DrawNormalized("histsame");
  leg3->Draw();
  c1->SaveAs((outputDir+"fotoniDiSegnale_fotoniDiFondo_chePassanoMVA.png").c_str());
  c1->Clear();

  combPfIsoFPR03Phot_notMatched_notPassMVA_EB->SetLineColor(4);
  combPfIsoFPR03Phot_matched_notPassMVA_EB->SetLineColor(2);
  TLegend* leg4=new TLegend(0.5,0.6,0.85, 0.8);
  leg4->SetBorderSize(0);
  leg4->SetFillColor(0);
  leg4->AddEntry(combPfIsoFPR03Phot_notMatched_notPassMVA_EB, "not matched, Bregion", "l");
  leg4->AddEntry(combPfIsoFPR03Phot_matched_notPassMVA_EB, "matched, Bregion", "l");
  combPfIsoFPR03Phot_matched_notPassMVA_EB->DrawNormalized("hist");
  combPfIsoFPR03Phot_notMatched_notPassMVA_EB->DrawNormalized("histsame");
  leg4->Draw();
  c1->SaveAs((outputDir+"fotoniDiSegnale_fotoniDiFondo_cheNonPassanoMVA.png").c_str());
  c1->Clear();

  c1->Close();
  
  outputFile->Close();
}
