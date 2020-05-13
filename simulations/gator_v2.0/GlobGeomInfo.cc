#include <string>
#include <sstream>
#include <unistd.h>

#include <globals.hh>
#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>
#include <G4VisExecutive.hh>
#include <G4GeneralParticleSource.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4ThreeVector.hh>

#include "GeConstruction.hh"


void usage();

int
main(int argc, char **argv){

  // switches
	int c = 0;
  
	bool bMassInfo = false;
	bool bVolumeName = false;
  
	G4String hCommand, hVolName;
  
	// parse switches
	while((c = getopt(argc,argv,"v:m")) != -1){
		switch(c)	{
        	case 'm':
				bMassInfo = true;
				break;
			
			case 'v':
        		bVolumeName = true;
				hVolName = optarg;
				break;
			
			default:
				usage();
		}
	}
  
  
	// Detector Construction (here doesn't play any role)
	GeConstruction *detector = new GeConstruction(); 
	detector->Construct();
  
	// geometry IO
	G4UImanager* pUImanager = G4UImanager::GetUIpointer();
  
	if(!bVolumeName){
		G4cout << "Physical volume name not set!!!" << G4endl;
	}
	
	G4PhysicalVolumeStore* pPhysVolStore = G4PhysicalVolumeStore::GetInstance();
	
	G4int Nvolumes = pPhysVolStore->size();
	
	//Take the physical volume pointer you want
	G4VPhysicalVolume *pPhysVol = NULL;
	for(G4int i=0; i<Nvolumes; i++){
		G4String tmp_name = pPhysVolStore->at(i)->GetName();
		if(tmp_name==hVolName){
			pPhysVol = pPhysVolStore->at(i);
		}
	}
	
	if(!pPhysVol){
		G4cout << "Physical Volume \"" << hVolName << "\" not found!!!" << G4endl;
		return(0);
	}
	
	G4cout << G4endl << G4endl;
	
	if(!bMassInfo){
		G4ThreeVector ShiftGlob = pPhysVol->GetTranslation();
	
		while(pPhysVol->GetMotherLogical()){
			//Find the mother phys volume
			G4VPhysicalVolume *pAncPhysVol;
		
			for(G4int i=0; i<Nvolumes; i++){
				if(pPhysVolStore->at(i)->GetLogicalVolume()->IsDaughter(pPhysVol)){
					pAncPhysVol = pPhysVolStore->at(i);
				}
			}
			G4cout << "Shift of physical volume \"" << pPhysVol->GetName() << "\" respect to \"" << pAncPhysVol->GetName() << "\" =  " << pPhysVol->GetTranslation()/mm << " mm" << G4endl;
			pPhysVol = pAncPhysVol;
			ShiftGlob = ShiftGlob + pPhysVol->GetTranslation();
		}
	
		G4cout << G4endl << "Global shift of physical volume \"" << hVolName << "\" =  " << ShiftGlob/mm << " mm" << G4endl;
	}else{
		
		G4double mass = (pPhysVol->GetLogicalVolume()->GetMass(false,false))/kg;
		G4double density = (pPhysVol->GetLogicalVolume()->GetMaterial()->GetDensity())/(kg/m3);
		G4double volume = mass/density;
		G4cout << "Mass of physical volume \"" << pPhysVol->GetName() << "\" = " << mass << " kg" << G4endl;
		G4cout << "Volume of physical volume \"" << pPhysVol->GetName() << "\" = " << volume << " m^3" << G4endl;
		G4cout << G4endl << G4endl;
	}


// write to file "macros" ... tbd


	return 0;
}

void usage(){
  exit(0);
}

