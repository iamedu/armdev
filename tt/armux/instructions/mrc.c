#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void mrc_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un mrc\n");
	//Instrucciones de LSC
	ARMAddr *modes = addr_modes_lsc();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
	ARMCoprocessorInterface *cpro;
	Word Rd;
	Word cp_num;
	Word data;	
	mode = fetch_addr(modes, instruction);
	cp_num = get_bits(instruction,8,4);
	Rd = get_bits(instruction,12,4);
	cpro =  proc->coprocessors[cp_num];
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
        if(cond(proc, instruction)){
		data = cpro->readOperation(cpro);
		if(*proc->r[Rd] == 15){
			set_status(proc, status_n, get_bits(data,31,1));
	        	set_status(proc, status_z, get_bits(data,30,1));
		        set_status(proc, status_c, get_bits(data,29,1));
        		set_status(proc, status_v, get_bits(data,28,1)); 
		}
		else
			*proc->r[Rd] = data;
	}
}

