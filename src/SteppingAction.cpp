#include "SteppingAction.hh"
#include "G4Step.hh"

#include <cmath>

using namespace CLHEP;

SteppingAction::SteppingAction() : G4UserSteppingAction(){};

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step){};
