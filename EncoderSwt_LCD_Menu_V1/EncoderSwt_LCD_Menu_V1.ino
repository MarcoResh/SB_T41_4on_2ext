/*    
      EncoderSwt_LCD_Menu_V1.ino
       Use with SB_T41_4on_2ext or SB_T41_7ext boards
       along with USER-IO_Stereo board which has 
       the Bourns PEC11R-4220K-S0024. A 24 position encoder with switch. 
       This example has 20 Switch...Case sections. Can have up to 24 total.
       In this example the Switch...Case sections just contain dummy
       actions such as "lcd.print("Menu Item 4"); // prints this to LCD"
       They only do an lcd.print(). Nothing else.
       To use, add your functions in each of the Switch...Case sections.

       The void pressHandler() function distinquishes between:
       "Single Push" which could be used to select the currently shown Switch...Case, such as for parameter entry.
       "Double Push" which could be used to erase a parameter that had been entered.
       "Long Push" which could be used to return the Switch...Case to number 1.
       These three could be used in conjuction with your Switch...Case sections is not limited
       to the above. They can be used for whatever you can come up with.
       If another version is created, you must copy the folder "Utility" into the new sketch folder.
*/

// *** start of library declarations, instantiations, and pin assignments ***
#include <Arduino.h>  // use the Arduino.h that came with the IDE

#include "NewEncoder.h"
// Instantiate NewEncoder encoder funtions
// constructor (clk pin, dt pin, min value, max value, initial value, FULL_PULSE or HALF_PULSE)
// T4.1  use: clk IO-9 pin 11 Lft, dt IO-10 pin 12 Lft, start at 0, end at 20, FULL_PULSE
// For USER-IO_Stereo Board use below
NewEncoder encoder(9, 10, 1, 20, 0, FULL_PULSE);// 20 positions, on USER-IO_Stereo board,
//NewEncoder encoder(9, 10, 1, 5, 0, FULL_PULSE);// 5 positions on USER-IO_Stereo board

byte prevEncoderValue;
byte currentEncPosition = 0; // inititalize dentent position of encoder
byte encPosition;  // to take the currentEncPosition found in encoderGetState()out of it
byte prevEncPosition; // used with above
// end of Encoder/Switch configutation

#include "BfButton.h"
byte btnPin = 11; // Push button on encoder IO-11, pin 13 Lft  for SB_7ext_COMBO_ICs with USER-IO_Stereo_I2Cs boards
// Instantiate BfButton switch funtion
//(MODE always STANDALONE_DIGITAL, GPIO PIN, PULLUP TRUE if use Teensy's internal FALSE if use external pulups, Logic LOW if trigger on low V)
BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);
// on Teensy 4.1 on USER-IO_Stereo board

// string variable to hold the type of button push
byte btn_pushType_index; // index for switch/case of button push type
byte prev_btn_pushType_index; // used to determine if btn was pushed

#include <Wire.h> //modified for Wire2 G:\TeensyDuino41_V1-56_Portable\hardware\teensy\avr\libraries\Wire 

#include "LiquidCrystal_I2C.h"  // save LiquidCrystal_I2C.h and .cpp rom John Rickman in this sketches folder
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars by 2 line display

//*** end of library declarations, instantiations, and pin assignments ***


// *** start of new function prototypes. Allows the functions follow void loop(). ***
void setupEncoder(void);
void pressHandler(void);
void buttonTypeDisplay(void);
void instructions(void);
void encoderGetState(void);

void setup() {
  pinMode(btnPin, INPUT_PULLUP);  // ******* not in original code. tried this to make switch work. didn't
  // Setup Teensduino IDE Serial Monitor for diagnostics
  Serial.begin(115200);
  //  while (!Serial) {}  // wait for Serial Monitor to connect.

  Serial.println("Starting");

  setupEncoder();
  instructions();
}  // *** end of void setup() *****

void loop() {
  encoderGetState();
  buttonTypeDisplay();


 if (currentEncPosition != prevEncPosition) {
    Serial.print("in void loop(), currentEncPosition= "); Serial.println(currentEncPosition); Serial.println();
   // worked> prevEncPosition = encPosition;  // if works try prevEncPosition = currentEncPosition, if works delete encPosition
   prevEncPosition = currentEncPosition;  // if works try prevEncPosition = currentEncPosition, if works delete encPosition
    delay(300);
  }

} // *** end of void loop() ******************************************


// *** start of new functions ***

void setupEncoder() {
  // *** setup Encoder with Switch ***
  NewEncoder::EncoderState state;

  if (!encoder.begin()) {
    Serial.println("Encoder Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    encoder.getState(state);
    Serial.print("Encoder Successfully Started at value = ");
    prevEncoderValue = state.currentValue;
    Serial.println(prevEncoderValue);
  }

  //Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout
  .onPressFor(pressHandler, 1000); // custom timeout for 1 second
} // *** end Setup Encoder with Switch ***

// *** Button switch press handling function ***
void pressHandler (BfButton * btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      btn_pushType_index = 1;
      break;

    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      btn_pushType_index = 2;
      break;

    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      btn_pushType_index = 3;
      break;
  }
} //**** end of pressHandler() ****

void buttonTypeDisplay() {
  if ( (btn_pushType_index) != (prev_btn_pushType_index) )
  {
    switch (btn_pushType_index)
    {
      case 1:
        Serial.print("in buttonTypeDisplay(), Case= "); Serial.println(btn_pushType_index); Serial.println();
        delay(50); // diagnostic only, remove when done
        lcd.setCursor(0, 1);
        lcd.print("Single Push     "); // want upper line so no lcd.clear()
        lcd.setCursor(13, 1);
        lcd.print(currentEncPosition);  //
        break;
      case 2:
        Serial.print("in buttonTypeDisplay(), Case= ");  Serial.println(btn_pushType_index); Serial.println();
        lcd.setCursor(0, 1);
        lcd.print("Double Push     "); // want upper line so no lcd.clear()
        lcd.setCursor(13, 1);
        lcd.print(currentEncPosition);  //
        break;
      case 3:
        // Serial.println("in buttonTypeDisplay(), Case3");
        Serial.print("in buttonTypeDisplay(), Case= ");  Serial.println(btn_pushType_index); Serial.println();
        lcd.setCursor(0, 1);
        lcd.print("Long Push       "); // want upper line so no lcd.clear()
        lcd.setCursor(13, 1);
        lcd.print(currentEncPosition);  //
        break;
    }
    btn_pushType_index = prev_btn_pushType_index;
  } //  end of if ( btn_pushType_index != prev...
} // *** end of buttonTypeDisplay() ***

void instructions() {
  lcd.init();   // initialize the lcd
  lcd.backlight(); // illuminate the LCD
  lcd.clear();  // clear LCD
  lcd.setCursor(0, 0);
  lcd.print("Turn to Function");  // value of one "1" for first entry
  lcd.setCursor(1, 1);
  lcd.print("Push to Select"); // prints this to LCD
  delay(1000);
} // *** end of instructions() ***

void encoderGetState() {

  //Wait for button press to execute commands
  btn.read(); // read the encoder's switch

  NewEncoder::EncoderState currentEncoderState;

  if (encoder.getState(currentEncoderState))
  {
    //  lcd.clear();  // clear LCD
    //  Serial.print("Encoder: ");
    currentEncPosition = currentEncoderState.currentValue;  // *change initialization of currentValue to use globally
    if (currentEncPosition != prevEncoderValue)
    {
      delay(50);  // diagnostic
      Serial.print("in encoderGetState() currentEncPosition= "); Serial.println(currentEncPosition);
      delay(50);  // diagnostic
      switch (currentEncPosition)
      {
        case 1:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);   // upper line
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Introduction");
          lcd.setCursor(1, 1);
          lcd.print("Push to Select");
          break;

        case 2:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Thermometer"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;

        case 3:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Talking Thermo"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;

        case 4:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 4"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;

        case 5:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 5"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
      
        case 6:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 6"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 7:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 7"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
         
        case 8:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 8"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
         
        case 9:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 9"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 10:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 10"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;

        case 11:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 11"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 12:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 12"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;

        case 13:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 13"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 14:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 14"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 15:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 15"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 16:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 16"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 17:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 17"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 18:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 18"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 19:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 19"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
          
        case 20:
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          encPosition = currentEncPosition; // try to get this outside the (). 'return' crashed BFButton.h
          lcd.setCursor(3, 0);
          lcd.print("Menu Item 20"); // prints this to LCD
          lcd.setCursor(0, 1);
          lcd.print("Push to Select");
          break;
      }

      prevEncoderValue = currentEncPosition;

      // The encoder moved to a new position but the switch
      //   was not pushed so, clear line 1, the second line.
      // lcd.clear();  // clear LCD
      lcd.setCursor(0, 1);
      lcd.print("Push to Select  ");

    } else

      switch (currentEncoderState.currentClick)
      {
        case NewEncoder::UpClick:
          Serial.println("at upper limit 20");
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);
          lcd.print(currentEncPosition);
          lcd.setCursor(3, 0);
          lcd.print("Blank");
          lcd.setCursor(0, 1);   // lower line
          lcd.print("upper limit 20  ");
          break;

        case NewEncoder::DownClick:
          Serial.println("at lower limit 1");
          lcd.clear();  // clear LCD
          lcd.setCursor(0, 0);   // upper line
          lcd.print(currentEncPosition);
          lcd.setCursor(3, 0);
          lcd.print("Introduction");
          lcd.setCursor(0, 1);   // lower line
          lcd.print("lower limit 1");
          break;

        default:
          break;
      } // end of switch currentEncoderState ... case upclick limit/downclick limit
  } // *** end of if encoder.getstate... ***

}
