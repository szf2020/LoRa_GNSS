/*
 * uart_dma.h
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#ifndef SRC_LORA_GNSS_UART_DMA_H_
#define SRC_LORA_GNSS_UART_DMA_H_

#include "stdint.h"
#include "stm32f1xx_hal.h"


#define RING_BUFFER_BOYUT   2048U
#define RX_BUFFER_BOYUT     2048U
#define TX_BUFFER_BOYUT     1024U


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;


typedef struct
{
    UART_HandleTypeDef *pUart;
    DMA_HandleTypeDef *pDmaUartRx;
    uint8_t txBuffer_u8a[TX_BUFFER_BOYUT];
    uint8_t rxBuffer_u8a[RX_BUFFER_BOYUT];
    uint8_t ringBuffer_u8a[RING_BUFFER_BOYUT];
    uint16_t yeniPoz_u16;
    uint16_t eskiPoz_u16;
    uint16_t okunanVeriSayisi_u16;
    uint8_t txCallBackFlag_u8;

}Dma_t;


void UartDmaInit(UART_HandleTypeDef *pUart, DMA_HandleTypeDef *pDmaUartRx, Dma_t *pDma_st);

uint8_t RingBufferdanVeriOku(Dma_t *pDma_st);

void RingBufferYaz(Dma_t *pDma_st, uint16_t boyut_u16);

void DmaVeriGonder(Dma_t *pDma_st, uint8_t *pBuffer, uint16_t boyut_u16);

void DmaRxKesme(Dma_t *pDma_st, uint16_t boyut_u16);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);


#endif /* SRC_LORA_GNSS_UART_DMA_H_ */
