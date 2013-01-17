#define fillPlot2012_gammaJets_cxx
#include "../interface/fillPlot2012_gammaJets.h"
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

TH1D * fillPlot2012_gammaJets::Plot(string var, string name, int nbin, double min, double max, int signal) {
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  TH1D * tempplot = new TH1D(name.c_str(),name.c_str(),nbin,min,max);
  tempplot->Sumw2();

  ofstream outfile;
  TFile* fOut=0;
  
  if (writeRoot != "") {
    string filename(writeRoot);
    fOut=TFile::Open(filename.c_str(),"RECREATE"); 
    fOut->cd();
  }
  if (writetxt != "") {
    string filename(writetxt);
    outfile.open(filename.c_str()); 
  }

  int enMax = nentries; 
  // if (enMax>10000) enMax = 10000;                    // chiara
  for (Long64_t jentry=0; jentry<enMax;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    // analysis cuts

    // patological events
    if(npu>=60) continue;    
    
    // chiara
    // preselezione legata al trigger - se non messa gia' nel dumpatore, che sarebbe meglio (anche perche' cosi' e' su tutti i gamma, qui uno solo)
    // il fotone nel tree e' quello a piu' alto pT che passa la preselezione, che al momento non c'e' a parte tagli eta/pT/eleVeto  
    // NB: questa selezione non e' applicata su tutti gli HLT path, da vedere 
    bool is_CaloIdVL_IsolL = true;
    if(pid_hlwTrack04phot1 > 3.5 + 0.002*ptphot1) is_CaloIdVL_IsolL = false;
    if(pid_jurECAL04phot1  > 5.5 + 0.012*ptphot1) is_CaloIdVL_IsolL = false;
    if(pid_twrHCAL04phot1  > 3.5 + 0.005*ptphot1) is_CaloIdVL_IsolL = false;
    bool iseb=1;
    if (TMath::Abs(etascphot1)>1.4442) iseb=0;
    if(iseb) {
      if(pid_sigmaIeIephot1>0.024) is_CaloIdVL_IsolL = false;
      if(pid_HoverEphot1>0.15)     is_CaloIdVL_IsolL = false;
    }
    if(!iseb) {
      if(pid_sigmaIeIephot1>0.040) is_CaloIdVL_IsolL = false;
      if(pid_HoverEphot1>0.10)     is_CaloIdVL_IsolL = false;
    }
    if (!is_CaloIdVL_IsolL) continue;
    
    // photon acceptance
    if((TMath::Abs(etascphot1)>1.4442 && TMath::Abs(etascphot1)<1.566) || TMath::Abs(etascphot1)>2.5) continue;  

    // photon pT
    if(ptphot1<ptphot1cut) continue;        

    // splitting between EB and EE
    int myEB=2; 
    if (TMath::Abs(etascphot1)>1.4442) myEB=0;
    if (TMath::Abs(etascphot1)<1.4442) myEB=1;

    // photon id as in 2011 Wgamma analysis
    bool isVgamma2011        = false;
    bool isVgamma2011_idOnly = false;
    
    float Rho25 = rhoPF;    // chiara: che rho e', controlla
    float ATr = 0.0167;  
    float AEc = 0.183;   
    float AHc = 0.062;   
    if (!myEB) {
      ATr = 0.032;
      AEc = 0.090;
      AHc = 0.180;
    }

    // full Id + Isolation
    float sigmaIetaIetaMax = 0.011 ;
    if(!myEB) sigmaIetaIetaMax = 0.03;
    if(pid_hlwTrack04phot1  < 2.0 + 0.001*ptphot1 + ATr*Rho25)     
      if(pid_jurECAL04phot1 < 4.2 + 0.006*ptphot1 + AEc*Rho25) 
	if(pid_twrHCAL04phot1 < 2.2 + 0.0025*ptphot1 + AHc*Rho25)
	  if(pid_sigmaIeIephot1<sigmaIetaIetaMax)
	    if(!pid_haspixelseedphot1)    
	      if(!myEB || (myEB && pid_sigmaIeIephot1 > 0.001)) // additional EB spike cleaning 
		                                                // chiara, c'era anche un taglio su IphiIphi, che pero' manca nelle ntuple
		if(pid_HoverEphot1<0.05) isVgamma2011 = true;  
    
    // --- Vgamma2011 photon id w/o isolation
    if(pid_sigmaIeIephot1<sigmaIetaIetaMax)
      if(!pid_haspixelseedphot1)   
	if(!myEB || (myEB && pid_sigmaIeIephot1 > 0.001)) 
	  if(pid_HoverEphot1<0.05) isVgamma2011_idOnly = true;

    // chiara: usa quella che serve
    if(!isVgamma2011_idOnly) continue;   
    // if(!isVgamma2011) continue;             

    // reco gammas matching the MC truth - only for plots
    // for the analysis we consider all gammas 
    bool isGenGamma = false;
    float theDR = sqrt(delta_eta(etaphot1,gen_eta_gamma1)*delta_eta(etaphot1,gen_eta_gamma1) +
		       delta_phi(phiphot1,gen_phi_gamma1)*delta_phi(phiphot1,gen_phi_gamma1) );
    if (theDR<0.1) isGenGamma = true;

    // finding variable to be plotted
    double variable(0);
    if (var == "ptphot1")         variable = ptphot1;
    else if (var == "etaphot1")   variable = TMath::Abs(etaphot1);
    else if (var == "phiphot1")   variable = phiphot1;
    else if (var == "nvtx")       variable = nvtx;
    else if (var == "npu")        variable = npu;
    else if (var == "sigmaIeIe")  variable = pid_sigmaIeIephot1;         
    else if (var == "HoE")        variable = pid_HoverEphot1;
    else if (var == "trackerIso") variable = pid_hlwTrack04phot1;
    else if (var == "ecalIso")    variable = pid_jurECAL04phot1;
    else if (var == "hcalIso")    variable = pid_twrHCAL04phot1;
    else if (var == "chargedIso") variable = pid_pfIsoCharged04phot1;
    else if (var == "neutralIso") variable = pid_pfIsoNeutrals04phot1;
    else if (var == "gammaIso")   variable = pid_pfIsoPhotons04phot1;
    else if (var == "pfIso")      variable = pid_pfIsoCharged04phot1 + pid_pfIsoNeutrals04phot1 + pid_pfIsoPhotons04phot1;
    else{
      cout << "NO SUCH VARIABLE IMPLEMENTED!" << endl;
      break;
    }
    
    // pu/pt reweighting
    float weight(1);
    if(dopureweight) weight *= pu_weight;
    
    if ( (signal!=18 && signal!=19) )                tempplot->Fill(variable, weight);
    if ( (signal==18 || signal==19) && isGenGamma )  tempplot->Fill(variable, weight);
  }
  
  if (writeRoot != "") fOut->Write();
  if (writetxt != "")  outfile.close(); 

  return tempplot;
}

void  fillPlot2012_gammaJets::Setcuts(double pt1, int eb, int r9) {

  ptphot1cut = pt1;
  ebcat = eb;
  r9cat = r9;
}

void fillPlot2012_gammaJets::Writetxt(char * filename) {
  writetxt=std::string(filename);
}

void fillPlot2012_gammaJets::WriteRoot(char * filename) {
  writeRoot=std::string(filename);
}

void fillPlot2012_gammaJets::DoPuReweight(){
  dopureweight = 1;
}

void fillPlot2012_gammaJets::SetPuWeights(bool isData,std::string puWeightFile) {
  
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

void fillPlot2012_gammaJets::getweights() {
  
  TFile *f  = new TFile("ptreweight.root","READ");
  
  TH1D *puweights = 0;
  
  puweights= (TH1D*) f->Get("pt2d");
  
  for (int i = 0; i<15; i++) {
    for (int j = 0; j<20; j++) {
      float weight=1.;
      weight=puweights->GetBinContent(i+1,j+1);
      weights_[i][j] =  weight;
    }
  }
}

