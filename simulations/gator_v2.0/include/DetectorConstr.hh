/////////////////////////////////////////////////////////
//													   //
//   ++++++++++++++++++++++++++++++++++++++++++++++++  //
//   + Alexander Kish for XENON experiment			+  //
//   + UZH, 2012									+  //
// 	 ++++++++++++++++++++++++++++++++++++++++++++++++  //
//													   //
/////////////////////////////////////////////////////////
#ifndef DetectorConstr_h
#define DetectorConstr_h 1

#include "G4VUserDetectorConstruction.hh"

#include "GeScintSD.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VisAttributes;
class G4Material;
class G4MaterialPropertiesTable;
class G4SubtractionSolid;
class G4UnionSolid;




class DetectorConstr : public G4VUserDetectorConstruction
{

  public:
    DetectorConstr();
   ~DetectorConstr();

  public:
    G4VPhysicalVolume *Construct();
	   
  private:

	
//----------	Logical Volumes		----------------
	G4LogicalVolume *	Laboratory_log;	
	
//----------	Physical Volumes	----------------
	G4VPhysicalVolume *	Laboratory_phys;
	//G4VPhysicalVolume* volF_phys;
//----------	Visual Attributes	----------------
	//G4VisAttributes *	Concrete_vis;
	
//----------	Sensitive Detectors	----------------
	GeScintSD* activeSD;

};

#endif

