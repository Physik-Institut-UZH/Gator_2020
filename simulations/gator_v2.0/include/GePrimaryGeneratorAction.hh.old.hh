
#ifndef GePrimaryGeneratorMessenger_h
#define GePrimaryGeneratorMessenger_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#ifdef XeENV_GPS_USE
class G4GeneralParticleSource;
#else
class GeParticleSource;
#endif

//class GeAnalysisManager;

class G4Event;

class GePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

   public:
      GePrimaryGeneratorAction();
      ~GePrimaryGeneratorAction();
  
   public:
      void GeneratePrimaries(G4Event* anEvent);

   private:
#ifdef XeENV_GPS_USE
  G4GeneralParticleSource* particleGun;
#else
  GeParticleSource* particleGun;
#endif

   private:
  //      const long* seeds;
  long seeds[2];
  G4double energy_pri;

   public:
  const long* GetEventSeeds()        {return seeds;};
  G4double GetEnergyPrimary()   {return energy_pri;};


};

#endif

