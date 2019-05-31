/*
 * Buoy Auto Position Holding Code 
 * By: Shane Matsushima
 * 5/21/2019
 */

/*
 * Libraries used for the GPS
 */
  #include <TinyGPS++.h>
  #include <SoftwareSerial.h>
  
/*
 * Library for the thruster control
 */
  #include <Servo.h>

/*
 * Pins used for controlling the rotating of the Buoy
 */
  #define MOTOR_PWM 6
  #define MOTOR_A1 4
  #define MOTOR_B1 9

/*
 * Pin used for controlling the Thruster motor (signal pin for the ESC)
 */
  #define MOTOR_THRUST_PIN 11

/*
 * This define is used as a base for figuring out coordinate difference to feet
 */
  #define COORD_TO_FT 0.000003

/*
 * Defining the power for the rotating motor and Thrusting motor on the Buoy
 */
  #define ROTATE_POWER_MAX 175
  #define THRUST_POWER_MAX 1750
  #define THRUST_POWER_MIN 1250

/*
 * Defining the Desired coordinate for the Buoy to hold
 */
 #define DESIREX 21.285604
 #define DESIREY -157.824996

/*
 * variables used for the GPS 
 */
  static const int RXPin = 0, TXPin = 1;
  static const uint32_t GPSBaud = 9600;

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
  float actualX;
  float actualY;

/*
 * Variables for the grabbing of longitude and langitude from the GPS
 */
  double lati;
  double lon; 

/*
 * Double array for holding the distance needed to get to the desired coordinate
 * Organization is N, E, S, W
 */
  double distance[4];

/*
 * Declaring the thrust motor as a servo for the library
 */
  Servo motorThrust;

/*
 * TinyGPS++ object declaration
 */
  TinyGPSPlus gps;

/* 
 * The serial connection to the GPS device
 */
  SoftwareSerial ss(RXPin, TXPin);

/*
 * Functions for controlling the direction and signal for the rotating motor on the Buoy
 */
  void motor(int pin, int input){
    analogWrite(pin, input);
  }

  void CW(){
    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_B1, HIGH);
  }

  void CCW(){
    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_B1, LOW);
  }

  void brake(){
    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_B1, LOW);
  }

/*
 * These functions runs the Thruster motor 
 */
void thrustForward(){
  motorThrust.write(THRUST_POWER_MAX);
}

void thrustReverse(){
  motorThrust.write(THRUST_POWER_MIN);
}

/*
 * This function takes the desired and actual gps coordinates and returns the difference based compass and feet 
 */
  double coordDif(double desireX, double desireY, double actualX, double actualY){
  
    totalChangeRawX = desireX - actualX;
    totalChangeRawY = desireY - actualY;
  
    totalChangeFeetX = totalChangeRawX/COORD_TO_FT;
    totalChangeFeetY = totalChangeRawY/COORD_TO_FT;

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
 * These function is used to grab GPS coordinate
 */
  double getLon(){
    gps.encode(ss.read());
    lon = gps.location.lng();
    return lon;
  }

  double getLat(){
    gps.encode(ss.read());
    lati = gps.location.lat();
    return lati;
  }

/*  
 * This function checks if all distances for in each compass heading is 0
 */
  bool atDesire(){
    if((distance[0] == 0) && (distance[1] == 0) && (distance[2] == 0) && (distance[3] == 0)){
      return true;
    }
    else{
      return false;
    }
  }

  void setup() {
    // put your setup code here, to run once:

    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);

    motorThrust.attach(MOTOR_THRUST_PIN);

    Serial.begin(9600);
    Serial.println("Initializing Position Holding For Buoy...");
    Serial.print("Desired X: "); Serial.print(DESIREX); Serial.print("\t");
    Serial.print("Desired Y: "); Serial.print(DESIREY); Serial.println();

    ss.begin(GPSBaud);

    Reset();
    
  }

  void loop() {
    // put your main code here, to run repeatedly:
   coordDif(DESIREX, DESIREY, getLon(), getLat());
   
   while(!(atDesire())){
   
   }


   
  }
