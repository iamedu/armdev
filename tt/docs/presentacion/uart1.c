#include <armux/connect.h>

void valueWritten(int address, void *params) {
	ARMDevice *uart;
	uart = (ARMDevice *)params;
	UARTInterface *inter = (UARTInterface *)
	                       uart->memory;
	/*
	 * ...
	 */
}

