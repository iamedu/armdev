#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void swp_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un swp\n");
#endif
	if( !cond(proc, instruction) )
                return;	
	ARMCoprocessorInterface *cp15;
	Word cp15_reg1, temp, address, Rm, Rd;
	address = *proc->r[get_bits(instruction, 16, 4)];
	Rm = get_bits(instruction, 0, 4);
	Rd = get_bits(instruction, 12, 4);
	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
	if( !get_bits(cp15_reg1, 22, 1) ){
		temp = ror(proc->readWord(proc, address), 8 * get_bits(address, 0, 2));
		proc->writeWord(proc, address, *proc->r[Rm]);
		*proc->r[Rd] = temp;
	}else{
		temp = proc->readWord(proc, address);
		proc->writeWord(proc, address, *proc->r[Rm]);
		*proc->r[Rd] = temp;
	}	
}

