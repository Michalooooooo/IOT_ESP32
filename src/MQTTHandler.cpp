#include "MQTTHandler.hpp"

MQTTHandler::MQTTHandler(char *ssid, char *password, char *mqtt_server, const SubTopic** topics_list, uint8_t len):
client(m_ESP32Client),
m_SSID(ssid),
m_Password(password),
m_MQTTServer(mqtt_server),
m_SubTopicsList(topics_list),
m_Len(len) {}

void MQTTHandler::Setup() {
    Serial.begin(9600);
    SetupWiFi();
    client.setServer(m_MQTTServer, 1883);
    // client.setCallback(Callback); // TODO
}

void MQTTHandler::SetupWiFi() {
    WiFi.begin(m_SSID, m_Password);

    Serial.print("Connecting ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(" . ");
    }
    Serial.println("\n WiFi connected!");
}


void MQTTHandler::Reconnect() {

    while(!client.connected()) {
        Serial.print("Connecting to MQTT...");

        if(client.connect("ESP32Client")) {
            Serial.println("ESP32 connected");

            // TODO można zrobić więcej topiców przez użycie petli for ! ! !
            client.subscribe("/motor/1/control");
        } else {
            Serial.print("Failed to connect ESP32! -> ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void MQTTHandler::Callback(char* topic, byte* payload, unsigned int length) {

    String message;

    for (size_t i = 0; i < length; i++) {
        message += (char)(payload[i]);
    }

    HandleTopic(topic);
}

void MQTTHandler::HandleTopic(char* topic) {

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
