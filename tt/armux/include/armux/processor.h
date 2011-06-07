#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <pthread.h>

#include <armux/types.h>
#include <armux/memory.h>
#include <armux/coprocessor.h>

#define mode_usr 0x10
#define mode_fiq 0x11
#define mode_irq 0x12
#define mode_svc 0x13
#define mode_abt 0x17
#define mode_und 0x1b
#define mode_sys 0x1f

#define status_m 0
#define status_t 5
#define status_ge 16
#define status_f 6
#define status_i 7
#define status_a 8
#define status_e 9
#define status_j 24
#define status_q 27
#define status_v 28 
#define status_c 29
#define status_z 30
#define status_n 31

typedef struct ARMProc {
	Word **r;
	Word *cpsr;
	Word *spsr;
	Word registers[37];
	MemInterface *memory;
	void (*changeMode)(struct ARMProc *, Word);
	Byte (*readByte)(struct ARMProc *, UWord);
	Halfword (*readHalfword)(struct ARMProc *, UWord);
	Word (*readWord)(struct ARMProc *, UWord);
	void (*writeByte)(struct ARMProc *, UWord, Byte);
	void (*writeHalfword)(struct ARMProc *, UWord, Halfword);
	void (*writeWord)(struct ARMProc *, UWord, Word);
	ARMCoprocessorInterface *coprocessors[17];
	void *thread;
	/*
	 * registers[0] = r0
	 * registers[1] = r1
	 * ...
	 * registers[15] = r15 //PC
	 * registers[16] = r13_svc
	 * registers[17] = r14_svc
	 * registers[18] = r13_abt
	 * registers[19] = r14_abt
	 * registers[20] = r13_und
	 * registers[21] = r14_und
	 * registers[22] = r13_irq
	 * registers[23] = r14_irq
	 * registers[24] = r8_fiq	
	 * registers[25] = r9_fiq	
	 * registers[26] = r10_fiq	
	 * registers[27] = r11_fiq	
	 * registers[28] = r12_fiq	
	 * registers[29] = r13_fiq	
	 * registers[30] = r14_fiq
	 * registers[31] = cpsr
	 * registers[32] = spsr_svc	
	 * registers[33] = spsr_abt	
	 * registers[34] = spsr_und	
	 * registers[35] = spsr_irq	
	 * registers[36] = spsr_fiq	
	 */ 
} ARMProc;

typedef struct ThreadParams {
	int pause;
	int stop;
	ARMProc *proc;
	void *instruction_set;
	pthread_t thread;
	pthread_mutex_t pause_mutex;
	pthread_cond_t pause_cond;
} ThreadParams;

ARMProc *init();

ThreadParams *startExecution(ARMProc *, void *);
void pauseExecution(ARMProc *, ThreadParams *);
void resumeExecution(ARMProc *, ThreadParams *);
void step(ThreadParams *);
void stopExecution(ARMProc *, ThreadParams *);
void loadProgram(ARMProc *, char *);
Word get_status(ARMProc *, Word);
void set_status(ARMProc *, Word, Word);

#endif


