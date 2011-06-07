#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void cps_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un cps\n");
#endif
	Word status_mode, imod, A, I, F, mmod, mode;
	status_mode = get_status(proc, status_m);
	imod = get_bits(instruction, 18, 2);
	A = get_bits(instruction, 8, 1);
	I = get_bits(instruction, 7, 1);
	F = get_bits(instruction, 6, 1);
	mmod = get_bits(instruction, 17, 1);
	mode = get_bits(instruction, 0, 5);
	if( status_mode == mode_fiq || status_mode == mode_irq || status_mode == mode_svc || status_mode == mode_abt || status_mode == mode_und ){
		if( get_bits(imod, 1, 1) ){
			if( A ) set_status(proc, status_a, get_bits(imod, 0, 1) );
			if( I ) set_status(proc, status_i, get_bits(imod, 0, 1) );
			if( F ) set_status(proc, status_f, get_bits(imod, 0, 1) );
		}
		if( mmod )
			set_bits(proc->cpsr, 0, 5, mode);
	}
}

