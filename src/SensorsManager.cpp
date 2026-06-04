#include "SensorsManager.hpp"

SensorsManager::SensorsManager(SystemState& sys_state): 
    m_LightSensor(0x23),
    m_SystemState(sys_state) {}


// TODO Zrobić Wire.begin raz w setup() //////////////////////////////////////////////////////////////////
void SensorsManager::Init()
{
    // Inicjalizacja sht31
    if (!m_THSensor.begin(0x44)) {
        Serial.println("BLAD: Nie znaleziono czujnika SHT31 pod adresem 0x44!");
    } else {
        Serial.println("SHT31: Połączono pomyślnie.");
    }

    // Inicjalizacja bh1750
    if (!m_LightSensor.init()) {
        Serial.println("BLAD: Nie znaleziono czujnika BH1750 pod adresem 0x23!");
    } else {
        Serial.println("BH1750: Połączono pomyślnie.");
    }
}

void SensorsManager::Update() {
    float light_intensity = m_LightSensor.getLux();
    m_SystemState.SetIlluminance((uint16_t)light_intensity);
    
    float temp = m_THSensor.readTemperature();
    float hum = m_THSensor.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {
        m_SystemState.SetTemperature(temp);
        m_SystemState.SetHumidity(hum);
    } else {
        Serial.println("ERROR: SHT31 | Temperature or humidity is NaN!");
    }
}
