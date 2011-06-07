#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mrrc_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un mrrc\n");
	//Instrucciones de LSC
	ARMAddr *modes = addr_modes_lsc();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
	ARMCoprocessorInterface *cpro;

        Word Rd;
	Word Rn;
        Word cp_num;
        Word data;

        mode = fetch_addr(modes, instruction);
        cp_num = get_bits(instruction,8,4);
        Rd = get_bits(instruction,12,4);
	Rn = get_bits(instruction,16,4);
        cpro =  proc->coprocessors[cp_num];

        if(mode != NULL)
                mode->execute(proc, instruction, &result);
        if(cond(proc, instruction)){
                 *proc->r[Rd] = cpro->readOperation(cpro);
		 *proc->r[Rn] = cpro->readOperation(cpro);
        }

}

