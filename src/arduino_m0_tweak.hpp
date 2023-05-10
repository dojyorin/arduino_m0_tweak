#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

/**
* Tweak the hardware behavior of SAMD21.
* @see https://github.com/dojyorin/arduino_m0_tweak
*/
namespace m0tweak{
    /**
    * Tweak CPU.
    */
    namespace m0cpu{
        /**
        * Change the operating frequency of CPU.
        * Configurable range is `16` ~ `96` MHz in `1` MHz steps.
        * Executing this function changes the clock source configuration.
        * Be sure to read the README.
        * <CAUTION> Overclock at your own risk!
        * @param f CPU frequency.
        */
        void changeFrequency(uint8_t f);
    }

    /**
    * Tweak ADC.
    */
    namespace m0adc{
        /**
        * Change the ADC sampling resolution.
        * Configurable value is `8` / `10` / `12` / `16` bits.
        * Only in `16` bits operation, it samples twice and output the average value.
        * @param n Number of sampling bits.
        */
        void changeResolution(uint8_t n);
    }
}