#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>
#include <stdlib.h>

void ldm2_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldm(2)\n");
#endif
	//Instrucciones de LSM
	ARMAddr *modes = addr_modes_lsm();
	ARMAddr *mode;
	ARMAddrLSMReturn result;
	Word address, register_list;
	int i;

	if( !cond(proc, instruction) )
                return;
	mode = fetch_addr(modes, instruction);
	register_list = get_bits(instruction, 0, 15);	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	address = result.start_address;
	for( i = 0; i < 15; i++)
		if( get_bits(register_list, i, 1) ){
			proc->registers[i] = proc->readWord(proc, address);
			address += 4;
		}
	if( result.end_address != address - 4 )
		exit(1);
			
}

