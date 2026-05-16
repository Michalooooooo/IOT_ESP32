#include "screens/HomeScreen.hpp"

HomeScreen::HomeScreen(Adafruit_SSD1306& display):
    Screen(display),
    m_Display(display) {}

void HomeScreen::Init() {
    m_Display.setTextColor(SSD1306_WHITE);
    m_Display.setTextSize(2);
}

void HomeScreen::Update() {
}

void HomeScreen::Render() {
    
    m_Display.setCursor(MARGIN, MARGIN);

    if(m_WiFiStatus) {
        m_Display.println("WiFi status: CONNECTED");
    }else {
        m_Display.println("WiFi status: DISCONNECTED");
    }

    m_Display.printf("%02d:%02d:%02d",
               m_CurrentHour,
               m_CurrentMinute,
               m_CurrentSecond);
}

void HomeScreen::SetCurrentTime(uint8_t hour, uint8_t minute, uint8_t second) {
    m_CurrentHour = hour;
    m_CurrentMinute = minute;
    m_CurrentSecond = second;
}

void HomeScreen::SetWiFiStatus(bool status) {
    m_WiFiStatus = status;
}
