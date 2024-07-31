/*
 * lora_gnss_main.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#include "lora_gnss_main.h"
#include "protokol.h"

Global_t Glo_st = {0};

void loraGnssMain()
{
//		UartDmaInit(&huart1, &hdma_usart1_rx, &Glo_st.usartDma1_st);
//		UartDmaInit(&huart2, &hdma_usart2_rx, &Glo_st.usartDma2_st);
		UartDmaInit(&huart3, &hdma_usart3_rx, &Glo_st.usartDma3_st);

	while(1)
	{
		if(1 == Glo_st._100HzFlag_u8)
		{
//			Lora_veri_gonderme_cevrimi(&Glo_st.usartDma3_st, &Glo_st.veri_pkt_st);
			Lora_veri_alma_cevrimi(&Glo_st.usartDma3_st, &Glo_st.veri_pkt_st);

			if(Glo_st.veri_pkt_st.paket_hazir_u8)
			{
				if(Glo_st.usartDma3_st.txCallBackFlag_u8)
				{
					HAL_UART_Transmit_DMA(&huart3, Glo_st.veri_pkt_st.data, Glo_st.usartDma3_st.gonderilecekVeriSayisi_u16);
					Glo_st.veri_pkt_st.paket_hazir_u8 = 0;
					Glo_st.usartDma3_st.txCallBackFlag_u8 = 0;
				}
			}

			Glo_st._100HzFlag_u8 = 0;
		}

	}
}
