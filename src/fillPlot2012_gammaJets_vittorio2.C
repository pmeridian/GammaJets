#define fillPlot2012_gammaJets_vittorio2_cxx
#include "../interface/fillPlot2012_gammaJets_vittorio2.h"
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

void fillPlot2012_gammaJets_vittorio2::Plot(string var, string name, vector<TH1D*>& tempplot, int nbin, double min, double max, int signal, int split) {
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  /*  vector<TH1D*> tempplot;

  TH1D* hist_sig_EB = new TH1D("hist_sig_EB", (name+"_sig_EB").c_str() ,nbin,min,max);
  hist_sig_EB->Sumw2();
  tempplot.push_back(hist_sig_EB);

  TH1D* hist_sig_EE = new TH1D("hist_sig_EE", (name+"_sig_EE").c_str() ,nbin,min,max);
  hist_sig_EE->Sumw2();
  tempplot.push_back(hist_sig_EE);

  TH1D* hist_bg_EB = new TH1D("hist_bg_EB", (name+"_bg_EB").c_str() ,nbin,min,max);
  hist_bg_EB->Sumw2();
  tempplot.push_back(hist_bg_EB);

  TH1D* hist_bg_EE = new TH1D("hist_bg_EE", (name+"_bg_EE").c_str() ,nbin,min,max);
  hist_bg_EE->Sumw2();
  tempplot.push_back(hist_bg_EE);
  */

  ofstream outfile;

  if (writetxt != "") {
    string filename(writetxt);
    outfile.open(filename.c_str()); 
  }

  // photonID MVA
  tmvaReaderID_Single_Endcap=0;
  tmvaReaderID_Single_Barrel=0;
  if (!tmvaReaderID_Single_Barrel || !tmvaReaderID_Single_Endcap) SetAllMVA();  

  // Loop over entries
  int enMax = nentries; 
  for (Long64_t jentry=0; jentry<enMax;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (jentry%100000==0) cout << jentry << endl;

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // patological events
    if (npu>=60) continue;    

    // first vertex must be good
    if (vtxId<0) continue;

    // HLT selection - for data only
    if ( signal==100 && hltcut==30 && !isHLT_30() )  continue;
    if ( signal==100 && hltcut==50 && !isHLT_50() )  continue;
    if ( signal==100 && hltcut==75 && !isHLT_75() )  continue;
    if ( signal==100 && hltcut==90 && !isHLT_90() )  continue;

    // vector with index of fully selected gammas
    vector<int> fullSelected;

    // apply the full cut based photonID selection (medium WP)
    // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012
    float EA_charged[7] = { 0.012, 0.010, 0.014, 0.012, 0.016, 0.020, 0.012};
    float EA_neutral[7] = { 0.030, 0.057, 0.039, 0.015, 0.024, 0.039, 0.072};
    float EA_photons[7]  = { 0.148, 0.130, 0.112, 0.216, 0.262, 0.260, 0.266};

    int theNumber = nPhot_presel;
    if (nPhot_presel>100) theNumber = 100;
    for (int theGamma=0; theGamma<theNumber; theGamma++) {

      bool isFullySel     = true;

      // for effective area calculation
      int theEAregion = effectiveAreaRegion(etaPhot_presel[theGamma]); 
      if (theEAregion>6) continue;

      // preselection to really emulate the single gamma HLT requirements (current preselection is H->gg one)
      bool isReallyPresel = true;      
      float preselECAL    = pid_jurECAL03_presel[theGamma]  - 0.012*ptPhot_presel[theGamma];  
      float preselHCAL    = pid_twrHCAL03_presel[theGamma]  - 0.005*ptPhot_presel[theGamma]; 
      float preselTracker = pid_hlwTrack03_presel[theGamma] - 0.002*ptPhot_presel[theGamma]; 
      if ( preselECAL > 5.5)    isReallyPresel = false;
      if ( preselHCAL > 3.5)    isReallyPresel = false;
      if ( preselTracker > 3.5) isReallyPresel = false;
      if ( theEAregion<2) {  // EB
	if ( pid_HoverE_presel[theGamma]>0.15 )   isReallyPresel = false;       
	if ( sEtaEtaPhot_presel[theGamma]>0.024 ) isReallyPresel = false;
      } else {     // EE
	if(pid_HoverE_presel[theGamma]>0.10)      isReallyPresel = false;       
	if (sEtaEtaPhot_presel[theGamma]>0.040)   isReallyPresel = false;
      }
      if( !isReallyPresel ) continue;


      /*      // for effective area calculation
      //      int theEAregion = effectiveAreaRegion(etaPhot_presel[theGamma]); 
      //if (theEAregion>6) continue;
      
      // isolations corrected with effective areas
      float rhoCorrCharged = pid_pfIsoCharged03ForCiC_presel[theGamma] - rhoAllJets*EA_charged[theEAregion];   
      float rhoCorrNeutral = pid_pfIsoNeutrals03ForCiC_presel[theGamma] - rhoAllJets*EA_neutral[theEAregion];
      float rhoCorrPhoton  = pid_pfIsoPhotons03ForCiC_presel[theGamma] - rhoAllJets*EA_photons[theEAregion];*/
      /*if (rhoCorrCharged<0) rhoCorrCharged = 0.;//commented to smooth distributions
      if (rhoCorrNeutral<0) rhoCorrNeutral = 0.;
      if (rhoCorrPhoton<0)  rhoCorrPhoton  = 0.;*/
      
      // if(pid_hasMatchedPromptElephot[theGamma]) isFullySel = false;   // already applied at preselection level
      /* if(pid_HoverE_presel[theGamma]>0.05)      isFullySel = false;       
      if (theEAregion<2) {  // EB
	if (sEtaEtaPhot_presel[theGamma]>0.011) isFullySel = false;
	if (rhoCorrCharged > 1.5)               isFullySel = false;
	if (rhoCorrNeutral > 1.0 + 0.04*ptPhot_presel[theGamma])  isFullySel = false;
	if (rhoCorrPhoton  > 0.7 + 0.005*ptPhot_presel[theGamma]) isFullySel = false;
      } else {     // EE
	if (sEtaEtaPhot_presel[theGamma]>0.033) isFullySel = false;
	if (rhoCorrCharged > 1.2)               isFullySel = false;
	if (rhoCorrNeutral > 1.5 + 0.04*ptPhot_presel[theGamma])  isFullySel = false;
	if (rhoCorrPhoton  > 1.0 + 0.005*ptPhot_presel[theGamma]) isFullySel = false;
	}*/
      

      // photon ID MVA
      float theIdMva = PhotonIDMVA(theGamma);
      //cuts on photon ID mva for fixed signal eff
      double mva_cut_EB[3] = {0.892656, 0.844931, 0.766479};//corresponding to sig eff 0.80, 0.90, 0.95
      double mva_cut_EE[3] = {0.871778, 0.778579, 0.601807};//corresponding to sig eff 0.80, 0.90, 0.95
      //selection 0.9 eff for signal
      if(theEAregion<2){//EB
	if(theIdMva < mva_cut_EB[2]) isFullySel = false;
      }
      else{//EE
	if(theIdMva < mva_cut_EE[2]) isFullySel = false;
      }

      if (isFullySel) fullSelected.push_back(theGamma); 
      }

    // choose the two highest pT preselected gammas 
    // if (fullSelected.size()<2) continue;            // chiara: per check Z
    //if (fullSelected.size()<1) continue;
    int firstG = -1;
    int secG   = -1;
    float firstGpt  = -999.;
    float secGpt    = -1000.;
    float firstGeta = -999.;
    for (int ii=0; ii<fullSelected.size(); ii++) {
      int index = fullSelected[ii];
      if (ptPhot_presel[index]>firstGpt) {
	secGpt    = firstGpt;
	firstGpt  = ptPhot_presel[index];
	firstGeta = etaPhot_presel[index];
	secG      = firstG;
	firstG    = index;
      } else if (ptPhot_presel[index]>secGpt) {
	secGpt = ptPhot_presel[index];
	secG   = index;
      }
    } 


    // ptcut to restrict to the wanted range - matching HLT
    if (firstGpt<ptphot1_mincut) continue;	
    if (firstGpt>ptphot1_maxcut) continue;	

    // make the invariant mass of the two highest pT photons
    TLorentzVector gamma1, gamma2;
    gamma1.SetPtEtaPhiM(ptPhot_presel[firstG],etaPhot_presel[firstG],phiPhot_presel[firstG],0.);
    gamma2.SetPtEtaPhiM(ptPhot_presel[secG],etaPhot_presel[secG],phiPhot_presel[secG],0.);
    float invMass = (gamma1+gamma2).M();

    // only for Z studies
    // if (invMass>110 || invMass<70) continue;         // chiara: per check Z
  

    int theEAregion_fG = effectiveAreaRegion(etaPhot_presel[firstG]); //EAregion of the first Gamma

    // pu/pt reweighting
    float weight(1);
    if (dopureweight && hltcut==30) weight *= pu_weight30;
    if (dopureweight && hltcut==50) weight *= pu_weight50;
    if (dopureweight && hltcut==75) weight *= pu_weight75;
    if (dopureweight && hltcut==90) weight *= pu_weight90;

    // finding variable to be plotted
    double variable=0;
    if (var == "nvtx")variable = nvtx;
    else if (var == "ngamma")variable = nPhot_presel;
    else if (var == "sigmaIeIe") variable = sEtaEtaPhot_presel[firstG];
    else if (var == "HoE")       variable = pid_HoverE_presel[firstG]; 
    else if (var == "photonIdMva")    variable = PhotonIDMVA(firstG);
    else if (var == "chargedIso") variable = pid_pfIsoCharged03ForCiC_presel[firstG];
    else if (var == "neutralIso") variable = pid_pfIsoNeutrals03ForCiC_presel[firstG];
    else if (var == "gammaIso") variable   = pid_pfIsoPhotons03ForCiC_presel[firstG];
    else if (var == "eta_phot") variable = gamma1.Eta();
    else if (var == "pt_phot")  variable = firstGpt;
    else if (var == "rhoAllJets")  variable = rhoAllJets;
    else if (var == "mass") variable = invMass;
    else if (var == "weight"){
      variable = weight;
      weight=1;
    }
    else if (var == "sumIso_EAcorrected") variable = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];

    //signal
    //sumIso pt bin 30-50
    else if (var == "sumIso_EAcorrected_pt30_50") variable = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];

    //sumIso pt bin 50-70
    else if (var == "sumIso_EAcorrected_pt50_70" ) variable = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];

    //sumIso pt bin 70-110
    else if (var == "sumIso_EAcorrected_pt70_110" ) variable = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];

    //sumIso pt bin 110-inf
    else if (var == "sumIso_EAcorrected_pt110_inf" ) variable = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];


    else{
      cout << "NO SUCH VARIABLE IMPLEMENTED!" << endl;
      break;
    }
    if(0==split){
      for(int ii=0; ii<4; ii++){
	tempplot[ii]->Fill(variable, weight);
      }
    }
    else if (1==split){
      if (fabs(firstGeta)<1.5){
	tempplot[0]->Fill(variable, weight);
	tempplot[2]->Fill(variable, weight);
      }
      else if (fabs(firstGeta)>1.5){
	tempplot[1]->Fill(variable, weight);
	tempplot[3]->Fill(variable, weight);
      }
    }
    else if (2==split){
      if (1==isMatchedPhot[firstG]){
	tempplot[0]->Fill(variable, weight);
	tempplot[1]->Fill(variable, weight);
      }
      else if (0==isMatchedPhot[firstG]){
	tempplot[2]->Fill(variable, weight);
	tempplot[3]->Fill(variable, weight);
      }
    }
    else if (3==split){
      if (1==isMatchedPhot[firstG] && fabs(firstGeta)<1.5) tempplot[0]->Fill(variable, weight);
      else if (1==isMatchedPhot[firstG] && fabs(firstGeta)>1.5) tempplot[1]->Fill(variable, weight);
      else if (0==isMatchedPhot[firstG] && fabs(firstGeta)<1.5) tempplot[2]->Fill(variable, weight);
      else if (0==isMatchedPhot[firstG] && fabs(firstGeta)>1.5) tempplot[3]->Fill(variable, weight);
    }

  }
  
  if (writetxt != "")  outfile.close(); 
}





TH2D * fillPlot2012_gammaJets_vittorio2::Plot2D(string name, string varx, int nbinx, double xmin, double xmax, string vary, int nbiny, double ymin, double ymax, int signal) {
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  TH2D * tempplot = new TH2D(name.c_str(),name.c_str(),nbinx,xmin,xmax, nbiny,ymin,ymax);
  tempplot->Sumw2();

  ofstream outfile;

  if (writetxt != "") {
    string filename(writetxt);
    outfile.open(filename.c_str()); 
  }

  // photonID MVA
  tmvaReaderID_Single_Endcap=0;
  tmvaReaderID_Single_Barrel=0;
  if (!tmvaReaderID_Single_Barrel || !tmvaReaderID_Single_Endcap) SetAllMVA();  

  // Loop over entries
  int enMax = nentries; 
  for (Long64_t jentry=0; jentry<enMax;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (jentry%100000==0) cout << jentry << endl;

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // patological events
    if (npu>=60) continue;    

    // first vertex must be good
    if (vtxId<0) continue;

    // HLT selection - for data only
    if ( signal==100 && hltcut==30 && !isHLT_30() )  continue;
    if ( signal==100 && hltcut==50 && !isHLT_50() )  continue;
    if ( signal==100 && hltcut==75 && !isHLT_75() )  continue;
    if ( signal==100 && hltcut==90 && !isHLT_90() )  continue;


    // vector with index of fully selected gammas
    vector<int> fullSelected;

    // apply the full cut based photonID selection (medium WP)
    // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012
    float EA_charged[7] = { 0.012, 0.010, 0.014, 0.012, 0.016, 0.020, 0.012};
    float EA_neutral[7] = { 0.030, 0.057, 0.039, 0.015, 0.024, 0.039, 0.072};
    float EA_photons[7]  = { 0.148, 0.130, 0.112, 0.216, 0.262, 0.260, 0.266};

    int theNumber = nPhot_presel;
    if (nPhot_presel>100) theNumber = 100;
    for (int theGamma=0; theGamma<theNumber; theGamma++) {

      bool isFullySel     = true;

      // for effective area calculation
      int theEAregion = effectiveAreaRegion(etaPhot_presel[theGamma]); 
      if (theEAregion>6) continue;

      // preselection to really emulate the single gamma HLT requirements (current preselection is H->gg one)
      bool isReallyPresel = true;      
      float preselECAL    = pid_jurECAL03_presel[theGamma]  - 0.012*ptPhot_presel[theGamma];  
      float preselHCAL    = pid_twrHCAL03_presel[theGamma]  - 0.005*ptPhot_presel[theGamma]; 
      float preselTracker = pid_hlwTrack03_presel[theGamma] - 0.002*ptPhot_presel[theGamma]; 
      if ( preselECAL > 5.5)    isReallyPresel = false;
      if ( preselHCAL > 3.5)    isReallyPresel = false;
      if ( preselTracker > 3.5) isReallyPresel = false;
      if ( theEAregion<2) {  // EB
	if ( pid_HoverE_presel[theGamma]>0.15 )   isReallyPresel = false;       
	if ( sEtaEtaPhot_presel[theGamma]>0.024 ) isReallyPresel = false;
      } else {     // EE
	if(pid_HoverE_presel[theGamma]>0.10)      isReallyPresel = false;       
	if (sEtaEtaPhot_presel[theGamma]>0.040)   isReallyPresel = false;
      }
      if( !isReallyPresel ) continue;


      /*      // for effective area calculation
      //      int theEAregion = effectiveAreaRegion(etaPhot_presel[theGamma]); 
      //if (theEAregion>6) continue;
      
      // isolations corrected with effective areas
      float rhoCorrCharged = pid_pfIsoCharged03ForCiC_presel[theGamma] - rhoAllJets*EA_charged[theEAregion];   
      float rhoCorrNeutral = pid_pfIsoNeutrals03ForCiC_presel[theGamma] - rhoAllJets*EA_neutral[theEAregion];
      float rhoCorrPhoton  = pid_pfIsoPhotons03ForCiC_presel[theGamma] - rhoAllJets*EA_photons[theEAregion];*/
      /*if (rhoCorrCharged<0) rhoCorrCharged = 0.;//commented to smooth distributions
      if (rhoCorrNeutral<0) rhoCorrNeutral = 0.;
      if (rhoCorrPhoton<0)  rhoCorrPhoton  = 0.;*/
      
      // if(pid_hasMatchedPromptElephot[theGamma]) isFullySel = false;   // already applied at preselection level
      /* if(pid_HoverE_presel[theGamma]>0.05)      isFullySel = false;       
      if (theEAregion<2) {  // EB
	if (sEtaEtaPhot_presel[theGamma]>0.011) isFullySel = false;
	if (rhoCorrCharged > 1.5)               isFullySel = false;
	if (rhoCorrNeutral > 1.0 + 0.04*ptPhot_presel[theGamma])  isFullySel = false;
	if (rhoCorrPhoton  > 0.7 + 0.005*ptPhot_presel[theGamma]) isFullySel = false;
      } else {     // EE
	if (sEtaEtaPhot_presel[theGamma]>0.033) isFullySel = false;
	if (rhoCorrCharged > 1.2)               isFullySel = false;
	if (rhoCorrNeutral > 1.5 + 0.04*ptPhot_presel[theGamma])  isFullySel = false;
	if (rhoCorrPhoton  > 1.0 + 0.005*ptPhot_presel[theGamma]) isFullySel = false;
	}*/
      

      // photon ID MVA
      // float theIdMva = PhotonIDMVA(theGamma);

      if (isFullySel) fullSelected.push_back(theGamma); 
    }

    // choose the two highest pT preselected gammas 
    // if (fullSelected.size()<2) continue;            // chiara: per check Z
    //if (fullSelected.size()<1) continue;
    int firstG = -1;
    int secG   = -1;
    float firstGpt  = -999.;
    float secGpt    = -1000.;
    float firstGeta = -999.;
    for (int ii=0; ii<fullSelected.size(); ii++) {
      int index = fullSelected[ii];
      if (ptPhot_presel[index]>firstGpt) {
	secGpt    = firstGpt;
	firstGpt  = ptPhot_presel[index];
	firstGeta = etaPhot_presel[index];
	secG      = firstG;
	firstG    = index;
      } else if (ptPhot_presel[index]>secGpt) {
	secGpt = ptPhot_presel[index];
	secG   = index;
      }
    } 

    // ptcut to restrict to the wanted range - matching HLT
    if (firstGpt<ptphot1_mincut) continue;	
    if (firstGpt>ptphot1_maxcut) continue;	

    // make the invariant mass of the two highest pT photons
    TLorentzVector gamma1, gamma2;
    gamma1.SetPtEtaPhiM(ptPhot_presel[firstG],etaPhot_presel[firstG],phiPhot_presel[firstG],0.);
    gamma2.SetPtEtaPhiM(ptPhot_presel[secG],etaPhot_presel[secG],phiPhot_presel[secG],0.);
    float invMass = (gamma1+gamma2).M();

    // only for Z studies
    // if (invMass>110 || invMass<70) continue;         // chiara: per check Z

    // for ID variables, splitting EB/EE
    if ((varx == "HoE_EB"        || vary == "HoE_EB")         && fabs(firstGeta)>1.5) continue;
    if ((varx == "HoE_EE"        || vary == "HoE_EE")         && fabs(firstGeta)<1.5) continue;
    if ((varx == "sigmaIeIe_EB"  || vary == "sigmaIeIe_EB")   && fabs(firstGeta)>1.5) continue;
    if ((varx == "sigmaIeIe_EE"  || vary == "sigmaIeIe_EE")   && fabs(firstGeta)<1.5) continue;
    if ((varx == "photonIdMva_EB"|| vary == "photonIdMva_EB") && fabs(firstGeta)>1.5) continue;
    if ((varx == "photonIdMva_EE"|| vary == "photonIdMva_EE") && fabs(firstGeta)<1.5) continue;

    //for ISO variables, splitting EB/EE
    if ((varx == "sumIso_EAcorrected_EB" || vary == "sumIso_EAcorrected_EB") && fabs(firstGeta)>1.5) continue;
    if ((varx == "sumIso_EAcorrected_EE" || vary == "sumIso_EAcorrected_EE") && fabs(firstGeta)<1.5) continue;

    int theEAregion_fG = effectiveAreaRegion(etaPhot_presel[firstG]); //EAregion of the first Gamma

// pu/pt reweighting
    float weight(1);
    if (dopureweight && hltcut==30) weight *= pu_weight30;
    if (dopureweight && hltcut==50) weight *= pu_weight50;
    if (dopureweight && hltcut==75) weight *= pu_weight75;
    if (dopureweight && hltcut==90) weight *= pu_weight90;

    // finding variable to be plotted
    double variable_x(0), variable_y(0);
    if (varx == "nvtx") variable_x = nvtx;
    else if (varx == "ngamma")    variable_x = nPhot_presel;
    else if (varx == "sigmaIeIe") variable_x = sEtaEtaPhot_presel[firstG];
    else if (varx == "sigmaIeIe_EB") variable_x = sEtaEtaPhot_presel[firstG];
    else if (varx == "sigmaIeIe_EE") variable_x = sEtaEtaPhot_presel[firstG];
    else if (varx == "HoE")       variable_x = pid_HoverE_presel[firstG]; 
    else if (varx == "HoE_EB")    variable_x = pid_HoverE_presel[firstG]; 
    else if (varx == "HoE_EE")    variable_x = pid_HoverE_presel[firstG]; 
    else if (varx == "photonIdMva")    variable_x = PhotonIDMVA(firstG);
    else if (varx == "photonIdMva_EB") variable_x = PhotonIDMVA(firstG);
    else if (varx == "photonIdMva_EE") variable_x = PhotonIDMVA(firstG);
    else if (varx == "chargedIso") variable_x = pid_pfIsoCharged03ForCiC_presel[firstG];
    else if (varx == "neutralIso") variable_x = pid_pfIsoNeutrals03ForCiC_presel[firstG];
    else if (varx == "gammaIso") variable_x   = pid_pfIsoPhotons03ForCiC_presel[firstG];
    else if (varx == "etaL") variable_x = gamma1.Eta();
    else if (varx == "ptL")  variable_x = firstGpt;
    else if (varx == "mass") variable_x = invMass;
    else if (varx == "weight"){
      variable_x = weight;
      weight=1;
    }
    else if (varx == "sumIso_EAcorrected_EB") variable_x = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];
    else if (varx == "sumIso_EAcorrected_EE") variable_x = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];
    else{
      cout <<varx<< ": NO SUCH VARIABLE IMPLEMENTED!" << endl;
      break;
    }

    if (vary == "nvtx") variable_y = nvtx;
    else if (vary == "ngamma")    variable_y = nPhot_presel;
    else if (vary == "sigmaIeIe") variable_y = sEtaEtaPhot_presel[firstG];
    else if (vary == "sigmaIeIe_EB") variable_y = sEtaEtaPhot_presel[firstG];
    else if (vary == "sigmaIeIe_EE") variable_y = sEtaEtaPhot_presel[firstG];
    else if (vary == "HoE")       variable_y = pid_HoverE_presel[firstG]; 
    else if (vary == "HoE_EB")    variable_y = pid_HoverE_presel[firstG]; 
    else if (vary == "HoE_EE")    variable_y = pid_HoverE_presel[firstG]; 
    else if (vary == "photonIdMva")    variable_y = PhotonIDMVA(firstG);
    else if (vary == "photonIdMva_EB") variable_y = PhotonIDMVA(firstG);
    else if (vary == "photonIdMva_EE") variable_y = PhotonIDMVA(firstG);
    else if (vary == "chargedIso") variable_y = pid_pfIsoCharged03ForCiC_presel[firstG];
    else if (vary == "neutralIso") variable_y = pid_pfIsoNeutrals03ForCiC_presel[firstG];
    else if (vary == "gammaIso") variable_y   = pid_pfIsoPhotons03ForCiC_presel[firstG];
    else if (vary == "etaL") variable_y = gamma1.Eta();
    else if (vary == "ptL")  variable_y = firstGpt;
    else if (vary == "mass") variable_y = invMass;
    else if (vary == "weight"){
      variable_y = weight;
      weight=1;
    }
    else if (vary == "sumIso_EAcorrected_EB") variable_y = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];
    else if (vary == "sumIso_EAcorrected_EE") variable_y = pid_pfIsoCharged03ForCiC_presel[firstG] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[firstG] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[firstG] - rhoAllJets*EA_photons[theEAregion_fG];
    else{
      cout <<vary<< ": NO SUCH VARIABLE IMPLEMENTED!" << endl;
      break;
    }
    
         weight = 1;
    tempplot->Fill(variable_x, variable_y, weight);
  }
  
  if (writetxt != "")  outfile.close(); 

  return tempplot;
}






void  fillPlot2012_gammaJets_vittorio2::Setcuts(double pt1min, double pt1max, int eb, int r9, int HLTth) {

  ptphot1_mincut = pt1min;
  ptphot1_maxcut = pt1max;
  ebcat = eb;
  r9cat = r9;
  hltcut = HLTth;
}

void fillPlot2012_gammaJets_vittorio2::Writetxt(char * filename) {
  writetxt=std::string(filename);
}

void fillPlot2012_gammaJets_vittorio2::WriteRoot(char * filename) {
  writeRoot=std::string(filename);
}

void fillPlot2012_gammaJets_vittorio2::DoPuReweight(){
  dopureweight = 1;
}

void fillPlot2012_gammaJets_vittorio2::SetPuWeights(bool isData,std::string puWeightFile) {
  
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

void fillPlot2012_gammaJets_vittorio2::getweights() {
  
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

bool fillPlot2012_gammaJets_vittorio2::isHLT_30() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v18") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v19") isok=true;
  }
  return isok;
}

bool fillPlot2012_gammaJets_vittorio2::isHLT_50() {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v17") isok=true;
  }
  return isok;
}

bool fillPlot2012_gammaJets_vittorio2::isHLT_75() {
  
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v15") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v16") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v17") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v18") isok=true;
  }
  return isok;
}

bool fillPlot2012_gammaJets_vittorio2::isHLT_90() {
  
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v12") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v13") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v14") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v15") isok=true;
  }
  return isok;
}

bool fillPlot2012_gammaJets_vittorio2::isHLT_150() {
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v1") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v2") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v3") isok=true;
  }
  return isok;
}

// for effective area calculation
int fillPlot2012_gammaJets_vittorio2::effectiveAreaRegion(float theEta) {

  int theEAregion = 999;
  if (fabs(theEta)<1.) theEAregion = 0;      
  if (fabs(theEta)<1.479 && fabs(theEta)>1.)    theEAregion = 1;
  if (fabs(theEta)<2.    && fabs(theEta)>1.479) theEAregion = 2;
  if (fabs(theEta)<2.2   && fabs(theEta)>2.0)   theEAregion = 3;
  if (fabs(theEta)<2.3   && fabs(theEta)>2.2)   theEAregion = 4;
  if (fabs(theEta)<2.4   && fabs(theEta)>2.3)   theEAregion = 5;
  if (fabs(theEta)>2.4) theEAregion = 6;
  return theEAregion;
}

// to compute photonID MVA
Float_t fillPlot2012_gammaJets_vittorio2::PhotonIDMVA(Int_t iPhoton) {

  Float_t mva = 999.;

  tmva_photonid_etawidth     = pid_scetawid_presel[iPhoton];
  tmva_photonid_phiwidth     = pid_scphiwid_presel[iPhoton];
  tmva_photonid_sieie        = sEtaEtaPhot_presel[iPhoton];
  tmva_photonid_sieip        = sEtaPhiPhot_presel[iPhoton];
  tmva_photonid_s4ratio      = s4RatioPhot_presel[iPhoton];
  tmva_photonid_r9           = r9Phot_presel[iPhoton];
  tmva_photonid_pt           = ptPhot_presel[iPhoton];
  tmva_photonid_sceta        = etascPhot_presel[iPhoton];
  tmva_photonid_rr           = 0.0; 
  if (rr_presel[iPhoton]>0. && rr_presel[iPhoton]<999999.) tmva_photonid_rr = rr_presel[iPhoton];

  bool isEBphot = true;
  if (fabs(etascPhot_presel[iPhoton])>1.5) isEBphot = false; 

  if (isEBphot)
    mva = tmvaReaderID_Single_Barrel->EvaluateMVA("GradBoost");
  else
    mva = tmvaReaderID_Single_Endcap->EvaluateMVA("GradBoost");
  
  return mva;
}

void fillPlot2012_gammaJets_vittorio2::SetAllMVA() {

  tmvaReaderID_Single_Barrel = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Barrel->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Barrel->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Barrel->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Barrel->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Barrel->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  tmvaReaderID_Single_Barrel->AddVariable("ptPhot_presel",       &tmva_photonid_pt );
  tmvaReaderID_Single_Barrel->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Barrel->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Barrel->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );

  tmvaReaderID_Single_Endcap = new TMVA::Reader("!Color:Silent");

  tmvaReaderID_Single_Endcap->AddVariable("pid_scetawid_presel", &tmva_photonid_etawidth );
  tmvaReaderID_Single_Endcap->AddVariable("pid_scphiwid_presel", &tmva_photonid_phiwidth );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaEtaPhot_presel",  &tmva_photonid_sieie );
  tmvaReaderID_Single_Endcap->AddVariable("sEtaPhiPhot_presel",  &tmva_photonid_sieip );
  tmvaReaderID_Single_Endcap->AddVariable("s4RatioPhot_presel",  &tmva_photonid_s4ratio );
  tmvaReaderID_Single_Endcap->AddVariable("r9Phot_presel",       &tmva_photonid_r9 );
  tmvaReaderID_Single_Endcap->AddVariable("ptPhot_presel",       &tmva_photonid_pt );
  tmvaReaderID_Single_Endcap->AddVariable("etascPhot_presel",    &tmva_photonid_sceta );
  tmvaReaderID_Single_Endcap->AddVariable("rr_presel",           &tmva_photonid_rr );
  tmvaReaderID_Single_Endcap->AddSpectator("nPhot_presel",       &tmva_photonid_nPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("isMatchedPhot",      &tmva_photonid_isMatchedPhot );
  tmvaReaderID_Single_Endcap->AddSpectator("ptWeight",           &tmva_photonid_ptWeight );

  std::cout << "Booking PhotonID EB MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EB/TMVAClassification_BDT.weights.xml" << endl;
  tmvaReaderID_Single_Barrel->BookMVA("GradBoost","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EB/TMVAClassification_BDT.weights.xml");
  std::cout << "Booking PhotonID EE MVA with file /afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EE/TMVAClassification_BDT.weights.xml" << endl;
  tmvaReaderID_Single_Endcap->BookMVA("GradBoost","/afs/cern.ch/user/g/gdimperi/public/4Chiara/weights_gradBoost_EE/TMVAClassification_BDT.weights.xml");
}
