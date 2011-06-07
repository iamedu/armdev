#ifndef _ARMY_WDT_H
#define _ARMY_WDT_H

#include <army/types.h>

#define WDT_PTR (WDTInterface *)0xFFFFFD40;

typedef struct WDTInterface {
	Word WDT_CR; //Control Register
	Word WDT_MR; //Mode register
	Word WDT_SR; //Status register
} WDTInterface;

//WDT_CR Bit definition
#define WDRSTT (0x1 << 0)

//WDT_MR Bit definition
#define WDFIEN (0x1 << 12)
#define WDRSTEN (0x1 << 13)
#define WDRPROC (0x1 << 14)
#define WDDIS (0x1 << 15)
#define WDD_Shift 16
#define WDDBGHLT (0x1 << 28)
#define WDIDLEHLT (0x1 << 29)

//WDT_SR Bit definition
#define WDUNF (0x1 << 0)
#define WDERR (0x1 << 1)

#endif

