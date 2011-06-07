#ifndef _ARMY_PIO_H
#define _ARMY_PIO_H

#include <army/types.h>

typedef struct PIOInterface {
	Word PIO_PER;
	Word PIO_PDR;
	Word PIO_PSR;
	Word reserved0;
	Word PIO_OER;
	Word PIO_ODR;
	Word PIO_OSR;
	Word reserved1;
	Word PIO_IFER;
	Word PIO_IFDR;
	Word PIO_IFSR;
	Word reserved2;
	Word PIO_SODR;
	Word PIO_CODR;
	Word PIO_ODSR;
	Word PIO_PDSR;
	Word PIO_IER;
	Word PIO_IDR;
	Word PIO_IMR;
	Word PIO_ISR;
	Word PIO_MDER;
	Word PIO_MDDR;
	Word PIO_MDSR;
	Word reserved3;
	Word PIO_PUDR;
	Word PIO_PUER;
	Word PIO_PUSR;
	Word reserved4;
	Word PIO_ASR;
	Word PIO_BSR;
	Word PIO_ABSR;
	Word reserved5[8];
	Word PIO_OWER;
	Word PIO_OWDR;
	Word PIO_OWSR;
} PIOInterface;

#endif

