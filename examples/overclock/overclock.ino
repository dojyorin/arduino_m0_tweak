#include "Arduino.h"
#include "arduino_m0_tweak.hpp"

void setup(){
    M0TWEAK::CPU::frequency(72);
}

void loop(){}