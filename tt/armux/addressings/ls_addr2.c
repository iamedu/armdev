#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void ls_addr2(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSReturn *res = result;
        Word Rn, Rm, U;

#ifdef DEBUG
        printf("Ejecutaste un LS addr2\n");
#endif
	U = get_bits(instruction, 23, 1);
	Rn = get_bits(instruction, 16, 4);
	Rm = get_bits(instruction, 0, 4);
	
	if( U )
		res->address = *proc->r[Rn] + *proc->r[Rm];
	else
		res->address = *proc->r[Rn] - *proc->r[Rm];
	
}

