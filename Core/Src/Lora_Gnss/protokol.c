/*
 * protokol.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Muhammed
 */

#include"uart_dma.h"
#include"protokol.h"
#include"lora_gnss_main.h"



void veri_paketle( uint8_t *data, uint8_t uzunluk, veri_paketi_t *veri_pkt )
{
	static uint8_t durum_u8 = 0;
	uint32_t checksum_u32   = 0;

	for( int i = 0; i < DURUM_SAYISI; i++ )
	{
		switch( durum_u8 )
		{
			case LORA_KANAL_ATAMA:
			{
				veri_pkt->data[0] = 0x00;
				veri_pkt->data[1] = 0x01;
				veri_pkt->data[2] = 0x04;
				durum_u8 =  BASLANGIC_BAYT_1;
				break;
			}
			case BASLANGIC_BAYT_1:
			{
				veri_pkt->data[3] = 0x4D;
				durum_u8 =  BASLANGIC_BAYT_2;
				break;
			}
			case BASLANGIC_BAYT_2:
			{
				veri_pkt->data[4] = 0x26;
				durum_u8 =  UZUNLUK;
				break;
			}
			case UZUNLUK:
			{
				veri_pkt->data[5]        = uzunluk;
				veri_pkt->veri_boyutu_u8 = uzunluk;

				durum_u8 =  DATA_AL;
				break;
			}
			case DATA_AL:
			{
				for( int k=0; k < uzunluk; k++)
				{
					veri_pkt->data[k+6] = data[k];
				}

				durum_u8 =  CHECKSUM;
				break;
			}
			case CHECKSUM:
			{
				for( int j=0; j < uzunluk; j++)
				{
					checksum_u32 = data[j] + checksum_u32;
				}
				veri_pkt->checksum_u8 = checksum_u32 % 256;
				veri_pkt->data[veri_pkt->veri_boyutu_u8 +6]  = veri_pkt->checksum_u8;
				durum_u8 =  BASLANGIC_BAYT_1;
				break;
			}
		}
	}
}


uint8_t veri_paket_coz( uint8_t *gelen_veri, uint8_t uzunluk, veri_paketi_t *veri_pkt )
{
	static uint8_t durum_u8  = 0;
	static uint8_t indeks_u8 = 0;
	uint32_t hesaplanan_checksum_u32  = 0;
	uint32_t gelen_checksum_u32       = 0;
	uint8_t sonuc_u8                  = 0;

	for( int i = 0; i < uzunluk	; i++ )
	{
		switch( durum_u8 )
		{
			case BASLANGIC_BAYT_1:
			{
				if( gelen_veri[i] ==  0x4D )
				{
					durum_u8 =  BASLANGIC_BAYT_2;
				}

				break;
			}
			case BASLANGIC_BAYT_2:
			{
				if( gelen_veri[i] ==  0x26 )
				{
					durum_u8 =  UZUNLUK;
				}
				else //makina sifirlanir
				{
					durum_u8  = BASLANGIC_BAYT_1;
					return 0;
				}

				break;
			}
			case UZUNLUK:
			{
				veri_pkt->veri_boyutu_u8  = gelen_veri[i];

				if( veri_pkt->veri_boyutu_u8 > 0 )
				{
					durum_u8 =  DATA_AL;
				}
				else //makina sifirlanir
				{
					durum_u8  = BASLANGIC_BAYT_1;
					return 0;
				}
				break;
			}
			case DATA_AL:
			{
				veri_pkt->data[indeks_u8++] = gelen_veri[i];

				if( indeks_u8 == veri_pkt->veri_boyutu_u8 )
				{
					durum_u8 =  CHECKSUM;
				}

				break;
			}
			case CHECKSUM:
			{
				gelen_checksum_u32 = gelen_veri[i];

				// CheckSUM hesaplaniyor
				for( int j=0; j < veri_pkt->veri_boyutu_u8; j++)
				{
					hesaplanan_checksum_u32 = veri_pkt->data[j] + hesaplanan_checksum_u32;
				}

				veri_pkt->checksum_u8 = hesaplanan_checksum_u32 % 256;

				if( gelen_checksum_u32 == veri_pkt->checksum_u8 &&
					gelen_checksum_u32 != 0                       )
				{
					veri_pkt->yakalanan_paket_u32++;
					sonuc_u8 = 1;
				}
				else
				{
					veri_pkt->hatali_paket_u32++  ;
					sonuc_u8 = 0;
				}

				//makina sifirlanir
				durum_u8  =  BASLANGIC_BAYT_1;
				indeks_u8 = 0;

				break;
			}
		}
	}

	return sonuc_u8;
}


void haberlesme_cevrimi(Dma_t *pDma_st)
{
	uint8_t buffer[100] = {0};
	static uint16_t indeks_u16 = 0;


	while(pDma_st->okunanVeriSayisi_u16 > 0)
	{

		buffer[indeks_u16++] = RingBufferdanVeriOku(pDma_st);

		if(indeks_u16 == 100)
		{
			veri_paketle(buffer, indeks_u16, &Glo_st.veri_pkt_st);
			Glo_st.veri_pkt_st.paket_hazir_u8 = 1;
			indeks_u16 = 0;
		}

	}





}
