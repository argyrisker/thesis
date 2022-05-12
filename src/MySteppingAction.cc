#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"

#include "G4ios.hh"
#include <fstream>
#include <iostream>
using namespace std;

MySteppingAction::MySteppingAction(MyEventAction* eventAction):G4UserSteppingAction(),
							       fEventAction(eventAction),
							       fScoringVolume(0),fScintillationCounter(0),fCerenkovCounter(0),fPMTCounter(0)
{}


MySteppingAction::~MySteppingAction()
{}



void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  fScintillationCounter = 0;
  fPMTCounter=0;
  if (!fScoringVolume) { 
    const MyDetectorConstruction* detectorConstruction
      = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  //for the step get volume
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  G4Track* track=step->GetTrack();

   G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();

    if (ParticleName == "opticalphoton" && volume == fScoringVolume) {
       fPMTCounter++;
        fEventAction->AddPMTCounter(fPMTCounter);
    }
const std::vector<const G4Track*>* secondaries =
                                            step->GetSecondaryInCurrentStep();

  if (secondaries->size()>0) {
     for(unsigned int i=0; i<secondaries->size(); ++i) {
        if (secondaries->at(i)->GetParentID()>0) {
           if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
               == G4OpticalPhoton::OpticalPhotonDefinition()){
              if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
               == "Scintillation")fScintillationCounter++; 
           }
        }
     }

      fEventAction->AddScintillatorCounter(fScintillationCounter);
  }
}
