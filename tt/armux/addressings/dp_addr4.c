#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void dp_addr4(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr4\n");
#endif
	ARMAddrDPReturn *res = result;
	Word Rs = get_bits(instruction,4,4);
	Word Rm = get_bits(instruction,0,4);
	Word aux = get_bits(*proc->r[Rs],0,8);
	Word Cflag = get_bits(*proc->cpsr,29,1);
	if(aux==0){
		res->shifter_operand = *proc->r[Rm];
		res->shifter_carry_out = Cflag;
	}else if(aux < 32){
		res->shifter_operand = *proc->r[Rm] << aux;
		res->shifter_carry_out = get_bits(*proc->r[Rm],32-aux,1);
	}else if(aux == 32){
		res->shifter_operand = 0;
		res->shifter_carry_out = get_bits(*proc->r[Rm],0,1);
	}else{/*aux > 32*/		
		res->shifter_operand = 0;
		res->shifter_carry_out = 0;
	}
}

