#include "main.h"
#include "exceptions.h"

extern HCD_HandleTypeDef hhcd;

// Cortex-M7 Processor Exceptions Handlers

void NMI_Handler(void) {
    while (1);
}

void HardFault_Handler(void) {
    while (1);
}

void MemManage_Handler(void) {
    while (1);
}

void BusFault_Handler(void) {
    while (1);
}

void UsageFault_Handler(void) {
    while (1);
}

void SVC_Handler(void) {
    while (1);
}

void DebugMon_Handler(void) {
    while (1);
}

void PendSV_Handler(void) {
    while (1);
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

// STM32F7xx Peripherals Interrupt Handlers 

void OTG_HS_IRQHandler(void) {
    HAL_HCD_IRQHandler(&hhcd);
}
