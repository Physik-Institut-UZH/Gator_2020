#ifndef GeScintSD_h
#define GeScintSD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "GeScintHit.hh"

class GeConstruction;
class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GeScintSD : public G4VSensitiveDetector
{
  public:
  
     GeScintSD(G4String);
     ~GeScintSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
        void clear();
        void DrawAll();
        void PrintAll();
  
  private:
  G4String HCname;
  GeScintHitsCollection*  scintillatorCollection;      
  //GeConstruction* GeDetector;
  G4int HCID;
  G4int nHits;
};

#endif

