#ifndef MyStackingAction_H
#define MyStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"



class MyStackingAction : public G4UserStackingAction
{
  public:
    MyStackingAction();
    virtual ~MyStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
    //G4long fScintillationCounter;
    //G4long fCerenkovCounter;
};



#endif
