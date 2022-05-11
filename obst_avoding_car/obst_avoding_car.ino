int leftMotorForwardPin = 3;
int leftMotorReversePin = 2;
int rightMotorForwardPin = 10;
int rightMotorReversePin = A5;
int trigPin = 6;
int echoPin = A4;
int LED = 12;
int buzzer = 13;
long duration, distance;
void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(leftMotorReversePin, OUTPUT);
  pinMode(leftMotorForwardPin, OUTPUT);
  pinMode(rightMotorReversePin, OUTPUT);
  pinMode(rightMotorForwardPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  /*Transmit a signal and get an echoed signal.
    Then calculate the distance from the obstacle*/
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  // distance=4;
  delay(10);
  /*
    If distance between robot car and and obstacle is still above 50cm,
    the robot car will keep on moving forward
  */
  if (distance <= 10) {
    /* The robot car will stop for a second... */
    digitalWrite(LED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorReversePin, LOW);
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorReversePin, LOW);
    delay(1000);
    /* ... then move backward for half a second... */
    digitalWrite(LED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorReversePin, HIGH);
    digitalWrite(leftMotorForwardPin, HIGH);
    digitalWrite(leftMotorReversePin, LOW);
    delay(500);
    /* ... then stop for half a second... */
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorReversePin, LOW);
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorReversePin, LOW);
    delay(500);
    /* ... then turn left for half a second... */
    digitalWrite(rightMotorForwardPin, HIGH);
    digitalWrite(rightMotorReversePin, LOW);
    digitalWrite(leftMotorReversePin, LOW);
    digitalWrite(leftMotorForwardPin, LOW);
    delay(500);
  }
  else {
    digitalWrite(LED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(leftMotorForwardPin,HIGH);
    digitalWrite(leftMotorReversePin,LOW);
    digitalWrite(rightMotorForwardPin,HIGH);
    digitalWrite(rightMotorReversePin,LOW);
  }
}
