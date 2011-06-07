#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void dp_addr1(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrDPReturn *res = result;
	Word immed_8;
	Word rotate_imm;
	Word Cflag = get_bits(*proc->cpsr,29,1);

#ifdef DEBUG
        printf("Ejecutaste un DP addr1\n");
#endif

	immed_8 = get_bits(instruction, 0, 8);
	rotate_imm = get_bits(instruction, 8, 8);

	res->shifter_operand = ror(immed_8, 32, rotate_imm * 2);
	if(rotate_imm == 0){
		res->shifter_carry_out = Cflag; 
	}else{
		res->shifter_carry_out = get_bits(res->shifter_operand,31,1); 
	}
}

