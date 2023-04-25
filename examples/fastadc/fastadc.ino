#include "arduino_m0_tweak.hpp"

void setup(){
    M0TWEAK::M0ADC::changeResolution(12);
}

void loop(){}