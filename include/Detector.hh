#ifndef D_h
#define D_h 1

#include "G4VSensitiveDetector.hh"
#include <vector>

class G4Step;

class G4HCofThisEvent;

class Detector : public G4VSensitiveDetector{
  
  public:

    Detector(const G4String& name);
  
    virtual ~Detector();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
  
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

};

#endif
