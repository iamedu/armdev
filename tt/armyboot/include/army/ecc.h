#ifndef _ARMY_ECC_H
#define _ARMY_ECC_H

#include <army/types.h>

typedef struct {
	Word ECC_CR;
	Word ECC_MR;
	Word ECC_SR;
	Word ECC_PR;
	Word ECC_NPR;
} ECCInterface;

#endif

