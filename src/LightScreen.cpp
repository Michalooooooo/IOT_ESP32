#include "screens/LightScreen.hpp"

LightScreen::LightScreen(Adafruit_SSD1306& display):
    Screen(display),
    m_Display(display) {}

void LightScreen::Init() {
    m_Display.setTextColor(SSD1306_WHITE);
}

void LightScreen::Render(const SystemState& sys_state) {
    m_Display.clearDisplay();
    m_Display.setTextColor(SSD1306_WHITE);
    
    uint16_t lux = sys_state.GetIlluminance(); 

    // =========================================================================
    // LEWA STRONA: IKONA SŁOŃCA 
    // =========================================================================
    
    m_Display.drawCircle(16, 32, 6, SSD1306_WHITE);
    
    m_Display.drawFastVLine(16, 18, 5, SSD1306_WHITE);  // Góra
    m_Display.drawFastVLine(16, 41, 5, SSD1306_WHITE);  // Dół
    m_Display.drawFastHLine(2, 32, 5, SSD1306_WHITE);   // Lewo
    m_Display.drawFastHLine(25, 32, 5, SSD1306_WHITE);  // Prawo
    
    m_Display.drawLine(7, 23, 10, 26, SSD1306_WHITE);   // Lewa góra
    m_Display.drawLine(22, 26, 25, 23, SSD1306_WHITE);  // Prawa góra
    m_Display.drawLine(7, 41, 10, 38, SSD1306_WHITE);   // Lewy dół
    m_Display.drawLine(22, 38, 25, 41, SSD1306_WHITE);  // Prawy dół


    // =========================================================================
    // PRAWA STRONA: WARTOŚĆ I PASEK 
    // =========================================================================
    
    m_Display.setTextSize(1);
    m_Display.setCursor(6, 6);
    m_Display.print("NATEZENIE SWIATLA"); 

    m_Display.setTextSize(2);
    m_Display.setCursor(40, 18);
    m_Display.print(lux); 
    
    m_Display.setTextSize(2);
    m_Display.print("lx");


    // =========================================================================
    // DOLNA CZĘŚĆ: PASEK POSTĘPU 
    // =========================================================================
    
    int bar_x = 40;
    int bar_y = 42;
    int bar_width = 80;
    int bar_height = 8;

    m_Display.drawRect(bar_x, bar_y, bar_width, bar_height, SSD1306_WHITE);
    
    float clamped_lux = lux;
    if (clamped_lux > MAX_LUX_REFERENCE) {
        clamped_lux = MAX_LUX_REFERENCE;
    }
    if (clamped_lux < 0.0f) {
        clamped_lux = 0.0f;
    }

    int fill_width = (clamped_lux / MAX_LUX_REFERENCE) * (bar_width - 4);
    
    if (fill_width > 0) {
        m_Display.fillRect(bar_x + 2, bar_y + 2, fill_width, bar_height - 4, SSD1306_WHITE);
    }

    m_Display.display();
}