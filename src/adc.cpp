#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto RES_8BIT = 8;
    constexpr auto RES_10BIT = 10;
    constexpr auto RES_12BIT = 12;
    constexpr auto RES_16BIT = 16;

    void syncBusy(){
        while(ADC->STATUS.bit.SYNCBUSY);
    }

    void sampleMethod(uint16_t resolution, uint8_t sample, uint8_t wait, uint8_t coefficient){
        ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | resolution;
        ADC->AVGCTRL.reg = sample | ADC_AVGCTRL_ADJRES(coefficient);
        ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(wait);
    }
}

void m0tweak::adcPrecision(uint8_t n){
    if(n != RES_8BIT && n != RES_10BIT && n != RES_12BIT && n != RES_16BIT){
        return;
    }

    ADC->CTRLA.reg = ADC_CTRLA_RESETVALUE;
    syncBusy();

    if(n == RES_8BIT){
        sampleMethod(ADC_CTRLB_RESSEL_8BIT, ADC_AVGCTRL_SAMPLENUM_1, 0, 0);
    }
    else if(n == RES_10BIT){
        sampleMethod(ADC_CTRLB_RESSEL_10BIT, ADC_AVGCTRL_SAMPLENUM_1, 0, 0);
    }
    else if(n == RES_12BIT){
        sampleMethod(ADC_CTRLB_RESSEL_12BIT, ADC_AVGCTRL_SAMPLENUM_1, 0, 0);
    }
    else if(n == RES_16BIT){
        sampleMethod(ADC_CTRLB_RESSEL_16BIT, ADC_AVGCTRL_SAMPLENUM_2, 32, 1);
    }

    ADC->CTRLA.reg = ADC_CTRLA_ENABLE;
    syncBusy();
}