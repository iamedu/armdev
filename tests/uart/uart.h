#ifndef _UART_H
#define _UART_H

#define USART0     (char *)0xfffb0000
#define USART1     (char *)0xfffb4000
#define USART2     (char *)0xfffb8000
#define USART0_THR (char *)0xfffb001c
#define USART0_CSR (char *)0xfffb0014

void uart_enable(unsigned char *);
void uart_write(unsigned char *, char);

#endif

