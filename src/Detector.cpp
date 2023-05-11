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

    for (G4int cx = 0; cx < Geometry::ncell_x; ++cx){
        for (G4int cy = 0; cy < Geometry::ncell_y; ++cy){
            if (SensitiveDetectorName == Form("Cell_%d_%d", cx, cy)){
                ROOTWriter::GetPointer()->
                    Incr_energy_edept(cx, cy, step->GetTotalEnergyDeposit());
            }
        }   
    }

    return true;
}

void Detector::EndOfEvent(G4HCofThisEvent*){}
