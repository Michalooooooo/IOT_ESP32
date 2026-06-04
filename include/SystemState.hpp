#pragma once

#include <stdint.h>

class SystemState {
public:
    SystemState();

    // Sensors
    void SetTemperature(float t);
    void SetHumidity(float h);
    void SetIlluminance(uint16_t lux);

    float GetTemperature() const;
    float GetHumidity() const;
    uint16_t GetIlluminance() const;

    // WiFi
    void SetWiFiStatus(bool status);

    bool GetWiFiStatus() const;

    // Peripherals
    void SetFanPower(uint8_t power);
    void SetLedPower(uint8_t power);
    void SetPumpPower(uint8_t power);
    void SetHeatPower(uint8_t power);
    void ResetPeripherals();

    float GetFanPower() const;
    float GetLedPower() const;
    float GetPumpPower() const;
    float GetHeatPower() const;

    enum class WorkMode {
        AUTO = 0,
        MANUAL
    };
    
    void SetWorkMode(WorkMode wm);
    WorkMode GetWorkMode() const;

private:
    WorkMode m_WorkMode;
    
    // Sensors
    float m_CurrentTemperature;
    float m_CurrentHumidity;
    
    uint16_t m_CurrentIlluminance;

    // WiFi
    bool m_WiFiStatus;

    //Peripherals
    uint8_t m_FanPower;   
    uint8_t m_LedPower;   
    uint8_t m_PumpPower;  
    uint8_t m_HeatPower;  
};