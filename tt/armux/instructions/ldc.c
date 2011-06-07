#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void ldc_inst(ARMProc *proc, UWord instruction) {
        printf("Ejecutaste un ldc\n");
	//Instrucciones de LSC
	ARMAddr *modes = addr_modes_lsc();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
	ARMCoprocessorInterface *cpro;
	Word cp_num;
	Word memory;
	cp_num = get_bits(instruction,8,4);
	mode = fetch_addr(modes, instruction);
 	cpro = 	proc->coprocessors[cp_num];
	if(mode != NULL)
		mode->execute(proc, instruction, &result);
	
	if(cond(proc, instruction)){
         	result.address = result.start_address;
		memory = readWord(proc,result.address);
		cpro->sendOperation(cpro,memory);
		while(result.address < result.end_address){
			result.address = result.address + 4;
			memory = readWord(proc,result.address);
			cpro->sendOperation(cpro,memory);
		}	
		       
	}
	if(result.address != result.end_address)
		exit(0);
}

