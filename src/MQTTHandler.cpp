#include "MQTTHandler.hpp"

MQTTHandler::MQTTHandler(char* ssid, char* password, char* mqtt_server, SubTopic* topics_list[], uint8_t len):
client(m_ESP32Client),
m_SSID(ssid),
m_Password(password),
m_MQTTServer(mqtt_server),
m_SubTopicsList(topics_list),
m_Len(len) {}

void MQTTHandler::Setup() {
    SetupWiFi();
    client.setServer(m_MQTTServer, 1883);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->HandleTopic(topic, payload, length);
    }); 
}

void MQTTHandler::SetupWiFi() {
    WiFi.begin(m_SSID, m_Password);

    Serial.print("Connecting ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Trying to connect... ");
    }
    Serial.println("\n WiFi connected!");
}


void MQTTHandler::Reconnect() {

    while(!client.connected()) {
        // Serial.print("MQTTHandler::Reconnect | Brak polaczenia, ponowne łaczenie...");

        if(client.connect("ESP32Client")) {
            Serial.println("MQTTHandler::Reconnect | ESP32 connected");

            SubscribeTopics();
        } else {
            // Serial.print("MQTTHandler::Reconnect | Nie mozna sie polaczyc z ESP32: ");
            // Serial.print(client.state());
            delay(2000);
        }
    }
}

void MQTTHandler::Loop() {
    client.loop();
}

void MQTTHandler::Publish(char* topic, char* message) {
    client.publish(topic, message);
}

void MQTTHandler::HandleTopic(char* topic, byte* payload, unsigned int length) {

    String message;

    for (size_t i = 0; i < length; i++) {
        message += (char)(payload[i]);
    }
    // Serial.print("MQTTHandler::HandleTopic | ");
    Serial.println(message);

    for(size_t i = 0; i < m_Len; i++) {
        const SubTopic *t = m_SubTopicsList[i];
        if(strcmp(topic, t->m_TopicName) == 0) {
            t->CallFunction();
        }
    }
}

void MQTTHandler::SubscribeTopics() {
    for(size_t i = 0; i < m_Len; i++) {
        const SubTopic *t = m_SubTopicsList[i];
        client.subscribe(t->m_TopicName);
    }
}
