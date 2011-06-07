#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void ls_addr8(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSReturn *res = result;
        Word Rn, U, Rm;

#ifdef DEBUG
        printf("Ejecutaste un LS addr8\n");
#endif

	U = get_bits(instruction, 23, 1);
        Rn = get_bits(instruction, 16, 4);
        Rm = get_bits(instruction, 0, 4);

        res->address = *proc->r[Rn];
        if( cond(proc, instruction) )
                if( U )
                        *proc->r[Rn] += Rm;
                else
                        *proc->r[Rn] -= Rm;
}

