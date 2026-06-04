#pragma once

#include <stdint.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>
#include "SystemState.hpp"
#include "screens/Screen.hpp"
#include "screens/HomeScreen.hpp"
#include "screens/EnvScreen.hpp"
#include "screens/LightScreen.hpp"
#include "screens/PeripheralsScreen.hpp"
#include "Button.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class OLEDHandler {
public:
    OLEDHandler(const SystemState& sys_state);

    void Init();
    void UpdateScreen();  
    
    Adafruit_SSD1306 m_Display;

private:
    void SetNextScreen();
    void SetPreviousScreen();
    const SystemState& m_SystemState;
    
    //Screens
    HomeScreen m_HomeScreen;
    EnvScreen m_EnvScreen;
    LightScreen m_LightScreen;
    PeripheralsScreen m_PeripheralsScreen;

    uint8_t m_ActiveScreen;
    const uint8_t m_NumScreens;
    Button m_NextButton;
    Button m_PreviousButton;
};