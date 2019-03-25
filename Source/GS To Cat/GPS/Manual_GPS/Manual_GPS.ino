#include <SPI.h>
#include <RH_RF95.h>
 
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

char gpsid = "G";

int check = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while (!Serial){ //comment out when not in use
  Serial.println("Error");
}
Serial.println(" To write the GPS coordinate, follow the layout: 'X:#, Y:#'");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String r = Serial.readString();
    char gpspacket[50];
    r.toCharArray(gpspacket, 50);
    char radiopacket[51];
    radiopacket[0] = gpsid;
    for (int y = 1; y <= 50; y++){
      radiopacket[y] = gpspacket[y];
    }
    rf95.send(radiopacket, 51);
    Serial.println(r);
    Serial.println(radiopacket);
  }
  //Serial.println("*"); //Test: comment out 
}
