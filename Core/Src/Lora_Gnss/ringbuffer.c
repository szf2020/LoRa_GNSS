#include "ringbuffer.h"

void ringbuffer_yaz(ringbuffer_t *pBuffer, uint8_t *pVeri, uint16_t boyut)
{
	uint16_t tSayac_u16 = 0;

	if(boyut >= RING_BUFFER_BOYUT)
	{
		boyut = RING_BUFFER_BOYUT;
	}

	for(tSayac_u16 = 0; tSayac_u16 < boyut; tSayac_u16++)
	{
		if(pBuffer->yazmaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->yazmaPtr_u16 %= RING_BUFFER_BOYUT;
		}
		pBuffer->buffer_u8a[pBuffer->yazmaPtr_u16++] = pVeri[tSayac_u16];
		pBuffer->kalan_u16++;

		if(pBuffer->yazmaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->yazmaPtr_u16 %= RING_BUFFER_BOYUT;
		}
		if(pBuffer->kalan_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->kalan_u16 %= RING_BUFFER_BOYUT;
		}
	}
}

void ringbuffer_yazma_sayac_arttır(ringbuffer_t *pBuffer, uint16_t boyut)
{
	uint16_t tSayac_u16 = 0;

	if(boyut >= RING_BUFFER_BOYUT)
	{
		boyut = RING_BUFFER_BOYUT;
	}

	pBuffer->kalan_u16 += boyut;
	pBuffer->yazmaPtr_u16 += boyut;
	if(pBuffer->yazmaPtr_u16 >= RING_BUFFER_BOYUT)
	{
		pBuffer->yazmaPtr_u16 %= RING_BUFFER_BOYUT;
	}
	if(pBuffer->kalan_u16 >= RING_BUFFER_BOYUT)
	{
		pBuffer->kalan_u16 %= RING_BUFFER_BOYUT;
	}
}


void ringbuffer_oku_char(ringbuffer_t *pBuffer, char *pVeri, uint16_t boyut)
{
	uint16_t tSayac_u16 = 0;

	if(boyut >= RING_BUFFER_BOYUT)
	{
		boyut = RING_BUFFER_BOYUT;
	}

	for(tSayac_u16 = 0; tSayac_u16 < boyut; tSayac_u16++)
	{
		if(pBuffer->okumaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->okumaPtr_u16 %= RING_BUFFER_BOYUT;
		}
		pVeri[tSayac_u16] = pBuffer->buffer_u8a[pBuffer->okumaPtr_u16++];
		if(pBuffer->kalan_u16 > 0)
		{
			pBuffer->kalan_u16--;
		}

		if(pBuffer->okumaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->okumaPtr_u16 %= RING_BUFFER_BOYUT;
		}
	}
}


void ringbuffer_oku(ringbuffer_t *pBuffer, uint8_t *pVeri, uint16_t boyut)
{
	uint16_t tSayac_u16 = 0;

	if(boyut >= RING_BUFFER_BOYUT)
	{
		boyut = RING_BUFFER_BOYUT;
	}

	for(tSayac_u16 = 0; tSayac_u16 < boyut; tSayac_u16++)
	{
		if(pBuffer->okumaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->okumaPtr_u16 %= RING_BUFFER_BOYUT;
		}
		pVeri[tSayac_u16] = pBuffer->buffer_u8a[pBuffer->okumaPtr_u16++];
		if(pBuffer->kalan_u16 > 0)
		{
			pBuffer->kalan_u16--;
		}

		if(pBuffer->okumaPtr_u16 >= RING_BUFFER_BOYUT)
		{
			pBuffer->okumaPtr_u16 %= RING_BUFFER_BOYUT;
		}
	}
}

void ringbuffer_okuma_sayac_arttır(ringbuffer_t *pBuffer, uint16_t boyut)
{
	uint16_t tSayac_u16 = 0;

	if(boyut >= RING_BUFFER_BOYUT)
	{
		boyut = RING_BUFFER_BOYUT;
	}

	pBuffer->kalan_u16 -= boyut;
	pBuffer->okumaPtr_u16 += boyut;
	if(pBuffer->okumaPtr_u16 >= RING_BUFFER_BOYUT)
	{
		pBuffer->okumaPtr_u16 %= RING_BUFFER_BOYUT;
	}
	if(pBuffer->kalan_u16 >= RING_BUFFER_BOYUT)
	{
		pBuffer->kalan_u16 %= RING_BUFFER_BOYUT;
	}
}
