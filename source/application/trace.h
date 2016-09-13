#ifndef DEBUG_H
#define DEBUG_H

#include "stm32f7xx_hal.h"

#if 1
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

void config_itm(void);
void itm_print(uint8_t, uint32_t);

#endif
