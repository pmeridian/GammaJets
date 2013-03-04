#ifndef MyEvaluateMVA_h
#define MyEvaluateMVA_h

#include <TFile.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TMath.h>
#include <TRandom3.h>
//#include <TString.h>
#include <vector>
#include <string>
#include <TChain.h>

#include <tree_reader.h>

#include "TMVA/Reader.h"

//class tree_reader;

class MyEvaluateMVA{

 public:

  MyEvaluateMVA();
  ~MyEvaluateMVA();
  void SetEBWeights(string EBWeights_file);
  void SetEEWeights(string EEWeights_file);

  void SetAllMVA();
  float ComputeMVAValue(float (*variables)[9]); //corresponding to PhotonIDMVANew

 private:

  TMVA::Reader *tmvaReader_Barrel;
  TMVA::Reader *tmvaReader_Endcap;

  float tmva_pid_scetawid_presel; 
  float tmva_pid_scphiwid_presel; 
  float tmva_sEtaEtaPhot_presel;  
  float tmva_sEtaPhiPhot_presel;	  
  float tmva_s4RatioPhot_presel;  
  float tmva_r9Phot_presel;	  
  float tmva_ptPhot_presel;	  
  float tmva_etascPhot_presel;    
  float tmva_rr_presel;

  float tmvaSpectator_nPhot_presel;
  float tmvaSpectator_isMatchedPhot;

  string _MVA_weights_EB;
  string _MVA_weights_EE;




};
#endif
