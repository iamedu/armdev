#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void stc_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un stc\n");
	//Instrucciones de LSC
	ARMAddr *modes = addr_modes_lsc();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
	
	mode = fetch_addr(modes, instruction);
	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
}

