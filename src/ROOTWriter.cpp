#include "ROOTWriter.hh"
#include "Geometry.hh"
#include "G4UImanager.hh"
#include "TRandom.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TSystem.h"

ROOTWriter* ROOTWriter::pInstance=0;

void ROOTWriter::Initialize(){

    gSystem->Load("libMyDict.so");

    if (input_chain == 0){
        input_chain = 
            new TChain("soft_QCD_data");
        for (int i = 0; i <= 18; ++i){
            FILE* fp = fopen(Form("tree_for_Geant_soft_QCD_%d.root", i), "rb");
            if (fp != NULL){
                input_chain->Add(Form("tree_for_Geant_soft_QCD_%d.root", i));
            }
        }
    }

    input_chain->Print();

    if (output_file == 0){
        output_file = 
            new TFile("Calorimeter_energy_edeption_data.root",
                      "RECREATE");
    }

    current_particle_edeption.resize(Geometry::ncell_x * Geometry::ncell_y);

    Link_tree_branches();

    calorimeter_data = new TTree("calorimeter_data", "calorimeter_data");
    calorimeter_data->SetMaxTreeSize(10000000000);
    calorimeter_data->SetAutoSave(0);
    calorimeter_data->Branch("cell_energy", &cell_energy_edeption);
    calorimeter_data->Branch("event_data", &event_data_to_output);
    calorimeter_data->Print();

    return;
}

void ROOTWriter::Link_tree_branches(){
    input_chain->SetBranchAddress("event", &event_data);
    return;
}

void ROOTWriter::Incr_energy_edept(G4int cellx, G4int celly, G4double en_ed){
    current_particle_edeption[cellx * Geometry::ncell_x + celly] += en_ed;
    return;
}

void ROOTWriter::Set_event_counter(G4int ev_counter){
    event_counter = ev_counter;
    return;
}

void ROOTWriter::Inc_event_counter(){
    ++event_counter;
    return;
}

void ROOTWriter::Inc_particle_counter(){
    ++particle_counter;
    return;
}

void ROOTWriter::Get_particle_in_event_by_number(G4int p_counter, std::vector<double>& data){
    
    data = (*event_data)[p_counter];
    
    return;
}

void ROOTWriter::Set_particle_in_output_data(std::vector<double> particle){
    event_data_to_output.push_back(particle);
    return;
}

// void ROOTWriter::Set_current_particle_edeption(){
//     std::vector<G4double> tmp = current_particle_edeption;
//     G4double edep = 0;
//     for (auto d : tmp){
//         edep += d;
//     }
//     G4cout << edep << "\n";
//     cell_energy_edeption.push_back(tmp);
//     return;
// }

void ROOTWriter::Get_tree_entry(G4int ientry){
    input_chain->GetEntry(ientry);
    Inc_event_counter();
    return;
}

void ROOTWriter::Fill(){

    if (particle_counter < Get_event_size() - 1){
        Inc_particle_counter();
        cell_energy_edeption.push_back(current_particle_edeption);
        current_particle_edeption.clear();
        current_particle_edeption.resize(Geometry::ncell_x * Geometry::ncell_y);
    } else { 
        particle_counter = 0;
        Get_tree_entry(event_counter);
        cell_energy_edeption.push_back(current_particle_edeption);
        current_particle_edeption.clear();
        current_particle_edeption.resize(Geometry::ncell_x * Geometry::ncell_y);
        calorimeter_data->Fill();
        event_data_to_output.clear();
        cell_energy_edeption.clear();
    }

    return;
}

void ROOTWriter::Finalize(){

    output_file->cd();
    calorimeter_data->Write();

    delete output_file;
    return;
}

G4int ROOTWriter::Get_tree_entries(){
    return input_chain->GetEntries();
}

G4int ROOTWriter::Get_event_counter(){
    return event_counter;
}

G4int ROOTWriter::Get_particle_counter(){   
    return particle_counter;
}

G4int ROOTWriter::Get_event_size(){
    return event_data->size();
}

G4bool ROOTWriter::Check_acceptance(G4double px, G4double py, G4double pz, G4double p0){
    G4double eta = 0.5*TMath::Log((TMath::Sqrt(px * px + py * py + pz * pz) + pz)/(TMath::Sqrt(px * px + py * py + pz * pz) - pz));
    if (fabs(eta) <= 0.5){
        return true;
    } else {
        return false;
    }
}
