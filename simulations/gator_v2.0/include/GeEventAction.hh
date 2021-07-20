#ifndef GeEventAction_h
#define GeEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ios.hh"

#include "GeScintHit.hh"
#include "GeMyTree.hh"

#include "TNtuple.h"
#include "TTree.h"
#include "TBranch.h"
#include "TROOT.h"

class GeRunAction;
class GePrimaryGeneratorAction;
class GeEventActionMessenger;

// class GeAnalysisManager;


class GeEventAction : public G4UserEventAction {

  public:
    GeEventAction(G4int *num, TTree *ntpl, class MyTree *arbol, GeRunAction*, GePrimaryGeneratorAction*);
    virtual ~GeEventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

  private:
    void writeScintHitsToFile(const GeScintHitsCollection*);
    void drawTracks(const G4Event*);

  public:
    void SetDrawTrksFlag (G4String val)     {drawTrksFlag    = val;};
    G4String GetDrawTrksFlag()              {return drawTrksFlag;};

    void SetDrawColsFlag (G4String val)     {drawColsFlag    = val;};
    G4String GetDrawColsFlag()              {return drawColsFlag;};

    void SetDrawHitsFlag (G4int val)        {drawHitsFlag    = val;};
    void SetSavePmtFlag  (G4int val)        {savePmtFlag     = val;};
    void SetSaveHitsFlag (G4bool val)        {saveHitsFlag    = val;};
    void SetPrintModulo  (G4int val)        {printModulo     = val;};

private:
  G4int event_id;
  G4int *evt_num;
  G4int n_pmt;
  TTree *t1;
  MyTree *tree;
  
    const long* seeds;
    G4double energy_pri;

    // hits collections
    G4int scintillatorCollID;                
    G4int S_hits; //Number of hits (saved in the hits collection of the event)

    // event summary
    G4double totEnergy;
    G4double totEnergyGammas;
    G4double totEnergyNeutrons;
    G4double hitEnergy;
    G4double firstLUFXeHitTime;
    G4double firstParticleE;
    G4double particleEnergy;
    G4String particleName;
    G4String firstParticleName;

//    G4bool gamma_ev;
//    G4bool neutron_ev;
//    G4bool positron_ev;
//    G4bool electron_ev;
//    G4bool proton_ev;
//    G4bool other_ev;
//    G4bool start_gamma;
//    G4bool start_neutron;

    // messenger
    G4String drawTrksFlag;
    G4String drawColsFlag;
    G4int drawHitsFlag;         
    G4int savePmtFlag;         
    G4bool saveHitsFlag;         
    G4int printModulo;                         
    GeEventActionMessenger*  eventMessenger;

    GeRunAction*    runAct;  //pointer to run action
    GePrimaryGeneratorAction* genAction; // pointer to particle generator

};

#endif
