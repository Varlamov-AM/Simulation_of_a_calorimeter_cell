#ifndef RootWriter_H
#define RootWriter_H 1
#include "G4Types.hh"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include <string>
#include <iostream>
#include "G4SystemOfUnits.hh"

using namespace std;

class ROOTWriter{
  
public:
  
  static ROOTWriter* GetPointer(){
    if(pInstance==0) pInstance = new ROOTWriter();
    return pInstance;
  };

  void Incr_energy_edept(G4double);

  void Set_init_data(G4double);

  void Refresh_data();
  
  void Initialize(); 
  
  void Fill();    
  
  void Finalize();

  TRandom* rndm;

private:


  TFile* output_hist_file = 0;
  TFile* output_tree_file = 0;

  TTree* energy_tree = 0;

  TH2D*  prime_edeption_hist = 0;
  TH2D*  smear_edeption_hist = 0;
  TH2D*  prime_optic_photons = 0;
  TH2D*  smear_optic_photons = 0;
  
  G4double optic_photons_energy_rate = 0.9; // MeV^{-1}
  G4double real_particle_energy = 0;
  G4double edepted_particle_energy = 0;

  static ROOTWriter* pInstance;

};

#endif
