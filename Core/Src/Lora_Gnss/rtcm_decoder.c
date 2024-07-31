/*
 * rtcm_decoder.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */


// RTCM v3 State Machine States

#include "rtcm_decoder.h"
#include "lora_gnss_main.h"
#include <string.h>


// Function to compute the CRC-24Q (used in RTCM v3)
uint32_t compute_crc24q(const uint8_t *buffer, int length)
{
    uint32_t crc = 0;
    int i;

    while (length--) {
        crc ^= (*buffer++) << 16;
        for (i = 0; i < 8; i++) {
            crc <<= 1;
            if (crc & 0x1000000) {
                crc ^= 0x1864CFB;
            }
        }
    }
    return crc & 0xFFFFFF;
}


// RTCM v3 Message Parser State Machine
void parse_rtcm_v3_message(uint8_t *data, int data_length)
{
    static rtcm_state_t state = STATE_PREAMBLE;
    static uint16_t length = 0;
    static uint16_t index = 0;
    static uint8_t message[1024];
    static uint32_t crc = 0;

    for (int i = 0; i < data_length; i++) {
        uint8_t byte = data[i];

        switch (state)
        {
            case STATE_PREAMBLE:
            {
                if (byte == 0xD3)
                {
                    state = STATE_LENGTH;
                    length = 0;
                    index = 0;
                    crc = 0;
                    message[index++] = byte;
                }
                break;
            }

            case STATE_LENGTH:
            {
                length = (length << 8) | (byte & 0x03);
                message[index++] = byte;
                if (index == 3)
                {
                    state = STATE_MESSAGE;
                }
                break;
            }

            case STATE_MESSAGE:
            {
                message[index++] = byte;
                if (index == (3 + length + 3))
                {  // 3 bytes header + message length + 3 bytes CRC
                    state = STATE_CRC;
                }
                break;
            }

            case STATE_CRC:
            {
                message[index++] = byte;
                if (index == (3 + length + 3 + 3))
                {  // 3 bytes header + message length + 3 bytes CRC
                    crc = (message[index-3] << 16) | (message[index-2] << 8) | message[index-1];
                    uint32_t computed_crc = compute_crc24q(message, 3 + length);

                    if (crc == computed_crc)
                    {

                        memcpy(Glo_st.rtcm_st.rtcm_buffer, message, index);
                        Glo_st.rtcm_st.rtcm_mesaj_geldi_u8 = 1;
                    }
                    else
                    {
                    	Glo_st.rtcm_st.rtcm_mesaj_geldi_u8 = 0;
                    }
                    state = STATE_PREAMBLE;
                }
                break;
            }
        }
    }
}
