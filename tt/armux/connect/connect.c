#include "connect.h"
#include <pthread.h>

typedef struct Params {
	ARMDevice *device;
	void *params;
} Params;

void wait_write(Params *params) {
	int address;
	int size;
	
	ARMDevice *device;
	device = params->device;

	while(1) {
		if((size = recv(device->socket, &address, 4, 0)) > 0) {
			device->tellWritten(address, params->params);
		}
	}
}

int register_device(ARMDevice *device, void (*func)(int, void *),
                    void *params) {
	FILE *tmpFile;
	int read;
	int i;
	char message[128];
	RegisterDevice reg;
	pthread_t thread;
	Params p;

	device->tellWritten = func;

	sprintf(device->sun_path, "/tmp/armux.un");
	sprintf(device->pathname, "/tmp/%s.ipc", device->name);
	
	tmpFile = fopen(device->pathname, "w");
	fclose(tmpFile);

	if((device->key = ftok(device->pathname, 'A')) == -1) {
		return -1;
	}

	if((device->semid = semget(device->key, 1, 0666 | IPC_CREAT)) == -1) {
		return -1;
	}

	unlock(device);

	if((device->shmid = shmget(device->key, device->size, 0666 | IPC_CREAT))
	   == -1) {
		return -1;
	}

	if((device->memory = shmat(device->shmid, NULL, 0)) == -1) {
		return -1;
	}

	for(i = 0; i < device->size; i++) {
		device->memory[i] = 0;
	}

	if((device->socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		return -1;
	}

	device->remote.sun_family = AF_UNIX;
	strcpy(device->remote.sun_path, device->sun_path);


	if(connect(device->socket, (struct sockaddr *)&device->remote,
	           sizeof(device->remote)) == -1) {
		return -1;
	}

	strcpy(reg.name, device->name);
	reg.base_addr = device->base_addr;
	reg.size      = device->size;
	if(send(device->socket, &reg, sizeof(RegisterDevice), 0) == -1) {
		return -1;
	}

	if((read = recv(device->socket, message, 128, 0)) > 0) {
		message[read] = '\0';
		if(strcmp(message, "accept") != 0) {
			return -2;
		}
	} else if(read < 0) {
		return -1;
	} else {
		return -2;
	}

	p.device = device;
	p.params = params;

	pthread_create(&thread, NULL, &wait_write, &p);

	return 0;
}

void lock(ARMDevice *device) {
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	if(semop(device->semid, &sops, 1) == -1) {
		perror("lock semop");
		exit(1);
	}
}


void unlock(ARMDevice *device) {
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = 0;
	if(semop(device->semid, &sops, 1) == -1) {
		perror("unlock semop");
		exit(1);
	}
}

Word readWord(ARMDevice *device , int addr) {
	Word value = 0;
	int i;
	lock(device);

	for(i = 0; i < 4; i++) {
		value |= (device->memory[addr + i] << i * 8) &
				(0xff << (i * 8));
	}

	unlock(device);
	return value;
}

Halfword readHalfword(ARMDevice *device, int addr) {
	Halfword value = 0;
	int i;
	lock(device);

	for(i = 0; i < 2; i++) {
		value |= (device->memory[addr + i] << i * 8) &
				(0xff << (i * 8));
	}

	unlock(device);
	return value;
}

Byte readByte(ARMDevice *device, int addr) {
	Byte value;
	lock(device);
	value = device->memory[addr];
	unlock(device);
	return value;
}

void writeWord(ARMDevice *device, int addr, Word value) {
	int i;
	lock(device);

	for(i = 0; i < 4; i++) {
		device->memory[addr + i] = 0;
		device->memory[addr + i] |= value >> (i * 8);
	}

	unlock(device);

}

void writeHalfword(ARMDevice *device, int addr, Halfword value) {
	int i;
	lock(device);

	for(i = 0; i < 2; i++) {
		device->memory[addr + i] = 0;
		device->memory[addr + i] |= value >> (i * 8);
	}

	unlock(device);
}

void writeByte(ARMDevice *device, int addr, Byte value) {
	lock(device);
	device->memory[addr] = value;
	unlock(device);
}
