#ifndef _ARMLDER_PMC_H
#define _ARMLDER_PMC_H

#define CKGR_OSCOUNT    (0xFF << 8 )
#define CKGR_MOSCEN	(0x1  << 0 )

#define PMC_SCER	0x0000
#define PMC_SCDR	0x0004
#define PMC_SCSR	0x0008

#define PMC_PCER	0x0010
#define PMC_PCDR	0x0014
#define PMC_PCSR	0x0018

#define CKGR_MOR	0x0020
#define CKGR_MCFR	0x0024
#define CKGR_PLLAR	0x0028
#define CKGR_PlLBR	0x002C
#define PMC_MCKR	0x0030
#define PMC_PCK0	0x0040
#define PMC_PCK1	0x0044

#define PMC_IER		0x0060
#define PMC_IDR		0x0064
#define PMC_SR		0x0068
#define PMC_IMR		0x006C

#define PMC_PLLICPR	0x0080

#endif

