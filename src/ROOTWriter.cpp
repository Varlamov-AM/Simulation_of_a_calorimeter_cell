#include "ROOTWriter.hh"
#include "G4UImanager.hh"
#include "TRandom.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"

ROOTWriter* ROOTWriter::pInstance=0;

void ROOTWriter::Initialize(){

    if (output_hist_file == 0){
        output_hist_file = 
            new TFile("Calorimeter_cell_energy_edeption_data_in_histogram.root",
                      "RECREATE");
    }

    if (output_tree_file == 0){
        output_tree_file = 
            new TFile("Calorimeter_cell_energy_edeption_data_in_tree.root",
                      "RECREATE");
    }

    output_hist_file->cd();

    if (prime_edeption_hist == 0){
        prime_edeption_hist = new TH2D("Prime_energy_edeption_in_calorimeter_cell",
                        "Energy edeption in calorimeter cell in GeV", 
                        200, 0., 50.,
                        2500, 0., 50.);
    }

    if (smear_edeption_hist == 0){
        smear_edeption_hist = new TH2D("Smear_energy_edeption_in_calorimeter_cell",
                        "Energy edeption in calorimeter cell in GeV", 
                        200, 0., 50.,
                        2500, 0., 50.);
    }

    if (prime_optic_photons == 0){
        prime_optic_photons = new TH2D("Prime_optic_photons_spectrum",
                        "Optic photons spectrum", 
                        200, 0., 50.,
                        50000, 0., 50000.);
    }

    if (smear_optic_photons == 0){
        smear_optic_photons = new TH2D("Smear_optic_photons_spectrum",
                        "Optic photons spectrum", 
                        200, 0., 50.,
                        50000, 0., 50000.);
    }

    output_tree_file->cd();

    energy_tree = new TTree("energy_tree", 
                            "energy edepted in calorimeter cell");

    TBranch* Edepted_enery = energy_tree->Branch("Edepted_energy", 
                                                  &edepted_particle_energy);
    
    rndm = new TRandom();  
    rndm->SetSeed(0);

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

    prime_edeption_hist->
        Fill(real_particle_energy / GeV, edepted_particle_energy/ GeV);
    
    G4int n_pr_opt_photons = 
        (int)(edepted_particle_energy * optic_photons_energy_rate);

    prime_optic_photons->
        Fill(real_particle_energy / GeV, n_pr_opt_photons);

    G4int n_sm_opt_photons = rndm->Poisson(n_pr_opt_photons);

    smear_optic_photons->
        Fill(real_particle_energy / GeV, n_sm_opt_photons);
    
    smear_edeption_hist->
        Fill(real_particle_energy / GeV, edepted_particle_energy/(0.9 * GeV));

    energy_tree->Fill();

    Refresh_data();

    return;
};

void ROOTWriter::Finalize(){

    output_hist_file->cd();
    prime_edeption_hist->Write();
    smear_edeption_hist->Write();
    prime_optic_photons->Write();
    smear_optic_photons->Write();
    output_tree_file->cd();
    energy_tree->Write();

    delete prime_edeption_hist;
    delete smear_edeption_hist;
    delete prime_optic_photons;
    delete smear_optic_photons;
    delete energy_tree;
    delete output_hist_file;
    delete output_tree_file;

    return;
};
