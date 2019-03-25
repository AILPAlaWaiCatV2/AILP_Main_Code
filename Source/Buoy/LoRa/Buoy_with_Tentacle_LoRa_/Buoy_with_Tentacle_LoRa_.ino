/**
 * Created By: Shane Matsushima 
 * Date: 12/5/2018
 * For: Data Sending from Buoy (Advanced Innovation and Leadership Project)
 * Description:
 *  Used for Sending data from the Buoy to the main hub where the NodeMCU is located
 *  Data being transmited consists of pH, temperature, conductivity, and dissolved oxygen
 *  The use of a LoRa, Tentacle Shield, and Arduino Uno is used for this code. This code incorporates the continuous reading
 *  code from White Box and incorporates LoRa. 
 *  Please check the gitHub for partnering codes 
 */


//Libraries needed for this code
#include <Wire.h> 
#include <SPI.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//Declaration of pins used for the LoRa 
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
/*
// standard pins for the shield, adjust as necessary
#define FONA_RX 7
#define FONA_TX 6
#define FONA_RST 8
*/
//check LED to make sure data is being sent
#define LED 13


//Change based on buoy name: (A, I, L, P)
char buoyID[1] = "A";

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

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

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() 
{ 
                         
  Wire.begin();    
  Serial.begin(9600);
  
  pinMode(LED, OUTPUT);
   pinMode(RFM95_RST, OUTPUT);
   
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
 
  Serial.println("Arduino LoRa TX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) 
  {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) 
  {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

 // packet counter, we increment per xmission
 int16_t packetnum = 0; 

  ss.begin(GPSBaud);

}



void loop() {

  //cycles through I2C channels grabbing sensor data from the Tentacle
  for (int channel = 0; channel < TOTAL_CIRCUITS; channel++) 
  {   

    Wire.beginTransmission(channel_ids[channel]);
    Wire.write('r');               
    Wire.endTransmission();                      

    delay(1000); 

    sensor_bytes_received = 0;                 
    memset(sensordata, 0, sizeof(sensordata));   

    Wire.requestFrom(channel_ids[channel], 48, 1);  
    code = Wire.read();

    while (Wire.available()) 
    {        
      in_char = Wire.read();           

      if (in_char == 0) 
      {        
        Wire.endTransmission();       
        break;                 
      }
      else 
      {
        sensordata[sensor_bytes_received] = in_char;
        //sendLat();
        //sendLon();      
        sensor_bytes_received++;
      }
    }

    //checks for channel being called and sending the data received from the designated sensor through the LoRa
    
   if(channel_names[channel] == "RTD")
   {
      float temp = atof(sensordata);
      String tempNumStr = String(temp);
      char tempNumChar[6];
      tempNumStr.toCharArray(tempNumChar, 6);
      char radiopacketTemp[8] = " T     ";
      radiopacketTemp[0] = buoyID[0];
      for(int i = 2; i <= 6; i++)
      {
        radiopacketTemp[i] = tempNumChar[i - 1];
      }
      
      radiopacketTemp[7] = 0;
      rf95.send(radiopacketTemp, 8);
      Serial.println(radiopacketTemp);
   }

   
   if(channel_names[channel] == "DO")
   {
      float dissolved = atof(sensordata);
      String disNumStr = String (dissolved);
      char disNumChar[6];
      disNumStr.toCharArray(disNumChar, 6);
      char radiopacketDis[8] = " D     ";
      radiopacketDis[0] = buoyID[0];
      for(int x = 2; x<=6; x++)
      {
        radiopacketDis[x] = disNumChar[x - 1];
      }
      
      radiopacketDis[7] = 0;
      rf95.send(radiopacketDis, 8);
      Serial.println(radiopacketDis);
   }

   
   if(channel_names[channel] == "PH"){
    float pH = atof(sensordata);
    String pHNumStr = String(pH);
    char pHNumChar[6];
    pHNumStr.toCharArray(pHNumChar, 6);
    char radiopacketpH[8] = " P     ";
    radiopacketpH[0] = buoyID[0];
    for(int y = 2; y <= 6; y++){
      radiopacketpH[y] = pHNumChar[y - 1];
    }
    radiopacketpH[7] = 0;
    rf95.send(radiopacketpH, 8);
    Serial.println(radiopacketpH);
   }

   
   if(channel_names[channel] == "EC"){
    float conduct = atof(sensordata);
    String conNumStr = String(conduct);
    char conNumChar[6];
    conNumStr.toCharArray(conNumChar, 6);
    char radiopacketCon[8] = " C     ";
    radiopacketCon[0] = buoyID[0];
    for(int c = 2; c <= 6; c++){
      radiopacketCon[c] = conNumChar[c - 1];
    }
    radiopacketCon[7] = 0;
    rf95.send(radiopacketCon, 7);
    Serial.println(radiopacketCon);
   }

   
  } // for loop 
   

} // void loop


float sendLat(){
      gps.encode(ss.read());
        String latNumStr = String(gps.location.lat(), 6);
      char latNumChar [11];
      latNumStr.toCharArray(latNumChar, 11);
      char radiopacketLat[12] = "X         ";
      for(int l = 1; l <= 11; l++){
        radiopacketLat[l] = latNumChar[l - 1];
      }
      radiopacketLat[11] = 0;
      rf95.send(radiopacketLat, 12);
      Serial.println(radiopacketLat);
}

float sendLon(){
      gps.encode(ss.read());
      String lngNumStr = String(gps.location.lng(), 6);
      char lngNumChar [11];
      lngNumStr.toCharArray(lngNumChar, 11);
      char radiopacketLng[12] = "Y         ";
      for(int l = 1; l <= 11; l++){
        radiopacketLng[l] = lngNumChar[l - 1];
      }
      radiopacketLng[11] = 0;
      rf95.send(radiopacketLng, 12);
      Serial.println(radiopacketLng);
}
