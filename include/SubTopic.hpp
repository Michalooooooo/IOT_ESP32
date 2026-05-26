#pragma once
#include <stdint.h>
#include <Arduino.h>
#include <functional>

class SubTopic {
public:
    SubTopic(char* name, std::function<void()> cb);
    void CallFunction() const;

    static uint8_t s_TopicID;
    char* m_TopicName;
    
    uint8_t m_ID;

private:
    std::function<void()> m_Function;
};