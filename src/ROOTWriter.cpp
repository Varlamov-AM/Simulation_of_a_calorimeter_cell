#include "ROOTWriter.hh"
#include "G4UImanager.hh"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"

ROOTWriter* ROOTWriter::pInstance=0;

void ROOTWriter::Initialize(){
    if (output_file == 0){
        output_file = 
            new TFile("Calorimeter_cell_energy_edeption_data.root",
                      "RECREATE");
    }

    if (energy_edeption_hist == 0){
        energy_edeption_hist = 
            new TH2D("Energy_edeption_in_calorimeter_cell",
                     "Hadrons energy edeption in calorimeter cell in MeV",
                     1000, 0., 1000., 
                     1000, 0., 1000.);
    }

    return;
};

void ROOTWriter::Set_init_data(G4double real_energy){

    real_particle_energy = real_energy;

    return;
}

void ROOTWriter::Incr_energy_edept(G4double local_edept){

    edepted_particle_energy += local_edept;

    return;
}

void ROOTWriter::Refresh_data(){

    real_particle_energy = 0;
    edepted_particle_energy = 0;

    return;
}

void ROOTWriter::Fill(){

    energy_edeption_hist->
        Fill(real_particle_energy, edepted_particle_energy);
    Refresh_data();

    return;
};

void ROOTWriter::Finalize(){

    output_file->cd();
    energy_edeption_hist->Write();

    return;
};
