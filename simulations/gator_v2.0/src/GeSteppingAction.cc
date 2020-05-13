
#include "GeSteppingAction.hh"

#include "G4SteppingManager.hh"






GeSteppingAction::GeSteppingAction()
{ }






void GeSteppingAction::UserSteppingAction(const G4Step* aStep){
	
	//G4StepPoint* fPreStepPoint = aStep -> GetPreStepPoint();
	//G4StepPoint* fPostStepPoint = aStep -> GetPostStepPoint();
	
	
	//G4cout << "PreStepPoint logical volume: <" << fPreStepPoint->GetPhysicalVolume()->GetLogicalVolume()->GetName() << ">" << G4endl;
	//G4cout << "In Matrial: <" << fPreStepPoint->GetMaterial()->GetName() << ">" << G4endl;
	//G4cout << "Pointer to sensitive volume is " << aStep->GetPreStepPoint()->GetSensitiveDetector() << G4endl;
	
	//G4cout << "PostStepPoint logical volume: " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() << G4endl;
	//G4cout << "Pointer to sensitive volume is " << aStep->GetPostStepPoint()->GetSensitiveDetector() << G4endl;
	
}
