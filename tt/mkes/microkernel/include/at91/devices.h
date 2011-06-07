#ifndef _ARMLDER_DEVICES_H
#define _ARMLDER_DEVICES_H

#define writel(value, address) \
        (*(volatile unsigned int *)(address)) = (value)
#define readl(address) \
	(*(volatile unsigned int *)(address))

//These are the AT91SAM9260 periherpal identifiers
#define AIC_FIQ  0  //Advanced interrupt controller, External Interrupt: FIQ
#define SYSC 1  //System Controller Interrupt
#define PIOA 2  //Parallel input output controller A
#define PIOB 3  //Parallel input output controller B
#define PIOC 4  //Parallel input output controller C
#define ADC  5  //Analog to Digital Converter
#define US0  6  //USART 0
#define US1  7  //USART 1
#define US2  8  //USART 2
#define MCI  9  //Multimedia Card Interface
#define UDP  10 //USB Device Port
#define TWI  11 //Two-wire interface
#define SPI0 12 //Serial Periherpal Interface 0
#define SPI1 13 //Serial Periherpal Interface 1
#define SSC  14 //Synchronous Serial Controller
#define TC0  17 //Timer/Counter 0
#define TC1  18 //Timer/Counter 1
#define TC2  19 //Timer/Counter 2
#define UHP  20 //USB Host Port
#define EMAC 21 //Ethernet MAC
#define ISI  22 //Image Sensor Interface
#define US3  23 //USART 3
#define US4  24 //USART 4
#define US5  25 //USART 5
#define TC3  26 //Timer/Counter 3
#define TC4  27 //Timer/Counter 4
#define TC5  28 //Timer/Counter 5
#define AIC_IRQ0 29 //Advanced Interrupt Controller, External Interrupt: IRQ0
#define AIC_IRQ1 30 //Advanced Interrupt Controller, External Interrupt: IRQ1
#define AIC_IRQ2 31 //Advanced Interrupt Controller, External Interrupt: IRQ2

//Address for each periherpal
#define PIOA_BASE 0xFFFFF400
#define PIOB_BASE 0xFFFFF600
#define PIOC_BASE 0xFFFFF800

#define DBGU_BASE 0xFFFFF200

#define PMC_BASE  0xFFFFFC00
#define AIC_BASE  0xFFFFF000
#define CCFG_BASE 0xFFFFEF10

#define RTT_BASE  0xFFFFFD20
#define WDT_BASE  0xFFFFFD40

#define US_IDR          (12)
#define US_CR           ( 0)
#define US_MR           ( 4)
#define US_BRGR         (32)

#define AT91C_US_RSTRX            (0x1 <<  2)
#define AT91C_US_RSTTX            (0x1 <<  3)

#define AT91C_US_RXDIS            (0x1 <<  5)
#define AT91C_US_TXDIS            (0x1 <<  7)
#define AT91C_US_PAR              (0x7 <<  9)
#define AT91C_US_RXEN             (0x1 <<  4)
#define AT91C_US_TXEN             (0x1 <<  6) 

#endif

