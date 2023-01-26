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

PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code)
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  
    fPtr = this;
    fParticleGun  = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(PDG_code);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-10*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    random_gen = new TRandom();
    random_gen->SetSeed(0);
    particle_PDG_code = PDG_code;

};

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
    delete random_gen;
};

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){


    particle_Energy = random_gen->Uniform(50.) * GeV;
    fParticleGun->SetParticleEnergy(particle_Energy);

    ROOTWriter::GetPointer()->Set_init_data(particle_Energy);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    return;
};
