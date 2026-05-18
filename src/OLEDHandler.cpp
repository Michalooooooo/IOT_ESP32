#include "OLEDHandler.hpp"

OLEDHandler::OLEDHandler(uint8_t& SDA, uint8_t& SCL, const SystemState& sys_state):
    m_Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    m_SDA(SDA), m_SCL(SCL),
    m_SystemState(sys_state),
    m_HomeScreen(m_Display),
    m_ActiveScreen(0),
    m_NumScreens(5) {}

void OLEDHandler::Init() {
    Wire.begin(m_SDA, m_SCL);

    if(!m_Display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while(true);
    }

    m_Display.clearDisplay();
}

void OLEDHandler::UpdateScreen() {
    switch (m_ActiveScreen) {
        case 0:
            m_HomeScreen.Update();
            m_HomeScreen.Render();
            break;
        
        case 1:
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
}

void OLEDHandler::SetPreviousScreen() {
    if(m_ActiveScreen == 0) {
        m_ActiveScreen = m_NumScreens - 1;
    } else {
        m_ActiveScreen--;
    }
}
