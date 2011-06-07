#ifndef _ARMY_RTT_H
#define _ARMY_RTT_H

#include <army/types.h>

#define RTT_PRT (RTTInterface *)0xFFFFFD20;

typedef struct RTTInterface {
	Word RTT_MR; //Mode Register
	Word RTT_AR; //Alarm Register
	Word RTT_VR; //Value Register
	Word RTT_SR; //Status Register
} RTTInterface;

//RTT_MR Bit definition
#define RTPRES_Shift 0
#define ALMIEN (0x1 << 16)
#define RTTINCIEN (0x1 << 17)
#define RTTRST (0x1 << 18)

//RTT SR
#define ALMS (0x1 << 0)
#define RTTINC (0x1 << 1)

#endif

