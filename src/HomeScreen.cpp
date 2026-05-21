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
    m_Display.setCursor(6, 6);

    if (sys_state.GetWiFiStatus()) {
        m_Display.print("WiFi: OK"); 
    } else {
        m_Display.print("WiFi: LOST CONN");
    }

    // =========================================================================
    // ZEGAR 
    // =========================================================================
    m_Display.setTextSize(2);
    m_Display.setCursor(16, 30);

    SysTime current_time = sys_state.GetTime();

    m_Display.printf("%02d:%02d:%02d",
               current_time.hour,
               current_time.minute,
               current_time.second);

    m_Display.display();
}