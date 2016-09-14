#ifndef __MAIN_H
#define __MAIN_H

#include "usbh_core.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stdio.h"
#include "rtl-sdr.h"
#include "trace.h"
#include "fm_radio.h"
#include "audio_player.h"

#define USB_PIPE_NUMBER 0x81
#define KILOBYTES 1024
#define RAW_BUFFER_BYTES (25*KILOBYTES)
#define SIZEOF_DEMOD_BUF_EL 2
#define DEMOD_BUFF_BYTES (RAW_BUFFER_BYTES/SIZEOF_DEMOD_BUF_EL)
#define DOWNSAMPLE 15
#define RTL_SAMPLERATE 240000

volatile uint8_t raw_bufA[RAW_BUFFER_BYTES];
volatile uint8_t raw_bufB[RAW_BUFFER_BYTES];
volatile uint8_t* raw_buf_filling;

volatile int16_t demod_bufferA[DEMOD_BUFF_BYTES];
volatile int16_t demod_bufferB[DEMOD_BUFF_BYTES];
volatile int16_t* curr_demod_buff;

USBH_HandleTypeDef hUSBHost;
uint8_t usb_device_ready;
uint8_t OutPipe, InPipe;

void USBH_UserProcess(USBH_HandleTypeDef* phost, uint8_t id);

#endif
