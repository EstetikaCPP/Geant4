#include "generator.hh"

#include <iostream>
#include <string>

using namespace std;


MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();

}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete particleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    

    G4int s_NumberOfParicles;

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
        s_NumberOfParicles = stoi(string(words[1]));
    } 
    else {
        cout << "Файл пустой или не содержит слов." << std::endl;
    }
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

// Установка количества частиц в пучке
    G4int numberOfParticlesInBeam = s_NumberOfParicles;
   // particleGun->SetNumberOfParticles(numberOfParticlesInBeam);

    
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0));

// Настройка пучкового распределения
    G4double beamSigma = 0.2*cm; // Сигма пучка
    G4double beamMomentum = 1.0*GeV; // Импульс пучка
    

    G4ThreeVector beamDirection(0.0, 0.0, -1.0); // Направление пучка
    
    G4double pi = 3.14159265358979323846;    

    for (G4int i = 0; i < numberOfParticlesInBeam; ++i){ 
        G4double beamTheta_1 = (pi/3) + (G4UniformRand() * (pi/3)); // Генерация угла
        G4double beamTheta_2 = (pi/3) + (G4UniformRand() * (pi/3));        

        G4double x = G4RandGauss::shoot(0.0, beamSigma); // Генерация координаты x
        G4double y = G4RandGauss::shoot(0.0, beamSigma); // Генерация координаты y
        G4double z = G4RandGauss::shoot(0.0, beamSigma); // Генерация координаты z
    
        G4double px = G4RandGauss::shoot(0.0, beamSigma); // Генерация импульса x
        G4double py = G4RandGauss::shoot(0.0, beamSigma); // Генерация импульса y
        G4double pz = -beamMomentum; // Импульс вдоль z

// Вычисление направления импульса
        G4ThreeVector momDirection(std::sin(beamTheta_1) * std::cos(beamTheta_2), std::sin(beamTheta_2) * std::cos(beamTheta_1), -std::sin(beamTheta_2));


// Применение сгенерированных параметров пучка
        G4ThreeVector beamMomentumVector = G4ThreeVector(px, py, pz);
        particleGun->SetParticleMomentumDirection(momDirection);

        G4ThreeVector beamPosition = G4ThreeVector(x, y, z);
        particleGun->SetParticlePosition(beamPosition);
    

   
        particleGun->GeneratePrimaryVertex(anEvent);
    }
    
}
