 /* 1-Wire_Multiple_Temps.ino
 *  Sensors wired in parallel to IO-12 on the 
 *  SB_T41_4on_2ext boards. Same IO pins.
 *  Use DS18B20 temperature sensor.
 */
 
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 12 on the Arduino
#define ONE_WIRE_BUS 12

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;

void setup(void)
{
  sensors.begin();  // Start up the library
  sensors.setResolution(10); // resolution 0.125C, takes minimum of 188mS
  Serial.begin(9600);

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop(void)
{
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures();

  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print( "\xC2\xB0"); // shows degree symbol
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print( "\xC2\xB0"); // shows degree symbol
    Serial.println("F");
  }

  Serial.println("");
  delay(1000);
}
