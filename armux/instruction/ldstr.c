/*
 * Copyright 2009 armux authors.
 *
 * This file is part of armux.
 *
 * armux is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * armux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with armux.  If not, see <http://www.gnu.org/licenses/>
 */

#include <armux/addressing.h>
#include <armux/instruction.h>
#include <armux/utils.h>
#include <stdio.h>

void ldrt_inst(int inst, ARMProc *proc) {
}

void ldr_inst(int inst, ARMProc *proc) {
	int i;
	int address;
	int rd;
	int **rd_ptr;
	int (*func)(int, ARMProc *);
	int data;

	if(!check_condition(proc, inst))
                return;

	ls_addr_modes = ls_addressing_dict();

	for(i = 0; i < LS_ADDRESSING_NUMBER; i++) {
                if(test_inst(ls_addr_modes[i], inst)) {
			printf("Addressing mode: %d\n", i);
                        func = ls_addr_modes[i]->execute;
                        address = (*func)(inst, proc);
			break;
                }
        }

	rd = getbits(inst, 12, 4);
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	data = read_mem(proc, address, 4);

	if(rd == 15) {
		**rd_ptr = data & 0xfffffffe;
	} else {
		**rd_ptr = data;
	}
}

void ldrbt_inst(int inst, ARMProc *proc) {
}

void ldrb_inst(int inst, ARMProc *proc) {
	int i;
	int address;
	int (*func)(int, ARMProc *);
	int rd;
	int data;
	int **rd_ptr;

	if(!check_condition(proc, inst))
                return;

	ls_addr_modes = ls_addressing_dict();
	rd = getbits(inst, 12, 4);

	rd_ptr = &proc->r0;
	rd_ptr += rd;

	for(i = 0; i < LS_ADDRESSING_NUMBER; i++) {
                if(test_inst(ls_addr_modes[i], inst)) {
                        func = ls_addr_modes[i]->execute;
                        address = (*func)(inst, proc);
			break;
                }
        }

	data = read_mem(proc, address, 1);
	**rd_ptr = data;
}

void ldrd_inst(int inst, ARMProc *proc) {
}

void ldrh_inst(int inst, ARMProc *proc) {
}

void ldrsb_inst(int inst, ARMProc *proc) {
}

void ldrsh_inst(int inst, ARMProc *proc) {
}

void ldm1_inst(int inst, ARMProc *proc) {
	int i;
	LSMAddrResult *result;
	LSMAddrResult *(*func)(int, ARMProc *);
	int register_list;
	int address;
	int start_address;
	int end_address;
	int value;
	int **reg;

	if(!check_condition(proc, inst))
                return;

	register_list = getbits(inst, 0, 16);
	lsm_addr_modes = lsm_addressing_dict();
	reg = &proc->r0;

	for(i = 0; i < LSM_ADDRESSING_NUMBER; i++) {
                if(test_inst(lsm_addr_modes[i], inst)) {
                        func = lsm_addr_modes[i]->execute;
                        result = (*func)(inst, proc);
			break;
                }
        }

	start_address = result->start_address;
	end_address   = result->end_address;

	address = start_address;

	for(i = 0; i < 15; i++) {
		if(getbit(register_list, i)) {
			**(reg + i) = read_mem(proc, address, 4);
			address += 4;
		}
	}

	if(getbit(register_list, 15)) {
		value = read_mem(proc, address, 4);
		*proc->pc = value & 0xFFFFFFFE;
		address += 4;
	}

	if(end_address != address - 4) {
		fprintf(stderr, "Load memory error");
	}

}

void ldm2_inst(int inst, ARMProc *proc) {
}

void strt_inst(int inst, ARMProc *proc) {
}

void str_inst(int inst, ARMProc *proc) {
	int i;
	int address;
	int rd;
	int **rd_ptr;
	int (*func)(int, ARMProc *);
	int data;

	if(!check_condition(proc, inst))
                return;

	ls_addr_modes = ls_addressing_dict();

	for(i = 0; i < LS_ADDRESSING_NUMBER; i++) {
                if(test_inst(ls_addr_modes[i], inst)) {
                        func = ls_addr_modes[i]->execute;
                        address = (*func)(inst, proc);
			break;
                }
        }

	rd = getbits(inst, 12, 4);
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	write_mem(proc, address, 4, **rd_ptr);
}

void strbt_inst(int inst, ARMProc *proc) {
}

void strb_inst(int inst, ARMProc *proc) {
	int i;
	int address;
	int rd;
	int **rd_ptr;
	int (*func)(int, ARMProc *);
	int data;

	if(!check_condition(proc, inst))
                return;

	ls_addr_modes = ls_addressing_dict();

	for(i = 0; i < LS_ADDRESSING_NUMBER; i++) {
                if(test_inst(ls_addr_modes[i], inst)) {
                        func = ls_addr_modes[i]->execute;
                        address = (*func)(inst, proc);
			break;
                }
        }

	rd = getbits(inst, 12, 4);
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	write_mem(proc, address, 1, getbits(**rd_ptr, 0, 8));
}

void strd_inst(int inst, ARMProc *proc) {
}

void strh_inst(int inst, ARMProc *proc) {
}

void stm1_inst(int inst, ARMProc *proc) {
	int i;
	LSMAddrResult *result;
	LSMAddrResult *(*func)(int, ARMProc *);
	int register_list;
	int address;
	int start_address;
	int end_address;
	int value;
	int **reg;

	if(!check_condition(proc, inst))
                return;

	register_list = getbits(inst, 0, 16);
	lsm_addr_modes = lsm_addressing_dict();
	reg = &proc->r0;

	for(i = 0; i < LSM_ADDRESSING_NUMBER; i++) {
                if(test_inst(lsm_addr_modes[i], inst)) {
                        func = lsm_addr_modes[i]->execute;
                        result = (*func)(inst, proc);
			break;
                }
        }

	start_address = result->start_address;
	end_address   = result->end_address;

	address = start_address;

	for(i = 0; i < 16; i++) {
		if(getbit(register_list, i)) {
			write_mem(proc, address, 4, **(reg + i));
			address += 4;
		}
	}

	if(end_address != address - 4) {
		fprintf(stderr, "Load memory error");
	}
}

void stm2_inst(int inst, ARMProc *proc) {
}


