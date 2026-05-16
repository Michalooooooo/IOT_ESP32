#pragma once
#include <stdint.h>
#include "SystemState.hpp"

class Sensor {
public:
    Sensor(SystemState& sys_state);
    virtual ~Sensor() = default;
    virtual void Init() = 0;
    virtual void Measure() = 0;

    inline uint8_t GetID() const {return m_ID;}
private:
    inline static uint8_t s_SensorID = 0;
    uint8_t m_ID;
    SystemState& m_SystemState;
};