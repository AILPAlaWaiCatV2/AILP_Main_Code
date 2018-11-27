

#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "5bef2e86c03f97550c8b5d5f" //temp
#define ID2 "5bef2e8bc03f97550c8b5d63" //pH
#define ID3 "5bef2e98c03f97558e49cc37" //Conductivity
#define ID4 "5bef2eadc03f97558e49cc48" //Dissolved Oxygen
#define TOKEN "A1E-OIKQ1rDhI0vq6NgdbDu1B3YOmWDrZN"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Palila"
#define PASSWORD "io71redbird51"

#define NAME "Iolani MonKit 1"


String sendvalue;
char tempval[7];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//while(!Serial){;}
client1.wifiConnection(WIFISSID, PASSWORD);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("*");
  if (Serial.available()){
     Serial.readBytes(tempval, 6);
Serial.println( tempval);
String tempSend(tempval);
float tempValSend = tempSend.toFloat();
Serial.println( tempValSend);
     
    //Serial.write(tempval);
  if(tempValSend > 10.00){
  client1.add(ID1, tempValSend);
  client1.sendAll();
    } 
  }
}
