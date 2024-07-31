
#ifndef EVYEPA_RINGBUFFER_H_
#define EVYEPA_RINGBUFFER_H_
#include "stm32f1xx_hal.h"

#define RING_BUFFER_BOYUT 1024U

typedef struct
{
	uint8_t buffer_u8a[RING_BUFFER_BOYUT];
	uint16_t okumaPtr_u16;
	uint16_t yazmaPtr_u16;
	uint16_t kalan_u16;
}ringbuffer_t;


void ringbuffer_yaz(ringbuffer_t *pBuffer, uint8_t *pVeri, uint16_t boyut);
void ringbuffer_yazma_sayac_arttır(ringbuffer_t *pBuffer, uint16_t boyut);

void ringbuffer_oku_char(ringbuffer_t *pBuffer, char *pVeri, uint16_t boyut);
void ringbuffer_oku(ringbuffer_t *pBuffer, uint8_t *pVeri, uint16_t boyut);
void ringbuffer_okuma_sayac_arttır(ringbuffer_t *pBuffer, uint16_t boyut);



#endif /* EVYEPA_RINGBUFFER_H_ */
