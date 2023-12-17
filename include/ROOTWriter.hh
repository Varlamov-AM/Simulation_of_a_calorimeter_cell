#ifndef RootWriter_H
#define RootWriter_H 1
#include "G4Types.hh"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include <string>
#include <iostream>
#include "G4SystemOfUnits.hh"
#include "Geometry.hh"

using namespace std;

class ROOTWriter{
  
public:

    static ROOTWriter* GetPointer(){
    if(pInstance==0) pInstance = new ROOTWriter();
    return pInstance;
    };

    void Incr_energy_edept(G4int, G4int, G4double);

    void Link_tree_branches();

    void Get_tree_entry(G4int);

    void Set_init_data(G4double);

    void Set_beam_positin(G4double, G4double);

    void Refresh_data();

    void Initialize(); 

    void Fill();    

    void Finalize();

    void Inc_event_counter();

    G4int Get_tree_entries();

    G4int Get_event_counter();
    
    G4double Get_photon_energy();

    G4bool Check_acceptance();

private:


    TFile* output_file = 0;
    TFile* input_file = 0;  
    TTree* calorimeter_data = 0;
    TTree* pythia_data = 0;

    G4double branching = 0;

    G4double electron_px = 0;
    G4double electron_py = 0;
    G4double electron_pz = 0;
    G4double electron_p0 = 0;

    G4double positron_px = 0;
    G4double positron_py = 0;
    G4double positron_pz = 0;
    G4double positron_p0 = 0;

    G4double gamma_px = 0;
    G4double gamma_py = 0;
    G4double gamma_pz = 0;
    G4double gamma_p0 = 0;

    G4double chi_c_mass_before_rotating = 0;
    G4double chi_c_pt_before_rotating = 0;

    G4int event_counter = 0;

    std::vector<G4double> cell_energy_edeption;
    G4double initial_energy = 0;
    G4double initial_x = 0;
    G4double initial_y = 0;

    TH2D* mass_chic = new TH2D("mass_chic", "mass_chic", 100, 3.2, 3.8, 10, 0., 10.);

    static ROOTWriter* pInstance;

};

#endif
