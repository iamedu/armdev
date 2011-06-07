#ifndef _ARMUX_CONNECT_H
#define _ARMUX_CONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef char Byte;
typedef short int Halfword;
typedef int Word;

typedef unsigned char UByte;
typedef unsigned short int UHalfword;
typedef unsigned int UWord;

typedef struct RegisterDevice {
	char name[80];
	int base_addr;
	int size;
	void (*tellWritten)(int, void *);
} RegisterDevice;

typedef struct ARMDevice {
	char name[80];
	int base_addr;
	int size;
	void (*tellWritten)(int, void *);
	char sun_path[108];
	char pathname[108];
	int socket;
	key_t key;
	struct sockaddr_un remote;
	int semid;
	int shmid;
	char *memory;
} ARMDevice;

int register_device(ARMDevice *, void (*func)(int, void*), void *);

Word readWord(ARMDevice *, int);
Halfword readHalfword(ARMDevice *, int);
Byte readByte(ARMDevice *, int);

void writeWord(ARMDevice *, int, Word);
void writeHalfword(ARMDevice *, int, Halfword);
void writeByte(ARMDevice *, int, Byte);

#endif

