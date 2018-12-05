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
char recVal[9];
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
  Serial.readBytes(recVal, 8);


    if(recVal[0] == 'T'){
    String tempRaw = String(recVal);
    String tempSend = tempRaw.substring(1,8);
    float tempValSend = tempSend.toFloat();
    Serial.println(tempvalSend);
    client1.add(ID1, tempValSend);
    client1.sendAll();
    }
      
    if(recVal[0] == 'P'){
    String phRaw = String(recVal);
    String phSend = phRaw.substring(1,8);
    float phValSend = phSend.toFloat();
    Serial.println(phValSend);
    client1.add(ID2, phValSend);
    client1.sendAll();
    }

    if(recVal[0] == 'D'){
    String dRaw = String(recVal);
    String dSend = dRaw.substring(1,8);
    float dValSend = dSend.toFloat();
    Serial.println(dValSend);
    client1.add(ID1, dValSend);
    client1.sendAll();
    }
    
    if(recVal[0] == 'C'){
    String cRaw = String(recVal);
    String cSend = cRaw.substring(1,8);
    float cValSend = cSend.toFloat();
    client1.add(ID1, cValSend);
    client1.sendAll();
    }


  
  }
}
