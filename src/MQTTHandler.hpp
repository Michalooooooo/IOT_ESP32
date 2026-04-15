#pragma once

#include "SubTopic.hpp"

#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>

class MQTTHandler {
public:
    MQTTHandler(char* ssid, char* password, char* mqtt_server, SubTopic* topics_list[], uint8_t len);

    void Setup();
    void Reconnect();
    void Loop();
private:
    void SetupWiFi();
    
    void HandleTopic(char* topic, byte* payload, unsigned int length);
    void SubscribeTopics();

    char* m_SSID;
    char* m_Password;
    char* m_MQTTServer;
    uint8_t m_Len;
    SubTopic** m_SubTopicsList;


    WiFiClient m_ESP32Client;
    PubSubClient client;
};