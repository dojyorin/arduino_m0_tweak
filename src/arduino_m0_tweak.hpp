#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

namespace M0TWEAK{
    void cpuFrequency(uint8_t f);
    void adcResolution(uint8_t b);
}