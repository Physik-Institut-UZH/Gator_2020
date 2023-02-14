#include "globals.hh"

#include "GeConstruction.hh"
#include "GeScintSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Sphere.hh"
#include "G4EllipticalTube.hh"
#include "G4Polycone.hh"

#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"
#include "G4Transform3D.hh"

#include <math.h>
#include <string.h>
#include <stdio.h>

#include <TMath.h>


GeConstruction::GeConstruction()
{;}

GeConstruction::~GeConstruction()
{
}

G4VPhysicalVolume* GeConstruction::Construct()
{


	if(pCheckOverlap)  
	   SecondOverlapCheck();
	   
	   
  //------------------------------------------------------ colors  
  G4cout << "start of Construction" << G4endl;

  G4Colour red (1.0, 0.0, 0.0);
  G4Colour green (0.0, 1.0, 0.0);
  G4Colour blue (0.0, 0.0, 1.0);
  G4Colour white (1.0, 1.0, 1.0);
  G4Colour grey (0.5, 0.5, 0.5);
  G4Colour lgrey (0.85, 0.85, 0.85);
  G4Colour cyan (0.0, 1.0, 1.0);
  G4Colour magenta (1.0, 0.0, 1.0);
  G4Colour yellow (1.0, 1.0, 0.0);
  G4Colour orange (0.75, 0.55, 0.0);
  G4Colour lblue (0.0, 0.0, 0.55);
  //G4Colour lgreen (0.0, 0.75, 0.0);
  G4Colour brown (0.7, 0.4, 0.1);
  G4Colour purple (0.5, 0.0, 0.5);


  //------------------------------------------------------ materials
  #include "includematerials.hh"

  //------------------------------------------------------ volumes

  //some solids to be subtracted stick out 1 cm to eliminate "shared surfaces"

  //------------------------ experimental hall (world volume)

  G4double lab_x = 2.0*m;
  G4double lab_y = 2.0*m;
  G4double lab_z = 2.0*m;

  G4Box* lab_box  = new G4Box("lab_box",0.5*lab_x,0.5*lab_y,0.5*lab_z);

  lab_log = new G4LogicalVolume(lab_box, Air,"lab_log",0,0,0);
  lab_log -> SetVisAttributes (G4VisAttributes::Invisible);
 
  lab_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),lab_log,"lab",0,false,0, true);

  G4cout<<"lab"<<G4endl;
//--------------------------------------Pb box 75 Bq/kg 
  G4double lead_box_75Bqkg_x = 75*cm;
  G4double lead_box_75Bqkg_y = 75*cm;
  G4double lead_box_75Bqkg_z = 60*cm;

  G4Box* Lead4_Shield = new G4Box("Lead4_Shield",0.5*lead_box_75Bqkg_x,0.5*lead_box_75Bqkg_y,0.5*lead_box_75Bqkg_z);

  G4LogicalVolume* lead_box_75Bqkg_log = new G4LogicalVolume(Lead4_Shield,Pb,"lead_box_75Bqkg_log");

  G4VisAttributes* lead_box_75Bqkg_vis = new G4VisAttributes(white);
  lead_box_75Bqkg_vis->SetVisibility(false);
  lead_box_75Bqkg_vis->SetForceSolid(false);
  lead_box_75Bqkg_log->SetVisAttributes(lead_box_75Bqkg_vis);

  G4double lead_box_75Bqkg_Pos_x = 0.0*cm;
  G4double lead_box_75Bqkg_Pos_y = 0.0*cm;
  G4double lead_box_75Bqkg_Pos_z = 0.0*cm;

  lead_box_75Bqkg_phys=new G4PVPlacement(0,G4ThreeVector(lead_box_75Bqkg_Pos_x,lead_box_75Bqkg_Pos_y,lead_box_75Bqkg_Pos_z),lead_box_75Bqkg_log,"lead_box_75Bqkg_phys",lab_log,false,0, true);

  G4cout<<"first lead box"<<G4endl;
//--------------------------------------Pb Box 3 Bq/kg
  G4double lead_box_3Bqkg_x = 45*cm;
  G4double lead_box_3Bqkg_y = 45*cm;
  G4double lead_box_3Bqkg_z = 45*cm;

  G4Box* Lead1_Shield = new G4Box("Lead1_Shield",0.5*lead_box_3Bqkg_x,0.5*lead_box_3Bqkg_y,0.5*lead_box_3Bqkg_z);

  G4LogicalVolume* lead_box_3Bqkg_log = new G4LogicalVolume(Lead1_Shield,Pb,"lead_box_3Bqkg_log");

  G4VisAttributes* lead_box_3Bqkg_vis = new G4VisAttributes(white);
  lead_box_3Bqkg_vis->SetVisibility(false);
  lead_box_3Bqkg_vis->SetForceSolid(false);
  lead_box_3Bqkg_log->SetVisAttributes(lead_box_3Bqkg_vis);

  G4double lead_box_3Bqkg_Pos_x = 0.0*cm;
  G4double lead_box_3Bqkg_Pos_y = 0.0*cm;
  G4double lead_box_3Bqkg_Pos_z = 7.5*cm;

  lead_box_3Bqkg_phys = 
       new G4PVPlacement(0,G4ThreeVector(lead_box_3Bqkg_Pos_x,lead_box_3Bqkg_Pos_y,lead_box_3Bqkg_Pos_z),
                         lead_box_3Bqkg_log,"lead_box_3Bqkg_phys",lead_box_75Bqkg_log,false,0, true);

  G4cout<<"second lead box"<<G4endl;
//--------------------------------------Cu Box of the Shield 
  G4double copper_box_x = 35*cm;
  G4double copper_box_y = 35*cm;
  G4double copper_box_z = 40*cm;

  G4Box* copper_box_Shield = new G4Box("copper_box_Shield",0.5*copper_box_x,0.5*copper_box_y,0.5*copper_box_z);

  G4LogicalVolume* copper_box_log = new G4LogicalVolume(copper_box_Shield,Cu,"copper_box_log");

  G4VisAttributes* copper_box_vis = new G4VisAttributes(green);
  copper_box_vis->SetVisibility(false);
  copper_box_vis->SetForceSolid(false);
  copper_box_vis->SetForceWireframe(true);
  copper_box_log->SetVisAttributes(copper_box_vis);

  G4double copperPos1_x = 0.0*cm;
  G4double copperPos1_y = 0.0*cm;
  G4double copperPos1_z = 2.5*cm;
	
  G4ThreeVector copper_box_Shift(copperPos1_x,copperPos1_y,copperPos1_z);

  copper_box_phys = 
       new G4PVPlacement(0,copper_box_Shift,
                         copper_box_log,"copper_box_phys",lead_box_3Bqkg_log,false,0, true);

  G4cout<<"copper box"<<G4endl;
	
	
	
 //-----------------------GATOR inner cavity

  G4double cavity1_x = 25.*cm;
  G4double cavity1_y = 25.*cm;
  G4double cavity1_z = 33.*cm;
	
	
  G4double base_hole_ID1 = 0.0*cm;
  G4double base_hole_OD1 = 13.7*cm; //The hole diameter is 1cm larger than the base diameter
	G4double base_hole_Height1 = 3.0*cm; //The cilindrical hole must be of 2cm inside the Cu shield

	
	G4double stick_hole_x = 0.5*cavity1_x;
	G4double stick_hole_y = 1.6*cm; //The same width of the cold stick cover diameter
	G4double stick_hole_z = 1.*cm;
	
	
  G4Box* cavity0 = new G4Box("cavity0",0.5*cavity1_x,0.5*cavity1_y,0.5*cavity1_z);
	
	G4Tubs* base_hole = new G4Tubs("base_hole",0.5*base_hole_ID1,0.5*base_hole_OD1,0.5*base_hole_Height1,0.0*deg,360.0*deg);
	
	G4Box* stick_hole = new G4Box("stick_hole",0.5*stick_hole_x,stick_hole_y,0.5*stick_hole_z);
	
	G4ThreeVector base_hole_Shift(0,0,-2*cm+0.5*(base_hole_Height1-cavity1_z));
	
	G4ThreeVector stick_hole_Shift(-0.5*stick_hole_x,0,-1.*cm+0.5*(stick_hole_z-cavity1_z));
	
	G4UnionSolid* cavityA = new G4UnionSolid("cavityA",cavity0,base_hole,0,base_hole_Shift);
	
	G4UnionSolid* cavity1 = new G4UnionSolid("cavity1",cavityA,stick_hole,0,stick_hole_Shift);

  G4LogicalVolume* cavity1_log = new G4LogicalVolume(cavity1,Air,"cavity1_log");

  G4VisAttributes* cavity1_vis = new G4VisAttributes(green);
  cavity1_vis->SetVisibility(true);
  cavity1_vis->SetForceSolid(false);
  cavity1_log->SetVisAttributes(cavity1_vis);

  G4double cavity1Pos_x = 0.0*cm;
  G4double cavity1Pos_y = 0.0*cm;
  G4double cavity1Pos_z = 3.5*cm;

	G4ThreeVector cavity1_shift(cavity1Pos_x,cavity1Pos_y,cavity1Pos_z);
	
  cavity1_phys = 
       new G4PVPlacement(0,cavity1_shift,
                         cavity1_log,"cavity1_phys",copper_box_log,false,0, true);

G4cout<<"cavity"<<G4endl;

// From here the cavity center absolute coordinates are (0,0,13.5) cm


//--------------------------------------Cu top Shield
  G4double copper_top_x = 75*cm;
  G4double copper_top_y = 75*cm;
  G4double copper_top_z = (5-0.00001)*cm;

  G4Box* copper_top_Shield = new G4Box("copper_top_Shield",0.5*copper_top_x,0.5*copper_top_y,0.5*copper_top_z);

  G4LogicalVolume* copper_top_log = new G4LogicalVolume(copper_top_Shield,Cu,"copper_top_log");

  G4VisAttributes* copper_top_vis = new G4VisAttributes(red);
  copper_top_vis->SetVisibility(false);
  copper_top_vis->SetForceSolid(false);
  copper_top_log->SetVisAttributes(copper_top_vis);

  G4double copper_top_Pos_x = 0.0*cm;
  G4double copper_top_Pos_y = 0.0*cm;
  G4double copper_top_Pos_z = 32.5*cm;

  copper_top_phys = 
       new G4PVPlacement(0,G4ThreeVector(copper_top_Pos_x,copper_top_Pos_y,copper_top_Pos_z),
                         copper_top_log,"copper_top_phys",lab_log,false,0, true);

G4cout<<"copper top"<<G4endl;
//--------------------------------------Pb layer top 3 Bq/kg
  G4double lead_top_3Bqkg_x = 75*cm;
  G4double lead_top_3Bqkg_y = 75*cm;
  G4double lead_top_3Bqkg_z = 5*cm;

  G4Box* Lead5_Shield = new G4Box("Lead5_Shield",0.5*lead_top_3Bqkg_x,0.5*lead_top_3Bqkg_y,0.5*lead_top_3Bqkg_z);

  G4LogicalVolume* lead_top_3Bqkg_log = new G4LogicalVolume(Lead5_Shield,Pb,"lead_top_3Bqkg_log");

  G4VisAttributes* lead_top_3Bqkg_vis = new G4VisAttributes(white);
  lead_top_3Bqkg_vis->SetVisibility(false);
  lead_top_3Bqkg_vis->SetForceSolid(false);
  lead_top_3Bqkg_log->SetVisAttributes(lead_top_3Bqkg_vis);

  G4double lead_top_3Bqkg_Pos_x = 0.0*cm;
  G4double lead_top_3Bqkg_Pos_y = 0.0*cm;
  G4double lead_top_3Bqkg_Pos_z = (37.5+0.00002)*cm;

  lead_top_3Bqkg_phys = 
       new G4PVPlacement(0,G4ThreeVector(lead_top_3Bqkg_Pos_x, lead_top_3Bqkg_Pos_y, lead_top_3Bqkg_Pos_z),
                         lead_top_3Bqkg_log,"lead_top_3Bqkg_phys",lab_log,false,0, true);

G4cout<<"lead top first layer "<<G4endl;
//--------------------------------------Pb layer top 75 Bq/kg
  G4double lead_top_75Bqkg_x = 75*cm;
  G4double lead_top_75Bqkg_y = 75*cm;
  G4double lead_top_75Bqkg_z = 15*cm;

  G4Box* Lead6_Shield = new G4Box("Lead6_Shield",0.5*lead_top_75Bqkg_x,0.5*lead_top_75Bqkg_y,0.5*lead_top_75Bqkg_z);

  G4LogicalVolume* lead_top_75Bqkg_log = new G4LogicalVolume(Lead6_Shield, Pb, "lead_top_75Bqkg_log");

  G4VisAttributes* lead_top_75Bqkg_vis = new G4VisAttributes(white);
  lead_top_75Bqkg_vis->SetVisibility(false);
  lead_top_75Bqkg_vis->SetForceSolid(false);
  lead_top_75Bqkg_log->SetVisAttributes(lead_top_75Bqkg_vis);

  G4double lead_top_75Bqkg_Pos_x = 0.0*cm;
  G4double lead_top_75Bqkg_Pos_y = 0.0*cm;
  G4double lead_top_75Bqkg_Pos_z = (47.5+0.00003)*cm;

  lead_top_75Bqkg_phys = 
       new G4PVPlacement(0,G4ThreeVector(lead_top_75Bqkg_Pos_x,lead_top_75Bqkg_Pos_y,lead_top_75Bqkg_Pos_z),
                         lead_top_75Bqkg_log,"lead_top_75Bqkg_phys",lab_log,false,0, true);

G4cout<<"lead top second layer"<<G4endl;
	
	
	//-----------------------------------------cryostat base
	G4double baseID1 = 0.0*cm;
	G4double baseOD1 = 12.7*cm;
	G4double baseHeight1 = 7.0*cm;
	
	G4Tubs* base = new G4Tubs("base",0.5*baseID1,0.5*baseOD1,0.5*baseHeight1,0.0*deg,360.0*deg);
	
	G4LogicalVolume* base_log = new G4LogicalVolume(base,Cu,"base_log");
	
	G4VisAttributes* base_vis = new G4VisAttributes(blue);
	base_vis->SetVisibility(true);
	base_vis->SetForceSolid(false);
	base_log->SetVisAttributes(base_vis);
	
	
	// Position of the base relative to the inner cavity.

	G4double basePos_x = 0.0*cm;
	G4double basePos_y = 0.0*cm;
	G4double basePos_z = -2.*cm+0.5*(baseHeight1-cavity1_z);
	
	G4ThreeVector base_Shift(basePos_x,basePos_y,basePos_z); 
	
	base_phys = new G4PVPlacement(0,base_Shift,base_log,"base_phys",cavity1_log,false,0, true);
	


//--------------------------------------cryostat endcap
  G4double endcapID1 = 0.0*cm;
  G4double endcapOD1 = 10.16*cm;
  G4double endcapHeight1 = 12.905*cm;

  G4Tubs* endcap_main = new G4Tubs("endcap_main", 0.5*endcapID1, 0.5*endcapOD1,
				   0.5*endcapHeight1, 0.0*deg, 360.0*deg);

  G4double endcapID3 = 0.0*cm;
  G4double endcapOD3 = 12.7*cm;
  G4double endcapHeight3 = 0.635*cm;

  G4Tubs* endcap_flange = new G4Tubs("endcap_flange", 0.5*endcapID3, 0.5*endcapOD3, 
				   0.5*endcapHeight3, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_2(0*cm,0*cm,-0.5*endcapHeight1-0.5*endcapHeight3);

  G4UnionSolid* Endcap = new G4UnionSolid("Endcap",endcap_main,
					       endcap_flange,0,translation_2);

  G4LogicalVolume* endcap_log = new G4LogicalVolume(Endcap,Cu,"endcap_log");

  G4VisAttributes* endcap_vis = new G4VisAttributes(blue);
  endcap_vis->SetVisibility(true);
  endcap_vis->SetForceSolid(false);
  endcap_log->SetVisAttributes(endcap_vis);

  G4double endcapPos_x = 0.0*cm; //base is 1.0cm from wall, decrease x to decrease separation
  G4double endcapPos_y = 0.0*cm;
  G4double endcapPos_z = -(2.*cm+0.5*cavity1_z) + endcapHeight3 + baseHeight1 + 0.5*endcapHeight1+(0.001*mm); //Added a little shift to avoid surfaces ovelapping
  //G4double endcapPos_z = -1.4325*cm; //base is 1.0cm from bottom, decrease z to lower base

	
	G4ThreeVector endcap_Shift(endcapPos_x,endcapPos_y,endcapPos_z);
  endcap_phys = new G4PVPlacement(0,endcap_Shift,endcap_log,"endcap_phys",cavity1_log,false,0, true);


//--------------------------------------outer vacuum
  G4double vacID = 0.0*cm;
  G4double vacOD = 9.86*cm;
  G4double vacHeight = 13.39999*cm;  //3-13-06

  G4Tubs* Outer_Vacuum = new G4Tubs("Outer_Vacuum", 0.5*vacID, 0.5*vacOD,
				   0.5*vacHeight, 0.0*deg, 360.0*deg);

  G4LogicalVolume* vacuum_log = new G4LogicalVolume(Outer_Vacuum,Vacuum,"vacuum_log");

  G4VisAttributes* vacuum_vis = new G4VisAttributes(purple);
  vacuum_vis->SetVisibility(false);
  vacuum_vis->SetForceSolid(false);
  vacuum_log->SetVisAttributes(vacuum_vis);

  G4double vacPos_x = 0.0*cm;
  G4double vacPos_y = 0.0*cm;
  G4double vacPos_z = -0.3675*cm;

  vacuum_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos_x,vacPos_y,vacPos_z),
                         vacuum_log,"vacuum_phys",endcap_log,false,0, true);

  //--------------------------------------crystal holder
  G4double holderID1 = 0.0*cm;
  G4double holderOD1 = 8.53*cm;
  G4double holderHeight1 = 8.9*cm;

  G4Tubs* Holder_main = new G4Tubs("Holder_main", 0.5*holderID1, 0.5*holderOD1,
				   0.5*holderHeight1, 0.0*deg, 360.0*deg);

  G4double holderID2 = 0.0*cm;
  G4double holderOD2 = 8.81*cm;
  G4double holderHeight2 = 0.13*cm;

  G4Tubs* Holder_top = new G4Tubs("Holder_top", 0.5*holderID2, 0.5*holderOD2,
				   0.5*holderHeight2, 0.0*deg, 360.0*deg);

  G4double holderID3 = 0.0*cm;
  G4double holderOD3 = 8.53*cm;
  G4double holderHeight3 = 1.5*cm;

  G4Tubs* Holder_base = new G4Tubs("Holder_base", 0.5*holderID3, 0.5*holderOD3,
				   0.5*holderHeight3, 0.0*deg, 360.0*deg);

  G4double holderID6 = 0.0*cm;
  G4double holderOD6 = 2.54*cm;
  G4double holderHeight6 = 2.0*cm;

  G4Tubs* Holder_bottom1 = new G4Tubs("Holder_bottom1", 0.5*holderID6, 0.5*holderOD6,
				   0.5*holderHeight6, 0.0*deg, 360.0*deg);

  G4double holderID7 = 0.0*cm;
  G4double holderOD7 = 2.54*cm;
  G4double holderHeight7 = 0.55*cm;  //cut in half due to extension into base

  G4Tubs* Holder_bottom2 = new G4Tubs("Holder_bottom2", 0.5*holderID7, 0.5*holderOD7,
				   0.5*holderHeight7, 0.0*deg, 360.0*deg);

  G4double holderID4 = 0.0*cm;
  G4double holderOD4 = 8.91*cm;
  G4double holderHeight4 = 0.86*cm;

  G4Tubs* Holder_ring1 = new G4Tubs("Holder_ring1", 0.5*holderID4, 0.5*holderOD4,
				   0.5*holderHeight4, 0.0*deg, 360.0*deg);

  G4double holderID5 = 0.0*cm;
  G4double holderOD5 = 8.91*cm;
  G4double holderHeight5 = 0.86*cm;

  G4Tubs* Holder_ring2 = new G4Tubs("Holder_ring2", 0.5*holderID5, 0.5*holderOD5,
				   0.5*holderHeight5, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_3(0*cm,0*cm,0.5*holderHeight1-0.5*holderHeight2);
  G4ThreeVector translation_4(0*cm,0*cm,-0.5*holderHeight1-0.5*holderHeight3);
  G4ThreeVector translation_5(0*cm,0*cm,2.62*cm);
  G4ThreeVector translation_6(0*cm,0*cm,-1.12*cm);
  G4ThreeVector translation_9(0*cm,0*cm,-0.5*holderHeight1-holderHeight3-
			      0.5*holderHeight6);
  G4ThreeVector translation_10(0*cm,0*cm,-0.5*holderHeight1-holderHeight3-
			      holderHeight6-0.5*holderHeight7);

  G4UnionSolid* Holder1 = new G4UnionSolid("Holder1",Holder_main,
					       Holder_top,0,translation_3);
  G4UnionSolid* Holder2 = new G4UnionSolid("Holder2",Holder1,
					       Holder_base,0,translation_4);
  G4UnionSolid* Holder3 = new G4UnionSolid("Holder3",Holder2,
					       Holder_ring1,0,translation_5);
  G4UnionSolid* Holder4 = new G4UnionSolid("Holder4",Holder3,
					       Holder_ring2,0,translation_6);
  G4UnionSolid* Holder5 = new G4UnionSolid("Holder5",Holder4,
					       Holder_bottom1,0,translation_9);
  G4UnionSolid* Holder = new G4UnionSolid("Holder",Holder5,
					       Holder_bottom2,0,translation_10);

  G4LogicalVolume* holder_log = new G4LogicalVolume(Holder,Cu,"holder_log");

  G4VisAttributes* holder_vis = new G4VisAttributes(white);
  holder_vis->SetVisibility(false);
  holder_vis->SetForceSolid(false);
  holder_log->SetVisAttributes(holder_vis);

  G4double holderPos_x = 0.0*cm;
  G4double holderPos_y = 0.0*cm;
  G4double holderPos_z = 1.815*cm;

  holder_phys = 
       new G4PVPlacement(0,G4ThreeVector(holderPos_x,holderPos_y,holderPos_z),
                         holder_log,"holder_phys",vacuum_log,false,0, true);

  //--------------------------------------inner vacuum
  G4double innervac1ID = 0.0*cm;
  G4double innervac1OD = 8.37*cm;
  G4double innervac1Height = 8.89999*cm; //3-13-06

  G4Tubs* inner_vacuum_top = new G4Tubs("inner_vacuum_top", 0.5*innervac1ID, 0.5*innervac1OD,
				   0.5*innervac1Height, 0.0*deg, 360.0*deg);

  G4double innervac2ID = 0.0*cm;
  G4double innervac2OD = 1.6*cm;
  G4double innervac2Height = 3.5*cm;

  G4Tubs* inner_vacuum_mid = new G4Tubs("inner_vacuum_mid", 0.5*innervac2ID, 0.5*innervac2OD,
				   0.5*innervac2Height, 0.0*deg, 360.0*deg);

  G4double innervac3ID = 0.0*cm;
  G4double innervac3OD = 0.60706*cm;
  G4double innervac3Height = 0.55*cm;  //cut in half due to extension into base

  G4Tubs* inner_vacuum_bot = new G4Tubs("inner_vacuum_bot", 0.5*innervac3ID, 0.5*innervac3OD,
				   0.5*innervac3Height, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_25(0*cm,0*cm,-0.5*innervac1Height-0.5*innervac2Height);
  G4ThreeVector translation_26(0*cm,0*cm,-0.5*innervac1Height-innervac2Height-
				0.5*innervac3Height);

  G4UnionSolid* innervac1 = new G4UnionSolid("innervac1",inner_vacuum_top,
					       inner_vacuum_mid,0,translation_25);
  G4UnionSolid* Innervac = new G4UnionSolid("Innervac",innervac1,
					       inner_vacuum_bot,0,translation_26);

  G4LogicalVolume* innervac_log = new G4LogicalVolume(Innervac,Vacuum,"innervac_log");

  G4VisAttributes* innervac_vis = new G4VisAttributes(yellow);
  innervac_vis->SetVisibility(false);
  innervac_vis->SetForceSolid(false);
  innervac_log->SetVisAttributes(innervac_vis);

  G4double vacPos4_x = 0.0*cm;
  G4double vacPos4_y = 0.0*cm;
  G4double vacPos4_z = 0.0*cm;

  innervac_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos4_x,vacPos4_y,vacPos4_z),
                         innervac_log,"innervac_phys",holder_log,false,0, true);

  //--------------------------------------teflon plug 
  G4double plug2ID1 = 0.0*cm;
  G4double plug2OD1 = 2.6*cm;
  G4double plug2Height1 = 0.3999*cm;

  G4Tubs* plug_top = new G4Tubs("plug_top", 0.5*plug2ID1, 0.5*plug2OD1,
				   0.5*plug2Height1, 0.0*deg, 360.0*deg);

  G4double plug2ID2 = 0.0*cm;
  G4double plug2OD2 = 1.5999*cm; //a tiny amount of clearance
  G4double plug2Height2 = 1.3*cm;

  G4Tubs* plug_middle = new G4Tubs("plug_middle", 0.5*plug2ID2, 0.5*plug2OD2,
				   0.5*plug2Height2, 0.0*deg, 360.0*deg);

  G4double plug2ID3 = 0.0*cm;
  G4double plug2OD3 = 1.5999*cm; //a tiny amount of clearance
  G4double plug2Height3 = 0.3*cm;

  G4Tubs* plug_bottom = new G4Tubs("plug_bottom", 0.5*plug2ID3, 0.5*plug2OD3,
				   0.5*plug2Height3, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_11(0*cm,0*cm,-0.5*plug2Height1-0.5*plug2Height2);
  G4ThreeVector translation_12(0*cm,0*cm,-0.5*plug2Height1-plug2Height2-
				0.5*plug2Height3);

  G4UnionSolid* Plug1 = new G4UnionSolid("Plug1",plug_top,plug_middle,0,
					 translation_11);
  G4UnionSolid* Plug2 = new G4UnionSolid("Plug2",Plug1,plug_bottom,0,
					 translation_12);

  G4LogicalVolume* plug_log = new G4LogicalVolume(Plug2,Teflon,"plug_log");

  G4VisAttributes* plug_vis = new G4VisAttributes(lgrey);
  plug_vis->SetVisibility(false);
  plug_vis->SetForceSolid(false);
  plug_log->SetVisAttributes(plug_vis);

  G4double plugPos_x = 0.0*cm;
  G4double plugPos_y = 0.0*cm;
  G4double plugPos_z = -4.24999*cm; //just above the bottom surface of the holder

  plug_phys = 
       new G4PVPlacement(0,G4ThreeVector(plugPos_x,plugPos_y,plugPos_z),
                         plug_log,"plug_phys",innervac_log,false,0, true);

  //-----------------------------------------plug vacuum
  G4double innervac4ID = 0.0*cm;
  G4double innervac4OD = 0.7*cm;
  G4double innervac4Height = 1.69989*cm;  //3-13-06

  G4Tubs* inner_vacuum2_top = new G4Tubs("inner_vacuum2_top", 0.5*innervac4ID, 0.5*innervac4OD,
				   0.5*innervac4Height, 0.0*deg, 360.0*deg);

  G4double innervac5ID = 0.0*cm;
  G4double innervac5OD = 0.38*cm;
  G4double innervac5Height = 0.3*cm;

  G4Tubs* inner_vacuum2_bot = new G4Tubs("inner_vacuum2_bot", 0.5*innervac5ID, 0.5*innervac5OD,
				   0.5*innervac5Height, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_27(0*cm,0*cm,-0.5*innervac4Height-0.5*innervac5Height);

  G4UnionSolid* innervac2 = new G4UnionSolid("innervac2",inner_vacuum2_top,
					       inner_vacuum2_bot,0,translation_27);

  G4LogicalVolume* innervac3_log = new G4LogicalVolume(innervac2,Vacuum,"innervac3_log");

  G4VisAttributes* innervac3_vis = new G4VisAttributes(lblue);
  innervac3_vis->SetVisibility(false);
  innervac3_vis->SetForceSolid(false);
  innervac3_log->SetVisAttributes(innervac3_vis);

  G4double vacPos6_x = 0.0*cm;
  G4double vacPos6_y = 0.0*cm;
  G4double vacPos6_z = -0.65*cm;

  innervac3_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos6_x,vacPos6_y,vacPos6_z),
                         innervac3_log,"innervac3_phys",plug_log,false,0, true);

  //------------------------------ crystal cover
  G4double coverID = 0.0*cm;
  G4double coverOD = 8.3*cm;
  G4double coverHeight = 8.5*cm;

  G4Tubs* Cover = new G4Tubs("Cover", 0.5*coverID, 0.5*coverOD,
				   0.5*coverHeight, 0.0*deg, 360.0*deg);
  //G4ThreeVector translation_19(0*cm,0*cm,-0.55*cm);


  G4LogicalVolume* cover_log = new G4LogicalVolume(Cover,Teflon,"cover_log");

  G4VisAttributes* cover_vis = new G4VisAttributes(lgrey);
  cover_vis->SetVisibility(false);
  cover_vis->SetForceSolid(false);
  cover_log->SetVisAttributes(cover_vis);

  G4double coverPos_x = 0.0*cm;
  G4double coverPos_y = 0.0*cm;
  G4double coverPos_z = 0.19999999*cm; //3-13-06


  //below is commented out for overlap check - it has a known overlap with its mother volume innervac_log
  cover_phys = 
       new G4PVPlacement(0,G4ThreeVector(coverPos_x,coverPos_y,coverPos_z),
                         cover_log,"cover_phys",innervac_log,false,0, false);

  //---------------------inner vacuum (inside crystal cover, around crystal)
  G4double vacID9 = 0.0*cm;
  G4double vacOD9 = 8.20001*cm;
  G4double vacHeight9 = 8.39999*cm;  //3-13-06

  G4Tubs* Inner_Vacuum2 = new G4Tubs("Inner_Vacuum2", 0.5*vacID9, 0.5*vacOD9,
				   0.5*vacHeight9, 0.0*deg, 360.0*deg);

  G4LogicalVolume* innervac2_log = new G4LogicalVolume(Inner_Vacuum2,Vacuum,"innervac2_log");

  G4VisAttributes* innervac2_vis = new G4VisAttributes(lblue);
  innervac2_vis->SetVisibility(false);
  innervac2_vis->SetForceSolid(false);
  innervac2_log->SetVisAttributes(innervac2_vis);

  G4double vacPos5_x = 0.0*cm;
  G4double vacPos5_y = 0.0*cm;
  G4double vacPos5_z = -0.05*cm;

  innervac2_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos5_x,vacPos5_y,vacPos5_z),
                         innervac2_log,"innervac2_phys",cover_log,false,0, true);

  //------------------------------ ge_crystal
  G4double innerRadiusOfTheCrystal = 0.0*cm;
  G4double outerRadiusOfTheCrystal = 4.085*cm; 
  G4double heightOfTheCrystal = 8.15*cm;

  G4Tubs* CrystalWOHole = new G4Tubs("CrystalWOHole",innerRadiusOfTheCrystal,
                                    outerRadiusOfTheCrystal,0.5*heightOfTheCrystal,
				     0.0*deg,360.0*deg);

  //G4ThreeVector translation_1(0*cm,0*cm,-0.5*heightOfTheCrystal
  //			      +0.5*heightOfTheHole-1*cm);
  //G4ThreeVector translation_20(0*cm,0*cm,-0.5*heightOfTheCrystal
  //			      +0.5*grooveHeight-1*cm);


  G4LogicalVolume* crystal_log = new G4LogicalVolume(CrystalWOHole,Ge,"crystal_log");

  G4VisAttributes* crystal_vis = new G4VisAttributes(grey);
  crystal_vis->SetVisibility(false);
  crystal_vis->SetForceSolid(false);
  crystal_log->SetVisAttributes(crystal_vis);

  G4double crystalPos_x = 0.0*cm;
  G4double crystalPos_y = 0.0*cm;
  G4double crystalPos_z = 0.12499*cm; //crystal almost touches the cover
  //crystal located at (-15.24, 0, 3.85998999)

  crystal_phys = 
       new G4PVPlacement(0,G4ThreeVector(crystalPos_x,crystalPos_y,crystalPos_z),
                         crystal_log,"crystal_phys",innervac2_log,false,0, true);

  //--------------------------------------crystal vacuum 1 (hole)
  G4double vacID7 = 0.0*cm;
  G4double vacOD7 = 1.05*cm;
  G4double vacHeight7 = 6.6*cm;

  G4Tubs* crystalhole = new G4Tubs("crystalhole", 0.5*vacID7, 0.5*vacOD7,
				   0.5*vacHeight7, 0.0*deg, 360.0*deg);

  G4LogicalVolume* crystalhole_log = new G4LogicalVolume(crystalhole,Vacuum,"crystalhole_log");

  G4VisAttributes* crystalhole_vis = new G4VisAttributes(lblue);
  crystalhole_vis->SetVisibility(false);
  crystalhole_vis->SetForceSolid(false);
  crystalhole_log->SetVisAttributes(crystalhole_vis);

  G4double vacPos7_x = 0.0*cm;
  G4double vacPos7_y = 0.0*cm;
  G4double vacPos7_z = -0.5*heightOfTheCrystal+0.5*vacHeight7+0.00001*cm;  //3-13-06

  crystalhole_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos7_x,vacPos7_y,vacPos7_z),
                         crystalhole_log,"crystalhole_phys",crystal_log,false,0, true);

  //--------------------------------------crystal vacuum (groove)
  G4double vacID8 = 2.4*cm;
  G4double vacOD8 = 3.0*cm;
  G4double vacHeight8 = 0.2*cm;

  G4Tubs* crystalgroove = new G4Tubs("crystalgroove", 0.5*vacID8, 0.5*vacOD8,
				   0.5*vacHeight8, 0.0*deg, 360.0*deg);

  G4LogicalVolume* crystalgroove_log = new G4LogicalVolume(crystalgroove,Vacuum,"crystalgroove_log");

  G4VisAttributes* crystalgroove_vis = new G4VisAttributes(orange);
  crystalgroove_vis->SetVisibility(false);
  crystalgroove_vis->SetForceSolid(false);
  crystalgroove_log->SetVisAttributes(crystalgroove_vis);

  G4double vacPos8_x = 0.0*cm;
  G4double vacPos8_y = 0.0*cm;
  G4double vacPos8_z = -3.975*cm+0.00001*cm; //3-13-06

  crystalgroove_phys = 
       new G4PVPlacement(0,G4ThreeVector(vacPos8_x,vacPos8_y,vacPos8_z),
                         crystalgroove_log,"crystalgroove_phys",crystal_log,false,0, true);


  //------------------------------ ge_crystal_active_region
  G4double crystalID = 0.0*cm;
  G4double crystalOD = 8.01*cm;  // as of 02.2023
  G4double crystalHeight = 8.02*cm;  // as of 02.2023

  G4Tubs* Crystal2WOHole = new G4Tubs("Crystal2WOHole", 0.5*crystalID,0.5*crystalOD,
				      0.5*crystalHeight,0.0*deg,360.0*deg);

  G4double holeID = 0.0*cm;
  G4double holeOD = 1.0506*cm;
  G4double holeHeight = 6.5203*cm;

  G4Tubs* Hole2 = new G4Tubs("Hole2",holeID,0.5*holeOD,0.5*holeHeight,
                                    0.0*deg,360.0*deg);

  G4double groove2ID = 2.24*cm;
  G4double groove2OD = 3.16*cm;
  G4double groove2Height = 1.2*cm;

  G4Tubs* groove2 = new G4Tubs("groove2",0.5*groove2ID,0.5*groove2OD,
				      0.5*groove2Height,0.0*deg,360.0*deg);

  G4ThreeVector translation_7(0*cm,0*cm,-0.5*crystalHeight+0.5*holeHeight);
  G4ThreeVector translation_21(0*cm,0*cm,-0.5*crystalHeight+0.5*groove2Height-1*cm);

  G4SubtractionSolid* Crystal2WOGroove = new G4SubtractionSolid("Crystal2WOGroove",
						Crystal2WOHole,Hole2,0,translation_7);
  G4SubtractionSolid* Crystal2 = new G4SubtractionSolid("Crystal2",Crystal2WOGroove,
         					      groove2,0,translation_21);

  G4LogicalVolume* active_log = new G4LogicalVolume(Crystal2,activeGe,"active_log");

  G4VisAttributes* active_vis = new G4VisAttributes(brown);
  active_vis->SetVisibility(false);
  active_vis->SetForceSolid(false);
  active_log->SetVisAttributes(active_vis);

  G4double crystal2Pos_x = 0.0*cm;
  G4double crystal2Pos_y = 0.0*cm;
  G4double crystal2Pos_z = 0.0*cm; //was -0.0110067

  active_phys = 
       new G4PVPlacement(0,G4ThreeVector(crystal2Pos_x,crystal2Pos_y,crystal2Pos_z),
                         active_log,"active_phys",crystal_log,false,0, true);

  //-------------------------------------------set sensitive detector
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  name = "/XeDet/activeSD";
  activeSD = new GeScintSD(name);
  SDman->AddNewDetector(activeSD);
  active_log->SetSensitiveDetector(activeSD);
  //----------------------------------------------------------------


  //------------------------------------IR Window - Mylar(top of crystal)
  G4double mylarID = 0.0*cm;
  G4double mylarOD = 8.17*cm;
  G4double mylarHeight = 0.0110067*cm;

  G4Tubs* Mylar = new G4Tubs("Mylar", 0.5*mylarID,0.5*mylarOD,
				      0.5*mylarHeight,0.0*deg,360.0*deg);

  G4LogicalVolume* mylar_log = new G4LogicalVolume(Mylar,mylar,"mylar_log");

  G4VisAttributes* mylar_vis = new G4VisAttributes(grey);
  mylar_vis->SetVisibility(false);
  mylar_vis->SetForceSolid(false);
  mylar_log->SetVisAttributes(mylar_vis);

  G4double mylarPos_x = 0.0*cm;
  G4double mylarPos_y = 0.0*cm;
  G4double mylarPos_z = 0.5*heightOfTheCrystal-0.5*mylarHeight-0.000001*cm; //3-13-06

  mylar_phys = 
       new G4PVPlacement(0,G4ThreeVector(mylarPos_x,mylarPos_y,mylarPos_z),
                         mylar_log,"mylar_phys",crystal_log,false,0, true);

  //------------------------------------IR Window - Kapton(top of crystal)
  G4double kaptonID = 0.0*cm;
  G4double kaptonOD = 8.17*cm;
  G4double kaptonHeight = 0.01016*cm;

  G4Tubs* Kapton = new G4Tubs("Kapton", 0.5*kaptonID,0.5*kaptonOD,
				      0.5*kaptonHeight,0.0*deg,360.0*deg);

  G4LogicalVolume* kapton_log = new G4LogicalVolume(Kapton,kapton,"kapton_log");

  G4VisAttributes* kapton_vis = new G4VisAttributes(brown);
  kapton_vis->SetVisibility(false);
  kapton_vis->SetForceSolid(false);
  kapton_log->SetVisAttributes(kapton_vis);

  G4double kaptonPos_x = 0.0*cm;
  G4double kaptonPos_y = 0.0*cm;
  G4double kaptonPos_z = 0.5*mylarHeight-0.5*kaptonHeight-0.000001*cm;  //3-13-06

  kapton_phys = 
       new G4PVPlacement(0,G4ThreeVector(kaptonPos_x,kaptonPos_y,kaptonPos_z),
                         kapton_log,"kapton_phys",mylar_log,false,0, true);

  //------------------------------------------------------------------------------------
  //-----------------------------------------------core signal contact 1 (crystal)
  G4double contactID1 = 0.0*cm;
  G4double contactOD1 = 1.049999*cm; //small clearance inside hole
  G4double contactHeight1 = 0.1*cm;
  
  G4Tubs* contact_top1 = new G4Tubs("contact_top1", 0.5*contactID1,0.5*contactOD1,
				      0.5*contactHeight1,0.0*deg,360.0*deg);

  G4LogicalVolume* contact1_log = new G4LogicalVolume(contact_top1,Cu,"contact1_log");

  G4VisAttributes* contact1_vis = new G4VisAttributes(orange);
  contact1_vis->SetVisibility(false);
  contact1_vis->SetForceSolid(false);
  contact1_log->SetVisAttributes(contact1_vis);

  G4double contact1Pos_x = 0.0*cm;
  G4double contact1Pos_y = 0.0*cm;
  G4double contact1Pos_z = -3.249*cm;

  contact1_phys = 
       new G4PVPlacement(0,G4ThreeVector(contact1Pos_x,contact1Pos_y,contact1Pos_z),
                         contact1_log,"contact1_phys",crystalhole_log,false,0, true);

  //---------------------------------------core signal contact 2 (inner vac)
  G4double contactID2 = 0.0*cm;
  G4double contactOD2 = 1.6*cm;
  G4double contactHeight2 = 0.1*cm;

  G4Tubs* contact_top2 = new G4Tubs("contact_top2", 0.5*contactID2,0.5*contactOD2,
				      0.5*contactHeight2,0.0*deg,360.0*deg);
  
  G4double contactID3 = 0.0*cm;
  G4double contactOD3 = 0.67*cm;
  G4double contactHeight3 = 0.119*cm; //.14

  G4Tubs* contact_middle = new G4Tubs("contact_middle", 0.5*contactID3,0.5*contactOD3,
				      0.5*contactHeight3,0.0*deg,360.0*deg);

  G4ThreeVector translation_14(0*cm,0*cm,-0.5*contactHeight2-0.5*contactHeight3);

  G4UnionSolid* Contact2 = new G4UnionSolid("Contact2",contact_top2,
					       contact_middle,0,translation_14);


  G4LogicalVolume* contact2_log = new G4LogicalVolume(Contact2,Cu,"contact2_log");

  G4VisAttributes* contact2_vis = new G4VisAttributes(orange);
  contact2_vis->SetVisibility(false);
  contact2_vis->SetForceSolid(false);
  contact2_log->SetVisAttributes(contact2_vis);

  G4double contact2Pos_x = 0.0*cm;
  G4double contact2Pos_y = 0.0*cm;
  G4double contact2Pos_z = -4.03*cm;

  contact2_phys = 
       new G4PVPlacement(0,G4ThreeVector(contact2Pos_x,contact2Pos_y,contact2Pos_z),
                         contact2_log,"contact2_phys",innervac2_log,false,0, true);


  //---------------------------------------core signal contact 3 (inner plug vac)
  G4double contactID4 = 0.0*cm;
  G4double contactOD4 = 0.67*cm;
  G4double contactHeight4 = 0.75*cm;

  G4Tubs* contact_mid2 = new G4Tubs("contact_mid2", 0.5*contactID4,0.5*contactOD4,
				      0.5*contactHeight4,0.0*deg,360.0*deg);
  
  G4double contactID5 = 0.0*cm;
  G4double contactOD5 = 0.35*cm;
  G4double contactHeight5 = 1.24*cm;

  G4Tubs* contact_bottom = new G4Tubs("contact_bottom", 0.5*contactID5,0.5*contactOD5,
				      0.5*contactHeight5,0.0*deg,360.0*deg);

  G4ThreeVector translation_15(0*cm,0*cm,-0.5*contactHeight4-0.5*contactHeight5);

  G4UnionSolid* Contact3 = new G4UnionSolid("Contact3",contact_mid2,
					       contact_bottom,0,translation_15);


  G4LogicalVolume* contact3_log = new G4LogicalVolume(Contact3,Cu,"contact3_log");

  G4VisAttributes* contact3_vis = new G4VisAttributes(orange);
  contact3_vis->SetVisibility(false);
  contact3_vis->SetForceSolid(false);
  contact3_log->SetVisAttributes(contact3_vis);

  G4double contact3Pos_x = 0.0*cm;
  G4double contact3Pos_y = 0.0*cm;
  G4double contact3Pos_z = 0.47*cm;

  contact3_phys = 
       new G4PVPlacement(0,G4ThreeVector(contact3Pos_x,contact3Pos_y,contact3Pos_z),
                         contact3_log,"contact3_phys",innervac3_log,false,0, true);


  //-------------------------------------------------spring



  //-------------------------------------------------lower vacuum
  G4double vacID2 = 0.0*cm;
  G4double vacOD2= 5.8*cm;
  G4double vacHeight2 = 1.8*cm;

  G4Tubs* vacuum_top = new G4Tubs("vacuum_top", 0.5*vacID2, 0.5*vacOD2,
				   0.5*vacHeight2, 0.0*deg, 360.0*deg);

  G4double vacID3 = 0.0*cm;
  G4double vacOD3= 12.1*cm;
  G4double vacHeight3 = 4.9*cm;  //was 4.6??

  G4Tubs* vacuum_bottom = new G4Tubs("vacuum_bottom", 0.5*vacID3, 0.5*vacOD3,
				   0.5*vacHeight3, 0.0*deg, 360.0*deg);

  G4ThreeVector translation_22(0*cm,0*cm,-0.5*vacHeight2-0.5*vacHeight3);

  G4UnionSolid* Lower_Vacuum= new G4UnionSolid("Lower_Vacuum",vacuum_top,
					       vacuum_bottom,0,translation_22);

  G4LogicalVolume* lower_vacuum_log = new G4LogicalVolume(Lower_Vacuum,Vacuum,"lower_vacuum_log");

  G4VisAttributes* lower_vacuum_vis = new G4VisAttributes(lblue);
  lower_vacuum_vis->SetVisibility(false);
  lower_vacuum_vis->SetForceSolid(false);
  lower_vacuum_log->SetVisAttributes(lower_vacuum_vis);

  G4double vacPos2_x = 0.0*cm;
  G4double vacPos2_y = 0.0*cm;
  G4double vacPos2_z = 2.6*cm-0.000001*cm;  //was 2.52? 3-13-06
	
	G4ThreeVector lower_vacuum_shift(vacPos2_x,vacPos2_y,vacPos2_z);
	
	lower_vacuum_phys = 
       new G4PVPlacement(0,lower_vacuum_shift,
                         lower_vacuum_log,"lower_vacuum_phys",base_log,false,0, true);

  //------------------------------------------------small holder piece
  G4double holder2ID = 0.0*cm;
  G4double holder2OD = 2.54*cm;
  G4double holder2Height = 0.55*cm;  //cut in half due to extension into base

  G4Tubs* Holder_new = new G4Tubs("Holder_new", 0.5*holder2ID, 0.5*holder2OD,
				   0.5*holder2Height, 0.0*deg, 360.0*deg);

  G4LogicalVolume* holder2_log = new G4LogicalVolume(Holder_new,Cu,"holder2_log");

  G4VisAttributes* holder2_vis = new G4VisAttributes(yellow);
  holder2_vis->SetVisibility(false);
  holder2_vis->SetForceSolid(false);
  holder2_log->SetVisAttributes(holder2_vis);

  G4double holder2Pos_x = 0.0*cm;
  G4double holder2Pos_y = 0.0*cm;
  G4double holder2Pos_z = 0.625*cm-0.000001*cm; //3-13-06

  holder2_phys = 
       new G4PVPlacement(0,G4ThreeVector(holder2Pos_x,holder2Pos_y,holder2Pos_z),
                         holder2_log,"holder2_phys",lower_vacuum_log,false,0, true);

  //------------------------------------------------small holder vacuum
  G4double holder2vacID = 0.0*cm;
  G4double holder2vacOD = 0.60706*cm;
  G4double holder2vacHeight = 0.54999*cm;  //cut in half due to extension into base 3-13-06

  G4Tubs* Holder2vac = new G4Tubs("Holder2vac", 0.5*holder2vacID, 0.5*holder2vacOD,
				   0.5*holder2vacHeight, 0.0*deg, 360.0*deg);

  G4LogicalVolume* holder2vac_log = new G4LogicalVolume(Holder2vac,Vacuum,"holder2vac_log");

  G4VisAttributes* holder2vac_vis = new G4VisAttributes(lblue);
  holder2vac_vis->SetVisibility(false);
  holder2vac_vis->SetForceSolid(false);
  holder2vac_log->SetVisAttributes(holder2vac_vis);

  G4double holder2vacPos_x = 0.0*cm;
  G4double holder2vacPos_y = 0.0*cm;
  G4double holder2vacPos_z = 0.0*cm;

  holder2vac_phys = 
       new G4PVPlacement(0,G4ThreeVector(holder2vacPos_x,holder2vacPos_y,holder2vacPos_z),
                         holder2vac_log,"holder2vac_phys",holder2_log,false,0, true);
	
	
	
	//-----------------------------------cold stick 5 (inside the base)
	//This piece of the code for the cold stick is put before in order to use its z coordinate for all the other stick pieces. This because this stick has relative coordinate referred to the base and more exactly to "lower_vacuum_phys".
	
	G4double stick5_ID = 0.0*cm;
	G4double stick5_OD= 1.9*cm;
	G4double stick5_Height = (3.15-0.00003)*cm; //3-13-06
	
	G4Tubs* Stick5 = new G4Tubs("Stick5", 0.5*stick5_ID, 0.5*stick5_OD,
										 0.5*stick5_Height, 0.0*deg, 360.0*deg);
	G4RotationMatrix rotStick5;
  	rotStick5.rotateY(90*deg);
	
	G4LogicalVolume* stick5_log = new G4LogicalVolume(Stick5,Cu,"stick5_log");
	
	G4VisAttributes* stick5_vis = new G4VisAttributes(purple);
	stick5_vis->SetVisibility(false);
	stick5_vis->SetForceSolid(false);
	stick5_log->SetVisAttributes(stick5_vis);
	
	G4double stick5_Pos_x = -4.275*cm; //should be 4.475, but ID of base
	G4double stick5_Pos_y = 0.0*cm;
	G4double stick5_Pos_z = -3.1*cm;
	
	G4ThreeVector stick5_Shift(stick5_Pos_x,stick5_Pos_y,stick5_Pos_z);
	
	stick5_phys = 
	new G4PVPlacement(G4Transform3D(rotStick5,stick5_Shift),
							stick5_log,"stick5_phys",lower_vacuum_log,false,0, true);
	
	

//-------------------------cold stick cover 1 (the one which sticks in lead box 75 Bq/kg)
  
  G4double cold_stick_cover1_ID = 0.0*cm;
  G4double cold_stick_cover1_OD= 3.2*cm;
  G4double cold_stick_cover1_Height = 15*cm-0.00001*cm; //3-13-06

  G4Tubs* Tube2 = new G4Tubs("Tube2", 0.5*cold_stick_cover1_ID, 0.5*cold_stick_cover1_OD,
				   0.5*cold_stick_cover1_Height, 0.0*deg, 360.0*deg);

  G4RotationMatrix rotTube2;
	rotTube2.rotateY(90*deg);

  G4LogicalVolume* cold_stick_cover1_log = new G4LogicalVolume(Tube2,Cu,"cold_stick_cover1_log");

  G4VisAttributes* cold_stick_cover1_vis = new G4VisAttributes(blue);
  cold_stick_cover1_vis->SetVisibility(false);
  cold_stick_cover1_vis->SetForceSolid(false);
  cold_stick_cover1_log->SetVisAttributes(cold_stick_cover1_vis);

	
	//Referring the 'z' shift coordinate of this piece of stick in relation of the 'z' coordinate of the stick5, which is inside the "lower_vacuum" volume, which is inside the "base" volume, which is in the "cavity1", which is in the "copper_box", which is in the "lead_box_3BqKg".
  G4double cold_stick_cover1_Pos_x = -30*cm; 
  G4double cold_stick_cover1_Pos_y = 0.0*cm;
  //G4double cold_stick_cover1_Pos_z = 1.0*cm;
	G4double cold_stick_cover1_Pos_z = stick5_Pos_z+vacPos2_z+basePos_z+cavity1Pos_z+copperPos1_z+lead_box_3Bqkg_Pos_z;
	
	G4ThreeVector cold_stick_cover1_Shift(cold_stick_cover1_Pos_x, cold_stick_cover1_Pos_y, cold_stick_cover1_Pos_z);

  cold_stick_cover1_phys = 
       new G4PVPlacement(G4Transform3D(rotTube2,cold_stick_cover1_Shift),
                         cold_stick_cover1_log,"cold_stick_cover1_phys",lead_box_75Bqkg_log,false,0, true);

//-------------------------------cold stick cover 2 (sticking in Pb box 3 Bq/kg)
  G4double cold_stick_cover2_ID = 0.0*cm;
  G4double cold_stick_cover2_OD= 3.2*cm;
  G4double cold_stick_cover2_Height = 5*cm-0.00001*cm; //3-13-06

  G4Tubs* Tube5 = new G4Tubs("Tube5", 0.5*cold_stick_cover2_ID, 0.5*cold_stick_cover2_OD,
				   0.5*cold_stick_cover2_Height, 0.0*deg, 360.0*deg);

  G4RotationMatrix rotTube5;
	rotTube5.rotateY(90*deg);

  G4LogicalVolume* cold_stick_cover2_log = new G4LogicalVolume(Tube5,Cu,"cold_stick_cover2_log");

  G4VisAttributes* cold_stick_cover2_vis = new G4VisAttributes(blue);
  cold_stick_cover2_vis->SetVisibility(false);
  cold_stick_cover2_vis->SetForceSolid(false);
  cold_stick_cover2_log->SetVisAttributes(cold_stick_cover2_vis);

	
	//Referring the 'z' shift coordinate of this piece of stick in relation of the 'z' coordinate of the stick5, which is inside the "lower_vacuum" volume, which is inside the "base" volume, which is in the "cavity1", which is in the "copper_box".
  G4double cold_stick_cover2_Pos_x = -20*cm; 
  G4double cold_stick_cover2_Pos_y = 0.0*cm;
  //G4double cold_stick_cover2_Pos_z = -6.5*cm;
	G4double cold_stick_cover2_Pos_z = stick5_Pos_z+vacPos2_z+basePos_z+cavity1Pos_z+copperPos1_z;

  cold_stick_cover2_phys = 
       new G4PVPlacement(G4Transform3D(rotTube5,G4ThreeVector(cold_stick_cover2_Pos_x,cold_stick_cover2_Pos_y,cold_stick_cover2_Pos_z)),
                        cold_stick_cover2_log,"cold_stick_cover2_phys",lead_box_3Bqkg_log,false,0, true);


//---------------------------------cold stick cover 3 (sticking in the copper box)
  G4double cold_stick_cover3_ID = 0.0*cm;
  G4double cold_stick_cover3_OD= 3.2*cm;
  G4double cold_stick_cover3_Height = 5*cm-0.00001*cm; //3-13-06

  G4Tubs* Tube6 = new G4Tubs("Tube6", 0.5*cold_stick_cover3_ID, 0.5*cold_stick_cover3_OD,
				   0.5*cold_stick_cover3_Height, 0.0*deg, 360.0*deg);

  G4RotationMatrix rotTube6;
	rotTube6.rotateY(90*deg);

  G4LogicalVolume* cold_stick_cover3_log = new G4LogicalVolume(Tube6,Cu,"cold_stick_cover3_log");

  G4VisAttributes* cold_stick_cover3_vis = new G4VisAttributes(blue);
  cold_stick_cover3_vis->SetVisibility(false);
  cold_stick_cover3_vis->SetForceSolid(false);
  cold_stick_cover3_log->SetVisAttributes(cold_stick_cover3_vis);

	
	//Referring the 'z' shift coordinate of this piece of stick in relation of the 'z' coordinate of the stick5, which is inside the "lower_vacuum" volume, which is inside the "base" volume, which is in the "cavity1".
  G4double cold_stick_cover3_Pos_x = -15.0*cm; 
  G4double cold_stick_cover3_Pos_y = 0.0*cm;
  //G4double cold_stick_cover3_Pos_z = -9.0*cm;
	G4double cold_stick_cover3_Pos_z = stick5_Pos_z+vacPos2_z+basePos_z+cavity1Pos_z;


	cold_stick_cover3_phys = 
       new G4PVPlacement(G4Transform3D(rotTube6,G4ThreeVector(cold_stick_cover3_Pos_x,cold_stick_cover3_Pos_y,cold_stick_cover3_Pos_z)),
cold_stick_cover3_log,"cold_stick_cover3_phys",copper_box_log,false,0, true);
											


//------------------------------cold stick cover 4 (sticking in the inner cavity)
  G4double cold_stick_cover4_ID = 0.0*cm;
  G4double cold_stick_cover4_OD= 3.2*cm;
  G4double cold_stick_cover4_Height = 6.15*cm-0.00001*cm; //3-13-06

  G4Tubs* Tube7 = new G4Tubs("Tube7", 0.5*cold_stick_cover4_ID, 0.5*cold_stick_cover4_OD,
				   0.5*cold_stick_cover4_Height, 0.0*deg, 360.0*deg);

  G4RotationMatrix rotTube7;
	rotTube7.rotateY(90*deg);

  G4LogicalVolume* cold_stick_cover4_log = new G4LogicalVolume(Tube7,Cu,"cold_stick_cover4_log");

  G4VisAttributes* cold_stick_cover4_vis = new G4VisAttributes(blue);
  cold_stick_cover4_vis->SetVisibility(true);
  cold_stick_cover4_vis->SetForceSolid(false);
  cold_stick_cover4_log->SetVisAttributes(cold_stick_cover4_vis);
	
  //Referring the 'z' shift coordinate of this piece of stick in relation of the 'z' coordinate of the stick5, which is inside the "lower_vacuum" volume, which is inside the "base" volume.
  G4double cold_stick_cover4_Pos_x = -9.425*cm; 
  G4double cold_stick_cover4_Pos_y = 0.0*cm;
  //G4double cold_stick_cover4_Pos_z = -12.5*cm;
	G4double cold_stick_cover4_Pos_z = stick5_Pos_z+vacPos2_z+basePos_z;
	
	G4ThreeVector cold_stick_cover4_Shift(cold_stick_cover4_Pos_x,cold_stick_cover4_Pos_y,cold_stick_cover4_Pos_z);

  cold_stick_cover4_phys = 
       new G4PVPlacement(G4Transform3D(rotTube7,cold_stick_cover4_Shift),
                        cold_stick_cover4_log,"cold_stick_cover4_phys",cavity1_log,false,0, true);


//----------------------------------------cold stick vacuum 1 (first lead box) 
  
  G4double csvacID1 = 0.0*cm;
  G4double csvacOD1 = 2.8*cm;
  G4double csvacHeight1 = (15-0.00002)*cm;

  G4Tubs* csvacuum1 = new G4Tubs("csvacuum1", 0.5*csvacID1, 0.5*csvacOD1,
				   0.5*csvacHeight1, 0.0*deg, 360.0*deg);
  //  G4RotationMatrix rotTube4;
  //	rotTube4.rotateY(90*deg);

  G4LogicalVolume* csvacuum1_log = new G4LogicalVolume(csvacuum1,Vacuum,"csvacuum1_log");

  G4VisAttributes* csvacuum1_vis = new G4VisAttributes(yellow);
  csvacuum1_vis->SetVisibility(false);
  csvacuum1_vis->SetForceSolid(false);
  csvacuum1_log->SetVisAttributes(csvacuum1_vis);

  G4double csvacPos1_x = 0.0*cm;
  G4double csvacPos1_y = 0.0*cm;
  G4double csvacPos1_z = 0.0*cm;

  csvacuum1_phys = 
       new G4PVPlacement(0,G4ThreeVector(csvacPos1_x,csvacPos1_y,csvacPos1_z),
                         csvacuum1_log,"csvacuum1_phys",cold_stick_cover1_log,false,0, true);

//---------------------------------cold stick vacuum 2 (in the second lead box)
  
  G4double csvacID2 = 0.0*cm;
  G4double csvacOD2 = 2.8*cm;
  G4double csvacHeight2 = (5-0.00002)*cm;

  G4Tubs* csvacuum2 = new G4Tubs("csvacuum2", 0.5*csvacID2, 0.5*csvacOD2,
				   0.5*csvacHeight2, 0.0*deg, 360.0*deg);
  //  G4RotationMatrix rotTube4;
  //	rotTube4.rotateY(90*deg);

  G4LogicalVolume* csvacuum2_log = new G4LogicalVolume(csvacuum2,Vacuum,"csvacuum2_log");

  G4VisAttributes* csvacuum2_vis = new G4VisAttributes(yellow);
  csvacuum2_vis->SetVisibility(false);
  csvacuum2_vis->SetForceSolid(false);
  csvacuum2_log->SetVisAttributes(csvacuum2_vis);

  G4double csvacPos2_x = 0.0*cm;
  G4double csvacPos2_y = 0.0*cm;
  G4double csvacPos2_z = 0.0*cm;

  csvacuum2_phys = 
       new G4PVPlacement(0,G4ThreeVector(csvacPos2_x,csvacPos2_y,csvacPos2_z),
                         csvacuum2_log,"csvacuum2_phys",cold_stick_cover2_log,false,0, true);
						 
//----------------------------------cold stick vacuum 3 (in the copper box)
  
  G4double csvacID3 = 0.0*cm;
  G4double csvacOD3 = 2.8*cm;
  G4double csvacHeight3 = (5-0.00002)*cm;

  G4Tubs* csvacuum3 = new G4Tubs("csvacuum3", 0.5*csvacID3, 0.5*csvacOD3,
				   0.5*csvacHeight3, 0.0*deg, 360.0*deg);
  //  G4RotationMatrix rotTube4;
  //	rotTube4.rotateY(90*deg);

  G4LogicalVolume* csvacuum3_log = new G4LogicalVolume(csvacuum3,Vacuum,"csvacuum3_log");

  G4VisAttributes* csvacuum3_vis = new G4VisAttributes(yellow);
  csvacuum3_vis->SetVisibility(false);
  csvacuum3_vis->SetForceSolid(false);
  csvacuum3_log->SetVisAttributes(csvacuum3_vis);

  G4double csvacPos3_x = 0.0*cm;
  G4double csvacPos3_y = 0.0*cm;
  G4double csvacPos3_z = 0.0*cm;

  csvacuum3_phys = 
       new G4PVPlacement(0,G4ThreeVector(csvacPos3_x,csvacPos3_y,csvacPos3_z),
                         csvacuum3_log,"csvacuum3_phys",cold_stick_cover3_log,false,0, true);


//--------------------------------cold stick vacuum 4 (inner cavity)
  
  G4double csvacID4 = 0.0*cm;
  G4double csvacOD4 = 2.8*cm;
  G4double csvacHeight4 = (6.15-0.00002)*cm;

  G4Tubs* csvacuum4 = new G4Tubs("csvacuum4", 0.5*csvacID4, 0.5*csvacOD4,
				   0.5*csvacHeight4, 0.0*deg, 360.0*deg);
  //  G4RotationMatrix rotTube4;
  //	rotTube4.rotateY(90*deg);

  G4LogicalVolume* csvacuum4_log = new G4LogicalVolume(csvacuum4,Vacuum,"csvacuum4_log");

  G4VisAttributes* csvacuum4_vis = new G4VisAttributes(yellow);
  csvacuum4_vis->SetVisibility(false);
  csvacuum4_vis->SetForceSolid(false);
  csvacuum4_log->SetVisAttributes(csvacuum4_vis);

  G4double csvacPos4_x = 0.0*cm;
  G4double csvacPos4_y = 0.0*cm;
  G4double csvacPos4_z = 0.0*cm;

  csvacuum4_phys = 
       new G4PVPlacement(0,G4ThreeVector(csvacPos4_x,csvacPos4_y,csvacPos4_z),
                         csvacuum4_log,"csvacuum1_phys",cold_stick_cover4_log,false,0, true);


//------------------------------------cold stick 1 (lead box 75 Bq/kg)
  G4double stick1_ID = 0.0*cm;
  G4double stick1_OD= 1.9*cm;
  G4double stick1_Height = (15.0-0.00003)*cm;  //3-13-06

  G4Tubs* Stick1 = new G4Tubs("Stick1", 0.5*stick1_ID, 0.5*stick1_OD,
				   0.5*stick1_Height, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick1_log = new G4LogicalVolume(Stick1,Cu,"stick1_log");

  G4VisAttributes* stick1_vis = new G4VisAttributes(purple);
  stick1_vis->SetVisibility(false);
  stick1_vis->SetForceSolid(false);
  stick1_log->SetVisAttributes(stick1_vis);

  G4double stick1_Pos_x = 0.0*cm;
  G4double stick1_Pos_y = 0.0*cm;
  G4double stick1_Pos_z = 0.0*cm;

  stick1_phys = 
    new G4PVPlacement(0,G4ThreeVector(stick1_Pos_x,stick1_Pos_y,stick1_Pos_z),
                         stick1_log,"stick1_phys",csvacuum1_log,false,0, true);

/*
//-------------------------------------------------cold stick 4 (lead 3)
  G4double stickID3 = 0.0*cm;
  G4double stickOD3= 1.9*cm;
  G4double stickHeight3 = (5.0-0.00003)*cm;  //3-13-06

  G4Tubs* Stick3 = new G4Tubs("Stick3", 0.5*stickID3, 0.5*stickOD3,
				   0.5*stickHeight3, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick3_log = new G4LogicalVolume(Stick3,Cu,"stick3_log");

  G4VisAttributes* stick3_vis = new G4VisAttributes(purple);
  stick3_vis->SetVisibility(false);
  stick3_vis->SetForceSolid(false);
  stick3_log->SetVisAttributes(stick3_vis);

  G4double stickPos3_x = 0.0*cm;
  G4double stickPos3_y = 0.0*cm;
  G4double stickPos3_z = 0.0*cm;

  stick4_phys = 
    new G4PVPlacement(0,G4ThreeVector(stickPos3_x,stickPos3_y,stickPos3_z),
                         stick3_log,"stick4_phys",csvacuum2_log,false,0, true);


//-------------------------------------------------cold stick 4 (lead 2)
  G4double stickID2 = 0.0*cm;
  G4double stickOD2= 1.9*cm;
  G4double stickHeight2 = (5.0-0.00003)*cm;  //3-13-06

  G4Tubs* Stick2 = new G4Tubs("Stick2", 0.5*stickID2, 0.5*stickOD2,
				   0.5*stickHeight2, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick2_log = new G4LogicalVolume(Stick2,Cu,"stick2_log");

  G4VisAttributes* stick2_vis = new G4VisAttributes(purple);
  stick2_vis->SetVisibility(false);
  stick2_vis->SetForceSolid(false);
  stick2_log->SetVisAttributes(stick2_vis);

  G4double stickPos2_x = 0.0*cm;
  G4double stickPos2_y = 0.0*cm;
  G4double stickPos2_z = 0.0*cm;

  stick4_phys = 
    new G4PVPlacement(0,G4ThreeVector(stickPos2_x,stickPos2_y,stickPos2_z),
                         stick2_log,"stick4_phys",csvacuum3_log,false,0, true);

*/
//-------------------------------------------------cold stick 2 (lead box 3 Bq/kg)
  G4double stick2_ID = 0.0*cm;
  G4double stick2_OD = 1.9*cm;
  G4double stick2_Height = (5.0-0.00003)*cm;  //3-13-06

  G4Tubs* Stick2 = new G4Tubs("Stick2", 0.5*stick2_ID, 0.5*stick2_OD,
				   0.5*stick2_Height, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick2_log = new G4LogicalVolume(Stick2,Cu,"stick2_log");

  G4VisAttributes* stick2_vis = new G4VisAttributes(purple);
  stick2_vis->SetVisibility(false);
  stick2_vis->SetForceSolid(false);
  stick2_log->SetVisAttributes(stick2_vis);

  G4double stick2_Pos_x = 0.0*cm;
  G4double stick2_Pos_y = 0.0*cm;
  G4double stick2_Pos_z = 0.0*cm;

  stick2_phys = 
    new G4PVPlacement(0,G4ThreeVector(stick2_Pos_x,stick2_Pos_y,stick2_Pos_z),
                         stick2_log,"stick2_phys",csvacuum2_log,false,0, true);


//-------------------------------------------------cold stick 3 (copper box)
  G4double stick3_ID = 0.0*cm;
  G4double stick3_OD= 1.9*cm;
  G4double stick3_Height = (5.0-0.00003)*cm;  //3-13-06

  G4Tubs* Stick3 = new G4Tubs("Stick3", 0.5*stick3_ID, 0.5*stick3_OD,
				   0.5*stick3_Height, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick3_log = new G4LogicalVolume(Stick3,Cu,"stick3_log");

  G4VisAttributes* stick3_vis = new G4VisAttributes(purple);
  stick3_vis->SetVisibility(false);
  stick3_vis->SetForceSolid(false);
  stick3_log->SetVisAttributes(stick3_vis);

  G4double stick3_Pos_x = 0.0*cm;
  G4double stick3_Pos_y = 0.0*cm;
  G4double stick3_Pos_z = 0.0*cm;

  stick3_phys = 
    new G4PVPlacement(0,G4ThreeVector(stick3_Pos_x,stick3_Pos_y,stick3_Pos_z),
                         stick3_log,"stick3_phys",csvacuum3_log,false,0, true);


//-------------------------------------------------cold stick 4 (inner cavity)
  G4double stick4_ID = 0.0*cm;
  G4double stick4_OD= 1.9*cm;
  G4double stick4_Height = (6.15-0.00003)*cm;  //3-13-06

  G4Tubs* Stick4 = new G4Tubs("Stick4", 0.5*stick4_ID, 0.5*stick4_OD,
				   0.5*stick4_Height, 0.0*deg, 360.0*deg);
  //G4RotationMatrix rotStick4;
  //	rotStick4.rotateY(90*deg);

  G4LogicalVolume* stick4_log = new G4LogicalVolume(Stick4,Cu,"stick4_log");

  G4VisAttributes* stick4_vis = new G4VisAttributes(purple);
  stick4_vis->SetVisibility(false);
  stick4_vis->SetForceSolid(false);
  stick4_log->SetVisAttributes(stick4_vis);

  G4double stick4_Pos_x = 0.0*cm;
  G4double stick4_Pos_y = 0.0*cm;
  G4double stick4_Pos_z = 0.0*cm;

  stick4_phys = 
    new G4PVPlacement(0,G4ThreeVector(stick4_Pos_x,stick4_Pos_y,stick4_Pos_z),
                         stick4_log,"stick4_phys",csvacuum4_log,false,0, true);



//----------------------- Overlap check --------------------------//
/*void Xenon1tDetectorConstruction::CheckOverlapping()
{

    G4cout << "Checking for overlapping... " << G4endl;
    int iOverlapped = 0;
    
    G4int res = 100000;
    G4bool verbose = true;


	 G4cout << "No overlaps in:" << G4endl;     
     iOverlapped +=  lead_box_3Bqkg_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lead_box_75Bqkg_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lab_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lead_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lead4_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lead3_phys->CheckOverlaps(res, 0, verbose);   
     iOverlapped +=  lead2_phys->CheckOverlaps(res, 0, verbose);   
	 iOverlapped +=  copper_box_phys->CheckOverlaps(res, 0, verbose);   
	 iOverlapped +=  copper_top_phys->CheckOverlaps(res, 0, verbose);   
	 iOverlapped +=  lead_top_3Bqkg_phys->CheckOverlaps(res, 0, verbose);
	iOverlapped +=  lead_top_75Bqkg_phys->CheckOverlaps(res, 0, verbose);   
	iOverlapped +=  lead6_phys->CheckOverlaps(res, 0, verbose);   
    iOverlapped +=  oldlead_phys->CheckOverlaps(res, 0, verbose);  
    iOverlapped +=  leadlayer_phys->CheckOverlaps(res, 0, verbose);  
    iOverlapped +=  cavity1_phys->CheckOverlaps(res, 0, verbose);  
     iOverlapped +=  copper_layer_phys->CheckOverlaps(res, 0, verbose);  
     iOverlapped +=  cavity2_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  endcap_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  vacuum_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  holder_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  innervac_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  plug_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  innervac3_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  cover_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  innervac2_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  crystal_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  crystalhole_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  crystalgroove_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  active_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  mylar_phys->CheckOverlaps(res, 0, verbose);
     iOverlapped +=  kapton_phys->CheckOverlaps(res, 0, verbose);
	iOverlapped +=  contact1_phys->CheckOverlaps(res, 0, verbose);
	iOverlapped +=  contact2_phys->CheckOverlaps(res, 0, verbose);
	iOverlapped +=  contact3_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  base_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  lower_vacuum_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  holder2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  holder2vac_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  tube1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cold_stick_cover1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cold_stick_cover2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cold_stick_cover3_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cold_stick_cover4_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  csvacuum1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  csvacuum2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  csvacuum3_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  csvacuum4_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  stick1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  stick2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  stick3_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  stick4_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  stick5_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  test_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  pmt1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  pmt2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  pmt3_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  pmt4_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  poly_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cirlex_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  lead_gap_top_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  lead_gap_mid_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  lead_gap_bot_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  feedthrough_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  teflonarcs_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cdms_pb1_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cdms_pb2_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cdms_pb1_inside_phys->CheckOverlaps(res, 0, verbose);
   iOverlapped +=  cdms_pb2_inside_phys->CheckOverlaps(res, 0, verbose);
	
	
      
     G4cout << "Done." << G4endl << G4endl;
	 assert(iOverlapped==0); 
	 	 
}	 
*/

// oooOOOooo......oooOOOooo......oooOOOooo.......oooOOOooo.......oooOOOooo.......oooOOOooo


//----------------------- Include here the Geometry of the sample --------------------------//

//Some coordinates for the placement of the samples:
// - The cavity floor z absolute coordinate is -3.0 cm
// - The endcap volume center z coordinate (respect to the cavity axis origin) is -4.4125 cm;
// - The endcap top-surface z coordinate (respect to the cavity axis origin) is 2.04 cm;
// - The minimum height of a brick placed in the floor to make an holding castle structure is 18.54 cm;
// - The gap from the endcap-top and the cavity "ceiling" is 14.46 cm;
// - The endcap volume center absolute z coordinate is 9.0875 cm;
// - The endcap top-surface absolute z coordinate is 15.54 cm;
						 
#include "includesample.hh"
return lab_phys;

}

//oooOOOooo......oooOOOooo......oooOOOooo.......oooOOOooo.......oooOOOooo.......oooOOOooo

void GeConstruction::SecondOverlapCheck()
{
  G4PhysicalVolumeStore *thePVStore = G4PhysicalVolumeStore::GetInstance();		// viene istanziato un puntatore
  // della classe G4PhysicalVolumeStore
  G4cout << "\n" << "******************************" << G4endl;
  G4cout << "\n" << "CHECK FOR OVERLAPS" << G4endl;
  G4cout << "\n" << "******************************" << G4endl;
  G4cout <<"\n" << G4endl;
  
  G4cout << thePVStore->size() << " physical volumes are defined" << G4endl;
  G4bool overlapFlag = true;	   // la variabile booleana overlapFlag
                                   // e' inizializzata a "falso"
  
  for (size_t i=0; i<thePVStore->size();i++) {		   
    overlapFlag = (*thePVStore)[i]->CheckOverlaps(5000) | overlapFlag;		
	}

}


