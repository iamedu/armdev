#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void cmp_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un cmp\n");
#endif
	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	ARMAddrDPReturn result;

        Word S;
        Word Rn;
        Word Rd;
	Word borrow;
        Word alu_out;

        mode = fetch_addr(modes, instruction);

        if(mode != NULL)
                mode->execute(proc, instruction, &result);
        if(!cond(proc,instruction))
                return;
        S =  get_bits(instruction,20,1);
        Rn = get_bits(instruction,16,4);
        Rd = get_bits(instruction,12,4);

        alu_out = SubWithBorrow(*proc->r[Rn],result.shifter_operand,&borrow);

        set_status(proc, status_n, get_bits(alu_out,31,1));
        set_status(proc, status_z, alu_out == 0);
        set_status(proc, status_c, !borrow);
        set_status(proc, status_v, (get_bits(*proc->r[Rn], 31, 1) != 
	                            get_bits(result.shifter_operand, 31, 1)) &&
				   (get_bits(result.shifter_operand, 31, 1) ==
				    get_bits(alu_out, 31, 1)));

}

