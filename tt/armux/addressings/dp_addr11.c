#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void dp_addr11(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr11\n");
#endif
	
	ARMAddrDPReturn *res = result;
        Word Rm = get_bits(instruction,0,4);
        Word Cflag = get_bits(*proc->cpsr,29,1);
        res->shifter_operand = (Cflag << 31) | (*proc->r[Rm] >> 1);
        res->shifter_carry_out = get_bits(*proc->r[Rm],0,1);
}

