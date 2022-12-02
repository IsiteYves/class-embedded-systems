#include <ESP8266WiFi.h>
#include <DHT.h>
DHT dht(14,DHT11); //pin14 is equivalent to D5 on esp8266 board

WiFiClient wifiClient;    
const char* host = "iot.benax.rw";

void readDHT11(String(&params)[3]){
  float Humidity = 0.0;
  float Temperature = 0.0;
  float HeatIndex = 0.0;
  /*Read temperature and humidity from DHT sensor*/
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  /*The block of code below checks if either temperature or humidity failed
  and then exits early, allowing you not to waste a time.*/
  if(isnan(Humidity) || isnan(Temperature)){
    Serial.println("Failed to read from DHT sensor.");
    params [0] = "";
    params [1] = "";
    params [2] = "";
  }
  else{
    /*Calculate Heat Index */
    HeatIndex = dht.computeHeatIndex(Temperature, Humidity, false);
    params [0] = String(Temperature);
    params [1] = String(Humidity);
    params [2] = String(HeatIndex);
  }
}
void loop(){
    String data[3];
    readDHT11(data);
    String temperature = data[0];
    if(temperature!=""){
      String humidity = data[1];
      String heat_index = data[2];
      String payload="";
      String device = "WEATHER-TRACK017";
      payload = "device="+device+"&temperature="+temperature+"&humidity="+humidity+"&heat_index="+heat_index;    
      connectToHost(80);
      upload(payload, "/projects/b9a31af7237a309d8f2654f837fd2871/Esp8266_dht_project/backend.php");
    }
    else{
      Serial.println("Sensor reading failed.");
    }
    delay(30000);  
}

void connectToWiFi(const char* ssid, const char* passwd){
    WiFi.mode(WIFI_OFF); //This prevents reconnection issue
    delay(10);
    WiFi.mode(WIFI_STA); //This hides the viewing of ESP as wifi hotspot
    WiFi.begin(ssid, passwd); //Connect to your WiFi router
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi Connected.");
    Serial.println();  
}

void connectToHost(const int httpPort){
    int retry_counter=0; //To be used while retrying to get connected
    wifiClient.setTimeout(15000); // 15 Seconds
    delay(1000);
    Serial.printf("Connecting to \"%s\"\n", host);
  
    while((!wifiClient.connect(host, httpPort)) && (retry_counter <= 30)){
      delay(100);
      Serial.print(".");
      retry_counter++;
    }
  
    if(retry_counter==31){
      Serial.println("\nConnection failed.");
      return;
    }
    else{
      Serial.println("Connected.");
    }   
}

void upload(String data, const char* filepath){
    wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
    wifiClient.println("Host: " + (String)host);
    wifiClient.println("User-Agent: ESP8266/1.0");
    wifiClient.println("Content-Type: application/x-www-form-urlencoded");
    wifiClient.println("Content-Length: " +(String)data.length());
    wifiClient.println();
    wifiClient.print(data); 
    Serial.println("Uploading data...");
    parseResponse("Success");
}


/*
 * GET FEEDBACK
*/
void parseResponse(String success_msg){
    String datarx;
    while (wifiClient.connected()){
        String line = wifiClient.readStringUntil('\n');
        if (line == "\r") {
        break;
        }
    }
    while (wifiClient.available()){
        datarx += wifiClient.readStringUntil('\n');
    }

    if(datarx.indexOf(success_msg) >= 0){
        Serial.println("Uploaded.\n");  
    }
    else{
        Serial.println("Failed.\n"); 
    }
    Serial.println("*******************\n");
    datarx = "";  
}

void setup(){
    Serial.begin(115200);
    dht.begin();
    connectToWiFi("NXT", "esyvpluk");                                                                                          
}
