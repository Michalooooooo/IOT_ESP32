#pragma once
#include <stdint.h>
#include "SysTime.hpp"

// To klasa z wszystkimi wartościami w systemie (wartości czujników, status wifi, godzina stan urządzeń itp).
// Ewentualnie można to podzielić na podklasy

class SystemState {
public:
    SystemState();

    // Sensors
    void SetTemperature(float t);
    void SetHumidity(float h);
    void SetIlluminance(uint16_t lux);

    float GetTemperature() const;
    float GetHumidity() const;
    int16_t GetIlluminance() const;

    // Time
    void SetTime(SysTime time);

    SysTime GetTime() const;

    // WiFi
    void SetWiFiStatus(bool status);

    bool GetWiFiStatus() const;

    // Peripherals
    void SetFanPower(uint8_t power);
    void SetLedPower(uint8_t power);
    void SetPumpPower(uint8_t power);
    void SetHeatPower(uint8_t power);

    float GetFanPower() const;
    float GetLedPower() const;
    float GetPumpPower() const;
    float GetHeatPower() const;

private:
    // Sensors
    float m_CurrentTemperature;
    float m_CurrentHumidity;
    
    uint16_t m_CurrentIlluminance;

    // Time
    SysTime m_CurrentTime;

    // WiFi
    bool m_WiFiStatus;

    //Peripherals
    uint8_t m_FanPower;   
    uint8_t m_LedPower;   
    uint8_t m_PumpPower;  
    uint8_t m_HeatPower;  
};