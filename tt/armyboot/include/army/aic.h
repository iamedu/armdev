#ifndef _ARMY_AIC_H
#define _ARMY_AIC_H

#include <army/types.h>

typedef struct AICInterface {
	Word AIC_SMR[32];
	Word AIC_SVR[32];
	Word AIC_IVR;
	Word AIC_FVR;
	Word AIC_ISR;
	Word AIC_IPR;
	Word AIC_IMR;
	Word AIC_CISR;
	Word reserved0[2];
	Word AIC_IECR;
	Word AIC_IDCR;
	Word AIC_ICCR;
	Word AIC_ISCR;
	Word AIC_EOICR;
	Word AIC_SPU;
	Word AIC_DCR;
	Word reserved1;
	Word AIC_FFER;
	Word AIC_FFDR;
	Word AIC_FFSR;
} AICInterface;

#endif

