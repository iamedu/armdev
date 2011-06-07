int main() {
	ARMDevice uart;
	UARTInterface *inter;
	uart.base_addr = 0xFFFB0000;
	uart.size = sizeof(UARTInterface);
	strcpy(uart.name, "uart");
	
	if(register_device(&uart,
	        &valueWritten, &uart) == -1) {
		perror("register_device");
		exit(1);
	}
