
#ifndef GeMinEkineCuts_h
#define GeMinEkineCuts_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "GeSpecialCuts.hh"


class GeMinEkineCuts : public GeSpecialCuts
{
  public:     

     GeMinEkineCuts(const G4String& processName ="GeMinEkineCuts" );

     virtual ~GeMinEkineCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
			     G4double   previousStepSize,
			     G4ForceCondition* condition
			    );
            
			    
  private:
  
  // hide assignment operator as private 
      GeMinEkineCuts(GeMinEkineCuts&);
      GeMinEkineCuts& operator=(const GeMinEkineCuts& right);

};

#endif
