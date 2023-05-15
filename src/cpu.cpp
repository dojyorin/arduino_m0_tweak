#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto FREQ_MIN = 16;
    constexpr auto FREQ_MAX = 96;

    void syncWait(){
        while(GCLK->STATUS.bit.SYNCBUSY);
    }
}

void m0tweak::m0cpu::setFrequency(uint8_t f){
    if(f < FREQ_MIN || FREQ_MAX < f){
        return;
    }

    USBDevice.detach();

    NVMCTRL->CTRLB.bit.RWS = (f + 23) / 24 - 1;

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(4) | GCLK_GENDIV_DIV(48);
    syncWait();

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(4) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    syncWait();

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_FDPLL | GCLK_CLKCTRL_GEN_GCLK4 | GCLK_CLKCTRL_CLKEN;
    syncWait();

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(5) | GCLK_GENDIV_DIV(1);
    syncWait();

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(5) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    syncWait();

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_USB | GCLK_CLKCTRL_GEN_GCLK5 | GCLK_CLKCTRL_CLKEN;
    syncWait();

    SYSCTRL->DPLLRATIO.reg = SYSCTRL_DPLLRATIO_LDR(f - 1);
    SYSCTRL->DPLLCTRLA.reg = SYSCTRL_DPLLCTRLA_ENABLE;
    SYSCTRL->DPLLCTRLB.reg = SYSCTRL_DPLLCTRLB_FILTER_DEFAULT | SYSCTRL_DPLLCTRLB_REFCLK_GCLK;
    while(!SYSCTRL->DPLLSTATUS.bit.LOCK & !SYSCTRL->DPLLSTATUS.bit.CLKRDY);

    GCLK->GENDIV.reg = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(1);
    syncWait();

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC_FDPLL | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    syncWait();

    USBDevice.attach();

    // SysTick->LOAD = f * 1000 - 1;
    // SysTick->VAL = 0;
}