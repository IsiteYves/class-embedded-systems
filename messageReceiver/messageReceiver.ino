#include <SPI.h>
#include <RH_RF95.h>
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RF95_FREQ 970.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);


void setup(){ 
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);
    Serial.begin(9600);
    
    while (!Serial){
        delay(1);
    }
    
    Serial.println("LoRa RX Test!");
    digitalWrite(RFM95_RST, LOW);
    digitalWrite(RFM95_RST, HIGH);
    while (!rf95.init()) {
        Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1)
        ;
    }
    Serial.println("LoRa radio init OK!");
    if (!rf95.setFrequency(RF95_FREQ)) {
            Serial.println("setFrequency failed");
            while (1)
                ;
    }
    Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    rf95.setTxPower(23, false);
}


void loop(){

  doReceive();

}



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


void doReply(uint8_t data[]){

  rf95.send(data, 160); //I know no limit of characters per message!

  rf95.waitPacketSent();

}
