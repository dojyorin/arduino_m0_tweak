#include "./arduino_m0_tweak.hpp"

namespace{
    constexpr auto FREQ_MIN = 1;
    constexpr auto FREQ_MAX = 96;

    void syncBusy(){
        while(GCLK->STATUS.bit.SYNCBUSY);
    }

    void inputGCLK(uint8_t id, uint8_t divide, uint32_t source){
        GCLK->GENDIV.reg = GCLK_GENDIV_ID(id) | GCLK_GENDIV_DIV(divide);
        syncBusy();
        GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(id) | source | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
        syncBusy();
    }

    void outputGCLK(uint32_t target, uint32_t source){
        GCLK->CLKCTRL.reg = target | source | GCLK_CLKCTRL_CLKEN;
        syncBusy();
    }
}

void m0tweak::cpuFrequency(uint8_t f){
    if(f < FREQ_MIN || FREQ_MAX < f){
        return;
    }

    SYSCTRL->DPLLRATIO.reg = SYSCTRL_DPLLRATIO_LDR(f - 1);
    NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_RWS((f + 23) / 24 - 1);
    // SysTick->LOAD = f * 1000 - 1;
    // SysTick->VAL = 0;

    if(!SYSCTRL->DPLLSTATUS.bit.ENABLE){
        SYSCTRL->DPLLCTRLB.reg = SYSCTRL_DPLLCTRLB_FILTER_DEFAULT | SYSCTRL_DPLLCTRLB_REFCLK_GCLK;
        SYSCTRL->DPLLCTRLA.reg = SYSCTRL_DPLLCTRLA_ENABLE;
        while(!SYSCTRL->DPLLSTATUS.bit.LOCK & !SYSCTRL->DPLLSTATUS.bit.CLKRDY);

        USBDevice.detach();

        inputGCLK(4, 48, GCLK_GENCTRL_SRC_DFLL48M);
        inputGCLK(5, 1, GCLK_GENCTRL_SRC_DFLL48M);
        outputGCLK(GCLK_CLKCTRL_ID_FDPLL, GCLK_CLKCTRL_GEN_GCLK4);
        outputGCLK(GCLK_CLKCTRL_ID_USB, GCLK_CLKCTRL_GEN_GCLK5);
        inputGCLK(0, 1, GCLK_GENCTRL_SRC_FDPLL);

        USBDevice.attach();
    }
}