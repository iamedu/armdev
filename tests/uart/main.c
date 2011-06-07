#include "uart.h"

int main() {
	uart_enable_write(USART0);
	while(1) {
		uart_write(USART0_THR, 'h');
		uart_write(USART0_THR, 'o');
		uart_write(USART0_THR, 'l');
		uart_write(USART0_THR, 'a');
		uart_write(USART0_THR, '\r');
		uart_write(USART0_THR, '\n');
	}
	return 0;
}

