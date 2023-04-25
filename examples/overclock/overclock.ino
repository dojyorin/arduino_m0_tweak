#include "arduino_m0_tweak.hpp"

void setup(){
    M0TWEAK::M0CPU::changeFrequency(72);
}

void loop(){}