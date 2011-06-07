#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void bkpt_inst(ARMProc *proc, UWord instruction) {
	int immed_16;
	int immed_4;
	int immed_12;

	immed_4 = get_bits(instruction, 0, 4);
	immed_12 = get_bits(instruction, 8, 12);

	immed_16 = immed_4 | ( (immed_12 << 4) & 0xfff0 );

	printf("bkpt: %d\n", immed_16);

	pauseExecution(proc, proc->thread);
}

