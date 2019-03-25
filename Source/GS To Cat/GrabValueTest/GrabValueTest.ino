#include "UbidotsMicroESP8266.h"

#define ID  "5bef2e98c03f97558e49cc37"  // Put here your Ubidots variable ID
#define TOKEN  "A1E-OIKQ1rDhI0vq6NgdbDu1B3YOmWDrZN"  // Put here your Ubidots TOKEN
#define WIFISSID "Palila" //change to WIFI name
#define PASSWORD "io71redbird51" //change to WIFI password

Ubidots client1(TOKEN);

void setup() {
    Serial.begin(115200);
    client1.wifiConnection(WIFISSID, PASSWORD);
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}
void loop() {
    float value = client1.getValueWithId(ID);
    if (value != ERROR_VALUE){
      Serial.print(F("value obtained: "));
      Serial.println(value);
    }else{
      Serial.println(F("Error getting value"));
    }
    delay(1000);
}
