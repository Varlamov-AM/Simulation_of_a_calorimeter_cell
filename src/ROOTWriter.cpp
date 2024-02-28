#include "ROOTWriter.hh"
#include "Geometry.hh"
#include "G4UImanager.hh"
#include "TRandom.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"

ROOTWriter* ROOTWriter::pInstance=0;

void ROOTWriter::Initialize(){

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
    calorimeter_data->Branch("cell_energy", &cell_energy_edeption);
    calorimeter_data->Branch("event_data", &event_data_to_output);

    return;
}

void ROOTWriter::Refresh_data()
{

    event_data_to_output.clear();
    cell_energy_edeption.clear();
    particle_counter = 0;

    return;
}

void ROOTWriter::Incr_energy_edept(G4int cellx, G4int celly, G4double en_ed){

    current_particle_edeption[cellx * Geometry::ncell_x + celly] += en_ed;

    return;
}

void ROOTWriter::Link_tree_branches(){

    input_chain->SetBranchAddress("event", &event_data);

    return;
}

void ROOTWriter::Get_tree_entry(G4int ientry){
    input_chain->GetEntry(ientry);

    return;
}

void ROOTWriter::Inc_event_counter(){
    ++event_counter;
}

void ROOTWriter::Resize_result_vectors(){
    event_data_to_output.resize(ROOTWriter::GetPointer()->Get_event_size());
    cell_energy_edeption.resize(ROOTWriter::GetPointer()->Get_event_size());
}

void ROOTWriter::Get_particle_in_event_by_number(G4int p_counter, std::vector<double>& particle_data){
    if (event_data->size() != 0){
        particle_data = (*event_data)[p_counter];
        event_data_to_output[p_counter] = particle_data;
    }
    return;
}

void ROOTWriter::Add_current_particle(G4int p_counter){

    std::vector<double> tmp = current_particle_edeption;
    cell_energy_edeption[p_counter] = tmp;

    G4double s = 0;
    for (auto d : tmp){
        s += d;
    }

    std::cout << "i = " << p_counter << " energy deposit = " << s << "\n";
    
    return;
}

G4int ROOTWriter::Get_tree_entries(){
    return input_chain->GetEntries();
}

G4int ROOTWriter::Get_event_counter(){
    return event_counter;
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

void ROOTWriter::Fill(){



    calorimeter_data->Fill();
    Refresh_data();

    return;
}

void ROOTWriter::Finalize(){

    output_file->cd();
    calorimeter_data->Write();

    delete output_file;
    // delete input_file;

    return;
}
