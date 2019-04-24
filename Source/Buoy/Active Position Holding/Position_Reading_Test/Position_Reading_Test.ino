int encoder = A3;
unsigned long duration;
unsigned long startValue;
int lastDegree;
int presentDegree;
int startDegree;
int finalDegree = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(encoder, INPUT);
  startValue = analogRead(encoder);
  startDegree = map(startValue, 0, 1023, 0, 360);
  lastDegree = startDegree;
}

void loop() {
  // put your main code here, to run repeatedly:
  lastDegree = presentDegree;
  duration = analogRead(encoder);
  presentDegree = map(duration, 0, 1023, 0, 360);
  
  if(presentDegree > lastDegree){
    finalDegree = finalDegree + presentDegree;
    Serial.println(finalDegree);
  }
  if(presentDegree < lastDegree){
    finalDegree = finalDegree - presentDegree;
    Serial.println(finalDegree);
  }
  else{
    finalDegree = finalDegree;
    Serial.println(finalDegree);
  }
}
