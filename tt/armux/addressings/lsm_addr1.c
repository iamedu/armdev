#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void lsm_addr1(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSMReturn *res = result;
	Word Rn, register_list, W;

#ifdef DEBUG
        printf("Ejecutaste un LSM addr1\n");
#endif
	Rn = get_bits(instruction, 16, 4);
	register_list = get_bits(instruction, 0, 16);
	W = get_bits(instruction, 21, 1);
	res->start_address = *proc->r[Rn];
	res->end_address = *proc->r[Rn] + (count32(register_list) * 4) - 4;
	if( cond(proc, instruction) && W )
		*proc->r[Rn] += count32(register_list) * 4;
}

