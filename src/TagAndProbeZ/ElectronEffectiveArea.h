//--------------------------------------------------------------------------------------------------
// $Id $
//
// ElectronEffectiveArea
//
// Helper Class for storing effective areas
//
// Authors: S.Xie, E. DiMarco
//
// molto semplificato !  (giulia)
//--------------------------------------------------------------------------------------------------


/// --> NOTE if you want to use this class as standalone without the CMSSW part 
///  you need to uncomment the below line and compile normally with scramv1 b 
///  Then you need just to load it in your root macro the lib with the correct path
#define STANDALONE   // <---- this line

#ifndef ElectronEffectiveArea_H
#define ElectronEffectiveArea_H

#ifndef STANDALONE
#endif

#include <math.h>

using namespace std;

class ElectronEffectiveArea{
 public:
  ElectronEffectiveArea();
  ~ElectronEffectiveArea(); 
  
    enum ElectronEffectiveAreaType {
        kEleTrkIso03, 
        kEleEcalIso03, 
        kEleHcalIso03, 
        kEleTrkIso04, 
        kEleEcalIso04, 
        kEleHcalIso04, 
        kEleChargedIso03, 
        kEleGammaIso03, 
        kEleNeutralHadronIso03, 
        kEleGammaAndNeutralHadronIso03,
        kEleChargedIso04, 
        kEleGammaIso04, 
        kEleNeutralHadronIso04, 
        kEleGammaAndNeutralHadronIso04,
        kEleGammaIsoDR0p0To0p1,
        kEleGammaIsoDR0p1To0p2,
        kEleGammaIsoDR0p2To0p3,
        kEleGammaIsoDR0p3To0p4,
        kEleGammaIsoDR0p4To0p5,
        kEleNeutralHadronIsoDR0p0To0p1,
        kEleNeutralHadronIsoDR0p1To0p2,
        kEleNeutralHadronIsoDR0p2To0p3,
        kEleNeutralHadronIsoDR0p3To0p4,
        kEleNeutralHadronIsoDR0p4To0p5
      };
      
    enum ElectronEffectiveAreaTarget {
      kEleEANoCorr,
      kEleEAData2011,
      kEleEASummer11MC,
      kEleEAFall11MC,
      kEleEAData2012
    };

    static Double_t GetElectronEffectiveArea(ElectronEffectiveAreaType type, Double_t SCEta, 
                                             ElectronEffectiveAreaTarget EffectiveAreaTarget = kEleEAData2011) {
      
      Double_t EffectiveArea = 0;


      if (EffectiveAreaTarget == kEleEANoCorr) {
        return 0.0;
      }

      //2012 Data Effective Areas 
      // see: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaEARhoCorrection
      //EA gamma+neutral had. estimated on Z->ee in DATA 2012 with <ICHEP dataset (~2 fb-1 at 8 TeV ).

      if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.10;
      if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.12;
      if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.085;
      if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.11;
      if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.12;
      if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 ) EffectiveArea = 0.12;
      if (fabs(SCEta) >= 2.4) EffectiveArea = 0.13;
      
      return EffectiveArea;  
    }

};

#endif
