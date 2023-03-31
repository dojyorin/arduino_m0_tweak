#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

namespace M0TWEAK{
    namespace M0CPU{
        /**
        * @param n CPU Frequency (MHz)
        */
        void frequency(uint8_t n);
    }

    namespace M0ADC{
        /**
        * @param n Sampling resolution (bits)
        */
        void resolution(uint8_t n);
    }
}