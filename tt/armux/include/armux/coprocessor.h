#ifndef COPROCESSOR_H
#define COPROCESSOR_H

#include <armux/types.h>

typedef struct ARMCoprocessorInterface {
	UWord (*readRegister)(void *, int);
	void (*writeRegister)(void *, int, UWord);
	void (*sendOperation)(void *, Word);
	Word (*readOperation)(void *);
} ARMCoprocessorInterface;

typedef struct CP15Coprocessor {
	UWord (*readRegister)(void *, int);
	void (*writeRegister)(void *, int, UWord);
	void (*sendOperation)(void *, Word);
	UWord *reg;
} CP15Coprocessor;

ARMCoprocessorInterface *new_cp15();

#endif

