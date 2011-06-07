#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mcr_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un mcr\n");
	//Instrucciones de LSC
	ARMAddr *modes = addr_modes_lsc();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
        ARMCoprocessorInterface *cpro;
	Word Rd;
	Word cp_num;
 
	cp_num = get_bits(instruction,8,4);
	mode = fetch_addr(modes, instruction);
	Rd = get_bits(instruction,12,4);
	cpro =  proc->coprocessors[cp_num];

	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	if(cond(proc, instruction)){
		 cpro->sendOperation(cpro,Rd);	
	}
}

