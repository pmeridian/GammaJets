#define MAXPHOT 40
#define MAXELE 40
#define MAXGENELE 5
//Additional variables specific for the T&P reduced trees

Float_t pu_weight;
Float_t pu_weight30;
Float_t pu_weight50;
Float_t pu_weight75;
Float_t pu_weight90;
Int_t vtxId;


//Generator Level Electrons fromZ
Int_t           nEleMC;
Int_t           idEleMC[MAXGENELE];   //[nEleMC]
Int_t           pdgIdEleMC[MAXGENELE];   //[nEleMC]
Int_t           statusEleMC[MAXGENELE];   //[nEleMC]
Int_t           motherIDEleMC[MAXGENELE];   //[nEleMC]
Float_t         ptEleMC [MAXGENELE];   //[nEleMC]
Float_t         eEleMC  [MAXGENELE];   //[nEleMC]
Float_t         etaEleMC[MAXGENELE];   //[nEleMC]
Float_t         phiEleMC[MAXGENELE];   //[nEleMC]

///Photons Probe
Int_t           isGenMatchPhot[MAXPHOT];   
Int_t           genMatchIndexPhot[MAXPHOT];   
Int_t           isProbePreselPhot[MAXPHOT];   
Int_t           isProbeTightPhot[MAXPHOT];   
Int_t           isProbeMediumPhot[MAXPHOT];   
Int_t           isProbeLoosePhot[MAXPHOT];   
Float_t         mvaIDPhot[MAXPHOT];   
Float_t         r9Phot[MAXPHOT];   
Float_t         s4RatioPhot[MAXPHOT];   
Float_t         sigmaRRPhot[MAXPHOT];   
Float_t         pid_hlwTrack03ForCiCVtx0[MAXPHOT];    
Float_t         pid_hlwTrackForCiCVtx0[MAXPHOT];      
Float_t         pid_pfIsoCharged01ForCiCVtx0[MAXPHOT];
Float_t         pid_pfIsoCharged02ForCiCVtx0[MAXPHOT];
Float_t         pid_pfIsoCharged03ForCiCVtx0[MAXPHOT];
Float_t         pid_pfIsoCharged04ForCiCVtx0[MAXPHOT];
Float_t         pid_pfIsoCharged05ForCiCVtx0[MAXPHOT];
Float_t         pid_pfIsoCharged06ForCiCVtx0[MAXPHOT];

//Electrons Tags
Int_t           isGenMatchEle[MAXELE];   
Int_t           genMatchIndexEle[MAXELE];   
Int_t           isTagTightEle[MAXELE];   
Int_t           isTagMediumEle[MAXELE];   
Int_t           isTagLooseEle[MAXELE];   
