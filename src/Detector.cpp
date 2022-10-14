#include "Detector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "ROOTWriter.hh"

using namespace CLHEP;

Detector::Detector(const G4String& name) : G4VSensitiveDetector(name){};

Detector::~Detector(){};

void Detector::Initialize(G4HCofThisEvent* hce){};

G4bool Detector::ProcessHits(G4Step* step, G4TouchableHistory*){

    if (SensitiveDetectorName == "Cal_cell"){
        // G4cout << "oh my god, my detector was heated!" << G4endl;
        G4double edep_energy_on_step = 
            step->GetTotalEnergyDeposit();
        ROOTWriter::GetPointer()->Incr_energy_edept(edep_energy_on_step);
    }

    return true;
};

void Detector::EndOfEvent(G4HCofThisEvent*){};
