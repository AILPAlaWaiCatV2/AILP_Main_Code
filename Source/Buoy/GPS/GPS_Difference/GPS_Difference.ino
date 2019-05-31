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
float desireX;
float desireY;
float actualX;
float actualY;

/*
 * String array used as place holder for user input desire and actual coordinates 
 */
String splited[4];

/*
 * String variables of desired and actual GPS coordinates
 */
String coordinate[4] = {"stringDesireX", "stringDesireY", "stringActualX", "stringActualY"};

/*
 * Float array for holding the distance needed to get to the desired coordinate
 * Organization is N, E, S, W
 */
double distance[4];

/*
 * This function takes the desired and actual gps coordinates and returns the difference based compass and feet 
 */
double coordDif(double desireX, double desireY, double actualX, double actualY){
  
  totalChangeRawX = desireX - actualX;
  totalChangeRawY = desireY - actualY;
  
  totalChangeFeetX = totalChangeRawX/coordToFt;
  totalChangeFeetY = totalChangeRawY/coordToFt;

  Serial.println("Direction:");

  if(totalChangeRawX < 0){
    Serial.print("E: ");
    Serial.print(abs(totalChangeFeetX), 10);
    Serial.print(", ");
    
    travelEast = abs(totalChangeFeetX);
    
  }
  
   else if(totalChangeRawX > 0){
    Serial.print("W: ");
    Serial.print(abs(totalChangeFeetX), 10);
    Serial.print(", ");
    
    travelWest = abs(totalChangeFeetX);
    
  }
  
  if(totalChangeRawY > 0){
    Serial.print("S: ");
    Serial.print(totalChangeFeetY, 10);
    Serial.println();

    travelSouth = abs(totalChangeFeetY);
    
  }
  
  if(totalChangeRawY < 0){
    Serial.print("N: ");
    Serial.print(abs(totalChangeFeetY), 10);
    Serial.println();

    travelNorth = abs(totalChangeFeetY);
    
  }

  distance[0] = travelNorth;
  distance[1] = travelEast;
  distance[2] = travelSouth;
  distance[3] = travelWest;

  return distance[4];
}

/*
 * This function resets the data needed to travel so that the data being sent out is new and up to date 
 */
void Reset(){
  for(int i = 0; i < 4; i++){
    distance[i] = 0;
  }
}

/*
 * This function allows the program to grab specific coordinates from the user input in the serial monitor. The user must place the GPS coordinates accordingly based on the How To Use that is displayed
 */
double getCoord(String coordinates){
  coordinates.toCharArray(coordArray, 65);
  
  int x =0;
  for(int i = 0; i < 4; i++){
    coordinate[i] = "";
    }
  for(int i = 0; i < 65; i++){
    if(coordArray[i] == ' '){
     x++;
    }
    else{
      coordinate[x]+=coordArray[i];
    }
  }
  
  
  desireX = coordinate[0].toFloat();
  desireY = coordinate[1].toFloat();
  actualX = coordinate[2].toFloat();
  actualY = coordinate[3].toFloat();

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
 * This function allows the user to run the program continously. This portion grabs data that the user inputs in the serial monitor and uses the function from before to print a direction and distance needed to travel. 
 */
void loop() {
  if(Serial.available()){
    String grabData = Serial.readString();
    Serial.println(grabData);
    
    getCoord(grabData);
    Serial.println("Return:");
    Serial.print("DesiredX:");Serial.print(desireX, 6);Serial.print("\t");
    Serial.print("DesiredY:");Serial.print(desireY, 6);Serial.print("\t");
    Serial.print("ActualX:");Serial.print(actualX, 6);Serial.print("\t");
    Serial.print("ActualY:");Serial.print(actualY, 6);Serial.print("\t");Serial.println();
    
    coordDif(desireX, desireY, actualX, actualY);
    
    Serial.print("Distance Array: ");
    
    for(int i = 0; i < 4; i++){
      Serial.print(distance[i]);
      Serial.print(" ");
    }
    Serial.println();
    
    Reset();
    
  }
}
