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
    * Set the CPU frequency.
    * Configurable range is `1` ~ `96` MHz in `1` MHz steps.
    * **!!CAUTION!! Overclocking should be performed at your own risk after fully understanding the risk.**
    * **I take no responsibility if the MCU burns or bricks.**
    * **Be sure to read the README.**
    * @see https://github.com/dojyorin/arduino_m0_tweak/blob/master/README.md#overclock
    * @example
    * ```c++
    * m0tweak::cpuFrequency(72);
    * ```
    */
    void cpuFrequency(uint8_t f);

    /**
    * Set the ADC sampling resolution.
    * Configurable value is `8` / `10` / `12` / `16` bits.
    * @example
    * ```c++
    * m0tweak::adcPrecision(12);
    * ```
    */
    void adcPrecision(uint8_t n);
}