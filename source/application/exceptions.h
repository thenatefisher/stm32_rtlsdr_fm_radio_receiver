#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include "main.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void OTG_HS_IRQHandler(void);
void AUDIO_IN_SAIx_DMAx_IRQHandler(void);
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void);

#endif
