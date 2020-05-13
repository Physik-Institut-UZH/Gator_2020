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


G4LogicalVolume* GeConstruction::ConstructPmtR11410(){
	
	//Colors for visualization properties
	G4Colour red (1.0, 0.0, 0.0);
	G4Colour blue (0.0, 0.0, 1.0);
	G4Colour yellow (1.0, 1.0, 0.0);
	G4Colour orange (0.75, 0.55, 0.0);
	G4Colour lblue (0.0, 0.0, 0.55);
	
	
	//Elements and materials usefull
	G4Element* O = G4Element::GetElement("Oxygen");
	G4Element* Si = G4Element::GetElement("Silicon");
	G4Element* Al = G4Element::GetElement("Aluminum");
	G4Element* Ni = G4Element::GetElement("Nickel");
	
	G4Material* Steel_304 = G4Material::GetMaterial("Steel_304");
	
	G4Material *kovar = G4Material::GetMaterial("PMTkovar_mat");
	
	//Define the pmt envelope as a polycon with 4 z-surfaces (maybe more z-surfaces is better)
	const G4double PMTOD_ext_bot = 76 * mm;
	const G4double PMTOD_ext_top = 53 * mm;
	const G4double PMT_h1 = 30 * mm;
	const G4double PMT_h2 = 13 * mm;
	const G4double PMT_h3 = 71 * mm;
	
	G4double PMT_envel_IRads[] = {0,0,0,0};
	G4double PMT_envel_ORads[] = {PMTOD_ext_bot/2.,PMTOD_ext_bot/2.,PMTOD_ext_top/2.,PMTOD_ext_top/2.};
	G4double PMT_envel_zPlanes[] = {0, PMT_h1, PMT_h1+PMT_h2, PMT_h1+PMT_h2+PMT_h3};
	
	G4Polycone* PMT_envel = new G4Polycone("PMT_envel", 0, 360*deg, 4, PMT_envel_zPlanes, PMT_envel_IRads, PMT_envel_ORads);
	
	//Envelope material definition (SS)
	G4Material* PMT_steel = new G4Material("PMT_steel",8.03*g/cm3,1);
	PMT_steel -> AddMaterial(Steel_304,1.0); //Just a trick to change the name of the steel ==> I can use the routine to generate the random points in the proper material
	
	//Envelope Logical volume
    G4LogicalVolume* PMT_envel_log = new G4LogicalVolume(PMT_envel, kovar, "PMT_envel_log", 0, 0, 0);
	
	G4VisAttributes* PMT_envel_vis = new G4VisAttributes(red);
	PMT_envel_vis -> SetVisibility(true);
	PMT_envel_vis -> SetForceSolid(false);
	PMT_envel_log -> SetVisAttributes(PMT_envel_vis);
	
	
	/******************************** Definition of the vacuum inside the PMTs *************************************/
	//Define the pmt vacuum as a polycon with 5 z-surfaces (maybe more z-surfaces is better)
	const G4double PMT_thickness = 0.8 * mm; //With this thickness the mass of the envelope is optimized to 101 g about (it fluctuates from run to run)
	
	const G4double PMTOD_int_bot = PMTOD_ext_bot - PMT_thickness;
	const G4double PMTOD_int_top = PMTOD_ext_top - PMT_thickness;
	const G4double PMTceram_OD = 35.*mm; //Put it before the definition of the ceramic
	const G4double PMTceram_ID = 0.*mm;
	//const G4double PMT_h1 = 30 * mm;
	//const G4double PMT_h2 = 13 * mm;
	//const G4double PMT_h3 = 71 * mm;
	
	G4double PMT_vacuum_IRads[] = {0,0,0,0};
	G4double PMT_vacuum_ORads[] = {PMTOD_int_bot/2., PMTOD_int_bot/2., PMTOD_int_top/2., PMTOD_int_top/2.};
	G4double PMT_vacuum_zPlanes[] = {0, PMT_h1, PMT_h1+PMT_h2, (PMT_h1+PMT_h2+PMT_h3)-PMT_thickness};
	
	G4Polycone* PMT_vacuum_poly = new G4Polycone("vacuum_PMT_poly", 0, 360*deg, 4, PMT_vacuum_zPlanes, PMT_vacuum_IRads, PMT_vacuum_ORads);
	G4Tubs* PMT_vacuum_tubs = new G4Tubs("vacuum_PMT_tubs",0.5*PMTceram_ID,0.5*PMTceram_OD,PMT_thickness,0.*deg,360.*deg);
	G4UnionSolid* PMT_vacuum = new G4UnionSolid("vacuum_PMT",PMT_vacuum_poly,PMT_vacuum_tubs,0,G4ThreeVector(0.,0.,PMT_h1+PMT_h2+PMT_h3-PMT_thickness));
	
	//Material definition for the vacuum inside the PMT
	G4Material* PMT_vacuum_mat = new G4Material("vacuum_PMT_mat",1.,1.*g/mole,1.e-20*g/cm3,kStateGas,0.1*kelvin,1.e-20*bar);
	
	
	//Vacuum Logical volume
	G4LogicalVolume* PMT_vacuum_log = new G4LogicalVolume(PMT_vacuum, PMT_vacuum_mat, "vacuum_PMT_log", 0, 0, 0);
	
	G4VisAttributes* PMT_vacuum_vis = new G4VisAttributes(yellow);
	PMT_vacuum_vis -> SetVisibility(true);
	PMT_vacuum_vis -> SetForceSolid(false);
	PMT_vacuum_log -> SetVisAttributes(G4VisAttributes::Invisible);
	
	
	//Placement of the vacuum logical volume inside the PMT envelope volume
	G4ThreeVector PTM_vacuum_pos(0.,0.,0.);
	
	G4VPhysicalVolume* PMT_vacuum_phys = new G4PVPlacement(0,PTM_vacuum_pos,PMT_vacuum_log,"vacuum_PMT_phys", PMT_envel_log, false, 0,true);
	
	
	
	
	/******************************** Definition of the ceramic stem to put in PMTs *************************************/
	//Material definition for the ceramic inside the pmt
	G4Material* PMT_ceram_mat = new G4Material("PMT_ceram_mat",2.811*g/cm3,2);
	PMT_ceram_mat -> AddElement(Al,2);
	PMT_ceram_mat -> AddElement(O,3);
	
	
	//Dimension of each cilinder
	//G4double PMTceram_ID = 0.*mm;
	//G4double PMTceram_OD = 35.*mm;
	G4double PMTceram_H = 5.916*mm;
	
	
	//Definition of the geometry
	G4Tubs* PMT_ceram = new G4Tubs("PMT_ceram",0.5*PMTceram_ID,0.5*PMTceram_OD,0.5*PMTceram_H,0.*deg,360.*deg);
	
	
	//Construction of logical volume
	G4LogicalVolume* PMT_ceram_log = new G4LogicalVolume(PMT_ceram,PMT_ceram_mat,"PMT_ceram_log");
	
	
	// Set visibility properties
	G4VisAttributes* PMT_ceram_vis = new G4VisAttributes(orange);
	PMT_ceram_vis -> SetVisibility(true);
	PMT_ceram_vis -> SetForceSolid(false);
	PMT_ceram_log -> SetVisAttributes(PMT_ceram_vis);
	
	
	// Put the ceramic stem in the PMT_envelop logical volume
	G4ThreeVector PMT_ceram_shift(0.,0.,(PMT_h1+PMT_h2+PMT_h3)-(PMTceram_H/2.));
	
	G4VPhysicalVolume* PMT_ceram_phys = new G4PVPlacement(0,PMT_ceram_shift,PMT_ceram_log,"PMT_ceram_phys",PMT_vacuum_log,false,0,true);
	
	
	
	
	/********************* Definition of the quartz window as a flat thin cilinder inside the PMTs vacuum ********************/
	//Material definition for the ceramic inside the pmt
	G4Material* PMT_quartz_mat = new G4Material("PMT_quartz_mat",2.648*g/cm3,2);
	PMT_quartz_mat -> AddElement(Si,1);
	PMT_quartz_mat -> AddElement(O,2);
	
	
	//Dimension of each cilinder
	G4double PMTwindow_ID = 0.*mm;
	G4double PMTwindow_OD = 70.5*mm;
	G4double PMTwindow_H = 3.1*mm;
	
	
	//Definition of the geometry
	G4Tubs* PMT_window = new G4Tubs("PMT_window",0.5*PMTwindow_ID,0.5*PMTwindow_OD,0.5*PMTwindow_H,0.*deg,360.*deg);
	
	
	//Construction of logical volume
	G4LogicalVolume* PMT_window_log = new G4LogicalVolume(PMT_window,PMT_quartz_mat,"PMT_window_log");
	
	
	// Set visibility properties
	G4VisAttributes* PMT_window_vis = new G4VisAttributes(blue);
	PMT_window_vis -> SetVisibility(true);
	PMT_window_vis -> SetForceSolid(false);
	PMT_window_log -> SetVisAttributes(PMT_window_vis);
	
	
	// Put the ceramic stem in the PMT_envelop logical volume
	G4ThreeVector PMT_window_shift(0.,0.,PMTwindow_H/2.);
	
	G4VPhysicalVolume* PMT_window_phys = new G4PVPlacement(0,PMT_window_shift,PMT_window_log,"PMT_window_phys",PMT_vacuum_log,false,0,true);
	
	
	
	
	/********************* Definition of the stuff inside a cilinder inside the PMTs vacuum ********************/
	//Dimension of the cilinder and mass of the internal cylinder
	G4double PMTinternal_ID = 0.*mm;
	G4double PMTinternal_OD = 35.0*mm;
	G4double PMTinternal_H = 35.0*mm;
	G4double PMTinternal_mass = 33.8*g;
	
	G4double PMTinternal_dens = PMTinternal_mass/(TMath::Pi()*pow(PMTinternal_OD/2,2)*PMTinternal_H);
	
	//Material definition as a mesh respecting the mass model
	G4double mfrac_SiO2 = 0.426; //This is for quartz
	G4double mfrac_SS304 = 1.-mfrac_SiO2; //This for some electrodes
	//G4double mfrac_Ni = 1.-(mfrac_SiO2+mfrac_SS304);
	
	
	G4Material* PMT_nickel_mat = new G4Material("PMT_nickel_mat",8.908*g/cm3,1);
	PMT_nickel_mat -> AddElement(Ni,1);
	
	G4Material* PMT_internal_mat = new G4Material("PMT_internal_mat",1.014*g/cm3,2);
	PMT_internal_mat -> AddMaterial(PMT_quartz_mat,mfrac_SiO2);
	PMT_internal_mat -> AddMaterial(Steel_304,mfrac_SS304);
	//PMT_internal_mat -> AddMaterial(PMT_nickel_mat,mfrac_Ni);
	
	
	//Definition of the geometry
	G4Tubs* PMT_internal = new G4Tubs("PMT_internal",0.5*PMTinternal_ID,0.5*PMTinternal_OD,0.5*PMTinternal_H,0.*deg,360.*deg);
	
	
	//Contruction of logical volume
	G4LogicalVolume* PMT_internal_log = new G4LogicalVolume(PMT_internal,PMT_internal_mat,"PMT_internal_log");
	
	
	// Set visibility properties
	G4VisAttributes* PMT_internal_vis = new G4VisAttributes(lblue);
	PMT_internal_vis -> SetVisibility(true);
	PMT_internal_vis -> SetForceSolid(false);
	PMT_internal_log -> SetVisAttributes(PMT_internal_vis);
	
	
	// Put the ceramic stem in the PMT_envelop logical volume
	G4ThreeVector PMT_internal_shift(0.,0.,(PMT_h1+PMT_h2+PMT_h3)-(PMTinternal_H/2.)-(PMTceram_H+1.*cm));
	
	G4VPhysicalVolume* PMT_internal_phys = new G4PVPlacement(0,PMT_internal_shift,PMT_internal_log,"PMT_internal_phys",PMT_vacuum_log,false,0,true);
	
	
	
	/********************* Definition of the kovar front flange the PMTs ********************/
	//Code this like a ring inside the first bottom segmant of the PMT (from the photocathode window)
	
	//Define the fron flange dimensions
	G4double PMT_frontflange_OD = PMTOD_ext_bot;
	G4double PMT_frontflange_ID = PMT_frontflange_OD-PMT_thickness;
	G4double PMT_frontflange_H = PMT_h1;
	
	
	//Definition of the geometry
	G4Tubs* PMT_frontflange = new G4Tubs("PMT_frontflange", 0.5*PMT_frontflange_ID, 0.5*PMT_frontflange_OD, 0.5*PMT_frontflange_H, 0.*deg, 360.*deg);
	
	
	//Construction of the logical volume
	G4LogicalVolume* PMT_frontflange_log = new G4LogicalVolume(PMT_frontflange,kovar,"PMT_frontflange_log");
	
	
	// Set visibility properties
	G4VisAttributes* PMT_frontflange_vis = new G4VisAttributes(lblue);
	PMT_frontflange_vis -> SetVisibility(true);
	PMT_frontflange_vis -> SetForceSolid(false);
	PMT_frontflange_log -> SetVisAttributes(PMT_frontflange_vis);
	
	
	//consider that the mother volume (the envelope) has z=0 at the surface level of the quartz window
	G4ThreeVector PMT_frontflange_shift(0., 0., PMT_frontflange_H/2.);
	
	
	G4VPhysicalVolume* PMT_frontflange_phys = new G4PVPlacement(0,PMT_frontflange_shift,PMT_frontflange_log,"PMT_frontflange_phys",PMT_envel_log,false,0,true);
	
	
	
	/********************* Definition of the kovar back flange of the PMTs ********************/
	//This will be a ring with an internal radius the same as the ceramic external radius
	
	G4double PMT_backflange_OD = PMTOD_ext_top;
	G4double PMT_backflange_ID = PMTceram_OD;
	G4double PMT_backflange_H = PMT_thickness;
	
	
	//Definition of the geometry
	G4Tubs* PMT_backflange = new G4Tubs("PMT_backflange",  0.5*PMT_backflange_ID, 0.5*PMT_backflange_OD, 0.5*PMT_backflange_H, 0.*deg, 360.*deg);
	
	
	//Construction of the logical volume
	G4LogicalVolume* PMT_backflange_log = new G4LogicalVolume(PMT_backflange,kovar,"PMT_backflange_log");
	
	
	// Set visibility properties
	G4VisAttributes* PMT_backflange_vis = new G4VisAttributes(lblue);
	PMT_backflange_vis -> SetVisibility(true);
	PMT_backflange_vis -> SetForceSolid(false);
	PMT_backflange_log -> SetVisAttributes(PMT_backflange_vis);
	
	
	//Consider that the mother volume (the envelope) has z=0 at the surface level of the quartz window
	G4ThreeVector PMT_backflange_shift(0., 0., (PMT_h1+PMT_h2+PMT_h3)-PMT_backflange_H/2.);
	
	
	G4VPhysicalVolume* PMT_backflange_phys = new G4PVPlacement(0,PMT_backflange_shift,PMT_backflange_log,"PMT_backflange_phys",PMT_envel_log,false,0,true);
	
	return PMT_envel_log;

}
