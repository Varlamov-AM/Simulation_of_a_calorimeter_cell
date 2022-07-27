#include "EventAction.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "ROOTWriter.hh"

EventAction::EventAction() : G4UserEventAction(){};

EventAction::~EventAction(){};

void EventAction::BeginOfEventAction(const G4Event* event){

  G4long total = G4RunManager::GetRunManager()->GetCurrentRun()
    ->GetNumberOfEventToBeProcessed();
  fPrintModulo = G4int(total/20);
  if(fPrintModulo<1) fPrintModulo=1;

  G4int eventNb = event->GetEventID();
  if (eventNb%fPrintModulo == 0) { 
    G4cout << "\n---> Begin of event: " << eventNb << G4endl;
  }
}

void EventAction::EndOfEventAction(const G4Event*){   
    ROOTWriter::GetPointer()->Finalize(); 
}
