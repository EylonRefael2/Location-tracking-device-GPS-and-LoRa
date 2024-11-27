#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <TinyGPSPlus.h>

#define L_RX 3
#define L_TX 2
SoftwareSerial LoRaSerial(L_RX, L_TX); // RX, TX

#define G_RX 5
#define G_TX 6
AltSoftSerial gpsSerial(G_RX, G_TX); // RX, TX

TinyGPSPlus gps;
#define BAUDRATE 115200

void setup() 
{
  Serial.println("start gps"); 
  Serial.begin(BAUDRATE); // USB Serial
  delay(1000);
  LoRaSerial.begin(BAUDRATE); // LoRa Software Serial
  gpsSerial.begin(9600); // NEO6M Software Serial
  
}

void loop() 
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0) 
  {
    if (gps.encode(gpsSerial.read())) 
    {
      displayInfo();
    }
  }
  
  if (millis() > 5000 && gps.charsProcessed() < 10) // if 5 sec passed and we got less then 10 chars 
  {
    Serial.println(F("No GPS detected: check your wiring."));
    while(true);
  }
  
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    String data;
    Serial.println("gps location is Valid");        //To show in the serial monitor that the sketch has started

    data += String(gps.location.lat(), 6);
    data += ",";
    data += String(gps.location.lng(), 6);
    data += "|";
    
    char charArray[20];    
    data.toCharArray(charArray, sizeof(charArray));
    
    sendLoraData(data, 2);
    Serial.println(data);
    Serial.flush();
    delay(3000);
  }
}

void sendLoraData(String data, int address) {
  String myString = "AT+SEND=" + String(address) + "," + String(data.length()) + "," + data + "\r\n";
  char* buf = (char*) malloc(sizeof(char) * myString.length() + 1);
  //Serial.println(myString);
  myString.toCharArray(buf, myString.length() + 1);
  LoRaSerial.write(buf);
  free(buf);
}


void flushSerialBuffer() 
{
  while (Serial.available()) 
  {
    Serial.read();
  }
}
