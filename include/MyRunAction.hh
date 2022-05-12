#ifndef MyRunAction_h
#define MyRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"



class G4Timer;
class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the accumulated number of optical photons across all events
/// from the scintillator and PMT optical photon numbers accumulated via stepping and event actions.
/// The accumulated number of optical photons is then printed on the screen.

class MyRunAction : public G4UserRunAction
{
  public:
  MyRunAction();
    virtual ~MyRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void AddScintillatorCounter(G4long fScintillationCounter); 
    void AddPMTCounter(G4long fPMTCounter); 

  private:
    G4Timer* fTimer;
    G4Accumulable<G4long> fEventSumScintillationCounter;
    G4Accumulable<G4long> fEventSumPMTCounter;
};



#endif
