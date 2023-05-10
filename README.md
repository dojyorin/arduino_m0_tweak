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

# CAUTION!
**Overclocking should be performed at your own risk after fully understanding the risk.**
**If the MCU burns or brick, we are not responsible for any responsibility.**

# Third Party Licenses
This library is thanks to them, respectful.

<p>
<details>
<summary>Show more details...</summary>
<p>

## TestOverclock
- https://next-hack.com/index.php/2020/02/12/overclocking-an-arduino-zero-or-any-atsamd21

TestOverclock: a test sketch to overclock the ATSAMD21

Copyright 2020 Nicola Wrachien www.next-hack.com

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

## AdcBooster
- https://synapse.kyoto/tips/AdcBooster/page001.html

</p>
</details>
</p>