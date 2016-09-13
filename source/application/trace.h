#ifndef TRACE_H
#define TRACE_H

#include "stm32f7xx_hal.h"

#if 1
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

typedef struct {
    uint8_t variant;
    uint8_t revision;
    uint16_t part_no;
} TargetInfo;

void trace_config(void);
void trace_itm_print(uint8_t, uint32_t);
void trace_set_traps(void);
void trace_get_tgt_info(TargetInfo* t);

#endif
