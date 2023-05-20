#pragma once

#include "stdint.h"
#include "sam.h"
#include "USB/USBAPI.h"

/**
* Bring out hardware performance of SAMD21 such as overclock.
* @see https://github.com/dojyorin/arduino_m0_tweak
*/
namespace m0tweak{
    /**
    * Set CPU frequency.
    * Configurable range is `1` ~ `96` MHz in `1` MHz steps.
    * **!!CAUTION!! Overclocking should be performed at your own risk after fully understanding risk.**
    * **I take no responsibility if MCU burn or brick.**
    * **Be sure to read the README.**
    * @see https://github.com/dojyorin/arduino_m0_tweak/blob/master/README.md#overclock
    * @example
    * ```c++
    * m0tweak::cpuFrequency(72);
    * ```
    */
    void cpuFrequency(uint8_t f);

    /**
    * Set ADC sampling resolution.
    * Configurable value is `8` / `10` / `12` / `16` bits.
    * @example
    * ```c++
    * m0tweak::adcPrecision(12);
    * ```
    */
    void adcPrecision(uint8_t n);
}