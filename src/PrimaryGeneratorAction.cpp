#include "PrimaryGeneratorAction.hh"
#include "ROOTWriter.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Gamma.hh"
#include "G4MuonMinus.hh"
#include "TMath.h"
#include "G4GeneralParticleSource.hh"




PrimaryGeneratorAction* PrimaryGeneratorAction::fPtr = 0;

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  
  fPtr = this;
  fParticleGun  = new G4ParticleGun(1);

};

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
};

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){};
