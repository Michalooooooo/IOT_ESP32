#pragma once

#include "SubTopic.hpp"
#include "SystemState.hpp"

#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>

class MQTTHandler {
public:
    MQTTHandler(SystemState& sys_state, const char* ssid, const char* password, const char* mqtt_server);

    void Init();
    void MaintainConnection();
    void Publish();
private:
    void SetupWiFi();
    void HandleTopic(char* topic, byte* payload, unsigned int length);
    void SubscribeTopics();

    // Subscribed topics
    enum class SubTopics : int8_t {
        TOPIC_WORKMODE = 0,
        TOPIC_SET_FAN,
        TOPIC_SET_LED,
        TOPIC_SET_PUMP,
        TOPIC_SET_HEAT,
        TOPIC_UNKNOWN = -1
    };

    const char* m_SubTopicsList[5] = {
        "greenhouse/ESP32_1/cmd/workmode",
        "greenhouse/ESP32_1/cmd/fan",
        "greenhouse/ESP32_1/cmd/led",
        "greenhouse/ESP32_1/cmd/pump",
        "greenhouse/ESP32_1/cmd/heat",
    };

    MQTTHandler::SubTopics GetTopicId(char* topic) const;

    // WiFi configuration
    const char* m_SSID;
    const char* m_Password;
    const char* m_MQTTServer;
    
    SystemState& m_SystemState;
    const int m_TopicsCount;
    uint32_t m_LastReconnectAttempt;
    WiFiClient m_ESP32Client;
    PubSubClient client;
};