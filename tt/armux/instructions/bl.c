#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void bl_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un bl\n");
#endif
	Word L, signed_immed_24;
	if( !cond(proc, instruction) )
                return;
	L = get_bits(instruction, 24, 1);


	signed_immed_24 = get_bits(instruction, 0, 24);
	if( L ) {
		*proc->r[14] = *proc->r[15];
	}
	*proc->r[15] += SignExtend30(signed_immed_24, 24) << 2;
	*proc->r[15] += 4;
}

