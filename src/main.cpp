#include "DS18B20Handler.hpp"

DS18B20Handler tmp_sensor = DS18B20Handler(4);

void setup() {
  Serial.println("Start pomiaru temperatury...");
}

void loop() {
  tmp_sensor.DisplayCurrentTemperature();

  delay(1000);
}
