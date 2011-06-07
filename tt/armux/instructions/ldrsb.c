#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void ldrsb_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldrsb\n");
#endif
	//Instrucciones de MLS
	ARMAddr *modes = addr_modes_mls();
	ARMAddr *mode;
	ARMAddrMLSReturn result;
	Word Rd, data;
	
	if( !cond(proc, instruction) )
                return;
	mode = fetch_addr(modes, instruction);
	Rd = get_bits(instruction, 12, 4);
	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	data = proc->readByte(proc,result.address);
	*proc->r[Rd] = SignExtend(data, 8);
}

