#pragma once

#include <Arduino.h>
#include "SystemState.hpp"
#include <stdint.h>
#include "FuzzyController.hpp"


class PeripheralsManager {
public:
    PeripheralsManager(SystemState& sys_state);
    void Init();
    void Update();

private:
    SystemState& m_SystemState;
    FuzzyController m_FuzzCtrl;
    const uint8_t m_CIECurve[32] = {
        0,   1,   2,   3,   4,   5,   7,   9,
        12,  15,  18,  22,  27,  32,  38,  44,
        51,  58,  67,  76,  86,  96,  108, 120,
        134, 148, 164, 180, 197, 216, 235, 255
    };
    const uint8_t FAN_PIN = 25;
    const uint8_t LED_PIN = 26;
    const uint8_t PUMP_PIN = 27;
    const uint8_t HEAT_PIN = 14;

    enum class Peripherals : uint8_t {
        NONE = 0,
        FAN,
        LED,
        PUMP,
        HEAT
    };

    void SetOutputPower(Peripherals name);

};