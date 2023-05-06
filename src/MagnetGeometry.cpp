#include "MagnetGeometry.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

MagnetGeometry::MagnetGeometry(G4int nPlates){

    nplates = nPlates;
    platePositions.resize(nplates);

    for (auto copyNo=0; copyNo < nplates; copyNo++) {
        platePositions[copyNo] = -25*cm + 0.21*cm + 2.5*cm*copyNo;
    }

}

void MagnetGeometry::ComputeTransformation(
       const G4int copyNo,G4VPhysicalVolume *physVol) const {
    physVol->SetTranslation(G4ThreeVector(0, 0, platePositions[copyNo]));
}
