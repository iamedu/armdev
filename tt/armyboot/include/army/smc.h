#ifndef _ARMY_SMC_H
#define _ARMY_SMC_H

#include <army/types.h>

#define SMC_BASE (SMCInterface *)0xFFFFEC00;
#define SMCN_PTR(N) (SMCInterface *)(0xFFFFEC00 + 0x10 * N);

typedef struct SMCInterface {
	Word SMC_SETUP;
	Word SMC_PULSE;
	Word SMC_CYCLE;
	Word SMC_MODE;
} SMCInterface;

#endif

