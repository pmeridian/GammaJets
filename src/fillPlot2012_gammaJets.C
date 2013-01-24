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

  if (writetxt != "") {
    string filename(writetxt);
    outfile.open(filename.c_str()); 
  }

  // Loop over entries
  int enMax = nentries; 
  for (Long64_t jentry=0; jentry<enMax;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    // patological events
    if(npu>=60) continue;    

    // passing reco preselection
    if(vtxId<0) continue;    

    // first vertex must be good
    if(vtxId>0) continue;
    
    // checking all preselected gammas to apply the full selection
    std::vector<int> _vgamma2011_idOnly_gammas;
    std::vector<int> _vgamma2011_gammas;
    for (int theGamma=0; theGamma<ngammas; theGamma++) {

      // classification: EB, EE, highR9, lowR9 
      int myEB=2; 
      int myR9=2;
      if (TMath::Abs(etascphot[theGamma])>1.4442) myEB=0;
      if (TMath::Abs(etascphot[theGamma])<1.4442) myEB=1;
      if (r9phot[theGamma]<0.94)  myR9=0;
      if (r9phot[theGamma]>=0.94) myR9=1;
      int hggCat=4;
      if (myEB && myR9)   hggCat=0;
      if (myEB && !myR9)  hggCat=1;
      if (!myEB && myR9)  hggCat=2;
      if (!myEB && !myR9) hggCat=3;
      
      // chiara: HLT preselection. NB: questa selezione non e' applicata su tutti gli HLT path, da studiare
      // oltre a questo nel dumpatore: ET>30, pid_twrHCAL[i]>4, !hasMatchedPromptElePhot
      bool is_CaloIdVL_IsolL = true;
      if(pid_hlwTrack04phot[theGamma] > 3.5 + 0.002*ptphot[theGamma]) is_CaloIdVL_IsolL = false;
      if(pid_jurECAL04phot[theGamma]  > 5.5 + 0.012*ptphot[theGamma]) is_CaloIdVL_IsolL = false;
      if(pid_twrHCAL04phot[theGamma]  > 3.5 + 0.005*ptphot[theGamma]) is_CaloIdVL_IsolL = false;
      if(myEB) {
	if(pid_sigmaIeIephot[theGamma]>0.024) is_CaloIdVL_IsolL = false;
	if(pid_HoverEphot[theGamma]>0.15)     is_CaloIdVL_IsolL = false;
      }
      if(!myEB) {
	if(pid_sigmaIeIephot[theGamma]>0.040) is_CaloIdVL_IsolL = false;
	if(pid_HoverEphot[theGamma]>0.10)     is_CaloIdVL_IsolL = false;
      }
      if (!is_CaloIdVL_IsolL) continue;
    
      // photon acceptance
      if((TMath::Abs(etascphot[theGamma])>1.4442 
	  && TMath::Abs(etascphot[theGamma])<1.566) || TMath::Abs(etascphot[theGamma])>2.5) continue;  

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
      if(pid_hlwTrack04phot[theGamma]  < 2.0 + 0.001*ptphot[theGamma] + ATr*Rho25)     
	if(pid_jurECAL04phot[theGamma] < 4.2 + 0.006*ptphot[theGamma] + AEc*Rho25) 
	  if(pid_twrHCAL04phot[theGamma] < 2.2 + 0.0025*ptphot[theGamma] + AHc*Rho25)
	    if(pid_sigmaIeIephot[theGamma]<sigmaIetaIetaMax)
	      if(!pid_hasMatchedPromptElephot[theGamma])    // chiara: diverso da 2011
		if(!myEB || (myEB && pid_sigmaIeIephot[theGamma] > 0.001)) // additional EB spike cleaning 
		  // chiara, c'era anche un taglio su IphiIphi, che pero' manca nelle ntuple
		  if(pid_HoverEphot[theGamma]<0.05) isVgamma2011 = true;  
      
      // --- Vgamma2011 photon id w/o isolation
      if(pid_sigmaIeIephot[theGamma]<sigmaIetaIetaMax)
	if(!pid_hasMatchedPromptElephot[theGamma])        // chiara: diverso da 2011
	  if(!myEB || (myEB && pid_sigmaIeIephot[theGamma] > 0.001)) 
	    if(pid_HoverEphot[theGamma]<0.05) isVgamma2011_idOnly = true;

      // chiara: vedi se serve anche un taglio extra per pulire meglio
      // bool dRToTrack;
      // if (hggCat==0) dRToTrack = (pid_deltaRToTrackphot[theGamma])>1;
      // if (hggCat==1) dRToTrack = (pid_deltaRToTrackphot[theGamma])>0.062;
      // if (hggCat==2) dRToTrack = (pid_deltaRToTrackphot[theGamma])>0.97;
      // if (hggCat==3) dRToTrack = (pid_deltaRToTrackphot[theGamma])>0.97;
      // if (!dRToTrack) isVgamma2011 = false;
      // if (!dRToTrack) isVgamma2011_idOnly = false;

      if(isVgamma2011_idOnly) _vgamma2011_idOnly_gammas.push_back(theGamma);  
      if(isVgamma2011)        _vgamma2011_gammas.push_back(theGamma);  
    }

    // at least one gamma passing the wanted ID - chiara, usa quella che serve 
    // if (_vgamma2011_idOnly_gammas.size()==0) continue;
    // int myLeadGamma = _vgamma2011_idOnly_gammas[0];
    if (_vgamma2011_gammas.size()==0) continue;
    int myLeadGamma = _vgamma2011_gammas[0];

    // photon pT
    if(ptphot[myLeadGamma]<ptphot1cut) continue;        

    // chiara: possibile rimozione di W/Z usando un bool sui leptoni
    // if (oneTightIsoMu) continue;
    // if (oneWP80Ele) continue;    
    // if (oneLooseIsoMu) continue;
    // if (oneHwwEle) continue;    

    // reco gammas matching the MC truth - only for plots
    // for the analysis we consider all gammas 
    bool isGenGamma = false;
    float theDR = sqrt(delta_eta(etaphot[myLeadGamma],gen_eta_gamma1)*delta_eta(etaphot[myLeadGamma],gen_eta_gamma1) +
		       delta_phi(phiphot[myLeadGamma],gen_phi_gamma1)*delta_phi(phiphot[myLeadGamma],gen_phi_gamma1) );
    if (theDR<0.1) isGenGamma = true;

    // bool leadEB = false;
    // if (TMath::Abs(etascphot[myLeadGamma])<1.4442) leadEB=1;
    // if (leadEB) continue;

    // finding variable to be plotted
    double variable(0);
    if (var == "ptphot")          variable = ptphot[myLeadGamma];
    else if (var == "etaphot")    variable = TMath::Abs(etaphot[myLeadGamma]);
    else if (var == "phiphot")    variable = phiphot[myLeadGamma];
    else if (var == "nvtx")       variable = nvtx;
    else if (var == "npu")        variable = npu;
    else if (var == "sigmaIeIe")  variable = pid_sigmaIeIephot[myLeadGamma];         
    else if (var == "HoE")        variable = pid_HoverEphot[myLeadGamma];
    else if (var == "trackerIso") variable = pid_hlwTrack04phot[myLeadGamma];
    else if (var == "ecalIso")    variable = pid_jurECAL04phot[myLeadGamma];
    else if (var == "hcalIso")    variable = pid_twrHCAL04phot[myLeadGamma];
    else if (var == "chargedIso") variable = pid_pfIsoCharged04phot[myLeadGamma];
    else if (var == "neutralIso") variable = pid_pfIsoNeutrals04phot[myLeadGamma];
    else if (var == "gammaIso")   variable = pid_pfIsoPhotons04phot[myLeadGamma];
    else if (var == "pfIso")      variable = pid_pfIsoCharged04phot[myLeadGamma] + pid_pfIsoNeutrals04phot[myLeadGamma] + pid_pfIsoPhotons04phot[myLeadGamma];
    else if (var == "oneTightIsoMu") variable = oneTightIsoMu;
    else if (var == "oneLooseIsoMu") variable = oneLooseIsoMu;
    else if (var == "oneHwwEle")     variable = oneHwwEle;
    else if (var == "oneHzzEle")     variable = oneHzzEle;
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

