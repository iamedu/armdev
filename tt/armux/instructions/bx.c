#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void bx_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un bx\n");
#endif
	Word Rm;
	Rm = get_bits(instruction, 0, 4);
	if( !cond(proc, instruction) )
                return;
	set_status( proc, status_t, get_bits(*proc->r[Rm], 0 ,1) );
	*proc->r[15] = *proc->r[Rm] & 0xFFFFFFFE;
}

