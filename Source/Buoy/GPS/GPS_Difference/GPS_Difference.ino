/*
 * GPS Coordinate Difference Code
 * By: Shane Matsushima
 * 4/5/2019
 * 
 * Note: 0.000003 in coordinates is about 1 foot 
 */

#define coordToFt 0.000003

int i = 0;

char coordArray[100];
char delimiter = 32;
char* valPosition;

double totalChangeRawX;
double totalChangeRawY;
double totalChangeFeetX;
double totalChangeFeetY;

double travelWest;
double travelEast;
double travelNorth;
double travelSouth;

double desireX;
double desireY;
double actualX;
double actualY;

String splited[4];

String stringDesireX;
String stringDesireY;
String stringActualX;
String stringActualY;

double coordDif(double desireX, double desireY, double actualX, double actualY){
  totalChangeRawX = desireX - actualX;
  totalChangeRawY = desireY - actualY;
  totalChangeFeetX = totalChangeRawX/coordToFt;
  totalChangeFeetY = totalChangeRawY/coordToFt;

  if(totalChangeRawX > 0){
    Serial.print("E: ");
    Serial.print(totalChangeFeetX);
    Serial.print(", ");
    
    travelEast = totalChangeFeetX;
    return travelEast;
  }
  if(totalChangeRawX < 0){
    Serial.print("W: ");
    Serial.print(abs(totalChangeFeetX));
    Serial.print(", ");

    travelWest = abs(totalChangeFeetX);
    return travelWest;
  }
  if(totalChangeRawY > 0){
    Serial.print("S: ");
    Serial.print(totalChangeFeetY);
    Serial.println();

    travelSouth = totalChangeFeetY;
    return travelSouth;
  }
  if(totalChangeRawY < 0){
    Serial.print("N: ");
    Serial.print(abs(totalChangeFeetY));
    Serial.println();

    travelNorth = abs(totalChangeFeetY);
    return travelNorth;
  }
  
}

void Reset(){
  travelWest = 0;
  travelEast = 0;
  travelSouth = 0;
  travelNorth = 0;
}

double getCoord(String coordinates){
  coordinates.toCharArray(coordArray, 65);
  valPosition = strtok(coordArray, delimiter);
  while(valPosition != NULL){
    splited[i] = valPosition;
    i++;
  }
  stringDesireX = splited[0];
  stringDesireY = splited[1];
  stringActualX = splited[2];
  stringActualY = splited[3];
  desireX = stringDesireX.toDouble();
  desireY = stringDesireY.toDouble();
  actualX = stringActualX.toDouble();
  actualY = stringActualY.toDouble();
  return desireX;
  return desireY;
  return actualX;
  return actualY;
  
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("This code showcases the difference in coordinated from the GPS module. It will display the direction the actual Device is based on the desired coordinate");
Serial.println("Direction from desire: distance away");
Serial.println("------Example------");
Serial.println("E: 24.5, N: 10.34");
Serial.println("This means the device would have to move 24.5 feet west and 10.34 feet south to get to the designated or desired location");
Serial.println("-----How To Use-----");
Serial.println("Place the desired data first, seperating the X and Y coordinates. And then place the actual GPS Data using spaces to sepserate");
Serial.println("Press Enter and wait for the system to calculate the difference in the X and Y coordinate");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char grabData = Serial.read();
    getCoord(grabData);
    coordDif(desireX, desireY, actualX, actualY);
    Reset();
    
  }
}
