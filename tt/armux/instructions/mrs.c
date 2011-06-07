#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mrs_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un mrs\n");
#endif
	Word R, Rd;

	if( !cond(proc, instruction) )
                return;
	R = get_bits(instruction, 22, 1);
	Rd = get_bits(instruction, 12, 4);
	if( R )
		*proc->r[Rd] = proc->spsr;
	else
		*proc->r[Rd] = proc->cpsr;
}

