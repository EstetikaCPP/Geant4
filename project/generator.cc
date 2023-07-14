#include "generator.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);//create a one particle for one action

}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
    
    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., -1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(0.005*GeV);
    fParticleGun->SetParticleDefinition(particle);


    fParticleGun->GeneratePrimaryVertex(anEvent);
}
