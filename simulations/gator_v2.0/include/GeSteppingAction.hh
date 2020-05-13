
#ifndef GeSteppingAction_h
#define GeSteppingAction_h 1

#include "G4UserSteppingAction.hh"





class GeSteppingAction : public G4UserSteppingAction
{
  public:
    GeSteppingAction();
   ~GeSteppingAction(){};

    void UserSteppingAction(const G4Step*);
};





#endif
