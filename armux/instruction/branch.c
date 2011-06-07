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
#include <armux/utils.h>

void bl_inst(int inst, ARMProc *proc) {
	int l;
	int signed_immed_24;
	int branch_addr;

	if(!check_condition(proc, inst))
		return;
	l = getbit(inst, 24);
	signed_immed_24 = getbits(inst, 0, 24);

	if(l) {
		*proc->lr = *proc->pc;
	}

	branch_addr = sign_extend(signed_immed_24, 24, 30);

	branch_addr <<= 2;


	*proc->pc += 4 + branch_addr;
}

void bx_inst(int inst, ARMProc *proc) {
}

void blx1_inst(int inst, ARMProc *proc) {
}

void blx2_inst(int inst, ARMProc *proc) {
}


