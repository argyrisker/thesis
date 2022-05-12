#ifndef MyActionInitialization_h
#define MyActionInitialization_h 1

#include "globals.hh"
#include "G4Accumulable.hh"
#include "G4VUserActionInitialization.hh"



class MyActionInitialization : public G4VUserActionInitialization
{
public:
  MyActionInitialization();
 virtual ~MyActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;


  virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};


#endif
