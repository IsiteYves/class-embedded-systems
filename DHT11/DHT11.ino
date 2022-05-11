#include <dht.h>            //import library for DHT sensor                      

int DHT_data_pin = 10;

dht DHT; //Instantiate object DHT from class dht
void setup() {
  Serial.begin(9600); 
}



void loop(){
  int readDHT = DHT.read11(DHT_data_pin);  //read data packet from DHT sensor 
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);

  Serial.print("C");

  Serial.print("Humidity: ");

  Serial.print(DHT.humidity);

  Serial.println("%");

  delay(3000); //Update after 3 seconds

}
