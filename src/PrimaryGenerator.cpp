#include "PrimaryGenerator.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "ROOTWriter.hh"



PrimaryGenerator::PrimaryGenerator() : G4VPrimaryGenerator(){}

PrimaryGenerator::~PrimaryGenerator(){}


void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event){

    // ROOTWriter::GetPointer()->Get_tree_entry(ROOTWriter::GetPointer()->Get_event_counter());
    // ROOTWriter::GetPointer()->Inc_event_counter();

    // G4int n_particle_in_event = ROOTWriter::GetPointer()->Get_event_size();
    // if (n_particle_in_event == 0){return;}

    // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    // ROOTWriter::GetPointer()->Resize_result_vectors();

    // G4PrimaryVertex* vertex = new G4PrimaryVertex(G4ThreeVector(0, 0, -250*mm), 0 * s);

    // G4PrimaryParticle** primary_part = new G4PrimaryParticle*[n_particle_in_event];

    // for (int i = 0; i < n_particle_in_event; ++i){
    //     std::vector<G4double> particle; 
    //     ROOTWriter::GetPointer()->Get_particle_in_event_by_number(0, particle);

    //     TLorentzVector v(particle[1], particle[2], particle[3], particle[0]);

    //     G4ParticleDefinition* particle_def = particleTable->FindParticle((G4int)particle[4]);
    //     G4double particle_Energy = (v.E() - v.M()) * GeV;

    //     primary_part[i] = new G4PrimaryParticle(particle_def);
    //     primary_part[i]->SetMomentumDirection(G4ThreeVector(0,0,1));
    //     primary_part[i]->SetKineticEnergy(particle_Energy);
    //     vertex->SetPrimary(primary_part[i]);
    // }

    // event->AddPrimaryVertex(vertex);
    // G4cout << event->GetNumberOfPrimaryVertex() << "\n";
    // G4cout << event->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy() << " ";
    // G4cout << event->GetPrimaryVertex()->GetPrimary()->GetUserInformation() << "\n";

}
