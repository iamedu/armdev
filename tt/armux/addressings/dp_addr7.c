#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>
#include <stdio.h>

void dp_addr7(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr7\n");
#endif
	ARMAddrDPReturn *res = result;
        Word shift_imm = get_bits(instruction,7,5);
        Word Rm = get_bits(instruction,0,4);
        if(shift_imm == 0){
                if(get_bits(*proc->r[Rm],31,1) == 0){
                        res->shifter_operand = 0;
                        res->shifter_carry_out = get_bits(*proc->r[Rm],31,1);
                }
                else{
                        res->shifter_operand = 0xFFFFFFFF;
                        res->shifter_carry_out = get_bits(*proc->r[Rm],31,1);
                }
        }
        else{
                res->shifter_operand = *proc->r[Rm] >> shift_imm;//Pendiente arithmetic
                res->shifter_carry_out = get_bits(*proc->r[Rm],shift_imm-1,1);
        }
	
}

