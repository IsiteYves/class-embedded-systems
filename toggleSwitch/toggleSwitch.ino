int LED = 2;
int Btn = 3;
int state = 0;
//
void setup(){
  pinMode(LED, OUTPUT);
  pinMode(Btn, INPUT_PULLUP);
}
void loop(){
  //Join pin and ground
  if(digitalRead(Btn) == 0 && state== 0){
    digitalWrite(LED, HIGH);
    state = 1;
  }
  else{
    if(digitalRead(Btn)==0 && state ==1){
      digitalWrite(LED, LOW);
      state == 1;
    }
  }
}
