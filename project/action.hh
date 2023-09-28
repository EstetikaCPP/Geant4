#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "G4UserEventAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;

};



class MySteppingAction : public G4UserSteppingAction{
public:
    MySteppingAction();
    virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step* );

};


class MyEventAction : public G4UserEventAction {
public:
    MyEventAction();
    ~MyEventAction();

    void EndOfEventAction(const G4Event*);
};










#endif
