#pragma once
#include "SystemState.hpp"
#include <stdint.h>
#include <cmath>

class FuzzyController {
public:
    FuzzyController(SystemState& sys_state);
    void Init();

    void Update();

private:
    float MfTrap(float x, float a, float b, float c, float d);

    float Cold(float t);
    float Ok(float t);
    float Hot(float t);

    float Dry(float h);
    float Wet(float h);

    float Dark(float l);
    float Bright(float l);

    void ComputeFan(float t, float h, float l);
    void ComputeHeater(float t, float h, float l);
    void ComputePump(float t, float h, float l);
    void ComputeLed(float t, float h, float l);

    float Weighted(float activation, float value, float& num, float& den);

    uint8_t m_CurrentFan;
    uint8_t m_CurrentLed;
    uint8_t m_CurrentHeat;
    uint8_t m_CurrentPump;
    
    SystemState& m_SystemState;
};