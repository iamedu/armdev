prueba.bin: prueba.o linker
	arm-elf-gcc -o prueba.bin prueba.o 
	#arm-elf-gcc -Xlinker -T linker -o prueba.bin prueba.o 

prueba.o: prueba.s
	arm-elf-gcc -c prueba.s

prueba.s: prueba.c
	arm-elf-gcc -S prueba.c

clean:
	rm prueba.bin prueba.o prueba.s 
