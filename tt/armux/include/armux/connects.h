#ifndef ARMUX_CONNECTS_H
#define ARMUX_CONNECTS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <pthread.h>

typedef struct RegisterDevice {
        char name[80];
	int base_addr;
	int size;
} RegisterDevice;

typedef struct ConnectsServer {
	key_t key;
	int socket;
	struct sockaddr_un local;
	pthread_t thread;
	char sun_path[108];
	int running;
	void *proc;
} ConnectsServer;

typedef struct Device {
	char name[80];
	void (*lock)(void *);
	void (*unlock)(void *);
	void (*tellWritten)(void *, int);
} Device;

typedef struct ExternalDevice {
	char name[80];
	void (*lock)(void *);
	void (*unlock)(void *);
	void (*tellWritten)(void *, int);
	key_t key;
	int semid;
	int shmid;
	struct sockaddr_un remote;
	int socket;
} ExternalDevice;

void tellWritten(void *, int);
void initConnectsServer(ConnectsServer *);
void lockExternalDevice(void *);
void unlockExternalDevice(void *);

#endif

