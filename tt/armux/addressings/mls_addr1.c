#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void mls_addr1(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrMLSReturn *res = result;
	Word U, Rn, immedH, immedL, offset_8;

#ifdef DEBUG
        printf("Ejecutaste un MLS addr1\n");
#endif

	U = get_bits(instruction, 23, 1);
	Rn = get_bits(instruction, 16, 4);
	immedH = get_bits(instruction, 8, 4);
	immedL = get_bits(instruction, 0, 4);
	offset_8 = ( immedH << 4 ) | immedL;
	if( U )
		res->address = *proc->r[Rn] + offset_8;
	else
		res->address = *proc->r[Rn] - offset_8;
}

