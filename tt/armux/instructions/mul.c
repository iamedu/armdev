#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mul_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un mul\n");
	Word Rm = get_bits(instruction,0,4);
        Word Rd = get_bits(instruction,16,4);
        Word Rs = get_bits(instruction,8,4);
        Word S = get_bits(instruction,20,0);
        if(!cond(proc,instruction)){
                *proc->r[Rd] = *proc->r[Rm] * *proc->r[Rs];
                if(S == 1){
                        set_status(proc,status_n,get_bits(*proc->r[Rd],31,1));
                        set_status(proc,status_z,*proc->r[Rd] == 0);
                }
        }

}

