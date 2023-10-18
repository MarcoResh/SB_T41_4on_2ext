/*    Test_Motors_1_and2_and3_and4_V1.ino
 *    12/10/22 Works
*     Moves 4 stepper motors at same time.
*     
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
  Example sketch to control a stepper motor with SB_Main_C.brd controlling
  DRV8825 stepper motor drivers or TB6600 external drivers,
  using Teensy 3.5 and AccelStepper library.
*/

// Include the AccelStepper library:
#include <AccelStepper.h>

// uStep Mode 1/32 Smoothest  uStep Switches HHH, LHH, or HLH
// CW very smooth. CCW slightly less smooth.

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
//unsigned int MaxSpeed1 = 25600;  // 1/16
unsigned int MaxSpeed1 = 1280;  // 1/32 slow
//unsigned int MaxSpeed1 = 12800;  // 1/16 ok
//unsigned int MaxSpeed1 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed1 = 12800;   // 1/16 uStep
//unsigned int MaxSpeed1 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed1 = 3200;  // 1/4 uStep:
//unsigned int MaxSpeed1 = 400;  // 1/1 uStep:

unsigned int Acceleration1 = 4000;  //16000;
//unsigned int Acceleration1 = 8000;    // 1/16 uStep
//unsigned int Acceleration1 = 8000;  // 1/32 uStep
//unsigned int Acceleration1 = 4000;    // 1/16 uStep
//unsigned int Acceleration1 = 2000;  // 1/8 uStep
//unsigned int Acceleration1 = 1000;  // 1/4 uStep
//unsigned int Acceleration1 = 250;  // 1/1 uStep

long Distance1 = -(3200 * 40);   // 1/16 uStep
//long Distance1 = (6400 * 20); // 1/32 uStep
//long Distance1 = (3200 * 20);   // 1/16 uStep
//long Distance1 = (1600 * 20); // 1/8 uStep
//long Distance1 = (800 * 20);  // 1/4 uSteps
//long Distance1 = (200 * 20);  // 1/1 uSteps

// DRV2
const int motorInterfaceType2 = 1;
const int stepPin2 = 22;  // IO-22, pin 5 right
const int dirPin2 = 21;   // IO-21, pin 6 right
const int enPin2 = 20;    // IO-20, pin 7 right

AccelStepper stepper2 = AccelStepper(motorInterfaceType1, stepPin2, dirPin2);

int PulsWidth2 = 10; //AccelStepper's MinPulsWidth, uS
//unsigned int MaxSpeed2 = 25600;   // 1/16
unsigned int MaxSpeed2 = 1280;   // 
//unsigned int MaxSpeed2 = 12800;   // 1/16 uStep ok
//unsigned int MaxSpeed2 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed2 = 12800;   // 1/16 uStep
//unsigned int MaxSpeed2 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed2 = 3200;  // 1/4 uStep:

unsigned int Acceleration2 = 4000;    // 1/16 uStep
//unsigned int Acceleration2 = 4000;    // 1/16 uStep
//unsigned int Acceleration2 = 2000;  // 1/8 uStep
//unsigned int Acceleration2 = 1000;  // 1/4 uStep

long Distance2 = -(3200 * 40);   // 1/16 uStep
//long Distance2 = (6400 * 20); // 1/32 uStep
//long Distance2 = (3200 * 20);   // 1/16 uStep
//long Distance2 = (1600 * 20); // 1/8 uStep
//long Distance2 = (800 * 20);  // 1/4 uSteps

// DRV3
const int motorInterfaceType3 = 1;
const int stepPin3 = 18;  // IO-18, pin 9 right
const int dirPin3 = 17;   // IO-17, pin 10 right
const int enPin3 = 13;    // IO-13, pin 14 right LED CANNOT be used

// Create instance of the AccelStepper class for motor 3

AccelStepper stepper3 = AccelStepper(motorInterfaceType3, stepPin3, dirPin3);

int PulsWidth3 = 10; //AccelStepper's MinPulsWidth, uS
//unsigned int MaxSpeed3 = 25600; // 1/16
unsigned int MaxSpeed3 = 1280;   // 1/32 slow
//unsigned int MaxSpeed3 = 12800; // 1/16 ok
//unsigned int MaxSpeed3 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed3 = 40000;   // 1/16 uStep
//unsigned int MaxSpeed3 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed3 = 3200;  // 1/4 uStep:
//unsigned int MaxSpeed3 = 800;  // 1/1 uStep:  rough
//unsigned int MaxSpeed3 = 50;    // 1/1 uStep:

unsigned int Acceleration3 = 4000;  // 1/32 uStep
//unsigned int Acceleration3 = 4000;    // 1/16 uStep
//unsigned int Acceleration3 = 2000;  // 1/8 uStep
//unsigned int Acceleration3 = 1000;  // 1/4 uStep
//unsigned int Acceleration3 = 250;  // 1/1 uStep

long Distance3 = (3200 * 40); // 1/16 uStep
//long Distance3 = (6400 * 20); // 1/32 uStep
//long Distance3 = (3200 * 20); // 1/16 uStep
//long Distance3 = (3200 * 1);  // 1/16 uStep
//long Distance3 = (1600 * 20); // 1/8 uStep
//long Distance3 = (800 * 20);  // 1/4 uSteps
//long Distance3 = (200 * 1);     // 1/1 uSteps

// DRV4
const int motorInterfaceType4 = 1;
const int stepPin4 = 40;  // IO-40, pin 17 right
const int dirPin4 = 39;   // IO-39, pin 18 right
const int enPin4 = 38;    // IO-38, pin 19 right

AccelStepper stepper4 = AccelStepper(motorInterfaceType4, stepPin4, dirPin4);

int PulsWidth4 = 10; //AccelStepper's MinPulsWidth, uS
//unsigned int MaxSpeed4 = 25600; // 1/16
unsigned int MaxSpeed4 = 1280;   // 1/32 slow
//unsigned int MaxSpeed4 = 12800; // 1/16 ok
//unsigned int MaxSpeed4 = 40000; // 1/16 too fast
//unsigned int MaxSpeed4 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed4 = 12800; // 1/16 uStep
//unsigned int MaxSpeed4 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed4 = 3200;  // 1/4 uStep:
//unsigned int MaxSpeed4 = 800;  // 1/1 uStep:
//unsigned int MaxSpeed4 = 50;    // 1/1 uStep:

unsigned int Acceleration4 = 4000;  // 1/32 uStep
//unsigned int Acceleration4 = 4000;    // 1/16 uStep
//unsigned int Acceleration4 = 2000;  // 1/8 uStep
//unsigned int Acceleration4 = 1000;  // 1/4 uStep
//unsigned int Acceleration4 = 250;  // 1/1 uStep

long Distance4 = (3200 * 40); // 1/16 uStep
//long Distance4 = (3200 * 20);   // 1/16 uStep
//long Distance4 = (3200 * 1);   // 1/16 uStep
//long Distance4 = (1600 * 20); // 1/8 uStep
//long Distance4 = (800 * 20);  // 1/4 uSteps
//long Distance4 = (200 * 1);     // 1/1 uSteps

// pins to use the RGB LED as an indicator
const int red_LED = 0;  // RGB LED on the SB_T41_40n_2ext_COMBO-ICs board
const int green_LED = 1;
const int blue_LED = 2;

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


  // set the outputs to the RGB and Onboard LEDs
  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);


  pinMode(LED_BUILTIN, OUTPUT); // LED to indicate sketch is running
  // Blinks indicate sketch is running
  for (int x = 1; x < 3; x++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }

  digitalWrite(LED_BUILTIN, HIGH); // turn on LED on Teensy to indicate sketch is running

  digitalWrite(LED_BUILTIN, HIGH); // turn on LED on Teensy to indicate sketch is running
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
  digitalWrite(green_LED, HIGH);   // turn the green LED on indicating motion

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
