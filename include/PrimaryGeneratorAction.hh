#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"
#include "TF1.h"

class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:

  PrimaryGeneratorAction();    

  virtual ~PrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event*);         
  
  static PrimaryGeneratorAction* GetPointer() {return fPtr;}
  
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    
   
private:
  
  static PrimaryGeneratorAction* fPtr;
  G4ParticleGun* fParticleGun;
  
};

#endif
