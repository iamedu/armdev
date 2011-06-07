uart: main.o
	gcc -m32 -o uart main.o -larmuxc

main.o: main.c
	gcc -m32 -c main.c

clean:
	rm main.o uart
