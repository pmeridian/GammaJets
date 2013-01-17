#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>

#include "interface/GammaJetsSelection.h"

using namespace std;

int main(int argc, char* argv[]) {

  //================ Parameters 
  if(argc<3 || argc>5) {
    cout << "Usage:  ./tmp/gammaJetsApp listfile outputfile selection jsonfile(optional) puweight(optional)\n" 
	 << "  listfile:   list of root files incusing protocol eg dcap:/// .....\n"
	 << "  outputfile: name of output root file  eg output.root\n"
	 << "  jsonfile:   jsonfile used to select RUN/LS when looping over data. -1 if not used"
	 << "  puweight:   puweight for MC nPU reweighting. -1 if not used"
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
  
  // run analysis code
  GammaJetsSelection tool(chain, OutputFileName);
  
  if (argc>3 && std::string(argv[3]) != "-1") tool.SetJsonFile(argv[3]);
    
  if (argc>4 && std::string(argv[4]) != "-1") tool.SetPuWeights(std::string(argv[4]));
  
  std::cout << "DONE with settings starting loop" << std::endl;
  
  tool.Loop();
}
