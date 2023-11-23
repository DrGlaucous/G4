/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_check.h"
#include "dshot_esc_encoder.h"

static const char *TAG = "dshot_encoder";

/**
 * @brief Type of Dshot ESC frame
 */
typedef union {
    struct {
        uint16_t crc: 4;       /*!< CRC checksum */
        uint16_t telemetry: 1; /*!< Telemetry request */
        uint16_t throttle: 11; /*!< Throttle value */
    };
    uint16_t val;
} dshot_esc_frame_t;

#ifndef __cplusplus
_Static_assert(sizeof(dshot_esc_frame_t) == 0x02, "Invalid size of dshot_esc_frame_t structure");
#endif

typedef struct {
    rmt_encoder_t base;
    rmt_encoder_t *bytes_encoder;
    rmt_encoder_t *copy_encoder;
    rmt_symbol_word_t dshot_delay_symbol; //raw incoder data, 32 bits, first 16 are for state 0, second are for state 1. (15 bits for duration, 1 for hi/lo)
    int state;
} rmt_dshot_esc_encoder_t;

static void make_dshot_frame(dshot_esc_frame_t *frame, uint16_t throttle, bool telemetry)
{
    frame->throttle = throttle;
    frame->telemetry = telemetry;
    uint16_t val = frame->val;
    uint8_t crc = ((val ^ (val >> 4) ^ (val >> 8)) & 0xF0) >> 4;;
    frame->crc = crc;
    val = frame->val;
    // change the endian
    frame->val = ((val & 0xFF) << 8) | ((val & 0xFF00) >> 8);
}

//the function that is run during the actual encode process
static size_t rmt_encode_dshot_esc(rmt_encoder_t *encoder, rmt_channel_handle_t channel,
                                   const void *primary_data, size_t data_size, rmt_encode_state_t *ret_state)
{
    //makes a rmt_dshot_esc_encoder_t object where the variable "base" is the same as "encoder" (?)
    rmt_dshot_esc_encoder_t *dshot_encoder = __containerof(encoder, rmt_dshot_esc_encoder_t, base);

    //rmt_encoder_t is the same type...
    //split these out so it is easer to type with them
    rmt_encoder_handle_t bytes_encoder = dshot_encoder->bytes_encoder;
    rmt_encoder_handle_t copy_encoder = dshot_encoder->copy_encoder;


    //these are supposed to persist... they're not static?
    int session_state = RMT_ENCODING_RESET; //gets the state of each mini-encoder, is used to evaluate the greater states
    int state = RMT_ENCODING_RESET; //rmt_encode_state_t, this is the state of the function that is returned through ret_state
    size_t encoded_symbols = 0;

    // convert user data into dshot frame
    //the primary data can be anything (void pointer), so we tell the program that it is actually a throttle object when we go to use it
    dshot_esc_throttle_t *throttle = (dshot_esc_throttle_t *)primary_data;

    //this is the "frame" (get it?) where the converted data goes just before being pushed over RMT. it is a uint16
    dshot_esc_frame_t frame = {};
    make_dshot_frame(&frame, throttle->throttle, throttle->telemetry_req); //makes the frame using the throttle data


    //copy the frame to the RMT depending on what state the encoder is in
    switch (dshot_encoder->state)
    {
    case 0: // send the dshot frame

        //not sure why it needs the channel... I guess it's because it needs to know if the buffer is full
        //arguments: (this, parent channel, *data, sizeof(data), *session state out)
        //encoded_symbols is an unsigned int
        encoded_symbols += bytes_encoder->encode(bytes_encoder, channel, &frame, sizeof(frame), (rmt_encode_state_t*)&session_state);
        
        //evaluate next action based on the result of the bytes_encoder
        if (session_state & RMT_ENCODING_COMPLETE) {
            dshot_encoder->state = 1; // switch to next state when current encoding session finished
        }

        //memory full, application does not advance to next state, returns FULL
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out; // yield if there's no free space for encoding artifacts
        }
    // fall-through
    case 1: //append the delay at the end of the frame

        //copy the delay frame (raw frame)
        encoded_symbols += copy_encoder->encode(copy_encoder, channel, &dshot_encoder->dshot_delay_symbol,
                                                sizeof(rmt_symbol_word_t), (rmt_encode_state_t*)&session_state);

        //return state finished, reset action state to case 0
        if (session_state & RMT_ENCODING_COMPLETE) {
            state |= RMT_ENCODING_COMPLETE;
            dshot_encoder->state = RMT_ENCODING_RESET; // switch to next state when current encoding session finished
        }
        //do not reset action state
        if (session_state & RMT_ENCODING_MEM_FULL) {
            state |= RMT_ENCODING_MEM_FULL;
            goto out; // yield if there's no free space for encoding artifacts
        }
    }
out:
    //return the current state and the encoded symbols
    *ret_state = (rmt_encode_state_t)state;
    return encoded_symbols;
}

static esp_err_t rmt_del_dshot_encoder(rmt_encoder_t *encoder)
{
    rmt_dshot_esc_encoder_t *dshot_encoder = __containerof(encoder, rmt_dshot_esc_encoder_t, base);
    rmt_del_encoder(dshot_encoder->bytes_encoder);
    rmt_del_encoder(dshot_encoder->copy_encoder);
    free(dshot_encoder);
    return ESP_OK;
}

static esp_err_t rmt_dshot_encoder_reset(rmt_encoder_t *encoder)
{
    rmt_dshot_esc_encoder_t *dshot_encoder = __containerof(encoder, rmt_dshot_esc_encoder_t, base);
    rmt_encoder_reset(dshot_encoder->bytes_encoder);
    rmt_encoder_reset(dshot_encoder->copy_encoder);
    dshot_encoder->state = RMT_ENCODING_RESET;
    return ESP_OK;
}


esp_err_t rmt_new_dshot_esc_encoder(const dshot_esc_encoder_config_t *config, rmt_encoder_handle_t *ret_encoder)
{
    esp_err_t ret = ESP_OK;
    rmt_dshot_esc_encoder_t *dshot_encoder = NULL;
    ESP_GOTO_ON_FALSE((rmt_dshot_esc_encoder_t*)config && ret_encoder, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    dshot_encoder = (rmt_dshot_esc_encoder_t*)calloc(1, sizeof(rmt_dshot_esc_encoder_t));
    ESP_GOTO_ON_FALSE(dshot_encoder, ESP_ERR_NO_MEM, err, TAG, "no mem for musical score encoder");
    {
        dshot_encoder->base.encode = rmt_encode_dshot_esc;
        dshot_encoder->base.del = rmt_del_dshot_encoder;
        dshot_encoder->base.reset = rmt_dshot_encoder_reset;
        uint32_t delay_ticks = config->resolution / 1e6 * config->post_delay_us;
        rmt_symbol_word_t dshot_delay_symbol =
        {
            delay_ticks / 2,
            0,
            delay_ticks / 2,
            0
        };

        dshot_encoder->dshot_delay_symbol = dshot_delay_symbol;
        // different dshot protocol have its own timing requirements,
        float period_ticks = (float)config->resolution / config->baud_rate;
        // 1 and 0 is represented by a 74.850% and 37.425% duty cycle respectively
        unsigned int t1h_ticks = (unsigned int)(period_ticks * 0.7485);
        unsigned int t1l_ticks = (unsigned int)(period_ticks - t1h_ticks);
        unsigned int t0h_ticks = (unsigned int)(period_ticks * 0.37425);
        unsigned int t0l_ticks = (unsigned int)(period_ticks - t0h_ticks);
        rmt_bytes_encoder_config_t bytes_encoder_config[2] = {};
        //c++ doesn't like those inline initializations, so we assign each one directly like this
        {
            bytes_encoder_config[0].bit0.duration0 = t0h_ticks;
            bytes_encoder_config[0].bit0.level0 = 1;
            bytes_encoder_config[0].bit0.duration1 = t0l_ticks;
            bytes_encoder_config[0].bit0.level1 = 0;

            bytes_encoder_config[0].bit0.duration0 = t0h_ticks;
            bytes_encoder_config[0].bit0.level0 = 1;
            bytes_encoder_config[0].bit0.duration1 = t0l_ticks;
            bytes_encoder_config[0].bit0.level1 = 0;
        }

        //  = {
        //     .bit0 = {
        //         .duration0 = t0h_ticks,
        //         .level0 = 1,
        //         .duration1 = t0l_ticks,
        //         .level1 = 0,
        //     },
        //     .bit1 = {
        //         .duration0 = t1h_ticks,
        //         .level0 = 1,
        //         .duration1 = t1l_ticks,
        //         .level1 = 0,
        //     },
        //     .flags.msb_first = 1,
        // };

        ESP_GOTO_ON_ERROR(rmt_new_bytes_encoder(&bytes_encoder_config[0], &dshot_encoder->bytes_encoder), err, TAG, "create bytes encoder failed");
        rmt_copy_encoder_config_t copy_encoder_config = {};
        ESP_GOTO_ON_ERROR(rmt_new_copy_encoder(&copy_encoder_config, &dshot_encoder->copy_encoder), err, TAG, "create copy encoder failed");
        *ret_encoder = &dshot_encoder->base;
        return ESP_OK;
    }

err:
    if (dshot_encoder) {
        if (dshot_encoder->bytes_encoder) {
            rmt_del_encoder(dshot_encoder->bytes_encoder);
        }
        if (dshot_encoder->copy_encoder) {
            rmt_del_encoder(dshot_encoder->copy_encoder);
        }
        free(dshot_encoder);
    }
    return ret;
}
