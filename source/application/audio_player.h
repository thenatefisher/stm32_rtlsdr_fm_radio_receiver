#ifndef __AUDIO_PLAYER_H
#define __AUDIO_PLAYER_H

#include "stm32746g_discovery_audio.h"
#include "stdio.h"
#include "trace.h"

static volatile uint32_t uwVolume;
uint16_t* next_seg;
uint32_t next_seg_sz;
uint8_t playing;

int8_t AUDIO_PLAYER_Init(void);
void AUDIO_PLAYER_Stop(void);
void AUDIO_PLAYER_Play_Segment(volatile int16_t* seg, uint32_t bytes);

#endif 
