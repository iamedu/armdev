#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void smlalxy_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un smlalxy\n");
	UWord RdLo = get_bits(instruction,12,4);
        UWord RdHi = get_bits(instruction,16,4);
        Word Rs = get_bits(instruction,8,4);
        Word Rm = get_bits(instruction,0,4);
        Word x = get_bits(instruction,5,1);
        Word y = get_bits(instruction,6,1);
        Word last_rd;
	Word result;
	Word carry;
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
		
		if((operand1 * operand2) < 0){
			result = 0xFFFFFFFF;
		}
		else{
			result = 0;
		}

		*proc->r[RdLo] = *proc->r[RdLo] + AddCarryFrom(RdLo,(operand1 * operand2),&carry);	
		*proc->r[RdHi] = *proc->r[RdHi] + *proc->r[RdLo] + result + carry;
        }

}

