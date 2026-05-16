#pragma once

#include "MQTTHandler.hpp"
#include "SubTopic.hpp"

void callback1() {
  Serial.println("Wywolanie callbacka 1");
}

void callback2() {
  Serial.println("Wywolanie callbacka 2");
}

SubTopic motor1("topic/motor/1", callback1);
SubTopic motor2("topic/motor/2", callback2);

MQTTHandler mqtt_handler = MQTTHandler(
  "ASUS_5C", 
  "soda_6735", 
  "192.168.50.135"
);