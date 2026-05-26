#include "PeripheralsManager.hpp"

PeripheralsManager::PeripheralsManager(SystemState &sys_state):
    m_SystemState(sys_state),
    m_FuzzCtrl(sys_state) {}

void PeripheralsManager::Init() {
    m_FuzzCtrl.Init();

    analogWrite(FAN_PIN, 0);
    analogWrite(LED_PIN, 0);
    analogWrite(PUMP_PIN, 0);
    analogWrite(HEAT_PIN, 0);
}

void PeripheralsManager::Update() {
    if(m_SystemState.GetWorkMode() == SystemState::WorkMode::AUTO) {
        m_FuzzCtrl.Update();

        SetOutputPower(Peripherals::FAN);
        SetOutputPower(Peripherals::LED);
        SetOutputPower(Peripherals::PUMP);
        SetOutputPower(Peripherals::HEAT);
    }
}

void PeripheralsManager::SetOutputPower(Peripherals name) {

    switch(name) {
        case Peripherals::FAN: {
            uint8_t fan_speed = m_SystemState.GetFanPower();
            uint8_t idx = static_cast<uint8_t>(static_cast<float>(fan_speed) / 255.0f) * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(FAN_PIN, pwm_value);
            break;
        }
        case Peripherals::LED: {
            uint8_t light_intensity = m_SystemState.GetLedPower();
            uint8_t idx = static_cast<uint8_t>(static_cast<float>(light_intensity) / 255.0f) * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(LED_PIN, pwm_value);
            break;
        }
        case Peripherals::PUMP: {
            uint8_t pump_power = m_SystemState.GetPumpPower();
            uint8_t idx = static_cast<uint8_t>(static_cast<float>(pump_power) / 255.0f) * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(PUMP_PIN, pwm_value);
            break;
        }
        case Peripherals::HEAT: {
            uint8_t heat_power = m_SystemState.GetPumpPower();
            uint8_t idx = static_cast<uint8_t>(static_cast<float>(heat_power) / 255.0f) * 31;
            uint8_t pwm_value = m_CIECurve[idx];

            analogWrite(HEAT_PIN, pwm_value);
            break;
        }
    }
}
