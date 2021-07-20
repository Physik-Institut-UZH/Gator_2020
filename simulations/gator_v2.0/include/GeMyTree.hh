#ifndef GeMyTree_h
#define GeMyTree_h 1

#include "GeEventAction.hh"
#include "globals.hh"
//#include "Rtypes.h"

class MyTree{
    
public:
  int eventid;
  int step;
  int NoHits;
  char detID[25];
  int parentid;
  char type[25];
  char inter[25];
  float xp;
  float yp;
  float zp;
  float te;   
  float GeEtot;
  float GeEhit;
  float time;
  int extint;
  
  MyTree(void);
  ~MyTree(); 
  
};

#endif
