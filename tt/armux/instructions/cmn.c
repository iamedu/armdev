#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void cmn_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un cmn\n");
#endif
	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	ARMAddrDPReturn result;
	
	Word S;
        Word Rn;
        Word Rd;
	Word carry;
	Word alu_out;

        mode = fetch_addr(modes, instruction);

        if(mode != NULL)
                mode->execute(proc, instruction, &result);
        if(!cond(proc,instruction))
                return;
        S =  get_bits(instruction,20,1);
        Rn = get_bits(instruction,16,4);
        Rd = get_bits(instruction,12,4);
	       
	alu_out = AddCarryFrom(*proc->r[Rn],result.shifter_operand,&carry);	
        set_status(proc,status_n,get_bits(alu_out,31,1));
        set_status(proc,status_z,alu_out == 0);
        set_status(proc,status_c, carry);
	if(OverflowFrom(*proc->r[Rn],alu_out) == 1  || OverflowFrom(result.shifter_operand,alu_out) == 1)	
	        set_status(proc,status_v,1);
	else 
	        set_status(proc,status_v,0);
		
	
}

