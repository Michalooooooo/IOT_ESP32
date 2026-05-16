#pragma once
#include <stdint.h>
#include <Adafruit_SSD1306.h>

#define MARGIN 10

class Screen {
public:
    Screen(Adafruit_SSD1306& display);
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
private:
    static uint8_t s_ID;
    uint8_t m_ScreenID;
protected:
    Adafruit_SSD1306& m_Display;
};