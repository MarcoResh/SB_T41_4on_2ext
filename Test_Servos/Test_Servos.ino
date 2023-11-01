/*  Test_Servos.ino
    Uses SB_T41_4on_2ext and the USER-IO_Stereo boards 
    sending I2C signals to an external PCA9685, 16 Channel servo driver.
    Such as from HiLeto on Amazon.com.
    
    Moves the first servo then the second servo.
    Look at the Serial Monitor to see approximaate positions. Not calibrated.
    This is a modification of code to test two servos.
    From https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all
  -------------
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to
  interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution.
  --------------
 ****************************************************/

#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire2); //for I2C SDA2/SCL2

// Set SERVOMIN and SERVOMAX. Note, these values have not been calibrated.
// For Servo 0
#define SERVOMIN_0  130 // This is the 'minimum' pulse length count   Parallax CW
#define SERVOMAX_0  322 // This is the 'maximum' pulse length count   Parallax CCW
// For Servo 1
#define SERVOMIN_1  200 // This is the 'minimum' pulse length count   HiTec   CCW note different direction
#define SERVOMAX_1  300 // This is the 'maximum' pulse length count   HiTec   CW


#define SERVO_FREQ 50 // Analog servo pulserate 50 Hz

// our servo # counter
//uint8_t servonum = 0;  // 0 is the first servo
uint8_t servonum;  // 0 is the first servo
const uint8_t NUMB_SERVOS = 2 ;  // enter the number of servos

void setup() {
  Serial.begin(115200);

  Serial.print(NUMB_SERVOS); Serial.println(" channel Servo test!"); Serial.println();
  delay(500);
  pwm.begin();
  /*
     In theory the internal oscillator (clock) is 25MHz but it really isn't
     that precise. You can 'calibrate' this by tweaking this number until
     you get the PWM update frequency you're expecting!
     The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
     is used for calculating things like writeMicroseconds()
     Analog servos run at ~50 Hz updates, It is importaint to use an
     oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
     1) Attach the oscilloscope to one of the PWM signal pins and ground on
        the I2C PCA9685 chip you are setting the value for.
     2) Adjust setOscillatorFrequency() until the PWM update frequency is the
        expected value (50Hz for most ESCs)
     Setting the value here is specific to each individual I2C PCA9685 chip and
     affects the calculations for the PWM update frequency.
     Failure to correctly set the int.osc value will cause unexpected PWM results
  */
  pwm.setOscillatorFrequency(25357142); //adjusted oscillator frequency
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {
  // slew 0 - 90 by one degree steps as fast as

  // variables for timing
  unsigned long startMillis;
  unsigned long endMillis;
  unsigned long timeMillis;

  Serial.println("  **************   START    *************"); Serial.println();

  startMillis = millis();
  for (servonum = 0; servonum < NUMB_SERVOS; servonum++) {
    for (int servo_position = SERVOMIN_0; servo_position <= SERVOMAX_0; servo_position++) {
      pwm.setPWM(servonum, 0, servo_position);
      Serial.print("Servo Number = "); Serial.print(servonum);
      Serial.print("   Servo Position = "); Serial.println(servo_position);
    }
    Serial.println();

    // slew 90 - 0 by one degree steps as fast as possible
    for (int servo_position = SERVOMAX_0; servo_position >= SERVOMIN_0; servo_position--) {
      pwm.setPWM(servonum, 0, servo_position);
      Serial.print("Servo Number = "); Serial.print(servonum);
      Serial.print("   Servo Position = "); Serial.println(servo_position);
    }
    endMillis = millis();
    timeMillis = endMillis - startMillis;
    Serial.print("Time in milliseconds = "); Serial.println(timeMillis);
    Serial.println();
    Serial.println("*******************   STOP    ****************");
    //delay(2000);
  }
  Serial.println();
  delay(500);

  // slew 0 - 90 by ten degree steps with delay
  for (servonum = 0; servonum < NUMB_SERVOS; servonum++) {
    for (int i = 0; i <= 179; i += 10) {
      int degrees = i;
      int pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
      pwm.setPWM(servonum, 0, pulselength);
      Serial.print("Servo Number = "); Serial.print(servonum);
      Serial.print("  Degrees = "); Serial.println(degrees);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(400);
      digitalWrite(LED_BUILTIN, LOW);
      delay(400);
    }
    delay(500);
    Serial.println();

    // slew 90 - 0 by ten degree steps with delay
    for (int i = 179; i > 0 ; i -= 10) {
      int degrees = i;
      int pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
      pwm.setPWM(servonum, 0, pulselength);
      Serial.print("Servo Number = "); Serial.print(servonum);
      Serial.print("  Degrees = "); Serial.println(degrees);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
    delay(500);
    Serial.println();
  }

  // move to specific degrees
  //for (int servonum = 0; servonum < NUMB_SERVOS; servonum++) {
  servonum = 0; //servo 0 only
  Serial.print("map to specific degrees, servonum = "); Serial.println(servonum);

  int degrees = 0;
  int pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print("  "); Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 90;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 135;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 90;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(" "); Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 45;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(" "); Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 0;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print("  "); Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 90;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);
  Serial.println();

  degrees = 180;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);
  
  degrees = 0;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print("  "); Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);

  degrees = 90;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);
  Serial.println();

  degrees = 180;
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pwm.setPWM(servonum, 0, pulselength);
  Serial.print(degrees); Serial.println(" Degrees");
  delay(4000);
  

  /*
    Serial.println("  ... 5 wild moves ...");
    for (int i = 1; i < 6; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print("i = "); Serial.println(i);
      pwm.setPWM(2, 0, 140);  // servo #1 to CCW
      pwm.setPWM(1, 0, 300);  // servo #1 to CW
      pwm.setPWM(0, 0, 460);  // servo #1 to MID
      delay(500);
      pwm.setPWM(2, 0, 300);  // servo #1 to CW
      pwm.setPWM(1, 0, 460);  // servo #1 to CCW
      pwm.setPWM(0, 0, 140);  // servo #1 to CW
      delay(500);
      pwm.setPWM(2, 0, 460);  // servo #1 to MID
      pwm.setPWM(1, 0, 140);  // servo #1 to CW
      pwm.setPWM(0, 0, 300);  // servo #1 to CW

      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
    }
  */

  Serial.println();

  // wag each servo CCW and CW
  for (servonum = 0; servonum < NUMB_SERVOS; servonum++) {
    // Drive each servo one at a time using setPWM()
    Serial.print("Servo "); Serial.print(servonum); Serial.println(" Wags 0-90-0");
    for (uint16_t pulselen = SERVOMIN_0; pulselen < SERVOMAX_0; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX_0; pulselen > SERVOMIN_0; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
    }
    delay(500);
  }
  delay(500);
  Serial.println(); // print a blank line

  //servonum = 2;
  //int degrees = 90;
  degrees = 90;
  // int pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);
  pulselength = map(degrees, 0, 90, SERVOMIN_0, SERVOMAX_0);

  pwm.setPWM(servonum, 0, pulselength);
  Serial.print("Servo Number = "); Serial.print(servonum);
  Serial.print("  Degrees = "); Serial.println(degrees); Serial.println();
  delay(3000);
}
