#include "ADXL345Handler.hpp"

ADXL345Handler::ADXL345Handler(uint32_t id, uint8_t SDA_pin, uint8_t SCL_pin): 
m_Id(id), m_Acc(id), m_SCLPin(SCL_pin), m_SDAPin(SDA_pin) {

    Init();
}

ADXL345Handler::ADXL345Handler(uint32_t id): 
m_Id(id), m_Acc(id), m_SCLPin(22), m_SDAPin(21) {

    Init();
}

void ADXL345Handler::Init() {
    Wire.begin(m_SDAPin, m_SCLPin);

    if(!m_Acc.begin()) {
        Serial.println("ADXL345 not detected!");
        while(1) {}
    }
}

void ADXL345Handler::GetAccelerations() {
    m_Acc.getEvent(&m_Event);
}

void ADXL345Handler::DisplayCurrentAccelerations() {
    Serial.print("X: ");
    Serial.print(m_Event.acceleration.x);
    Serial.println(" ");
    Serial.print("Y: ");
    Serial.print(m_Event.acceleration.y);
    Serial.println(" ");
    Serial.print("Z: ");
    Serial.print(m_Event.acceleration.z);
    Serial.println(" ");
}
