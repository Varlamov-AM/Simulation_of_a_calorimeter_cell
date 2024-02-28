#include "PrimaryGenerator.hh"
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
#include "TRandom.h"




PrimaryGeneratorAction* PrimaryGeneratorAction::fPtr = 0;

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction() {
  
    fPtr = this;
    fPrimaryGenerator = new PrimaryGenerator();

}

PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code)
    : G4VUserPrimaryGeneratorAction(){
  
    fPtr = this;
    fParticleGun  = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(PDG_code);
    
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    particle_PDG_code = PDG_code;
    Action_generator_mode = true;

}

PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code, G4double Particle_energy)
    : G4VUserPrimaryGeneratorAction(){
  
    fPtr = this;
    fParticleGun  = new G4ParticleGun(1);

    particle_PDG_code = PDG_code;
    particle_Energy = Particle_energy;

    rndm = new TRandom();

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(PDG_code);
    fParticleGun->SetParticleDefinition(particle);
    // fParticleGun->SetParticlePosition(G4ThreeVector(rndm->Uniform(-1, 1) * 11 * mm, rndm->Uniform(-1, 1) * 11 * mm, -240*mm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    fParticleGun->SetParticleEnergy(particle_Energy);
    Action_generator_mode = false;

}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    fPrimaryGenerator->GeneratePrimaryVertex(anEvent);

    return;
}
