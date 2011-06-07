#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void swpb_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un swpb\n");
#endif
	Word temp, address, Rm, Rd;
        if( !cond(proc, instruction) )
                return;
	address = *proc->r[get_bits(instruction, 16, 4)];
	Rm = get_bits(instruction, 0, 4);
	Rd = get_bits(instruction, 12, 4);
	temp = proc->readByte(proc, address);
	proc->writeByte(proc, address, get_bits(*proc->r[Rm], 0, 8));
	*proc->r[Rd] = temp;
}

