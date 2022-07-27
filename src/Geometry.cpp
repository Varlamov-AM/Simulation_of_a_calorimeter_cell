#include "Geometry.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "Detector.hh"

using namespace CLHEP;

Geometry::Geometry() 
  : G4VUserDetectorConstruction(), fScoringVolume(0){};

Geometry::~Geometry(){};

G4VPhysicalVolume* Geometry::Construct(){ 

 
 G4bool checkOverlaps = true;

  G4Material* air = DefineMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld, air, "World");
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     
                      G4ThreeVector(),       
                      logicWorld,            
                      "World",               
                      0,                     
                      false,                 
                      0,                     
                      checkOverlaps);

  return physWorld;

}


G4Material* Geometry::DefineMaterial(G4String material){
  
  G4int ncomponents;
  G4double fractionmass;
  G4NistManager* nist = G4NistManager::Instance();
    
  G4Material* mat = 0;
  
  mat = nist->FindOrBuildMaterial(material);
  if (mat != 0)
    return mat;
  
  if (material == "Steel12H18N10T"){
      G4Element* Fe = nist->FindOrBuildElement("Fe");
      G4Element* Ni = nist->FindOrBuildElement("Ni");
      G4Element* Cr = nist->FindOrBuildElement("Cr");
      G4Element* Mn = nist->FindOrBuildElement("Mn");
      mat = new G4Material("Steel12H18N10T", 7.92*g/cm3, ncomponents=4);
      mat->AddElement(Fe, fractionmass=68*perCent);
      mat->AddElement(Ni, fractionmass=11*perCent);
      mat->AddElement(Cr, fractionmass=19*perCent);
      mat->AddElement(Mn, fractionmass=2*perCent);
  } else {
      G4cerr << "Unknown material: " << material << G4endl;
  }
  
  return mat;
}
