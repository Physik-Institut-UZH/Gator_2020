#ifndef GeMaxTimeCuts_h
#define GeMaxTimeCuts_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "GeSpecialCuts.hh"


class GeMaxTimeCuts : public GeSpecialCuts
{
  public:     

     GeMaxTimeCuts(const G4String& processName ="GeMaxTimeCuts" );

     virtual ~GeMaxTimeCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
			     G4double   previousStepSize,
			     G4ForceCondition* condition
			    );
            
			    
  private:
  
  // hide assignment operator as private 
      GeMaxTimeCuts(GeMaxTimeCuts&);
      GeMaxTimeCuts& operator=(const GeMaxTimeCuts& right);

};

#endif

