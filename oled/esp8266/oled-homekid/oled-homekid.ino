/* this is  a fork of https://github.com/klarsys/esp8266-OLED structore was changed so it can be added to arduino std libraries
  This is an [esp8266-Arduino](https://github.com/esp8266/Arduino) library for I2C-OLED displays.

  ## Credits

  Original code was taken from [ESP8266-I2C-OLED](https://github.com/costonisp/ESP8266-I2C-OLED) project and was modified in form of a library suitable for using with [Arduino IDE](https://www.arduino.cc/en/Main/Software).
*/


#include <Wire.h>
#include <BME280I2C.h>
#include "OLED.h"         // https://github.com/klarsys/esp8266-OLED



#define OLED_SDA  13
#define OLED_SCL  14

OLED display(OLED_SDA, OLED_SCL);
BME280I2C bme;

//-----------------------------------------------------------------

void drawWithMetricUnits(float tempC, float humidity, float pressurePascals)
{

  float pressureHectoPascals = pressurePascals / 100.0;

  display.clear();
  display.print("BME280", 1, 5);

  char charBuf[5];
  String stringOne = String(tempC);
  stringOne.toCharArray(charBuf, 5);

  display.print("Temp = ", 3,1);
  display.print(charBuf, 3, 8);
  display.print(" *C", 3, 12);

  stringOne = String(humidity);
  stringOne.toCharArray(charBuf, 5);

  display.print("HUMI = ", 5,1);
  display.print(charBuf, 5, 8);
  display.print(" %", 5, 12);


  stringOne = String(pressureHectoPascals);
  stringOne.toCharArray(charBuf, 5);

  display.print("BARO = ", 7,1);
  display.print(charBuf, 7, 8);
  display.print(" hPa", 7, 12);

  // display.print("Humidity = " + String(humidity) + "%",5);
  // display.print("Pressure = " + String(pressureHectoPascals) + " h,Pa",5);
}

//-----------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  Wire.begin();


  //BME280 init
  while (!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  switch (bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      Serial.println("Found BME280 sensor! Success.");
      break;
    case BME280::ChipModel_BMP280:
      Serial.println("Found BMP280 sensor! No Humidity available.");
      break;
    default:
      Serial.println("Found UNKNOWN sensor! Error!");
  }
}
//-----------------------------------------------------------------

void loop() {

  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);

  //Serial.println("Temp = " + String(temp) + " *C");
  // Serial.println();

  // Initialize display
  display.begin();

  // Display data on screen in metric units
  drawWithMetricUnits(temp, hum, pres);

  delay(10000);

  ESP.reset();
}
