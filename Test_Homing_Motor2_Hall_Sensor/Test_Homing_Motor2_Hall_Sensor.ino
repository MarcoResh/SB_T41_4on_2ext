/*  Test_Homing_Motor2_Hall_Sensor.ino
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
// onboard DRV8825 driver
AccelStepper stepper2(1, 22, 21);    //stepper  2: step on IO-22, direction on IO-21
void setup()
{
  Serial.begin(115200);
  delay(1000);  // give time for the Serial Monitor to initialize
}

void loop()
{
  home_2();  // call the homing function
}

// declare the homing function

void home_2()
{
  Serial.println("Start Homing");
  delay(200);  // give time for the Serial Monitor to display

  // stepper 2 pins
  // define the Teensy pins used for homing stepper 2
  const int enPin2 = 20;    // T41 pin to !Sleep stepper 2 pin
  const int switch2 = 23;  // T41 pin to stepper 2 homing switch

  pinMode(enPin2, OUTPUT);
  digitalWrite(enPin2, HIGH);  // wake the stepper 2
  pinMode(switch2, INPUT_PULLUP);

  bool switch2_Status = false; // flag if true indicates stepper 2 moved to switch 2
  bool doneStatus2 = false;  // flag if true indicates stepper 2 done

  long initial_homing2 = -1; // position to move toward switch 2
  const int back_off_2 = 3200; // final position of stepper 2

  //  Set Max Speed and Acceleration of stepper 2 for homing
  stepper2.setMaxSpeed(3000);      // Set Max Speed of Stepper 2
  stepper2.setAcceleration(1500);  // Set Acceleration of Stepper 2

  bool allSwitchesHit = false;  // flag true if all steppers reached their homing switches
  bool doneHoming = false; // flag true if all steppers have backed off their homing switchs

  // *** Start Homing procedure of Stepper Motors at startup ***

  while (allSwitchesHit == false)	// Make the Stepper move until the switches are activated
  {
    if ( digitalRead(switch2) != 0 ) {
      stepper2.moveTo(initial_homing2);
      initial_homing2--;
      stepper2.run();
    }
    else {
      stepper2.setCurrentPosition(0);   // this is the new 0 position for stepper 2
      switch2_Status = true;
      Serial.println(" Motor2 at the home switch");
    }

    // *** all steppers hit their homing switches yet? ***
    if (switch2_Status == true )
    {
      allSwitchesHit = true;
    }

  } // *** end of while(allSwitchesHit == false) ***

  // move to face forward
  doneStatus2 = false;

  doneHoming = false;

  // Set speeds to use backing off the homing sensor switch
  stepper2.setMaxSpeed(1500);      // Set Max Speed of Stepper 2
  stepper2.setAcceleration(1000);  // Set Acceleration of Stepper 2

  while (doneHoming == false) {
    if (stepper2.currentPosition() != back_off_2) {
      stepper2.moveTo(back_off_2);	//move to face forward
      stepper2.run();
    }
    else {
      doneStatus2 = true;
    }

    if (doneStatus2 == true )
    {
      doneHoming = true;

      stepper2.setCurrentPosition(0);   // this is the new 0 position for stepper 2
      digitalWrite(enPin2, LOW);    // relax stepper 2

    } // *** end of if doneStatus_2
  }	// *** end of while(doneHoming) ***

  Serial.println("Done Homing. Repeats procedure after 5 second delay");
  delay(5000);

}	// *** end of home_2() ***
