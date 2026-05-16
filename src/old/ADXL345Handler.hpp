#pragma once

#include <stdint.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Wire.h>


/*Podłączenie 

GPIO_VCC    -> ADXL345_VCC
GPIO_GND    -> ADXL345_GND
GPIO_21     -> ADXL345_SDA
GPIO_22     -> ADXL345_SCL

//////////////////////////////////////////////////////////*/ 

class ADXL345Handler {
public:
    ADXL345Handler(uint32_t id, uint8_t SDA_pin, uint8_t SCL_pin);
    ADXL345Handler(uint32_t id);

    void Init();
    void GetAccelerations();
    void DisplayCurrentAccelerations();
private:
    

    uint32_t m_Id;
    uint8_t m_SDAPin, m_SCLPin;
    Adafruit_ADXL345_Unified m_Acc;
    sensors_event_t m_Event;
};