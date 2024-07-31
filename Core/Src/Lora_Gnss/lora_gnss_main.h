/*
 * lora_gnss_main.h
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#ifndef SRC_LORA_GNSS_LORA_GNSS_MAIN_H_
#define SRC_LORA_GNSS_LORA_GNSS_MAIN_H_


#include "stdint.h"
#include "uart_dma.h"
#include "protokol.h"
#include "rtcm_decoder.h"



typedef struct
{
	uint32_t sayac_u32;
	uint8_t _1HzFlag_u8;
	uint8_t _2HzFlag_u8;
	uint8_t _5HzFlag_u8;
	uint8_t _10HzFlag_u8;
	uint8_t _20HzFlag_u8;
	uint8_t _50HzFlag_u8;
	uint8_t _100HzFlag_u8;
	uint8_t _200HzFlag_u8;

	Dma_t usartDma1_st;
	Dma_t usartDma2_st;
	Dma_t usartDma3_st;

	veri_paketi_t veri_pkt_st;
	Rtcm_t rtcm_st;

}Global_t;

extern Global_t Glo_st;

void loraGnssMain();

#endif /* SRC_LORA_GNSS_LORA_GNSS_MAIN_H_ */
