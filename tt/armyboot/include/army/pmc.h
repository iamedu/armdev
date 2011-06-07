#ifndef _ARMY_PMC_H
#define _ARMY_PMC_H

#include <army/types.h>

typedef struct PMCInterface {
	Word PMC_SCER;
	Word PMC_SCDR;
	Word PMC_SCSR;
	Word reserved0;
	Word PMC_PCER;
	Word PMC_PCDR;
	Word PMC_PCSR;
	Word reserved1;
	Word CKGR_MOR;
	Word CKGR_MCFR;
	Word CKGR_PLLAR;
	Word CKGR_PLLBR;
	Word PMC_MCKR;
	Word reserved2[3];
	Word PMC_PCK0;
	Word PMC_PCK1;
	Word reserved3[6];
	Word PMC_IER;
	Word PMC_IDR;
	Word PMC_SR;
	Word PMC_IMR;
	Word reserved4[4];
	Word PMC_PLLICPR;
} PMCInterface;

#endif

