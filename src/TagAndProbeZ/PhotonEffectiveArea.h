//--------------------------------------------------------------------------------------------------
// $Id $
//
// PhotonEffectiveArea
//
// Helper Class for storing effective areas
//
// Authors: S.Xie, E. DiMarco
//
// Semplificato e riadattato per i fotoni!
//--------------------------------------------------------------------------------------------------


/// --> NOTE if you want to use this class as standalone without the CMSSW part 
///  you need to uncomment the below line and compile normally with scramv1 b 
///  Then you need just to load it in your root macro the lib with the correct path
#define STANDALONE   // <---- this line

#ifndef PhotonEffectiveArea_H
#define PhotonEffectiveArea_H

#ifndef STANDALONE
#endif

#include <math.h>

using namespace std;

class PhotonEffectiveArea{
 public:
  PhotonEffectiveArea();
  ~PhotonEffectiveArea(); 
  
    enum PhotonEffectiveAreaType {

      pid_jurECAL03;   
      pid_twrHCAL03;   
      pid_hlwTrack03;   
      pid_hlwTrack03NoDz;   
      pid_hlwTrack03ForCiC;
      pid_pfIsoCharged01ForCiC;
      pid_pfIsoCharged02ForCiC;
      pid_pfIsoCharged03ForCiC;
      pid_pfIsoCharged04ForCiC;
      pid_pfIsoCharged05ForCiC;
      pid_pfIsoCharged06ForCiC;
      pid_pfIsoPhotons01ForCiC;   
      pid_pfIsoPhotons02ForCiC;   
      pid_pfIsoPhotons03ForCiC;   
      pid_pfIsoPhotons04ForCiC;   
      pid_pfIsoPhotons05ForCiC;   
      pid_pfIsoPhotons06ForCiC;   
      pid_pfIsoNeutrals01ForCiC;   
      pid_pfIsoNeutrals02ForCiC;   
      pid_pfIsoNeutrals03ForCiC;   
      pid_pfIsoNeutrals04ForCiC;   
      pid_pfIsoNeutrals05ForCiC;   
      pid_pfIsoNeutrals06ForCiC;   
      
      
    };
      
    enum PhotonEffectiveAreaTarget {
      kPhotEANoCorr,
      //kEleEAData2011,
      //kEleEASummer11MC,
      //kEleEAFall11MC,
      kPhotEAData2012
    };

    static Double_t GetPhotonEffectiveArea(PhotonEffectiveAreaType type, Double_t SCEta, PhotonEffectiveAreaTarget  target = kPhotEAData2012) {
      
      Double_t EffectiveArea = 0;


      if (EffectiveAreaTarget == kPhotEANoCorr) {
        return 0.0;
      }

      //2012 Data Effective Areas
      else if (EffectiveAreaTarget == kPhotEAData2012) {

        if (type == kPhotEAData) {
          if (fabs(SCEta) >= 0.0 && fabs(SCEta) < 1.0 ) EffectiveArea = 0.122;
          if (fabs(SCEta) >= 1.0 && fabs(SCEta) < 1.479 ) EffectiveArea = 0.147;
          if (fabs(SCEta) >= 1.479 && fabs(SCEta) < 2.0 ) EffectiveArea = 0.055;
          if (fabs(SCEta) >= 2.0 && fabs(SCEta) < 2.2 ) EffectiveArea = 0.106;
          if (fabs(SCEta) >= 2.2 && fabs(SCEta) < 2.3 ) EffectiveArea = 0.138;
          if (fabs(SCEta) >= 2.3 && fabs(SCEta) < 2.4 ) EffectiveArea = 0.221;
          if (fabs(SCEta) >= 2.4 ) EffectiveArea = 0.211;
        }
      }
      return EffectiveArea;  
    }

};

#endif
