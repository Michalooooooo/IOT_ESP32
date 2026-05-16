#pragma once
#include "Screen.hpp"

class HomeScreen: public Screen {
public:
    HomeScreen(Adafruit_SSD1306& display);
    void Init() override;
    void Update() override;
    void Render() override;

    void SetCurrentTime(uint8_t hour, uint8_t min, uint8_t sec);
    void SetWiFiStatus(bool status);

private:
    Adafruit_SSD1306 m_Display;
    uint8_t m_CurrentHour; 
    uint8_t m_CurrentMinute; 
    uint8_t m_CurrentSecond;
    bool m_WiFiStatus;

};