#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"
#include "MyStackingAction.hh"
#include "MySteppingVerbose.hh"


MyActionInitialization::MyActionInitialization()
  : G4VUserActionInitialization(){}


MyActionInitialization::~MyActionInitialization()
{}


void MyActionInitialization::BuildForMaster() const
{
  MyRunAction* runAction = new MyRunAction;
  SetUserAction(runAction);
}


void MyActionInitialization::Build() const
{
  SetUserAction(new MyPrimaryGeneratorAction);

  MyRunAction* runAction = new MyRunAction;
  SetUserAction(runAction);

  MyEventAction* eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new MySteppingAction(eventAction));

  SetUserAction(new MyStackingAction());

}

G4VSteppingVerbose*
               MyActionInitialization::InitializeSteppingVerbose() const
{
  return new MySteppingVerbose();
}
