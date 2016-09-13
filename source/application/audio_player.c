
/* Includes ------------------------------------------------------------------*/
#include "audio_player.h"


/**
    @brief  Initializes Audio Interface.
    @param  None
    @retval Audio error
*/
int8_t AUDIO_PLAYER_Init(void) {

    uwVolume = 70;
    playing = 0;

    if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, uwVolume, I2S_AUDIOFREQ_32K) == AUDIO_OK) {

        BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);

        printf("Audio init success\n");
        return 0;

    } else {

        printf("Audio init failure\n");
        return -1;

    }


}

/**
    @brief  Stops Audio streaming.
    @param  None
    @retval Audio error
*/
void AUDIO_PLAYER_Stop(void) {

    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);

}



void AUDIO_PLAYER_Play_Segment(volatile int16_t* seg, uint32_t s) {

    if (!playing) {
        playing = 1;
        next_seg = seg;
        next_seg_sz = s;
        BSP_AUDIO_OUT_Play(seg, s);
        return;
    }

    next_seg = seg;
    next_seg_sz = s;

}
/**
    @brief  Calculates the remaining file size and new position of the pointer.
    @param  None
    @retval None
*/
void BSP_AUDIO_OUT_TransferComplete_CallBack(void) {

    BSP_AUDIO_OUT_Play(next_seg, next_seg_sz);

}

/**
    @brief  Manages the DMA Half Transfer complete interrupt.
    @param  None
    @retval None
*/
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void) {

}
