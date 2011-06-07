#ifndef _ARMY_SPI_H
#define _ARMY_SPI_H

#include <army/types.h>

typedef struct SPIInterface {
	Word SPI_CR;
	Word SPI_MR;
	Word SPI_RDR;
	Word SPI_TDR;
	Word SPI_SR;
	Word SPI_IER;
	Word SPI_IDR;
	Word SPI_IMR;
	Word reserved0[4];
	Word SPI_CSR[4];
} SPIInterface;

#endif

