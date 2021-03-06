#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "Place Variable ID here" //temp
#define ID2 "Place Variable ID here" //pH
#define ID3 "Place Variable ID here" //Conductivity
#define ID4 "Place Variable ID here" //Dissolved Oxygen
#define CAT1 "Place Variable ID here" //temp
#define CAT2 "Place Variable ID here" //pH
#define CAT3 "Place Variable ID here" //Conductivity
#define CAT4 "Place Variable ID here" //Dissolved Oxygen
#define CAT5 "Place Variable ID here" //Lon
#define CAT6 "Place Variable ID here" //Lat
#define TOKEN "Place Token Here"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Wifi Name"
#define PASSWORD "Wifi Password"

#define NAME "Device Name"


String sendvalue;
char recVal[9];


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

client1.wifiConnection(WIFISSID, PASSWORD);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("*");
  if (Serial.available()){
    Serial.readBytes(recVal, 8);
    Serial.println(recVal);

    //-------Buoy A---------
  
    if(recVal[0] == 'A'){
      if(recVal[1] == 'T'){
        String tempRaw = String(recVal);
        String tempSend = tempRaw.substring(2,8);
        float tempValSend = tempSend.toFloat();
        Serial.print("Sending Temp: ");
        Serial.println(tempValSend);
        client1.add(ID1, tempValSend);
        client1.sendAll();
        }
      
      if(recVal[1] == 'P'){
        String phRaw = String(recVal);
        String phSend = phRaw.substring(2,8);
        float phValSend = phSend.toFloat();
        Serial.print("Sending pH: ");
        Serial.println(phValSend);
        client1.add(ID2, phValSend);
        client1.sendAll();
        }

      if(recVal[1] == 'D'){
        String dRaw = String(recVal);
        String dSend = dRaw.substring(2,8);
        float dValSend = dSend.toFloat();
        Serial.print("Sending DO: ");
        Serial.println(dValSend);
        client1.add(ID4, dValSend);
        client1.sendAll();
        }
    
      if(recVal[1] == 'C'){
        String cRaw = String(recVal);
        String cSend = cRaw.substring(2,8);
        float cValSend = cSend.toFloat();
        Serial.print("Sending Temp: ");
        Serial.println(cValSend);
        client1.add(ID3, cValSend);
        client1.sendAll();
      }
    }

        //-------Buoy I---------
  
    if(recVal[0] == 'I'){
      if(recVal[1] == 'T'){
        String tempRaw = String(recVal);
        String tempSend = tempRaw.substring(1,8);
        float tempValSend = tempSend.toFloat();
        Serial.println(tempValSend);
        client1.add(ID1, tempValSend);
        client1.sendAll();
        }
      
      if(recVal[1] == 'P'){
        String phRaw = String(recVal);
        String phSend = phRaw.substring(1,8);
        float phValSend = phSend.toFloat();
        //Serial.println(phValSend);
        client1.add(ID2, phValSend);
        client1.sendAll();
        }

      if(recVal[1] == 'D'){
        String dRaw = String(recVal);
        String dSend = dRaw.substring(1,8);
        float dValSend = dSend.toFloat();
        //Serial.println(dValSend);
        client1.add(ID4, dValSend);
        client1.sendAll();
        }
    
      if(recVal[1] == 'C'){
        String cRaw = String(recVal);
        String cSend = cRaw.substring(1,8);
        float cValSend = cSend.toFloat();
        client1.add(ID3, cValSend);
        client1.sendAll();
      }
    }

        //-------Buoy L---------
  
    if(recVal[0] == 'L'){
      if(recVal[1] == 'T'){
        String tempRaw = String(recVal);
        String tempSend = tempRaw.substring(1,8);
        float tempValSend = tempSend.toFloat();
        Serial.println(tempValSend);
        client1.add(ID1, tempValSend);
        client1.sendAll();
        }
      
      if(recVal[1] == 'P'){
        String phRaw = String(recVal);
        String phSend = phRaw.substring(1,8);
        float phValSend = phSend.toFloat();
        //Serial.println(phValSend);
        client1.add(ID2, phValSend);
        client1.sendAll();
        }

      if(recVal[1] == 'D'){
        String dRaw = String(recVal);
        String dSend = dRaw.substring(1,8);
        float dValSend = dSend.toFloat();
        //Serial.println(dValSend);
        client1.add(ID4, dValSend);
        client1.sendAll();
        }
    
      if(recVal[1] == 'C'){
        String cRaw = String(recVal);
        String cSend = cRaw.substring(1,8);
        float cValSend = cSend.toFloat();
        client1.add(ID3, cValSend);
        client1.sendAll();
      }
    }

        //-------Buoy P---------
  
    if(recVal[0] == 'P'){
      if(recVal[1] == 'T'){
        String tempRaw = String(recVal);
        String tempSend = tempRaw.substring(1,8);
        float tempValSend = tempSend.toFloat();
        Serial.println(tempValSend);
        client1.add(ID1, tempValSend);
        client1.sendAll();
        }
      
      if(recVal[1] == 'P'){
        String phRaw = String(recVal);
        String phSend = phRaw.substring(1,8);
        float phValSend = phSend.toFloat();
        //Serial.println(phValSend);
        client1.add(ID2, phValSend);
        client1.sendAll();
        }

      if(recVal[1] == 'D'){
        String dRaw = String(recVal);
        String dSend = dRaw.substring(1,8);
        float dValSend = dSend.toFloat();
        //Serial.println(dValSend);
        client1.add(ID4, dValSend);
        client1.sendAll();
        }
    
      if(recVal[1] == 'C'){
        String cRaw = String(recVal);
        String cSend = cRaw.substring(1,8);
        float cValSend = cSend.toFloat();
        client1.add(ID3, cValSend);
        client1.sendAll();
      }
    }

        //------CAT-------
   if(recVal[0] == 'C'){
     if(recVal[1] == 'T'){
        String tempRaw = String(recVal);
        String tempSend = tempRaw.substring(1,8);
        float tempValSend = tempSend.toFloat();
        Serial.println(tempValSend);
        client1.add(CAT1, tempValSend);
        client1.sendAll();      
      }

     if(recVal[1] == 'P'){
        String phRaw = String(recVal);
        String phSend = phRaw.substring(1,8);
        float phValSend = phSend.toFloat();
        //Serial.println(phValSend);
        client1.add(CAT2, phValSend);
        client1.sendAll();      
     }

     if(recVal[1] == 'D'){
        String dRaw = String(recVal);
        String dSend = dRaw.substring(1,8);
        float dValSend = dSend.toFloat();
        //Serial.println(dValSend);
        client1.add(CAT3, dValSend);
        client1.sendAll();      
     }

     if(recVal[1] == 'C'){
        String cRaw = String(recVal);
        String cSend = cRaw.substring(1,8);
        float cValSend = cSend.toFloat();
        client1.add(CAT4, cValSend);
        client1.sendAll();      
     }

     if(recVal[1] == 'X'){
        String xRaw = String(recVal);
        String xSend = xRaw.substring(1,25);
        float xValSend = xSend.toFloat();
        client1.add(CAT5, xValSend);
        client1.sendAll();
     }

     if(recVal[1] == 'Y'){
        String yRaw = String(recVal);
        String ySend = yRaw.substring(1,25);
        float yValSend = ySend.toFloat();
        client1.add(CAT6, yValSend);
        client1.sendAll();
     }
   }
  }
}
