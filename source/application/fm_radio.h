#ifndef FM_RADIO_H
#define FM_RADIO_H

#include "stdint.h"
#include "main.h"
#include "arm_math.h"
#include "convenience/convenience.h"
#include "rtl-sdr.h"
#include "audio_player.h"

// use statically defined rtlsdr instance
extern rtlsdr_dev_t static_dev;
rtlsdr_dev_t *dev;

struct FMRadio {
    int32_t tuner_ppm_error;
    uint32_t tuner_frequency;
    uint32_t adc_samp_rate;
    volatile int32_t raw_buf_remain_bytes;
    volatile uint8_t is_raw_buf_complete;
    volatile uint8_t is_usb_app_started;
};

int32_t fmradio_atan2(int32_t y, int32_t x);
void fmradio_cmultiply(int32_t ar, int32_t aj, int32_t br, int32_t bj, int32_t* cr, int32_t* cj);
int32_t fmradio_polar_disc(int32_t ar, int32_t aj, int32_t br, int32_t bj);
void fmradio_process(void);
int fmradio_init(void);

#endif
