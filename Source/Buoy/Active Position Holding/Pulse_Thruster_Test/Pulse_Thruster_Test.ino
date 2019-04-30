/*
 * Pulse Thruster For Active Position Holding Testing 
 * By: Shane Matsushima
 * 4/25/2019
 */

/*
 * This is the library used for controlling the thrustermotor via ESC
 */
#include <Servo.h>

/*
 * Attaching the thruster motor to the Servo Class
 */
Servo thruster;

/*
 * Thruster pin 
 */
#define THRUSTER_PIN 11

/*
 * Defining direction/power variable for moving the thruster
 */
#define FORWARD_POWER 2000
#define REVERSE_POWER 1000
#define STOP 1500

/*
 * This runs once before the full program starts and allocates what each pin is doing
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting Pulse Code");
  thruster.attach(THRUSTER_PIN);
}

/*
 * This is the main portion of the code that runs infinetly unless told otherwise
 */
void loop() {
  /*
   * Pulses the thruster forward with max power for 1 sec and then stops the thrusting for 1 sec 
   */
  thruster.write(FORWARD_POWER);
  wait();
  thruster.write(STOP);
  wait();
}

/*
 * Used as a delay code for delaying the start and stop and duration of how long the pulse is 
 */
void wait(){
  delay(1000);
}
