#ifndef MyDetectorConstruction_h 
#define MyDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//class G4VPhysicalVolume;
//class G4LogicalVolume;
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
 virtual  ~MyDetectorConstruction();

public:
  virtual G4VPhysicalVolume *Construct();
  G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}
  // virtual void ConstructSDandField();

private:
  G4double worldXY;
  G4double worldZ;
  G4VPhysicalVolume *ConstructDetector();
  //   G4bool  fCheckOverlaps;

protected:
  G4LogicalVolume* fScoringVolume;
};

#endif
