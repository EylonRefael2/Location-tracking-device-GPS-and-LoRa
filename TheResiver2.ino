
#include <SoftwareSerial.h>

#define RX 1
#define TX 2
SoftwareSerial LoRaSerial(RX, TX); // RX, TX

void setup() {
  Serial.begin(11520); // USB Serial
  delay(1000);
  Serial.println("stat");
  LoRaSerial.begin(11520); // LoRa Software Serial
}

void loop()
{
  while (LoRaSerial.available()) // Check if data is available on Software Serial
  {
    String data = LoRaSerial.readString(); //String response = LoRaSerial.readStringUntil('\n');
    Serial.println(data); // Send data to USB Serial
  }
}
