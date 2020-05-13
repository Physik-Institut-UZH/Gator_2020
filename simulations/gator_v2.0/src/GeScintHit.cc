#include "GeScintHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>

G4Allocator<GeScintHit> GeScintHitAllocator; //Redundant!!!

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeScintHit::GeScintHit()
{
  //G4cout << "Start of ScintHit" << G4endl;
  edep=0.;
  pos = G4ThreeVector(0., 0., 0.);
  time = 0.;
  particleEnergy = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeScintHit::~GeScintHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeScintHit::GeScintHit(const GeScintHit& right)
  : G4VHit(right)
{
  edep      = right.edep;
  pos       = right.pos;
  time           = right.time;
  particleName   = right.particleName;
  particleEnergy = right.particleEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const GeScintHit& GeScintHit::operator=(const GeScintHit& right)
{
  edep      = right.edep;
  pos       = right.pos;
  time            = right.time;
  particleName    = right.particleName;
  particleEnergy  = right.particleEnergy;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int GeScintHit::operator==(const GeScintHit& right) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void GeScintHit::Draw()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeScintHit::Print()
{

  G4cout << "      LXe hit ENERGY: " << std::setw(5) << G4BestUnit(edep,"Energy") 
	 << ", at " << G4BestUnit(pos,"Length") << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


