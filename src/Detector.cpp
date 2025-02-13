#include "Detector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "ROOTWriter.hh"
#include "Geometry.hh"
#include "TString.h"

using namespace CLHEP;

Detector::Detector(const G4String& name) : G4VSensitiveDetector(name){}

Detector::~Detector(){}

void Detector::Initialize(G4HCofThisEvent* hce){}

G4bool Detector::ProcessHits(G4Step* step, G4TouchableHistory*){


    if (SensitiveDetectorName == "calorimeter"){
        G4String cal_cell_phys_vol_name = 
            step->GetTrack()->GetTouchable()->GetVolume()->GetName();
        G4String cy_str= 
            cal_cell_phys_vol_name.substr(10, cal_cell_phys_vol_name.
                                                find("_", 10) - 10);
        G4String cx_str= 
            cal_cell_phys_vol_name.substr(
                cal_cell_phys_vol_name.find_last_of("_") + 1, 
                cal_cell_phys_vol_name.size());
        int cx = std::atoi(cx_str);
        int cy = std::atoi(cy_str) - 1;
        
        ROOTWriter::GetPointer()->
            Incr_energy_edept(cx, cy, step->GetTotalEnergyDeposit());
    }        

    return true;
}

void Detector::EndOfEvent(G4HCofThisEvent*){}
