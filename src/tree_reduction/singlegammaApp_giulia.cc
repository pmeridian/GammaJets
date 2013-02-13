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
  if(argc<2 || argc>7) {
    cout << "Usage:  ./tmp/singlegammaApp listfile outputfile jsonfile(optional) puweight(optional) scaleCorrections(optional)\n" 
	 << "  listfile:    list of root files incusing protocol eg dcap:/// .....\n"
	 << "  outputfile:  name of output root file  eg output.root\n"
	 << "  jsonfile: jsonfile used to select RUN/LS when looping over data. -1 if not used"
	 << "  puweight: puweight for MC nPU reweighting. -1 if not used"
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

  if (argc>3 && std::string(argv[3]) != "-1") 
    tool.SetJsonFile(argv[3]);
  
  if (argc>4 && std::string(argv[4]) != "-1") 
    tool.SetPuWeights(std::string(argv[4]));
  
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
