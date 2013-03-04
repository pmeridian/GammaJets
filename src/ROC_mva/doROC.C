{
  TFile* stocazzo = new TFile("/xrootdfs/cms/local/gdimperi/Higgs/reduced/redntp.53xv2.cicpfloose.noCorrections.singleGamma_v2_noPresel/merged/redntp_GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1.root");
  TTree* tree = (TTree*)stocazzo->Get("AnaTree");
  gROOT->ProcessLine(".L tree_reader.C++");
  gROOT->ProcessLine(".L MyEvaluateMVA.cc++");
  gROOT->ProcessLine(".L ROC_curve.C++");
  ROC_curve prova(tree);
  prova.CreateROC("mva", 200, -5, 5);
}
