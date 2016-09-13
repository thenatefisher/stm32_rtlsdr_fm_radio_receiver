#include "rtl-sdr.h"
#include "stdint.h"
#include "main.h"
#include "arm_math.h"
#include "convenience/convenience.h"
#include "audio_player.h"

int32_t fast_atan2(int32_t y, int32_t x);
void multiply(int32_t ar, int32_t aj, int32_t br, int32_t bj, int32_t* cr, int32_t* cj);
int32_t polar_disc_fast(int32_t ar, int32_t aj, int32_t br, int32_t bj);
void fmradio_process(void);
int fmradio_init(void);
