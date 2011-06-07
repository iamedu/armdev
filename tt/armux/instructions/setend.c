#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void setend_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un setend\n");
#endif
	Word E;
	E = get_bits(instruction, 9, 1);
	set_status(proc, status_e, E);
}

