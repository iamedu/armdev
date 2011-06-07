#ifndef _ARMY_RSTC_H
#define _ARMY_RSTC_H

#include <army/types.h>

#define RSTC_PTR (RSTCInterface *)0xFFFFFD00

typedef struct RSTCInterface {
	Word RSTC_CR; //Control Register
	Word RSTC_SR; //Status Register
	Word RSTC_MR; //Mode Register
} RSTCInterface;

//RSTC_CR Bit definition
#define PROCRST (1 << 0)
#define PERRST  (1 << 2)
#define EXTRST  (1 << 3)

//RSTC_SR Bit definition
#define URSTS (1 << 0)
#define RSTTYP_General  (0x0 << 8)
#define RSTTYP_WakeUp   (0x1 << 8)
#define RSTTYP_Watchdog (0x2 << 8)
#define RSTTYP_Software (0x3 << 8)
#define RSTTYP_User     (0x4 << 8)
#define NRSTL (1 << 16)
#define SRCMP (1 << 17)

//RSTC_MR Bit definition
#define URSTEN  0x01
#define URSTIEN 0x10
#define ERSTL_Shift 8 //This value could be variable, the shift indicates
                      //the offset of the value
#define RSTC_MR_KEY 0xA5000000

#endif

