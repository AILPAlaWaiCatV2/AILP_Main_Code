/*
 * GPS Coordinate Difference Code
 * By: Shane Matsushima
 * 4/5/2019
 */


/*
 * This define is used as a base for figuring out coordinate difference to feet
 */
#define coordToFt 0.000003

/*
 * Integer used to declare specific string array place in array of GPS points
 */ 
int i = 0;

/*
 * These char are declared for the seperation of user inputs for desire and actual GPS
 */
char coordArray[100];
char delimiter = 32;
char* valPosition;

/*
 * Final variables used for difference math
 */
double totalChangeRawX;
double totalChangeRawY;
double totalChangeFeetX;
double totalChangeFeetY;

/*
 * Return values for later functions for moving in a specific direction
 */
double travelWest;
double travelEast;
double travelNorth;
double travelSouth;

/*
 * Variables for inputing into the coordDif function
 */
double desireX;
double desireY;
double actualX;
double actualY;

/*
 * String array used as place holder for user input desire and actual coordinates 
 */
String splited[4];

/*
 * String variables of desired and actual GPS coordinates
 */
String stringDesireX;
String stringDesireY;
String stringActualX;
String stringActualY;

/*
 * This function takes the desired and actual gps coordinates and returns the difference based compass and feet 
 */
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

/*
 * This function resets the data needed to travel so that the data being sent out is new and up to date 
 */
void Reset(){
  travelWest = 0;
  travelEast = 0;
  travelSouth = 0;
  travelNorth = 0;
}

/*
 * This function allows the program to grab specific coordinates from the user input in the serial monitor. The user must place the GPS coordinates accordingly based on the How To Use that is displayed
 */
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

/*
 * This function is run once at the beginning of the program. This is where the program alerts the user on how to utilize this program. 
 */
void setup() {
Serial.begin(9600);
Serial.println("This code showcases the difference in coordinated from the GPS module. It will display the direction the actual Device is based on the desired coordinate");
Serial.println("Direction from desire: distance away");
Serial.println("------Example------");
Serial.println("E: 24.5, N: 10.34");
Serial.println("This means the device would have to move 24.5 feet west and 10.34 feet south to get to the designated or desired location");
Serial.println("-----How To Use-----");
Serial.println("Place the desired data first, seperating the X and Y coordinates. And then place the actual GPS Data using spaces to sepserate");
Serial.println("Press Enter and wait for the system to calculate the difference in the X and Y coordinate");
Serial.println("------Example------");
Serial.println("24.38 34.28 54.56 48.97");
}

/*
 * THis function allows the user to run the program continously. This portion grabs data that the user inputs in the serial monitor and uses the function from before to print a direction and distance needed to travel. 
 */
void loop() {
  if(Serial.available()){
    String grabData = Serial.readString();
    getCoord(grabData);
    coordDif(desireX, desireY, actualX, actualY);
    Reset();
    
  }
}
