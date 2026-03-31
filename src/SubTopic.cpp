#include "SubTopic.hpp"

uint8_t SubTopic::s_TopicID = 0;

SubTopic::SubTopic(char *name, void (*cb)()):
m_TopicName(name),
m_Function(cb) {
    if(sizeof(s_TopicID + 1) > sizeof(uint8_t)) {
        Serial.println("To many topics. Cannot create more!");
    } else {
        m_ID = s_TopicID;
        s_TopicID++;
    }
}

inline void SubTopic::CallFunction() const {
    m_Function();
}
