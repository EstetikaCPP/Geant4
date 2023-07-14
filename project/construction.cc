#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *object = nist->FindOrBuildMaterial("G4_Al");

    G4Box *solidWorld = new G4Box("solidWorld", 1.*m, 1.*m, 1.5*m);
    G4Box *solidObject = new G4Box("solidObject", 0.8*m, 0.8*m, 1.*cm);

    G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4LogicalVolume *logicalObject = new G4LogicalVolume(solidObject, object, "logicalObject");

    G4VisAttributes *objectVisAttr = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 1.));
    objectVisAttr->SetForceSolid(true);
    logicalObject->SetVisAttributes(objectVisAttr);

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physWorld", 0, false, 0, true);
    G4VPhysicalVolume *physObject = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.7*m), logicalObject, "physObject", logicalWorld, false, 0, true);
    
    return physWorld;
}

