#include "FuzzyController.hpp"

FuzzyController::FuzzyController(SystemState& sys_state):
    m_SystemState(sys_state),
    m_CurrentFan(0),
    m_CurrentLed(0),
    m_CurrentHeat(0),
    m_CurrentPump(0) {}

void FuzzyController::Init() {}

void FuzzyController::Update() {
    float temp  = m_SystemState.GetTemperature();
    float hum   = m_SystemState.GetHumidity();
    float light = m_SystemState.GetIlluminance();

    ComputeFan(temp, hum, light);
    ComputeHeater(temp, hum, light);
    ComputePump(temp, hum, light);
    ComputeLed(temp, hum, light);

    m_SystemState.SetFanPower(m_CurrentFan);
    m_SystemState.SetHeatPower(m_CurrentHeat);
    m_SystemState.SetPumpPower(m_CurrentPump);
    m_SystemState.SetLedPower(m_CurrentLed);
}

// ===================== MEMBERSHIP FUNCTION =====================

float FuzzyController::MfTrap(float x, float a, float b, float c, float d) {
    if (x <= a || x >= d) return 0.0f;
    if (x >= b && x <= c) return 1.0f;

    if (x < b) {
        if (b == a) return 1.0f; // Dielenie przez zero
        return (x - a) / (b - a);
    } else {
        if (d == c) return 1.0f; // Dielenie przez zero
        return (d - x) / (d - c);
    }
}

// ===== FUZIFICATION =====

float FuzzyController::Cold(float t)  { return MfTrap(t, 0.f, 0.f, 14.f, 22.f); } 
float FuzzyController::Ok(float t)    { return MfTrap(t, 14.f, 20.f, 27.f, 32.f); }
float FuzzyController::Hot(float t)   { return MfTrap(t, 24.f, 32.f, 50.f, 50.f); }

float FuzzyController::Dry(float h)   { return MfTrap(h, 0.f, 0.f, 40.f, 60.f); }
float FuzzyController::Wet(float h)   { return MfTrap(h, 45.f, 70.f, 100.f, 100.f); }

float FuzzyController::Dark(float l)  { return MfTrap(l, 0.f, 0.f, 300.f, 600.f); }
float FuzzyController::Bright(float l){ return MfTrap(l, 400.f, 750.f, 1023.f, 1023.f); } // FIXME moze byc koniecznosc zmodyfikowania

// ==========================================

float FuzzyController::Weighted(float a, float v, float& num, float& den) {
    num += a * v;
    den += a;
    return 0;
}

// ===================== DEVICES =====================

void FuzzyController::ComputeFan(float t, float h, float l) {
    float num = 0, den = 0;

    float c = Cold(t);
    float o = Ok(t);
    float hgt = Hot(t);
    float w = Wet(h); 

    Weighted(c, 0, num, den);     
    Weighted(o, 60, num, den);    
    Weighted(hgt, 255, num, den); 
    Weighted(w, 200, num, den);   

    if(den == 0) {
        m_CurrentFan = 0;
    } else {
        m_CurrentFan = static_cast<uint8_t>(std::roundf(num / den));
    }

}

void FuzzyController::ComputeHeater(float t, float h, float l) {
    float num = 0, den = 0;

    float c = Cold(t);
    float o = Ok(t);
    float hgt = Hot(t);

    Weighted(c, 255, num, den); 
    Weighted(o, 0, num, den);   
    Weighted(hgt, 0, num, den); 

    if(den == 0) {
        m_CurrentHeat = 0;
    } else {
        m_CurrentHeat = static_cast<uint8_t>(std::roundf(num / den));
    }
}

void FuzzyController::ComputePump(float t, float h, float l) {
    float num = 0, den = 0;

    float d = Dry(h);
    float w = Wet(h);

    Weighted(d, 255, num, den); 
    Weighted(w, 0, num, den);   

    if(den == 0) {
        m_CurrentPump = 0;
    } else {
        m_CurrentPump = static_cast<uint8_t>(std::roundf(num / den));
    }
}

void FuzzyController::ComputeLed(float t, float h, float l) {
    float num = 0, den = 0;

    float dk = Dark(l);
    float br = Bright(l);

    Weighted(dk, 255, num, den); 
    Weighted(br, 0, num, den);  

    if(den == 0) {
        m_CurrentLed = 0;
    } else {
        m_CurrentLed = static_cast<uint8_t>(std::roundf(num / den));
    }
}