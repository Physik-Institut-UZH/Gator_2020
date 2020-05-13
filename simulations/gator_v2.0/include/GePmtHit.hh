
#ifndef GePmtHit_h
#define GePmtHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


class GePmtHit : public G4VHit 
{
  public:

      GePmtHit();
     ~GePmtHit();

      GePmtHit(const GePmtHit&);
      const GePmtHit& operator=(const GePmtHit&);
      int operator==(const GePmtHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  private:
     G4ThreeVector pos;
     G4double time;


  public:
     inline void SetPos(G4ThreeVector xyz)       {pos=xyz;};
     inline G4ThreeVector GetPos()               const {return pos;};

     inline void SetTime(G4double t)             {time=t;};
     inline G4double GetTime()                   const {return time;};


};


// vector collection of one type of hits
typedef G4THitsCollection<GePmtHit> GePmtHitsCollection;


extern G4Allocator<GePmtHit> GePmtHitsAllocator;


inline void* GePmtHit::operator new(size_t) {
  void* aHit;
  aHit = (void*) GePmtHitsAllocator.MallocSingle();
  return aHit;
}


inline void GePmtHit::operator delete(void* aHit) {
  GePmtHitsAllocator.FreeSingle((GePmtHit*) aHit);
}

#endif

