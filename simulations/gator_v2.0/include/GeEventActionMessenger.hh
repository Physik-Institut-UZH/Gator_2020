
#ifndef GeEventActionMessenger_h
#define GeEventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GeEventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;


class GeEventActionMessenger: public G4UImessenger {

  public:
    GeEventActionMessenger(GeEventAction*);
   ~GeEventActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
  private:
    GeEventAction*     eventAction;   
  
    G4UIdirectory*        GeDirectory;
    G4UIdirectory*        drawDirectory;
    G4UIcmdWithAString*   DrawTrksCmd;
    G4UIcmdWithAString*   DrawColsCmd;
    G4UIcmdWithABool*     DrawHitsCmd;    
    G4UIcmdWithABool*     SavePmtCmd;    
    G4UIcmdWithABool*     SaveHitsCmd;    
    G4UIcmdWithAnInteger* PrintCmd;  
    
   	//check for overlaps     
	G4UIcmdWithABool *m_pCheckOverlapCmd;  

};

#endif
