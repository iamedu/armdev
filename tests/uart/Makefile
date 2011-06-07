init.bin: init.out
	arm-elf-objcopy -O binary init.out init.bin
init.out: init.o main.o uart.o
	arm-elf-ld -nostdlib -e init_all init.o main.o uart.o -o init.out
main.o: main.c
	arm-elf-gcc -c main.c
uart.o: uart.c uart.h
	arm-elf-gcc -c uart.c
init.o: init.s
	arm-elf-gcc -c init.s
clean:
	rm *.o *.out *.bin
