#include "MyEvaluateMVA.h"

#include <TH2.h>
#include <TStyle.h>
#include <TString.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <iostream>
#include <vector>
#include <TString.h>
#include <TLorentzVector.h>
#include <TRegexp.h>

using namespace std;

MyEvaluateMVA::MyEvaluateMVA(){
  cout<<"MyEvaluateMVA object created"<<endl;
}

MyEvaluateMVA::~MyEvaluateMVA(){
  cout<<"MyEvaluateMVA object destroyed"<<endl;
}

void MyEvaluateMVA::SetEBWeights(string EBWeights_file){
  _MVA_weights_EB = EBWeights_file;
}

void MyEvaluateMVA::SetEEWeights(string EEWeights_file){
  _MVA_weights_EE = EEWeights_file;
}

void MyEvaluateMVA::SetAllMVA(){

  tmvaReader_Barrel = new TMVA::Reader();
  
  tmvaReader_Barrel->AddVariable("pid_scetawid_presel", &tmva_pid_scetawid_presel); 
  tmvaReader_Barrel->AddVariable("pid_scphiwid_presel", &tmva_pid_scphiwid_presel); 
  tmvaReader_Barrel->AddVariable("sEtaEtaPhot_presel", &tmva_sEtaEtaPhot_presel);  
  tmvaReader_Barrel->AddVariable("sEtaPhiPhot_presel", &tmva_sEtaPhiPhot_presel);	  
  tmvaReader_Barrel->AddVariable("s4RatioPhot_presel", &tmva_s4RatioPhot_presel);  
  tmvaReader_Barrel->AddVariable("r9Phot_presel", &tmva_r9Phot_presel);	  
  tmvaReader_Barrel->AddVariable("ptPhot_presel", &tmva_ptPhot_presel);	  
  tmvaReader_Barrel->AddVariable("etascPhot_presel", &tmva_etascPhot_presel);    
  tmvaReader_Barrel->AddSpectator("nPhot_presel", &tmvaSpectator_nPhot_presel);
  tmvaReader_Barrel->AddSpectator("isMatchedPhot", &tmvaSpectator_isMatchedPhot);

  std::cout << "Booking EB MVA with file " << _MVA_weights_EB.c_str() << std::endl;
  tmvaReader_Barrel->BookMVA("AdaBoost", _MVA_weights_EB.c_str());
  
  
  tmvaReader_Endcap = new TMVA::Reader();
  
  tmvaReader_Endcap->AddVariable("pid_scetawid_presel", &tmva_pid_scetawid_presel); 
  tmvaReader_Endcap->AddVariable("pid_scphiwid_presel", &tmva_pid_scphiwid_presel); 
  tmvaReader_Endcap->AddVariable("sEtaEtaPhot_presel", &tmva_sEtaEtaPhot_presel);  
  tmvaReader_Endcap->AddVariable("sEtaPhiPhot_presel", &tmva_sEtaPhiPhot_presel);	  
  tmvaReader_Endcap->AddVariable("s4RatioPhot_presel", &tmva_s4RatioPhot_presel);  
  tmvaReader_Endcap->AddVariable("r9Phot_presel", &tmva_r9Phot_presel);	  
  tmvaReader_Endcap->AddVariable("ptPhot_presel", &tmva_ptPhot_presel);	  
  tmvaReader_Endcap->AddVariable("etascPhot_presel", &tmva_etascPhot_presel);    
  tmvaReader_Endcap->AddVariable("rr_presel", &tmva_rr_presel);    
  tmvaReader_Endcap->AddSpectator("nPhot_presel", &tmvaSpectator_nPhot_presel);
  tmvaReader_Endcap->AddSpectator("isMatchedPhot", &tmvaSpectator_isMatchedPhot);  

  std::cout << "Booking EE MVA with file " << _MVA_weights_EE.c_str() << std::endl;
  tmvaReader_Endcap->BookMVA("AdaBoost", _MVA_weights_EE.c_str());
}

float MyEvaluateMVA::ComputeMVAValue(float (*variables)[9]){//variables added to the mva. Mandatory to have correct order  
  float mva = -9999;

  tmva_pid_scetawid_presel = (*variables)[0];
  tmva_pid_scphiwid_presel = (*variables)[1];
  tmva_sEtaEtaPhot_presel  = (*variables)[2];
  tmva_sEtaPhiPhot_presel  = (*variables)[3];
  tmva_s4RatioPhot_presel  = (*variables)[4];
  tmva_r9Phot_presel       = (*variables)[5]; 
  tmva_ptPhot_presel       = (*variables)[6];
  tmva_etascPhot_presel    = (*variables)[7];
  tmva_rr_presel           = (*variables)[8];

  if (fabs(tmva_etascPhot_presel)<1.442){
    mva = tmvaReader_Barrel->EvaluateMVA("AdaBoost");
  }

  if(fabs(tmva_etascPhot_presel)>1.566 && fabs(tmva_etascPhot_presel)<2.5){
    mva = tmvaReader_Endcap->EvaluateMVA("AdaBoost");
  }
  //  cout<<"MVA value is "<<mva<<endl;
  return mva;

}
