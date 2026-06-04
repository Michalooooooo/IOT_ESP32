#include "mqtt/MQTTHandler.hpp"

MQTTHandler::MQTTHandler(SystemState& sys_state, const char* ssid, const char* password, const char* mqtt_server):
    m_SystemState(sys_state),
    client(m_ESP32Client),
    m_SSID(ssid),
    m_Password(password),
    m_MQTTServer(mqtt_server),
    m_TopicsCount(sizeof(m_SubTopicsList) / sizeof(m_SubTopicsList[0])),
    m_LastReconnectAttempt(millis())
    {}

void MQTTHandler::Init() {
    SetupWiFi();
    client.setServer(m_MQTTServer, 1883);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->HandleTopic(topic, payload, length);
    });   
    Serial.println("Zainicjalizowano MQTTHandler!");
}

void MQTTHandler::SetupWiFi() {
    WiFi.begin(m_SSID, m_Password);

    Serial.print("Connecting . . .");
    while (WiFi.status() != WL_CONNECTED) {
        m_SystemState.SetWiFiStatus(false);
        delay(500);
        Serial.println("Trying to connect... ");
    }
    Serial.println("\n WiFi connected!");
    m_SystemState.SetWiFiStatus(true);
}

void MQTTHandler::MaintainConnection() {

    if(client.connected()) {
        client.loop();
        return;
    }

    uint32_t now = millis();
    if(now - m_LastReconnectAttempt > 5000) {
        m_LastReconnectAttempt = now;
        Serial.println("No MQTT connection. Trying to connect . . .");

        if(client.connect("greenhouse_ESP32")) {
            Serial.println("Connected with MQTT!");
            SubscribeTopics();
        } else {
            Serial.print("Connection failed: ");
            Serial.println(client.state());
        }
    }    
}

void MQTTHandler::Publish() {

    const char* workmode;
    if(m_SystemState.GetWorkMode() == SystemState::WorkMode::AUTO) {
        workmode = "AUTO";
    } else if(m_SystemState.GetWorkMode() == SystemState::WorkMode::MANUAL) {
        workmode = "MANUAL";
    } else { 
        workmode = "NONE"; 
    }

    client.publish("greenhouse/ESP32_1/status/workmode", workmode);
    client.publish("greenhouse/ESP32_1/status/fan", String((int)m_SystemState.GetFanPower()).c_str());
    client.publish("greenhouse/ESP32_1/status/led", String((int)m_SystemState.GetLedPower()).c_str());
    client.publish("greenhouse/ESP32_1/status/pump", String((int)m_SystemState.GetPumpPower()).c_str());
    client.publish("greenhouse/ESP32_1/status/heat", String((int)m_SystemState.GetHeatPower()).c_str());
    client.publish("greenhouse/ESP32_1/status/temperature", String(m_SystemState.GetTemperature(), 1).c_str());
    client.publish("greenhouse/ESP32_1/status/humidity", String(m_SystemState.GetHumidity(), 1).c_str());
    client.publish("greenhouse/ESP32_1/status/light", String(m_SystemState.GetIlluminance()).c_str());
}

void MQTTHandler::HandleTopic(char* topic, byte* payload, unsigned int length) {

    payload[length] = '\0';
    char* msg = (char*)payload;

    SubTopics topic_id = GetTopicId(topic);
    
    switch (topic_id) {
        case SubTopics::TOPIC_WORKMODE:
            if(strcmp(msg, "AUTO") == 0) {
                m_SystemState.SetWorkMode(SystemState::WorkMode::AUTO);
            } else if(strcmp(msg, "MANUAL") == 0) { 
                m_SystemState.SetWorkMode(SystemState::WorkMode::MANUAL);
            } else {
                Serial.println("Unknown command, omitting.");
            }
            break;

        case SubTopics::TOPIC_SET_FAN: {
            if(m_SystemState.GetWorkMode() == SystemState::WorkMode::MANUAL) {
                uint8_t pwm = static_cast<uint8_t>(atoi(msg));
                m_SystemState.SetFanPower(pwm);
            }
            break;
        }

        case SubTopics::TOPIC_SET_LED: {
            if(m_SystemState.GetWorkMode() == SystemState::WorkMode::MANUAL) {
                uint8_t pwm = static_cast<uint8_t>(atoi(msg));
                m_SystemState.SetLedPower(pwm);
           }
            break;
        }

        case SubTopics::TOPIC_SET_PUMP: {
            if(m_SystemState.GetWorkMode() == SystemState::WorkMode::MANUAL) {
                uint8_t pwm = static_cast<uint8_t>(atoi(msg));
                m_SystemState.SetPumpPower(pwm);
            }
            break;
        }

        case SubTopics::TOPIC_SET_HEAT: {
            if(m_SystemState.GetWorkMode() == SystemState::WorkMode::MANUAL) {
                uint8_t pwm = static_cast<uint8_t>(atoi(msg));
                m_SystemState.SetHeatPower(pwm);
            }
            break;
        }  

        default:
            break;
    }
}

void MQTTHandler::SubscribeTopics() {
    for(size_t i = 0; i < m_TopicsCount; i++) {
        const char *t = m_SubTopicsList[i];
        Serial.printf("Subscribes topic: %s \n", t);
        client.subscribe(t);
    }
}

MQTTHandler::SubTopics MQTTHandler::GetTopicId(char* topic) const {
    for (size_t i = 0; i < m_TopicsCount; i++) {
        if (strcmp(topic, m_SubTopicsList[i]) == 0) {
            return static_cast<SubTopics>(i); 
        }
    }
    return SubTopics::TOPIC_UNKNOWN; 
}
