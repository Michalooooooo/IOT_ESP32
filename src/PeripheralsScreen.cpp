#include "screens/PeripheralsScreen.hpp"

PeripheralsScreen::PeripheralsScreen(Adafruit_SSD1306& display):
    Screen(display),
    m_Display(display) {}

void PeripheralsScreen::Init() {
    m_Display.setTextColor(SSD1306_WHITE);
}

void PeripheralsScreen::Render(const SystemState& sys_state) {
    m_Display.clearDisplay();
    m_Display.setTextSize(1);
    m_Display.setTextColor(SSD1306_WHITE);

    float fan_power   = static_cast<float>(sys_state.GetFanPower()) / 255.f;
    float led_power   = static_cast<float>(sys_state.GetLedPower()) / 255.f;
    float pump_power  = static_cast<float>(sys_state.GetPumpPower()) / 255.f;
    float heat_power  = static_cast<float>(sys_state.GetHeatPower()) / 255.f;

    m_Display.drawFastVLine(64, 0, 64, SSD1306_WHITE);  
    m_Display.drawFastHLine(0, 32, 128, SSD1306_WHITE); 

    const int bar_w = 54; 
    const int bar_h = 7;  
    const int max_fill_w = bar_w - 4; 

    // =========================================================================
    // KAFELEK 1: WENTYLATOR (Lewy górny)
    // =========================================================================
    m_Display.setCursor(4, 3);
    m_Display.print("FAN:"); 
    m_Display.print((int)(fan_power * 100.0f)); 
    m_Display.print("%");
    
    m_Display.drawRect(4, 16, bar_w, bar_h, SSD1306_WHITE);
    int fan_fill = fan_power * max_fill_w;
    if (fan_fill > 0) {
        m_Display.fillRect(6, 18, fan_fill, bar_h - 4, SSD1306_WHITE);
    }

    // =========================================================================
    // KAFELEK 2: OŚWIETLENIE LED (Prawy górny)
    // =========================================================================
    m_Display.setCursor(69, 3);
    m_Display.print("LED:"); 
    m_Display.print((int)(led_power * 100.0f));
    m_Display.print("%");
    
    m_Display.drawRect(69, 16, bar_w, bar_h, SSD1306_WHITE);
    int led_fill = led_power * max_fill_w;
    if (led_fill > 0) {
        m_Display.fillRect(71, 18, led_fill, bar_h - 4, SSD1306_WHITE);
    }

    // =========================================================================
    // KAFELEK 3: POMPA WODY (Lewy dolny)
    // =========================================================================
    m_Display.setCursor(4, 35);
    m_Display.print("PUMP:"); 
    m_Display.print((int)(pump_power * 100.0f));
    m_Display.print("%");
    
    m_Display.drawRect(4, 48, bar_w, bar_h, SSD1306_WHITE);
    int pump_fill = pump_power * max_fill_w;
    if (pump_fill > 0) {
        m_Display.fillRect(6, 50, pump_fill, bar_h - 4, SSD1306_WHITE);
    }

    // =========================================================================
    // KAFELEK 4: GRZAŁKA (Prawy dolny)
    // =========================================================================
    m_Display.setCursor(69, 35);
    m_Display.print("HTR:"); 
    m_Display.print((int)(heat_power * 100.0f));
    m_Display.print("%");
    
    m_Display.drawRect(69, 48, bar_w, bar_h, SSD1306_WHITE);
    int heat_fill = heat_power * max_fill_w;
    if (heat_fill > 0) {
        m_Display.fillRect(71, 50, heat_fill, bar_h - 4, SSD1306_WHITE);
    }

    m_Display.display();
}