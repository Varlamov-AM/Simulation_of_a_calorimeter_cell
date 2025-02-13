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
#include "G4AssemblyVolume.hh"
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
    G4Material* cooper = DefineMaterial("Cooper");
    G4Material* carbon = DefineMaterial("Carbon");
    G4Material* PbW04 = DefineMaterial("PbWO4");


    G4double cell_x = 22*mm/2;
    G4double cell_y = 22*mm/2;
    G4double cell_z  = 18*cm/2;

    G4double cu_layer_1_pos = 0*mm;
    G4double cu_layer_1_wid = 1.5*mm/2;

    G4double al_layer_1_pos = 5*mm;
    G4double al_layer_1_wid = 5*mm/2;

    G4double he_layer_1_pos = 10*mm;
    G4double he_layer_1_wid = 180*mm/2;

    G4double al_layer_2_pos = 190*mm;
    G4double al_layer_2_wid = 15*mm/2;

    G4double c_layer_1_pos = 207*mm;
    G4double c_layer_1_wid = 5*mm/2;

    G4double al_layer_3_pos = 213*mm;
    G4double al_layer_3_wid = 15*mm/2;

    G4double al_layer_4_pos = 228*mm;
    G4double al_layer_4_wid = 10*mm/2;

    G4cout << 4 * cu_layer_1_wid/(cooper->GetRadlen()) + 4 * (al_layer_1_wid + al_layer_2_wid + al_layer_3_wid + al_layer_4_wid)/(aluminium->GetRadlen()) + 4 * (c_layer_1_wid)/(carbon->GetRadlen())  + 4 * (he_layer_1_wid)/(liquidHe->GetRadlen()) << "\n";
    G4cout << "Rad lenght: " << cooper->GetRadlen() << " " << aluminium->GetRadlen() << " " << carbon->GetRadlen() << " " << liquidHe->GetRadlen() << "\n";
    



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

    // // Create cooper, aluminium, liquid helium and carbon layer

    // G4Box* solid_cu_layer_1 = 
    //     new G4Box("al_layer_1", world_x, world_y, cu_layer_1_wid);

    // G4LogicalVolume* logic_cu_layer_1 = 
    //     new G4LogicalVolume(solid_cu_layer_1, cooper, "logic_cu_layer_1");

    // G4VPhysicalVolume* phys_cu_layer_1 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, cu_layer_1_pos + cu_layer_1_wid), "phys_cu_layer_1",  logic_cu_layer_1, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_he_layer_1 = 
    //     new G4Box("he_layer_1", world_x, world_y, he_layer_1_wid);

    // G4LogicalVolume* logic_he_layer_1 = 
    //     new G4LogicalVolume(solid_he_layer_1, liquidHe, "logic_he_layer_1");

    // G4VPhysicalVolume* phys_he_layer_1 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0,he_layer_1_pos + he_layer_1_wid), "phys_he_layer_1",  logic_he_layer_1, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_1 = 
    //     new G4Box("al_layer_1", world_x, world_y, al_layer_1_wid);

    // G4LogicalVolume* logic_al_layer_1 = 
    //     new G4LogicalVolume(solid_al_layer_1, aluminium, "logic_al_layer_1");

    // G4VPhysicalVolume* phys_al_layer_1 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, al_layer_1_pos + al_layer_1_wid), "phys_al_layer_1",  logic_al_layer_1, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_2 = 
    //     new G4Box("al_layer_2", world_x, world_y, al_layer_2_wid);

    // G4LogicalVolume* logic_al_layer_2 = 
    //     new G4LogicalVolume(solid_al_layer_2, aluminium, "logic_al_layer_2");

    // G4VPhysicalVolume* phys_al_layer_2 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, al_layer_2_pos + al_layer_2_wid ), "phys_al_layer_2",  logic_al_layer_2, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_c_layer_1 = 
    //     new G4Box("c_layer_1", world_x, world_y, c_layer_1_wid);

    // G4LogicalVolume* logic_c_layer_1 = 
    //     new G4LogicalVolume(solid_c_layer_1, carbon, "logic_c_layer_1");

    // G4VPhysicalVolume* phys_c_layer_1 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, c_layer_1_pos + c_layer_1_wid ), "phys_c_layer_1",  logic_c_layer_1, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_3 = 
    //     new G4Box("al_layer_3", world_x, world_y, al_layer_3_wid);

    // G4LogicalVolume* logic_al_layer_3 = 
    //     new G4LogicalVolume(solid_al_layer_3, aluminium, "logic_al_layer_3");

    // G4VPhysicalVolume* phys_al_layer_3 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, al_layer_3_pos + al_layer_3_wid + 0.01), "phys_al_layer_3",  logic_al_layer_3, phys_World, false, 0, checkOverlaps);
    
    // G4Box* solid_al_layer_4 = 
    //     new G4Box("al_layer_4", world_x, world_y, al_layer_4_wid    );

    // G4LogicalVolume* logic_al_layer_4 = 
    //     new G4LogicalVolume(solid_al_layer_4, aluminium, "logic_al_layer_4");

    // G4VPhysicalVolume* phys_al_layer_4 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, al_layer_4_pos + al_layer_4_wid + 0.01), "phys_al_layer_4",  logic_al_layer_4, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_cu_layer_2 = 
    //     new G4Box("al_layer_2", world_x, world_y, cu_layer_1_wid);

    // G4LogicalVolume* logic_cu_layer_2 = 
    //     new G4LogicalVolume(solid_cu_layer_2, cooper, "logic_cu_layer_2");

    // G4VPhysicalVolume* phys_cu_layer_2 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -cu_layer_1_pos - cu_layer_1_wid), "phys_cu_layer_2",  logic_cu_layer_2, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_he_layer_2 = 
    //     new G4Box("he_layer_2", world_x, world_y, he_layer_1_wid);

    // G4LogicalVolume* logic_he_layer_2 = 
    //     new G4LogicalVolume(solid_he_layer_2, liquidHe, "logic_he_layer_2");

    // G4VPhysicalVolume* phys_he_layer_2 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -he_layer_1_pos - he_layer_1_wid), "phys_he_layer_2",  logic_he_layer_2, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_5 = 
    //     new G4Box("al_layer_5", world_x, world_y, al_layer_1_wid);

    // G4LogicalVolume* logic_al_layer_5 = 
    //     new G4LogicalVolume(solid_al_layer_5, aluminium, "logic_al_layer_5");

    // G4VPhysicalVolume* phys_al_layer_5 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -al_layer_1_pos - al_layer_1_wid), "phys_al_layer_5",  logic_al_layer_5, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_6 = 
    //     new G4Box("al_layer_6", world_x, world_y, al_layer_2_wid);

    // G4LogicalVolume* logic_al_layer_6 = 
    //     new G4LogicalVolume(solid_al_layer_6, aluminium, "logic_al_layer_6");

    // G4VPhysicalVolume* phys_al_layer_6 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -al_layer_2_pos - al_layer_2_wid ), "phys_al_layer_6",  logic_al_layer_6, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_c_layer_2 = 
    //     new G4Box("c_layer_2", world_x, world_y, c_layer_1_wid);

    // G4LogicalVolume* logic_c_layer_2 = 
    //     new G4LogicalVolume(solid_c_layer_2, carbon, "logic_c_layer_2");

    // G4VPhysicalVolume* phys_c_layer_2 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -c_layer_1_pos - c_layer_1_wid ), "phys_c_layer_2",  logic_c_layer_2, phys_World, false, 0, checkOverlaps);

    // G4Box* solid_al_layer_7 = 
    //     new G4Box("al_layer_7", world_x, world_y, al_layer_3_wid);

    // G4LogicalVolume* logic_al_layer_7 = 
    //     new G4LogicalVolume(solid_al_layer_7, aluminium, "logic_al_layer_7");

    // G4VPhysicalVolume* phys_al_layer_7 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -al_layer_3_pos - al_layer_3_wid - 0.01), "phys_al_layer_7",  logic_al_layer_7, phys_World, false, 0, checkOverlaps);
    
    // G4Box* solid_al_layer_8 = 
    //     new G4Box("al_layer_8", world_x, world_y, al_layer_4_wid);

    // G4LogicalVolume* logic_al_layer_8 = 
    //     new G4LogicalVolume(solid_al_layer_8, aluminium, "logic_al_layer_8");

    // G4VPhysicalVolume* phys_al_layer_8 = 
    //     new G4PVPlacement(0, G4ThreeVector(0, 0, -al_layer_4_pos - al_layer_4_wid - 0.01), "phys_al_layer_8",  logic_al_layer_8, phys_World, false, 0, checkOverlaps);
    
    
    // Create calorimeter (cells array);
    // Create ncell_x x ncell_y calorimeter with 22 mm cells.
    
    G4Box* solid_calorimeter_cell = 
        new G4Box("Calorimeter_cell", cell_x, cell_y, cell_z);

    G4LogicalVolume* logic_calorimeter_cell = 
        new G4LogicalVolume(solid_calorimeter_cell, PbW04, "logic_call_cell");

    G4AssemblyVolume* assembly_cell = new G4AssemblyVolume();

    G4RotationMatrix cell_rotation;

    for (G4int x_pos = 0; x_pos < ncell_x; ++x_pos){
        G4ThreeVector cell_transl((-(ncell_x/2) + x_pos) * cell_x * 2, 0, 0);
        G4Transform3D cell_transform(cell_rotation, cell_transl);
        assembly_cell->
            AddPlacedVolume(logic_calorimeter_cell, cell_transform);
    }
    
    for (G4int y_pos = 0; y_pos < ncell_y; ++y_pos){
        G4RotationMatrix cal_rotation;
        G4ThreeVector cell_position(0, 
                                    (-(ncell_y/2) + y_pos) * cell_y * 2, 
                                    250*mm + cell_z + 10*cm);
        G4Transform3D curr_cell_transform(cal_rotation, cell_position);
        assembly_cell->MakeImprint(logic_World, curr_cell_transform);
    }
    

    Detector* calorimeter;
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    G4String calorimeter_name = "calorimeter";
    calorimeter = 
        new Detector(calorimeter_name);
    SDman->AddNewDetector(calorimeter);
    logic_calorimeter_cell->SetSensitiveDetector(calorimeter);


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

    } else if (material == "Cooper"){

        G4Element* Cu = nist->FindOrBuildElement("Cu");

        G4int nel;
        G4int natoms;

        mat = new G4Material("Cooper", 8.9*g/cm3, nel = 1);

        mat->AddElement(Cu, natoms = 1);

    }  else if (material == "Carbon"){

        G4Element* C = nist->FindOrBuildElement("C");

        G4int nel;
        G4int natoms;

        mat = new G4Material("Carbon", 1.5*g/cm3, nel = 1);

        mat->AddElement(C, natoms = 1);

    } else {
        G4cerr << "Unknown material: " << material << G4endl;
    }
  
  return mat;
}
