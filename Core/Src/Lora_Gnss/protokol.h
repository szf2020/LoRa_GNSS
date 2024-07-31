/*
 * protokol.h
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#ifndef SRC_LORA_GNSS_PROTOKOL_H_
#define SRC_LORA_GNSS_PROTOKOL_H_



#define LORA_E22_MAKS_BOYUT		240U
#define PROTOKOL_FAZLALIK		4U
#define LORA_E22_FAZLALIK		3U


typedef struct
{
	uint8_t  veri_turu_u8;
	uint8_t  veri_boyutu_u8;
	uint8_t  data[LORA_E22_MAKS_BOYUT];
	uint32_t yakalanan_paket_u32;
	uint8_t  checksum_u8;
	uint32_t hatali_paket_u32;
	uint8_t  paket_hazir_u8;
}veri_paketi_t;


typedef enum
{
	LORA_KANAL_ATAMA,
	BASLANGIC_BAYT_1,
	BASLANGIC_BAYT_2,
	UZUNLUK,
	DATA_AL,
	CHECKSUM,
	DURUM_SAYISI
}paket_isimleri;


void veri_paketle( uint8_t *data, uint8_t uzunluk, veri_paketi_t *veri_pkt );

uint8_t veri_paket_coz( uint8_t *gelen_veri, uint8_t uzunluk, veri_paketi_t *veri_pkt );

void haberlesme_cevrimi(Dma_t *pDma_st);

#endif /* SRC_LORA_GNSS_PROTOKOL_H_ */
