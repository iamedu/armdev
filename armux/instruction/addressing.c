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
#include <armux/processor.h>
#include <armux/addressing.h>
#include <armux/utils.h>
#include <stdlib.h>

DPAddrResult *dpaddressingmode1_inst(int inst, ARMProc *proc) {
	int rotate_imm;
	int immed_8;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;

	rotate_imm = getbits(inst, 8, 4);
	immed_8    = getbits(inst, 0, 8);
	shifter_operand = ror(immed_8, rotate_imm * 2);
	if(rotate_imm == 0)
		shifter_carry_out = read_status(proc, CPSR_C);
	else
		shifter_carry_out = getbit(shifter_operand, 31);
	result = malloc(sizeof(DPAddrResult));
	result->shifter_carry_out = shifter_carry_out;
	result->shifter_operand   = shifter_operand;
	return result;
}

DPAddrResult *dpaddressingmode2_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int **reg;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;

	reg = &proc->r0;
	reg += rm;

	shifter_operand   = **reg;
	shifter_carry_out = read_status(proc, CPSR_C);

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode3_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int shift_imm = getbits(inst, 7, 5);
	int **reg;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;

	reg = &proc->r0;
	reg += rm;

	if(shift_imm == 0) {
		shifter_operand = **reg;
		shifter_carry_out = read_status(proc, CPSR_C);
	} else {
		shifter_operand = (**reg) << shift_imm;
		shifter_carry_out = getbit(**reg, 32 - shift_imm);
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode4_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int rs = getbits(inst, 8, 4);
	int **reg1;
	int **reg2;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;

	reg1 = &proc->r0;
	reg1 += rm;

	reg2 = &proc->r0;
	reg2 += rs;

	if((**reg2) == 0) {
		shifter_operand   = **reg1;
		shifter_carry_out = read_status(proc, CPSR_C);
	} else if((**reg2) < 32) {
		shifter_operand = (**reg1) << (**reg2);
		shifter_carry_out = getbit(**reg1, 32 - (**reg2));
	} else if((**reg2) == 32) {
		shifter_operand = 0;
		shifter_carry_out = getbit(**reg1, 0);
	} else {
		shifter_operand = 0;
		shifter_carry_out = 0;
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode5_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int shift_imm = getbits(inst, 7, 5);
	int **reg;
	int shifter_operand;
	int shifter_carry_out;
	unsigned int operand;
	DPAddrResult *result;

	reg = &proc->r0;
	reg += rm;

	if(shift_imm == 0) {
		shifter_operand = **reg;
		shifter_carry_out = getbit(**reg, 31);
	} else {
		operand = **reg;
		shifter_operand = operand >> shift_imm;
		shifter_carry_out = getbit(**reg, shift_imm - 1);
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode6_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int rs = getbits(inst, 8, 4);
	int **reg1;
	int **reg2;
	int shifter_operand;
	int shifter_carry_out;
	unsigned int operand;
	DPAddrResult *result;

	reg1 = &proc->r0;
	reg1 += rm;

	reg2 = &proc->r0;
	reg2 += rs;

	if((**reg2) == 0) {
		shifter_operand   = **reg1;
		shifter_carry_out = read_status(proc, CPSR_C);
	} else if((**reg2) < 32) {
		operand = **reg1;
		shifter_operand = operand >> (**reg2);
		shifter_carry_out = getbit(**reg1, (**reg2) - 1);
	} else if((**reg2) == 32) {
		shifter_operand = 0;
		shifter_carry_out = getbit(**reg1, 1);
	} else {
		shifter_operand = 0;
		shifter_carry_out = 0;
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode7_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int shift_imm = getbits(inst, 7, 5);
	int **reg;
	int shifter_operand;
	int shifter_carry_out;
	int operand;
	DPAddrResult *result;

	reg = &proc->r0;
	reg += rm;

	if(shift_imm == 0) {
		if(getbit(**reg, 31) == 0) {
			shifter_operand   = 0;
			shifter_carry_out = 0;
		} else {
			shifter_operand = 0xffffffff;
			shifter_carry_out = 1;
		}
	} else {
		operand = **reg;
		shifter_operand = operand >> shift_imm;
		shifter_carry_out = getbit(**reg, shift_imm - 1);
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode8_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int rs = getbits(inst, 8, 4);
	int **reg1;
	int **reg2;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;
	int operand;

	reg1 = &proc->r0;
	reg1 += rm;

	reg2 = &proc->r0;
	reg2 += rs;

	if((**reg2) == 0) {
		shifter_operand   = **reg1;
		shifter_carry_out = read_status(proc, CPSR_C);
	} else if((**reg2) < 32) {
		operand = **reg1;
		shifter_operand = operand >> (**reg2);
		shifter_carry_out = getbit(**reg1, 32 - (**reg2));
	} else {
		if(getbit(**reg1, 31) == 0) {
			shifter_operand = 0;
			shifter_carry_out = 0;
		} else {
			shifter_operand = 0xffffffff;
			shifter_carry_out = 1;
		}
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode9_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int shift_imm = getbits(inst, 7, 5);
	int **reg;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;
	unsigned int operand1;
	unsigned int operand2;

	reg = &proc->r0;
	reg += rm;

	if(shift_imm == 0) {
		operand1 = read_status(proc, CPSR_C) << 31;
		operand2 = (**reg) >> 1;
		shifter_operand = operand1 | operand2;
		shifter_carry_out = getbit(**reg, 0);
	} else {
		shifter_operand = ror(**reg, shift_imm);
		shifter_carry_out = getbit(**reg, shift_imm - 1);
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

DPAddrResult *dpaddressingmode10_inst(int inst, ARMProc *proc) {
	int rm = getbits(inst, 0, 4);
	int rs = getbits(inst, 8, 4);
	int **reg1;
	int **reg2;
	int rs_val1;
	int rs_val2;
	int shifter_operand;
	int shifter_carry_out;
	DPAddrResult *result;

	reg1 = &proc->r0;
	reg1 += rm;

	reg2 = &proc->r0;
	reg2 += rs;

	rs_val1 = getbits(**reg2, 0, 8);
	rs_val2 = getbits(**reg2, 0, 5);

	if(rs_val1 == 0) {
		shifter_operand = **reg1;
		shifter_carry_out = read_status(proc, CPSR_C);
	} else if(rs_val2 == 0) {
		shifter_operand = **reg1;
		shifter_carry_out = getbit(**reg1, 31);
	} else {
		shifter_operand = ror(**reg1, **reg2);
		shifter_carry_out = getbit(**reg1, (**reg2) - 1);
	}

	result = malloc(sizeof(DPAddrResult));
        result->shifter_carry_out = shifter_carry_out;
        result->shifter_operand   = shifter_operand;
        return result;
}

int lsaddressingmode1_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int **rn_ptr;
	int offset_12;
	int address;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	offset_12 = getbits(inst, 0, 12);
	if(u) {
		address = **rn_ptr + offset_12;
	} else {
		address = **rn_ptr - offset_12;
	}
	return address;
}

int lsaddressingmode2_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int rm;
	int **rn_ptr;
	int **rm_ptr;
	int address;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rm = getbits(inst, 0, 4);
	rm_ptr = &proc->r0;
	rm_ptr += rm;

	if(u) {
		address = (**rn_ptr) + (**rm_ptr);
	} else {
		address = (**rn_ptr) - (**rm_ptr);
	}
	return address;
}

int lsaddressingmode3_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int rm;
	int **rn_ptr;
	int **rm_ptr;
	int address;
	int shift;
	int shift_imm;
	int index;
	unsigned int operand_logic;
	int operand_arithmetic;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rm = getbits(inst, 0, 4);
	rm_ptr = &proc->r0;
	rm_ptr += rm;

	shift = getbits(inst, 5, 2);
	shift_imm = getbit(7, 5);

	if(shift == 0) { //LSL
		index = (**rm_ptr) << shift_imm;
	} else if(shift == 1) { //LSR
		if(shift_imm == 0) {
			index = 0;
		} else {
			operand_logic = **rm_ptr;
			operand_logic >>= shift_imm;
			index = operand_logic;
		}
	} else if(shift == 2) {	//ASR
		if(shift_imm == 0) {
			if(getbit(**rm_ptr, 31) == 1) {
				index = 0xffffffff;
			} else {
				index = 0;
			}
		} else {
			operand_arithmetic = **rm_ptr;
			operand_arithmetic >>= shift_imm;
			index = operand_arithmetic;
		}
	} else {
		if(shift_imm = 0) {
			operand_logic = **rm_ptr;
			index = read_status(proc, CPSR_C << 31) |
				(operand_logic >> 1);
		} else {
			index = ror(**rm_ptr, shift_imm);
		}
	}
	
	if(u) {
		address = (**rn_ptr) + index;
	} else {
		address = (**rn_ptr) - index;
	}
	return address;
}

int lsaddressingmode4_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int **rn_ptr;
	int offset_12;
	int address;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	offset_12 = getbits(inst, 0, 12);
	if(u) {
		address = **rn_ptr + offset_12;
	} else {
		address = **rn_ptr - offset_12;
	}

	if(check_condition(proc, inst)) {
		**rn_ptr = address;
	}

	return address;
}

int lsaddressingmode5_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int rm;
	int **rn_ptr;
	int **rm_ptr;
	int address;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rm = getbits(inst, 0, 4);
	rm_ptr = &proc->r0;
	rm_ptr += rm;

	if(u) {
		address = (**rn_ptr) + (**rm_ptr);
	} else {
		address = (**rn_ptr) - (**rm_ptr);
	}

	if(check_condition(proc, inst)) {
		**rn_ptr = address;
	}

	return address;
}

int lsaddressingmode6_inst(int inst, ARMProc *proc) {
	int u;
	int rn;
	int rm;
	int **rn_ptr;
	int **rm_ptr;
	int address;
	int shift;
	int shift_imm;
	int index;
	unsigned int operand_logic;
	int operand_arithmetic;

	u = getbit(inst, 23);
	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	rm = getbits(inst, 0, 4);
	rm_ptr = &proc->r0;
	rm_ptr += rm;

	shift = getbits(inst, 5, 2);
	shift_imm = getbit(7, 5);

	if(shift == 0) { //LSL
		index = (**rm_ptr) << shift_imm;
	} else if(shift == 1) { //LSR
		if(shift_imm == 0) {
			index = 0;
		} else {
			operand_logic = **rm_ptr;
			operand_logic >>= shift_imm;
			index = operand_logic;
		}
	} else if(shift == 2) {	//ASR
		if(shift_imm == 0) {
			if(getbit(**rm_ptr, 31) == 1) {
				index = 0xffffffff;
			} else {
				index = 0;
			}
		} else {
			operand_arithmetic = **rm_ptr;
			operand_arithmetic >>= shift_imm;
			index = operand_arithmetic;
		}
	} else {
		if(shift_imm = 0) {
			operand_logic = **rm_ptr;
			index = read_status(proc, CPSR_C << 31) |
				(operand_logic >> 1);
		} else {
			index = ror(**rm_ptr, shift_imm);
		}
	}
	
	if(u) {
		address = (**rn_ptr) + index;
	} else {
		address = (**rn_ptr) - index;
	}

	if(check_condition(proc, inst)) {
		**rn_ptr = address;
	}

	return address;
}

LSMAddrResult *lsmaddressingmode1_inst(int inst, ARMProc *proc) {
	int rn;
	int **rn_ptr;
	int register_list;
	int start_address;
	int end_address;
	LSMAddrResult *result;

	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	register_list = getbits(inst, 0, 16);

	result = malloc(sizeof(LSMAddrResult));

	start_address = **rn_ptr;
	end_address = **rn_ptr + count_set_bits(register_list) * 4 - 4;

	if(check_condition(proc, inst)) {
		**rn_ptr = end_address + 4;
	}

	result->start_address = start_address;
	result->end_address = end_address;

	return result;
}

LSMAddrResult *lsmaddressingmode2_inst(int inst, ARMProc *proc) {
	int rn;
	int **rn_ptr;
	int register_list;
	int start_address;
	int end_address;
	int w;
	LSMAddrResult *result;

	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	register_list = getbits(inst, 0, 16);
	w = getbit(inst, 21);

	result = malloc(sizeof(LSMAddrResult));

	start_address = **rn_ptr + 4;
	end_address = **rn_ptr + count_set_bits(register_list) * 4;

	if(check_condition(proc, inst) && w) {
		**rn_ptr = end_address;
	}

	result->start_address = start_address;
	result->end_address = end_address;

	return result;
}

LSMAddrResult *lsmaddressingmode3_inst(int inst, ARMProc *proc) {
	int rn;
	int **rn_ptr;
	int register_list;
	int start_address;
	int end_address;
	int w;
	LSMAddrResult *result;

	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	register_list = getbits(inst, 0, 16);
	w = getbit(inst, 21);

	result = malloc(sizeof(LSMAddrResult));

	start_address = **rn_ptr - count_set_bits(register_list) * 4 + 4;
	end_address = **rn_ptr;

	if(check_condition(proc, inst) && w) {
		**rn_ptr = start_address - 4;
	}

	result->start_address = start_address;
	result->end_address = end_address;

	return result;
}

LSMAddrResult *lsmaddressingmode4_inst(int inst, ARMProc *proc) {
	int rn;
	int **rn_ptr;
	int register_list;
	int start_address;
	int end_address;
	int w;
	LSMAddrResult *result;

	rn = getbits(inst, 16, 4);
	rn_ptr = &proc->r0;
	rn_ptr += rn;
	register_list = getbits(inst, 0, 16);
	w = getbit(inst, 21);

	result = malloc(sizeof(LSMAddrResult));

	start_address = **rn_ptr - count_set_bits(register_list) * 4;
	end_address = **rn_ptr - 4;

	if(check_condition(proc, inst) && w) {
		**rn_ptr = start_address;
	}

	result->start_address = start_address;
	result->end_address = end_address;

	return result;
}


ARMInst **dp_addressing_dict() {
	ARMInst **dict = malloc(sizeof(ARMInst *) * 10);
	dict[0] = create_inst(0xe000000, 0x2000000, dpaddressingmode1_inst);
	dict[1] = create_inst(0xe000ff0, 0x0, dpaddressingmode2_inst);
	dict[2] = create_inst(0xe000070, 0x0, dpaddressingmode3_inst);
	dict[3] = create_inst(0xe0000f0, 0x10, dpaddressingmode4_inst);
	dict[4] = create_inst(0xe000070, 0x20, dpaddressingmode5_inst);
	dict[5] = create_inst(0xe0000f0, 0x30, dpaddressingmode6_inst);
	dict[6] = create_inst(0xe000070, 0x40, dpaddressingmode7_inst);
	dict[7] = create_inst(0xe0000f0, 0x50, dpaddressingmode8_inst);
	dict[8] = create_inst(0xe000070, 0x60, dpaddressingmode9_inst);
	dict[9] = create_inst(0xe0000f0, 0x70, dpaddressingmode10_inst);
	return dict;
}

ARMInst **ls_addressing_dict() {
	ARMInst **dict = malloc(sizeof(ARMInst *) * 6);
	dict[1] = create_inst(0xf200000, 0x5000000, lsaddressingmode1_inst);
	dict[0] = create_inst(0xf200ff0, 0x7000000, lsaddressingmode2_inst);
	dict[2] = create_inst(0xf200010, 0x7000000, lsaddressingmode3_inst);
	dict[3] = create_inst(0xf200000, 0x5200000, lsaddressingmode4_inst);
	dict[4] = create_inst(0xf200ff0, 0x7200000, lsaddressingmode5_inst);
	dict[5] = create_inst(0xf200010, 0x7200000, lsaddressingmode6_inst);
	return dict;
}


ARMInst **lsm_addressing_dict() {
	ARMInst **dict = malloc(sizeof(ARMInst *) * 4);
	dict[0] = create_inst(0xf800010, 0x8800000, lsmaddressingmode1_inst);
	dict[1] = create_inst(0xf800010, 0x9800000, lsmaddressingmode2_inst);
	dict[2] = create_inst(0xf800010, 0x8000000, lsmaddressingmode3_inst);
	dict[3] = create_inst(0xf800010, 0x9000000, lsmaddressingmode4_inst);
	return dict;
}

