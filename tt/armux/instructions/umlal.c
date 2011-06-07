#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void umlal_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un umlal\n");
#endif
        UWord RdLo =  get_bits(instruction,12,4);
        UWord RdHi =  get_bits(instruction,16,4);
        Word Rs = get_bits(instruction,8,4);
        Word Rm = get_bits(instruction,0,4);
        Word S = get_bits(instruction,20,1);
        Word carry;
        Word result;
        Word z;
	Word Hi;
	Word Lo;
        if(cond(proc,instruction)){
		Mul64(*proc->r[Rm],*proc->r[Rs],&Hi,&Lo);
		*proc->r[RdLo] =  AddCarryFrom(Lo,*proc->r[RdLo],&carry);
                *proc->r[RdHi] =  Hi + *proc->r[RdHi] + carry;
                if(S == 1){
                        set_status(proc,status_n,get_bits(*proc->r[RdHi],31,1));
                        if(*proc->r[RdHi] == 0 && *proc->r[RdLo] == 0)
                                z = 1;
                        else
                                z = 0;
                        set_status(proc,status_z,z);
                }
          }

}

