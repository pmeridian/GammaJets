{  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptFile(1);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(.3);
  gStyle->SetMarkerColor(1);
  
  // mc distributions
  TFile* inFileMC=TFile::Open("tandp_ntuple_tagTight_HLT__mc_conRichiestaHLT_xv6.root");    
  TTree* inTreeMC=(TTree*)inFileMC->Get("myTaPDir/myTree");

  // data distributions
  TFile* inFileData=TFile::Open("tandp_ntuple_tagTight_HLT__data_xv6.root");  
  TTree* inTreeData=(TTree*)inFileData->Get("myTaPDir/myTree");


  // ---------------------------------------------
  // histos

  // mc variables, all
  inTreeMC->Draw("numvtx             >> h1_numvtx_Mc(60,0.,60.)",           "puW*1");

  // mc variables, barrel
  inTreeMC->Draw("probe_eta          >> h1_eta_EB_Mc(60,-2.5,2.5)",            "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_etasc        >> h1_etasc_EB_Mc(60,-2.5,2.5)",          "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_pt           >> h1_pt_EB_Mc(80,0.,120.)",              "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_r9           >> h1_r9_EB_Mc(120,0.,1.)",               "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_pid_scetawid >> h1_scetawid_EB_Mc(120,0.,0.03)",       "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_pid_scphiwid >> h1_scphiwid_EB_Mc(120,0.,0.15)",       "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_sEtaEta      >> h1_sEtaEta_EB_Mc(120,0.,0.0001)",      "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_sEtaPhi      >> h1_sEtaPhi_EB_Mc(120,-0.00015,0.00015)", "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_s4Ratio      >> h1_s4Ratio_EB_Mc(120,0.,1)",           "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_mvaId        >> h1_BDToutput_EB_Mc(120,-1.,1.)",       "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprCharged03   >> h1_fprCh03_EB_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprNeutral03   >> h1_fprNeu03_EB_Mc(120, 0., 30.)",     "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprPhoton03    >> h1_fprPh03_EB_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprRCCharged03 >> h1_fprRCCh03_EB_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)<1.5 && probe_fprRCCharged03<900)");
  inTreeMC->Draw("probe_fprRCNeutral03 >> h1_fprRCNeu03_EB_Mc(120, 0., 30.)",   "puW*(abs(probe_eta)<1.5 && probe_fprRCNeutral03<900)");
  inTreeMC->Draw("probe_fprRCPhoton03  >> h1_fprRCPh03_EB_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)<1.5 && probe_fprRCPhoton03<900)");
  /*
  inTreeMC->Draw("probe_fprCharged04   >> h1_fprCh04_EB_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprNeutral04   >> h1_fprNeu04_EB_Mc(120, 0., 30.)",     "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprPhoton04    >> h1_fprPh04_EB_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)<1.5)");
  inTreeMC->Draw("probe_fprRCCharged04 >> h1_fprRCCh04_EB_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)<1.5 && probe_fprRCCharged04<900)");
  inTreeMC->Draw("probe_fprRCNeutral04 >> h1_fprRCNeu04_EB_Mc(120, 0., 30.)",   "puW*(abs(probe_eta)<1.5 && probe_fprRCNeutral04<900)");
  inTreeMC->Draw("probe_fprRCPhoton04  >> h1_fprRCPh04_EB_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)<1.5 && probe_fprRCPhoton04<900)");
  */

  // mc variables, endcap
  inTreeMC->Draw("probe_eta          >> h1_eta_EE_Mc(60,-2.5,2.5)",            "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_etasc        >> h1_etasc_EE_Mc(60,-2.5,2.5)",          "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_pt           >> h1_pt_EE_Mc(80,0.,120.)",              "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_r9           >> h1_r9_EE_Mc(120,0.,1.)",               "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_pid_scetawid >> h1_scetawid_EE_Mc(120,0.005,0.04)",    "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_pid_scphiwid >> h1_scphiwid_EE_Mc(120,0.,0.15)",       "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_sEtaEta      >> h1_sEtaEta_EE_Mc(120,0.,0.0015)",      "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_sEtaPhi      >> h1_sEtaPhi_EE_Mc(120,-0.0005,0.0005)", "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_s4Ratio      >> h1_s4Ratio_EE_Mc(120,0.,1)",           "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_mvaId        >> h1_BDToutput_EE_Mc(120,-1.,1.)",       "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_rr           >> h1_rr_EE_Mc(120,0.,15)",               "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprCharged03   >> h1_fprCh03_EE_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprNeutral03   >> h1_fprNeu03_EE_Mc(120, 0., 30.)",     "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprPhoton03    >> h1_fprPh03_EE_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprRCCharged03 >> h1_fprRCCh03_EE_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)>1.5 && probe_fprRCCharged03<900)");
  inTreeMC->Draw("probe_fprRCNeutral03 >> h1_fprRCNeu03_EE_Mc(120, 0., 30.)",   "puW*(abs(probe_eta)>1.5 && probe_fprRCNeutral03<900)");
  inTreeMC->Draw("probe_fprRCPhoton03  >> h1_fprRCPh03_EE_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)>1.5 && probe_fprRCPhoton03<900)");
  /*
  inTreeMC->Draw("probe_fprCharged04   >> h1_fprCh04_EE_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprNeutral04   >> h1_fprNeu04_EE_Mc(120, 0., 30.)",     "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprPhoton04    >> h1_fprPh04_EE_Mc(120, 0., 30.)",      "puW*(abs(probe_eta)>1.5)");
  inTreeMC->Draw("probe_fprRCCharged04 >> h1_fprRCCh04_EE_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)>1.5 && probe_fprRCCharged04<900)");
  inTreeMC->Draw("probe_fprRCNeutral04 >> h1_fprRCNeu04_EE_Mc(120, 0., 30.)",   "puW*(abs(probe_eta)>1.5 && probe_fprRCNeutral04<900)");
  inTreeMC->Draw("probe_fprRCPhoton04  >> h1_fprRCPh04_EE_Mc(120, 0., 30.)",    "puW*(abs(probe_eta)>1.5 && probe_fprRCPhoton04<900)");
  */

  // data variables, all
  inTreeData->Draw("numvtx             >> h1_numvtx_Data(60,0.,60.)",           "1.*1");

  // data variables, barrel
  inTreeData->Draw("probe_eta          >> h1_eta_EB_Data(60,-2.5,2.5)",            "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_etasc        >> h1_etasc_EB_Data(60,-2.5,2.5)",          "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_pt           >> h1_pt_EB_Data(80,0.,120.)",              "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_r9           >> h1_r9_EB_Data(120,0.,1.)",               "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_pid_scetawid >> h1_scetawid_EB_Data(120,0.,0.03)",       "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_pid_scphiwid >> h1_scphiwid_EB_Data(120,0.,0.15)",       "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_sEtaEta      >> h1_sEtaEta_EB_Data(120,0.,0.0001)",      "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_sEtaPhi      >> h1_sEtaPhi_EB_Data(120,-0.00015,0.00015)", "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_s4Ratio      >> h1_s4Ratio_EB_Data(120,0.,1)",           "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_mvaId        >> h1_BDToutput_EB_Data(120,-1.,1.)",       "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprCharged03   >> h1_fprCh03_EB_Data(120, 0., 30.)",      "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprNeutral03   >> h1_fprNeu03_EB_Data(120, 0., 30.)",     "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprPhoton03    >> h1_fprPh03_EB_Data(120, 0., 30.)",      "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprRCCharged03 >> h1_fprRCCh03_EB_Data(120, 0., 30.)",    "1.*(abs(probe_eta)<1.5 && probe_fprRCCharged03<900)");
  inTreeData->Draw("probe_fprRCNeutral03 >> h1_fprRCNeu03_EB_Data(120, 0., 30.)",   "1.*(abs(probe_eta)<1.5 && probe_fprRCNeutral03<900)");
  inTreeData->Draw("probe_fprRCPhoton03  >> h1_fprRCPh03_EB_Data(120, 0., 30.)",    "1.*(abs(probe_eta)<1.5 && probe_fprRCPhoton03<900)");
  /*
  inTreeData->Draw("probe_fprCharged04   >> h1_fprCh04_EB_Data(120, 0., 30.)",      "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprNeutral04   >> h1_fprNeu04_EB_Data(120, 0., 30.)",     "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprPhoton04    >> h1_fprPh04_EB_Data(120, 0., 30.)",      "1.*(abs(probe_eta)<1.5)");
  inTreeData->Draw("probe_fprRCCharged04 >> h1_fprRCCh04_EB_Data(120, 0., 30.)",    "1.*(abs(probe_eta)<1.5 && probe_fprRCCharged04<900)");
  inTreeData->Draw("probe_fprRCNeutral04 >> h1_fprRCNeu04_EB_Data(120, 0., 30.)",   "1.*(abs(probe_eta)<1.5 && probe_fprRCNeutral04<900)");
  inTreeData->Draw("probe_fprRCPhoton04  >> h1_fprRCPh04_EB_Data(120, 0., 30.)",    "1.*(abs(probe_eta)<1.5 && probe_fprRCPhoton04<900)");
  */

  // data variables, endcap
  inTreeData->Draw("probe_eta          >> h1_eta_EE_Data(60,-2.5,2.5)",            "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_etasc        >> h1_etasc_EE_Data(60,-2.5,2.5)",          "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_pt           >> h1_pt_EE_Data(80,0.,120.)",              "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_r9           >> h1_r9_EE_Data(120,0.,1.)",               "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_pid_scetawid >> h1_scetawid_EE_Data(120,0.005,0.04)",    "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_pid_scphiwid >> h1_scphiwid_EE_Data(120,0.,0.15)",       "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_sEtaEta      >> h1_sEtaEta_EE_Data(120,0.,0.0015)",      "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_sEtaPhi      >> h1_sEtaPhi_EE_Data(120,-0.0005,0.0005)", "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_s4Ratio      >> h1_s4Ratio_EE_Data(120,0.,1)",           "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_mvaId        >> h1_BDToutput_EE_Data(120,-1.,1.)",       "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_rr           >> h1_rr_EE_Data(120,0.,15)",               "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprCharged03   >> h1_fprCh03_EE_Data(120, 0., 30.)",      "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprNeutral03   >> h1_fprNeu03_EE_Data(120, 0., 30.)",     "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprPhoton03    >> h1_fprPh03_EE_Data(120, 0., 30.)",      "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprRCCharged03 >> h1_fprRCCh03_EE_Data(120, 0., 30.)",    "1.*(abs(probe_eta)>1.5 && probe_fprRCCharged03<900)");
  inTreeData->Draw("probe_fprRCNeutral03 >> h1_fprRCNeu03_EE_Data(120, 0., 30.)",   "1.*(abs(probe_eta)>1.5 && probe_fprRCNeutral03<900)");
  inTreeData->Draw("probe_fprRCPhoton03  >> h1_fprRCPh03_EE_Data(120, 0., 30.)",    "1.*(abs(probe_eta)>1.5 && probe_fprRCPhoton03<900)");
  /*
  inTreeData->Draw("probe_fprCharged04   >> h1_fprCh04_EE_Data(120, 0., 30.)",      "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprNeutral04   >> h1_fprNeu04_EE_Data(120, 0., 30.)",     "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprPhoton04    >> h1_fprPh04_EE_Data(120, 0., 30.)",      "1.*(abs(probe_eta)>1.5)");
  inTreeData->Draw("probe_fprRCCharged04 >> h1_fprRCCh04_EE_Data(120, 0., 30.)",    "1.*(abs(probe_eta)>1.5 && probe_fprRCCharged04<900)");
  inTreeData->Draw("probe_fprRCNeutral04 >> h1_fprRCNeu04_EE_Data(120, 0., 30.)",   "1.*(abs(probe_eta)>1.5 && probe_fprRCNeutral04<900)");
  inTreeData->Draw("probe_fprRCPhoton04  >> h1_fprRCPh04_EE_Data(120, 0., 30.)",    "1.*(abs(probe_eta)>1.5 && probe_fprRCPhoton04<900)");
  */

  // ---------------------------------------------
  // scaling
  h1_numvtx_Mc       -> Sumw2();     
  h1_numvtx_Data     -> Sumw2();     

  h1_eta_EB_Mc       -> Sumw2();     
  h1_etasc_EB_Mc     -> Sumw2();     
  h1_pt_EB_Mc        -> Sumw2();
  h1_r9_EB_Mc        -> Sumw2();     
  h1_scetawid_EB_Mc  -> Sumw2();     
  h1_scphiwid_EB_Mc  -> Sumw2();     
  h1_sEtaEta_EB_Mc   -> Sumw2();     
  h1_sEtaPhi_EB_Mc   -> Sumw2();     
  h1_s4Ratio_EB_Mc   -> Sumw2();     
  h1_BDToutput_EB_Mc -> Sumw2();     

  h1_fprCh03_EB_Mc    -> Sumw2();     
  h1_fprNeu03_EB_Mc   -> Sumw2();     
  h1_fprPh03_EB_Mc    -> Sumw2();     
  h1_fprRCCh03_EB_Mc  -> Sumw2();     
  h1_fprRCNeu03_EB_Mc -> Sumw2();     
  h1_fprRCPh03_EB_Mc  -> Sumw2();     
  /*
  h1_fprCh04_EB_Mc    -> Sumw2();     
  h1_fprNeu04_EB_Mc   -> Sumw2();     
  h1_fprPh04_EB_Mc    -> Sumw2();     
  h1_fprRCCh04_EB_Mc  -> Sumw2();     
  h1_fprRCNeu04_EB_Mc -> Sumw2();     
  h1_fprRCPh04_EB_Mc  -> Sumw2();     
  */

  h1_eta_EB_Data       -> Sumw2();     
  h1_etasc_EB_Data     -> Sumw2();     
  h1_pt_EB_Data        -> Sumw2();
  h1_r9_EB_Data        -> Sumw2();     
  h1_scetawid_EB_Data  -> Sumw2();     
  h1_scphiwid_EB_Data  -> Sumw2();     
  h1_sEtaEta_EB_Data   -> Sumw2();     
  h1_sEtaPhi_EB_Data   -> Sumw2();     
  h1_s4Ratio_EB_Data   -> Sumw2();     
  h1_BDToutput_EB_Data -> Sumw2();     

  h1_fprCh03_EB_Data    -> Sumw2();     
  h1_fprNeu03_EB_Data   -> Sumw2();     
  h1_fprPh03_EB_Data    -> Sumw2();     
  h1_fprRCCh03_EB_Data  -> Sumw2();     
  h1_fprRCNeu03_EB_Data -> Sumw2();     
  h1_fprRCPh03_EB_Data  -> Sumw2();     
  /*
  h1_fprCh04_EB_Data    -> Sumw2();     
  h1_fprNeu04_EB_Data   -> Sumw2();     
  h1_fprPh04_EB_Data    -> Sumw2();     
  h1_fprRCCh04_EB_Data  -> Sumw2();     
  h1_fprRCNeu04_EB_Data -> Sumw2();     
  h1_fprRCPh04_EB_Data  -> Sumw2();     
  */

  h1_eta_EE_Mc       -> Sumw2();     
  h1_etasc_EE_Mc     -> Sumw2();     
  h1_pt_EE_Mc        -> Sumw2();
  h1_r9_EE_Mc        -> Sumw2();     
  h1_scetawid_EE_Mc  -> Sumw2();     
  h1_scphiwid_EE_Mc  -> Sumw2();     
  h1_sEtaEta_EE_Mc   -> Sumw2();     
  h1_sEtaPhi_EE_Mc   -> Sumw2();     
  h1_s4Ratio_EE_Mc   -> Sumw2();     
  h1_BDToutput_EE_Mc -> Sumw2();     
  h1_rr_EE_Mc        -> Sumw2();   

  h1_fprCh03_EE_Mc    -> Sumw2();     
  h1_fprNeu03_EE_Mc   -> Sumw2();     
  h1_fprPh03_EE_Mc    -> Sumw2();     
  h1_fprRCCh03_EE_Mc  -> Sumw2();     
  h1_fprRCNeu03_EE_Mc -> Sumw2();     
  h1_fprRCPh03_EE_Mc  -> Sumw2();     
  /*
  h1_fprCh04_EE_Mc    -> Sumw2();     
  h1_fprNeu04_EE_Mc   -> Sumw2();     
  h1_fprPh04_EE_Mc    -> Sumw2();     
  h1_fprRCCh04_EE_Mc  -> Sumw2();     
  h1_fprRCNeu04_EE_Mc -> Sumw2();     
  h1_fprRCPh04_EE_Mc  -> Sumw2();     
  */

  h1_eta_EE_Data       -> Sumw2();     
  h1_etasc_EE_Data     -> Sumw2();     
  h1_pt_EE_Data        -> Sumw2();
  h1_r9_EE_Data        -> Sumw2();     
  h1_scetawid_EE_Data  -> Sumw2();     
  h1_scphiwid_EE_Data  -> Sumw2();     
  h1_sEtaEta_EE_Data   -> Sumw2();     
  h1_sEtaPhi_EE_Data   -> Sumw2();     
  h1_s4Ratio_EE_Data   -> Sumw2();     
  h1_BDToutput_EE_Data -> Sumw2();     
  h1_rr_EE_Data        -> Sumw2();   

  h1_fprCh03_EE_Data    -> Sumw2();     
  h1_fprNeu03_EE_Data   -> Sumw2();     
  h1_fprPh03_EE_Data    -> Sumw2();     
  h1_fprRCCh03_EE_Data  -> Sumw2();     
  h1_fprRCNeu03_EE_Data -> Sumw2();     
  h1_fprRCPh03_EE_Data  -> Sumw2();     
  /*
  h1_fprCh04_EE_Data    -> Sumw2();     
  h1_fprNeu04_EE_Data   -> Sumw2();     
  h1_fprPh04_EE_Data    -> Sumw2();     
  h1_fprRCCh04_EE_Data  -> Sumw2();     
  h1_fprRCNeu04_EE_Data -> Sumw2();     
  h1_fprRCPh04_EE_Data  -> Sumw2();     
  */

  
  // ---------------------------------------------
  // axes titles 
  h1_numvtx_Mc       -> GetXaxis()->SetTitle("#vertices");
  h1_numvtx_Data     -> GetXaxis()->SetTitle("#vertices");

  h1_eta_EB_Mc       -> GetXaxis()->SetTitle("#eta");
  h1_etasc_EB_Mc     -> GetXaxis()->SetTitle("supercluster #eta");    
  h1_pt_EB_Mc        -> GetXaxis()->SetTitle("p_{T} [GeV]");
  h1_r9_EB_Mc        -> GetXaxis()->SetTitle("R9");
  h1_scetawid_EB_Mc  -> GetXaxis()->SetTitle("#eta width");
  h1_scphiwid_EB_Mc  -> GetXaxis()->SetTitle("#phi width");
  h1_sEtaEta_EB_Mc   -> GetXaxis()->SetTitle("#sigma(#eta#eta)");
  h1_sEtaPhi_EB_Mc   -> GetXaxis()->SetTitle("#sigma(#eta#phi)");
  h1_s4Ratio_EB_Mc   -> GetXaxis()->SetTitle("S4");
  h1_BDToutput_EB_Mc -> GetXaxis()->SetTitle("BDT output");

  h1_fprCh03_EB_Mc    -> GetXaxis()->SetTitle("chargedIso03 (FPR)");     
  h1_fprNeu03_EB_Mc   -> GetXaxis()->SetTitle("neutralIso03 (FPR)");     
  h1_fprPh03_EB_Mc    -> GetXaxis()->SetTitle("photonIso03 (FPR)");     
  h1_fprRCCh03_EB_Mc  -> GetXaxis()->SetTitle("chargedIso03 (FPR, RC)");     
  h1_fprRCNeu03_EB_Mc -> GetXaxis()->SetTitle("neutralIso03 (FPR, RC)");     
  h1_fprRCPh03_EB_Mc  -> GetXaxis()->SetTitle("photonIso03 (FPR, RC)");     
  /*
  h1_fprCh04_EB_Mc    -> GetXaxis()->SetTitle("chargedIso04 (FPR)");     
  h1_fprNeu04_EB_Mc   -> GetXaxis()->SetTitle("neutralIso04 (FPR)");     
  h1_fprPh04_EB_Mc    -> GetXaxis()->SetTitle("photonIso04 (FPR)");     
  h1_fprRCCh04_EB_Mc  -> GetXaxis()->SetTitle("chargedIso04 (FPR, RC)");     
  h1_fprRCNeu04_EB_Mc -> GetXaxis()->SetTitle("neutralIso04 (FPR, RC)");     
  h1_fprRCPh04_EB_Mc  -> GetXaxis()->SetTitle("photonIso04 (FPR, RC)");     
  */

  h1_eta_EB_Data       -> GetXaxis()->SetTitle("#eta");
  h1_etasc_EB_Data     -> GetXaxis()->SetTitle("supercluster #eta");    
  h1_pt_EB_Data        -> GetXaxis()->SetTitle("p_{T} [GeV]");
  h1_r9_EB_Data        -> GetXaxis()->SetTitle("R9");
  h1_scetawid_EB_Data  -> GetXaxis()->SetTitle("#eta width");
  h1_scphiwid_EB_Data  -> GetXaxis()->SetTitle("#phi width");
  h1_sEtaEta_EB_Data   -> GetXaxis()->SetTitle("#sigma(#eta#eta)");
  h1_sEtaPhi_EB_Data   -> GetXaxis()->SetTitle("#sigma(#eta#phi)");
  h1_s4Ratio_EB_Data   -> GetXaxis()->SetTitle("S4");
  h1_BDToutput_EB_Data -> GetXaxis()->SetTitle("BDT output");

  h1_fprCh03_EB_Data    -> GetXaxis()->SetTitle("chargedIso03 (FPR)");     
  h1_fprNeu03_EB_Data   -> GetXaxis()->SetTitle("neutralIso03 (FPR)");     
  h1_fprPh03_EB_Data    -> GetXaxis()->SetTitle("photonIso03 (FPR)");     
  h1_fprRCCh03_EB_Data  -> GetXaxis()->SetTitle("chargedIso03 (FPR, RC)");     
  h1_fprRCNeu03_EB_Data -> GetXaxis()->SetTitle("neutralIso03 (FPR, RC)");     
  h1_fprRCPh03_EB_Data  -> GetXaxis()->SetTitle("photonIso03 (FPR, RC)");     
  /*
  h1_fprCh04_EB_Data    -> GetXaxis()->SetTitle("chargedIso04 (FPR)");     
  h1_fprNeu04_EB_Data   -> GetXaxis()->SetTitle("neutralIso04 (FPR)");     
  h1_fprPh04_EB_Data    -> GetXaxis()->SetTitle("photonIso04 (FPR)");     
  h1_fprRCCh04_EB_Data  -> GetXaxis()->SetTitle("chargedIso04 (FPR, RC)");     
  h1_fprRCNeu04_EB_Data -> GetXaxis()->SetTitle("neutralIso04 (FPR, RC)");     
  h1_fprRCPh04_EB_Data  -> GetXaxis()->SetTitle("photonIso04 (FPR, RC)");     
  */

  h1_eta_EE_Mc       -> GetXaxis()->SetTitle("#eta");
  h1_etasc_EE_Mc     -> GetXaxis()->SetTitle("supercluster #eta");    
  h1_pt_EE_Mc        -> GetXaxis()->SetTitle("p_{T} [GeV]");
  h1_r9_EE_Mc        -> GetXaxis()->SetTitle("R9");
  h1_scetawid_EE_Mc  -> GetXaxis()->SetTitle("#eta width");
  h1_scphiwid_EE_Mc  -> GetXaxis()->SetTitle("#phi width");
  h1_sEtaEta_EE_Mc   -> GetXaxis()->SetTitle("#sigma(#eta#eta)");
  h1_sEtaPhi_EE_Mc   -> GetXaxis()->SetTitle("#sigma(#eta#phi)");
  h1_s4Ratio_EE_Mc   -> GetXaxis()->SetTitle("S4");
  h1_BDToutput_EE_Mc -> GetXaxis()->SetTitle("BDT output");
  h1_rr_EE_Mc        -> GetXaxis()->SetTitle("#sigmaRR");

  h1_fprCh03_EE_Mc    -> GetXaxis()->SetTitle("chargedIso03 (FPR)");     
  h1_fprNeu03_EE_Mc   -> GetXaxis()->SetTitle("neutralIso03 (FPR)");     
  h1_fprPh03_EE_Mc    -> GetXaxis()->SetTitle("photonIso03 (FPR)");     
  h1_fprRCCh03_EE_Mc  -> GetXaxis()->SetTitle("chargedIso03 (FPR, RC)");     
  h1_fprRCNeu03_EE_Mc -> GetXaxis()->SetTitle("neutralIso03 (FPR, RC)");     
  h1_fprRCPh03_EE_Mc  -> GetXaxis()->SetTitle("photonIso03 (FPR, RC)");     
  /*
  h1_fprCh04_EE_Mc    -> GetXaxis()->SetTitle("chargedIso04 (FPR)");     
  h1_fprNeu04_EE_Mc   -> GetXaxis()->SetTitle("neutralIso04 (FPR)");     
  h1_fprPh04_EE_Mc    -> GetXaxis()->SetTitle("photonIso04 (FPR)");     
  h1_fprRCCh04_EE_Mc  -> GetXaxis()->SetTitle("chargedIso04 (FPR, RC)");     
  h1_fprRCNeu04_EE_Mc -> GetXaxis()->SetTitle("neutralIso04 (FPR, RC)");     
  h1_fprRCPh04_EE_Mc  -> GetXaxis()->SetTitle("photonIso04 (FPR, RC)");     
  */

  h1_eta_EE_Data       -> GetXaxis()->SetTitle("#eta");
  h1_etasc_EE_Data     -> GetXaxis()->SetTitle("supercluster #eta");    
  h1_pt_EE_Data        -> GetXaxis()->SetTitle("p_{T} [GeV]");
  h1_r9_EE_Data        -> GetXaxis()->SetTitle("R9");
  h1_scetawid_EE_Data  -> GetXaxis()->SetTitle("#eta width");
  h1_scphiwid_EE_Data  -> GetXaxis()->SetTitle("#phi width");
  h1_sEtaEta_EE_Data   -> GetXaxis()->SetTitle("#sigma(#eta#eta)");
  h1_sEtaPhi_EE_Data   -> GetXaxis()->SetTitle("#sigma(#eta#phi)");
  h1_s4Ratio_EE_Data   -> GetXaxis()->SetTitle("S4");
  h1_BDToutput_EE_Data -> GetXaxis()->SetTitle("BDT output");
  h1_rr_EE_Data        -> GetXaxis()->SetTitle("#sigmaRR");

  h1_fprCh03_EE_Data    -> GetXaxis()->SetTitle("chargedIso03 (FPR)");     
  h1_fprNeu03_EE_Data   -> GetXaxis()->SetTitle("neutralIso03 (FPR)");     
  h1_fprPh03_EE_Data    -> GetXaxis()->SetTitle("photonIso03 (FPR)");     
  h1_fprRCCh03_EE_Data  -> GetXaxis()->SetTitle("chargedIso03 (FPR, RC)");     
  h1_fprRCNeu03_EE_Data -> GetXaxis()->SetTitle("neutralIso03 (FPR, RC)");     
  h1_fprRCPh03_EE_Data  -> GetXaxis()->SetTitle("photonIso03 (FPR, RC)");     
  /*
  h1_fprCh04_EE_Data    -> GetXaxis()->SetTitle("chargedIso04 (FPR)");     
  h1_fprNeu04_EE_Data   -> GetXaxis()->SetTitle("neutralIso04 (FPR)");     
  h1_fprPh04_EE_Data    -> GetXaxis()->SetTitle("photonIso04 (FPR)");     
  h1_fprRCCh04_EE_Data  -> GetXaxis()->SetTitle("chargedIso04 (FPR, RC)");     
  h1_fprRCNeu04_EE_Data -> GetXaxis()->SetTitle("neutralIso04 (FPR, RC)");     
  h1_fprRCPh04_EE_Data  -> GetXaxis()->SetTitle("photonIso04 (FPR, RC)");     
  */

  // ---------------------------------------------
  // histo titles
  h1_numvtx_Mc       -> SetTitle();
  h1_numvtx_Data     -> SetTitle();

  h1_eta_EB_Mc       -> SetTitle();
  h1_etasc_EB_Mc     -> SetTitle();
  h1_pt_EB_Mc        -> SetTitle();
  h1_r9_EB_Mc        -> SetTitle();
  h1_scetawid_EB_Mc  -> SetTitle();
  h1_scphiwid_EB_Mc  -> SetTitle();
  h1_sEtaEta_EB_Mc   -> SetTitle();
  h1_sEtaPhi_EB_Mc   -> SetTitle();
  h1_s4Ratio_EB_Mc   -> SetTitle();
  h1_BDToutput_EB_Mc -> SetTitle();

  h1_fprCh03_EB_Mc    -> SetTitle();
  h1_fprNeu03_EB_Mc   -> SetTitle();
  h1_fprPh03_EB_Mc    -> SetTitle();
  h1_fprRCCh03_EB_Mc  -> SetTitle();
  h1_fprRCNeu03_EB_Mc -> SetTitle();
  h1_fprRCPh03_EB_Mc  -> SetTitle();
  /*
  h1_fprCh04_EB_Mc    -> SetTitle();
  h1_fprNeu04_EB_Mc   -> SetTitle();
  h1_fprPh04_EB_Mc    -> SetTitle();
  h1_fprRCCh04_EB_Mc  -> SetTitle();
  h1_fprRCNeu04_EB_Mc -> SetTitle();
  h1_fprRCPh04_EB_Mc  -> SetTitle();
  */

  h1_eta_EB_Data       -> SetTitle();
  h1_etasc_EB_Data     -> SetTitle();
  h1_pt_EB_Data        -> SetTitle();
  h1_r9_EB_Data        -> SetTitle();
  h1_scetawid_EB_Data  -> SetTitle();
  h1_scphiwid_EB_Data  -> SetTitle();
  h1_sEtaEta_EB_Data   -> SetTitle();
  h1_sEtaPhi_EB_Data   -> SetTitle();
  h1_s4Ratio_EB_Data   -> SetTitle();
  h1_BDToutput_EB_Data -> SetTitle();

  h1_fprCh03_EB_Data    -> SetTitle();
  h1_fprNeu03_EB_Data   -> SetTitle();
  h1_fprPh03_EB_Data    -> SetTitle();
  h1_fprRCCh03_EB_Data  -> SetTitle();
  h1_fprRCNeu03_EB_Data -> SetTitle();
  h1_fprRCPh03_EB_Data  -> SetTitle();
  /*
  h1_fprCh04_EB_Data    -> SetTitle();
  h1_fprNeu04_EB_Data   -> SetTitle();
  h1_fprPh04_EB_Data    -> SetTitle();
  h1_fprRCCh04_EB_Data  -> SetTitle();
  h1_fprRCNeu04_EB_Data -> SetTitle();
  h1_fprRCPh04_EB_Data  -> SetTitle();
  */

  h1_eta_EE_Mc       -> SetTitle();
  h1_etasc_EE_Mc     -> SetTitle();
  h1_pt_EE_Mc        -> SetTitle();
  h1_r9_EE_Mc        -> SetTitle();
  h1_scetawid_EE_Mc  -> SetTitle();
  h1_scphiwid_EE_Mc  -> SetTitle();
  h1_sEtaEta_EE_Mc   -> SetTitle();
  h1_sEtaPhi_EE_Mc   -> SetTitle();
  h1_s4Ratio_EE_Mc   -> SetTitle();
  h1_BDToutput_EE_Mc -> SetTitle();
  h1_rr_EE_Mc        -> SetTitle();

  h1_fprCh03_EE_Mc    -> SetTitle();
  h1_fprNeu03_EE_Mc   -> SetTitle();
  h1_fprPh03_EE_Mc    -> SetTitle();
  h1_fprRCCh03_EE_Mc  -> SetTitle();
  h1_fprRCNeu03_EE_Mc -> SetTitle();
  h1_fprRCPh03_EE_Mc  -> SetTitle();
  /*
  h1_fprCh04_EE_Mc    -> SetTitle();
  h1_fprNeu04_EE_Mc   -> SetTitle();
  h1_fprPh04_EE_Mc    -> SetTitle();
  h1_fprRCCh04_EE_Mc  -> SetTitle();
  h1_fprRCNeu04_EE_Mc -> SetTitle();
  h1_fprRCPh04_EE_Mc  -> SetTitle();
  */

  h1_eta_EE_Data       -> SetTitle();
  h1_etasc_EE_Data     -> SetTitle();
  h1_pt_EE_Data        -> SetTitle();
  h1_r9_EE_Data        -> SetTitle();
  h1_scetawid_EE_Data  -> SetTitle();
  h1_scphiwid_EE_Data  -> SetTitle();
  h1_sEtaEta_EE_Data   -> SetTitle();
  h1_sEtaPhi_EE_Data   -> SetTitle();
  h1_s4Ratio_EE_Data   -> SetTitle();
  h1_BDToutput_EE_Data -> SetTitle();
  h1_rr_EE_Data        -> SetTitle();

  h1_fprCh03_EE_Data    -> SetTitle();
  h1_fprNeu03_EE_Data   -> SetTitle();
  h1_fprPh03_EE_Data    -> SetTitle();
  h1_fprRCCh03_EE_Data  -> SetTitle();
  h1_fprRCNeu03_EE_Data -> SetTitle();
  h1_fprRCPh03_EE_Data  -> SetTitle();
  /*
  h1_fprCh04_EE_Data    -> SetTitle();
  h1_fprNeu04_EE_Data   -> SetTitle();
  h1_fprPh04_EE_Data    -> SetTitle();
  h1_fprRCCh04_EE_Data  -> SetTitle();
  h1_fprRCNeu04_EE_Data -> SetTitle();
  h1_fprRCPh04_EE_Data  -> SetTitle();
  */

  // ---------------------------------------------
  // cosmetics
  h1_numvtx_Mc       -> SetFillColor(kBlue-9);
  h1_numvtx_Data     -> SetMarkerStyle(20);

  h1_eta_EB_Mc         -> SetFillColor(kBlue-9);
  h1_etasc_EB_Mc       -> SetFillColor(kBlue-9);
  h1_pt_EB_Mc          -> SetFillColor(kBlue-9);
  h1_r9_EB_Mc          -> SetFillColor(kBlue-9);
  h1_scetawid_EB_Mc    -> SetFillColor(kBlue-9);
  h1_scphiwid_EB_Mc    -> SetFillColor(kBlue-9);
  h1_sEtaEta_EB_Mc     -> SetFillColor(kBlue-9);
  h1_sEtaPhi_EB_Mc     -> SetFillColor(kBlue-9);
  h1_s4Ratio_EB_Mc     -> SetFillColor(kBlue-9);
  h1_BDToutput_EB_Mc   -> SetFillColor(kBlue-9);

  h1_fprCh03_EB_Mc     -> SetFillColor(kBlue-9);
  h1_fprNeu03_EB_Mc    -> SetFillColor(kBlue-9);
  h1_fprPh03_EB_Mc     -> SetFillColor(kBlue-9); 
  h1_fprRCCh03_EB_Mc   -> SetFillColor(kBlue-9);
  h1_fprRCNeu03_EB_Mc  -> SetFillColor(kBlue-9);
  h1_fprRCPh03_EB_Mc   -> SetFillColor(kBlue-9);
  /*
  h1_fprCh04_EB_Mc     -> SetFillColor(kBlue-9);
  h1_fprNeu04_EB_Mc    -> SetFillColor(kBlue-9);
  h1_fprPh04_EB_Mc     -> SetFillColor(kBlue-9);
  h1_fprRCCh04_EB_Mc   -> SetFillColor(kBlue-9);
  h1_fprRCNeu04_EB_Mc  -> SetFillColor(kBlue-9);
  h1_fprRCPh04_EB_Mc   -> SetFillColor(kBlue-9);
  */

  h1_eta_EB_Data       -> SetMarkerStyle(20);
  h1_etasc_EB_Data     -> SetMarkerStyle(20);
  h1_pt_EB_Data        -> SetMarkerStyle(20);
  h1_r9_EB_Data        -> SetMarkerStyle(20);
  h1_scetawid_EB_Data  -> SetMarkerStyle(20);
  h1_scphiwid_EB_Data  -> SetMarkerStyle(20);
  h1_sEtaEta_EB_Data   -> SetMarkerStyle(20);
  h1_sEtaPhi_EB_Data   -> SetMarkerStyle(20);
  h1_s4Ratio_EB_Data   -> SetMarkerStyle(20);
  h1_BDToutput_EB_Data -> SetMarkerStyle(20);

  h1_fprCh03_EB_Data     -> SetMarkerStyle(20);
  h1_fprNeu03_EB_Data    -> SetMarkerStyle(20);
  h1_fprPh03_EB_Data     -> SetMarkerStyle(20); 
  h1_fprRCCh03_EB_Data   -> SetMarkerStyle(20);
  h1_fprRCNeu03_EB_Data  -> SetMarkerStyle(20);
  h1_fprRCPh03_EB_Data   -> SetMarkerStyle(20);
  /*
  h1_fprCh04_EB_Data     -> SetMarkerStyle(20);
  h1_fprNeu04_EB_Data    -> SetMarkerStyle(20);
  h1_fprPh04_EB_Data     -> SetMarkerStyle(20);
  h1_fprRCCh04_EB_Data   -> SetMarkerStyle(20);
  h1_fprRCNeu04_EB_Data  -> SetMarkerStyle(20);
  h1_fprRCPh04_EB_Data   -> SetMarkerStyle(20);
  */

  h1_eta_EE_Mc         -> SetFillColor(kBlue-9);
  h1_etasc_EE_Mc       -> SetFillColor(kBlue-9);
  h1_pt_EE_Mc          -> SetFillColor(kBlue-9);
  h1_r9_EE_Mc          -> SetFillColor(kBlue-9);
  h1_scetawid_EE_Mc    -> SetFillColor(kBlue-9);
  h1_scphiwid_EE_Mc    -> SetFillColor(kBlue-9);
  h1_sEtaEta_EE_Mc     -> SetFillColor(kBlue-9);
  h1_sEtaPhi_EE_Mc     -> SetFillColor(kBlue-9);
  h1_s4Ratio_EE_Mc     -> SetFillColor(kBlue-9);
  h1_BDToutput_EE_Mc   -> SetFillColor(kBlue-9);
  h1_rr_EE_Mc          -> SetFillColor(kBlue-9);

  h1_fprCh03_EE_Mc     -> SetFillColor(kBlue-9);
  h1_fprNeu03_EE_Mc    -> SetFillColor(kBlue-9);
  h1_fprPh03_EE_Mc     -> SetFillColor(kBlue-9); 
  h1_fprRCCh03_EE_Mc   -> SetFillColor(kBlue-9);
  h1_fprRCNeu03_EE_Mc  -> SetFillColor(kBlue-9);
  h1_fprRCPh03_EE_Mc   -> SetFillColor(kBlue-9);
  /*
  h1_fprCh04_EE_Mc     -> SetFillColor(kBlue-9);
  h1_fprNeu04_EE_Mc    -> SetFillColor(kBlue-9);
  h1_fprPh04_EE_Mc     -> SetFillColor(kBlue-9);
  h1_fprRCCh04_EE_Mc   -> SetFillColor(kBlue-9);
  h1_fprRCNeu04_EE_Mc  -> SetFillColor(kBlue-9);
  h1_fprRCPh04_EE_Mc   -> SetFillColor(kBlue-9);
  */

  h1_eta_EE_Data       -> SetMarkerStyle(20);
  h1_etasc_EE_Data     -> SetMarkerStyle(20);
  h1_pt_EE_Data        -> SetMarkerStyle(20);
  h1_r9_EE_Data        -> SetMarkerStyle(20);
  h1_scetawid_EE_Data  -> SetMarkerStyle(20);
  h1_scphiwid_EE_Data  -> SetMarkerStyle(20);
  h1_sEtaEta_EE_Data   -> SetMarkerStyle(20);
  h1_sEtaPhi_EE_Data   -> SetMarkerStyle(20);
  h1_s4Ratio_EE_Data   -> SetMarkerStyle(20);
  h1_BDToutput_EE_Data -> SetMarkerStyle(20);
  h1_rr_EE_Data        -> SetMarkerStyle(20);

  h1_fprCh03_EE_Data     -> SetMarkerStyle(20);
  h1_fprNeu03_EE_Data    -> SetMarkerStyle(20);
  h1_fprPh03_EE_Data     -> SetMarkerStyle(20); 
  h1_fprRCCh03_EE_Data   -> SetMarkerStyle(20);
  h1_fprRCNeu03_EE_Data  -> SetMarkerStyle(20);
  h1_fprRCPh03_EE_Data   -> SetMarkerStyle(20);
  /*
  h1_fprCh04_EE_Data     -> SetMarkerStyle(20);
  h1_fprNeu04_EE_Data    -> SetMarkerStyle(20);
  h1_fprPh04_EE_Data     -> SetMarkerStyle(20);
  h1_fprRCCh04_EE_Data   -> SetMarkerStyle(20);
  h1_fprRCNeu04_EE_Data  -> SetMarkerStyle(20);
  h1_fprRCPh04_EE_Data   -> SetMarkerStyle(20);
  */

  TLegend *leg;
  leg = new TLegend(0.15,0.65,0.40,0.90);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(h1_eta_EE_Mc,   "MC",   "f");
  leg->AddEntry(h1_eta_EE_Data, "data", "p");

  TCanvas myC("myC","",1);
  h1_numvtx_Mc->DrawNormalized("hist");
  h1_numvtx_Data->DrawNormalized("sameEp");
  leg->Draw();
  myC.SaveAs("h1_numVtx.png");
  myC.SaveAs("h1_numVtx.root");

  TCanvas myCB("myCB","barrel",1);
  h1_eta_EB_Mc->DrawNormalized("hist");  
  h1_eta_EB_Data->DrawNormalized("sameEp");  
  leg->Draw();
  myCB.SaveAs("h1_eta_EB.png");
  myCB.SaveAs("h1_eta_EB.root");

  h1_etasc_EB_Mc->DrawNormalized("hist");
  h1_etasc_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_etasc_EB.png");
  myCB.SaveAs("h1_etasc_EB.root");

  h1_pt_EB_Mc->DrawNormalized("hist");
  h1_pt_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_pt_EB.png");
  myCB.SaveAs("h1_pt_EB.root");

  h1_r9_EB_Mc->DrawNormalized("hist");
  h1_r9_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_r9_EB.png");
  myCB.SaveAs("h1_r9_EB.root");
  
  h1_scetawid_EB_Mc->DrawNormalized("hist");
  h1_scetawid_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_scetawid_EB.png");
  myCB.SaveAs("h1_scetawid_EB.root");

  h1_scphiwid_EB_Mc->DrawNormalized("hist");
  h1_scphiwid_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_scphiwid_EB.png");
  myCB.SaveAs("h1_scphiwid_EB.root");

  h1_sEtaEta_EB_Mc->DrawNormalized("hist");
  h1_sEtaEta_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_sEtaEta_EB.png");
  myCB.SaveAs("h1_sEtaEta_EB.root");

  h1_sEtaPhi_EB_Mc->DrawNormalized("hist");
  h1_sEtaPhi_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_sEtaPhi_EB.png");
  myCB.SaveAs("h1_sEtaPhi_EB.root");

  h1_s4Ratio_EB_Mc->DrawNormalized("hist");
  h1_s4Ratio_EB_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_s4Ratio_EB.png");
  myCB.SaveAs("h1_s4Ratio_EB.root");

  myCB.SetLogy();
  h1_BDToutput_EB_Mc ->DrawNormalized("hist");
  h1_BDToutput_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_BDToutput_EB.png");
  myCB.SaveAs("h1_BDToutput_EB.root");

  h1_fprCh03_EB_Mc   ->DrawNormalized("hist");
  h1_fprCh03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprCh03_EB.png");
  myCB.SaveAs("h1_fprCh03_EB.root");

  h1_fprNeu03_EB_Mc   ->DrawNormalized("hist");
  h1_fprNeu03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprNeu03_EB.png");
  myCB.SaveAs("h1_fprNeu03_EB.root");

  h1_fprPh03_EB_Mc   ->DrawNormalized("hist");
  h1_fprPh03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprPh03_EB.png");
  myCB.SaveAs("h1_fprPh03_EB.root");

  h1_fprRCCh03_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCCh03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCCh03_EB.png");
  myCB.SaveAs("h1_fprRCCh03_EB.root");

  h1_fprRCNeu03_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCNeu03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCNeu03_EB.png");
  myCB.SaveAs("h1_fprRCNeu03_EB.root");

  h1_fprRCPh03_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCPh03_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCPh03_EB.png");
  myCB.SaveAs("h1_fprRCPh03_EB.root");

  /*
  h1_fprCh04_EB_Mc   ->DrawNormalized("hist");
  h1_fprCh04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprCh04_EB.png");
  myCB.SaveAs("h1_fprCh04_EB.root");

  h1_fprNeu04_EB_Mc   ->DrawNormalized("hist");
  h1_fprNeu04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprNeu04_EB.png");
  myCB.SaveAs("h1_fprNeu04_EB.root");

  h1_fprPh04_EB_Mc   ->DrawNormalized("hist");
  h1_fprPh04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprPh04_EB.png");
  myCB.SaveAs("h1_fprPh04_EB.root");

  h1_fprRCCh04_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCCh04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCCh04_EB.png");
  myCB.SaveAs("h1_fprRCCh04_EB.root");

  h1_fprRCNeu04_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCNeu04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCNeu04_EB.png");
  myCB.SaveAs("h1_fprRCNeu04_EB.root");

  h1_fprRCPh04_EB_Mc   ->DrawNormalized("hist");
  h1_fprRCPh04_EB_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCB.SaveAs("h1_fprRCPh04_EB.png");
  myCB.SaveAs("h1_fprRCPh04_EB.root");
  */


  TCanvas myCE("myCE","endcap",1);
  h1_eta_EE_Mc->DrawNormalized("hist");  
  h1_eta_EE_Data->DrawNormalized("sameEp");  
  leg->Draw();
  myCE.SaveAs("h1_eta_EE.png");
  myCE.SaveAs("h1_eta_EE.root");

  h1_etasc_EE_Mc->DrawNormalized("hist");
  h1_etasc_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_etasc_EE.png");
  myCE.SaveAs("h1_etasc_EE.root");

  h1_pt_EE_Mc->DrawNormalized("hist");
  h1_pt_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_pt_EE.png");
  myCE.SaveAs("h1_pt_EE.root");

  h1_r9_EE_Mc->DrawNormalized("hist");
  h1_r9_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_r9_EE.png");
  myCE.SaveAs("h1_r9_EE.root");
  
  h1_scetawid_EE_Mc->DrawNormalized("hist");
  h1_scetawid_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_scetawid_EE.png");
  myCE.SaveAs("h1_scetawid_EE.root");

  h1_scphiwid_EE_Mc->DrawNormalized("hist");
  h1_scphiwid_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_scphiwid_EE.png");
  myCE.SaveAs("h1_scphiwid_EE.root");

  h1_sEtaEta_EE_Mc->DrawNormalized("hist");
  h1_sEtaEta_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_sEtaEta_EE.png");
  myCE.SaveAs("h1_sEtaEta_EE.root");

  h1_sEtaPhi_EE_Mc->DrawNormalized("hist");
  h1_sEtaPhi_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_sEtaPhi_EE.png");
  myCE.SaveAs("h1_sEtaPhi_EE.root");

  h1_s4Ratio_EE_Mc->DrawNormalized("hist");
  h1_s4Ratio_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_s4Ratio_EE.png");
  myCE.SaveAs("h1_s4Ratio_EE.root");

  h1_rr_EE_Mc->DrawNormalized("hist");
  h1_rr_EE_Data->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_rr_EE.png");
  myCE.SaveAs("h1_rr_EE.root");

  myCE.SetLogy();
  h1_BDToutput_EE_Mc ->DrawNormalized("hist");
  h1_BDToutput_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_BDToutput_EE.png");
  myCE.SaveAs("h1_BDToutput_EE.root");

  h1_fprCh03_EE_Mc   ->DrawNormalized("hist");
  h1_fprCh03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprCh03_EE.png");
  myCE.SaveAs("h1_fprCh03_EE.root");

  h1_fprNeu03_EE_Mc   ->DrawNormalized("hist");
  h1_fprNeu03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprNeu03_EE.png");
  myCE.SaveAs("h1_fprNeu03_EE.root");

  h1_fprPh03_EE_Mc   ->DrawNormalized("hist");
  h1_fprPh03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprPh03_EE.png");
  myCE.SaveAs("h1_fprPh03_EE.root");

  h1_fprRCCh03_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCCh03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCCh03_EE.png");
  myCE.SaveAs("h1_fprRCCh03_EE.root");

  h1_fprRCNeu03_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCNeu03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCNeu03_EE.png");
  myCE.SaveAs("h1_fprRCNeu03_EE.root");

  h1_fprRCPh03_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCPh03_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCPh03_EE.png");
  myCE.SaveAs("h1_fprRCPh03_EE.root");

  /*
  h1_fprCh04_EE_Mc   ->DrawNormalized("hist");
  h1_fprCh04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprCh04_EE.png");
  myCE.SaveAs("h1_fprCh04_EE.root");

  h1_fprNeu04_EE_Mc   ->DrawNormalized("hist");
  h1_fprNeu04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprNeu04_EE.png");
  myCE.SaveAs("h1_fprNeu04_EE.root");

  h1_fprPh04_EE_Mc   ->DrawNormalized("hist");
  h1_fprPh04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprPh04_EE.png");
  myCE.SaveAs("h1_fprPh04_EE.root");

  h1_fprRCCh04_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCCh04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCCh04_EE.png");
  myCE.SaveAs("h1_fprRCCh04_EE.root");

  h1_fprRCNeu04_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCNeu04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCNeu04_EE.png");
  myCE.SaveAs("h1_fprRCNeu04_EE.root");

  h1_fprRCPh04_EE_Mc   ->DrawNormalized("hist");
  h1_fprRCPh04_EE_Data ->DrawNormalized("sameEp");
  leg->Draw();
  myCE.SaveAs("h1_fprRCPh04_EE.png");
  myCE.SaveAs("h1_fprRCPh04_EE.root");
  */
}
