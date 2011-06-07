#include "uart.h"

void uart_enable_write(unsigned char *id) {
	*id = 0x50;
}

void uart_write(unsigned char *id, char c) {
	char *csr = USART0_CSR;
        while(!(*csr & 0x00000002));
	*id = c;
}

