#include <iostream>
#include "MyDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4Colour.hh"
using namespace std;

MyDetectorConstruction::MyDetectorConstruction()
  :G4VUserDetectorConstruction(),
   fScoringVolume(0)
{
  worldXY=worldZ=40*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{;}//?????????????????????????



G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  //MATERIALS USED SOME OF THEM ARE GUESS...
  std::cout<<"HERE IN CONST 1"<<std::endl;
  G4NistManager* nist = G4NistManager::Instance();
   std::cout<<"HERE IN CONST 1/2"<<std::endl;

   G4double a,density,fracMass,z;
   G4int ncomp,natoms;
   G4String symbol;
   
   G4Material* scint = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 std::cout<<"HERE IN CONST 1/3"<<std::endl;
  G4Material* plastic = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");

  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  // Glass window 
   a = 28.0855*g/mole;
   G4Element* elSilicon = new G4Element("Silicon", symbol="Si",z=14.,a);
   a = 15.9994*g/mole;
   G4Element* elOxygen = new G4Element("Oxygen", symbol="O",z=8.,a);
   density = 2.648*g/cm3;
   G4Material* Glass = new G4Material("Glass",density,ncomp=2);
   Glass->AddElement(elOxygen,natoms=2);
   Glass->AddElement(elSilicon,natoms=1);

     // Container (Aluminum)
   a = 26.9815*g/mole;
   G4Element* elAluminum = new G4Element("Aluminum", symbol="Al",z=13.,a);
   density = 2.6989*g/cm3;
   G4Material* matAl= new G4Material("Container Scintillator", density,ncomp=1);
   matAl->AddElement(elAluminum,fracMass=100.*perCent);

  
 std::cout<<"HERE IN CONST 1/4"<<std::endl;
  // Scintillation Parameter Initialization
   G4OpticalParameters::Instance()->SetScintEnhancedTimeConstants(true);
   //G4OpticalParameters::Instance()->SetTrackSecondariesFirst(true);
   G4OpticalParameters::Instance()->SetScintByParticleType(true);
   G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);

   // Glass Optical Properties
   
   std::vector<G4double> PhotonEnergyGlass         = { 2.39*eV, 2.48*eV, 2.61*eV, 2.76*eV, 2.84*eV, 2.92*eV, 3.10*eV, 3.20*eV, 3.31*eV };
   std::vector<G4double> RefractiveIndexGlass =      { 1.53, 1.53, 1.53, 1.53, 1.53, 1.53, 1.53, 1.53, 1.53 };
   std::vector<G4double> AbsorptionGlass =           { 4.81*m, 4.81*m, 4.81*m, 4.81*m, 4.81*m, 4.81*m, 4.81*m, 4.81*m, 4.81*m }; // (lower value)
  
   G4MaterialPropertiesTable* MatGlass = new G4MaterialPropertiesTable(); 
   MatGlass->AddProperty("RINDEX", PhotonEnergyGlass, RefractiveIndexGlass); //index of refraction
   MatGlass->AddProperty("ABSLENGTH", PhotonEnergyGlass, AbsorptionGlass);

   G4cout << "Glass G4MaterialPropertiesTable:" << G4endl;
   MatGlass->DumpTable();

   Glass->SetMaterialPropertiesTable(MatGlass);


    // Scintillator Optical Properties
    
   
   std::vector<G4double> photonEnergy=         { 2.39*eV, 2.40*eV, 2.42*eV, 2.45*eV, 2.47*eV, 2.49*eV, 2.52*eV, 2.55*eV, 2.57*eV, 2.59*eV,
                                                       2.62*eV, 2.64*eV, 2.66*eV, 2.67*eV, 2.70*eV, 2.71*eV, 2.72*eV, 2.74*eV, 2.75*eV, 2.76*eV,
                                                       2.77*eV, 2.78*eV, 2.80*eV, 2.82*eV, 2.83*eV, 2.86*eV, 2.87*eV, 2.88*eV, 2.89*eV, 2.90*eV,
                                                       2.91*eV, 2.93*eV, 2.94*eV, 2.95*eV, 2.97*eV, 2.98*eV, 2.99*eV, 3.00*eV, 3.01*eV, 3.02*eV,
                                                       3.04*eV, 3.08*eV};
                                                        
 
   std::vector<G4double> refractiveIndex     = { 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                                             1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,
                                                             1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,1.58, 1.58};

   
   std::vector<G4double> absorption         = { 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m,
                                                       7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m,
                                                       7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m,
                                                       7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m, 7.0*m,
                                                       7.0*m, 7.0*m}; // (lower value)
  

   std::vector<G4double> scintComponent1 =      { 0.08, 0.09, 0.09, 0.10, 0.11, 0.13, 0.15, 0.17, 0.19, 0.22,
                                                       0.25, 0.27, 0.29, 0.33, 0.36, 0.40, 0.43, 0.47, 0.52, 0.57,
                                                       0.63, 0.65, 0.68, 0.70, 0.70, 0.70, 0.73, 0.78, 0.84, 0.91,
                                                       0.97, 0.99, 0.97, 0.95, 0.90, 0.82, 0.75, 0.58, 0.42, 0.29,
                                                       0.19, 0.08};
                                                        
   std::vector<G4double> scintComponent2 =      { 0.08, 0.09, 0.09, 0.10, 0.11, 0.13, 0.15, 0.17, 0.19, 0.22,
                                                       0.25, 0.27, 0.29, 0.33, 0.36, 0.40, 0.43, 0.47, 0.52, 0.57,
                                                       0.63, 0.65, 0.68, 0.70, 0.70, 0.70, 0.73, 0.78, 0.84, 0.91,
                                                       0.97, 0.99, 0.97, 0.95, 0.90, 0.82, 0.75, 0.58, 0.42, 0.29,
                                                       0.19, 0.08};
                                                        
   std::vector<G4double> scintComponent3 =      { 0.08, 0.09, 0.09, 0.10, 0.11, 0.13, 0.15, 0.17, 0.19, 0.22,
                                                       0.25, 0.27, 0.29, 0.33, 0.36, 0.40, 0.43, 0.47, 0.52, 0.57,
                                                       0.63, 0.65, 0.68, 0.70, 0.70, 0.70, 0.73, 0.78, 0.84, 0.91,
                                                       0.97, 0.99, 0.97, 0.95, 0.90, 0.82, 0.75, 0.58, 0.42, 0.29,
                                                       0.19, 0.08};
   
   G4MaterialPropertiesTable* detmat = new G4MaterialPropertiesTable(); 

   detmat->AddProperty("RINDEX", photonEnergy, refractiveIndex);
   detmat ->AddProperty("ABSLENGTH", photonEnergy, absorption);
   detmat ->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintComponent1);
   detmat->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintComponent2);
   detmat->AddProperty("SCINTILLATIONCOMPONENT3", photonEnergy, scintComponent3);

   
   std::vector<G4double> particleEnergy =            {0.001*MeV, 0.10*MeV, 0.13*MeV, 0.17*MeV, 0.20*MeV, 0.24*MeV, 0.30*MeV, 0.34*MeV, 0.40*MeV, 0.48*MeV, 0.60*MeV,
                                                      0.72*MeV, 0.84*MeV, 1.00*MeV, 1.30*MeV, 1.70*MeV, 2.00*MeV, 2.40*MeV, 3.00*MeV, 3.40*MeV, 4.00*MeV,
                                                      4.80*MeV, 6.00*MeV, 7.20*MeV, 8.40*MeV, 10.00*MeV, 13.00*MeV, 17.00*MeV, 20.00*MeV, 24.00*MeV, 30.00*MeV,
                                                      34.00*MeV, 40.00*MeV};
   
   std::vector<G4double> scintYieldElectron    = {100, 1000, 1300, 1700, 2000, 2400,
						  3000, 3400, 4000, 4800, 6000, 7200, 8400, 10000, 13000, 17000,
						  20000, 24000, 30000, 34000, 40000, 48000, 60000, 72000 ,84000,
						  100000, 130000, 170000, 200000, 240000, 300000, 340000, 400000};
                                               
   std::vector<G4double> scintYieldMuon      = {100, 1000, 1300, 1700, 2000, 2400,
						  3000, 3400, 4000, 4800, 6000, 7200, 8400, 10000, 13000, 17000,
						  20000, 24000, 30000, 34000, 40000, 48000, 60000, 72000 ,84000,
						100000, 130000, 170000, 200000, 240000, 300000, 340000, 400000}; // not sure for that
                                               
   std::vector<G4double> scintYieldDeuteron    = {0.87, 87., 114., 156., 189., 237., 317., 374., 471., 623., 875.,
                                                  1174., 1516., 2015., 3077., 4721., 6095., 8063., 11171., 13442., 17118.,
                                                  22162., 29799., 38055., 46698., 58695., 82044., 113907., 139320., 174150., 228330.,
                                                  264450., 319920.}; //assumed same as proton because no other data  MIGHT DELETE LATER


   detmat->AddProperty("ELECTRONSCINTILLATIONYIELD", particleEnergy, scintYieldElectron);
   detmat->AddProperty("MUONSCINTILLATIONYIELD", particleEnergy, scintYieldMuon);
   detmat->AddProperty("DEUTERONSCINTILLATIONYIELD", particleEnergy, scintYieldDeuteron);

    detmat->AddConstProperty("ELECTRONSCINTILLATIONYIELD1",0.87); //Relative yield of component 1 for electrons
   detmat->AddConstProperty("ELECTRONSCINTILLATIONYIELD2",0.13); //Relative yield of component 2
   detmat->AddConstProperty("ELECTRONSCINTILLATIONYIELD3",0.001); //Relative yield of component 3
    
   detmat->AddConstProperty("MUONSCINTILLATIONYIELD1",0.87); //Relative yield of component 1 
   detmat->AddConstProperty("MUONSCINTILLATIONYIELD2",0.13); //Relative yield of component 2
   detmat->AddConstProperty("MUONSCINTILLATIONYIELD3",0.001); //Relative yield of component 3
    
  detmat ->AddConstProperty("DEUTERONSCINTILLATIONYIELD1",0.80); //Relative yield of component 1 for deuterons
  detmat->AddConstProperty("DEUTERONSCINTILLATIONYIELD2",0.20); //Relative yield of component 2
  detmat ->AddConstProperty("DEUTERONSCINTILLATIONYIELD3",0.001); //Relative yield of component 


  detmat->AddConstProperty("RESOLUTIONSCALE",1.0);      // statistical fluctuation of number of scintillation photons is RESOLUTIONSCALE*sqrt(MeanNumberPhotons)



  detmat->AddConstProperty("SCINTILLATIONTIMECONSTANT1",0.9*ns); 
  detmat->AddConstProperty("SCINTILLATIONTIMECONSTANT2",2.1*ns);  
  
    
  detmat->AddConstProperty("SCINTILLATIONRISETIME1", 1.0*ns); // fast component
  detmat->AddConstProperty("SCINTILLATIONRISETIME2", 1.0*ns); // slow component

    
  
  G4cout << " scint G4MaterialPropertiesTable:" << G4endl;
  detmat->DumpTable();
  scint->SetMaterialPropertiesTable(detmat);
  
  //...................................................................................COSMOS BEGIN......................................................................................................
 std::cout<<"HERE IN CONST 2"<<std::endl;
 worldXY= 40.*m;
 worldZ = 40.*m;
  G4double pos_x=0;
   G4double pos_y=0;
  G4Box* worldBox = new G4Box("World", worldXY*0.5, worldXY*0.5, worldZ*0.5);
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox,air,"World");
 std::cout<<"HERE IN CONST 3"<<std::endl;
 G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(),worldLog,"PhysWorld",0,false,0, 0);
  //...................................................................................COSMOS END........................................................................................................"
   //// Scintillator 
   G4double diScint = 0.0*cm;      // inner scintillator diameter
   G4double doScint = 2.0*3.75*cm; // outer scintillator diameter
   G4double lScint  = 2.0*20*cm; // scintillator length
 

   G4Tubs* scintillatorTub = new G4Tubs("G4Tubs Scintillator", diScint*0.5, doScint*0.5, lScint*0.5, 0.*deg,360.*deg);
   G4LogicalVolume* logicScintillator = new G4LogicalVolume(scintillatorTub,scint,"LogicalScintillator",0,0,0);
   G4VPhysicalVolume* physScintillator = new G4PVPlacement(0,G4ThreeVector(), logicScintillator,"PhysicalScintillator",worldLog,false,0);
   
   // Scintillator Container (an open ended hollow cylinder surrounding the scintillator)
   G4double tSContainer = 0.1*cm; // container wall thickness
   G4double diSContainer = doScint; // container inner diameter
   G4double doSContainer = diSContainer + tSContainer*2.0; // container outer diameter
   G4double lSContainer = lScint + tSContainer*2.0; // container length

   G4Tubs* scintillatorContainer = new G4Tubs("G4Tubs Container", diSContainer*0.5, doSContainer*0.5, lSContainer*0.5, 0.*deg, 360.*deg);
   G4LogicalVolume* logicContainer = new G4LogicalVolume(scintillatorContainer,matAl,"LogicalContainer",0,0,0);
   G4VPhysicalVolume* physContainer = new G4PVPlacement(0,G4ThreeVector(), logicContainer,"PhysicalContainer",worldLog,false,0);

   // Scintillator Front Container (solid front plate)
   G4double diSContainerF = 0.0*cm;  // inner diameter
   G4double doSContainerF = doScint; // outer diameter
   G4double lSContainerF = tSContainer; // length
   G4double xSContainerF = 0.0;  // coords of center of container
   G4double ySContainerF = 0.0;
   G4double zSContainerF = -(lScint+tSContainer)*0.5;
   
   G4Tubs* scintillatorContainerFront = new G4Tubs("G4Tubs Front Container", diSContainerF*0.5, doSContainerF*0.5, lSContainerF*0.5, 0.*deg, 360.*deg);
   G4LogicalVolume* logicContainerFront = new G4LogicalVolume(scintillatorContainerFront,matAl, "LogicalFrontContainer",0,0,0);
   G4VPhysicalVolume* physContainerFront = new G4PVPlacement(0,G4ThreeVector(xSContainerF,ySContainerF,zSContainerF),logicContainerFront,"PhysicalFrontContainer", worldLog,false,0);

   // Scintillator Back Container(solid back plate)
   G4double diSContainerB = 0.0*cm;  // inner diameter
   G4double doSContainerB = doScint; // outer diameter
   G4double lSContainerB = tSContainer; // length
   G4double xSContainerB = 0.0;  // coords of center of container
   G4double ySContainerB = 0.0;
   G4double zSContainerB = (lScint+tSContainer)*0.5;

   G4Tubs* scintillatorContainerBack = new G4Tubs("G4Tubs Back Container", diSContainerB*0.5, doSContainerB*0.5, lSContainerB*0.5, 0.*deg, 360.*deg);
   G4LogicalVolume* logicContainerBack = new G4LogicalVolume(scintillatorContainerBack,Glass,"LogicalBackContainer",0,0,0);
   //G4LogicalVolume* logicContainerBack = new G4LogicalVolume(scintillatorContainerBack,matContainerScintillator,"Logical Back Container",0,0,0);
   G4VPhysicalVolume* physContainerBack = new G4PVPlacement(0, G4ThreeVector(xSContainerB,ySContainerB,zSContainerB),logicContainerBack,"PhysicalBackContainer", worldLog, false,0);

   // PM Glass (front glass plate of PMT)
   G4double diPMF = 0.0*cm;        // inner diameter
   G4double doPMF = doSContainerB; // outer diameter
   G4double lPMF = lSContainerB; // length
   G4double xPMF = 0.0;  // coords of center of container
   G4double yPMF = 0.0;
   G4double zPMF = zSContainerB+lSContainerB*0.5+lPMF*0.5;

   G4Tubs* PMTubFront = new G4Tubs("G4Tubs PM Tub Front", diPMF*0.5, doPMF*0.5, lPMF*0.5, 0.*deg, 360.*deg);
   G4LogicalVolume* logicPMTubFront = new G4LogicalVolume(PMTubFront,Glass, "LogicalPMTubFront",0,0,0);
   G4VPhysicalVolume* physPMTubFront = new G4PVPlacement(0,G4ThreeVector(xPMF,yPMF,zPMF), logicPMTubFront,"PhysicalPMTubeFront", worldLog,false,0);

   // PM - photomultiplier is modeled as hollow tube coaxial with scintillator container and same thickness
   G4double diPM = diSContainer; // inner diameter
   G4double doPM = doSContainer; // outer diameter
   G4double lPM = 10.0*cm; // length
   G4double xPM = 0.0;  // coords of center of PMT
   G4double yPM = 0.0;
   G4double zPM = zPMF-lPMF*0.5+lPM*0.5;

   G4Tubs* PMTub = new G4Tubs("G4Tubs PM Tub", diPM*0.5, doPM*0.5, lPM*0.5, 0.*deg, 360.*deg);
   G4LogicalVolume* logicPMTub = new G4LogicalVolume(PMTub,Glass, "logicalPMTub",0,0,0);
   G4VPhysicalVolume* physPMTub = new G4PVPlacement(0,G4ThreeVector(xPM,yPM,zPM),logicPMTub,"PhysicalPMTube",worldLog,false,0);

   // Set Front Face of PMT as scoring volume
   //
   fScoringVolume = logicPMTubFront;

   //Make front and sides of container reflective, make back (PMT side) a dielectric
   //
   //Front 
   G4OpticalSurface* OpSurface_Front = new G4OpticalSurface("ScintillatorFrontSurface");

   G4LogicalBorderSurface* Surface_Front = new G4LogicalBorderSurface("ScintillatorFrontSurface",physScintillator,physContainerFront,OpSurface_Front);

   OpSurface_Front -> SetType(dielectric_metal);
   OpSurface_Front -> SetModel(glisur);
   OpSurface_Front -> SetFinish(polished);

    std::vector<G4double> pp_Front = {2.038*eV, 4.144*eV};
    std::vector<G4double> reflectivity_Front = {1.0, 1.0};
    std::vector<G4double> efficiency_Front = {0.0, 0.0};

    G4MaterialPropertiesTable* SMPT_Front = new G4MaterialPropertiesTable();
    SMPT_Front -> AddProperty("REFLECTIVITY",pp_Front,reflectivity_Front);
   SMPT_Front -> AddProperty("EFFICIENCY",pp_Front,efficiency_Front);

   OpSurface_Front -> SetMaterialPropertiesTable(SMPT_Front);

   //Sides

   G4OpticalSurface* OpSurface_Side = new G4OpticalSurface("ScintillatorSideSurface");

   G4LogicalBorderSurface* Surface_Side = new G4LogicalBorderSurface("ScintillatorSideSurface",physScintillator,physContainer,OpSurface_Side);

   OpSurface_Side -> SetType(dielectric_metal);
   OpSurface_Side -> SetModel(glisur);
   OpSurface_Side -> SetFinish(polished);

   std::vector<G4double> pp_Side = {2.038*eV, 4.144*eV};

   std::vector<G4double> reflectivity_Side = {1.0, 1.0};
   std::vector<G4double> efficiency_Side = {0.0, 0.0};

    G4MaterialPropertiesTable* SMPT_Side = new G4MaterialPropertiesTable();
    SMPT_Side -> AddProperty("REFLECTIVITY",pp_Side,reflectivity_Side);
    SMPT_Side -> AddProperty("EFFICIENCY",pp_Side,efficiency_Side);
  
    OpSurface_Side -> SetMaterialPropertiesTable(SMPT_Side);
     G4VisAttributes *WorldVisAtt= new G4VisAttributes(G4Colour(0.0,0.0,0.0)); //black
    worldLog->SetVisAttributes(WorldVisAtt); 

   G4VisAttributes *ScintVisAtt= new G4VisAttributes(G4Colour(0.5,0.5,0.5)); //gray
   logicScintillator->SetVisAttributes(ScintVisAtt); 

   G4VisAttributes *ContainerVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0)); //cyan
   logicContainer->SetVisAttributes(ContainerVisAtt);
   logicContainerFront->SetVisAttributes(ContainerVisAtt);
   logicContainerBack->SetVisAttributes(ContainerVisAtt);

   //G4VisAttributes *PMTVisAtt= new G4VisAttributes(G4Colour(0.80,0.36,0.36));
   G4VisAttributes *PMTVisAtt= new G4VisAttributes(G4Colour(0.5,0.0,0.0)); //maroon
   logicPMTubFront->SetVisAttributes(PMTVisAtt);
   logicPMTub->SetVisAttributes(PMTVisAtt);

  //always return the physical World
  return physWorld;
   
}
