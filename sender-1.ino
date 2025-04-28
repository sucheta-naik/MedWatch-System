#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust LCD address and size as needed
PulseOximeter pox;

#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(9600); // Initialize serial communication with ESP8266
  lcd.init();   // Initialize the LCD with column and row numbers
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Initialize MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED");
    lcd.setCursor(0, 1);
    lcd.print("MAX30100 not found");
    while (1);
  } else {
    Serial.println("SUCCESS");
    lcd.setCursor(0, 1);
    lcd.print("MAX30100 found");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float spO2 = pox.getSpO2();

    lcd.setCursor(0, 0);
    lcd.print("Heart rate: ");
    lcd.print(heartRate);
    lcd.print(" bpm    "); // Ensure the previous text is cleared

    lcd.setCursor(0, 1);
    lcd.print("SpO2: ");
    lcd.print(spO2);
    lcd.print(" %     "); // Ensure the previous text is cleared

    // Send data to ESP8266
    String data = "Heart rate:" + String(heartRate) + ", SpO2:" + String(spO2);
    Serial.println(data);

    tsLastReport = millis();
  }
}
