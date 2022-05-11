int LED = 3;

void setup(){  
  pinMode(LED, OUTPUT);
}

void loop(){
  digitalWrite(LED, HIGH);  
  delay(2000);  
  digitalWrite(LED, LOW);   
  delay(1000);     
}

if(message == 'ON){
  digitalWrite(relayPin, HIGH);
}else if(message == 'OFF' ){
  digitalWrite(relayPin, LOW)
}
