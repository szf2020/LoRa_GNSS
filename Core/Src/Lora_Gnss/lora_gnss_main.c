/*
 * lora_gnss_main.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#include "lora_gnss_main.h"
#include "protokol.h"
#include "main.h"

Global_t Glo_st = {0};

void loraGnssMain()
{
//		UartDmaInit(&huart1, &hdma_usart1_rx, &Glo_st.usartDma1_st);
		UartDmaInit(&huart2, &hdma_usart2_rx, &Glo_st.usartDma2_st);
		UartDmaInit(&huart3, &hdma_usart3_rx, &Glo_st.usartDma3_st);

		Glo_st.lora_st.adres_u8 = 0x02;
		Glo_st.lora_st.kanal_u8 = 0x05;

	while(1)
	{
		if(1 == Glo_st._50HzFlag_u8)
		{
//			Lora_veri_gonderme_cevrimi(&Glo_st.usartDma2_st, &Glo_st.veri_pkt_st, &Glo_st.lora_st);
			Lora_veri_alma_cevrimi(&Glo_st.usartDma3_st, &Glo_st.veri_pkt_st);

			Glo_st._50HzFlag_u8 = 0;
		}

	}
}
