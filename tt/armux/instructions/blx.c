#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void blx_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un blx\n");
#endif
	Word Rm, target;
	if( !cond(proc, instruction) )
                return;
	Rm = get_bits(instruction, 0, 4);
	target = Rm;
	*proc->r[14] = *proc->r[15] + 4;
	set_status( proc, status_t, get_bits(target, 0, 1) );
	*proc->r[15] = target & 0xFFFFFFFE;
}

