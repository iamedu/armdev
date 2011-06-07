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

#include <armux/instruction.h>
#include <armux/addressing.h>
#include <armux/processor.h>
#include <armux/utils.h>
#include <stdlib.h>

void and_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S = getbit(inst, 20);
	int I = getbit(inst, 25);
	int rd = getbits(inst, 12, 4);
	int rn = getbits(inst, 16, 4);
	int **rd_ptr;
	int **rn_ptr;
	int i;

	rd_ptr = &proc->r0;
	rd_ptr += rd;
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	**rd_ptr = **rn_ptr & shifter_operand;

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}

}

void eor_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int rd;
	int rn;
	int **rd_ptr;
	int **rn_ptr;
	int i;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	**rd_ptr = (**rn_ptr) ^ shifter_operand;

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}
}

void sub_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int rd;
	int rn;
	int **rd_ptr;
	int **rn_ptr;
	int i;
	int borrow;
	int v;
	int last_rd;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	**rd_ptr = sub_with_borrow(**rn_ptr, shifter_operand, &borrow);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, borrow == 0);
		write_status(proc, CPSR_V, v);
	}
}

void rsb_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int rd;
	int rn;
	int **rd_ptr;
	int **rn_ptr;
	int i;
	int borrow;
	int v;
	int last_rd;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	**rd_ptr = sub_with_borrow(shifter_operand, **rn_ptr, &borrow);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, borrow == 0);
		write_status(proc, CPSR_V, v);
	}
}

void add_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int rd;
	int rn;
	int **rn_ptr;
	int **rd_ptr;
	int i;
	int carry;
	int last_rd;
	int v;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	**rd_ptr = add_with_carry(**rn_ptr, shifter_operand, &carry);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, carry);
		write_status(proc, CPSR_V, v);
	}
}

void adc_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int C;
	int rd;
	int rn;
	int **rn_ptr;
	int **rd_ptr;
	int i;
	int carry;
	int last_rd;
	int v;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	C = read_status(proc, CPSR_C);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	//TODO: Check how adc should be implemented
	**rd_ptr = add_with_carry(**rn_ptr + shifter_operand, C, &carry);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, carry);
		write_status(proc, CPSR_V, v);
	}
}

void sbc_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int C;
	int rd;
	int rn;
	int **rn_ptr;
	int **rd_ptr;
	int i;
	int borrow;
	int last_rd;
	int v;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	C = read_status(proc, CPSR_C);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	//TODO: Check how adc should be implemented
	**rd_ptr = sub_with_borrow(**rn_ptr - shifter_operand, C, &borrow);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, borrow == 0);
		write_status(proc, CPSR_V, v);
	}
}

void rsc_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int C;
	int rd;
	int rn;
	int **rn_ptr;
	int **rd_ptr;
	int i;
	int borrow;
	int last_rd;
	int v;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	C = read_status(proc, CPSR_C);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	last_rd = **rd_ptr;

	//TODO: Check how adc should be implemented
	**rd_ptr = sub_with_borrow(shifter_operand - **rn_ptr, C, &borrow);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		if(getbit(last_rd, 31) == 0 && getbit(**rd_ptr, 31) == 1)
			v = 1;
		else
			v = 0;
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, borrow == 0);
		write_status(proc, CPSR_V, v);
	}
}

void tst_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int rn = getbits(inst, 16, 4);
	int **rn_ptr;
	int i;
	int alu_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	alu_out = **rn_ptr & shifter_operand;

	write_status(proc, CPSR_N, getbit(alu_out, 31));
	write_status(proc, CPSR_Z, alu_out == 0);
	write_status(proc, CPSR_C, shifter_carry_out);
}

void teq_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int rn = getbits(inst, 16, 4);
	int **rn_ptr;
	int i;
	int alu_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	alu_out = **rn_ptr ^ shifter_operand;

	write_status(proc, CPSR_N, getbit(alu_out, 31));
	write_status(proc, CPSR_Z, alu_out == 0);
	write_status(proc, CPSR_C, shifter_carry_out);
}

void cmp_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int rn = getbits(inst, 16, 4);
	int **rn_ptr;
	int i;
	int alu_out;
	int borrow;
	int v;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	alu_out = sub_with_borrow(**rn_ptr, shifter_operand, &borrow);

	if(getbit(**rn_ptr, 31) == 0 && getbit(alu_out, 31) == 1)
		v = 1;
	else
		v = 0;
	write_status(proc, CPSR_N, getbit(alu_out, 31));
	write_status(proc, CPSR_Z, alu_out == 0);
	write_status(proc, CPSR_C, borrow == 0);
	write_status(proc, CPSR_V, v);
}

void cmn_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int rn = getbits(inst, 16, 4);
	int **rn_ptr;
	int i;
	int alu_out;
	int carry;
	int v;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	alu_out = add_with_carry(**rn_ptr, shifter_operand, &carry);

	if(getbit(**rn_ptr, 31) == 0 && getbit(alu_out, 31) == 1)
		v = 1;
	else
		v = 0;
	write_status(proc, CPSR_N, getbit(alu_out, 31));
	write_status(proc, CPSR_Z, alu_out == 0);
	write_status(proc, CPSR_C, carry);
	write_status(proc, CPSR_V, v);
}

void orr_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S;
	int I;
	int rd;
	int rn;
	int **rd_ptr;
	int **rn_ptr;
	int i;

	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	S = getbit(inst, 20);
	I = getbit(inst, 25);
	rn = getbits(inst, 16, 4);
	rd = getbits(inst, 12, 4);
	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rd_ptr = &proc->r0;
	rd_ptr += rd;

	**rd_ptr = (**rn_ptr) | shifter_operand;

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}
}

void mov_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	int shifter_operand;
	int shifter_carry_out;
	int S = getbit(inst, 20);
	int I = getbit(inst, 25);
	int rd = getbits(inst, 12, 4);
	int **rd_ptr;
	int i;

	rd_ptr = &proc->r0;
	rd_ptr += rd;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	**rd_ptr = shifter_operand;

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}
}

void bic_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	unsigned int shifter_operand;
	unsigned int shifter_carry_out;
	int S = getbit(inst, 20);
	int I = getbit(inst, 25);
	int rd = getbits(inst, 12, 4);
	int rn = getbits(inst, 16, 4);
	int **rd_ptr;
	int **rn_ptr;
	int i;

	rd_ptr = &proc->r0;
	rd_ptr += rd;
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	**rd_ptr = **rn_ptr & (~shifter_operand);

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}
}

void mvn_inst(int inst, ARMProc *proc) {
	DPAddrResult *operands;
	unsigned int shifter_operand;
	int shifter_carry_out;
	int S = getbit(inst, 20);
	int I = getbit(inst, 25);
	int rd = getbits(inst, 12, 4);
	int **rd_ptr;
	int i;

	rd_ptr = &proc->r0;
	rd_ptr += rd;
	
	DPAddrResult *(*func)(int, ARMProc *);

	if(!check_condition(proc, inst))
		return;

	dp_addr_modes = dp_addressing_dict();

	for(i = 0; i < DP_ADDRESSING_NUMBER; i++) {
		if(test_inst(dp_addr_modes[i], inst)) {
			func = dp_addr_modes[i]->execute;
			operands = (*func)(inst, proc);
		}
	}

	shifter_operand = operands->shifter_operand;
	shifter_carry_out = operands->shifter_carry_out;

	**rd_ptr = ~shifter_operand;

	if(S && rd == 15) {
		if(proc->spsr != NULL) {
			*proc->cpsr = *proc->spsr;
		}
	} else if(S) {
		write_status(proc, CPSR_N, getbit(**rd_ptr, 31));
		write_status(proc, CPSR_Z, (**rd_ptr) == 0);
		write_status(proc, CPSR_C, shifter_carry_out);
	}
}

