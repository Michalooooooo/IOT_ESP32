// #include "DS18B20Handler.hpp"
// #include "ADXL345Handler.hpp"
// #include "MQTTHandler.hpp"
// #include "SubTopic.hpp"
// #include "MQTT.hpp"
// #include "SSD1306Handler.hpp"

// // extern MQTTHandler mqtt_handler;
// // extern SubTopic motor1, motor2;
// SSD1306Handler oled = SSD1306Handler(21, 22);
#include "Button.hpp"
#include <Arduino.h>

void* on_click() { Serial.println("Wcisnieto przycisk!"); }
void* on_release() { Serial.println("Puszczono przycisk!"); }

Button b1(BUTTON_NO, 14, on_click, on_release);

void setup() {

  Serial.begin(460800);

}

void loop() {
  b1.Update();

}

