#define GammaJetAnalysis_cxx
#include "GammaJetAnalysis.h"
#include <TH2.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TStopwatch.h>


void GammaJetAnalysis::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L GammaJetAnalysis.C
//      Root > GammaJetAnalysis t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //Long64_t nentries = 10000;

   //Initialize
   SetAllMVA();
   BookFinalTree();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npassing = 0; 
   TStopwatch timer;
   timer.Start();
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (jentry%50000==0) std::cout << "Analyzing event " << sampleName << " " << jentry << "/" << nentries << " (" <<  setprecision(4) << jentry*100./nentries << "%)" << std::endl;

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      //////////// Selection //////////////
      // Inclusive photon selection

      // patological events
      if (npu>=60) continue;    

      // first vertex must be good
      if (vtxId<0) continue;
      
      if (!passHLT(hltiso)) continue;

      std::vector<int> photons=sortedPtPhotons();
      if (photons.size()<1)
	continue;

      std::vector<int> preselectPhotons=preselectedPhotons(photons);
      if (preselectPhotons.size()<1)
	continue;
      
      std::vector<int> selectPhotons=selectedPhotons(preselectPhotons);
      if (selectPhotons.size()<1)
	continue;

      // ptcut to restrict to the wanted range - matching HLT
      if (selectPhotons.size()>0)
	{
	  if (ptPhot_presel[selectPhotons[0]]<ptphot1_mincut && selectionType!="efficiencyStudy") continue;	
	  if (ptPhot_presel[selectPhotons[0]]>ptphot1_maxcut && selectionType!="efficiencyStudy") continue;	
	}


      if (selectionType=="efficiencyStudy")
	{
	  //now matching with the selected photon
	  if (nPhot_gen<1)
	    continue;
	  std::vector<int> genPhotons=sortedPtGenPhotons();
	  int i_nPhot=-1;

	  FillTreeGenPhot(genPhotons[0]);

	  TVector3 gen;
	  gen.SetPtEtaPhi(ptTrueMatch_gen[genPhotons[0]], etaMatch_gen[genPhotons[0]], phiMatch_gen[genPhotons[0]]);
	  float deltaRmin = 0.3;
	  int i_nPhot=-1;
	  for(int j=0; j<photons.size(); j++)
	    {
	      TVector3 reco;
	      reco.SetPtEtaPhi(ptPhot[photons[j]],etaPhot[photons[j]],phiPhot[photons[j]]);
	      if(gen.DeltaR(reco) < deltaRmin) 
		{
		  deltaRmin = gen.DeltaR(reco);
		  i_nPhot = photons[j];
		}
	    }


// 	  if (iRecoPhotMatch_gen[0]>-1)
// 	    {
// 	      for(int j=0; j<photons.size(); j++)
// 		{
// 		  if (photons[j]==iRecoPhotMatch_gen[0])
// 		    {
// 		      i_nPhot=j;
// 		      break;
// 		    }
// 		}
// 	    }

	  bool isPresel=false;
	  bool isSel=false;

	  if (i_nPhot>-1)
	    {
	      for(int j=0; j<preselectPhotons.size(); j++)
		if (preselectPhotons[j]==i_nPhot)
		  {
		    isPresel=true;
		    break;
		  }
	      for(int j=0; j<selectPhotons.size(); j++)
		if (selectPhotons[j]==i_nPhot)
		  {
		    isSel=true;
		    break;
		  }
	    FillTreePhot(photons[i_nPhot],isPresel,isSel);
	    }
	  else
	    FillTreePhot(-1,-1,-1);
	}
      else
	{
	  FillTreePhot(selectPhotons[0],1,1);
	  if (iMatchedPhot[selectPhotons[0]]>-1)
	    FillTreeGenPhot(iMatchedPhot[selectPhotons[0]]);
	  else
	    FillTreeGenPhot(-1);
	}

      //////////// End selection //////////////

      ++npassing;
      float weight(1);
      weight *= GetPUWeight()*GetSampleWeight();
      
      //Filling Tree
      FillTreeEvent(weight);
      FillTreePhot(selectPhotons[0]);
      finalTree->Fill();
   }
   timer.Stop();   
   std::cout << "Fraction of events passing the selection in sample " << sampleName <<  ":\t" <<  setprecision(4) << npassing*100./nentries*1. << "%" << std::endl;
   std::cout << "Processed events/s (CPU Time):\t" << setprecision(6) << (float) nentries/timer.CpuTime() << " Hz" << std::endl; 
   std::cout << "Processed events/s (Real Time):\t" << setprecision(6) << (float) nentries/timer.RealTime() << " Hz" << std::endl; 
   std::cout << "Bandwidth used:\t" << setprecision(6) << (float) nbytes/(1024*1024)/timer.RealTime() << " MB/s" << std::endl; 

   //Write output
   //finalTree->Print();
   finalTree->Write();
   outFile->Write();
   std::cout << "Written output into:\t" << outputFile << std::endl;
   outFile->Close();
}

// to compute photonID MVA
Float_t GammaJetAnalysis::PhotonIDMVA(Int_t iPhoton) 
{
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
  if (fabs(etascPhot_presel[iPhoton])>1.479) isEBphot = false; 

  //rescale MC to match data (Hgg analysis rescalings)
//   if (sampleIndex>0)
//     {
//       if (isEBphot) {
//         tmva_photonid_r9 = 1.0045*tmva_photonid_r9 + 0.0010;
//         tmva_photonid_s4ratio = 1.01894*tmva_photonid_s4ratio - 0.01034;
//         tmva_photonid_sieie = 0.891832*tmva_photonid_sieie + 0.0009133;
//         tmva_photonid_etawidth =  1.04302*tmva_photonid_etawidth - 0.000618;
//         tmva_photonid_phiwidth =  1.00002*tmva_photonid_phiwidth - 0.000371;
//       } else {
//         tmva_photonid_r9 = 1.0086*tmva_photonid_r9 - 0.0007;
//         tmva_photonid_s4ratio = 1.04969*tmva_photonid_s4ratio - 0.03642;
//         tmva_photonid_sieie = 0.99470*tmva_photonid_sieie + 0.00003;
//         tmva_photonid_etawidth =  0.903254*tmva_photonid_etawidth + 0.001346;
//         tmva_photonid_phiwidth =  0.99992*tmva_photonid_phiwidth - 0.00000048;
//       }
//     }

  if (isEBphot)
    mva = tmvaReaderID_Single_Barrel->EvaluateMVA("GradBoost");
  else
    mva = tmvaReaderID_Single_Endcap->EvaluateMVA("GradBoost");
  
  return mva;
}

void GammaJetAnalysis::SetAllMVA() {
  
  if (isMVAinitialized)
    return;

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

  isMVAinitialized=true;
  return;
}

bool GammaJetAnalysis::isHLT_30(bool isoCut) {

  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if (isoCut)
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v16") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v17") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v18") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_IsoL_v19") isok=true;
      }
    else
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v11") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v12") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v13") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon30_CaloIdVL_v14") isok=true;
      }
  }
  return isok;
}

bool GammaJetAnalysis::isHLT_50(bool isoCut) {
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if (isoCut)
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v14") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v15") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v16") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_IsoL_v17") isok=true;
      }
    else
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v7") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v8") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v9") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon50_CaloIdVL_v10") isok=true;
      }
  }
  return isok;
}

bool GammaJetAnalysis::isHLT_75(bool isoCut) {
  
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if (isoCut)
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v15") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v16") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v17") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_IsoL_v18") isok=true;
      }
    else
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v10") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v11") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v12") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon75_CaloIdVL_v13") isok=true;
      }
  }
  return isok;
}

bool GammaJetAnalysis::isHLT_90(bool isoCut) {
  
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if (isoCut)
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v12") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v13") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v14") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_IsoL_v15") isok=true;
      }
    else
      {
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v7") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v8") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v9") isok=true;
	if ( (*firedHLTNames)[ii]=="HLT_Photon90_CaloIdVL_v10") isok=true;
      }
  }
  return isok;
}

bool GammaJetAnalysis::isHLT_150() {
  bool isok = false;
  for (int ii=0; ii<firedHLTNames->size(); ii++) {
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v1") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v2") isok=true;
    if ( (*firedHLTNames)[ii]=="HLT_Photon150_v3") isok=true;
  }
  return isok;
}

// for effective area calculation
int GammaJetAnalysis::effectiveAreaRegion(float theEta) {

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

// void GammaJetAnalysis::SetPuWeights(bool isData,std::string puWeightFile) {

//   if (isData)
//     return;
  
//   if (puWeightFile == "") {
//     std::cout << "you need a weights file to use this function" << std::endl;
//     return;
//   }

//   std::cout << "PU REWEIGHTING:: Using file " << puWeightFile << std::endl;
  
//   TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  
//   TH1D *puweights = 0;
//   TH1D *gen_pu = 0;

//   gen_pu= (TH1D*) f_pu->Get("generated_pu");
//   puweights= (TH1D*) f_pu->Get("weights");
  
//   if (!puweights || !gen_pu)  {
//     std::cout << "weights histograms  not found in file " << puWeightFile << std::endl;
//     return;
//   }
  
//   TH1D* weightedPU= (TH1D*)gen_pu->Clone("weightedPU");
//   weightedPU->Multiply(puweights);

//   //Rescaling weights in order to preserve same integral of events
//   TH1D* weights= (TH1D*)puweights->Clone("rescaledWeights");
//   weights->Scale( gen_pu->Integral(1,MAX_PU_REWEIGHT) / weightedPU->Integral(1,MAX_PU_REWEIGHT) );
		  
//   float sumPuWeights=0.;

//   for (int i = 0; i<MAX_PU_REWEIGHT; i++) {
//     weight=weights->GetBinContent(i+1);
//     sumPuWeights+=weight;
//     puweights_.push_back(weight);
//   }
// }

void GammaJetAnalysis::BookFinalTree()
{
  outFile=TFile::Open(outputFile,"recreate");
  outFile->cd();
   
  finalTree=new TTree("finalTree","finalTree");

  finalTree->Branch("sampleIndex",&finalTree_sampleIndex,"sampleIndex/i");
  finalTree->Branch("run",&finalTree_run,"run/i");
  finalTree->Branch("lumi",&finalTree_lumi,"lumi/i");
  finalTree->Branch("event",&finalTree_event,"event/i");
  finalTree->Branch("nvtx",&finalTree_nvtx,"nvtx/i");
  finalTree->Branch("weight",&finalTree_weight,"weght/F");
  finalTree->Branch("rho",&finalTree_rho,"rho/F");

  finalTree->Branch("ptPhot",&finalTree_ptPhot,"ptPhot/F");
  finalTree->Branch("isMatchedPhot",&finalTree_isMatchedPhot,"isMatchedPhot/I");
  finalTree->Branch("etaPhot",&finalTree_etaPhot,"etaPhot/F");
  finalTree->Branch("mvaIdPhot",&finalTree_mvaIdPhot,"mvaIdPhot/F");
  finalTree->Branch("sEtaEtaPhot",&finalTree_setaetaPhot,"sEtaEtaPhot/F");
  finalTree->Branch("combinedPfIso03Phot",&finalTree_combinedPfIso03Phot,"combinedPfIso03Phot/F");

}


std::vector<int> GammaJetAnalysis::preselectedPhotons(const std::vector<int>& photons)
{
  std::vector<int> selPhotons;

  for (int ipho=0;ipho<photons.size();++ipho)
    {
      int theEAregion = effectiveAreaRegion(etaPhot_presel[photons[ipho]]); 
      if (theEAregion>6) continue;
      
      float preselECAL    = pid_jurECAL03_presel[photons[ipho]]  - 0.012*ptPhot_presel[photons[ipho]];  
      float preselHCAL    = pid_twrHCAL03_presel[photons[ipho]]  - 0.005*ptPhot_presel[photons[ipho]]; 
      float preselTracker = pid_hlwTrack03_presel[photons[ipho]] - 0.002*ptPhot_presel[photons[ipho]]; 

      if ( preselECAL > 10.)    continue;
      if ( preselHCAL > 10.)    continue;
      if ( preselTracker > 10) continue;

      if ( theEAregion<2) {  // EB
	if ( pid_HoverE_presel[photons[ipho]]>0.075 )   continue;
	if ( sEtaEtaPhot_presel[photons[ipho]]>0.014 ) continue;
      } else {     // EE
	if(pid_HoverE_presel[photons[ipho]]>0.075)      continue;
	if (sEtaEtaPhot_presel[photons[ipho]]>0.034)   continue;
      }
      selPhotons.push_back(photons[ipho]);
    }
  return selPhotons;
}

std::vector<int> GammaJetAnalysis::selectedPhotons(const std::vector<int>& photons)
{
  std::vector<int> selPhotons;
  double mva_cut_EB[3] = {0.892656, 0.844931, 0.766479};//corresponding to sig eff 0.80, 0.90, 0.95
  double mva_cut_EE[3] = {0.871778, 0.778579, 0.601807};//corresponding to sig eff 0.80, 0.90, 0.95

  for (int ipho=0;ipho<photons.size();++ipho)
    {
      int theEAregion = effectiveAreaRegion(etaPhot_presel[photons[ipho]]); 
      if (theEAregion>6) continue;
      // photon ID MVA
      float theIdMva = PhotonIDMVA(photons[ipho]);
      //cuts on photon ID mva for fixed signal eff

      //selection 0.9 eff for signal
      if(theEAregion<2){//EB
	if(mvaIDWP>0 && theIdMva < mva_cut_EB[mvaIDWP-1]) continue;
	if(mvaIDWP<0 && theIdMva > mva_cut_EB[abs(mvaIDWP)-1]) continue;
      }
      else{//EE
	if(mvaIDWP>0 && theIdMva < mva_cut_EE[mvaIDWP-1]) continue;
	if(mvaIDWP<0 && theIdMva > mva_cut_EE[abs(mvaIDWP)-1]) continue;
      }
      
      selPhotons.push_back(photons[ipho]);
    }
  return selPhotons;
}

float GammaJetAnalysis::combinedPfIso03(const int& pho)
{
  float EA_charged[7] = { 0.012, 0.010, 0.014, 0.012, 0.016, 0.020, 0.012};
  float EA_neutral[7] = { 0.030, 0.057, 0.039, 0.015, 0.024, 0.039, 0.072};
  float EA_photons[7]  = { 0.148, 0.130, 0.112, 0.216, 0.262, 0.260, 0.266};

  int theEAregion_fG = effectiveAreaRegion(pho); 
  return pid_pfIsoCharged03ForCiC_presel[pho] - rhoAllJets*EA_charged[theEAregion_fG] + pid_pfIsoNeutrals03ForCiC_presel[pho] - rhoAllJets*EA_neutral[theEAregion_fG]  + pid_pfIsoPhotons03ForCiC_presel[pho] - rhoAllJets*EA_photons[theEAregion_fG];    
}
  
std::vector<int> GammaJetAnalysis::sortedPtPhotons()
{
  std::vector<int> sortedPhotons;
  int sorted_index[nPhot_presel];
  TMath::Sort(nPhot_presel,ptPhot_presel,sorted_index);
  for (int ipho=0;ipho<nPhot_presel;++ipho)
    sortedPhotons.push_back(sorted_index[ipho]);
  return sortedPhotons;
}

bool GammaJetAnalysis::passHLT(bool isoCut)
{
  // HLT selection - for data only
  if ( sampleIndex==0 && hltcut==30 && !isHLT_30(isoCut) )  return false;
  if ( sampleIndex==0 && hltcut==50 && !isHLT_50(isoCut) )  return false;
  if ( sampleIndex==0 && hltcut==75 && !isHLT_75(isoCut) )  return false;
  if ( sampleIndex==0 && hltcut==90 && !isHLT_90(isoCut) )  return false;
  return true;
}

float GammaJetAnalysis::GetPUWeight()
{
  float weight=1;
  if (sampleIndex!=0 && dopureweight && hltcut==30) weight *= pu_weight30;
  if (sampleIndex!=0 && dopureweight && hltcut==50) weight *= pu_weight50;
  if (sampleIndex!=0 && dopureweight && hltcut==75) weight *= pu_weight75;
  if (sampleIndex!=0 && dopureweight && hltcut==90) weight *= pu_weight90;
  return weight;
}

float GammaJetAnalysis::GetSampleWeight()
{
  float weight=1;
  if (sampleIndex!=0) weight *= normLumi*xsec*kfac/sampleSize;
  return weight;
}

void GammaJetAnalysis::FillTreeEvent(float weight)
{
  finalTree_sampleIndex=sampleIndex;
  finalTree_run=run;
  finalTree_lumi=lumi;  
  finalTree_event=event;
  finalTree_nvtx=nvtx;
  finalTree_weight=weight;
  finalTree_rho=rhoAllJets;
  return;
}

void GammaJetAnalysis::FillTreePhot(const int& phot)
{
  if (phot>-1)
    {
      finalTree_etaPhot=etascPhot_presel[phot];
      finalTree_ptPhot=ptPhot_presel[phot];
      finalTree_isMatchedPhot=isMatchedPhot[phot];  
      finalTree_mvaIdPhot=PhotonIDMVA(phot);
      finalTree_setaetaPhot=sEtaEtaPhot_presel[phot];
      finalTree_combinedPfIso03Phot=combinedPfIso03(phot);
      finalTree_isPreselectedPhot=isPresel;
      finalTree_isSelectedPhot=isSel;
    }
  else
    {
      finalTree_etaPhot=-999;
      finalTree_ptPhot=-999;
      finalTree_isMatchedPhot=-999;
      finalTree_mvaIdPhot=-999;
      finalTree_setaetaPhot=-999;
      finalTree_combinedPfIso03Phot=-999;
      finalTree_isPreselectedPhot=-999;
      finalTree_isSelectedPhot=-999;
    }
  
  return;
}

void GammaJetAnalysis::FillTreeGenPhot(const int& genphot)
{
  if (genphot>-1)
    {
      finalTree_etaPhotGen=etaMatch_gen[genphot];
      finalTree_ptPhotGen=ptTrueMatch_gen[genphot];
      finalTree_iso03PhotGen=iso03_gen[genphot];
      finalTree_iso04PhotGen=iso04_gen[genphot];
      finalTree_isRecoMatchedPhotGen=(iRecoPhotMatch_gen[genphot]>-1);
    }
  else
    {
      finalTree_etaPhotGen=-1;
      finalTree_ptPhotGen=-1;
      finalTree_iso03PhotGen=-1;
      finalTree_iso04PhotGen=-1;
    }
  
  return;
}
