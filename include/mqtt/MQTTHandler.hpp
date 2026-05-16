#pragma once

#include "SubTopic.hpp"

#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>

class MQTTHandler {
public:
    MQTTHandler(char* ssid, char* password, char* mqtt_server);

    void Init();
    void Reconnect();
    void Loop();
    // Mozna zrobić funkcje do dodawania SubTopics zamiast dodawania ich w konstruktorze.
    void Publish(char* topic, char* message);
    void AddSubTopic(SubTopic* sub_topic);
private:
    void SetupWiFi();
    
    void HandleTopic(char* topic, byte* payload, unsigned int length);
    void SubscribeTopics();

    char* m_SSID;
    char* m_Password;
    char* m_MQTTServer;
    SubTopic* m_SubTopicsList[10];
    uint8_t m_Itr;


    WiFiClient m_ESP32Client;
    PubSubClient client;
};