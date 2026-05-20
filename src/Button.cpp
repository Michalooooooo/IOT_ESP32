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
    m_Active = (m_RawState != m_NormalState); // Przycisk wcisniety - 1, przycisk puszczony - 0;

    if(m_RawState != m_LastRawState) { // Zacznij odliczanie w momencie gdy wykryjesz zmiane stanu
        m_LastChangeTime = millis();
    }

    // Jesli stan jest stablilny wiecej niz 50ms i ostatni stabilny stan jest inny niż surowy teraz
    if(millis() - m_LastChangeTime >= 50) { 
        m_StableState = m_Active;

        if(m_StableState != m_LastStableState) {
            if(m_StableState == m_NormalState) { 
                m_OnRelease();
            } else {
                m_OnClick();
            }
            m_LastStableState = m_StableState;
        }
         
    }
    m_LastRawState = m_RawState;
}
