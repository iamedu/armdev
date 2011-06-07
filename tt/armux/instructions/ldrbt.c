#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void ldrbt_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldrbt\n");
#endif
	//Instrucciones de LS
	ARMAddr *modes = addr_modes_ls();
	ARMAddr *mode;
	ARMAddrLSReturn result;
	Word Rd, Rn;
	
	if( !cond(proc, instruction) )
                return;
	mode = fetch_addr(modes, instruction);
	Rd = get_bits(instruction, 12, 4);
	Rn = get_bits(instruction, 16, 4);
	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	*proc->r[Rd] = proc->readByte(proc, result.address);
	*proc->r[Rn] = result.address;
}

