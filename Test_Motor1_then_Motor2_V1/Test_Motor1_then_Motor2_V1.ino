/*     Test_Motor1_then_Motor2_V1.ino
       12/9/22 Works
       Reduces some delay()s and minor stuff then a rename.
       Motor1_then_Motor2.ino
       9/17/22 Works
       Teensy 4.1
       Moves Motor1 CW, Motor2 CW, Motor1 CCW, Motor2 CCW, repeat.
       One is after the other.

      Microstepping switch setting
                          123
      Full step (coarse)  LLL
      Half step           HLL
      1/4 step            LHL
      1/8 step            HHL
      1/16 step           LLH
      1/32 step (smooth)  HLH or
      1/32 step           LHH or
      1/32 step           HHH

      Test_DRVs_uStep.ino
      9/11/2022
      Teensy 4.1
      Use Switch/Case to select driver number 1,2,3,4
     Test_DRV1_uStep.ino
     Teensy 4.1 on SB_4on_2ext_COMBO-ICs board
     Waits for Serial Monitor so must open it after starting sketch.
     Next version use Switch/Case to make it convenient to check drivers 2,3,4, and external.
     9/10/22 Works
     SB_Stepper_uStep_Test.ino
    6/20/22
    Test for maximum speed in each of the six microstepping modes.
    Used Jugeteck N23 Hollow stepper motor.
    DRV88225 Marked with 3 white lines near pin 1,2,3, 4.
    Vref set to 0.65V for coil current of 1.95A.
    No load. I held my finger on hub to ensure it has at least some torque.
    Move max.speed, acceleration, and distance before setup() to make global.

  SB_Stepper_Test.ino
  6/19/22 Works
  Test on board SB_T41_4on_2ext_spdif.
  Initially did not work. I had it in Full Step Mode.
  The max speed and acceleration I used were for 1/32 Step Mode.
  The speed and acceleleration were too fast so,
  after about 3 revolutions the motor would stall and buzz.

  Driver 1:
  ENA1-H, IO 6, HDR pin 8 Lft
  PUL1-H, IO 4, HDR pin 6 Lft
  DIR1-H, IO 5, HDR pin 7 Lft

  Driver 2:
  ENA2-H, IO 20, HDR pin 7 Rht
  PUL2-H, IO 22, HDR pin 5 Rht
  DIR2-H, IO 21, HDR pin 6 Rht

  10/20/20 Works for Motor 1 and Motor 5. Motors 2, 3, 4, 6 to do.
  From step_accelstepper.ino
  Motor accelerates to a max speed then decelerates, stops, reverses and repeats.
  4/22/20 Works.
  Example sketch to control a stepper motor with SB_Main_C.brd controlling
  DRV8825 stepper motor drivers or TB6600 external drivers,
  using Teensy 3.5 and AccelStepper library.
*/

// Include the AccelStepper library:
#include <AccelStepper.h>

// Driver/Motor operating parameters
/* // uStep Mode Full roughest  LLL
  const int MaxSpeed = 600;
  const int Acceleration = 500;
  const int Distance = 6400;
  // Rough. Less rough CW then CCW.
*/

/*
  // uStep Mode 1/2   HLL
  const int DRV1_MaxSpeed = 2000;
  const int DRV1_Acceleration = 500;
  const int DRV1_Distance = 19200;
  // Occasional roughness.
*/

/*
  // uStep Mode 1/4   LHL
  const int DRV1_MaxSpeed = 4000;
  const int DRV1_Acceleration = 1000;
  const int DRV1_Distance = 28800;
  // Smooth. CCW slightly less smooth.
*/

/*
  // uStep Mode 1/8    HHL
  const int DRV1_MaxSpeed = 10000;
  const int DRV1_Acceleration = 2000;
  const int DRV1_Distance = 124416;
  // CW smooth. CCW rougher but no stall.
*/

/*
  // uStep Mode 1/16    LLH
  const int DRV1_MaxSpeed = 24000; //
  const int DRV1_Acceleration = 4000;
  const int DRV1_Distance = 248832;
  // CW smooth. CCW smooth.
*/

// Set the Teensy pins to stepper motor drivers and create the AccelStepper instances

// Teensy 4.1 on board SB_T41_4on_2ext_COMBO_ICs pins
// DRV1
const int enPin1 = 6;
const int stepPin1 = 4;
const int dirPin1 = 5;
const int motorInterfaceType1 = 1;

// Create instance of the AccelStepper class for motor 1
AccelStepper stepper1 = AccelStepper(motorInterfaceType1, stepPin1, dirPin1);

int PulsWidth1 = 10; //AccelStepper's MinPulsWidth, uS
unsigned int MaxSpeed1 = 12800;  // 1/16
//unsigned int MaxSpeed1 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed1 = 12800;   // 1/16 uStep
//unsigned int MaxSpeed1 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed1 = 3200;  // 1/4 uStep:
//unsigned int MaxSpeed1 = 400;  // 1/1 uStep:

unsigned int Acceleration1 = 4000;    // 1/16 uStep
//unsigned int Acceleration1 = 8000;  // 1/32 uStep
//unsigned int Acceleration1 = 4000;    // 1/16 uStep
//unsigned int Acceleration1 = 2000;  // 1/8 uStep
//unsigned int Acceleration1 = 1000;  // 1/4 uStep
//unsigned int Acceleration1 = 250;  // 1/1 uStep

long Distance1 = (3200 * 20);   // 1/16 uStep
//long Distance1 = (6400 * 20); // 1/32 uStep
//long Distance1 = (3200 * 20);   // 1/16 uStep
//long Distance1 = (1600 * 20); // 1/8 uStep
//long Distance1 = (800 * 20);  // 1/4 uSteps
//long Distance1 = (200 * 20);  // 1/1 uSteps

// DRV2
const int enPin2 = 20;
const int stepPin2 = 22;
const int dirPin2 = 21;
AccelStepper stepper2 = AccelStepper(motorInterfaceType1, stepPin2, dirPin2);

int PulsWidth2 = 10; // AccelStepper's MinPulsWidth, uS
unsigned int MaxSpeed2 = 12800;   // 1/16 uStep
//unsigned int MaxSpeed2 = 25600; // 1/32 uStep: 2 rev per sec 12800 //3 rev per sec 19200 //4 rev per sec 25600 // fails 40000;
//unsigned int MaxSpeed2 = 12800;   // 1/16 uStep
//unsigned int MaxSpeed2 = 6400;  // 1/8 uStep: 2 rev per sec ---- //3 rev per sec ---- //4 rev per sec 6400
//unsigned int MaxSpeed2 = 3200;  // 1/4 uStep:

unsigned int Acceleration2 = 4000;    // 1/16 uStep
//unsigned int Acceleration2 = 4000;    // 1/16 uStep
//unsigned int Acceleration2 = 2000;  // 1/8 uStep
//unsigned int Acceleration2 = 1000;  // 1/4 uStep

long Distance2 = (3200 * 20);   // 1/16 uStep
//long Distance2 = (6400 * 20); // 1/32 uStep
//long Distance2 = (3200 * 20);   // 1/16 uStep
//long Distance2 = (1600 * 20); // 1/8 uStep
//long Distance2 = (800 * 20);  // 1/4 uSteps

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
  // enable motors
  // for Motor 1, onboard driver DRV8825
  digitalWrite(enPin1, HIGH); // enables the DRV8825 to Motor 1

  // for Motor 2, onboard driver DRV8825
  digitalWrite(enPin2, HIGH); // enables the DRV8825 to Motor 2
}

void loop() {
  // Move Motor1 to the target position CCW
  stepper1.moveTo(Distance1);
  stepper2.moveTo(Distance2);

  // Run Motor 1 to target position with set speed and acceleration/deceleration
  // for onboard DRV8825 driver
   stepper1.runToPosition();
  //stepper1.run();
   stepper2.runToPosition();
  //stepper2.run();

  // Move back to zero
  stepper1.moveTo(0);
  stepper2.moveTo(0);

  // Run Motor1 then Motor2 back to 0 position with set speed and acceleration/deceleration
  stepper1.runToPosition();
  stepper2.runToPosition();
  //digitalWrite(green_LED, LOW);
  digitalWrite(blue_LED, LOW);
  digitalWrite(red_LED, HIGH); // indicate stopped and changing direction
  delay(1000);
  digitalWrite(red_LED, LOW);

  // repeat the loop
}
