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

PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code)
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  
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
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  
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
    delete rndm;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    if (Action_generator_mode){
        particle_Energy = gRandom->Uniform(20 * GeV);
        fParticleGun->SetParticleEnergy(particle_Energy);
    } 

    G4double beam_x = rndm->Uniform(-1, 1) * 11 * mm;
    G4double beam_y = rndm->Uniform(-1, 1) * 11 * mm;

    fParticleGun->SetParticlePosition(G4ThreeVector(rndm->Uniform(-1, 1) * 11 * mm, rndm->Uniform(-1, 1) * 11 * mm, -240*mm)); 

    ROOTWriter::GetPointer()->Set_init_data(particle_Energy);
    ROOTWriter::GetPointer()->Set_beam_positin(beam_x, beam_y);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    return;
}
