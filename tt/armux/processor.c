#include <armux/types.h>
#include <armux/processor.h>
#include <armux/instruction.h>

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void loadProgram(ARMProc *proc, char *filename) {
	FILE *f;
	int inst;
	int it = 0;

	f = fopen(filename, "r");
	if(f == NULL) {
		perror(filename);
		exit(1);
	}

	while(fread(&inst, 4, 1, f) != 0) {
		proc->writeWord(proc, it, inst);
		it += 4;
	}

	fclose(f);
}

Byte readByte(ARMProc *proc, UWord addr) {
	return proc->memory->readByte(proc->memory, addr);
}

Halfword readHalfword(ARMProc *proc, UWord addr) {
	return proc->memory->readHalfword(proc->memory, addr, LittleEndian);
}

Word readWord(ARMProc *proc, UWord addr) {
	return proc->memory->readWord(proc->memory, addr, LittleEndian);
}

void writeByte(ARMProc *proc, UWord addr, Byte value) {
	proc->memory->writeByte(proc->memory, addr, value);
}

void writeHalfword(ARMProc *proc, UWord addr, Halfword value) {
	proc->memory->writeHalfword(proc->memory, addr, value, LittleEndian);
}

void writeWord(ARMProc *proc, UWord addr, Word value) {
	proc->memory->writeWord(proc->memory, addr, value, LittleEndian);
}

void changeMode(ARMProc *proc, Word mode) {
	int i;
	switch(mode) {
		case mode_usr:
			for(i = 8; i < 15; i++) {
				proc->r[i] = &proc->registers[i];
			}
			proc->spsr = NULL;
		break;
		case mode_fiq:
			for(i = 8; i < 15; i++) {
				proc->r[i] = &proc->registers[24 + i];
			}
			proc->spsr = &proc->registers[36];
		break;
		case mode_irq:
			for(i = 8; i < 13; i++) {
				proc->r[i] = &proc->registers[i];
			}
			for(i = 13; i < 15; i++) {
				proc->r[i] = &proc->registers[22 + i];
			}
			proc->spsr = &proc->registers[35];
		break;
		case mode_svc:
			for(i = 8; i < 13; i++) {
				proc->r[i] = &proc->registers[i];
			}
			for(i = 13; i < 15; i++) {
				proc->r[i] = &proc->registers[16 + i];
			}
			proc->spsr = &proc->registers[32];
		break;
		case mode_abt:
			for(i = 8; i < 13; i++) {
				proc->r[i] = &proc->registers[i];
			}
			for(i = 13; i < 15; i++) {
				proc->r[i] = &proc->registers[18 + i];
			}
			proc->spsr = &proc->registers[33];
		break;
		case mode_und:
			for(i = 8; i < 13; i++) {
				proc->r[i] = &proc->registers[i];
			}
			for(i = 13; i < 15; i++) {
				proc->r[i] = &proc->registers[20 + i];
			}
			proc->spsr = &proc->registers[34];
		break;
		case mode_sys:
			for(i = 8; i < 15; i++) {
				proc->r[i] = &proc->registers[i];
			}
			proc->spsr = NULL;
		break;
		default:
			printf("Invalid mode change\n");
			exit(1);
		break;
	}

	set_status(proc, status_m, mode);
}

ARMProc *init() {
	//Declarations
	int i;
	ARMProc *instance;

	//Initializations
	instance = malloc(sizeof(ARMProc));

	instance->r = malloc(sizeof(Word) * 16);

	//Process
	//Init registers array to 0
	for(i = 0; i < 37; i++) {
		instance->registers[i] = 0;
	}
	
	//Init registers r0 to r12 as in svc mode
	for(i = 0; i < 13; i++) {
		instance->r[i] = &(instance->registers[i]);
	}

	//Initialize PC
	instance->r[15] = &(instance->registers[15]);
	
	//Initialize CPSR
	instance->cpsr = &(instance->registers[31]);
	instance->spsr = &instance->registers[32];

	//Initialize r13_svc
	instance->r[13] = &(instance->registers[16]);

	//Initialize r14_svc
	instance->r[14] = &(instance->registers[17]);

	//Change M bits to mode svc
	*instance->cpsr = mode_svc;

	set_status(instance, status_t, 0);
	set_status(instance, status_f, 1);
	set_status(instance, status_i, 1);
	set_status(instance, status_a, 1);

	//TODO: Implement CP15 to set endianess and high interrupt vectors
	
	instance->memory = memInterface();

	instance->readByte = &readByte;
	instance->readHalfword = &readHalfword;
	instance->readWord = &readWord;
	instance->writeByte = &writeByte;
	instance->writeHalfword = &writeHalfword;
	instance->writeWord = &writeWord;

	instance->changeMode = &changeMode;

	instance->coprocessors[15] = new_cp15();

	return instance;
}

Word get_status(ARMProc *proc, Word flag) {
	//Declarations
	Word tmp;
	Word bitmask;

	//Initializations
	tmp = *proc->cpsr;
	
	//Process

	if(flag == status_m) {
		bitmask = 0x1f;
	} else if(flag == status_ge) {
		bitmask = 0xf;
	} else {
		bitmask = 1;
	}

	return (tmp >> flag) & bitmask;
}

void set_status(ARMProc *proc, Word flag, Word value){
	//Declarations
	Word bitmask;
	UWord ubitmask;	
	//Initializations
	
	//Process
	if(flag == status_m) {
		bitmask = 0x1f;
	} else if(flag == status_ge) {
		bitmask = 0xf;
	} else {
		bitmask = 1;
	}
	
	//Valida si tiene el tamaño correcto usando un maskara
	value &= bitmask; 
 	
	//Generar la mascara para enCerar
	ubitmask= bitmask;
	ubitmask= ~(ubitmask << flag);
	
	//Aplicamos la mascar enCerada
	*proc->cpsr &= ubitmask;
	//Se actualiza el nuevo valor en el procesador
	*proc->cpsr |= (value << flag);
}

void step(ThreadParams *params) {
	ARMInst *instruction_set;
	ARMProc *proc;
	ARMInst *inst;
	int inst_code;

	proc = params->proc;
	instruction_set = (ARMInst *)params->instruction_set;

	inst_code = proc->readWord(proc, *proc->r[15]);
	inst = fetch(instruction_set, inst_code);
	*proc->r[15] += 4;
	inst->execute(proc, inst_code);
}

void execute(ThreadParams *params) {
	int inst_code;
	ARMInst *inst;
	ARMInst *instruction_set;
	ARMProc *proc;
	proc = params->proc;

	instruction_set = (ARMInst *)params->instruction_set;

	do {
		pthread_mutex_lock(&params->pause_mutex);
		if(params->pause) {
			pthread_cond_wait(&params->pause_cond,
			                  &params->pause_mutex);
		}
		pthread_mutex_unlock(&params->pause_mutex);

		inst_code = proc->readWord(proc, *proc->r[15]);
#ifdef DEBUG
		printf("Instruccion: %x %x\n", *proc->r[15], inst_code);
#endif
		inst = fetch(instruction_set, inst_code);
		*proc->r[15] += 4;
		inst->execute(proc, inst_code);
	} while(!params->stop);
	pthread_exit(0);
}

ThreadParams *startExecution(ARMProc *proc, void *iset) {
	ThreadParams *params = malloc(sizeof(ThreadParams));

	params->proc = proc;
	params->pause = 1;
	params->stop = 0;
	params->instruction_set = iset;

	proc->thread = params;

	pthread_create(&params->thread, NULL, (void *)&execute, params);


	return params;
}

void pauseExecution(ARMProc *proc, ThreadParams *params) {
	pthread_mutex_lock(&params->pause_mutex);
	params->pause = 1;
	pthread_mutex_unlock(&params->pause_mutex);
}

void stopExecution(ARMProc *proc, ThreadParams *params) {
	params->stop = 1;
	if(params->pause) {
		resumeExecution(proc, params);
	}
	pthread_join(params->thread, NULL);
}

void resumeExecution(ARMProc *proc, ThreadParams *params) {
	pthread_mutex_lock(&params->pause_mutex);
	params->pause = 0;
	pthread_cond_signal(&params->pause_cond);
	pthread_mutex_unlock(&params->pause_mutex);
}

