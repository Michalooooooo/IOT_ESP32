#pragma once
#include <BH1750_WE.h>
#include <Adafruit_SHT31.h>
#include <Wire.h>
#include <stdint.h>
#include "SystemState.hpp"

class SensorsManager {
public:
    SensorsManager(SystemState& sys_state);
    void Init();
    void Update();
private:

    Adafruit_SHT31 m_THSensor;
    BH1750_WE m_LightSensor;

    uint32_t m_LastReadTime;
    const uint32_t READ_INTERVAL = 2000;
    SystemState& m_SystemState;
};