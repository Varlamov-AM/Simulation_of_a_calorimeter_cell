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
    G4Material* PbW04 = DefineMaterial("PbWO4");

    G4double cell_x = 40*cm/2;
    G4double cell_y = 40*cm/2;
    G4double cell_z  = 18*cm/2;
  
    G4Box* solid_World =    
        new G4Box("World", world_x, world_y, world_z);

    G4LogicalVolume* logic_World =                         
        new G4LogicalVolume(solid_World, air, "World");

    G4VPhysicalVolume* phys_World = 
        new G4PVPlacement(0,                     
                          G4ThreeVector(),       
                          logic_World,            
                          "World",               
                          0,                     
                          false,                 
                          0,                     
                          checkOverlaps);

    G4Box* solid_Calorimeter_cell = 
        new G4Box("Calorimeter_cell", cell_x, cell_y, cell_z);
      
    G4LogicalVolume* logic_Calorimeter_cell = 
        new G4LogicalVolume(solid_Calorimeter_cell, PbW04, "Calorimeter_cell");

    G4VPhysicalVolume* phys_Calorimeter_cell = 
        new G4PVPlacement(0, 
                          G4ThreeVector(0, 0, cell_z),
                          logic_Calorimeter_cell,
                          "Calorimeter_cell",
                          logic_World, 
                          false, 
                          0,
                          checkOverlaps);
                                   
    

    Detector* Cal_cell = new Detector("Cal_cell");
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(Cal_cell);
    logic_Calorimeter_cell->SetSensitiveDetector(Cal_cell);

    return phys_World;

}


G4Material* Geometry::DefineMaterial(G4String material){
  

    G4NistManager* nist = G4NistManager::Instance();
    
    G4Material* mat = 0;
  
    mat = nist->FindOrBuildMaterial(material);
        if (mat != 0){return mat;}

    if (material == "PbWO4"){
        
        G4Element* Pb = nist->FindOrBuildElement("Pb");
        G4Element* W = nist->FindOrBuildElement("W");
        G4Element* O = nist->FindOrBuildElement("O");

        G4int nel;
        G4int natoms;

        mat = new G4Material("PbWO4", 8.28*g/cm3, nel = 3);
        
        mat->AddElement(Pb, natoms = 1);
        mat->AddElement(W,  natoms = 1);
        mat->AddElement(O,  natoms = 4);

    } else {
        G4cerr << "Unknown material: " << material << G4endl;
    }
  
  return mat;
}
