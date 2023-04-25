#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

/**
* Tweak the hardware behavior of SAMD21.
* @see https://github.com/dojyorin/arduino_m0_tweak
*/
namespace M0TWEAK{
    /**
    * Tweak the CPU.
    */
    namespace M0CPU{
        /**
        * Change the operating frequency of CPU.
        * Configurable range is `16` ~ `96` MHz in `1` MHz steps.
        * Executing this function changes the clock source configuration.
        * Be sure to read the README.
        * [CAUTION] Overclock at your own risk!
        * @param f CPU frequency (MHz)
        */
        void changeFrequency(uint8_t f);
    }

    /**
    * Tweak the ADC.
    */
    namespace M0ADC{
        /**
        * @param n Sampling resolution (bits)
        */
        void changeResolution(uint8_t n);
    }
}