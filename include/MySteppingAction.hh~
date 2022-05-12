#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class MyEventAction;
class G4LogicalVolume;

class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction(MyEventAction* eventAction);
    virtual ~MySteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    MyEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
    G4long fScintillationCounter;
    G4long fCerenkovCounter;
    G4long fPMTCounter;
    G4long fEventNumber;
};

#endif
