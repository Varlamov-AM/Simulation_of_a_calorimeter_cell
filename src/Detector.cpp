#include "Detector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "ROOTWriter.hh"
#include <iostream>

using namespace CLHEP;

Detector::Detector(const G4String& name) : G4VSensitiveDetector(name){};

Detector::~Detector(){};

void Detector::Initialize(G4HCofThisEvent* hce){};

G4bool Detector::ProcessHits(G4Step* step, G4TouchableHistory*){
  return true;
};

void Detector::EndOfEvent(G4HCofThisEvent*){};
