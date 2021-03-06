#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mvn_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un mvn\n");
#endif

	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	ARMAddrDPReturn result;
	
	Word S;
        Word Rn;
        Word Rd;

        mode = fetch_addr(modes, instruction);

        if(mode != NULL)
                mode->execute(proc, instruction, &result);
        if(!cond(proc,instruction))
                return;
        Rd = get_bits(instruction,12,4);
        *proc->r[Rd] = ~result.shifter_operand;
        if(S && Rd==15){
                if(proc->cpsr != NULL){
                        *proc->cpsr = *proc->spsr;
                }
        }
        else if(S == 1){
                set_status(proc,status_n,get_bits(*proc->r[Rd],31,1));
                set_status(proc,status_z,*proc->r[Rd] == 0);
                set_status(proc,status_c,result.shifter_carry_out);
        }

}

