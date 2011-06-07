#include <armux/coprocessor.h>
#include <stdlib.h>

UWord readCP15Register(void *cp, int reg) {
	CP15Coprocessor *coprocessor;
	coprocessor = cp;
	return coprocessor->reg[reg];
}

void writeCP15Register(void *cp, int reg, UWord value) {
	CP15Coprocessor *coprocessor;
	coprocessor = cp;
	coprocessor->reg[reg] = value;
}

ARMCoprocessorInterface *new_cp15() {
	CP15Coprocessor *cp15 = malloc(sizeof(CP15Coprocessor));

	cp15->reg = malloc(sizeof(UWord) * 16);

	cp15->readRegister = &readCP15Register;
	cp15->writeRegister = &writeCP15Register;

	return (ARMCoprocessorInterface *)cp15;
}

