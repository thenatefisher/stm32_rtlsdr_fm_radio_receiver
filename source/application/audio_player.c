#include "audio_player.h"

static struct AudioPlayer self;

int8_t audio_init(void) {

    self.volume = 70;
    self.is_playing = 0;

    if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, self.volume, I2S_AUDIOFREQ_32K) == AUDIO_OK) {

        BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);

        DEBUG_PRINT("Audio init success\n");
        return 0;

    } else {

        DEBUG_PRINT("Audio init failure\n");
        return -1;

    }


}

void audio_stop(void) {

    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);

}

void audio_set_next_segment(int16_t* segment, uint32_t bytes) {

    self.next_segment_ptr = segment;
    self.next_segment_bytes = bytes;

    if (!self.is_playing) {
        self.is_playing = 1;
        BSP_AUDIO_OUT_Play(segment, bytes);
    }

}

/**
    @brief  Calculates the remaining file size and new position of the pointer.
    @param  None
    @retval None
*/
void BSP_AUDIO_OUT_TransferComplete_CallBack(void) {

    BSP_AUDIO_OUT_Play(self.next_segment_ptr, self.next_segment_bytes);

}

/**
    @brief  Manages the DMA Half Transfer complete interrupt.
    @param  None
    @retval None
*/
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void) {

}
