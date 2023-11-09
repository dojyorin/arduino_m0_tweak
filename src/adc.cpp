#include "./arduino_m0_tweak.hpp"

void m0tweak::adcPrecision(uint8_t bit){
    if(bit != 8 && bit != 10 && bit != 12 && bit != 16){
        return;
    }

    ADC->CTRLA.reg = ADC_CTRLA_RESETVALUE;
    while(ADC->STATUS.bit.SYNCBUSY);

    ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(0);

    switch(bit){
        case 8: {
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_8BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
        } break;

        case 10: {
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_10BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
        } break;

        case 12: {
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_12BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
        } break;

        case 16: {
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_16BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_2 | ADC_AVGCTRL_ADJRES(0);
        } break;

        default: break;
    }

    ADC->CTRLA.reg = ADC_CTRLA_ENABLE;
    while(ADC->STATUS.bit.SYNCBUSY);
}