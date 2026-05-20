#pragma once
#include <stdint.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "SystemState.hpp"
#include "screens/Screen.hpp"
#include "screens/HomeScreen.hpp"
#include "Button.hpp"
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class OLEDHandler {
public:
    OLEDHandler(uint8_t& SDA, uint8_t& SCL, const SystemState& sys_state);

    void Init();
    void UpdateScreen();  
    
    Adafruit_SSD1306 m_Display;

private:
    void SetNextScreen();
    void SetPreviousScreen();
    uint8_t m_SDA, m_SCL;
    const SystemState& m_SystemState;
    HomeScreen m_HomeScreen;
    uint8_t m_ActiveScreen;
    const uint8_t m_NumScreens;
    Button m_NextButton;
    Button m_PreviousButton;
};