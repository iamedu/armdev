#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void smulw_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un smulw\n");
#endif
        Word Rm = get_bits(instruction,0,4);
        Word Rd = get_bits(instruction,16,4);
        Word Rs = get_bits(instruction,8,4);
        Word Rn = get_bits(instruction,12,4);
        Word y = get_bits(instruction,6,1);
        Word operand2;
        if(cond(proc,instruction)){
                if(y == 0)
                        operand2 = SignExtend(get_bits(*proc->r[Rs],0,16),16);
                else
                        operand2 = SignExtend(get_bits(*proc->r[Rs],16,16),16);
                *proc->r[Rd] = (*proc->r[Rm] * operand2) + *proc->r[Rn];//TO DO
        }

}

