#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto RESOLUTION_8BIT = 8;
    constexpr auto RESOLUTION_10BIT = 10;
    constexpr auto RESOLUTION_12BIT = 12;
    constexpr auto RESOLUTION_16BIT = 16;
    constexpr auto WAIT_0US = 0;
    constexpr auto WAIT_16US = 32;

    void regWait(){
        while(ADC->STATUS.bit.SYNCBUSY);
    }
}

namespace M0TWEAK{
    /**
    * description.
    */
    void modifyAdcResolution(uint8_t b){
        ADC->CTRLA.bit.ENABLE = 0;
        regWait();

        if(b == RESOLUTION_8BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_8BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(b == RESOLUTION_10BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_10BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(b == RESOLUTION_12BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_12BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(b == RESOLUTION_16BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_16BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_2 | ADC_AVGCTRL_ADJRES(1);
            ADC->SAMPCTRL.reg = WAIT_16US;
        }

        ADC->CTRLA.bit.ENABLE = 1;
        regWait();
    }
}