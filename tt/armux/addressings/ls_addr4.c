#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void ls_addr4(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSReturn *res = result;
        Word Rn, offset_12, U;

#ifdef DEBUG
        printf("Ejecutaste un LS addr4\n");
#endif

	U = get_bits(instruction, 23, 1);
	Rn = get_bits(instruction, 16, 4);
	offset_12 = get_bits(instruction, 0, 12);
	
	if( U )
		res->address = *proc->r[Rn] + offset_12;
	else
		res->address = *proc->r[Rn] - offset_12;
	if( cond(proc, instruction) )
                *proc->r[Rn] = res->address;
}

