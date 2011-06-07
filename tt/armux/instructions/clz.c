#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void clz_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un clz\n");
#endif
	Word Rm, Rd;
	Rm = get_bits(instruction, 0, 4);
	Rd = get_bits(instruction, 12, 4);
	if( !*proc->r[Rm] )
		*proc->r[Rd] = 32;
	else
		Rd = 31 - msb_position(*proc->r[Rm]);
}
