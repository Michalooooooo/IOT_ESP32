#include "screens/HomeScreen.hpp"

HomeScreen::HomeScreen(Adafruit_SSD1306& display):
    Screen(display),
    m_Display(display) {}

void HomeScreen::Init() {
    m_Display.setTextColor(SSD1306_WHITE);
}

void HomeScreen::Render(const SystemState& sys_state) {
    m_Display.clearDisplay();
    
    m_Display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

    // =========================================================================
    // STATUS WI-FI 
    // =========================================================================
    m_Display.setTextSize(1);
    m_Display.setCursor(5, 5);

    if (sys_state.GetWiFiStatus()) {
        m_Display.print("WiFi: OK"); 
    } else {
        m_Display.print("WiFi: LOST CONN");
    }

    // =========================================================================
    // Tryb pracy 
    // =========================================================================
    m_Display.setCursor(5, 25);
    m_Display.print("System workmode: ");
    m_Display.setCursor(5, 40);
    m_Display.setTextSize(2);

    SystemState::WorkMode wm = sys_state.GetWorkMode();

    switch(wm) {
        case SystemState::WorkMode::AUTO:
            m_Display.print("AUTO");
            break;
        case SystemState::WorkMode::MANUAL:
            m_Display.print("MANUAL");
            break;
        default:
            m_Display.print("ERROR!!!");
    }

    m_Display.display();
}