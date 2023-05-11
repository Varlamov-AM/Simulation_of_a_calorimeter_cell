#include "Geometry.hh"
#include "MagnetGeometry.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "Detector.hh"
#include "TString.h"

using namespace CLHEP;

Geometry::Geometry() 
  : G4VUserDetectorConstruction(), fScoringVolume(0){}

Geometry::~Geometry(){}

G4VPhysicalVolume* Geometry::Construct(){ 

 
    G4bool checkOverlaps = true;

    G4int n_al_plates_in_magnet = 21;

    G4Material* air = DefineMaterial("G4_AIR");
    G4Material* liquidHe = DefineMaterial("liquidHe");
    G4Material* aluminium = DefineMaterial("Aluminium");
    G4Material* PbW04 = DefineMaterial("PbWO4");

    G4double cell_x = 22*mm/2;
    G4double cell_y = 22*mm/2;
    G4double cell_z  = 18*cm/2;

    G4double magnet_x = 40*cm/2;
    G4double magnet_y = 40*cm/2;
    G4double magnet_z = 52*cm/2;

    G4double al_x = 40*cm/2;
    G4double al_y = 40*cm/2;
    G4double al_z = 0.21*cm;

    G4cout << al_z << "\n";

    // Create world
  
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

    // Create magnet

    G4Box* solid_magnet = 
        new G4Box("Magnet", magnet_x, magnet_y, magnet_z);

    G4LogicalVolume* logic_magnet = 
        new G4LogicalVolume(solid_magnet, liquidHe, "Magnet");

    G4cout << liquidHe << "\n";

    G4VPhysicalVolume* phys_magnet = 
        new G4PVPlacement(0, 
                          G4ThreeVector(0, 0, magnet_z), 
                          logic_magnet, 
                          "Magnet",
                          logic_World,
                          false, 
                          0, 
                          checkOverlaps);

    // Create magnets inner aluminium plates

    G4Box* solid_plate = 
        new G4Box("Aluminium_plate", al_x, al_y, al_z);

    G4LogicalVolume* logic_plate = 
        new G4LogicalVolume(solid_plate, aluminium, "logic_al_plate");

    G4cout << aluminium << "\n";

    G4VPVParameterisation* plates_parametrisation = 
        new MagnetGeometry(n_al_plates_in_magnet);

    G4VPhysicalVolume* phys_plates = 
        new G4PVParameterised("Aluminium_plates",
                              logic_plate, 
                              logic_magnet, 
                              kZAxis, 
                              n_al_plates_in_magnet, 
                              plates_parametrisation, 
                              checkOverlaps);

    // Create calorimeter (cells array);

    // First attempt to create cell structure of calorimeter.
    // Create ncell_x x ncell_y calorimeter with 22 mm cells.
    

   G4Box* solid_calorimeter_cells[ncell_x][ncell_y];
   TString solid_cell_name[ncell_x][ncell_y];

    for (G4int cx = 0; cx < ncell_x; ++cx){
        for (G4int cy = 0; cy < ncell_y; ++cy){
            solid_cell_name[cx][cy] = 
                Form("Calorimeter_cell_solid_column_%d_row_%d", cx, cy);
            solid_calorimeter_cells[cx][cy] = 
                new G4Box(G4String(solid_cell_name[cx][cy].Data()), 
                          cell_x, 
                          cell_y, 
                          cell_z);
        }
    }
      
    G4LogicalVolume* logical_calorimeter_cells[ncell_x][ncell_y];
    TString logic_cell_name[ncell_x][ncell_y];

    for (G4int cx = 0; cx < ncell_x; ++cx){
        for (G4int cy = 0; cy < ncell_y; ++cy){
            logic_cell_name[cx][cy] = 
                Form("Calorimeter_cell_logic_column_%d_row_%d", cx, cy);
            logical_calorimeter_cells[cx][cy] = 
                new G4LogicalVolume(solid_calorimeter_cells[cx][cy], 
                                    PbW04, 
                                    G4String(logic_cell_name[cx][cy].Data()));
        }
    }

    G4cout << PbW04 << "\n";

    G4VPhysicalVolume* phys_calorimeter_cells[ncell_x][ncell_y];
    TString phys_cell_name[ncell_x][ncell_y];

    for (G4int cx = 0; cx < ncell_x; ++cx){
        for (G4int cy = 0; cy < ncell_y; ++cy){
            phys_cell_name[cx][cy] = 
                Form("Calorimeter_cell_phys_column_%d_row_%d", cx, cy);
            phys_calorimeter_cells[cx][cy] = 
                new G4PVPlacement(0, 
                                  G4ThreeVector((cx - 2) * cell_x * 2, 
                                                (cy - 2) * cell_y * 2,
                                                2*magnet_z + cell_z + 10*cm), 
                                  logical_calorimeter_cells[cx][cy],
                                  G4String(phys_cell_name[cx][cy].Data()), 
                                  logic_World, 
                                  false, 
                                  0, 
                                  checkOverlaps);
        }
    }

    Detector* calorimeter_cells[ncell_x][ncell_y];
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    for (G4int cx = 0; cx < ncell_x; ++cx){
        for (G4int cy = 0; cy < ncell_y; ++cy){
            cell_sens_name[cx][cy] = Form("Cell_%d_%d", cx, cy);
            calorimeter_cells[cx][cy] = 
                new Detector(G4String(cell_sens_name[cx][cy].Data()));
            SDman->AddNewDetector(calorimeter_cells[cx][cy]);
            logical_calorimeter_cells[cx][cy]->
                SetSensitiveDetector(calorimeter_cells[cx][cy]);
        }
    }

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

        
    } else if (material == "liquidHe"){
        G4Element* He = nist->FindOrBuildElement("He");

        G4int nel;
        G4int natoms;

        mat = new G4Material("liquidHe", 0.1249*g/cm3, nel = 1);

        mat->AddElement(He, natoms = 1);

    } else if (material == "Aluminium"){

        G4Element* Al = nist->FindOrBuildElement("Al");

        G4int nel;
        G4int natoms;

        mat = new G4Material("Aluminium", 2.7*g/cm3, nel = 1);

        mat->AddElement(Al, natoms = 1);

    } else {
        G4cerr << "Unknown material: " << material << G4endl;
    }
  
  return mat;
}
