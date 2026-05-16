#include "DS18B20Handler.hpp"
#include "ADXL345Handler.hpp"
#include "MQTTHandler.hpp"
#include "SubTopic.hpp"
#include "MQTT.hpp"
#include "SSD1306Handler.hpp"

// extern MQTTHandler mqtt_handler;
// extern SubTopic motor1, motor2;
SSD1306Handler oled = SSD1306Handler(21, 22);

void setup() {

  Serial.begin(460800);
  // mqtt_handler.Init();
  // mqtt_handler.AddSubTopic(&motor1);
  // mqtt_handler.AddSubTopic(&motor2);

}

void loop() {
  

}

