#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void ls_addr9(ARMProc *proc, UWord instruction, void *result) {
	ARMAddrLSReturn *res = result;
        Word shift, shift_imm, Rm, index, U, Rn;

#ifdef DEBUG
        printf("Ejecutaste un LS addr9\n");
#endif

        shift = get_bits(instruction, 5, 2);
        shift_imm = get_bits(instruction, 7, 5);
        Rm = get_bits(instruction, 0, 4);
        U = get_bits(instruction, 23, 1);
        Rn = get_bits(instruction, 16, 4);
	res->address = *proc->r[Rn];
	switch(shift){
                case 0:
                        index = *proc->r[Rm] << shift_imm;
                        break;
                case 1:
                        if(shift_imm == 0)
                                index = 0;
                        else
                                index = *proc->r[Rm] >> shift_imm;
                        break;
                case 2:
                        if(shift_imm == 0)
                                if(get_bits(Rm, 31, 1) == 1)
                                        index = 0xffffffff;
                                else
                                        index = 0;
                        else
                                index = asr32(*proc->r[Rm], shift_imm);
                        break;
                case 3:
                        if(shift_imm == 0)
                                index = (get_bits(*proc->cpsr,29,1) << 31) | (*proc->r[Rm] >> 1);
                        else
                                index = ror32(Rm, shift_imm);
                        break;
                default:
                        break;
        }

        if( cond(proc, instruction) )
        	if( U )
                	*proc->r[Rn] += index;
	        else
	                *proc->r[Rn] -= index;
}

