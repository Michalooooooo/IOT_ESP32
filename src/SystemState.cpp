#include "SystemState.hpp"

SystemState::SystemState():
    m_CurrentTemperature(0),
    m_CurrentHumidity(0),
    m_CurrentIlluminance(0) {}

    // Sensors
void SystemState::SetTemperature(float& t) {
    m_CurrentTemperature = t;
}

void SystemState::SetHumidity(float& h) {
    m_CurrentHumidity = h;
}

void SystemState::SetIlluminance(uint16_t& lux) {
    m_CurrentIlluminance = lux;
}

float SystemState::GetTemperature() const {
    return m_CurrentTemperature;
}

float SystemState::GetHumidity() const {
    return m_CurrentHumidity;
}

int16_t SystemState::GetIlluminance() const {
    return m_CurrentIlluminance;
}

void SystemState::SetTime(SysTime &time) {
    m_CurrentTime = time;
}

SysTime SystemState::GetTime() const {
    return m_CurrentTime;
}

void SystemState::SetWiFiStatus(bool &status) {
    m_WiFiStatus = status;
}

bool SystemState::GetWiFiStatus() const {
    return m_WiFiStatus;
}
