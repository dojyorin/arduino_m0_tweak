#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

namespace M0TWEAK{
    void modifyCpuFrequency(uint8_t f);
    void modifyAdcResolution(uint8_t b);
}