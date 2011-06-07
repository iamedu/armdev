prueba.bin: prueba
	../EL_FREAD/fread prueba prueba.bin

prueba: init.o prueba.o linker
	arm-elf-gcc -nostdlib -o prueba init.o prueba.o -lgcc

init.o:	init.s
	arm-elf-gcc -c init.s

prueba.o: prueba.s
	arm-elf-gcc -c prueba.s

prueba.s: prueba.c
	arm-elf-gcc -S prueba.c

clean:
	rm prueba.bin prueba.o prueba.s init.o prueba
