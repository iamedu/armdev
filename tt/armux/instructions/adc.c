#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void adc_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un adc\n");
#endif
	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	Word S;	
	Word Rn;
	Word Rd;
	Word carry;
	Word last_rd;
	ARMAddrDPReturn result;
	
	if(!cond(proc, instruction))
		return;
	S =  get_bits(instruction,20,1);
	Rn = get_bits(instruction,16,4);
	Rd = get_bits(instruction,12,4);
	
	//---Parte indispensable para obtener el result
	mode = fetch_addr(modes, instruction);
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	//---
	
	last_rd = *proc->r[Rd];
	*proc->r[Rd] = AddCarryFrom(*proc->r[Rn],result.shifter_operand + get_bits(*proc->cpsr,29,1),&carry); 

	if(S && Rd == 15) {
		if(proc->cpsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S == 1) {
			set_status(proc, status_n, get_bits(*proc->r[Rd], 31, 1));
			set_status(proc, status_z, *proc->r[Rd] == 0);
			set_status(proc, status_c, carry);
			set_status(proc, status_v, OverflowFrom(last_rd,*proc->r[Rd]));
	}

}

