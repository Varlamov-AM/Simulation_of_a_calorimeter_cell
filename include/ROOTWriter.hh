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
  
  void Initialize(); // initialization method. Declare in ROOTWriter.cc
  
  void Fill();    
  
  void Finalize();
  
private:

  static ROOTWriter* pInstance;

};

#endif
