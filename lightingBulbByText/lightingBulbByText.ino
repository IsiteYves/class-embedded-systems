int LED =3;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); // set the digital pin as output:
  digitalWrite(LED, HIGH);
}

void loop() {
  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if(command == "ON")
    {
      digitalWrite(LED, LOW); // turn on LED
      Serial.println("LED is turned ON"); // send action to Serial Monitor
    }
    else
    if(command == "OFF")
    {
      digitalWrite(LED, HIGH);  // turn off LED
      Serial.println("LED is turned OFF"); // send action to Serial Monitor
    }
  }
}
