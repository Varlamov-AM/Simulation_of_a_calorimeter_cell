#ifndef PrimaryGenerator_h
#define PrimaryGenerator_h 1

#include "G4VPrimaryGenerator.hh"

class G4Event;

class PrimaryGenerator : public G4VPrimaryGenerator
{
  public:
    PrimaryGenerator();    
   ~PrimaryGenerator();

  public:
    virtual void GeneratePrimaryVertex(G4Event*);

};

#endif