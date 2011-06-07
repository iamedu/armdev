#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void ldrd_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldrd\n");
#endif
	//Instrucciones de MLS
	ARMAddr *modes = addr_modes_mls();
	ARMAddr *mode;
	ARMAddrMLSReturn result;
	ARMCoprocessorInterface *cp15;
	Word Rd, cp15_reg1;

	if( !cond(proc, instruction) )
                return;	
	mode = fetch_addr(modes, instruction);
	Rd = get_bits(instruction, 12, 4);
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
	if( Rd % 2 && Rd != 14 && !get_bits(result.address, 0, 2) && (get_bits(cp15_reg1, 22, 1)  || !get_bits(result.address, 2, 1)) ) {
		*proc->r[Rd] = proc->readWord(proc, result.address);
		*proc->r[Rd + 1] = proc->readWord(proc, result.address + 4);
	}
}

