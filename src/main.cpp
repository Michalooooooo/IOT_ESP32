
#include <Wire.h>
#include <stdint.h>
#include <Arduino.h>

#include "SystemState.hpp"
#include "OLEDHandler.hpp"
#include "SensorsManager.hpp"
#include "MQTTHandler.hpp"
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

// ========== WiFi and MQTT configuration ==========
const char* ssid = "PLAY Niziolek";
const char* password = "AD50714MGZT11";
const char* broker = "192.168.1.184";

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

    sm.Update();
    oh.UpdateScreen(); 
}