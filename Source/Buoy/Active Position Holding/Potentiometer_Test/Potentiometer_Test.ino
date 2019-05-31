#define POT A0

#define POT_MAX 4.5

int oldRead = 0;
int newRead = 0;

const int thrustGear = 72;
const int potGear = 16;

int degree;
int degreeTotal;


int numRotations = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  oldRead = newRead;
  newRead = map (analogRead(POT), 0, 1024, 0, 360);

  if(oldRead == 360 && newRead == 1){
    numRotations +=1;
  }
  if(oldRead == 1 && newRead = 360){
    numRotations -=1;
  }
  else{
    degree += (newRead - oldRead);
  }

  degreeTotal = degree + (306*numRotations);
  Serial.print("Degree: "); Serial.print(degreeTotal); 
  degreeTotal = 0;
}
