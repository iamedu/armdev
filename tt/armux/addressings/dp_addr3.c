#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void dp_addr3(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr3\n");
#endif
	ARMAddrDPReturn *res = result;
	Word Rm = get_bits(instruction,0,4);;
	Word Cflag = get_bits(*proc->cpsr,29,1);
	Word shift_imm = get_bits(instruction,7,5);
	if(shift_imm == 0){
		res->shifter_operand = *proc->r[Rm];
		res->shifter_carry_out = Cflag;
	}	
	else
	{
		res->shifter_operand = *proc->r[Rm] << shift_imm;
		res->shifter_carry_out = get_bits(*proc->r[Rm],32-shift_imm,1);
	}
}

