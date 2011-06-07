#include <armux/processor.h>
#include <armux/types.h>
#include <armux/addressing.h>

#include <stdio.h>

void lsc_addr4(ARMProc *proc, UWord instruction, void *result) {
#ifdef DEBUG
        printf("Ejecutaste un LSC addr4\n");
#endif
        ARMAddrLSCReturn *res = result;
        Word U = get_bits(instruction,23,1);
        Word Rn = get_bits(instruction,16,4);
        Word offset_8 = get_bits(instruction,0,8);
        if(cond(proc, instruction)){
                res->start_address = *proc->r[Rn];
                res->address = res->start_address;
                while(1){//TODO EL WHILE
                        res->address = res->address + 4;
                }
                res->end_address = res->address;
        }

}

