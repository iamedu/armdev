#include <at91/devices.h>

#include <at91/aic.h>
#include <at91/pmc.h>
#include <at91/pio.h>
#include <at91/wdt.h>
#include <at91/dbgu.h>

/*
void write_register(int addr, int value) {
	int *reg = (int *)addr;
	*reg = value;
}

int read_register(int addr) {
	int *reg = (int *)addr;
	return *reg;
}
*/


void init() {
	/*
	unsigned int i;
	//Aqui empiezan otras cosas
	write_register(PIOA_BASE + PIO_OER, 0x00000240);
	write_register(PIOA_BASE + PIO_OWDR, 0x00000024);
	write_register(PIOA_BASE + PIO_OWER, 0x00000240);
	write_register(PIOA_BASE + PIO_PER, 0x00000240);

	//write_register(PIOC_BASE + PIO_ODR, 0x00008000);
	//write_register(PIOC_BASE + PIO_PER, 0x00008000);
	//write_register(PIOC_BASE + PIO_BSR, 0x00008000);
	
	//dbg_init(115200);

	while(1) {
		write_register(PIOA_BASE + PIO_ODSR, 0x00000000);
		for(i = 0; i < 0xfffff; i++);
		write_register(PIOA_BASE + PIO_ODSR, 0xffffffff);
		for(i = 0; i < 0xfffff; i++);
		dbg_print("Hola\r\n");
	}
	*/
	//dbg_init(115200);
	//dbg_putch('h');
	while(1) {
		dbg_print("Hola\r\n");
	}

}


