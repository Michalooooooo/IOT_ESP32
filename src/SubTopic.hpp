#pragma once
#include <stdint.h>
#include <Arduino.h>

class SubTopic {
public:
    SubTopic(char* name, void (*cb)());
    inline void CallFunction() const;

    static uint8_t s_TopicID;
    char* m_TopicName;

private:
    uint8_t m_ID;
    void (*m_Function)();
};