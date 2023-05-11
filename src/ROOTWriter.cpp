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

    if (output_file == 0){
        output_file = 
            new TFile("Calorimeter_energy_edeption_data.root",
                      "RECREATE");
    }

    cell_energy_edeption.resize(Geometry::ncell_x * Geometry::ncell_y);

    calorimeter_data = new TTree("calorimeter_data", "calorimeter_data");
    calorimeter_data->Branch("initial_particle_energy", &initial_energy);
    calorimeter_data->Branch("cell_energy", &cell_energy_edeption);

    return;
}

void ROOTWriter::Refresh_data()
{

    for (G4int i = 0; i < cell_energy_edeption.size(); ++i){
        cell_energy_edeption[i] = 0.;
    }   

    return;
}

void ROOTWriter::Incr_energy_edept(G4int cellx, G4int celly, G4double en_ed){

    cell_energy_edeption[cellx * Geometry::ncell_x + celly] += en_ed;

    return;
}

void ROOTWriter::Set_init_data(G4double energy){

    initial_energy = energy;

    return;
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

    return;
}
