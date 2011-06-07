#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <armux/connect.h>

typedef struct UARTInterface {
        Word US_CR;
        Word US_MR;
        Word US_IER;
        Word US_IDR;
        Word US_IMR;
        Word US_CSR;
        Word US_RHR;
        Word US_THR;
        Word US_BRGR;
        Word US_RTOR;
        Word US_TTGR;
        Word US_Reserved_1;
        Word US_FIDI;
        Word US_NER;
        Word US_Reserved_2;
        Word US_IF;
} UARTInterface;

void valueWritten(int address, void *params) {
	ARMDevice *uart;
	uart = (ARMDevice *)params;
	UARTInterface *inter = (UARTInterface *)uart->memory;
	if(address == 0 && (inter->US_CR & 0x40)) {
		inter->US_IER |= 0x2;
		return;
	}
	inter->US_IER &= 0xfffffffd;
	printf("%c", inter->US_THR);
	fflush(stdout);
	inter->US_IER |= 0x2;
}

int main() {
	ARMDevice uart;
	UARTInterface *inter;
	uart.base_addr = 0xFFFB0000;
	uart.size = sizeof(UARTInterface);
	strcpy(uart.name, "uart");
	
	if(register_device(&uart, &valueWritten, &uart) == -1) {
		perror("register_device");
		exit(1);
	}
	
	inter = (UARTInterface *)uart.memory;
	inter->US_IMR = 0x0;
	inter->US_RHR = 0x0;
	inter->US_BRGR = 0x0;
	inter->US_RTOR = 0x0;
	inter->US_TTGR = 0x0;
	inter->US_FIDI = 0x174;
	inter->US_IF = 0x0;	

	while(1) {}

	return 0;
}

