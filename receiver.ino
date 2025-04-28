#include <SoftwareSerial.h>

// Define pin numbers if using a standard Arduino board
const int RX_PIN = 10;  // Example RX pin
const int TX_PIN = 11;  // Example TX pin

SoftwareSerial espSerial(RX_PIN, TX_PIN); // RX, TX (Change pins as necessary)

void setup() {
  Serial.begin(9600);   // Serial monitor baud rate
  espSerial.begin(9600);  // Serial communication with Arduino

  Serial.println("ESP8266 Receiver Ready");
}

void loop() {
  if (espSerial.available()) {
    String data = espSerial.readStringUntil('\n');
    Serial.println("Received data: " + data);
  }
  delay(100); // Small delay to avoid excessive Serial Monitor output
}
