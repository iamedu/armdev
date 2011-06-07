#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void dp_addr9(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr9\n");
#endif
	ARMAddrDPReturn *res = result;
        Word Rm =  get_bits(instruction,0,4);
        Word shift_imm = get_bits(instruction,7,5);
        if(shift_imm == 0){
		//See "Data-Processing operands - Rotate right with extend" on page A5-17
        }
        else{
                res->shifter_operand = ror(*proc->r[Rm],32,shift_imm);
                res->shifter_carry_out = get_bits(*proc->r[Rm],shift_imm-1,1);
        }

}

