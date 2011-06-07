#ifndef _ARMLDER_PIO_H
#define _ARMLDER_PIO_H

#define PIO_PER  0x0000 //PIO Enable Register
#define PIO_PDR  0x0004 //PIO Disable Register
#define PIO_PSR  0x0008 //PIO Status Register
#define PIO_OER  0x0010 //Output Enable Register
#define PIO_ODR  0x0014 //Output Disable Register
#define PIO_OSR  0x0018 //Output Status Register
#define PIO_IFER 0x0020 //Glitch Input Filter Enable Register
#define PIO_IFDR 0x0024 //Glitch Input Filter Disable Register
#define PIO_IFSR 0x0028 //Glitch Input Filter Status Register
#define PIO_SODR 0x0030 //Set Output Data Register
#define PIO_CODR 0x0034 //Clear Output Data Register
#define PIO_ODSR 0x0038 //Output Data Status Register
#define PIO_PDSR 0x003C //Pin Data Status Register
#define PIO_IER  0x0040 //Interrupt Enable Register
#define PIO_IDR  0x0044 //Interrupt Disable Register
#define PIO_IMR  0x0048 //Interrupt Mask Register
#define PIO_ISR  0x004C //Interrupt Status Register
#define PIO_MDER 0x0050 //Multi-driver Enable Register
#define PIO_MDDR 0x0054 //Multi-driver Disable Register
#define PIO_MDSR 0x0058 //Multi-driver Status Register
#define PIO_PUDR 0x0060 //Pull-up Disable Register
#define PIO_PUER 0x0064 //Pull-up Enable Register
#define PIO_PUSR 0x0068 //Pull-up Status Register
#define PIO_ASR  0x0070 //Peripheral A Select Register
#define PIO_BSR  0x0074 //Peripheral B Select Register
#define PIO_ABSR 0x0078 //AB Status Register
#define PIO_OWER 0x00A0 //Output Write Enable
#define PIO_OWDR 0x00A4 //Output Write Disable
#define PIO_OWSR 0x00A8 //Output Write Status Register

#endif

