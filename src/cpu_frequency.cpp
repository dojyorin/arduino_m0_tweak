#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto FREQ_MIN = 48;
    constexpr auto FREQ_MAX = 96;
    constexpr auto CLOCK_DIV1 = 1;
    constexpr auto CLOCK_DIV48 = 48;
}

/**
* description.
*/
void M0TWEAK::CPU::frequency(uint8_t f){
    #ifndef __SAMD21__
        return;
    #endif

    if(f < FREQ_MIN || FREQ_MAX < f){
        return;
    }

    USBDevice.detach();

    NVMCTRL->CTRLB.bit.RWS = (f + 23) / 24 - 1;

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(4) | GCLK_GENDIV_DIV(CLOCK_DIV48);
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(4) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_DFLL48M;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(4) | GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_FDPLL_Val) | GCLK_CLKCTRL_CLKEN;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    SYSCTRL->DPLLRATIO.reg = SYSCTRL_DPLLRATIO_LDR(f - 1);
    SYSCTRL->DPLLCTRLB.reg = SYSCTRL_DPLLCTRLB_REFCLK_GCLK | SYSCTRL_DPLLCTRLB_FILTER(SYSCTRL_DPLLCTRLB_FILTER_DEFAULT_Val);
    SYSCTRL->DPLLCTRLA.reg = SYSCTRL_DPLLCTRLA_ENABLE;
    while(!(SYSCTRL->DPLLSTATUS.reg & (SYSCTRL_DPLLSTATUS_CLKRDY | SYSCTRL_DPLLSTATUS_LOCK)));

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(CLOCK_DIV1);
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_FDPLL;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(5);
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(5) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_USB_Val) | GCLK_CLKCTRL_GEN_GCLK0;
    while(GCLK->CLKCTRL.bit.CLKEN);

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_USB_Val) | GCLK_CLKCTRL_GEN_GCLK5;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_USB_Val) | GCLK_CLKCTRL_GEN_GCLK5 | GCLK_CLKCTRL_CLKEN;
    while(GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);

    USBDevice.attach();
}