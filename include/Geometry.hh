#ifndef Geometry_h
#define Geometry_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "TString.h"
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

	const static G4int ncell_x = 5;
    const static G4int ncell_y = 5;
	TString cell_sens_name[ncell_x][ncell_y];
  
protected:

  	G4LogicalVolume*  fScoringVolume;

private:

	G4double world_x = 50*cm;
	G4double world_y = 50*cm;
	G4double world_z = 160*cm;

  
};

#endif
