#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto R_8BIT = 8;
    constexpr auto R_10BIT = 10;
    constexpr auto R_12BIT = 12;
    constexpr auto R_16BIT = 16;
    constexpr auto WAIT_0US = 0;
    constexpr auto WAIT_16US = 32;

    void syncWait(){
        while(ADC->STATUS.bit.SYNCBUSY);
    }
}

    /**
    * description.
    */
    void M0TWEAK::M0ADC::resolution(uint8_t n){
        if(n != R_8BIT && n != R_10BIT && n != R_12BIT && n != R_16BIT){
            return;
        }

        ADC->CTRLA.bit.ENABLE = 0;
        syncWait();

        if(n == R_8BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_8BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(n == R_10BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_10BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(n == R_12BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_12BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 | ADC_AVGCTRL_ADJRES(0);
            ADC->SAMPCTRL.reg = WAIT_0US;
        }
        else if(n == R_16BIT){
            ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64 | ADC_CTRLB_RESSEL_16BIT;
            ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_2 | ADC_AVGCTRL_ADJRES(1);
            ADC->SAMPCTRL.reg = WAIT_16US;
        }

        ADC->CTRLA.bit.ENABLE = 1;
        syncWait();
    }