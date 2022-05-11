int motorForwardPin = 2;
int motorReversePin = 3;

void setup(){ 
  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(motorReversePin, LOW);  
  digitalWrite(motorForwardPin, HIGH);  
  delay(2000);
  digitalWrite(motorForwardPin, LOW);
  digitalWrite(motorReversePin, LOW);
  delay(1000); 

  digitalWrite(motorForwardPin, LOW);
  digitalWrite(motorReversePin, HIGH);
  delay(2000);   
}
