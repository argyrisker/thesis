#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGeneratorAction();    
  ~MyPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* particleSource;
};

#endif
