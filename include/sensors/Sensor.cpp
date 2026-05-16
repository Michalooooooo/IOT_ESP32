#include "Sensor.hpp"

Sensor::Sensor(SystemState& sys_state): 
    m_ID(s_SensorID++),
    m_SystemState(sys_state) {}