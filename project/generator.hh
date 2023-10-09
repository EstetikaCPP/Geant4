#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4SPSAngDistribution.hh"
#include "Randomize.hh"




class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGeneratorAction();
    ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);
private:
    G4ParticleGun *particleGun;    

};

#endif
