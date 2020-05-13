
#include "GeSpecialCuts.hh"
#include "G4VParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"

GeSpecialCuts::GeSpecialCuts(const G4String& aName)
  : G4VProcess(aName)
{
  //G4cout << "Start of SpecialCuts" << G4endl; 
  if (verboseLevel>1) {
     G4cout << GetProcessName() << " is created "<< G4endl;
   }
}

GeSpecialCuts::~GeSpecialCuts() 
{                                     
}                                     

G4VParticleChange* GeSpecialCuts::PostStepDoIt(
			     const G4Track& aTrack,
			     const G4Step& 
			    )
//
// Stop the current particle, if requested by G4UserLimits 
// 			    			    			    
{
   aParticleChange.Initialize(aTrack);
   aParticleChange.ProposeEnergy(0.) ;
   aParticleChange.ProposeLocalEnergyDeposit (aTrack.GetKineticEnergy()) ;
   aParticleChange.ProposeTrackStatus(fStopButAlive);
   return &aParticleChange;
}

G4double GeSpecialCuts::PostStepGetPhysicalInteractionLength(
                             const G4Track&,
                             G4double,
                             G4ForceCondition*
                            )
{
  return DBL_MAX;
}
