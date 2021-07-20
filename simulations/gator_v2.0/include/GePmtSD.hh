#ifndef GePmtSD_h
#define GePmtSD_h 1


#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "GePmtHit.hh"

class GeConstruction;

class G4Step;
class G4HCofThisEvent;

class GePmtSD : public G4VSensitiveDetector {

   public:
  
     GePmtSD(G4String, GeConstruction*);
     ~GePmtSD();
  
     void Initialize(G4HCofThisEvent*);
     G4bool ProcessHits(G4Step*,G4TouchableHistory*);
     void EndOfEvent(G4HCofThisEvent*);
     void clear();
     void DrawAll();
     void PrintAll();
  
  private:
  
  GePmtHitsCollection* pmtCollection;
     GeConstruction* GeDetector;
     G4int HitID;
};

#endif
