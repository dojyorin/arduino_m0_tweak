#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

namespace M0TWEAK{
    /**
    * Adjust CPU behavior.
    */
    namespace M0CPU{
        /**
        * Change the operating frequency of CPU.
        * Configurable range is `16` ~ `96` MHz in `1` MHz steps.
        * Executing this function changes the clock source configuration.
        * Be sure to read the README.
        * **Caution! Overclock at your own risk!**
        * @param n CPU Frequency (MHz)
        * @see https://github.com/dojyorin/arduino_m0_tweak
        */
        void frequency(uint8_t n);
    }

    /**
    * Adjust ADC behavior.
    */
    namespace M0ADC{
        /**
        * @param n Sampling resolution (bits)
        */
        void resolution(uint8_t n);
    }
}