#ifndef MyEventAction_h
#define MyEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class MyRunAction;

class MyEventAction : public G4UserEventAction
{
	public:
		MyEventAction(MyRunAction* runAction);
		virtual ~MyEventAction();

		virtual void BeginOfEventAction(const G4Event* event);
		virtual void EndOfEventAction(const G4Event* event);

		void AddScintillatorCounter(G4long fScintillationCounter){ fEventSumScintillationCounter+= fScintillationCounter;}

		void AddPMTCounter(G4long fPMTCounter){fEventSumPMTCounter+=fPMTCounter;}

	private:
		MyRunAction* fRunAction;
		G4long fEventSumScintillationCounter;
		G4long fEventSumPMTCounter;
};

#endif

