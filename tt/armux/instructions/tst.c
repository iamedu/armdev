#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>

#include <stdio.h>

void tst_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un tst\n");
#endif
	//Instrucciones de DP
	ARMAddr *modes = addr_modes_dp();
	ARMAddr *mode;
	ARMAddrDPReturn result;
	Word alu_out;
        Word Rn;
        mode = fetch_addr(modes, instruction);

        if(mode != NULL)
                mode->execute(proc, instruction, &result);

        Rn = get_bits(instruction,16,4);

        if(cond(proc,instruction)){
                alu_out = *proc->r[Rn] & result.shifter_operand;
                set_status(proc,status_n,get_bits(alu_out,31,1));
                set_status(proc,status_z,alu_out == 0);
                set_status(proc,status_c,result.shifter_carry_out);
        }

}

