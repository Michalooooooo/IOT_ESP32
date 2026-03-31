#pragma once

#include "SubTopic.hpp"

#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>

class MQTTHandler {
public:
    MQTTHandler(char* ssid, char* password, char* mqtt_server, const SubTopic** topics_list, uint8_t len);

    void Setup();
private:
    void SetupWiFi();
    void Reconnect();
    void Callback(char* topic, byte* payload, unsigned int length);
    void HandleTopic(char* topic);
    void SubscribeTopics();

    char* m_SSID;
    char* m_Password;
    char* m_MQTTServer;
    const SubTopic** m_SubTopicsList;
    uint8_t m_Len;

    WiFiClient m_ESP32Client;
    PubSubClient client;
};