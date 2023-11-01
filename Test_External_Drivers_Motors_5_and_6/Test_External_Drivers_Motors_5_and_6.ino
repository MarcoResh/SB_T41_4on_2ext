/*    Test_External_Drivers_Motors_5_and_6.ino
      Uses SB_T41_4on_7ext board to send
      signals to two external stepper drivers 
      such as TB6600.
      
      Microstepper is smoothest. If more speed is required
      use 1/16, 1/8, 1/4, 1/2, or full step.
      1/32 step (smooth)  HLH or
      1/32 step           LHH or
      1/32 step           HHH
*/

// Include the AccelStepper library:
#include <AccelStepper.h>

// uStep Mode 1/32 Smoothest  uStep Switches HHH, LHH, or HLH
// CW very smooth. CCW slightly less smooth.

// Set the Teensy pins to stepper motor drivers and create the AccelStepper instances

// ExternalDriver to Motor5
const int enPin5 = 34;
const int dirPin5 = 35;
const int stepPin5 = 36;

const int motorInterfaceType5 = 1;
// Create instance of the AccelStepper class for motor 5
AccelStepper stepper5 = AccelStepper(motorInterfaceType5, stepPin5, dirPin5);
int PulsWidth5 = 10; //AccelStepper's MinPulsWidth, uS
unsigned int MaxSpeed5 = 19200;
unsigned int Acceleration5 = 4000;  //12800;
long Distance5 = (6400 * 20); // 1/32 uStep

// External Driver to Motor6
const int enPin6 = 30;
const int dirPin6 = 31;
const int stepPin6 = 32;

const int motorInterfaceType6 = 1;
AccelStepper stepper6 = AccelStepper(motorInterfaceType6, stepPin6, dirPin6);
int PulsWidth6 = 10; //AccelStepper's MinPulsWidth, uS
unsigned int MaxSpeed6 = 19200;
unsigned int Acceleration6 = 4000;   
long Distance6 = (6400 * 20);

void setup() {

  // Motion parameters and pin outputs for Motor 5, External Driver
  stepper5.setMinPulseWidth(PulsWidth5);
  stepper5.setMaxSpeed(MaxSpeed5);
  stepper5.setAcceleration(Acceleration5);

  // Set pins to Motor 5 to be outputs
  pinMode(enPin5, OUTPUT);
  pinMode(dirPin5, OUTPUT);
  pinMode(stepPin5, OUTPUT);

  // Motion parameters and pin outputs for Motor 6, External Driver
  stepper6.setMinPulseWidth(PulsWidth6);
  stepper6.setMaxSpeed(MaxSpeed6);
  stepper6.setAcceleration(Acceleration6);

  // Set pins to Motor 6 to be outputs
  pinMode(enPin6, OUTPUT);
  pinMode(dirPin6, OUTPUT);
  pinMode(stepPin6, OUTPUT);

  // enable motors
  // for Motor 5, external driver
  digitalWrite(enPin5, LOW); // enables the external driver for Motor 5

  // for Motor 6, external driver
  digitalWrite(enPin6, LOW); // enables the external driver for Motor 6

}

void loop() {

  if (stepper5.distanceToGo() == 0)
  {
    Distance5 = -Distance5;
    stepper5.moveTo(Distance5);
  }

  if (stepper6.distanceToGo() == 0)
  {
    Distance6 = -Distance6;
    stepper6.moveTo(Distance6);
  }

  stepper5.run();
  stepper6.run();

  // repeat the loop
}
