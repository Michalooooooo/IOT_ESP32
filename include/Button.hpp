#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <functional>

#define BUTTON_NO false
#define BUTTON_NC true

class Button {
public:
    Button(
        const bool button_type, 
        const uint8_t pin, 
        std::function<void()> on_click, 
        std::function<void()> on_release
    );

    void Update();

private:
    bool m_RawState;
    bool m_LastRawState;
    bool m_StableState;
    bool m_LastStableState;
    bool m_Active;
    const bool m_NormalState;
    const uint8_t m_Pin;
    uint32_t m_LastChangeTime;

    std::function<void()> m_OnClick; 
    std::function<void()> m_OnRelease;

};