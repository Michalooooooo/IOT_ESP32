#pragma once

#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*Podłączenie 

GPIO_VCC    -> DS18B20345_RED
GPIO_GND    -> DS18B20345_BLACK
GPIO_4      -> DS18B20345_YELLOW

+ REZYSTOR 5.1kΩ RED -> REZYSTOR -> YELLOW

//////////////////////////////////////////////////////////*/ 

class DS18B20Handler {
public:
    DS18B20Handler(uint8_t OneWireBus);
    void GetTemperature();
    void DisplayCurrentTemperature();
    void Init();
    
 private:   
    static uint8_t ID;

    float m_CurrentTemp;
    uint8_t ONE_WIRE_BUS;
    
    OneWire ow;
    DallasTemperature sensors;
    uint8_t m_SensorID;
};