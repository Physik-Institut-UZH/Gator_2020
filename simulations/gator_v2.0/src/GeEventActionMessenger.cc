#include "GeEventActionMessenger.hh"

#include "GeEventAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"
#include "globals.hh"
#include "iostream"


GeEventActionMessenger::GeEventActionMessenger(GeEventAction* EvAct)
:eventAction(EvAct){
  G4cout << "Start of EventActionMessenger" << G4endl;
  // saving event information
  GeDirectory = new G4UIdirectory("/Xe/");
  GeDirectory->SetGuidance("DM Example commands.");

  SavePmtCmd = new G4UIcmdWithABool("/Xe/savePmt",this);
  SavePmtCmd->SetGuidance("Set flag to save (x,y,z) of hits in PMT");
  SavePmtCmd->SetGuidance("into file 'pmt.out'");
  SavePmtCmd->SetGuidance("Default = false");
  SavePmtCmd->SetParameterName("savePmtFlag", false);

  SaveHitsCmd = new G4UIcmdWithABool("/Xe/saveHits",this);
  SaveHitsCmd->SetGuidance("Set flag to save hits in each run");
  SaveHitsCmd->SetGuidance("into file 'hits.out'");
  SaveHitsCmd->SetGuidance("Default = true");
  SaveHitsCmd->SetParameterName("saveHitsFlag", false);

  // drawing event
  drawDirectory = new G4UIdirectory("/Xe/draw/");
  drawDirectory->SetGuidance("DM Example draw commands.");

  DrawColsCmd = new G4UIcmdWithAString("/Xe/draw/drawColours",this);
  DrawColsCmd->SetGuidance("Tracks drawn by Event (standard colours) or by Step (custom colours)");
  DrawColsCmd->SetGuidance("  Choice : custom, standard(default)");
  DrawColsCmd->SetParameterName("drawColsFlag", false);
  DrawColsCmd->SetCandidates("custom standard");
  DrawColsCmd->AvailableForStates(G4State_Idle);

  DrawTrksCmd = new G4UIcmdWithAString("/Xe/draw/drawTracks",this);
  DrawTrksCmd->SetGuidance("Draw the tracks in the event");
  DrawTrksCmd->SetGuidance("  Choice : none, charged, noscint, all(default)");
  DrawTrksCmd->SetParameterName("drawTrksFlag", false);
  DrawTrksCmd->SetCandidates("none charged noscint all");
  DrawTrksCmd->AvailableForStates(G4State_Idle);

  DrawHitsCmd = new G4UIcmdWithABool("/Xe/draw/drawHits",this);
  DrawHitsCmd->SetGuidance("Set flag to draw hits in PMT.");
  DrawHitsCmd->SetGuidance("Default = true");
  DrawHitsCmd->SetParameterName("drawHitsFlag", false);
  DrawHitsCmd->SetDefaultValue(true);

  PrintCmd = new G4UIcmdWithAnInteger("/Xe/printModulo",this);
  PrintCmd->SetGuidance("Print events modulo n");
  PrintCmd->SetParameterName("EventNb",false);
  PrintCmd->SetRange("EventNb>0");
  PrintCmd->AvailableForStates(G4State_Idle);     

}


GeEventActionMessenger::~GeEventActionMessenger() {

  delete SavePmtCmd;  
  delete SaveHitsCmd;  
  delete GeDirectory;
  delete DrawColsCmd;
  delete DrawTrksCmd;
  delete DrawHitsCmd;  
  delete drawDirectory;
  delete PrintCmd;

}

void GeEventActionMessenger::SetNewValue
   (G4UIcommand* command, G4String newValue) { 

  if(command == DrawColsCmd)
    eventAction->SetDrawColsFlag(newValue);

  if(command == DrawTrksCmd)
    eventAction->SetDrawTrksFlag(newValue);

  if(command == DrawHitsCmd) {
    G4int vl;
//    const char* t = newValue;
    //istrstream is((char*)t);
    //is >> vl;
    eventAction->SetDrawHitsFlag(vl!=0);
  }

  if(command == SavePmtCmd) {
    G4int vl;
//    const char* t = newValue;
    //istrstream is((char*)t);
    //is >> vl;
    eventAction->SetSavePmtFlag(vl!=0);
  }

  if(command == SaveHitsCmd) {
	eventAction->SetSaveHitsFlag(true);    
  }

  if(command == PrintCmd)
    {eventAction->SetPrintModulo(PrintCmd->GetNewIntValue(newValue));}


}
