#pragma once
#include "Screen.hpp"

class PeripheralsScreen: public Screen {
public:
    PeripheralsScreen(Adafruit_SSD1306& display);
    void Init() override;
    void Render(const SystemState& sys_state) override;

private:
    Adafruit_SSD1306& m_Display;
    const float MAX_LUX_REFERENCE = 1000.0f; // Powyżej tej wartości pasek będzie pełny

};