#pragma once

#include "stdint.h"
#include "sam.h"

namespace M0TWEAK{}

void M0TWEAK::modifyCpuFrequency(uint8_t f);
void M0TWEAK::modifyAdcResolution(uint8_t b);