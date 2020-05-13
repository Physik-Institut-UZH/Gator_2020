
#ifndef GeScintHit_h
#define GeScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GeScintHit : public G4VHit
{
  public:

      GeScintHit();
      ~GeScintHit();
      GeScintHit(const GeScintHit&);
      const GeScintHit& operator=(const GeScintHit&);
      int operator==(const GeScintHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetEdep           (G4double de)       { edep = de; };
      void SetPos            (G4ThreeVector xyz) { pos = xyz; };
      void SetParticle       (G4String name)     { particleName = name; };
      void SetParticleEnergy (G4double e1)       { particleEnergy = e1; };
      void SetTime           (G4double t2)       { time = t2; };


      G4double GetEdep()                         { return edep; };      
      G4ThreeVector GetPos()                     { return pos; };
      G4String GetParticle()                     { return particleName;};
      G4double GetParticleEnergy()               { return particleEnergy;};
      G4double GetTime()                         { return time; };      


  private:
      G4double      edep;
      G4ThreeVector pos;
      G4double      time;
      G4String      particleName;
      G4double      particleEnergy;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

typedef G4THitsCollection<GeScintHit> GeScintHitsCollection;

extern G4Allocator<GeScintHit> GeScintHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void* GeScintHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) GeScintHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void GeScintHit::operator delete(void* aHit)
{
  GeScintHitAllocator.FreeSingle((GeScintHit*) aHit);
}

#endif
