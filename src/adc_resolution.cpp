#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto SR_8BIT = 8;
    constexpr auto SR_10BIT = 10;
    constexpr auto SR_12BIT = 12;
    constexpr auto SR_16BIT = 16;
    constexpr auto WAIT_0US = 0;
    constexpr auto WAIT_16US = 32;
}

/**
* description.
*/
void M0TWEAK::ADC::resolution(uint8_t b){
    #ifndef __SAMD21__
        return;
    #endif

    ADC->CTRLA.bit.ENABLE = 0;
    while(ADC->STATUS.bit.SYNCBUSY);

    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_8BIT;
    ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
    ADC->SAMPCTRL.reg = WAIT_0US;

    ADC->CTRLA.bit.ENABLE = 1;
    while(ADC->STATUS.bit.SYNCBUSY);
}