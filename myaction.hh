#ifndef MYACTION_HH
#define MYACTION_HH

#include "G4Event.hh"
#include "G4UserEventAction.hh"

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction();
    ~MyEventAction();

    virtual void EndOfEventAction(const G4Event*);
};


#endif
