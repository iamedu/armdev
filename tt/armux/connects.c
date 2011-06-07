#include <armux/connects.h>
#include <armux/memory.h>
#include <armux/processor.h>
#include <pthread.h>

void tellWritten(void *device, int addr) {
	ExternalDevice *dev;
	dev = (ExternalDevice *)dev;

	if(send(dev->socket, &addr, 4, 0) < 0) {
		perror("send");
		exit(1);
	}
}

void serveLoop(ConnectsServer *connectDesc) {
	ExternalDevice *dev;
	char accept_text[10];
	int size, base_addr, block_size;
	ARMMemBlock *mem_block;
	ARMMemNode *mem_node;
	ARMProc *proc;
	char pathname[108];
	RegisterDevice reg;
	char *memory;

	proc = (ARMProc *)connectDesc->proc;

	while(connectDesc->running) {
		dev = malloc(sizeof(ExternalDevice));
		dev->tellWritten = &tellWritten;
		dev->lock = &lockExternalDevice;
		dev->unlock = &unlockExternalDevice;
		size = sizeof(dev->remote);
		if((dev->socket = accept(connectDesc->socket,
			(struct sockaddr *)&dev->remote,
			&size)) == -1) {
			perror("accept");
			exit(1);
		}
		size = recv(dev->socket, &reg, sizeof(RegisterDevice), 0);
		if(size < 0) {
			perror("recv");
			exit(1);
		} else if(size == 0) {
			printf("No se recibio nada");
			exit(1);
		}
		strcpy(accept_text, "accept");
		if(send(dev->socket, accept_text, strlen(accept_text), 0) < 0) {
			perror("send");
			exit(1);
		}

		strcpy(dev->name, reg.name);
		sprintf(pathname, "/tmp/%s.ipc", dev->name);

		if((dev->key = ftok(pathname, 'A')) == -1) {
			perror("ftok");
			exit(1);
		}

		if((dev->semid = semget(dev->key, 1, 0666)) == -1) {
			perror("semget");
			exit(1);
		}

		if((dev->shmid = shmget(dev->key, reg.size, 0666)) == -1) {
			perror("shmget");
			exit(1);
		}

		if((memory = shmat(dev->shmid, NULL, 0)) == (char *)-1) {
			perror("shmat");
			exit(1);
		}

		mem_block = new_mem_block_shm(reg.base_addr, reg.size, memory);
		mem_block->device = dev;
		mem_node = new_mem_node(mem_block);

		add_mem_block(proc->memory->root, mem_node);
	}
}

void initConnectsServer(ConnectsServer *connectsDesc) {
	strcpy(connectsDesc->sun_path, "/tmp/armux.un");

	if((connectsDesc->socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	connectsDesc->local.sun_family = AF_UNIX;
	strcpy(connectsDesc->local.sun_path, connectsDesc->sun_path);
	unlink(connectsDesc->local.sun_path);

	if(bind(
	   connectsDesc->socket,
	   (struct sockaddr *)&connectsDesc->local,
	   sizeof(connectsDesc->local)
	   ) == -1) {
		perror("bind");
		exit(1);
	}

	if(listen(connectsDesc->socket, 5) == -1) {
		perror("listen");
		exit(1);
	}

	pthread_create(&connectsDesc->thread,
	               NULL,
		       (void *)&serveLoop,
		       connectsDesc);

}

void lockExternalDevice(void *device) {
	ExternalDevice *externalDevice = (ExternalDevice*)device;
	struct sembuf op;
	op.sem_num  = 0;
	op.sem_op   = -1;
	op.sem_flg = 0;
	if(semop(externalDevice->semid, &op, 1) == -1) {
		perror("lock");
		exit(1);
	}
}

void unlockExternalDevice(void *device) {
	ExternalDevice *externalDevice = (ExternalDevice*)device;
	struct sembuf op;
	op.sem_num  = 0;
	op.sem_op   = 1;
	op.sem_flg = 0;
	if(semop(externalDevice->semid, &op, 1) == -1) {
		perror("unlock");
		exit(1);
	}
}


