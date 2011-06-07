all: libc.la crt0.o

crt0.o: crt0.S
	arm-elf-gcc -c -nostdlib -isystem include crt0.S

libc.la: stdlib.lo string.lo
	libtool --tag=CC --mode=link arm-elf-gcc stdlib.lo string.lo -o libc.la
stdlib.lo: stdlib.c	
	libtool --tag=CC --mode=compile arm-elf-gcc -c -nostdlib -isystem include -o stdlib.lo stdlib.c

string.lo: string.c	
	libtool --tag=CC --mode=compile arm-elf-gcc -c -nostdlib -isystem include -o string.lo string.c

clean:
	rm -rf *.lo *.la .libs *.o

