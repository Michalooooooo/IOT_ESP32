#include "Button.hpp"

Button::Button(const bool button_type, const uint8_t pin, void (*on_click)(), void (*on_release)()):
    m_RawState(false),
    m_LastRawState(false),
    m_NormalState(button_type),
    m_Pin(pin),
    m_LastChangeTime(0),
    m_StableState(false),
    m_OnClick(on_click), 
    m_OnRelease(on_release),
    m_Active(false) {
    
    pinMode(pin, INPUT_PULLDOWN);

}

void Button::Update() {
    m_RawState = digitalRead(m_Pin); 
    m_Active = (m_RawState != m_NormalState); // Przycisk wcisniety - 1, przycisk puszczony - 0;
    if(IsPressed()) {
        m_OnClick();
    }
    if(IsReleased()) {
        m_OnRelease();
    }
}

bool Button::IsPressed() {
    // m_NormalState = 0
    m_RawState = digitalRead(m_Pin);    

    if(m_Active != m_LastRawState) {
        m_LastChangeTime = millis();
    }

    m_LastRawState = m_Active;

    if ((millis() - m_LastChangeTime) >= 50) {
        
        if(m_Active != m_StableState) {
            m_StableState = m_Active;
            if(m_Active) {
                return true;
            }
        }
    }

    return false;
}

bool Button::IsReleased() {
    // m_NormalState = 0   

    if(m_Active != m_LastRawState) {
        m_LastChangeTime = millis();
    }

    m_LastRawState = m_Active;

    if ((millis() - m_LastChangeTime) >= 50) {
        
        if(m_Active != m_StableState) {
            m_StableState = m_Active;
            if(!m_Active) {
                return true;
            }
        }
    }

    return false;
}