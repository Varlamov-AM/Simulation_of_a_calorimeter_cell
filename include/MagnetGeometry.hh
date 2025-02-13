#ifndef MagnetGeometry_h
#define MagnetGeometry_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include <vector>

class G4VPhysicalVolume;

class MagnetGeometry : public G4VPVParameterisation {

public:

    MagnetGeometry(G4int);
    ~MagnetGeometry() override = default;

    void ComputeTransformation(const G4int copyNo,G4VPhysicalVolume *physVol) 
        const override;

    std::vector<G4double> platePositions;

private:

    G4int nplates;
    G4double platesGap;

};

#endif