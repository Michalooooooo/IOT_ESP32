#include "PeripheralsManager.hpp"

PeripheralsManager::PeripheralsManager(const SystemState &sys_state):
    m_SystemState(sys_state) {}

void PeripheralsManager::Init() {
    analogWrite(FAN_PIN, 0);
    analogWrite(LED_PIN, 0);
    analogWrite(PUMP_PIN, 0);
    analogWrite(HEAT_PIN, 0);
}

void PeripheralsManager::Update() {
    SetOutputPower(Peripherals::FAN);
    SetOutputPower(Peripherals::LED);
    SetOutputPower(Peripherals::PUMP);
    SetOutputPower(Peripherals::HEAT);
}

void PeripheralsManager::SetOutputPower(Peripherals name) {

    switch(name) {
        case Peripherals::FAN:
            float fan_speed = m_SystemState.GetFanPower();
            uint8_t idx = fan_speed * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(FAN_PIN, pwm_value);
            break;

        case Peripherals::LED:
            float light_intensity = m_SystemState.GetLedPower();
            uint8_t idx = light_intensity * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(LED_PIN, pwm_value);
            break;

        case Peripherals::PUMP:
            float pump_power = m_SystemState.GetPumpPower();
            uint8_t idx = pump_power * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(PUMP_PIN, pwm_value);
            break;

        case Peripherals::HEAT:
            float heat_power = m_SystemState.GetPumpPower();
            uint8_t idx = heat_power * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(HEAT_PIN, pwm_value);
            break;

    }
}
