
// #include "Button.hpp"
// #include "OLEDHandler.hpp"
// #include "SystemState.hpp"
// #include "SensorManager.hpp"
// #include <Arduino.h>
// #include <stdint.h>

// SystemState sys_state;
// // OLEDHandler oh(21, 22, sys_state);
// SensorManager sm(sys_state);

// void setup() {
//   //Zrobić wire begin raz tutaj w setup
//   Serial.begin(115200);
//   Serial.println("START");
//   // oh.Init();
//   sm.Init();
// }

// void loop() {
//   // oh.UpdateScreen();
//   sm.Update();
//   Serial.printf("Illuminance: %u \n", sys_state.GetIlluminance());
//   Serial.printf("Temperature: %f \n", sys_state.GetTemperature());
//   Serial.printf("Humidity:    %f \n", sys_state.GetHumidity());

//   delay(2000);
// }
#include <Arduino.h>

const int led_pin = 25;

// Tablica 32 kroków dopasowanych do ludzkiego oka (Krzywa CIE 1931)
// Chociaż indeks rośnie równomiernie, wartości PWM rosną wykładniczo!
const uint8_t cie_curve[32] = {
    0,   1,   2,   3,   4,   5,   7,   9,
    12,  15,  18,  22,  27,  32,  38,  44,
    51,  58,  67,  76,  86,  96,  108, 120,
    134, 148, 164, 180, 197, 216, 235, 255
};

void setup() {
    Serial.begin(115200);
    pinMode(led_pin, OUTPUT);
}

void loop() {
    // Płynne rozjaśnianie diody "po ludzku"
    for (int i = 0; i < 32; i++) {
        uint8_t hardware_pwm = cie_curve[i];
        
        Serial.printf("Ludzki poziom: %d/31 -> Sprzętowy PWM: %d\n", i, hardware_pwm);
        analogWrite(led_pin, hardware_pwm);
        
        delay(100); // Małe opóźnienie, żeby zobaczyć efekt
    }
    
    delay(1000);
}