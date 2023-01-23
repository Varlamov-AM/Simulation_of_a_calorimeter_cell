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
        const G4int nbinsy = 2500;
        G4double* hist_bining = new G4double[nbinsy + 1];
        for (G4int i= 0; i <= nbinsy; i++){
            if (i <= 500){
                hist_bining[i] = (1. / 500) * i;
            } else {
                hist_bining[i] = 1. + (49. / 2000) * (i - 500);
            }
        }
        energy_edeption_hist = new TH2D("Energy_edeption_in_calorimeter_cell",
                        "Hadrons energy edeption in calorimeter cell in GeV", 
                        200, 0., 50.,
                        nbinsy, hist_bining);
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
        Fill(real_particle_energy / GeV, edepted_particle_energy/ GeV);
    Refresh_data();

    return;
};

void ROOTWriter::Finalize(){

    output_file->cd();
    energy_edeption_hist->Write();

    delete energy_edeption_hist;
    delete output_file;

    return;
};
