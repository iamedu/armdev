#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>
#include <armux/utils.h>
#include <stdio.h>

void smla_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un smla\n");
	Word Rm = get_bits(instruction,0,4);
        Word Rd = get_bits(instruction,16,4);
        Word Rs = get_bits(instruction,8,4);
        Word Rn = get_bits(instruction,12,4);
	Word x = get_bits(instruction,5,1);
	Word y = get_bits(instruction,6,1);
	Word last_rd;
	Word operand1,operand2;
        if(cond(proc,instruction)){
                if(x == 0)
               		operand1 = SignExtend(get_bits(*proc->r[Rm],0,16),16); 
		else
               		operand1 = SignExtend(get_bits(*proc->r[Rm],16,16),16);

		if(y == 0)
               		operand2 = SignExtend(get_bits(*proc->r[Rs],0,16),16); 
		else 
               		operand2 = SignExtend(get_bits(*proc->r[Rs],16,16),16); 
		last_rd = *proc->r[Rd];
		*proc->r[Rd] = (operand1 * operand2) + *proc->r[Rn];
		if(OverflowFrom(last_rd,*proc->r[Rn])) 
		        set_status(proc,status_q,1);
        }
}

