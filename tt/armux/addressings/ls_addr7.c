#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void ls_addr7(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSReturn *res = result;
        Word Rn, U, offset_12;

#ifdef DEBUG
        printf("Ejecutaste un LS addr7\n");
#endif

	U = get_bits(instruction, 23, 1);
        Rn = get_bits(instruction, 16, 4);
	offset_12 = get_bits(instruction, 0, 12);
	
	res->address = *proc->r[Rn];
	if( cond(proc, instruction) )
		if( U )
			*proc->r[Rn] += offset_12;
		else
			*proc->r[Rn] -= offset_12;
}

