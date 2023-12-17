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

    if (input_file == 0){
        input_file = 
            new TFile("electron_positron_gamma_4momentum.root", "READ");
    }

    pythia_data = (TTree*)input_file->Get("signal_event_electron_positron_gamma_from_chic_with_branchings");
    pythia_data->Print();

    if (output_file == 0){
        output_file = 
            new TFile("Calorimeter_energy_edeption_data.root",
                      "RECREATE");
    }

    cell_energy_edeption.resize(Geometry::ncell_x * Geometry::ncell_y);

    Link_tree_branches();

    calorimeter_data = new TTree("calorimeter_data", "calorimeter_data");
    calorimeter_data->Branch("initial_particle_energy", &initial_energy);
    calorimeter_data->Branch("cell_energy", &cell_energy_edeption);
    calorimeter_data->Branch("initial_x", &initial_x);
    calorimeter_data->Branch("initial_y", &initial_y);
    calorimeter_data->Branch("electron_px", &electron_px);
    calorimeter_data->Branch("electron_py", &electron_py);
    calorimeter_data->Branch("electron_pz", &electron_pz);
    calorimeter_data->Branch("electron_p0", &electron_p0);
    calorimeter_data->Branch("positron_px", &positron_px);
    calorimeter_data->Branch("positron_py", &positron_py);
    calorimeter_data->Branch("positron_pz", &positron_pz);
    calorimeter_data->Branch("positron_p0", &positron_p0);
    calorimeter_data->Branch("gamma_px", &gamma_px);
    calorimeter_data->Branch("gamma_py", &gamma_py);
    calorimeter_data->Branch("gamma_pz", &gamma_pz);
    calorimeter_data->Branch("gamma_p0", &gamma_p0);
    calorimeter_data->Branch("chi_c_mass_before_rotating", &chi_c_mass_before_rotating);
    calorimeter_data->Branch("chi_c_pt_before_rotating", &chi_c_pt_before_rotating);
    calorimeter_data->Branch("event_branching", &branching);

    return;
}

void ROOTWriter::Refresh_data()
{

    for (G4int i = 0; i < cell_energy_edeption.size(); ++i){
        cell_energy_edeption[i] = 0.;
    }   

    initial_x = 0;
    initial_y = 0;

    electron_px = 0;
    electron_py = 0;
    electron_pz = 0;
    electron_p0 = 0;

    positron_px = 0;
    positron_py = 0;
    positron_pz = 0;
    positron_p0 = 0;

    gamma_px = 0;
    gamma_py = 0;
    gamma_pz = 0;
    gamma_p0 = 0;

    chi_c_mass_before_rotating = 0;
    chi_c_pt_before_rotating = 0;

    return;
}

void ROOTWriter::Set_beam_positin(G4double bx, G4double by){
    initial_x = bx;
    initial_y = by;
}

void ROOTWriter::Incr_energy_edept(G4int cellx, G4int celly, G4double en_ed){

    cell_energy_edeption[cellx * Geometry::ncell_x + celly] += en_ed;

    return;
}

void ROOTWriter::Set_init_data(G4double energy){

    initial_energy = energy;

    return;
}

void ROOTWriter::Link_tree_branches(){

    pythia_data->SetBranchAddress("electron_px", &electron_px);
    pythia_data->SetBranchAddress("electron_py", &electron_py);
    pythia_data->SetBranchAddress("electron_pz", &electron_pz);
    pythia_data->SetBranchAddress("electron_p0", &electron_p0);

    pythia_data->SetBranchAddress("positron_px", &positron_px);
    pythia_data->SetBranchAddress("positron_py", &positron_py);
    pythia_data->SetBranchAddress("positron_pz", &positron_pz);
    pythia_data->SetBranchAddress("positron_p0", &positron_p0);

    pythia_data->SetBranchAddress("gamma_px", &gamma_px);
    pythia_data->SetBranchAddress("gamma_py", &gamma_py);
    pythia_data->SetBranchAddress("gamma_pz", &gamma_pz);
    pythia_data->SetBranchAddress("gamma_p0", &gamma_p0);

    pythia_data->SetBranchAddress("event_branching", &branching);

    return;
}

void ROOTWriter::Get_tree_entry(G4int ientry){
    pythia_data->GetEntry(ientry);

    TLorentzVector* elec = new TLorentzVector(electron_px, electron_py, electron_pz, electron_p0);
    TLorentzVector* posi = new TLorentzVector(positron_px, positron_py, positron_pz, positron_p0);
    TLorentzVector* gamm = new TLorentzVector(gamma_px, gamma_py, gamma_pz, gamma_p0);

    chi_c_mass_before_rotating = (*elec + *posi + *gamm).M();
    chi_c_pt_before_rotating = (*elec + *posi + *gamm).Pt();

    return;
}

void ROOTWriter::Inc_event_counter(){
    ++event_counter;
}

G4int ROOTWriter::Get_tree_entries(){
    return pythia_data->GetEntries();
}

G4int ROOTWriter::Get_event_counter(){
    return event_counter;
}

G4double ROOTWriter::Get_photon_energy(){
    return gamma_p0;
}

G4bool ROOTWriter::Check_acceptance(){
    G4double eta = 0.5*TMath::Log((TMath::Sqrt(gamma_px * gamma_px + gamma_py * gamma_py + gamma_pz * gamma_pz) + gamma_pz)/(TMath::Sqrt(gamma_px * gamma_px + gamma_py * gamma_py + gamma_pz * gamma_pz) - gamma_pz));
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
    delete input_file;

    return;
}
