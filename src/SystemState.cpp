#include "SystemState.hpp"

SystemState::SystemState():
    m_CurrentTemperature(0),
    m_CurrentHumidity(0),
    m_CurrentIlluminance(0),
    m_FanPower(0),
    m_LedPower(0),
    m_PumpPower(0),
    m_HeatPower(0),
    m_WorkMode(WorkMode::MANUAL) {}

    // Sensors
void SystemState::SetTemperature(float t) {
    m_CurrentTemperature = t;
}

void SystemState::SetHumidity(float h) {
    m_CurrentHumidity = h;
}

void SystemState::SetIlluminance(uint16_t lux) {
    m_CurrentIlluminance = lux;
}

float SystemState::GetTemperature() const {
    return m_CurrentTemperature;
}

float SystemState::GetHumidity() const {
    return m_CurrentHumidity;
}

uint16_t SystemState::GetIlluminance() const {
    return m_CurrentIlluminance;
}

void SystemState::SetTime(SysTime time) {
    m_CurrentTime = time;
}

SysTime SystemState::GetTime() const {
    return m_CurrentTime;
}

void SystemState::SetWiFiStatus(bool status) {
    m_WiFiStatus = status;
}

bool SystemState::GetWiFiStatus() const {
    return m_WiFiStatus;
}

void SystemState::SetFanPower(uint8_t power) {
    m_FanPower = power;
}

void SystemState::SetLedPower(uint8_t power) {
    m_LedPower = power;
}

void SystemState::SetPumpPower(uint8_t power) {
    m_PumpPower = power;
}

void SystemState::SetHeatPower(uint8_t power) {
    m_HeatPower = power;
}

float SystemState::GetFanPower() const {
    return m_FanPower;
}

float SystemState::GetLedPower() const {
    return m_LedPower;
}

float SystemState::GetPumpPower() const {
    return m_PumpPower;
}

float SystemState::GetHeatPower() const {
    return m_HeatPower;
}

void SystemState::SetWorkMode(WorkMode wm) {
    m_WorkMode = wm;
}

SystemState::WorkMode SystemState::GetWorkMode() const {
    return m_WorkMode;
}
