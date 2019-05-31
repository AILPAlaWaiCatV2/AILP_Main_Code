#include <Servo.h>

#define MOTOR_THRUST_PIN 11

#define THROTTLE_JOY 3
#define ROTATE_JOY 10

#define MOTOR_PWM 6
#define MOTOR_A1 4
#define MOTOR_B1 9

int throttleJoy;
int rotateJoy;

int throttlePower;
int rotatePower;

Servo motorThrust;

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

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);

  motorThrust.attach(MOTOR_THRUST_PIN);

  Serial.begin(57600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  throttleJoy = pulseIn(THROTTLE_JOY, HIGH);
  rotateJoy = pulseIn(ROTATE_JOY, HIGH);

  Serial.print("Throttle: "); Serial.print(throttleJoy); Serial.print("\t");
  Serial.print("Rotate: "); Serial.print(rotateJoy); Serial.print("\t");

  rotatePower = constrain(abs(map(rotateJoy, 980, 2000, -255, 255)), 0, 255);
  throttlePower = map(throttleJoy, 980, 2000, 1000,2000);

  Serial.print("Rotate Power: "); Serial.print(rotatePower); Serial.print("\t");
  Serial.print("Rotate Direction: ");
  if(rotateJoy > 1000){
      if(rotateJoy < 1400){
        CCW();
        analogWrite(MOTOR_PWM, rotatePower);
        Serial.print("CCW");
      } 
      else if(rotateJoy > 1500){
        CW();
        analogWrite(MOTOR_PWM, rotatePower);
        Serial.print("CW");
      }
      else{
        brake();
      }
  }
  Serial.print("\t");
  Serial.print("Thruster Direction: ");
  if(throttleJoy > 1000){
  if(throttleJoy < 1400){
    motorThrust.write(throttlePower);
    Serial.print("BACKWARD");
  }
  else if(throttleJoy > 1500){
    motorThrust.write(throttlePower);
    Serial.print("FORWARD");
  }
  else{
    motorThrust.write(0);
    
  }
  }
  Serial.println();

  
}
