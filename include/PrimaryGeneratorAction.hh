#include "G4VUserPrimaryGeneratorAction.hh"

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"
#include "TF1.h"
#include "TRandom.h"

class G4Event;
class PrimaryGenerator;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:

  PrimaryGeneratorAction();    

  PrimaryGeneratorAction(G4int);    

  PrimaryGeneratorAction(G4int, G4double);   

  virtual ~PrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event*);         
  
  static PrimaryGeneratorAction* GetPointer() {return fPtr;}
  
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    
   
private:

  PrimaryGenerator* fPrimaryGenerator;
  
  static PrimaryGeneratorAction* fPtr;
  G4ParticleGun* fParticleGun;
  G4ParticleTable* fParticleTable;
  G4int     ievent;
  G4int     particle_PDG_code;
  G4double  particle_Energy;
  G4bool    Action_generator_mode;
  TRandom*  rndm;
  
};

#endif
