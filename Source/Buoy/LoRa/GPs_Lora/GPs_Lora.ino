

//Libraries included 
#include <SPI.h>
#include <RH_RF95.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//Defining pins that the LoRa breakout baord uses
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0


//Defining LED pin for checking if the system sent a packet
#define LED 13

 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

float lati;
float lon;

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
 
void setup() 
{
  //connects LED pin to an output (LED is an output)
  pinMode(LED, OUTPUT); 
  pinMode(RFM95_RST, OUTPUT);
  
  digitalWrite(RFM95_RST, HIGH);
 
  Serial.begin(9600);
  ss.begin(GPSBaud);
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
}

// packet counter, we increment per xmission
int16_t packetnum = 0;  
 
void loop()
{
  Serial.println("Sending to rf95_server");
   gps.encode(ss.read());
    if (gps.location.isUpdated()){
      lati = gps.location.lat();
      Serial.println(lati, 18);
      Serial.println(lon, 18);
      lon = gps.location.lng();
    }

  Serial.println(lati, 18);
  Serial.println(lon, 18);

  String latNumStr = String(lati);
  String lonNumStr = String(lon);

  char latNumChar[18];
  char lonNumChar[18];

  latNumStr.toCharArray(latNumChar, 18);
  lonNumStr.toCharArray(lonNumChar, 18);

  char radiopacket[18];

  for(int i = 0; i <= 17; i++){
    radiopacket[i] = latNumChar[i];  
  }
  //sends the [acket of data while indicating it sent using the LED
  Serial.println(radiopacket);
  if(rf95.send(radiopacket, 18))
  {
    digitalWrite(LED, HIGH);
  }

  for(int x = 0; x <= 17; x++)
  {
    radiopacket[x] = lonNumChar[x];
  }
 Serial.println(radiopacket);
    //sends the [acket of data while indicating it sent using the LED
  if(rf95.send(radiopacket, 18))
  {
    digitalWrite(LED, HIGH);
  }
  
  digitalWrite(LED, LOW);
  Serial.println("Waiting for packet to complete..."); delay(10);
  rf95.waitPacketSent();
  
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
 
  Serial.println("Waiting for reply..."); delay(10);
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  delay(1000);
}

//function to grab the temperature data as a float 
float getLat()
{
   gps.encode(ss.read());
    if (gps.location.isUpdated()){
      lati = gps.location.lat();
      return lati;
  }
}

float getLon()
{
   gps.encode(ss.read());
    if (gps.location.isUpdated()){ 
      lon = gps.location.lng();
      return lon;
}
}
