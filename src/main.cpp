#include "DS18B20Handler.hpp"
#include "ADXL345Handler.hpp"
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

SubTopic *topics[] = {&motor1, &motor2};

DS18B20Handler tmp_sensor = DS18B20Handler(4);
ADXL345Handler acc = ADXL345Handler(1);
MQTTHandler mqtt_handler = MQTTHandler(
  "ASUS_5C", 
  "soda_6735", 
  "192.168.50.135",
  topics,
  2
);

void setup() {

  acc.Init();
  tmp_sensor.Init();

  Serial.begin(460800);
  mqtt_handler.Setup();

}

void loop() {
  
  delay(1000);

  // Serial.println("Reconnect");
  mqtt_handler.Reconnect();
  mqtt_handler.Loop();
  
  //Serial.println(WiFi.status());
  // // acc.GetAccelerations();
  // // acc.DisplayCurrentAccelerations();
  // delay(1000);
  // // tmp_sensor.GetTemperature();
  // // tmp_sensor.DisplayCurrentTemperature();
  // delay(1000);

}

