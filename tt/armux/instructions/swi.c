#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void swi_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un swi\n");
#endif
	ARMCoprocessorInterface *cp15;
	Word cp15_reg1;
	if( !cond(proc, instruction) )
        	return;
	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
	proc->registers[17] = *proc->r[14] - 4;
	proc->registers[32] = *proc->cpsr;
	set_bits(proc->cpsr, 0, 4, 0x13);
	set_status(proc, status_t, 0);
	set_status(proc, status_i, 1);
	set_status(proc, status_e, get_bits(cp15_reg1, 25, 1));
	*proc->r[15] = 0x00000008;
}

