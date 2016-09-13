#ifndef __AUDIO_PLAYER_H
#define __AUDIO_PLAYER_H

#include "stm32746g_discovery_audio.h"
#include "stdio.h"
#include "trace.h"

struct AudioPlayer {
    uint8_t volume;
    uint8_t is_playing;
    int16_t* next_segment_ptr;
    size_t next_segment_bytes;
};

int8_t audio_init(void);
void audio_stop(void);
void audio_set_next_segment(int16_t* seg, uint32_t bytes);

#endif
