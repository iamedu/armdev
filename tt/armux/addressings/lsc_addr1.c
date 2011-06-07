#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>
#include <stdio.h>

void lsc_addr1(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un LSC addr1\n");
#endif
	ARMAddrLSCReturn *res = result;
	Word U = get_bits(instruction,23,1);
	Word Rn = get_bits(instruction,16,4);
	Word offset_8 = get_bits(instruction,0,8);
	if(cond(proc, instruction)){
		if(U == 1){
			res->address = *proc->r[Rn] + offset_8 * 4;
		}
		else{	
			res->address = *proc->r[Rn] - offset_8 * 4;
		} 
        res->start_address = res->address;
	while(1){//TODO EL WHILE
		res->address = res->address + 4;
	}  	
	res->end_address = res->address;
	}
               

}

