#ifndef GeConstruction_H
#define GeConstruction_H 1

class G4UnionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Box;
class G4Material;
class GeScintSD;

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class GeConstruction : public G4VUserDetectorConstruction
{
  public:

	GeConstruction();
	~GeConstruction();

	G4VPhysicalVolume* Construct();
	
    void SetCheckOverlap(G4bool dCheckOverlap)  {pCheckOverlap = dCheckOverlap;};

  private:


	void CheckOverlapping();   
	void SecondOverlapCheck();
//	void PrintGeometryInformation(); 

#include "includesample.hh"

    // Logical volumes
	G4LogicalVolume* lab_log;
	G4LogicalVolume* lead4_log;
	G4LogicalVolume* lead3_log;
	G4LogicalVolume* lead2_log;
	G4LogicalVolume* lead_box_3Bqkg_log;
	G4LogicalVolume* lead_top_75Bqkg_log;
	G4LogicalVolume* lead_top_3Bqkg_log;
	G4LogicalVolume* lead6_log;
	G4LogicalVolume* leadlayer_log;
	G4LogicalVolume* cavity1_log;
	G4LogicalVolume* copper_layer_log;
	G4LogicalVolume* cavity2_log;
	G4LogicalVolume* endcap_log;
	G4LogicalVolume* vacuum_log;
	G4LogicalVolume* holder_log;
	G4LogicalVolume* innervac_log;
	G4LogicalVolume* plug_log;
	G4LogicalVolume* innervac3_log;
	G4LogicalVolume* cover_log;
	G4LogicalVolume* innervac2_log;
	G4LogicalVolume* crystal_log;
	G4LogicalVolume* crystalhole_log;
	G4LogicalVolume* crystalgroove_log;
	G4LogicalVolume* active_log;
	G4LogicalVolume* mylar_log;
	G4LogicalVolume* kapton_log;
	G4LogicalVolume* contact1_log;
	G4LogicalVolume* contact2_log;
	G4LogicalVolume* contact3_log;
    G4LogicalVolume* base_log;
    G4LogicalVolume* lower_vacuum_log;
    G4LogicalVolume* holder2_log;
    G4LogicalVolume* holder2vac_log;
    G4LogicalVolume* tube1_log;
    G4LogicalVolume* cold_stick_cover1_log;
    G4LogicalVolume* cold_stick_cover2_log;
    G4LogicalVolume* cold_stick_cover3_log;
    G4LogicalVolume* cold_stick_cover4_log;
    G4LogicalVolume* csvacuum1_log;
    G4LogicalVolume* csvacuum2_log;
    G4LogicalVolume* csvacuum3_log;
    G4LogicalVolume* csvacuum4_log;
    G4LogicalVolume* stick1_log;
    G4LogicalVolume* stick2_log;
    G4LogicalVolume* stick3_log;
    G4LogicalVolume* stick4_log;
    G4LogicalVolume* stick5_log;
    G4LogicalVolume* test_log;
    G4LogicalVolume* pmt_log;
  G4LogicalVolume* poly_log;
  G4LogicalVolume* cirlex_log;
  G4LogicalVolume* lead_gap_top_log;
	G4LogicalVolume* lead_gap_mid_log;
	G4LogicalVolume* lead_gap_bot_log;
	G4LogicalVolume* feedthrough_log;
	G4LogicalVolume* teflonarcs_log;
	G4LogicalVolume* cdms_pb_log;
	G4LogicalVolume* cdms_pb2_log;
	G4LogicalVolume* cdms_pb_inside_log;
	G4LogicalVolume* copper_box_log;
/*	G4LogicalVolume* plastic_container_log;
	G4LogicalVolume* bases_stack1_log; 
	G4LogicalVolume* bases_stack2_log; 
	G4LogicalVolume* bases_stack3_log; 
	G4LogicalVolume* bases_stack4_log; 
	G4LogicalVolume* bases_stack5_log; 
	G4LogicalVolume* bases_stack6_log; 
*/
    // Physical volumes
	G4VPhysicalVolume* lead_box_3Bqkg_phys;
	G4VPhysicalVolume* lead_box_75Bqkg_phys;
   G4VPhysicalVolume* lab_phys;
   G4VPhysicalVolume* lead_phys;
   G4VPhysicalVolume* lead4_phys;
   G4VPhysicalVolume* lead3_phys;
   G4VPhysicalVolume* lead2_phys;
	G4VPhysicalVolume* copper_box_phys;
	G4VPhysicalVolume* copper_top_phys;
	G4VPhysicalVolume* lead_top_3Bqkg_phys;
	G4VPhysicalVolume* lead_top_75Bqkg_phys;
	G4VPhysicalVolume* lead6_phys;
//    G4VPhysicalVolume* lead7_phys;
    G4VPhysicalVolume* oldlead_phys;
  G4VPhysicalVolume* leadlayer_phys;
//  G4VPhysicalVolume* copper2_phys;
//  G4VPhysicalVolume* copper5_phys;
    G4VPhysicalVolume* cavity1_phys;
    G4VPhysicalVolume* copper_layer_phys;
    G4VPhysicalVolume* cavity2_phys;
    G4VPhysicalVolume* endcap_phys;
    G4VPhysicalVolume* vacuum_phys;
    G4VPhysicalVolume* holder_phys;
    G4VPhysicalVolume* innervac_phys;
    G4VPhysicalVolume* plug_phys;
    G4VPhysicalVolume* innervac3_phys;
    G4VPhysicalVolume* cover_phys;
    G4VPhysicalVolume* innervac2_phys;
    G4VPhysicalVolume* crystal_phys;
    G4VPhysicalVolume* crystalhole_phys;
    G4VPhysicalVolume* crystalgroove_phys;
    G4VPhysicalVolume* active_phys;
    G4VPhysicalVolume* mylar_phys;
    G4VPhysicalVolume* kapton_phys;
  G4VPhysicalVolume* contact1_phys;
  G4VPhysicalVolume* contact2_phys;
  G4VPhysicalVolume* contact3_phys;
  //G4VPhysicalVolume* contact_phys;
    G4VPhysicalVolume* base_phys;
    //G4VPhysicalVolume* tube_phys;
    G4VPhysicalVolume* lower_vacuum_phys;
    G4VPhysicalVolume* holder2_phys;
    G4VPhysicalVolume* holder2vac_phys;
    //G4VPhysicalVolume* lower_vacuum2_phys;
    //G4VPhysicalVolume* stick_phys;
    G4VPhysicalVolume* tube1_phys;
    G4VPhysicalVolume* cold_stick_cover1_phys;
    G4VPhysicalVolume* cold_stick_cover2_phys;
    G4VPhysicalVolume* cold_stick_cover3_phys;
    G4VPhysicalVolume* cold_stick_cover4_phys;
    G4VPhysicalVolume* csvacuum1_phys;
    G4VPhysicalVolume* csvacuum2_phys;
    G4VPhysicalVolume* csvacuum3_phys;
    G4VPhysicalVolume* csvacuum4_phys;
    G4VPhysicalVolume* stick1_phys;
    G4VPhysicalVolume* stick2_phys;
    G4VPhysicalVolume* stick3_phys;
    G4VPhysicalVolume* stick4_phys;
    G4VPhysicalVolume* stick5_phys;
    G4VPhysicalVolume* test_phys;
    //G4VPhysicalVolume* steel304_phys;
    G4VPhysicalVolume* pmt1_phys;
    G4VPhysicalVolume* pmt2_phys;
    G4VPhysicalVolume* pmt3_phys;
    G4VPhysicalVolume* pmt4_phys;
  //G4VPhysicalVolume* steel304_2_phys;
  G4VPhysicalVolume* poly_phys;
  G4VPhysicalVolume* cirlex_phys;
  G4VPhysicalVolume* lead_gap_top_phys;
  G4VPhysicalVolume* lead_gap_mid_phys;
  G4VPhysicalVolume* lead_gap_bot_phys;
  G4VPhysicalVolume* feedthrough_phys;
  G4VPhysicalVolume* teflonarcs_phys;
  G4VPhysicalVolume* cdms_pb1_phys;
  G4VPhysicalVolume* cdms_pb2_phys;
  G4VPhysicalVolume* cdms_pb1_inside_phys;
  G4VPhysicalVolume* cdms_pb2_inside_phys;
  //G4VPhysicalVolume* lead_box_3Bqkg_phys;
/*	G4VPhysicalVolume* plastic_container_phys;
	G4VPhysicalVolume* bases_stack1_phys; 
	G4VPhysicalVolume* bases_stack2_phys; 
	G4VPhysicalVolume* bases_stack3_phys; 
	G4VPhysicalVolume* bases_stack4_phys; 
	G4VPhysicalVolume* bases_stack5_phys; 
	G4VPhysicalVolume* bases_stack6_phys; 
*/	


	G4bool   pCheckOverlap;

	GeScintSD* activeSD;
};

#endif
