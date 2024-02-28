#ifndef RootWriter_H
#define RootWriter_H 1
#include "G4Types.hh"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TChain.h"
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

    void Refresh_data();

    void Initialize(); 

    void Fill();    

    void Finalize();

    void Add_current_particle(G4int);

    void Inc_event_counter();

    void Resize_result_vectors();

    void Get_particle_in_event_by_number(G4int, std::vector<double>&);

    G4int Get_tree_entries();

    G4int Get_event_counter();

    G4int Get_event_size();
    
    G4bool Check_acceptance(G4double, G4double, G4double, G4double);

private:


    TFile* output_file = 0;
    TChain* input_chain = 0;  
    TTree* calorimeter_data = 0;

    G4int event_counter = 0;
    G4int particle_counter = 0;
    
    std::vector<std::vector<G4double>> cell_energy_edeption;
    std::vector<double> current_particle_edeption;

    std::vector<std::vector<double>>* event_data;
    std::vector<std::vector<double>> event_data_to_output;
    
    static ROOTWriter* pInstance;

};

#endif
