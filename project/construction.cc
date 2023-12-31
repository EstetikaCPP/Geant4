#include "construction.hh"

#include <iostream>
#include <string>

using namespace std;

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

    G4String s_material;
    G4double s_thickness;
    

    ifstream file;
    file.open("/home/user/soft/project/parameters.txt");

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << std::endl;
        
    }

    string line;
    vector<std::string> words;
    
    while (getline(file, line)) {
        // Разбиваем строку на слова с использованием пробелов как разделителей
        istringstream iss(line);
        string word;
        
        while (iss >> word) {
            words.push_back(word);
        }
    }

    file.close();

    // Проверяем, есть ли слова в векторе
    if (!words.empty()) {
        // Последнее слово находится в конце вектора
        s_material = string(words[3]);
        s_thickness = stod(string(words[5]));
    } 
    else {
        cout << "Файл пустой или не содержит слов." << std::endl;
    }



    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *object = nist->FindOrBuildMaterial(s_material);
    G4Material *generator = nist->FindOrBuildMaterial("G4_Pb");
    

    G4Box *solidWorld = new G4Box("solidWorld", 1.*m, 1.*m, 1.5*m);
    G4Box *solidObject = new G4Box("solidObject", 0.8*m, 0.8*m, s_thickness*cm);
    G4Cons *solidGenerator = new G4Cons("solidGenerator", 0.*cm, 5.*cm, 0.*cm, 25.*cm, 40.*cm, 0.*deg, 360.*deg);

    G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4LogicalVolume *logicalObject = new G4LogicalVolume(solidObject, object, "logicalObject");
    G4LogicalVolume *logicalGenerator = new G4LogicalVolume(solidGenerator, generator, "logicalGenerator");

    G4VisAttributes *objectVisAttr = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 1.));
    objectVisAttr->SetForceSolid(true);
    logicalObject->SetVisAttributes(objectVisAttr);

    G4VisAttributes *generatorVisAttr = new G4VisAttributes(G4Colour(0.5, 0.5, 0.9, 1.));
    generatorVisAttr->SetForceSolid(true);
    logicalGenerator->SetVisAttributes(generatorVisAttr);

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physWorld", 0, false, 0, true);
    
    G4VPhysicalVolume *physObject = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.7*m), logicalObject, "physObject", logicalWorld, false, 0, true);

    G4VPhysicalVolume *physGenerator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.5*m), logicalGenerator, "physGenerator", logicalWorld, false, 0, true);
    
    return physWorld;
}

