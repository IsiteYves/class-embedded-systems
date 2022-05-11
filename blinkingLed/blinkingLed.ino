int LED = 3
;
int BUZZER = 12;

void setup() {

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
  
  digitalWrite(LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(800);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
  delay(10888);

}
