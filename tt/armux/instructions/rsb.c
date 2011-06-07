#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void rsb_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un rsb\n");
#endif
	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	ARMAddrDPReturn result;
	
	Word S;
        Word Rn;
        Word Rd;
	Word borrow;
	Word last_rd;
	Word carry;

        mode = fetch_addr(modes, instruction);

        if(mode != NULL)
                mode->execute(proc, instruction, &result);
        if(!cond(proc,instruction))
                return;
        Rn = get_bits(instruction,16,4);
        Rd = get_bits(instruction,12,4);

	last_rd = *proc->r[Rd];
        *proc->r[Rd] =  SubWithBorrow(result.shifter_operand,*proc->r[Rn],&borrow);

        if(S && Rd==15){
                if(proc->cpsr != NULL){
                        *proc->cpsr = *proc->spsr;
                }
        }
        else if(S == 1){
                set_status(proc,status_n,get_bits(*proc->r[Rd],31,1));
                set_status(proc,status_z,*proc->r[Rd] == 0);
		set_status(proc,status_c,borrow == 0); 
                set_status(proc,status_v,OverflowFrom(last_rd,*proc->r[Rd])); 
        }

}

