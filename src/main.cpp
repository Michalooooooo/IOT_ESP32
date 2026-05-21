
#include "Button.hpp"
#include "OLEDHandler.hpp"
#include "SystemState.hpp"
#include <Arduino.h>
#include <stdint.h>

SystemState sys_state;
OLEDHandler oh(21, 22, sys_state);

void setup() {
  
  Serial.begin(115200);
  Serial.println("START");
  oh.Init();

}

void loop() {
  oh.UpdateScreen();
}

