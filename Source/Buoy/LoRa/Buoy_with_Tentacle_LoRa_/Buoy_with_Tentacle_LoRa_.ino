#include <Wire.h> 
#include <SPI.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3

// standard pins for the shield, adjust as necessary
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4



#define LED 13

char sensordata[30];
byte sensor_bytes_received = 0; 

byte code = 0; 
byte in_char = 0;

#define TOTAL_CIRCUITS 4

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

int channel_ids[] = {102, 97, 99, 100};

char *channel_names[] = {"RTD", "DO", "PH", "EC"}; 

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);



void setup() {                        
  Wire.begin();    
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
   pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
 
 // while (!Serial); // remove if not tethered to computer (looks for serial monitor to open)
  Serial.begin(9600);
  delay(100);
 
  Serial.println("Arduino LoRa TX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

 int16_t packetnum = 0;  // packet counter, we increment per xmission

   fona.enableGPS(true);

}



void loop() {
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

    
    
   if(channel_names[channel] == "RTD"){
    float temp = atof(sensordata);
    String tempNumStr = String(temp);
    char tempNumChar[6];
    tempNumStr.toCharArray(tempNumChar, 6);
    char radiopacketTemp[7] = "T     ";
    for(int i = 1; i <= 5; i++){
      radiopacketTemp[i] = tempNumChar[i - 1];
    }
    radiopacketTemp[6] = 0;
    rf95.send(radiopacketTemp, 7);
    Serial.println(radiopacketTemp);
   }

   
   if(channel_names[channel] == "DO"){
    float dissolved = atof(sensordata);
    String disNumStr = String (dissolved);
    char disNumChar[6];
    disNumStr.toCharArray(disNumChar, 6);
    char radiopacketDis[7] = "D     ";
    for(int x = 1; x<=5; x++){
      radiopacketDis[x] = disNumChar[x - 1];
    }
    radiopacketDis[6] = 0;
    rf95.send(radiopacketDis, 7);
    Serial.println(radiopacketDis);
   }

   
   if(channel_names[channel] == "PH"){
    float pH = atof(sensordata);
    String pHNumStr = String(pH);
    char pHNumChar[6];
    pHNumStr.toCharArray(pHNumChar, 6);
    char radiopacketpH[7] = "P     ";
    for(int y = 1; y <= 5; y++){
      radiopacketpH[y] = pHNumChar[y - 1];
    }
    radiopacketpH[6] = 0;
    rf95.send(radiopacketpH, 7);
    Serial.println(radiopacketpH);
   }

   
   if(channel_names[channel] == "EC"){
    float conduct = atof(sensordata);
    String conNumStr = String(conduct);
    char conNumChar[6];
    conNumStr.toCharArray(conNumChar, 6);
    char radiopacketCon[7] = "C     ";
    for(int c = 1; c <= 5; c++){
      radiopacketCon[c] = conNumChar[c - 1];
    }
    radiopacketCon[6] = 0;
    rf95.send(radiopacketCon, 6);
    Serial.println(radiopacketCon);
   }

     float latitude, longitude;
     fona.getGPS(&latitude, &longitude);
     
     String latNumStr = String(latitude);
     char latNumChar[32];
     latNumStr.toCharArray(latNumChar, 32);
     char radiopacketLat[33];
     radiopacketLat[0] = 'X';
     for(int lat = 1; lat <= 31; lat++){
      radiopacketLat[lat] = latNumChar[lat];
     }
     radiopacketLat[32] = 0;
     rf95.send(radiopacketLat, 33);
     String lonNumStr = String(longitude);
     char lonNumChar[32];
     lonNumStr.toCharArray(lonNumChar, 32);
     char radiopacketLon[33];
     radiopacketLon[0] = 'Y';
     for(int lon = 1; lon <= 31; lon++){
      radiopacketLon[lon] = lonNumChar[lon];
     }
     radiopacketLon[32] = 0;
     rf95.send(radiopacketLon, 33);
     
   
  } // for loop 
   

} // void loop
