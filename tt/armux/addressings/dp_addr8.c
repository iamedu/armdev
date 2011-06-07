#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void dp_addr8(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un DP addr8\n");
#endif
	ARMAddrDPReturn *res = result;
        Word Rm = get_bits(instruction,0,4);
        Word Cflag = get_bits(*proc->cpsr,29,1);
        Word Rs = get_bits(instruction,8,4);
        if(get_bits(*proc->r[Rs],0,8) == 0){
                res->shifter_operand = *proc->r[Rm];
                res->shifter_carry_out = Cflag;
        }else if(get_bits(*proc->r[Rs],0,8) < 32){
                res->shifter_operand = *proc->r[Rm] >> get_bits(*proc->r[Rs],0,8);//Pendiente arithmetic
                res->shifter_carry_out = get_bits(*proc->r[Rm],get_bits(*proc->r[Rs],0,8)-1,1);
        }else if(get_bits(*proc->r[Rm],31,1) == 0){
                res->shifter_operand = 0;
                res->shifter_carry_out = get_bits(*proc->r[Rm],31,1);
        }else{
                res->shifter_operand = 0xFFFFFFFF;
                res->shifter_carry_out = get_bits(*proc->r[Rm],31,1);
        }

}

