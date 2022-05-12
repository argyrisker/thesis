#include "G4Timer.hh"

#include "MyRunAction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

MyRunAction::MyRunAction()
 : G4UserRunAction(),
   fTimer(0),
   fEventSumScintillationCounter(0.),
   fEventSumPMTCounter(0.)
{
  fTimer = new G4Timer;

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEventSumScintillationCounter);
  accumulableManager->RegisterAccumulable(fEventSumPMTCounter); 
}

MyRunAction::~MyRunAction()
{
  delete fTimer;
}

void MyRunAction::BeginOfRunAction(const G4Run* aRun)
{
  // start timer
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
  // output timer
  fTimer->Stop();

  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4cout << "number of event = " << nofEvents << " " << *fTimer << G4endl;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute total number of scintillation photons and total that reach PMT
  //
  G4long totalScintCounts  = fEventSumScintillationCounter.GetValue();
  G4long totalPMTCounts = fEventSumPMTCounter.GetValue();
  
  G4double nScintPerEvent = (G4double) totalScintCounts/ (G4double) nofEvents; 
  G4double nPMTPerEvent = (G4double) totalPMTCounts/ (G4double) nofEvents;
  G4double PMTRatio = (G4double) totalPMTCounts/(G4double) totalScintCounts;  

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const MyPrimaryGeneratorAction* generatorAction
   = static_cast<const MyPrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
   
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
 
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " Events " << runCondition
     << G4endl
     << " Total Scintillation Counts : " << totalScintCounts << " or " << nScintPerEvent << " Counts per event " 
     << G4endl
     << " Total PMT Counts : " << totalPMTCounts << " or " << nPMTPerEvent << " Counts per event "
     << G4endl
     << " Fraction hitting PMT : " << PMTRatio
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;
}

void MyRunAction::AddScintillatorCounter(G4long fScintillationCounter)
{
  fEventSumScintillationCounter += fScintillationCounter;
}

void MyRunAction::AddPMTCounter(G4long fPMTCounter)
{
  fEventSumPMTCounter += fPMTCounter;
}
