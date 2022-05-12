class MySteppingVerbose;

#ifndef MySteppingVerbose_h
#define MySteppingVerbose_h 1

#include "G4SteppingVerbose.hh"



class MySteppingVerbose : public G4SteppingVerbose
{
 public:

   MySteppingVerbose();
   virtual ~MySteppingVerbose();

   virtual void StepInfo();
   virtual void TrackingStarted();

};



#endif
