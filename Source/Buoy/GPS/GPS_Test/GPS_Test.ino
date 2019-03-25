#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 7, TXPin = 6;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

float lati;
float lon;

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      lati = gps.location.lat();
      Serial.print(lati, 18);
      Serial.print(" Longitude= "); 
      lon = gps.location.lng();
      Serial.println(lon, 18);
    }
  }
}
