#include <armux/processor.h>
#include <armux/types.h>
#include <armux/instruction.h>
#include <armux/addressing.h>
#include <armux/utils.h>

#include <stdio.h>

void ldr_inst(ARMProc *proc, UWord instruction) {
#ifdef DEBUG
        printf("Ejecutaste un ldr\n");
#endif
	//Instrucciones de LS
	ARMAddr *modes = addr_modes_ls();
	ARMAddr *mode;
	ARMAddrLSCReturn result;
	ARMCoprocessorInterface *cp15;
        Word data, Rd, cp15_reg1;

        if( !cond(proc, instruction) )
                return;
	mode = fetch_addr(modes, instruction);
	Rd = get_bits(instruction, 12, 4);
	
	if(mode != NULL)
		mode->execute(proc, instruction, &result);


	cp15  = proc->coprocessors[15];
        cp15_reg1 = cp15->readRegister(cp15, 1);
        /*if( !get_bits(cp15_reg1, 22, 1) )
                data = ror32(proc->readWord(proc, result.address), (8 * get_bits(result.address, 0, 1)));
        else*/
                data = proc->readWord(proc, result.address);
        if( Rd == 15 ){
		//if (ARMv5 or above) then
			*proc->r[15] = data & 0xFFFFFFFE;
                        set_status(proc, status_t, get_bits(data, 0 ,1));
		/*
	        else
	                *proc->r[15] = data & 0xFFFFFFFC;
   	        */
	}else
                *proc->r[Rd] = data;
}
