#pragma once
#include <stdint.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Wire.h>

class ADXL345Handler {
public:
    ADXL345Handler(uint32_t id, uint8_t SDA_pin, uint8_t SCL_pin);
    ADXL345Handler(uint32_t id);

    void GetAccelerations();
    void DisplayCurrentAccelerations();
private:
    inline void Init();


    uint32_t m_Id;
    uint8_t m_SDAPin, m_SCLPin;
    Adafruit_ADXL345_Unified m_Acc;
    sensors_event_t m_Event;
};