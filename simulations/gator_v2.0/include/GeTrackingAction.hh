#include "G4UserTrackingAction.hh"


class GeTrackingAction : public G4UserTrackingAction {

  public:
    GeTrackingAction(){};
    virtual ~GeTrackingAction(){};
   
    virtual void PreUserTrackingAction(const G4Track*);


};
