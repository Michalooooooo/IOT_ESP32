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
#include <stdint.h>

uint8_t ctr = 0;


void on_click() { Serial.printf("%u Wcisnieto przycisk! \n", ctr); ctr++; }
void on_release() { Serial.printf("%u Puszczono przycisk! \n", ctr); ctr++; }

Button b1(BUTTON_NO, 32, on_click, on_release);

void setup() {

  Serial.begin(115200);
  Serial.println("START");

}

void loop() {
  b1.Update();

}

