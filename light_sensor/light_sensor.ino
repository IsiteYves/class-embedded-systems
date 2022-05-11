int lightSensorPin = A0;
int RELAY=3;
int lightIntensity;
void setup(){
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}
void loop(){
  lightIntensity = analogRead-(lightSensorPin);
  if(lightIntensity<400) {
    digitalWrite(RELAY, LOW);
    delay(2000); 
    }else{
      digitalWrite(RELAY, HIGH);
      delay(2000);}
  Serial.println(lightIntensity);
  delay(200);
}`
