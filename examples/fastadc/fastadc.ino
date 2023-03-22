#include "Arduino.h"
#include "arduino_m0_tweak.hpp"

void setup(){
    M0TWEAK::ADC::resolution(12);
}

void loop(){}