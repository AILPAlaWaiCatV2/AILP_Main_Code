/*
 * Notes:
  LH = Ch4
  LV = CH3
  RH = CH1
  RV = CH2
*/


#include <EnableInterrupt.h>

#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3


//motor throttle
int pwm1 = 5;
int in1 = 8;
int in2 = 7;

//motor rotate
int pwm2 = 6;
int in3 = 9;
int in4 = 4;

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

void rotF(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void rotR(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void throtF(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void throtR(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);

  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
int rotPower = constrain(abs(map(rc_values[RC_CH1], 980, 2000, -255, 255)), 0, 255);
int throtPower = constrain(abs(map(rc_values[RC_CH2], 980, 2000, -255, 255)), 0, 255);
  rc_read_values();
  Serial.print("rotPower:"); Serial.print(rotPower);
  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("CH4:"); Serial.print(rc_values[RC_CH4]); Serial.print("\t");
  Serial.print("Rotate Direction: ");


if(rc_values[RC_CH1] < 1420){
  rotR();
  analogWrite(pwm2, rotPower);
  Serial.print("Clockwise");
}
else if(rc_values[RC_CH1] > 1580){
  rotF();
  analogWrite(pwm2, rotPower);
  Serial.print("CounterClockwise");
}
else{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(pwm2, 0);
}

Serial.print("\t"); Serial.print("Throttle Direction: ");

if(rc_values[RC_CH2] < 1420){
  throtR();
  analogWrite(pwm1, throtPower);
  Serial.print("Reverse");
}
else if(rc_values[RC_CH2] > 1580){
  throtF();
  analogWrite(pwm1, throtPower);
  Serial.print("Forward");
}
else{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(pwm1, 0);
}
Serial.println();
}
