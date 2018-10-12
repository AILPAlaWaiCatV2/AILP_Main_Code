#include <Wire.h>
#include <UbidotsFONA.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define APN  "xxxxxxxxxx"  // The APN of your operator
#define USER "xxxxxxxxxx"  // if your apn doesnt have username just leave it ""
#define PASS "xxxxxxxxxx"  // if your apn doesnt have password just leave it ""
#define TOKEN "A1E-4gfwu1P5Vt4Gi6L3m7y5ziXpoRPD52"  
#define VARIABLE_LABEL_1 "Temperature" 
#define VARIABLE_LABEL_2 "pH" 
#define VARIABLE_LABEL_3 "Conductivity" 
#define VARIABLE_LABEL_4 "Dissolved Oxygen"

char sensordata[30];
byte sensor_bytes_received = 0; 

byte code = 0; 
byte in_char = 0;

#define TOTAL_CIRCUITS 4

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

int channel_ids[] = {102, 97, 99, 100};

char *channel_names[] = {"RTD", "DO", "PH", "EC"}; 

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

Ubidots client(TOKEN);



void setup() {                        
  Wire.begin();    
    while (! Serial);

  Serial.begin(115200);
  Serial.println(F("Adafruit FONA 808 & 3G GPS demo"));
  Serial.println(F("Initializing FONA... (May take a few seconds)"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));
  

  Serial.println(F("Enabling GPS..."));
  fona.enableGPS(true);

  client.setDebug(true);
  while(!client.setApn(APN, USER, PASS));
}



void loop() {
  readGPS();
  for (int channel = 0; channel < TOTAL_CIRCUITS; channel++) {   

    Wire.beginTransmission(channel_ids[channel]);
    Wire.write('r');               
    Wire.endTransmission();                      

    delay(1000); 

    sensor_bytes_received = 0;                 
    memset(sensordata, 0, sizeof(sensordata));   

    Wire.requestFrom(channel_ids[channel], 48, 1);  
    code = Wire.read();

    while (Wire.available()) {        
      in_char = Wire.read();           

      if (in_char == 0) {        
        Wire.endTransmission();       
        break;                 
      }
      else {
        sensordata[sensor_bytes_received] = in_char;      
        sensor_bytes_received++;
      }
    }

    switch (code) {                        
      case 1:                               
        Serial.println(sensordata);      
        break; 
                                      
      case 2:                              
        Serial.println("command failed");   
        break;                                 

      case 254:                             
        Serial.println("circuit not ready");
        break;                                 

      case 255:                              
        Serial.println("no data");          
        break;                                
    }
   if(channel_names[channel] == "RTD"){
    float temp = atof(sensordata);
    client.add(VARIABLE_LABEL_1, temp);
   }
   if(channel_names[channel] == "DO"){
    float dissolved = atof(sensordata);
    client.add(VARIABLE_LABEL_4, dissolved);
   }
   if(channel_names[channel] == "PH"){
    float pH = atof(sensordata);
    client.add(VARIABLE_LABEL_2, pH);
   }
   
   if(channel_names[channel] == "EC"){
    float conduct = atof(sensordata);
    client.add(VARIABLE_LABEL_3, conduct);
   }
   
   client.sendAll();
  } 
   

}

void readGPS(){
    delay(2000);

  float latitude, longitude, speed_kph, heading, speed_mph, altitude;

  // if you ask for an altitude reading, getGPS will return false if there isn't a 3D fix
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);

  if (gps_success) {

    Serial.print("GPS lat:");
    Serial.println(latitude, 6);
    Serial.print("GPS long:");
    Serial.println(longitude, 6);
    Serial.print("GPS speed KPH:");
    Serial.println(speed_kph);
    Serial.print("GPS speed MPH:");
    speed_mph = speed_kph * 0.621371192;
    Serial.println(speed_mph);
    Serial.print("GPS heading:");
    Serial.println(heading);
    Serial.print("GPS altitude:");
    Serial.println(altitude);

  } else {
    Serial.println("Waiting for FONA GPS 3D fix...");
  }

  // Fona 3G doesnt have GPRSlocation :/
  if ((fona.type() == FONA3G_A) || (fona.type() == FONA3G_E))
    return;
  // Check for network, then GPRS 
  Serial.println(F("Checking for Cell network..."));
  if (fona.getNetworkStatus() == 1) {
    // network & GPRS? Great! Print out the GSM location to compare
    boolean gsmloc_success = fona.getGSMLoc(&latitude, &longitude);

    if (gsmloc_success) {
      Serial.print("GSMLoc lat:");
      Serial.println(latitude, 6);
      Serial.print("GSMLoc long:");
      Serial.println(longitude, 6);
    } else {
      Serial.println("GSM location failed...");
      Serial.println(F("Disabling GPRS"));
      fona.enableGPRS(false);
      Serial.println(F("Enabling GPRS"));
      if (!fona.enableGPRS(true)) {
        Serial.println(F("Failed to turn GPRS on"));  
      }
    }
  }
}
