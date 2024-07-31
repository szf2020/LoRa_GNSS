/*
 * rtcm_decoder.h
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#ifndef SRC_LORA_GNSS_RTCM_DECODER_H_
#define SRC_LORA_GNSS_RTCM_DECODER_H_

#include "stdint.h"

typedef enum {
    STATE_PREAMBLE,
    STATE_LENGTH,
    STATE_MESSAGE,
    STATE_CRC
} rtcm_state_t;


uint32_t compute_crc24q(const uint8_t *buffer, int length);

void parse_rtcm_v3_message(uint8_t *data, int data_length);


#endif /* SRC_LORA_GNSS_RTCM_DECODER_H_ */
