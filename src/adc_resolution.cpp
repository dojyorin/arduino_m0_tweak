#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto SAMPLING_INTERVAL = 0x20;
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

    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_12BIT;
    ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
    ADC->SAMPCTRL.reg = 0;

    ADC->CTRLA.bit.ENABLE = 1;
    while(ADC->STATUS.bit.SYNCBUSY);
}