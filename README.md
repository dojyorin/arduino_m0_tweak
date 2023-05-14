# **Arduino M0 Tweak**
![actions:test](https://github.com/dojyorin/arduino_m0_tweak/actions/workflows/test.yaml/badge.svg)
![actions:release](https://github.com/dojyorin/arduino_m0_tweak/actions/workflows/release.yaml/badge.svg)

Tweak the hardware behavior of SAMD21.
Easily hardware behavior tweak, such as CPU overclocking, ADC acceleration, etc.

# Example

```c++
m0tweak::m0cpu::setFrequency(72);
m0tweak::m0adc::setResolution(12);
```

# Details
The only export of this library will be [`arduino_m0_tweak.hpp`](./src/arduino_m0_tweak.hpp).
Other source files are for internal use and should not normally be include.

# OverClock
**!!CAUTION!! Overclocking should be performed at your own risk after fully understanding the risk.**
**I take no responsibility if the MCU burns or bricks.**

I tried simple serialport communication program on my board (Feather M0) and it worked up to 78MHz, but when set it to 80MHz the serialport connection broke.

The ATSAM series clock supply system is divided into 3 stages.

1. "Clock Source" that generates the clock. (Crystal or Lock-Loop)
2. "Clock Generator" that adjust (Prescale, etc.) the clock. (GCLK)
3. "Peripherals" that use clock.

The SAMD21 uses clock source that always outputs 48MHz, usually called "DFLL", and clock generator called "GCLK0" to generate a 48MHz core clock.

SAMD21 also has clock source called "FDPLL" that can output any clock up to 96MHz, although it is not used in normal operation.

You can overclock up to 96MHz by changing the clock source used by the core clock on the sketch to FDPLL.

If only the clock source is changed, GCLK0 is still used as the clock generator, but GCLK0 is shared with various peripherals such as USB in addition to the core clock.

Set the peripheral to use different clock generator to prevent the peripheral from malfunctioning due to clock fluctuations on GCLK0.

In this library, executing the core clock setting function configures to use "GCLK5" as the clock generator for USB.

**Before**

```mermaid
flowchart LR

Crystal --> DFLL --"48MHz"--> GCLK0 --"1/1"--> CPU & USB
```

**After**

```mermaid
flowchart LR

Crystal --> DFLL --"48MHz"--> GCLK4 --"1/48"--> FDPLL --"1~96MHz"--> GCLK0 --"1/1"--> CPU
DFLL --"48MHz"--> GCLK5 --"1/1"--> USB
```

# API
## `m0tweak::m0cpu::setFrequency(f)`
- Arguments
    - `f` : `uint8_t` ... CPU frequency.
- Result
    - `void`

Change the operating frequency of CPU.
Configurable range is `16` ~ `96` MHz in `1` MHz steps.

## `m0tweak::m0adc::setResolution(n)`
- Arguments
    - `n` : `uint8_t` ... Number of sampling bits.
- Result
    - `void`

Change the ADC sampling resolution.
Configurable value is `8` / `10` / `12` / `16` bits.

# Third Party Licenses
This library is thanks to them, respectful.

<details>
<summary>TestOverclock</summary>

- https://next-hack.com/index.php/2020/02/12/overclocking-an-arduino-zero-or-any-atsamd21

```text
TestOverclock: a test sketch to overclock the ATSAMD21

Copyright 2020 Nicola Wrachien www.next-hack.com

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
```

</details>

<details>
<summary>AdcBooster</summary>

- https://synapse.kyoto/tips/AdcBooster/page001.html

```text
license.
```

</details>