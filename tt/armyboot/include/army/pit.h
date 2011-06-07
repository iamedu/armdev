#ifndef _ARMY_PIT_H
#define _ARMY_PIT_H

#include <army/types.h>

#define PIT_PTR (PITInterface *)0xFFFFFD30;

typedef struct PITInterface {
	Word PIT_MR;
	Word PIT_SR;
	Word PIT_PIVR;
	Word PIT_PIIR;
} PITInterface;

//PIT_MR Bit Definition
#define PIV_Shift 0
#define PITEN  (0x1 << 24)
#define PITIEN (0x1 << 25)

//PIT_SR Bit Definition
#define PITS 0

//PIT_PIVR and PIT_PIIR Bit Definition
#define CPIV_Shift  0
#define PICNT (0x1 << 20)

#endif

