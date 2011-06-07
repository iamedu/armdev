#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void mls_addr2(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrMLSReturn *res = result;
        Word U, Rn, Rm;

#ifdef DEBUG
        printf("Ejecutaste un MLS addr2\n");
#endif

	U = get_bits(instruction, 23, 1);
        Rn = get_bits(instruction, 16, 4);
	Rm = get_bits(instruction, 0, 4);
	if( U )
                res->address = *proc->r[Rn] + *proc->r[Rm];
        else
                res->address = *proc->r[Rn] - *proc->r[Rm];
}

