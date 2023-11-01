/* Test_PIR_4on2ext_V1.ino
 *  Uses SB_T41_4on_2ext Board.
 *  Hiletgo SR602 PIR Sensor. The round shaped type. 
 *  https://www.amazon.com/HiLetgo-Detector-Pyroelectric-Infrared-Sensitivity/dp/B07VLFL5VP
 *  This sensor may be wired to the SB_T41_4on_2ext at location labelled PIR 
 *  or it may be directly soldered to the USER-IO_Stereo. The Front Panel has a 
 *  small guide hole which may be drilled out to enable the PIR to mount.
 *  The AM312 and HC-SR505 sensors also works but have different pinout 
 *  so won't directly connect to USER-IO_Stereo.
 *  The Teensy 4.1 LED_BUILTIN turns on and the Serial Monitor displays "Sensor High"
 *  and "Motion detected!" when a person moves. Sensitivity to about ten feet.
 *  
 */

int sensor = 15;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // initalize LED at IO pin 13 as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(115200);        // initialize serial
}

void loop(){
 // Serial.println("In void loop");
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(LED_BUILTIN, HIGH);   // turn LED ON
     Serial.println("Sensor High");
    delay(500);                // delay 500 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(LED_BUILTIN, LOW); // turn LED OFF
       Serial.println("Sensor Low");
      delay(500);             // delay 500 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}
