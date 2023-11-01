/*  Test_Homing_Motor1_Hall_Sensor.ino
    When a stepper motor is turned on it has no knowledge of its position.
    By using a "Homing" sketch it can go to a specific location and other movements can
    be made from that starting loction.

    Uses SB_T41_4on_2ext board, DRV8825 stepper driver, stepper motor
    and a Hall Effect Magnetic Sensor such as from Hiletgo.com
    and a small magnet. Could use an Opto-interuptor or a mechanical switch but
    check polarity.
    The Teensy 4.1 is looking for a signal HIGH to LOW signal transition.

    Motor rotates until the magnet is within about 10mm of the Hall Sensor.
    The motor then stops and reverses direction to back off from the sensor, or switch,
    and moves to the final "HOME" position.
*/

#include "AccelStepper.h"
// AccelStepper() instantiation
// onboard DRV8825 drivers
AccelStepper stepper1(1, 4, 5);    //stepper  1: step on IO-4, direction on IO-5

void setup()
{
  Serial.begin(115200);
  delay(1000);  // give time for the Serial Monitor to initialize
}

void loop()
{
  home_1();  // call the homing function
}

// declare the homing function

void home_1()
{
  Serial.println("Start Homing");
  delay(200);  // give time for the Serial Monitor to display

  // stepper 1 pins
  // define the Teensy pins used for homing stepper 1
  const int enPin1 = 6;    // T41 pin to !Sleep stepper 1 pin
  const int switch1 = 3;  // T41 pin to stepper 1 homing switch

  pinMode(enPin1, OUTPUT);
  digitalWrite(enPin1, HIGH);  // wake the stepper 1
  pinMode(switch1, INPUT_PULLUP);

  bool switch1_Status = false; // flag if true indicates stepper 1 moved to switch 1
  bool doneStatus1 = false;  // flag if true indicates stepper 1 done

  long initial_homing1 = -1; // position to move toward switch 1
  const int back_off_1 = 3200; // final position of stepper 1

  //  Set Max Speed and Acceleration of stepper 1 for homing
  stepper1.setMaxSpeed(3000);      // Set Max Speed of Stepper 1
  stepper1.setAcceleration(1500);  // Set Acceleration of Stepper 1

  bool allSwitchesHit = false;  // flag true if all steppers reached their homing switches
  bool doneHoming = false; // flag true if all steppers have backed off their homing switchs

  // *** Start Homing procedure of Stepper Motors at startup ***

  while (allSwitchesHit == false)	// Make the Stepper move until the switches are activated
  {
    if ( digitalRead(switch1) != 0 ) {
      stepper1.moveTo(initial_homing1);
      initial_homing1--;
      stepper1.run();
    }
    else {
      stepper1.setCurrentPosition(0);   // this is the new 0 position for stepper 1
      switch1_Status = true;
      Serial.println(" Motor1 at the home switch");
    }

    // *** all steppers hit their homing switches yet? ***
    if (switch1_Status == true )
    {
      allSwitchesHit = true;
    }

  } // *** end of while(allSwitchesHit == false) ***

  // move to face forward
  doneStatus1 = false;

  doneHoming = false;

  // Set speeds to use backing off the homing sensor switch
  stepper1.setMaxSpeed(1500);      // Set Max Speed of Stepper 1
  stepper1.setAcceleration(1000);  // Set Acceleration of Stepper 1

  while (doneHoming == false) {
    if (stepper1.currentPosition() != back_off_1) {
      stepper1.moveTo(back_off_1);	//move to face forward
      stepper1.run();
    }
    else {
      doneStatus1 = true;
    }

    if (doneStatus1 == true )
    {
      doneHoming = true;

      stepper1.setCurrentPosition(0);   // this is the new 0 position for stepper 1
      digitalWrite(enPin1, LOW);    // relax stepper 1

    } // *** end of if doneStatus_1
  }	// *** end of while(doneHoming) ***

  Serial.println("Done Homing. Repeats procedure after 5 second delay");
  delay(5000);

}	// *** end of home_1() ***
