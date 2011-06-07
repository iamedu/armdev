#include <devices.h>

#include <aic.h>
#include <pmc.h>
#include <pio.h>
#include <wdt.h>
#include <rtt.h>
#include <dbgu.h>

void write_register(int addr, int value) {
	int *reg = (int *)addr;
	*reg = value;
}

int read_register(int addr) {
	int *reg = (int *)addr;
	return *reg;
}

void loop() {
	while(1);
}

void irq_handler() {
	int i = 0;
	if(read_register(PIOA_BASE + PIO_ODSR)) {
		write_register(PIOA_BASE + PIO_ODSR, 0x00000000);
	} else {
		write_register(PIOA_BASE + PIO_ODSR, 0xffffffff);
	}


	write_register(DBGU_BASE + DBGU_THR, 'H');
	while(i++ < 0xff);
	write_register(DBGU_BASE + DBGU_THR, 'o');
	while(i++ < 0xff);
	write_register(DBGU_BASE + DBGU_THR, 'l');
	while(i++ < 0xff);
	write_register(DBGU_BASE + DBGU_THR, 'a');
	while(i++ < 0xff);
	write_register(DBGU_BASE + DBGU_THR, '\r');

	read_register(RTT_BASE + RTT_SR);
	write_register(AIC_BASE + AIC_EOICR, 0);

	asm volatile ("stmfd	sp!,	{r0}\n"
		      "mrs	r0,	cpsr\n"
	              "bic	r0,	r0,	#0x80\n"
		      "msr	cpsr,	r0\n"
		      "ldmfd	sp!,	{r0}");

	loop();
}


void init() {
	unsigned int i;

	write_register(CCFG_BASE + 32, 0x1003A);

	write_register(PMC_BASE + CKGR_MOR,
			CKGR_OSCOUNT & (0x8 << 8) | CKGR_MOSCEN);

	while(!(read_register(PMC_BASE + PMC_SR) & (0x1 <<  0)));

	write_register(PMC_BASE + PMC_MCKR, 0x1);
	
	write_register(PMC_BASE + CKGR_PLLAR, ((0x1) << 29) |
	                                      ((172 << 16) & (0x7FF << 16)) |
					      (0x3F << 8) | 
					      (0x2 << 14) |
					      16);

	while(!(read_register(PMC_BASE + PMC_SR) & (0x1 << 1)));
	
	write_register(PMC_BASE + PMC_MCKR, 0x2 | 0 | (0x1 << 8));

	while(!(read_register(PMC_BASE + PMC_SR) & (0x1 << 3)));

	write_register(PMC_BASE + WDT_MR, 1 << 15);

	//Aqui empiezan otras cosas
	write_register(PMC_BASE + PMC_PCER, 0xffffffff);

	write_register(PIOA_BASE + PIO_OER, 0x00000240);
	write_register(PIOA_BASE + PIO_OWDR, 0xffffffff);
	write_register(PIOA_BASE + PIO_OWER, 0x00000240);
	write_register(PIOA_BASE + PIO_PER, 0x00000240);

	//Configurar dbgu
	/*
	write_register(PIOB_BASE + PIO_ODR, 0x0000C000);
	write_register(PIOB_BASE + PIO_ASR, 0x0000C000);
	write_register(PIOB_BASE + PIO_PDR, 0x0000C000);

	write_register(DBGU_BASE + DBGU_CR, 0x0000006C);
	write_register(DBGU_BASE + DBGU_MR, 0x4 << 9);

	write_register(DBGU_BASE + DBGU_BRGR, 54);

	write_register(DBGU_BASE + DBGU_CR, 0x00000050);
	*/

	/*
	write_register(PIOC_BASE + PIO_ODR, 0x00008000);
	write_register(PIOC_BASE + PIO_BSR, 0x00008000);
	write_register(PIOC_BASE + PIO_PDR, 0x00008000);
	
	write_register(AIC_BASE + AIC_SMR30, 1 << 5);
	write_register(AIC_BASE + AIC_SVR30, (unsigned int)&irq_handler);
	write_register(AIC_BASE + AIC_IECR, (1 << AIC_IRQ1));

	write_register(AIC_BASE + AIC_SMR1, 1 << 5);
	write_register(AIC_BASE + AIC_SVR1, (unsigned int)&irq_handler);
	write_register(AIC_BASE + AIC_IECR, (1 << SYSC));

	write_register(PIOA_BASE + PIO_ODSR, 0xffffffff);
	write_register(RTT_BASE + RTT_MR, 0x0002f000);
	write_register(RTT_BASE + RTT_MR, 0x0006f000);
	*/


	/*
	while(1) {
		if(read_register(PIOC_BASE + PIO_PDSR) & 0x00008000) {
			write_register(PIOA_BASE + PIO_ODSR, 0xffffffff);
		} else {
			write_register(PIOA_BASE + PIO_ODSR, 0x00000000);
		}
		for(i = 0; i < 0xfffff; i++);
		write_register(PIOA_BASE + PIO_ODSR, 0xffffffff);
		for(i = 0; i < 0xfffff; i++);
	}
	*/
	loop();

}


