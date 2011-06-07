#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void lsm_addr4(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSMReturn *res = result;
        Word Rn, register_list, W;

#ifdef DEBUG
        printf("Ejecutaste un LSM addr4\n");
#endif

	Rn = get_bits(instruction, 16, 4);
        register_list = get_bits(instruction, 0, 16);
        W = get_bits(instruction, 21, 1);
        res->start_address = *proc->r[Rn] - (count32(register_list) * 4);
        res->end_address = *proc->r[Rn] - 4;
        if( cond(proc, instruction) && W )
                *proc->r[Rn] -= count32(register_list) * 4;
}

