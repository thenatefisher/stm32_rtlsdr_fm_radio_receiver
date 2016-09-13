#ifndef FM_RADIO_H
#define FM_RADIO_H

#include "rtl-sdr.h"
#include "stdint.h"
#include "main.h"
#include "arm_math.h"
#include "convenience/convenience.h"
#include "audio_player.h"

int32_t gain;
int32_t ppm_error;
uint32_t frequency;
uint32_t samp_rate;
volatile int32_t raw_buf_remain_bytes;
volatile uint8_t raw_buf_complete;
volatile uint8_t usb_app_started;
rtlsdr_dev_t *dev;
extern rtlsdr_dev_t static_dev;



int32_t fast_atan2(int32_t y, int32_t x);
void multiply(int32_t ar, int32_t aj, int32_t br, int32_t bj, int32_t* cr, int32_t* cj);
int32_t polar_disc_fast(int32_t ar, int32_t aj, int32_t br, int32_t bj);
void fmradio_process(void);
int fmradio_init(void);

#endif
