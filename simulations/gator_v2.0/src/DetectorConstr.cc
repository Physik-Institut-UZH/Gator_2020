/////////////////////////////////////////////////////////
//													   //
//   ++++++++++++++++++++++++++++++++++++++++++++++++  //
//   + GEANT4 workshop example 1       				   //
//   + Alexander Kish                  UZH, 2012	   //
// 	 ++++++++++++++++++++++++++++++++++++++++++++++++  //
//													   //
/////////////////////////////////////////////////////////

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Orb.hh"
#include "G4Polyhedra.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"

#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

#include "G4VisAttributes.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"

#include "G4Colour.hh"
#include "globals.hh"

#include "G4ios.hh"

#include "vector"
#include "numeric"
#include "sstream"
#include "algorithm"
#include "cmath"
#include "cassert"

using std::vector;
using std::stringstream;
using std::max;

#include "DetectorConstr.hh"


DetectorConstr::DetectorConstr()
{
}

DetectorConstr::~DetectorConstr()
{
}

G4VPhysicalVolume *DetectorConstr::Construct()
{
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
G4cout 																			<< G4endl;
G4cout << 	" ============================================================ "	<< G4endl;
G4cout <<	"|   Workshop Example 1                                       |"	<< G4endl;
G4cout <<	" ============================================================ "	<< G4endl;
G4cout <<	"| "																<< G4endl;
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////




	////////////////////////////////////////////////////////////////
	//--------------	colours		--------------------------------
	G4Colour white  (1.0,	1.0,	1.0);
	G4Colour grey   (0.5,	0.5,	0.5);
	G4Colour lgrey  (.85,	.85,	.85);
	G4Colour red    (1.0,	0.0,	0.0);
	G4Colour lred   (0.75,	0.0,	0.0);
	G4Colour xlred  (0.5,	0.0,	0.0);
	G4Colour cyan   (0.0,	1.0,	1.0);
	G4Colour blue   (0.0,	0.0,	1.0);
	G4Colour lblue  (.5,	0.5,	1.,		1.);
	G4Colour xlblue (.5,	0.5,	1.,		0.2);
	G4Colour magenta(1.0,	0.0,	1.0);
	G4Colour yellow (1.0,	1.0,	0.0);
	G4Colour green  (0.,	.1,		0.);
	G4Colour lgreen (0.0,	.75,	0.0);
	G4Colour xlgreen(0.0,	0.5,	0.0);
	G4Colour brown  (0.7,	0.4,	0.1);
	G4Colour orange (1.0,	0.5,	0.0);

	
	
	//---------Materials------------//
	
	G4NistManager *pNistManager = G4NistManager::Instance();
	
	//Defining air material from NIST
	G4Material* Air = pNistManager->FindOrBuildMaterial("G4_AIR");
	
	//Constructing steel from elements as a "compound" (using NIST elements)
	G4Element* pIron = pNistManager->FindOrBuildElement("Fe");
	G4Element* pCarbon = pNistManager->FindOrBuildElement("C");
	G4Element* pCobalt = pNistManager->FindOrBuildElement("Co");
	
	G4Material* pSteel = new G4Material("steel",7.7*g/cm3,3);
	pSteel->AddElement(pIron,88.0*perCent);
	pSteel->AddElement(pCarbon,4.0*perCent);
	pSteel->AddElement(pCobalt,8.0*perCent);
	
	//Constructing NaI from molecules (using NIST elements)
	G4Element* pSodium = pNistManager->FindOrBuildElement("Na");
	G4Element* pIodium = pNistManager->FindOrBuildElement("I");
	
	G4Material* pNaI = new G4Material("NaI",3.67*g/cm3,2);
	pNaI->AddElement(pSodium,1);
	pNaI->AddElement(pIodium,1);
	
	//Constructing lead from molecules (using NIST)
	G4Element* pLead_el = pNistManager->FindOrBuildElement("Pb");
	
	G4Material* pLead_mat = new G4Material("lead",11.34*g/cm3,1);
	pLead_mat->AddElement(pLead_el,100.0*perCent);
	
	G4Element* Ge  = new G4Element("Germanium","Ge",32.,72.64*g/mole);
	G4Material* activeGe = new G4Material("activeGe",5.332*g/cm3,1);
	activeGe->AddElement(Ge,1);
	
	//---------Geomtry-------------------//
	
	//---------Defining solids-----------//
	
	//-------Laboratory solid------------//
	G4double labXdim = 1000.0*cm;
	G4double labYdim = 1000.0*cm;
	G4double labZdim = 1000.0*cm;
	
	G4Box* Laboratory_sol = new G4Box("Laboratory_sol",0.5*labXdim,0.5*labYdim,0.5*labZdim);
	
	Laboratory_log = new G4LogicalVolume(Laboratory_sol,Air,"Laboratory_log");
	
	G4VisAttributes* Laboratory_vis = new G4VisAttributes(white);
	Laboratory_vis->SetVisibility(false);
	Laboratory_vis->SetForceSolid(false);
	Laboratory_log->SetVisAttributes(Laboratory_vis);
	
	Laboratory_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),Laboratory_log,"Laboratory",0,false,0);
	
	
	//Plate geometry
	G4double plate_Xdim = 150.0*cm;
	G4double plate_Ydim = 150.0*cm;
	G4double plate_Zdim = 10.0*cm; //Plate thickness
	
	G4Box* plate_sol = new G4Box("plate_sol",0.5*plate_Xdim,0.5*plate_Ydim,0.5*plate_Zdim);
	
	//---------Plate Volumes---------------------//
	
	G4LogicalVolume* plate_log = new G4LogicalVolume(plate_sol,pLead_mat,"plate_log");
	
	G4VisAttributes* plate_vis = new G4VisAttributes(lgreen);
	plate_vis->SetVisibility(true);
	plate_vis->SetForceSolid(true);
	plate_log->SetVisAttributes(plate_vis);
	
	G4double plate_ShiftX = 45.0*cm; //Arbitrary choise
	G4double plate_ShiftY = 0;
	G4double plate_ShiftZ = -0.5*plate_Zdim;
	
	G4ThreeVector plate_Shift(plate_ShiftX,plate_ShiftY,plate_ShiftZ);
	
	G4VPhysicalVolume* plate_phys = new G4PVPlacement(0,plate_Shift,plate_log,"plate_phys",Laboratory_log,false,0);
	

	//Box dimentions.... necessary here to shift properly the volume F
	G4double box_Xdim = 30.0*cm;
	G4double box_Ydim = 40.0*cm;
	G4double box_Zdim = 50.0*cm;
	
	//----------Volume F construction------------------//
	
	//Solid cylinder geometry
	G4double cyl_IR = 0.0*cm; //Inner Radius
	G4double cyl_OR = 30*cm; //Outer Radius
	G4double cyl_Zdim = 60.0*cm; //Height
	
	G4Tubs* cyl_sol = new G4Tubs("cyl_sol",cyl_IR,cyl_OR,0.5*cyl_Zdim,0*deg,360*deg);
	
	//Half sphere geometry
	G4double hSph_IR = 0.0*cm; //Inner Radius
	G4double hSph_OR = 30.0*cm; //Outer Radius
	G4double hSph_SPhi = 0.0*deg;
	G4double hSph_DPhi = 360.0*deg;
	G4double hSph_STheta = 0.0*deg;
	G4double hSph_DTheta = 180.0*deg;//90is enough but is better to overlap the volumes
	
	G4Sphere* halfSph_sol = new G4Sphere("halfSph_sol",hSph_IR,hSph_OR,hSph_SPhi,hSph_DPhi,hSph_STheta,hSph_DTheta);
	
	
	//Shift coordinates of the half sphere respect to the cylinder
	G4double hSph_Shift_X = 0.0*cm;
	G4double hSph_Shift_Y = 0.0*cm;
	G4double hSph_Shift_Z = 0.5*cyl_Zdim;
	
	G4ThreeVector hSph_Shift(hSph_Shift_X,hSph_Shift_Y,hSph_Shift_Z);
	
	G4UnionSolid* volF_sol = new G4UnionSolid("volF_sol",cyl_sol,halfSph_sol,0,hSph_Shift);
	
	//------------F Volumes--------------//
	
	G4LogicalVolume* volF_log = new G4LogicalVolume(volF_sol,activeGe,"volF_log");
	
	G4VisAttributes* volF_vis = new G4VisAttributes(red);
	volF_vis->SetVisibility(true);
	volF_vis->SetForceSolid(true);
	volF_log->SetVisAttributes(volF_vis);
	
	//Shift of the F volume	
	G4double volF_Shift_X = (30.0*cm)+(0.5*box_Xdim)+cyl_OR;
	G4double volF_Shift_Y = 0.0*cm;
	G4double volF_Shift_Z = 0.5*cyl_Zdim;
	
	G4ThreeVector volF_Shift(volF_Shift_X,volF_Shift_Y,volF_Shift_Z);
	
	
	G4VPhysicalVolume* volF_phys =new G4PVPlacement(0,volF_Shift,volF_log,"volF_phys",Laboratory_log,false,0);
	
	//----------- Volume F becomes the sensitive detector --------------//
	
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  	G4String name = "/XeDet/activeSD";
  	activeSD = new GeScintSD(name);
  	SDman->AddNewDetector(activeSD);
  	volF_log->SetSensitiveDetector(activeSD);
	
	
	
	//----------Volume G construction------------------//
	
	
	//---------Volume G geometry (box)
	G4Box* box_sol = new G4Box("box_sol",0.5*box_Xdim,0.5*box_Ydim,0.5*box_Zdim);
	
	
	//Sphere geometry
	G4double fullSph_diam = 5.0*cm;
	
	G4Orb* fullSph_sol = new G4Orb("fullSph_sol",fullSph_diam);
	
	//Shift coordinates of the sphere respect to the box
	G4double fullSph_Shift_X = 0.0*cm;
	G4double fullSph_Shift_Y = 0.0*cm;
	G4double fullSph_Shift_Z = 0.5*box_Zdim - 10.0*cm;
	
	G4ThreeVector hfullSph_Shift(fullSph_Shift_X,fullSph_Shift_Y,fullSph_Shift_Z);
	
	G4SubtractionSolid* volG_sol = new G4SubtractionSolid("volG_sol",box_sol,fullSph_sol,0,hfullSph_Shift);
	
	//------------G Volumes--------------//
	
	G4LogicalVolume* volG_log = new G4LogicalVolume(volG_sol,pNaI,"volG_log");
	
	G4VisAttributes* volG_vis = new G4VisAttributes(red);
	volG_vis->SetVisibility(true);
	volG_vis->SetForceSolid(true);
	volG_log->SetVisAttributes(volG_vis);
	
	//Shift of the G volume	
	G4double volG_Shift_X = 0.0*cm;
	G4double volG_Shift_Y = 0.0*cm;
	G4double volG_Shift_Z = 0.5*box_Zdim;
	
	G4ThreeVector volG_Shift(volG_Shift_X,volG_Shift_Y,volG_Shift_Z);
	
	G4VPhysicalVolume* volG_phys = new G4PVPlacement(0,volG_Shift,volG_log,"volG_phys",Laboratory_log,false,0);
	
	return Laboratory_phys;

////////////////////////////////////////
//--------------	END PROGRAM	------------------------
//------------------------------------------------------

}






