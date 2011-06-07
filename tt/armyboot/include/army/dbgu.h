#ifndef _ARMY_DBGU_H
#define _ARMY_DBGU_H

#include <army/types.h>

typedef struct DBGUInterface {
	Word DBGU_CR;
	Word DBGU_MR;
	Word DBGU_IER;
	Word DBGU_IDR;
	Word DBGU_IMR;
	Word DBGU_SR;
	Word DBGU_RHR;
	Word DBGU_THR;
	Word DBGU_BRGR;
	Word reserved[10];
	Word DBGU_CIDR;
	Word DBGU_EXID;
	Word DBGU_FNR;
} DBGUInterface;

#endif

