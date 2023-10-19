/*    Test_Motors_1_and2_and3_and4_V2.ino
 *    10-19-23
*     Moves 4 stepper motors at same time. 
 *    Microstepping switch setting
 *                        123
 *    Full step (coarse)  LLL
 *    Half step           HLL
 *    1/4 step            LHL
 *    1/8 step            HHL
 *    1/16 step           LLH
 *    1/32 step (smooth)  HLH or
 *    1/32 step           LHH or
 *    1/32 step           HHH 
 *  
  Example sketch to control stepper motors with 
  the MuvMotors.com Model SB_T41_4on_2ext board controlling
  up to 4 DRV8825 stepper motor drivers.
  using Teensy 3.5 and AccelStepper library.
*/

// Include the AccelStepper library:
#include <AccelStepper.h>

// uStep Mode 1/32 Smoothest  uStep Switches HHH, LHH, or HLH

// Set the Teensy pins to stepper motor drivers and create the AccelStepper instances

// Teensy 4.1 on board SB_T41_4on_2ext_COMBO_ICs pins
// DRV1
const int motorInterfaceType1 = 1;
const int stepPin1 = 4; // IO-4, pin 6 left
const int dirPin1 = 5;  // IO-5, pin 7 left
const int enPin1 = 6;   // IO-6, pin 8 left

// Create instance of the AccelStepper class for motor 1
AccelStepper stepper1 = AccelStepper(motorInterfaceType1, stepPin1, dirPin1);

int PulsWidth1 = 10; //AccelStepper's MinPulsWidth, uS

//unsigned int MaxSpeed1 = 6400;
//unsigned int MaxSpeed1 = 12800;  
unsigned int MaxSpeed1 = 19200; 
//unsigned int MaxSpeed1 = 25600; 

//unsigned int Acceleration1 = 2000;  //1/32 uStep gradual
unsigned int Acceleration1 = 4000;  // 1/32 uStep
//unsigned int Acceleration1 = 8000;  // 1/32 uStep 

long Distance1 = (6400 * 20);  
//long Distance1 = (6400 * 2); 

// DRV2
const int motorInterfaceType2 = 1;
const int stepPin2 = 22;  // IO-22, pin 5 right
const int dirPin2 = 21;   // IO-21, pin 6 right
const int enPin2 = 20;    // IO-20, pin 7 right

AccelStepper stepper2 = AccelStepper(motorInterfaceType1, stepPin2, dirPin2);

int PulsWidth2 = 10; //AccelStepper's MinPulsWidth, uS

// 1/32 uStep   1 rev/sec 6400, 2 rev/sec 12800, 3 rev/sec 19200,4 rev/sec 25600
//unsigned int MaxSpeed2 = 6400;
//unsigned int MaxSpeed2 = 12800;  
unsigned int MaxSpeed2 = 19200; 
//unsigned int MaxSpeed2 = 25600; 

// unsigned int Acceleration2 = 2000;  //1/32 uStep gradual
unsigned int Acceleration2 = 4000;    // 1/32 uStep
//unsigned int Acceleration2 = 8000;    // 1/32 uStep

long Distance2 = (6400 * 20); 
//long Distance2 = (6400 * 2);

// DRV3
const int motorInterfaceType3 = 1;
const int stepPin3 = 18;  // IO-18, pin 9 right
const int dirPin3 = 17;   // IO-17, pin 10 right
const int enPin3 = 13;    // IO-13, pin 14 right LED CANNOT be used

// Create instance of the AccelStepper class for motor 3

AccelStepper stepper3 = AccelStepper(motorInterfaceType3, stepPin3, dirPin3);

int PulsWidth3 = 10; //AccelStepper's MinPulsWidth, uS

// 1/32 uStep   1 rev/sec 6400, 2 rev/sec 12800, 3 rev/sec 19200,4 rev/sec 25600
//unsigned int MaxSpeed3 = 6400;
//unsigned int MaxSpeed3 = 12800;  
unsigned int MaxSpeed3 = 19200; 
//unsigned int MaxSpeed3 = 25600; 

//unsigned int Acceleration3 = 2000;  //1/32 uStep
unsigned int Acceleration3 = 4000;    // 1/32 uStep
//unsigned int Acceleration3 = 8000;    // 1/32 uStep

long Distance3 = (6400 * 20);
//long Distance3 = (6400 * 2);

// DRV4
const int motorInterfaceType4 = 1;
const int stepPin4 = 40;  // IO-40, pin 17 right
const int dirPin4 = 39;   // IO-39, pin 18 right
const int enPin4 = 38;    // IO-38, pin 19 right

AccelStepper stepper4 = AccelStepper(motorInterfaceType4, stepPin4, dirPin4);

int PulsWidth4 = 10; //AccelStepper's MinPulsWidth, uS

// 1/32 uStep   1 rev/sec 6400, 2 rev/sec 12800, 3 rev/sec 19200,4 rev/sec 25600
//unsigned int MaxSpeed4 = 6400;
//unsigned int MaxSpeed4 = 12800;  
unsigned int MaxSpeed4 = 19200; 
//unsigned int MaxSpeed4 = 25600; 

//unsigned int Acceleration4 = 2000;  //1/32 uStep gradual acceleration
unsigned int Acceleration4 = 4000;    // 1/32 uStep
//unsigned int Acceleration4 = 8000;

long Distance4 = (6400 * 20);
//long Distance4 = (6400 * 2);

void setup() {
  // Motion parameters and pin outputs for Motor 1, DRV8825
  stepper1.setMinPulseWidth(PulsWidth1); // Required or steps lost
  stepper1.setMaxSpeed(MaxSpeed1);
  stepper1.setAcceleration(Acceleration1);

  // Set pins to Motor 1 to be outputs
  pinMode(enPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin1, OUTPUT);

  // Motion parameters and pin outputs for Motor 2, DRV8825
  stepper2.setMinPulseWidth(PulsWidth2); // Required or steps lost
  stepper2.setMaxSpeed(MaxSpeed2);
  stepper2.setAcceleration(Acceleration2);

  // Set pins to Motor 2 to be outputs
  pinMode(enPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);

  // Motion parameters and pin outputs for Motor 3, DRV8825
  stepper3.setMinPulseWidth(PulsWidth3); // Required or steps lost
  stepper3.setMaxSpeed(MaxSpeed3);
  stepper3.setAcceleration(Acceleration3);

  // Set pins to Motor 3 to be outputs
  pinMode(enPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin3, OUTPUT);

  // Motion parameters and pin outputs for Motor 4, DRV8825
  stepper4.setMinPulseWidth(PulsWidth4); // Required or steps lost
  stepper4.setMaxSpeed(MaxSpeed4);
  stepper4.setAcceleration(Acceleration4);

  // Set pins to Motor 4 to be outputs
  pinMode(enPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
  pinMode(stepPin4, OUTPUT);

  // enable motors
  // for Motor 1, onboard driver DRV8825
  digitalWrite(enPin1, HIGH); // enables the DRV8825 to Motor 1

  // for Motor 2, onboard driver DRV8825
  digitalWrite(enPin2, HIGH); // enables the DRV8825 to Motor 2

  // for Motor 3, onboard driver DRV8825
  digitalWrite(enPin3, HIGH); // enables the DRV8825 to Motor 3

  // for Motor 4, onboard driver DRV8825
  digitalWrite(enPin4, HIGH); // enables the DRV8825 to Motor 4
}

void loop() {
 
 if (stepper1.distanceToGo() == 0)
  {
    Distance1 = -Distance1;
    stepper1.moveTo(Distance1);
  }
  if (stepper2.distanceToGo() == 0)
  {
    Distance2 = -Distance2;
    stepper2.moveTo(Distance2);
  }

  if (stepper3.distanceToGo() == 0)
  {
    Distance3 = -Distance3;
    stepper3.moveTo(Distance3);
  }

  if (stepper4.distanceToGo() == 0)
  {
    Distance4 = -Distance4;
    stepper4.moveTo(Distance4);
  }
  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();

  // repeat the loop
}
