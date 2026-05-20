#include "mqtt/MQTTHandler.hpp"

MQTTHandler::MQTTHandler(char* ssid, char* password, char* mqtt_server):
client(m_ESP32Client),
m_SSID(ssid),
m_Password(password),
m_MQTTServer(mqtt_server),
m_Itr(0)
{}

void MQTTHandler::Init() {
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

        if(client.connect("ESP32Client")) {
            Serial.println("MQTTHandler::Reconnect | ESP32 connected");
            SubscribeTopics();
        } else {
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

void MQTTHandler::AddSubTopic(SubTopic *sub_topic) {
    // Sprawdzenie czy długosc po dodaniu nie przekroczy maksymalnej długości (10)
    if (m_Itr > 9) {
        Serial.println("Nie mozna dodac topika! Zbyt mala tablica topikow!");
        return;
    }

    // Sprawdzenie czy już nie ma takiego topika
    for(size_t i = 0; i < m_Itr; i++) {
        SubTopic* topic = m_SubTopicsList[i];
        if(topic->m_ID == sub_topic->m_ID) {
            Serial.println("Nie mozna dodac topika! Taki topik juz istnieje!");
            return;
        }
    }

    // Dodanie topika
    m_SubTopicsList[m_Itr] = sub_topic;
    m_Itr++;
}

void MQTTHandler::HandleTopic(char* topic, byte* payload, unsigned int length) {

    String message;

    for (size_t i = 0; i < length; i++) {
        message += (char)(payload[i]);
    }
    // Serial.print("MQTTHandler::HandleTopic | ");
    Serial.println(message);

    for(size_t i = 0; i < m_Itr; i++) {
        const SubTopic *t = m_SubTopicsList[i];
        if(strcmp(topic, t->m_TopicName) == 0) {
            t->CallFunction();
        }
    }
}

void MQTTHandler::SubscribeTopics() {
    for(size_t i = 0; i < m_Itr; i++) {
        const SubTopic *t = m_SubTopicsList[i];
        client.subscribe(t->m_TopicName);
    }
}
