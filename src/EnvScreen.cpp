#include "screens/EnvScreen.hpp"

EnvScreen::EnvScreen(Adafruit_SSD1306& display):
    Screen(display),
    m_Display(display) {}

void EnvScreen::Init() {
    m_Display.setTextColor(SSD1306_WHITE);
}

void EnvScreen::Render(const SystemState& sys_state) {
    m_Display.clearDisplay();
    m_Display.setTextColor(SSD1306_WHITE);
    
    float temperature = sys_state.GetTemperature(); 
    float humidity = sys_state.GetHumidity();

    for (int x = 0; x < 128; x += 4) {
        m_Display.drawFastHLine(x, 32, 2, SSD1306_WHITE);
    }

    // =========================================================================
    // GÓRNA SEKCJA: TEMPERATURA 
    // =========================================================================
    
    m_Display.drawCircle(12, 20, 3, SSD1306_WHITE);      // Zbiorniczek
    m_Display.fillRect(11, 10, 3, 8, SSD1306_WHITE);    // Słupek
    
    m_Display.setTextSize(2); 
    m_Display.setCursor(32, 9);
    m_Display.print(temperature, 1); 
    
    m_Display.setTextSize(2);
    m_Display.write(247); 
    m_Display.print("C");


    // =========================================================================
    // DOLNA SEKCJA: WILGOTNOŚĆ 
    // =========================================================================
    
    m_Display.drawCircle(12, 50, 4, SSD1306_WHITE);                    
    m_Display.drawTriangle(8, 49, 16, 49, 12, 42, SSD1306_WHITE);     
    m_Display.fillRect(9, 49, 7, 2, SSD1306_BLACK);                  
    
    m_Display.setTextSize(2);
    m_Display.setCursor(32, 41);
    m_Display.print(humidity, 1); 
    
    m_Display.setTextSize(2);
    m_Display.print("%");

    m_Display.display();
}