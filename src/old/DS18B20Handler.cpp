#include "DS18B20Handler.hpp"

uint8_t DS18B20Handler::ID = 0;

DS18B20Handler::DS18B20Handler(uint8_t OneWireBus)
    : ow(OneWireBus), sensors(&ow), ONE_WIRE_BUS(OneWireBus) {    
}

void DS18B20Handler::Init() {
    m_SensorID = ID;
    ID++;

    m_CurrentTemp = 0.0f;
    sensors.begin();
}



void DS18B20Handler::GetTemperature() {
    sensors.requestTemperatures();          
    m_CurrentTemp = sensors.getTempCByIndex(m_SensorID); 
}

void DS18B20Handler::DisplayCurrentTemperature() {
    Serial.print("Temperatura: ");
    Serial.print(m_CurrentTemp);
    Serial.println(" C");
}
