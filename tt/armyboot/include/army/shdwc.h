#ifndef _ARMY_SHDWC_H
#define _ARMY_SHDWC_H

#include <army/types.h>

#define SHDWC_PTR (SHDWCInterface *)0xFFFFFD30;

typedef struct SHDWCInterface {
	Word SHDW_CR;
	Word SHDW_MR;
	Word SHDW_SR;
} SHDWCInterface;

//SHDW_CR Bit definition
#define SHDW (0x1 << 0)

//SHDW_MR Bit definition
#define WKMODE0_NONE  0x0
#define WKMODE0_L_T_H 0x1
#define WKMODE0_H_T_L 0x2
#define WKMODE0_NONE  0x0
#define WKMODE0_BOTH  0x3

#define CPTWK0_Shift  4		//Counter on Wake-up 0
#define CPTWK1_Shift  12	//Counter on Wake-up 1

#define RTTWKEN 16

//SHDW_SR Bit definition
#define WAKEUP0 (0x1 << 0)

#endif

