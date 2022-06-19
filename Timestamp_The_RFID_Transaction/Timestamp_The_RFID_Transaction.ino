#include <SPI.h>
#include <MFRC522.h>
#include "DS1302.h" 
#define RST_PIN 9           
#define SS_PIN 10  
#define ResetPin 7  
#define DataPin 6  
#define ClockPin 5 
 
DS1302 rtc(ResetPin, DataPin, ClockPin); //Create a DS1302 object
MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
MFRC522::StatusCode card_status;
void setup(){
    Serial.begin(9600); 
    rtc.writeProtect(false); // turn off write protection
    rtc.halt(false); // clear the clock halt flag  
    /*
    rtc.time(t);  is only used to set time. 
    Other times it will be commented out.
    The format for Time t() is t(year,month,date,hour,minutes,seconds,day)
    */
    Time t(2022, 6, 6, 14, 57, 10, Time::kMonday); 
    rtc.time(t); //use it ONLY to set time. Otherwise, comment it out.                                          
    SPI.begin();
    mfrc522.PCD_Init();                                             
    Serial.println(F("System Ready!"));
}
void loop(){
    byte block_number = 4;
    byte buffer_for_reading[18];
    for (byte i = 0; i < 6; i++){
        key.keyByte[i] = 0xFF;
    }
    if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
        return;
    }
    String initial_balance = readBalanceFromCard(block_number, buffer_for_reading);
    operateData(block_number, initial_balance); 
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}
String readBalanceFromCard(byte blockNumber, byte readingBuffer[]){
    card_status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
    if(card_status != MFRC522::STATUS_OK){
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(card_status));
        return;
    }
    byte readDataLength = 18;
    card_status = mfrc522.MIFARE_Read(blockNumber, readingBuffer, &readDataLength);
    if(card_status != MFRC522::STATUS_OK){
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(card_status));
        return;
    }
    String value = "";
    for (uint8_t i = 0; i < 16; i++){
        value += (char)readingBuffer[i];
    }
    value.trim();
    
    return value;
}
bool saveBalanceToCard(byte blockNumber, byte writingBuffer[]){
    card_status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &key, &(mfrc522.uid));
    if(card_status != MFRC522::STATUS_OK){
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(card_status));
        return;
    }
    else{
        //Serial.println(F("PCD_Authenticate() success: "));
    }
    // Write block
    card_status = mfrc522.MIFARE_Write(blockNumber, writingBuffer, 16);
    if(card_status != MFRC522::STATUS_OK){
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(card_status));
        return;
    }
    else{
        //Serial.println(F("Data saved."));
        delay(5000);
        return true;
    }
}
void operateData(byte blockNumber, String initialBalance){
    int fareToKimironko = 450;
    float newBalance = initialBalance.toInt()-fareToKimironko;
    if(initialBalance.toInt()<fareToKimironko){
        Serial.print("Insufficient Balance: ");
        Serial.println(initialBalance); 
        return;
    }
    String initial_balance_str;
    char writingBuffer[16];
    initial_balance_str = (String)newBalance;
    initial_balance_str.toCharArray(writingBuffer, 16);
    int strLeng = initial_balance_str.length()-3;
    /*
    * This servers to add spaces to the typed text in order to fill up to 16 characters
    */
    for(byte i = strLeng; i < 30; i++){
        writingBuffer[i] = ' ';     
    }
    Serial.println("_______________________________");
    Serial.println("New transaction processing...");
    Serial.println("********************");
    if(saveBalanceToCard(blockNumber, writingBuffer)==true){
        Serial.print("Initial Balance: ");
        Serial.println(initialBalance); 
        Serial.print("Fare to Kimironko: ");
        Serial.println(fareToKimironko);
        Serial.print("New Balance: ");
        Serial.println(newBalance);   
    }
    else{
        Serial.print("Transaction Failed.\nPlease try again.\n"); 
    }
    
    char * timearray = readTime();
    Serial.print("Timestamp: ");
    Serial.println(timearray);
    Serial.println("********************");
    Serial.println("Status: Success");
    Serial.println("_______________________________");  
}
String dayAsString(const Time::Day day) { // function that converts the day ouptput into a string
    switch (day) {
        case Time::kSunday: return "Sunday";
        case Time::kMonday: return "Monday";
        case Time::kTuesday: return "Tuesday";
        case Time::kWednesday: return "Wednesday";
        case Time::kThursday: return "Thursday";
        case Time::kFriday: return "Friday";
        case Time::kSaturday: return "Saturday";
    }
    return "(unknown day)";
}
char * readTime(){
    Time t = rtc.time(); // get the time and date from the chip.
    const String day = dayAsString(t.day); // obtain text for the day of the week
    static char CurrentTime[50]; // initialise a character array to hold the date text
    snprintf(
        CurrentTime, 
        sizeof(CurrentTime), 
        "%s %04d-%02d-%02d %02d:%02d:%02d", 
        day.c_str(), 
        t.yr, 
        t.mon, 
        t.date, 
        t.hr, 
        t.min, 
        t.sec
    ); // format the time into the character array
    return CurrentTime; // return the current time
}
