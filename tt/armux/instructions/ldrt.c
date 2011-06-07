#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void ldrt_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldrt\n");
#endif
	//Instrucciones de LS
	ARMAddr *modes = addr_modes_ls();
	ARMAddr *mode;
	ARMAddrLSReturn result;
	ARMCoprocessorInterface *cp15;
        Word data, cp15_reg1, Rd;
	
	if( !cond(proc, instruction) )
                return;
	mode = fetch_addr(modes, instruction);
	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
        Rd = get_bits(instruction, 12, 4);
        if( !get_bits(cp15_reg1, 22, 1) )
		*proc->r[Rd] = ror( proc->readWord(proc, result.address), ( 8 * get_bits(result.address,0,2) ) );
	else
		*proc->r[Rd] = proc->readWord(proc, result.address);
}
