#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TAxis.h>
#include <TString.h>

#include "SingleGammaTree_giulia.h"
#include "IsGJet.h"
#include "CrossSection.h"

#include "EnergyScaleCorrection.h"

using namespace std;

int main(int argc, char* argv[]) {

  //================ Parameters 
  if(argc<2 || argc>13) {
    cout << "Usage:  ./tmp/singlegammaApp listfile outputfile jsonfile(optional) puweight(optional) puweight_HLT30(optional) puweight_HLT50(optional) puweight_HLT75(optional) puweight_HLT90(optional) puweight_HLT135(optional) puweight_HLT150(optional) scaleCorrections(optional)\n" 
	 << "  listfile:    list of root files incusing protocol eg dcap:/// .....\n"
	 << "  outputfile:  name of output root file  eg output.root\n"
	 << "  jsonfile: jsonfile used to select RUN/LS when looping over data. -1 if not used\n"
	 << "  puweight: puweight for MC nPU reweighting. -1 if not used\n"
	 << "  puweight_HLT30: puweight for MC nPU reweighting corresponding to HLT30 selected data. -1 if not used\n"
	 << "  puweight_HLT50: puweight for MC nPU reweighting corresponding to HLT50 selected data. -1 if not used\n"
	 << "  puweight_HLT75: puweight for MC nPU reweighting corresponding to HLT75 selected data. -1 if not used\n"
	 << "  puweight_HLT90: puweight for MC nPU reweighting corresponding to HLT90 selected data. -1 if not used\n"
	 << "  puweight_HLT135: puweight for MC nPU reweighting corresponding to HLT135 selected data. -1 if not used\n"
	 << "  puweight_HLT150: puweight for MC nPU reweighting corresponding to HLT150 selected data. -1 if not used\n"
	 << "  scalCorrection: ...."
	 << endl;
    exit(-1);
    }
  
  // Input list
  char listName[500];
  sprintf(listName,argv[1]); 
  
  // Output filename (.root)  
  TString OutputFileName(argv[2]);
  
  // Name of input tree objects in (.root) files 
  char treeName[100] = "myanalysis/pippo";

  // fai TChain
  TChain *chain = new TChain(treeName);
  char pName[500];
  ifstream is(listName);
  if(! is.good()) {
    cout << "int main() >> ERROR : file " << listName << " not read" << endl;
    is.close();
    exit(-1);
  }
  cout << "Reading list : " << listName << " ......." << endl;
  
  while( is.getline(pName, 500, '\n') ) {
    if (pName[0] == '#') continue;
    chain->Add(pName); 
  }
  is.close();
  
  /*
  //4th option:  name of flat file with cuts
  char  selection[100];
  sprintf(selection,argv[3]);
  string finder(selection);
  if(finder == "") sprintf(selection,"looseeg");
  cout << "Photon selection is : " << selection << endl;
  */ 

  // find cross section for this list
  float myxsec = CrossSection(listName);

  // filter for 2gam + jets. this is included in GJets samples but we use dedicated DiPhotonjets-madgraph
  int isGJetQCD = IsGJet(listName);
  
  // compute equivalent luminosity
  Long64_t  ntot = 1;
  double lumi = ntot/myxsec;
  cout << "#events: " << ntot << "\t xsec: " << myxsec << " pb\t equiv. lumi: " 
       << lumi/1000. << " fb-1"
       << endl;
  
  // run analysis code
  SingleGammaTree_giulia tool(chain, OutputFileName);
  tool.cicVersion="7TeV";
  tool.SetNtotXsection( ntot, myxsec );
  //  tool.photonLevelNewIDMVA_EB=std::string(argv[4]);
  //  tool.photonLevelNewIDMVA_EE=std::string(argv[5]);

  if (argc>3 && std::string(argv[3]) != "-1") {
    cout << "SetJsonFile" << endl;
    tool.SetJsonFile(argv[3]);
  }
  
  if (argc>4 && std::string(argv[4]) != "-1") {
    cout << "SetPuWeights, no HLT" << endl;
    tool.SetPuWeights(std::string(argv[4]));
  }

  if (argc>5 && std::string(argv[5]) != "-1") {
    cout << "SetPuWeightsHLT, 30" << endl;
    tool.SetPuWeightsHLT(std::string(argv[5]),30);
  }

  if (argc>6 && std::string(argv[6]) != "-1") {
    cout << "SetPuWeightsHLT, 50" << endl;
    tool.SetPuWeightsHLT(std::string(argv[6]),50);
  }

  if (argc>7 && std::string(argv[7]) != "-1") {
    cout << "SetPuWeightsHLT, 75" << endl;
    tool.SetPuWeightsHLT(std::string(argv[7]),75);
  }

  if (argc>8 && std::string(argv[8]) != "-1") {
    cout << "SetPuWeightsHLT, 90" << endl;
    tool.SetPuWeightsHLT(std::string(argv[8]),90);
  }

  if (argc>9 && std::string(argv[9]) != "-1") {
    cout << "SetPuWeightsHLT, 135" << endl;
    tool.SetPuWeightsHLT(std::string(argv[9]),135);
  }

  if (argc>10 && std::string(argv[10]) != "-1") {
    cout << "SetPuWeightsHLT, 150" << endl;
    tool.SetPuWeightsHLT(std::string(argv[10]),150);
  }
  
  /*
  if (argc>8 && std::string(argv[8]) != "-1") {
    TString scaleCorrectionFile(argv[8]);
    if (scaleCorrectionFile!="")
      tool.setEnergyScaleCorrections(scaleCorrectionFile,"Hgg_eta_R9");
  }
  */  

  std::cout << "DONE with settings starting loop" << std::endl;
  
  tool.Loop();
}
