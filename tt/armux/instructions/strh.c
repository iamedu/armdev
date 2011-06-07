#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void strh_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un strh\n");
#endif
	//Instrucciones de MLS
	ARMAddr *modes = addr_modes_mls();
	ARMAddr *mode;
	ARMAddrMLSReturn result;
	ARMCoprocessorInterface *cp15;
        Word cp15_reg1, Rd;

        if( !cond(proc, instruction) )
                return;	
	mode = fetch_addr(modes, instruction);
	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
        Rd = get_bits(instruction, 12, 4);
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	if( !get_bits(cp15_reg1, 22, 1) )
		if( !get_bits(result.address, 0 ,1) )
			proc->writeHalfword(proc, result.address, get_bits(*proc->r[Rd], 0, 16));
	else
		proc->writeHalfword(proc, result.address, get_bits(*proc->r[Rd], 0, 16));
}
