#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

namespace M0TWEAK{
    namespace M0CPU{
        void frequency(uint8_t n);
    }

    namespace M0ADC{
        void resolution(uint8_t n);
    }
}