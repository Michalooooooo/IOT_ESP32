#include "OLEDHandler.hpp"

OLEDHandler::OLEDHandler(const SystemState& sys_state):
    m_Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    m_SystemState(sys_state),
    m_HomeScreen(m_Display),
    m_EnvScreen(m_Display),
    m_LightScreen(m_Display),
    m_PeripheralsScreen(m_Display),
    m_ActiveScreen(0),
    m_NumScreens(4),
    m_NextButton(BUTTON_NO, 33, [this]() { SetNextScreen(); }, nullptr),
    m_PreviousButton(BUTTON_NO, 32, [this]() { SetPreviousScreen(); }, nullptr) {}

void OLEDHandler::Init() {

    if(!m_Display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while(true);
    }

    m_Display.clearDisplay();

    m_HomeScreen.Init();
    m_EnvScreen.Init();
    m_LightScreen.Init();
    Serial.println("Zainicjalizowano OLEDHandler!");
}

void OLEDHandler::UpdateScreen() {
    m_NextButton.Update();
    m_PreviousButton.Update();
    
    switch (m_ActiveScreen) {
        case 0:
            m_HomeScreen.Render(m_SystemState);
            break;
        
        case 1:
            m_EnvScreen.Render(m_SystemState);
            break;

        case 2:
            m_LightScreen.Render(m_SystemState);
            break;

        case 3:
            m_PeripheralsScreen.Render(m_SystemState);
            break;

        default:
            Serial.println("OLEDHandler::UpdateScreen(): Active screen out of range!");
            break;
    }
}

void OLEDHandler::SetNextScreen() {
    if(m_ActiveScreen == m_NumScreens - 1) {
        m_ActiveScreen = 0;
    } else {
        m_ActiveScreen++;
    }
    
    Serial.printf("Displayed screen: %u \n", m_ActiveScreen);
}

void OLEDHandler::SetPreviousScreen() {
    if(m_ActiveScreen == 0) {
        m_ActiveScreen = m_NumScreens - 1;
    } else {
        m_ActiveScreen--;
    }
    
    Serial.printf("Displayed screen: %u \n", m_ActiveScreen);
}
