#include "fm_radio.h"


int fmradio_init() {

    dev = &static_dev;
    usb_app_started = 1;
    curr_demod_buff = demod_bufferA;
    raw_buf_filling = raw_bufA;
    gain = 0;
    ppm_error = 0;
    frequency = 99700000;
    samp_rate = RTL_SAMPLERATE;
    raw_buf_remain_bytes = RAW_BUFFER_BYTES;
    raw_buf_complete = 0;

    int8_t dongle_open = rtlsdr_open(&dev, 0);

    if (dongle_open < 0) {
        DEBUG_PRINT("Failed to open rtlsdr device (%i).\n", dongle_open);
        return dongle_open;
    } else {
        DEBUG_PRINT("Opened rtlsdr\n");
    }

    // Set the sample rate
    verbose_set_sample_rate(dev, samp_rate);

    // Set the frequency
    verbose_set_frequency(dev, frequency);

    if (0 == gain) {
        // Enable automatic gain
        verbose_auto_gain(dev);

    } else {
        // Enable manual gain
        gain = nearest_gain(dev, gain);
        verbose_gain_set(dev, gain);
    }

    // set ppm error
    verbose_ppm_set(dev, ppm_error);

    // Reset endpoint before we start reading from it (mandatory)
    verbose_reset_buffer(dev);

    DEBUG_PRINT("Starting user app\n");

    // begin capture radio data
    rtlsdr_read_sync(dev, raw_buf_filling, USBH_MAX_DATA_BUFFER, 0);

    return 0;

}

void fmradio_process() {

    // run init
    if (!usb_app_started) fmradio_init();

    // wait for raw buffer to fill completely
    if (!raw_buf_complete) return;

    raw_buf_complete = 0;

    itm_print(3,0);

    // demodulate the completed raw buffer
    uint32_t demod_index = 0;
    volatile uint8_t* raw_buf_complete = (raw_buf_filling == raw_bufA) ? raw_bufB : raw_bufA;

    for (uint32_t sample_index = 0;
            (sample_index + (2 * DOWNSAMPLE) + 3) < RAW_BUFFER_BYTES;
            sample_index += 2 * DOWNSAMPLE) {

        // todo reconsider -127 offset as samples are actually only 7-bit reso
        int16_t s1[2], s2[2];
        s1[0] = (int16_t)raw_buf_complete[sample_index + 0] - 127; // I
        s1[1] = (int16_t)raw_buf_complete[sample_index + 1] - 127; // Q
        s2[0] = (int16_t)raw_buf_complete[sample_index + 2] - 127; // I
        s2[1] = (int16_t)raw_buf_complete[sample_index + 3] - 127; // Q

        int16_t pcm = polar_disc_fast(s2[0], s2[1],
                                      s1[0], s1[1]);
        pcm = pcm * 8.0f / PI;

        curr_demod_buff[demod_index++] = pcm;
        curr_demod_buff[demod_index++] = pcm;

    }

    // play demodulated buffer
    AUDIO_PLAYER_Play_Segment(curr_demod_buff, 2*demod_index);

    // swap demod buffers
    curr_demod_buff = (curr_demod_buff == demod_bufferA) ? demod_bufferB : demod_bufferA;

}

void HAL_HCD_HC_NotifyURBChange_Callback(
    HCD_HandleTypeDef* hhcd,
    uint8_t chnum,
    HCD_URBStateTypeDef urb_state) {

    UNUSED(hhcd);
    UNUSED(chnum);

    if (!usb_app_started) { return; }

    if (urb_state == URB_DONE) {

        // decrement bytes remaining
        raw_buf_remain_bytes -= USBH_MAX_DATA_BUFFER;

        // switch buffers?
        if (raw_buf_remain_bytes == 0) {

            // reset remaining bytes count
            raw_buf_remain_bytes = RAW_BUFFER_BYTES;

            // swap double buffer pointer
            raw_buf_filling = (raw_buf_filling == raw_bufA) ? raw_bufB : raw_bufA;

            // signal buffer is ready for demod
            raw_buf_complete = 1;

        }

        // start another transaction
        uint32_t buf_offset = RAW_BUFFER_BYTES - raw_buf_remain_bytes;
        rtlsdr_read_sync(dev,
                         (void*)(raw_buf_filling + buf_offset),
                         USBH_MAX_DATA_BUFFER,
                         0);

    }

}
