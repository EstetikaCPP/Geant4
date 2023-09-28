#include "action.hh"
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

MyEventAction::MyEventAction() {}

MyEventAction::~MyEventAction() {}

MySteppingAction::MySteppingAction() {}

MySteppingAction::~MySteppingAction() {}


G4int totalSteps = 0;
G4int gammaCount = 0;
G4int electronCount = 0;
G4int positronCount = 0;
G4int eventID = 1;


void MyEventAction::EndOfEventAction(const G4Event* event) {
    G4cout << "EVENT NUMBER " << eventID << G4endl;   
    G4cout << "Total Steps: " << totalSteps << G4endl;
    G4cout << "Gamma Particles: " << gammaCount << G4endl;
    G4cout << "Electrons: " << electronCount << G4endl;
    G4cout << "Positrons: " << positronCount << G4endl;

    totalSteps = 0;
    gammaCount = 0;
    electronCount = 0;
    positronCount = 0;
    eventID++;

}





void MySteppingAction::UserSteppingAction(const G4Step* step) {
    totalSteps++;

    G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
    G4double particleEnergy = step->GetPostStepPoint()->GetKineticEnergy();

    if (particleName == "gamma") {
        gammaCount++;
    } else if (particleName == "e-") {
        electronCount++;
    } else if (particleName == "e+") {
        positronCount++;
    }

    G4String processName = "Unknown Process";
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    if (process) {
        processName = process->GetProcessName();
    }

    G4cout << "Step " << totalSteps << " | Particle: " << particleName << " | Process: " << processName << " | " <<"Kinetic Energy: " << particleEnergy << " MeV" << G4endl;
}










void MyActionInitialization::Build() const {
    MyPrimaryGeneratorAction* generator = new MyPrimaryGeneratorAction();
    SetUserAction(generator);

    // Установите пользовательский класс события
    SetUserAction(new MyEventAction());

    SetUserAction(new MySteppingAction());
}



