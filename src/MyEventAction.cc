#include "MyEventAction.hh"
#include "MyRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

using namespace std;

MyEventAction::MyEventAction(MyRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEventSumScintillationCounter(0), fEventSumPMTCounter(0)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{    
  fEventSumScintillationCounter = 0;
  fEventSumPMTCounter = 0;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{   
  mtx.lock(); // mutex lock for shared resource

  // accumulate statistics in run action
  fRunAction->AddScintillatorCounter(fEventSumScintillationCounter);
  fRunAction->AddPMTCounter(fEventSumPMTCounter);

  // Write them to a file
  ofstream outfile;
  if (fEventSumScintillationCounter != 0.0) {
      outfile.open("PhotonCountsPerEvent.txt", ios::out | ios::app );   // open a file in write mode.
  }
  if(outfile.is_open()) {
      outfile << fEventSumScintillationCounter << " " << fEventSumPMTCounter << endl;
      outfile.close(); // close the opened file.
  } else{
      //cout<<"file isn't open"<<endl;
  }

  mtx.unlock();
}
