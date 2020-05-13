#include "GeScintSD.hh"

#include "GeScintHit.hh"
#include "GeConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Ions.hh"
#include "G4ios.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeScintSD::GeScintSD(G4String name) 
  :G4VSensitiveDetector(name),HCID(-1)
{
  
  HCname="scintillatorCollection";
  collectionName.insert(HCname); //This is an object of a class derived from std::vector<T> => I have the same methods
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeScintSD::~GeScintSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintSD::Initialize(G4HCofThisEvent* HCE){
  /* This method is called once at the start of each event by SDManager class through the method PrepareNewEvent() */
  //static G4int SDinitcall = 0; //For debugging purposes (this declaration/initial will be executed only once because it is static)
  //G4cout << "<ScintSD Initializer>" << G4endl; //For debugging purposes
  
  //G4cout << "Elements in 'collectionName': " << collectionName.size() << G4endl;
  
  //Create an hits collection
  
  scintillatorCollection = new GeScintHitsCollection(SensitiveDetectorName,collectionName[0]);
  
  // Add this collection in hce
  if(HCID < 0){
  	
  	//HCID is the "vector index" of this collection, Since I have only 1 hits collection (scintillatorCollection) this should be alway be 0
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(scintillatorCollection);

  }
  
  HCE->AddHitsCollection(HCID,scintillatorCollection);
  
  //G4cout << "Number of Collections = " <<  HCE->GetNumberOfCollections() << G4endl; //For debugging purpose
  
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool GeScintSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
  /* This method is called by G4SteppingManager when a step is composed in the logical volume which has the pointer to this sensitive detector */
  
  //G4cout << "\n<ProcessHits call>" << G4endl; //For debugging purposes
  
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
  G4String particleName = particleType->GetParticleName();

  G4double stepl = 0.;
  if (particleType->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();
  
  if ((edep==0.)&&(stepl==0.)){
    //G4cout << "ProcessHits returning FALSE VALUE" << G4endl;
    return false;
  }      


  // fill in hit
  GeScintHit* newHit = new GeScintHit(); //Generates a memory leakage!!!
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetParticle(particleName);
  newHit->SetParticleEnergy(aStep->GetPreStepPoint()->GetKineticEnergy() );

  //nHits = scintillatorCollection->insert(newHit);
  scintillatorCollection->insert(newHit);
  
  //G4cout << "Number of Hits in the collection: " <<  nHits << " hits" << G4endl;
  
  //G4cout << "ProcessHits returning TRUE VALUE" << G4endl;
  return true;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  
  //G4cout << "<EndOfEvent call>" << G4endl; //For debugging purposes
  
  //G4cout << "Hits Collection: in this event they are " << scintillatorCollection->entries() << G4endl; //For debugging purposes
  
  nHits = scintillatorCollection->entries();
  
  //HCE->AddHitsCollection(HCID,scintillatorCollection);
  /*
  G4String HCname = collectionName[0];
  static G4int HCID = -1;
  if(HCID<0)
  G4int  HCID = G4SDManager::GetSDMpointer()->GetCollectionID(HCname);
  HCE->AddHitsCollection(HCID,scintillatorCollection);
  */

  
  
  if (verboseLevel>=1 && nHits!=0)
    //    G4cout << "     LXe collection: " <<  nHits << " hits" << G4endl;
  if (verboseLevel>=2 && nHits!=0)
    scintillatorCollection->PrintAllHits();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintSD::clear()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintSD::DrawAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintSD::PrintAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
