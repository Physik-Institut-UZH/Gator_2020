
#include "GeRunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "Randomize.hh"

#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>

GeRunAction::GeRunAction()
{}


GeRunAction::~GeRunAction()
{}

void GeRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    }
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine); //selection of a random engine 
  G4long seed=time(0); //returns time in seconds as an integer
  CLHEP::HepRandom::setTheSeed(seed);//changes the seed of the random engine
  CLHEP::HepRandom::showEngineStatus();//shows the actual seed
 
}


void GeRunAction::EndOfRunAction(const G4Run*)
{
  if (G4VVisManager::GetConcreteInstance())
    {
     //G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
    }


}


