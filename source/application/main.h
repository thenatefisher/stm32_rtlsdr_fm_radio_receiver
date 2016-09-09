#ifndef __MAIN_H
#define __MAIN_H

#include "usbh_core.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stdio.h"

#define USB_PIPE_NUMBER (0x81)

USBH_HandleTypeDef hUSBHost;
uint8_t isUSBConfigComplete;
uint8_t OutPipe, InPipe;

void USBH_UserProcess(USBH_HandleTypeDef* phost, uint8_t id);

#endif
