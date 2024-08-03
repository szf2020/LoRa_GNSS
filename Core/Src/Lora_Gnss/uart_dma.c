/*
 * uart_dma.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Muhammed
 */


#include "uart_dma.h"
#include "lora_gnss_main.h"
#include <string.h>
#include "main.h"




void UartDmaInit(UART_HandleTypeDef *pUart, DMA_HandleTypeDef *pDmaUartRx, Dma_t *pDma_st)
{
    pDma_st->pUart = pUart;
    pDma_st->pDmaUartRx = pDmaUartRx;

    HAL_UART_Transmit_DMA(pUart, pDma_st->txBuffer_u8a, TX_BUFFER_BOYUT);

    HAL_UARTEx_ReceiveToIdle_DMA(pUart, pDma_st->rxBuffer_u8a, RX_BUFFER_BOYUT);
    __HAL_DMA_DISABLE_IT(pDmaUartRx, DMA_IT_HT);
}


uint8_t RingBufferdanVeriOku(Dma_t *pDma_st)
{
    uint8_t veri = 0;

    // Eğer okunan veri sayısı sıfırdan büyükse işlem yap
    if (pDma_st->okunanVeriSayisi_u16 > 0)
    {
        // Ring buffer'dan bir bayt veri oku
        veri = pDma_st->ringBuffer_u8a[pDma_st->eskiPoz_u16];

        // Eski pozisyonu güncelle ve wrap-around kontrolü yap
        pDma_st->eskiPoz_u16 = (pDma_st->eskiPoz_u16 + 1) % RING_BUFFER_BOYUT;

        // Okunan veri sayısını bir azalt
        pDma_st->okunanVeriSayisi_u16--;
    }
    return veri;
}


void RingBufferYaz(Dma_t *pDma_st, uint16_t boyut_u16)
{
    uint16_t eskiPozTemp = pDma_st->yeniPoz_u16; // Mevcut pozisyonu geçici bir değişkene kaydet

    if((eskiPozTemp + boyut_u16) > RING_BUFFER_BOYUT)
    {
        uint16_t kalan_u16 = RING_BUFFER_BOYUT - eskiPozTemp;
        memcpy((uint8_t *)pDma_st->ringBuffer_u8a + eskiPozTemp, pDma_st->rxBuffer_u8a, kalan_u16);

        eskiPozTemp = 0;
        memcpy((uint8_t *)pDma_st->ringBuffer_u8a, (uint8_t *)pDma_st->rxBuffer_u8a + kalan_u16, (boyut_u16 - kalan_u16));
        pDma_st->yeniPoz_u16 = (boyut_u16 - kalan_u16);
    }
    else
    {
        memcpy((uint8_t *)pDma_st->ringBuffer_u8a + eskiPozTemp, pDma_st->rxBuffer_u8a, boyut_u16);
        pDma_st->yeniPoz_u16 = (eskiPozTemp + boyut_u16) % RING_BUFFER_BOYUT;
    }

    pDma_st->okunanVeriSayisi_u16 += boyut_u16;
}


void DmaVeriGonder(Dma_t *pDma_st, uint8_t *pBuffer, uint16_t boyut_u16)
{
	if(pDma_st->txCallBackFlag_u8)
	{
		HAL_UART_Transmit_DMA(pDma_st->pUart, pBuffer, boyut_u16);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		pDma_st->txCallBackFlag_u8 = 0;
	}
}


void DmaRxKesme(Dma_t *pDma_st, uint16_t boyut_u16)
{
    // Ring buffer'a veri yaz
    RingBufferYaz(pDma_st, boyut_u16);


    // UART DMA alımını yeniden başlat
    if (HAL_UARTEx_ReceiveToIdle_DMA(pDma_st->pUart, pDma_st->rxBuffer_u8a, RX_BUFFER_BOYUT) != HAL_OK)
    {

    }

    // Half Transfer Interrupt'ı devre dışı bırak
    __HAL_DMA_DISABLE_IT(pDma_st->pDmaUartRx, DMA_IT_HT);
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART1)
	{
		DmaRxKesme(&Glo_st.usartDma1_st, Size);
	}
	if (huart->Instance == USART2)
	{
		DmaRxKesme(&Glo_st.usartDma2_st, Size);
	}
	if (huart->Instance == USART3)
	{
		DmaRxKesme(&Glo_st.usartDma3_st, Size);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		Glo_st.usartDma1_st.txCallBackFlag_u8 = 1;
	}
	if (huart->Instance == USART2)
	{
		Glo_st.usartDma2_st.txCallBackFlag_u8 = 1;
	}
	if (huart->Instance == USART3)
	{
		Glo_st.usartDma3_st.txCallBackFlag_u8 = 1;
	}

}















