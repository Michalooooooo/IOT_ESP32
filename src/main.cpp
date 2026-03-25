// #include <Arduino.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_ADXL345_U.h>
// #include <Wire.h>

#include "DS18B20Handler.hpp"
// Adafruit_ADXL345_Unified acc = Adafruit_ADXL345_Unified(12345);

// void setup() {
//   Serial.begin(9600);
//   if(!acc.begin()) {
//     Serial.println("ADXL345 not detected");
//     while(1) {}
//   }

// }

// void loop() {
//   sensors_event_t event;
//   acc.getEvent(&event);
//   Serial.print("X: ");
//   Serial.print(event.acceleration.x);
//   Serial.println(" ");
//   Serial.print("Y: ");
//   Serial.print(event.acceleration.y);
//   Serial.println(" ");
//   Serial.print("Z: ");
//   Serial.print(event.acceleration.z);
//   Serial.println(" ");
//   delay(500);
// }

DS18B20Handler tmp_sensor = DS18B20Handler(4);

void setup() {
  Serial.println("Start pomiaru temperatury...");
}

void loop() {
  tmp_sensor.DisplayCurrentTemperature();

  delay(1000);
}
