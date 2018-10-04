#include <Wire.h>
#include "TSYS01.h"

/* Pin Layout
 *  Converter - Arduino Uno
 *  SDA - A4
 *  SCL - A5
 *  GND - GND
 *  5v - 5v
 */

TSYS01 sensor;

void setup() {

  Serial.begin(9600);
  
  Serial.println("Starting");
  
  Wire.begin();

  sensor.init();

}

void loop() {

  sensor.read();
 
  Serial.print("Temperature: ");
  Serial.print(sensor.temperature()); 
  Serial.println(" deg C");
   
  Serial.println("---");

  delay(1000);
}
