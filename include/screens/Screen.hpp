#pragma once
#include <stdint.h>
#include <Adafruit_SSD1306.h>
#include "SystemState.hpp"

class Screen {
public:
    Screen(Adafruit_SSD1306& display);
    virtual void Init() = 0;
    virtual void Render(const SystemState& sys_state) = 0;
private:
    static uint8_t s_ID;
    uint8_t m_ScreenID;
protected:
    Adafruit_SSD1306& m_Display;
};