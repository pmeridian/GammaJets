#define SingleGammaMVA_cxx
#include "SingleGammaMVA.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void SingleGammaMVA::Loop(TH1F** plots_sig_EB, TH1F** plots_sig_EE, TH1F** plots_bkg_EB, TH1F** plots_bkg_EE, TH1F* h_isMatchedPhot, TH1F* h_PromptPhot, TH1F* h_FakePhot)
{
//   In a ROOT session, you can do:
//      Root > .L SingleGammaMVA.C
//      Root > SingleGammaMVA t
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


   //SingleGammaMVA 



   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      int nPromptPhot(0), nFakePhot(0);      
    
      for(int i=0; i<nPhot_presel; i++){
	if(isMatchedPhot[i] == 1
	   && TMath::Abs(etascPhot_presel[i]) < 1.4442) {
	  nPromptPhot++;
	  plots_sig_EB[0]    ->Fill(pid_scetawid_presel[i]); 
	  plots_sig_EB[1]    ->Fill(pid_scphiwid_presel[i]); 
	  plots_sig_EB[2]    ->Fill(sEtaEtaPhot_presel[i]);  
	  plots_sig_EB[3]    ->Fill(sEtaPhiPhot_presel[i]);  
	  plots_sig_EB[4]    ->Fill(s4RatioPhot_presel[i]);  
	  plots_sig_EB[5]    ->Fill(r9Phot_presel[i]);	    
	  plots_sig_EB[6]    ->Fill(etascPhot_presel[i]);    
	  plots_sig_EB[7]    ->Fill(rhoAllJets);	    
	  plots_sig_EB[8]    ->Fill(rr_presel[i]);          
	  plots_sig_EB[9]    ->Fill(pid_lambdaRatio_presel[i]);             
	}
	else if(isMatchedPhot[i] == 1
		&& TMath::Abs(etascPhot_presel[i]) > 1.566
		&& TMath::Abs(etascPhot_presel[i]) < 2.5
		) {
	  nPromptPhot++;
	  plots_sig_EE[0]   ->Fill(pid_scetawid_presel[i]); 
	  plots_sig_EE[1]   ->Fill(pid_scphiwid_presel[i]); 
	  plots_sig_EE[2]   ->Fill(sEtaEtaPhot_presel[i]);  
	  plots_sig_EE[3]   ->Fill(sEtaPhiPhot_presel[i]);  
	  plots_sig_EE[4]   ->Fill(s4RatioPhot_presel[i]);  
	  plots_sig_EE[5]   ->Fill(r9Phot_presel[i]);	    
	  plots_sig_EE[6]   ->Fill(etascPhot_presel[i]);    
	  plots_sig_EE[7]   ->Fill(rhoAllJets);	    
	  plots_sig_EE[8]   ->Fill(rr_presel[i]);          
	  plots_sig_EE[9]   ->Fill(pid_lambdaRatio_presel[i]);             
	  
	}
	else if(isMatchedPhot[i] == 0
		&& TMath::Abs(etascPhot_presel[i]) < 1.4442) {
	  nFakePhot++;
	  plots_bkg_EB[0] ->Fill(pid_scetawid_presel[i]); 
	  plots_bkg_EB[1] ->Fill(pid_scphiwid_presel[i]); 
	  plots_bkg_EB[2] ->Fill(sEtaEtaPhot_presel[i]);  
	  plots_bkg_EB[3] ->Fill(sEtaPhiPhot_presel[i]);  
	  plots_bkg_EB[4] ->Fill(s4RatioPhot_presel[i]);  
	  plots_bkg_EB[5] ->Fill(r9Phot_presel[i]);	    
	  plots_bkg_EB[6] ->Fill(etascPhot_presel[i]);    
	  plots_bkg_EB[7]  ->Fill(rhoAllJets);	    
	  plots_bkg_EB[8]  ->Fill(rr_presel[i]);          
	  plots_bkg_EB[9]  ->Fill(pid_lambdaRatio_presel[i]);             
	}
	else if(isMatchedPhot[i] == 0
                && TMath::Abs(etascPhot_presel[i]) > 1.566
		&& TMath::Abs(etascPhot_presel[i]) < 2.5
		){
	  nFakePhot++;
	  plots_bkg_EE[0] ->Fill(pid_scetawid_presel[i]); 
	  plots_bkg_EE[1] ->Fill(pid_scphiwid_presel[i]); 
	  plots_bkg_EE[2] ->Fill(sEtaEtaPhot_presel[i]);  
	  plots_bkg_EE[3] ->Fill(sEtaPhiPhot_presel[i]);  
	  plots_bkg_EE[4] ->Fill(s4RatioPhot_presel[i]);  
	  plots_bkg_EE[5] ->Fill(r9Phot_presel[i]);	    
	  plots_bkg_EE[6] ->Fill(etascPhot_presel[i]);    
	  plots_bkg_EE[7]  ->Fill(rhoAllJets);	    
	  plots_bkg_EE[8]  ->Fill(rr_presel[i]);          
	  plots_bkg_EE[9]  ->Fill(pid_lambdaRatio_presel[i]);             
	  }
	h_isMatchedPhot->Fill(isMatchedPhot[i]);
      }
      h_PromptPhot->Fill(nPromptPhot);
      h_FakePhot->Fill(nFakePhot);


   }

}
