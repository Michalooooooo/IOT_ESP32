#include "Button.hpp"

Button::Button(
        const bool button_type, 
        const uint8_t pin, 
        std::function<void()> on_click, 
        std::function<void()> on_release
    ):
    m_RawState(false),
    m_LastRawState(button_type),
    m_NormalState(button_type),
    m_Pin(pin),
    m_LastChangeTime(0),
    m_StableState(false),
    m_LastStableState(button_type),
    m_OnClick(on_click), 
    m_OnRelease(on_release),
    m_Active(false) {
    
    if(m_NormalState) {
        pinMode(pin, INPUT_PULLUP);
    } else {
        pinMode(pin, INPUT_PULLDOWN);
    }

}

void Button::Update() {
    m_RawState = digitalRead(m_Pin);
    m_Active = (m_RawState != m_NormalState); // Button pressed - 1, button released - 0;

    if(m_RawState != m_LastRawState) { 
        m_LastChangeTime = millis();
    }

    if(millis() - m_LastChangeTime >= 50) { 
        m_StableState = m_Active;

        if(m_StableState != m_LastStableState) {
            if(m_StableState == m_NormalState && m_OnRelease) { 
                m_OnRelease();
            } else if (m_StableState != m_NormalState && m_OnClick){
                m_OnClick();
            }
            m_LastStableState = m_StableState;
        }
         
    }
    m_LastRawState = m_RawState;
}
