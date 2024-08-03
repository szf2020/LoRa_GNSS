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
void parse_rtcm_v3_message(uint8_t *data, int data_length, Rtcm_t *pRtcm_st)
{
    static rtcm_state_t state = STATE_PREAMBLE;
    static uint16_t length = 0;
    static uint16_t index = 0;
    static uint8_t message[1024];
    uint32_t crc = 0;

    for (int i = 0; i < data_length; i++)
    {
        uint8_t byte = data[i];

		switch (state) {
			case STATE_PREAMBLE:
			{
				if (byte == 0xD3) {
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
				if (index == 1) {
					length = (byte & 0x03) << 8; // İlk byte'ı uzunluğun yüksek 8 bitine yerleştir
				} else if (index == 2) {
					length |= byte; // İkinci byte'ı uzunluğun düşük 8 bitine yerleştir
				}
				message[index++] = byte;
				if (index == 3) {
					state = STATE_MESSAGE;
				}
				break;
			}

			case STATE_MESSAGE:
			{
				message[index++] = byte;
				if (index == (3 + length)) {  // 3 bytes header + message length
					state = STATE_CRC;
				}
				break;
			}

			case STATE_CRC:
			{
				message[index++] = byte;
				if ((index) == (3 + length + 3))
				{  // 3 bytes header + message length + 3 bytes CRC
					crc = (message[index-3] << 16) | (message[index-2] << 8) | message[index-1];
					uint32_t computed_crc = compute_crc24q(message, 3 + length);

					if (crc == computed_crc)
					{
//						memcpy(pRtcm_st->rtcm_buffer, message, index);

						DmaVeriGonder(&Glo_st.usartDma2_st, message, index);

						pRtcm_st->veri_boyutu_u16 = index;
						pRtcm_st->basarili_mesaj_u32++;
						pRtcm_st->rtcm_mesaj_geldi_u8 = 1;
					}
					else
					{
						pRtcm_st->rtcm_mesaj_geldi_u8 = 0;
						pRtcm_st->crc_hatali_mesaj_u32++;
					}

					state = STATE_PREAMBLE;
					length = 0;
					index = 0;
				}
				break;
			}
		}
    }
}


void parse_rtcm_v3_message_while(Dma_t *pDma_st, Rtcm_t *pRtcm_st)
{
    static rtcm_state_t state = STATE_PREAMBLE;
    static uint16_t length = 0;
    static uint16_t index = 0;
    static uint8_t message[1024];
    uint32_t crc = 0;

	while(pDma_st->okunanVeriSayisi_u16 > 0)
	{
		uint8_t byte = RingBufferdanVeriOku(pDma_st);

        switch (state) {
            case STATE_PREAMBLE:
            {
                if (byte == 0xD3) {
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
                if (index == 1) {
                    length = (byte & 0x03) << 8; // İlk byte'ı uzunluğun yüksek 8 bitine yerleştir
                } else if (index == 2) {
                    length |= byte; // İkinci byte'ı uzunluğun düşük 8 bitine yerleştir
                }
                message[index++] = byte;
                if (index == 3) {
                    state = STATE_MESSAGE;
                }
                break;
            }

            case STATE_MESSAGE:
            {
                message[index++] = byte;
                if (index == (3 + length)) {  // 3 bytes header + message length
                    state = STATE_CRC;
                }
                break;
            }

            case STATE_CRC:
            {
                message[index++] = byte;
                if ((index) == (3 + length + 3))
                {  // 3 bytes header + message length + 3 bytes CRC
                    crc = (message[index-3] << 16) | (message[index-2] << 8) | message[index-1];
                    uint32_t computed_crc = compute_crc24q(message, 3 + length);

                    if (crc == computed_crc)
                    {
//                        memcpy(pRtcm_st->rtcm_buffer, message, index);
                        pRtcm_st->veri_boyutu_u16 = index;
                        pRtcm_st->basarili_mesaj_u32++;
                        pRtcm_st->rtcm_mesaj_geldi_u8 = 1;
                    }
                    else
                    {
                    	pRtcm_st->rtcm_mesaj_geldi_u8 = 0;
                    	pRtcm_st->crc_hatali_mesaj_u32++;
                    }

                    state = STATE_PREAMBLE;
                    length = 0;
                    index = 0;
                }
                break;
            }
        }
    }
}
