#ifndef _ARMY_PDC_H
#define _ARMY_PDC_H

#include <army/types.h>

typedef struct PDCInterface {
	Word PERIPH_RPR;
	Word PERIPH_RCR;
	Word PERIPH_TPR;
	Word PERIPH_TCR;
	Word PERIPH_RNPR;
	Word PERIPH_RNCR;
	Word PERIPH_TNPR;
	Word PERIPH_PTCR;
	Word PERIPH_PTSR;
} PDCInterface;

#endif

