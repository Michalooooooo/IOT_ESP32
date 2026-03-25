#pragma once

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20Handler {
public:
    DS18B20Handler(uint8_t OneWireBus);
    void GetTemperature();
    void DisplayCurrentTemperature();

 private:   
    inline void Init();

    static uint8_t ID;

    float m_CurrentTemp;
    uint8_t ONE_WIRE_BUS;
    
    OneWire ow;
    DallasTemperature sensors;
    uint8_t m_SensorID;
};