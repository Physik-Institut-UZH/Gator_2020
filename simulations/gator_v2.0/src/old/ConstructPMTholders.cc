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


G4LogicalVolume* GeConstruction::ConstructPMTholder_long(){
	
	//G4int HolesNum=4;
	
	//General geometrical parameters (relevant)
	G4double HolesOffset=43*mm;
	G4double HoleSpacing=80*mm; //Distance between the hole centers
	G4double PanelsZ=326*mm; //Height of the frontal and back panels
	
	G4ThreeVector FirstHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ);
	G4ThreeVector SecondHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ+HoleSpacing);
	G4ThreeVector ThirdHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ+2*HoleSpacing);
	G4ThreeVector FourthHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ+3*HoleSpacing);
	G4RotationMatrix* HolesRotation = new G4RotationMatrix();
	HolesRotation->rotateX(90*deg);

	
	//Frontal mask
	G4double FrontX=100*mm; //The width
	G4double FrontY=8*mm; //The thickness
	G4double FrontHolesDiam=77.25*mm;
	
	
	G4Box* FrontPlate = new G4Box("FrontPlate",0.5*FrontX,0.5*FrontY,0.5*PanelsZ);
	G4Tubs* FrontHole = new G4Tubs("FrontHoleCyl",0.0*mm,0.5*FrontHolesDiam,5*mm,0.*deg,360.*deg);
	
	
	G4SubtractionSolid* FrontMask_1H = new G4SubtractionSolid("FrontMask_1H",FrontPlate,FrontHole,HolesRotation,FirstHoleOffset);
	G4SubtractionSolid* FrontMask_2H = new G4SubtractionSolid("FrontMask_2H",FrontMask_1H,FrontHole,HolesRotation,SecondHoleOffset);
	G4SubtractionSolid* FrontMask_3H = new G4SubtractionSolid("FrontMask_3H",FrontMask_2H,FrontHole,HolesRotation,ThirdHoleOffset);
	G4SubtractionSolid* FrontMask_4H = new G4SubtractionSolid("FrontMask_4H",FrontMask_3H,FrontHole,HolesRotation,FourthHoleOffset);
	
	
	//Back mask
	G4double BackX=58*mm; //The width
	G4double BackY=8*mm; //The thickness, changed from 5 to 8, 2018
	G4double BackRingID=54.5*mm;
	G4double BackRingOD=60.5*mm;
	G4double BackGrooveX=42*mm;
	G4double BackGrooveY=6*mm;
	G4double BackGrooveZ=HoleSpacing-BackRingID;
	
	G4Box* BackPlate = new G4Box("BackPlate",0.5*BackX,0.5*BackY,0.5*PanelsZ);
	G4Box* BackGroove_0 = new	G4Box("BackGroove_0",0.5*BackGrooveX,0.5*BackGrooveY,0.5*BackGrooveZ);
	G4Tubs* GrooveCleaner = new G4Tubs("GrooveCleaner",0.*mm,0.5*BackRingOD,0.5*(BackGrooveY+0.1),0.*deg,360.*deg);
	G4Tubs* BackHole = new G4Tubs("BackHole",0.*mm,0.5*BackRingID,0.5*BackGrooveY,0.*deg,360.*deg); //6mm thick is enough
	
	
	G4SubtractionSolid* BackGroove_1 = new	G4SubtractionSolid("BackGroove_1",BackGroove_0,GrooveCleaner,HolesRotation,G4ThreeVector(0.,0.,0.5*HoleSpacing));
	G4SubtractionSolid* BackGroove = new	G4SubtractionSolid("BackGroove",BackGroove_1,GrooveCleaner,HolesRotation,G4ThreeVector(0.,0.,-0.5*HoleSpacing));
	G4SubtractionSolid* BackMask_1hole = new G4SubtractionSolid("BackMask_1hole",BackPlate,BackHole,HolesRotation,FirstHoleOffset);
	G4SubtractionSolid* BackMask_2hole = new G4SubtractionSolid("BackMask_2hole",BackMask_1hole,BackHole,HolesRotation,SecondHoleOffset);
	G4SubtractionSolid* BackMask_3hole = new G4SubtractionSolid("BackMask_3hole",BackMask_2hole,BackHole,HolesRotation,ThirdHoleOffset);
	G4SubtractionSolid* BackMask_4hole = new G4SubtractionSolid("BackMask_4hole",BackMask_3hole,BackHole,HolesRotation,FourthHoleOffset);
	G4SubtractionSolid* BackMaskWithGroove1 = new G4SubtractionSolid("BackMaskWithGroove1",BackMask_4hole,BackGroove,0,0.5*(FirstHoleOffset+SecondHoleOffset));
	G4SubtractionSolid* BackMaskWithGroove2 = new G4SubtractionSolid("BackMaskWithGroove2",BackMaskWithGroove1,BackGroove,0,0.5*(SecondHoleOffset+ThirdHoleOffset));
	G4SubtractionSolid* BackMask = new G4SubtractionSolid("BackMask",BackMaskWithGroove2,BackGroove,0,0.5*(ThirdHoleOffset+FourthHoleOffset));
	
	
	//Lateral Frames 
	G4double FramesX_max=FrontX,FramesX_min=55*mm; //Max and min width
	G4double FramesY=78*mm; //The distance beween the two plates (a bit shorter than PMTs)
	G4double FramesZ=10*mm; //Their thickness
	// changed LatPlateHoleY from 60 to 57, due to 3 mm increase in back plate thickness, 2018
	G4double LatPlateHoleX=35*mm, LatPlateHoleY=57*mm, LatPlateHoleZ=12*mm;
	G4double LatFrameFootX=32.5, LatFrameFootY=10*mm, LatFrameFootZ=FramesZ;
	
	G4Box* LatPlate = new G4Box("LatPlate",0.5*FramesX_min,0.5*FramesY,0.5*FramesZ);
	G4Box* LatPlateHole = new G4Box("LatPlateHole",0.5*LatPlateHoleX,0.5*LatPlateHoleY,0.5*LatPlateHoleZ);
	G4Box* LatFrameFoot = new G4Box("LatFrameFoot",0.5*LatFrameFootX,0.5*LatFrameFootY,0.5*LatFrameFootZ);
	
	
	G4ThreeVector LatPlateHoleOffset(0.*mm,1.*mm,0.*mm);
	G4SubtractionSolid* LatFrame_A = new G4SubtractionSolid("LatFram_A",LatPlate,LatPlateHole,0,LatPlateHoleOffset);
	
	G4ThreeVector LatPlateFootOffsetA(0.5*(FramesX_min+LatFrameFootX)-10.*mm,-0.5*(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* LatFrame_B = new G4UnionSolid("LatFrame_B",LatFrame_A,LatFrameFoot,0,LatPlateFootOffsetA);
	
	G4ThreeVector LatPlateFootOffsetB(-0.5*(FramesX_min+LatFrameFootX)+10.*mm,-0.5*(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* LatFrame = new G4UnionSolid("LatFrame",LatFrame_B,LatFrameFoot,0,LatPlateFootOffsetB);
	
	
	//Try to put everything together
	G4ThreeVector LatFrameOffsetA(0.*mm,0.5*(FrontY+FramesY)+LatFrameFootY,-0.5*(PanelsZ-FramesZ));
	G4UnionSolid* HoldersA = new G4UnionSolid("HoldersA",FrontMask_4H,LatFrame,0,LatFrameOffsetA);
	
	G4ThreeVector LatFrameOffsetB(0.*mm,0.5*(FrontY+FramesY)+LatFrameFootY,0.5*(PanelsZ-FramesZ));
	G4UnionSolid* HoldersB = new G4UnionSolid("HoldersB",HoldersA,LatFrame,0,LatFrameOffsetB);
	
	G4ThreeVector BackMaskOffset(0.*mm,0.5*(FrontY+BackY)+(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* LongHolder = new G4UnionSolid("LongHolder",HoldersB,BackMask,0,BackMaskOffset);
	
	G4Material* Teflon = G4Material::GetMaterial("Teflon");
	G4LogicalVolume* LongHolder_log = new G4LogicalVolume(LongHolder,Teflon,"LongHolder_log");
	
	return LongHolder_log;
	
}

/**************************************************************************************/


G4LogicalVolume* GeConstruction::ConstructPMTholder_short(){
	
	//G4int HolesNum=3;
	
	//General geometrical parameters (relevant)
	G4double HolesOffset=43*mm;
	G4double HoleSpacing=80*mm; //Distance between the hole centers
	G4double PanelsZ=246*mm; //Height of the frontal and back panels
	
	G4ThreeVector FirstHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ);
	G4ThreeVector SecondHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ+HoleSpacing);
	G4ThreeVector ThirdHoleOffset(0.0*mm,0.0*mm,HolesOffset-0.5*PanelsZ+2*HoleSpacing);
	G4RotationMatrix* HolesRotation = new G4RotationMatrix();
	HolesRotation->rotateX(90*deg);

	
	//Frontal mask
	G4double FrontX=100*mm; //The width
	G4double FrontY=8*mm; //The thickness
	G4double FrontHolesDiam=77.5*mm; //Actually is 77.25 but I want to avoid overlaps
	
	
	G4Box* FrontPlate = new G4Box("FrontPlate",0.5*FrontX,0.5*FrontY,0.5*PanelsZ);
	G4Tubs* FrontHole = new G4Tubs("FrontHoleCyl",0.0*mm,0.5*FrontHolesDiam,5*mm,0.*deg,360.*deg);
	
	
	G4SubtractionSolid* FrontMask_1H = new G4SubtractionSolid("FrontMask_1H",FrontPlate,FrontHole,HolesRotation,FirstHoleOffset);
	G4SubtractionSolid* FrontMask_2H = new G4SubtractionSolid("FrontMask_2H",FrontMask_1H,FrontHole,HolesRotation,SecondHoleOffset);
	G4SubtractionSolid* FrontMask_3H = new G4SubtractionSolid("FrontMask_3H",FrontMask_2H,FrontHole,HolesRotation,ThirdHoleOffset);
	
	
	
	//Back mask
	G4double BackX=58*mm; //The width
	G4double BackY=5*mm; //The thickness
	G4double BackRingID=54.5*mm;
	G4double BackRingOD=60.5*mm;
	G4double BackGrooveX=42*mm;
	G4double BackGrooveY=6*mm;
	G4double BackGrooveZ=HoleSpacing-BackRingID;
	
	G4Box* BackPlate = new G4Box("BackPlate",0.5*BackX,0.5*BackY,0.5*PanelsZ);
	G4Box* BackGroove_0 = new	G4Box("BackGroove_0",0.5*BackGrooveX,0.5*BackGrooveY,0.5*BackGrooveZ);
	G4Tubs* GrooveCleaner = new G4Tubs("GrooveCleaner",0.*mm,0.5*BackRingOD,0.5*(BackGrooveY+0.1),0.*deg,360.*deg);
	G4Tubs* BackHole = new G4Tubs("BackHole",0.*mm,0.5*BackRingID,0.5*BackGrooveY,0.*deg,360.*deg); //6mm thick is enough
	
	G4SubtractionSolid* BackGroove_1 = new	G4SubtractionSolid("BackGroove_1",BackGroove_0,GrooveCleaner,HolesRotation,G4ThreeVector(0.,0.,0.5*HoleSpacing));
	G4SubtractionSolid* BackGroove = new	G4SubtractionSolid("BackGroove",BackGroove_1,GrooveCleaner,HolesRotation,G4ThreeVector(0.,0.,-0.5*HoleSpacing));
	G4SubtractionSolid* BackMask_1hole = new G4SubtractionSolid("BackMask_1hole",BackPlate,BackHole,HolesRotation,FirstHoleOffset);
	G4SubtractionSolid* BackMask_2hole = new G4SubtractionSolid("BackMask_2hole",BackMask_1hole,BackHole,HolesRotation,SecondHoleOffset);
	G4SubtractionSolid* BackMask_3hole = new G4SubtractionSolid("BackMask_3hole",BackMask_2hole,BackHole,HolesRotation,ThirdHoleOffset);
	G4SubtractionSolid* BackMaskWithGroove1 = new G4SubtractionSolid("BackMaskWithGroove1",BackMask_3hole,BackGroove,0,0.5*(FirstHoleOffset+SecondHoleOffset));
	G4SubtractionSolid* BackMask = new G4SubtractionSolid("BackMask",BackMaskWithGroove1,BackGroove,0,0.5*(SecondHoleOffset+ThirdHoleOffset));
	
	
	//Lateral Frames 
	G4double FramesX_max=FrontX,FramesX_min=55*mm; //Max and min width
	G4double FramesY=78*mm; //The distance beween the two plates (a bit shorter than PMTs)
	G4double FramesZ=10*mm; //Their thickness
	G4double LatPlateHoleX=35*mm, LatPlateHoleY=60*mm, LatPlateHoleZ=12*mm;
	G4double LatFrameFootX=32.5, LatFrameFootY=10*mm, LatFrameFootZ=FramesZ;
	
	G4Box* LatPlate = new G4Box("LatPlate",0.5*FramesX_min,0.5*FramesY,0.5*FramesZ);
	G4Box* LatPlateHole = new G4Box("LatPlateHole",0.5*LatPlateHoleX,0.5*LatPlateHoleY,0.5*LatPlateHoleZ);
	G4Box* LatFrameFoot = new G4Box("LatFrameFoot",0.5*LatFrameFootX,0.5*LatFrameFootY,0.5*LatFrameFootZ);
	
	
	G4ThreeVector LatPlateHoleOffset(0.*mm,1.*mm,0.*mm);
	G4SubtractionSolid* LatFrame_A = new G4SubtractionSolid("LatFram_A",LatPlate,LatPlateHole,0,LatPlateHoleOffset);
	
	G4ThreeVector LatPlateFootOffsetA(0.5*(FramesX_min+LatFrameFootX)-10.*mm,-0.5*(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* LatFrame_B = new G4UnionSolid("LatFrame_B",LatFrame_A,LatFrameFoot,0,LatPlateFootOffsetA);
	
	G4ThreeVector LatPlateFootOffsetB(-0.5*(FramesX_min+LatFrameFootX)+10.*mm,-0.5*(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* LatFrame = new G4UnionSolid("LatFrame",LatFrame_B,LatFrameFoot,0,LatPlateFootOffsetB);
	
	
	//Try to put everything together
	G4ThreeVector LatFrameOffsetA(0.*mm,0.5*(FrontY+FramesY)+LatFrameFootY,-0.5*(PanelsZ-FramesZ));
	G4UnionSolid* HoldersA = new G4UnionSolid("HoldersA",FrontMask_3H,LatFrame,0,LatFrameOffsetA);
	
	G4ThreeVector LatFrameOffsetB(0.*mm,0.5*(FrontY+FramesY)+LatFrameFootY,0.5*(PanelsZ-FramesZ));
	G4UnionSolid* HoldersB = new G4UnionSolid("HoldersB",HoldersA,LatFrame,0,LatFrameOffsetB);
	
	G4ThreeVector BackMaskOffset(0.*mm,0.5*(FrontY+BackY)+(FramesY+LatFrameFootY),0.*mm);
	G4UnionSolid* ShortHolder = new G4UnionSolid("ShortHolder",HoldersB,BackMask,0,BackMaskOffset);
	
	G4Material* Teflon = G4Material::GetMaterial("Teflon");
	G4LogicalVolume* ShortHolder_log = new G4LogicalVolume(ShortHolder,Teflon,"ShortHolder_log");
	
	return ShortHolder_log;
	
}


/*
G4LogicalVolume* GeConstruction::ConstructPMTcolumn_long(){
	
	G4Colour red (1.0, 0.0, 0.0);
	
	G4Material* Air = G4Material::GetMaterial("Air");
	G4Material* Teflon = G4Material::GetMaterial("Teflon");
	
	G4double ColFr_X=100*mm, ColFr_Y=35*mm, ColFr_Z=326*mm;
	G4double ColBa_X=58*mm, ColBa_Y=83*mm, ColBa_Z=326*mm;
	G4double PMTlenght = 114*mm;
	
	G4double PMTsZoffset=43*mm; //Vertical Offset of the lowest PMT
	G4double PMTsSpacing=80*mm; //Distance between the PMTs central axis
	
	
	G4Box* PMTcolumnFront = new G4Box("PMTcolumnFront",ColFr_X/2.,ColFr_Y/2.,ColFr_Z/2.);
	G4Box* PMTcolumnBack = new G4Box("PMTcolumnBack",ColBa_X/2.,ColBa_Y/2.,ColBa_Z/2.);
	G4UnionSolid* PMTcolumn = new G4UnionSolid("PMTcolumn",PMTcolumnFront,PMTcolumnBack,0,G4ThreeVector(0.*mm,PMTlenght-(ColFr_Y+ColBa_Y)/2.,0.*mm));
	
	G4LogicalVolume* PMTLongColumn_log = new G4LogicalVolume(PMTcolumn,Air,"PMTLongColumn_log");
	
	G4VisAttributes* PMTLongColumn_vis = new G4VisAttributes(red);
	PMTLongColumn_vis->SetVisibility(true);
	PMTLongColumn_vis->SetForceSolid(false);
	PMTLongColumn_log->SetVisAttributes(PMTLongColumn_vis);
	
	
	//Construction and placement of the holder
	G4UnionSolid* LongHolder = ConstructPMTholder_long();
	G4LogicalVolume* LongHolder_log = new G4LogicalVolume(LongHolder,Teflon,"LongHolder_log");
	
	//Visualization properties
	
	G4ThreeVector LongHolder_offset(0.*mm,1.5*mm,0.*mm);
	G4VPhysicalVolume* LongHolder_phys = new G4PVPlacement(0,LongHolder_offset,LongHolder_log,"LongHolder_phys",PMTLongColumn_log,false,0);
	
	
	
	//Construction and placement of the PMTs
	G4LogicalVolume* PMT_log = ConstructPMT();
	
	G4ThreeVector PMT1_offset(0.0*mm,-ColFr_Y/2.,(PMTsZoffset-0.5*ColFr_Z));
	G4ThreeVector PMT2_offset(0.0*mm,-ColFr_Y/2.,(PMTsZoffset-0.5*ColFr_Z)+PMTsSpacing);
	G4ThreeVector PMT3_offset(0.0*mm,-ColFr_Y/2.,(PMTsZoffset-0.5*ColFr_Z)+2*PMTsSpacing);
	G4ThreeVector PMT4_offset(0.0*mm,-ColFr_Y/2.,(PMTsZoffset-0.5*ColFr_Z)+3*PMTsSpacing);
	
	G4RotationMatrix PMTrot;
	PMTrot.rotateX(-90*deg);
	
	//G4VPhysicalVolume* PMT1_phys = new G4PVPlacement(G4Transform3D(PMTrot,PMT1_offset),PMT_log,"PMT1_phys",PMTLongColumn_log,false,0);
	//G4VPhysicalVolume* PMT2_phys = new G4PVPlacement(G4Transform3D(PMTrot,PMT2_offset),PMT_log,"PMT2_phys",PMTLongColumn_log,false,0);
	//G4VPhysicalVolume* PMT3_phys = new G4PVPlacement(G4Transform3D(PMTrot,PMT3_offset),PMT_log,"PMT3_phys",PMTLongColumn_log,false,0);
	//G4VPhysicalVolume* PMT4_phys = new G4PVPlacement(G4Transform3D(PMTrot,PMT4_offset),PMT_log,"PMT4_phys",PMTLongColumn_log,false,0);
	
	
	return PMTLongColumn_log;
	
}
*/


