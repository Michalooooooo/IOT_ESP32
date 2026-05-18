#pragma once
#include <stdint.h>
#include <Arduino.h>

#define BUTTON_NO 0
#define BUTTON_NC 1

class Button {
public:
    Button(const bool button_type, const uint8_t pin, void (*on_click)(), void (*on_release)());

    void Update();

private:
    
    bool IsPressed();
    bool IsReleased();
    bool m_RawState;
    bool m_LastRawState;
    bool m_StableState;
    bool m_Active;
    const bool m_NormalState;
    const uint8_t m_Pin;
    uint32_t m_LastChangeTime;

    void (*m_OnClick)();
    void (*m_OnRelease)();

};