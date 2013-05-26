#define fillPlot2012_doubleEle_cxx
#include "fillPlot2012_doubleEle.h"
#include <TH2.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TMath.h>

#define MAX_PU_REWEIGHT 60

inline double delta_phi(double phi1, double phi2) {

  double dphi = TMath::Abs(phi1 - phi2);
  return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
}

inline double delta_eta(double eta1, double eta2) {

  return (eta2 >= 0 ? eta1 - eta2 : eta2 - eta1);
}

void fillPlot2012_doubleEle::Plot(TH1D* plots_EB[], TH1D* plots_EE[],  int signal) {
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  

  ofstream outfile;

  if (writetxt != "") {
    string filename(writetxt);
    outfile.open(filename.c_str()); 
  }


  // Loop over entries
  int enMax = nentries; 
  for (Long64_t jentry=0; jentry<enMax;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (jentry%100000==0) cout << jentry << endl;

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // patological events
    if (npu>=60) continue;    

    // test to remove possible duplicated events between samples
    // if ( signal<6 && (ISRGamma>0 || FSRGamma>0) ) continue; // chiara

    // first vertex must be good
    if (vtxId<0) continue;

    //if(isHLT_30())   cout << "before calling isHLT_30" << endl;

    // HLT selection - for data only
    if ( signal==100 && hltcut==30 && !isHLT_30() )  continue;
    if ( signal==100 && hltcut==50 && !isHLT_50() )  continue;
    if ( signal==100 && hltcut==75 && !isHLT_75() )  continue;
    if ( signal==100 && hltcut==90 && !isHLT_90() )  continue;

    //if(isHLT_30()) cout << "after calling isHLT_30" << endl;

    // vector with index of fully selected gammas
    vector<int> fullSelected;


    // pu/pt reweighting for mc only
    
    float weight(1);
    if (dopureweight && hltcut==30) weight *= (pu_weight30);
    if (dopureweight && hltcut==50) weight *= (pu_weight50);
    if (dopureweight && hltcut==75) weight *= (pu_weight75);
    if (dopureweight && hltcut==90) weight *= (pu_weight90);


    int edge_phot;
    if(edge_phot>20) edge_phot = 20;
    else edge_phot = nPhot;
    for(int iPhot=0; iPhot<edge_phot; iPhot++) {
      //data, not pu reweight
      if(signal == 100) {
	if(isEleProbe[iPhot] && isEBPhot[iPhot]) {
	  plots_EB[0]->Fill(ptPhot[iPhot]);
	  plots_EB[1]->Fill(etascPhot[iPhot]);
	  plots_EB[2]->Fill(pid_etawid[iPhot]);
	  plots_EB[3]->Fill(sEtaPhiPhot[iPhot]);
	  plots_EB[4]->Fill(pid_scetawid[iPhot]);
	  plots_EB[5]->Fill(pid_scphiwid[iPhot]);
	  plots_EB[6]->Fill(r9Phot[iPhot]);
	  plots_EB[7]->Fill(s4RatioPhot[iPhot]);
	  plots_EB[8]->Fill(pid_HoverE[iPhot]);
	  plots_EB[9]->Fill(rhoAllJets);
	  plots_EB[10]->Fill(BDT_output[iPhot]);
	
	}
	
	if(isEleProbe[iPhot] && isEEPhot[iPhot]) {
	  plots_EE[0]->Fill(ptPhot[iPhot]);
	  plots_EE[1]->Fill(etascPhot[iPhot]);
	  plots_EE[2]->Fill(pid_etawid[iPhot]);
	  plots_EE[3]->Fill(sEtaPhiPhot[iPhot]);
	  plots_EE[4]->Fill(pid_scetawid[iPhot]);
	  plots_EE[5]->Fill(pid_scphiwid[iPhot]);
	  plots_EE[6]->Fill(r9Phot[iPhot]);
	  plots_EE[7]->Fill(s4RatioPhot[iPhot]);
	  plots_EE[8]->Fill(pid_HoverE[iPhot]);
	  plots_EE[9]->Fill(rhoAllJets);
	  plots_EE[10]->Fill(BDT_output[iPhot]);
	  plots_EE[11]->Fill(sigmaRRPhot[iPhot]);
	}
      }
      //mc, pu reweight
      else if (signal == 0){
	if(isEleProbe_match[iPhot] && isEBPhot[iPhot]) {
	  /*
	  if(dopureweight){
	    cout << "dopureweight: " << dopureweight << endl;
	    //      cout << "pu_weight30: " << pu_weight30 << "  pu_weight50: " << pu_weight50 << "   pu_weight75: " << pu_weight75 << "  pu_weight90: " << pu_weight90 << endl;
	    cout << "weight: " << weight << endl;
	    cout << "signal: " << signal << endl;
	  }
	  */

	  plots_EB[0]->Fill(ptPhot[iPhot],weight);
	  plots_EB[1]->Fill(etascPhot[iPhot],weight);
	  plots_EB[2]->Fill(pid_etawid[iPhot],weight);
	  plots_EB[3]->Fill(sEtaPhiPhot[iPhot],weight);
	  plots_EB[4]->Fill(pid_scetawid[iPhot],weight);
	  plots_EB[5]->Fill(pid_scphiwid[iPhot], weight);
	  plots_EB[6]->Fill(r9Phot[iPhot], weight);
	  plots_EB[7]->Fill(s4RatioPhot[iPhot], weight);
	  plots_EB[8]->Fill(pid_HoverE[iPhot], weight);
	  plots_EB[9]->Fill(rhoAllJets, weight);
	  plots_EB[10]->Fill(BDT_output[iPhot], weight);
	
	}
	
	if(isEleProbe_match[iPhot] && isEEPhot[iPhot]) {
	  plots_EE[0]->Fill(ptPhot[iPhot],weight);
	  plots_EE[1]->Fill(etascPhot[iPhot],weight);
	  plots_EE[2]->Fill(pid_etawid[iPhot],weight);
	  plots_EE[3]->Fill(sEtaPhiPhot[iPhot],weight);
	  plots_EE[4]->Fill(pid_scetawid[iPhot],weight);
	  plots_EE[5]->Fill(pid_scphiwid[iPhot], weight);
	  plots_EE[6]->Fill(r9Phot[iPhot], weight);
	  plots_EE[7]->Fill(s4RatioPhot[iPhot], weight);
	  plots_EE[8]->Fill(pid_HoverE[iPhot], weight);
	  plots_EE[9]->Fill(rhoAllJets, weight);
	  plots_EE[10]->Fill(BDT_output[iPhot], weight);
	  plots_EE[11]->Fill(sigmaRRPhot[iPhot], weight);
	}
      }
    }
    

  }
  
  if (writetxt != "")  outfile.close(); 


}

void  fillPlot2012_doubleEle::Setcuts(double pt1min, double pt1max, int eb, int r9, int HLTth) {

  ptphot1_mincut = pt1min;
  ptphot1_maxcut = pt1max;
  ebcat = eb;
  r9cat = r9;
  hltcut = HLTth;
}

void fillPlot2012_doubleEle::Writetxt(char * filename) {
  writetxt=std::string(filename);
}

void fillPlot2012_doubleEle::WriteRoot(char * filename) {
  writeRoot=std::string(filename);
}

void fillPlot2012_doubleEle::DoPuReweight(){
  dopureweight = 1;
}

void fillPlot2012_doubleEle::SetPuWeights(bool isData,std::string puWeightFile) {
  
  if (puWeightFile == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }
  
  if (!isData)
    std::cout << "PU REWEIGHTING:: Using file " << puWeightFile << std::endl;
  
  TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  
  TH1D *puweights = 0;
  TH1D *gen_pu = 0;

  gen_pu= (TH1D*) f_pu->Get("generated_pu");
  puweights= (TH1D*) f_pu->Get("weights");
  
  if (!puweights || !gen_pu)  {
    std::cout << "weights histograms  not found in file " << puWeightFile << std::endl;
    return;
  }
  
  TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
  weightedPU->Multiply(puweights);

  //Rescaling weights in order to preserve same integral of events
  TH1D* weights= (TH1D*)puweights->Clone("rescaledWeights");
  weights->Scale( gen_pu->Integral(1,MAX_PU_REWEIGHT) / weightedPU->Integral(1,MAX_PU_REWEIGHT) );
		  
  float sumPuWeights=0.;

  for (int i = 0; i<MAX_PU_REWEIGHT; i++) {
    float weight=1.;
    if( !isData ) weight=weights->GetBinContent(i+1);

    sumPuWeights+=weight;
    puweights_.push_back(weight);
  }
}

bool fillPlot2012_doubleEle::isHLT_30() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v18") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v19") isok=true;
  }
  return isok;
}

bool fillPlot2012_doubleEle::isHLT_50() {

  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v17") isok=true;
  }
  return isok;
}

bool fillPlot2012_doubleEle::isHLT_75() {
  
  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v18") isok=true;
  }
  return isok;
}

bool fillPlot2012_doubleEle::isHLT_90() {
  
  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v13") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v15") isok=true;
  }
  return isok;
}

bool fillPlot2012_doubleEle::isHLT_150() {
  bool isok = false;
  for (int ii=0; ii<(int)firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v1") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v2") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v3") isok=true;
  }
  return isok;
}
