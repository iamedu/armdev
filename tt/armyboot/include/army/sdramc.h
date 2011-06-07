#ifndef _ARMY_SDRAMC_H
#define _ARMY_SDRAMC_H

#include <army/types.h>

typedef struct SDRAMCInterface {
	Word SDRAMC_MR;
	Word SDRAMC_TR;
	Word SDRAMC_CR;
	Word SDRAMC_LPR;
	Word SDRAMC_IER;
	Word SDRAMC_IDR;
	Word SDRAMC_IMR;
	Word SDRAMC_ISR;
	Word SDRAMC_MDR;
} SDRAMCInterface;

#endif

