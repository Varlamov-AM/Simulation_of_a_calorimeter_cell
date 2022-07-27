#ifndef Geometry_h
#define Geometry_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class Geometry : public G4VUserDetectorConstruction{
  public:

  Geometry();

  virtual ~Geometry();
  
  virtual G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
  
  G4Material* DefineMaterial(G4String material);
  
protected:

  G4LogicalVolume*  fScoringVolume;

private:
  
};

#endif
