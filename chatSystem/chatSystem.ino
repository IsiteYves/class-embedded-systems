#include <SPI.h>
#include <RH_RF95.h>
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RF95_FREQ 950.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);

String reply;
int16_t packetnum = 0; // packet counter incrementing per xmission

void setup(){
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  Serial.begin(9600);
  delay(100);
  
  //Reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()){
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }

  Serial.println("LoRa radio init OK!");
  if(!rf95.setFrequency(RF95_FREQ)){
    Serial.println("setFrequency failed");
    while(1);
  }
  Serial.print("Freq set to: "); Serial.println(RF95_FREQ);
  rf95.setTxPower(23, false);
}
String doTransmit(char* message){
   itoa(packetnum++, message+1600, 10); //we set a message chars to 1600. We can actuallyset any number. I know no limit.
   message[1000] = 0; //Can receive 1000 characters
   delay(10);
   rf95.send((uint8_t *)message, 1001);
   delay(10);
   rf95.waitPacketSent();
   //Get a reply
  
   uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
   uint8_t len = sizeof(buf);

   if(rf95.waitAvailableTimeout(50000)){ 
      if(rf95.recv(buf, &len)){ 
        String mString;
        char* mChar = (char*)buf;    
        return mString+mChar;
      } 
      else{
        return "Receive failed";
      }
   }
   else{
    return "No reply. So no listener around.";
   }       
}
void loop(){
  String mData = Serial.readStringUntil('\n');
  char Buf[mData.length()+1];
  mData.toCharArray(Buf, mData.length()+1);

  if(mData.length()>0){
  String reply = doTransmit(Buf);
  Serial.print(Buf);
    if(reply.length()>0){      
      
      Serial.print("Verite: ");
      Serial.println(reply);
    }
  }
  //switch to receiver
  
  doReceive();
}
//doReceive function
void doReceive(){
  if(rf95.available()){
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if(rf95.recv(buf, &len)){
    char* mChar = (char*)buf;
    Serial.println(mChar);
  }
  else{
    Serial.println("Receive failed");
  }
}  
}
