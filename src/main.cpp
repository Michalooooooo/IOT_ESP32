
// #include "Button.hpp"
// #include "OLEDHandler.hpp"
// #include "SystemState.hpp"
// #include "SensorManager.hpp"
// #include <Arduino.h>
// #include <stdint.h>

// SystemState sys_state;
// // OLEDHandler oh(21, 22, sys_state);
// SensorManager sm(sys_state);

// void setup() {
//   //Zrobić wire begin raz tutaj w setup
//   Serial.begin(115200);
//   Serial.println("START");
//   // oh.Init();
//   sm.Init();
// }

// void loop() {
//   // oh.UpdateScreen();
//   sm.Update();
//   Serial.printf("Illuminance: %u \n", sys_state.GetIlluminance());
//   Serial.printf("Temperature: %f \n", sys_state.GetTemperature());
//   Serial.printf("Humidity:    %f \n", sys_state.GetHumidity());

//   delay(2000);
// }

#include <Wire.h>
#include <stdint.h>
#include <Arduino.h>

#include "SystemState.hpp"
#include "OLEDHandler.hpp"
#include "SensorsManager.hpp"
#include "mqtt/MQTTHandler.hpp"
#include "PeripheralsManager.hpp"

// ========== Timing (ms) ==========
uint32_t now = 0;
// MQTT Publish
const uint32_t pub_treshold = 3000;
uint32_t last_pub = 0;
// Fuzzy controller update
const uint32_t fc_step_treshold = 1000;
uint32_t last_fc_step = 0;

// ========== Hardware configuration ==========
const uint8_t SDA_PIN = 21;
const uint8_t SCL_PIN = 22;

SystemState sys_state;
OLEDHandler oh(sys_state);
SensorsManager sm(sys_state);
PeripheralsManager pm(sys_state);

// ========== MQTT configuration ==========
const char* ssid = "ASUS_5C";
const char* password = "soda_6735";
const char* broker = "192.168.50.135";

MQTTHandler mqtt_h(sys_state, ssid, password, broker);

void setup() {
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200);
    Serial.println("START");
    delay(2000);

    oh.Init();
    sm.Init();
    mqtt_h.Init();
    pm.Init();

}

void loop() {
    mqtt_h.MaintainConnection();

    now = millis();
    if(now - last_pub > pub_treshold) {
        last_pub = now;
        mqtt_h.Publish();
    }
    
    if(now - last_fc_step > fc_step_treshold) {
        last_fc_step = now;
        pm.Update();
    }

    oh.UpdateScreen();
}