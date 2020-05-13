#include "GePrimaryGeneratorAction.hh"

#ifdef XeENV_GPS_USE
#include "G4GeneralParticleSource.hh"
#else
#include "GeParticleSource.hh"
#endif

#ifdef G4ANALYSIS_USE
#include "GeAnalysisManager.hh"
#endif

#include "G4Event.hh"
#include "Randomize.hh"
#include "globals.hh"


GePrimaryGeneratorAction::GePrimaryGeneratorAction() {
  G4cout << "Start of PrimaryGeneratorAction" << G4endl;
#ifdef XeENV_GPS_USE
  particleGun = new G4GeneralParticleSource();
#else
  particleGun = new GeParticleSource();
#endif

  energy_pri=0;
  //  seeds=NULL;
  seeds[0] =-1;
  seeds[1] =-1;

}


GePrimaryGeneratorAction::~GePrimaryGeneratorAction() {

  delete particleGun;
}


void GePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

  energy_pri = 0.;

  // seeds
  //  seeds = HepRandom::getTheSeeds();
  seeds[0] = *CLHEP::HepRandom::getTheSeeds();
  seeds[1] = *(CLHEP::HepRandom::getTheSeeds()+1);

  particleGun->GeneratePrimaryVertex(anEvent);

  energy_pri = particleGun->GetParticleEnergy();

#ifdef G4ANALYSIS_USE 
  GeAnalysisManager* analysis =  GeAnalysisManager::getInstance();
  analysis->analysePrimaryGenerator(energy_pri);
#endif


}




