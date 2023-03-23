#include "Arduino.h"
#include "arduino_m0_tweak.hpp"

void setup(){
    M0TWEAK::modifyAdcResolution(12);
}

void loop(){}