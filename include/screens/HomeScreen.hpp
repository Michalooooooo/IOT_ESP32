#pragma once
#include "Screen.hpp"

class HomeScreen: public Screen {
public:
    HomeScreen(Adafruit_SSD1306& display);
    void Init() override;
    void Render(const SystemState& sys_state) override;

private:
    Adafruit_SSD1306& m_Display;
};