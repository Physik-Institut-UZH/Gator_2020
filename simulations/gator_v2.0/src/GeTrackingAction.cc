
#include "GeTrackingAction.hh"
#include "G4UnitsTable.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "math.h"

// #include "myGenericSD.hh"

void GeTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{

//    G4int ParentID = aTrack->GetParentID();
// //    G4ThreeVector aPos = aTrack->GetPosition();



//    if(ParentID == 1)
//     {

// 	  G4int prec = G4cout.precision(3);

// 	  G4cout << std::setw(5) << aTrack->GetTrackID()-1 << " "
// 		 << std::setw(10) << aTrack->GetPosition().x()
// 		 << std::setw(10) << aTrack->GetPosition().y()
// 		 << std::setw(10) << aTrack->GetPosition().z()
// 		 << std::setw(10) << aTrack->GetKineticEnergy() << G4endl;
      
// 	  G4cout.precision(prec);

//     }
}


