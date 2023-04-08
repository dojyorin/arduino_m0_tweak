#include "./arduino_m0_tweak.hpp"

namespace{

constexpr auto RES_8BIT = 8;
constexpr auto RES_10BIT = 10;
constexpr auto RES_12BIT = 12;
constexpr auto RES_16BIT = 16;
constexpr auto DELAY_0US = 0;
constexpr auto DELAY_16US = 32;

void syncWait(){
    while(ADC->STATUS.bit.SYNCBUSY);
}

}

void M0TWEAK::M0ADC::resolution(uint8_t n){
    if(n != RES_8BIT && n != RES_10BIT && n != RES_12BIT && n != RES_16BIT){
        return;
    }

    ADC->CTRLA.bit.ENABLE = 0;
    syncWait();

    ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
    ADC->SAMPCTRL.reg = DELAY_0US;

    if(n == RES_8BIT){
        ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_8BIT;
    }
    else if(n == RES_10BIT){
        ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_10BIT;
    }
    else if(n == RES_12BIT){
        ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_12BIT;
    }
    else if(n == RES_16BIT){
        ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_16BIT;
        ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_2 | ADC_AVGCTRL_ADJRES(1);
        ADC->SAMPCTRL.reg = DELAY_16US;
    }

    ADC->CTRLA.bit.ENABLE = 1;
    syncWait();
}