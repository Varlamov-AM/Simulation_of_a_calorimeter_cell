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
    fParticleGun = new G4ParticleGun(1);
    ROOTWriter::GetPointer()->Get_tree_entry(0);
    fParticleTable = G4ParticleTable::GetParticleTable();
}

// PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code)
//     : G4VUserPrimaryGeneratorAction(){
  
//     fPtr = this;
//     fParticleGun  = new G4ParticleGun(1);

//     G4ParticleDefinition* particle = fParticleTable->FindParticle(PDG_code);
    
//     fParticleGun->SetParticleDefinition(particle);
//     fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*cm));
//     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
//     particle_PDG_code = PDG_code;
//     Action_generator_mode = true;

// }

// PrimaryGeneratorAction::PrimaryGeneratorAction(G4int PDG_code, G4double Particle_energy)
//     : G4VUserPrimaryGeneratorAction(){
  
//     fPtr = this;
//     fParticleGun  = new G4ParticleGun(1);

//     particle_PDG_code = PDG_code;
//     particle_Energy = Particle_energy;

//     rndm = new TRandom();

//     G4ParticleDefinition* particle = fParticleTable->FindParticle(PDG_code);
//     fParticleGun->SetParticleDefinition(particle);
//     // fParticleGun->SetParticlePosition(G4ThreeVector(rndm->Uniform(-1, 1) * 11 * mm, rndm->Uniform(-1, 1) * 11 * mm, -240*mm));
//     fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
//     fParticleGun->SetParticleEnergy(particle_Energy);
//     Action_generator_mode = false;

// }

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    std::vector<G4double> particle_data{5};
    ROOTWriter::GetPointer()->Get_particle_in_event_by_number(ROOTWriter::GetPointer()->Get_particle_counter(), particle_data);
    // G4cout << ROOTWriter::GetPointer()->Get_event_counter() << " " << ROOTWriter::GetPointer()->Get_particle_counter() << " " << ROOTWriter::GetPointer()->Get_event_size() << " ";
    // G4cout << "\n";
    // for (auto p : particle_data){
    //     G4cout << p << " ";
    // }
    // G4cout << "\n";

    G4ParticleDefinition* particle = fParticleTable->FindParticle(particle_data[4]);

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -250 * mm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    if (particle->GetParticleName() == "gamma"){
        fParticleGun->SetParticleEnergy(particle_data[0] * GeV);
    } else {
        fParticleGun->SetParticleEnergy((particle_data[0] - 
            TMath::Sqrt(particle_data[0] * particle_data[0] - 
                    (particle_data[1] * particle_data[1] + 
                        particle_data[2] * particle_data[2] + 
                        particle_data[3] * particle_data[3]))) * GeV);
    }

    // fParticleGun->SetParticleMomentum(TMath::Sqrt(particle_data[1] * particle_data[1] + particle_data[2] * particle_data[2] + particle_data[3] * particle_data[3]) * GeV);
    // G4cout << TMath::Sqrt(particle_data[1] * particle_data[1] + particle_data[2] * particle_data[2] + particle_data[3] * particle_data[3]) * GeV << "\n";

    fParticleGun->GeneratePrimaryVertex(anEvent);

    ROOTWriter::GetPointer()->Set_particle_in_output_data(particle_data);
    
    return;
}
