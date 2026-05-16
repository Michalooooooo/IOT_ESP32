#pragma once
#include <stdint.h>
#include <Arduino.h>

class SubTopic {
public:
    SubTopic(char* name, void (*cb)());
    void CallFunction() const;

    static uint8_t s_TopicID;
    char* m_TopicName;
    
    uint8_t m_ID;

private:
    void (*m_Function)();
};