#pragma once

#ifdef __SAMD21__

#include "stdint.h"
#include "sam.h"

namespace M0TWEAK{
    void modifyCpuFrequency(uint8_t f);
    void modifyAdcResolution(uint8_t b);
}

#endif