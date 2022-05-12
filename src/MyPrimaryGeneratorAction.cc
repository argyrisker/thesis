#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"
#include "G4ios.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
  particleSource = new G4GeneralParticleSource();
}  

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete particleSource;
}


void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleSource->GeneratePrimaryVertex(anEvent);
} 
