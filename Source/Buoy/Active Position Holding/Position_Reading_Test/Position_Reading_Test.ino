int encoder = A3;
int startDegree;
int startvalue;
int lastDegree;
int finalDegree = 0;

int rotation = 0
;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(encoder, INPUT);
  startValue = analogRead(encoder);
  startDegree = map(startValue, 0, 1023, 0, 360);
  lastDegree = startDegree;
  
}

void countRotate(){
  rotation++;
  Serial.print("Full Rotations: ");
  Serial.println(rotation);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
