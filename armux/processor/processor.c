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

#include <stdlib.h>
#include <stdio.h>
#include <armux/utils.h>
#include <armux/processor.h>

int  read_status(ARMProc *proc, int flag) {
	int num_bits = 1;
	if(flag == CPSR_M)
		num_bits = 5;
	else if(flag == CPSR_GE)
		num_bits = 4;
	return getbits(*proc->cpsr, flag, num_bits);
}

void write_status(ARMProc *proc, int flag, int value) {
	int num_bits = 1;
	if(flag == CPSR_M)
		num_bits = 5;
	else if(flag == CPSR_GE)
		num_bits = 4;
	setbits(*proc->cpsr, value, flag, num_bits);
}

ARMProc *create_proc() {
	ARMProc *proc = malloc(sizeof(ARMProc));
	int **reg;
	int i;

	proc->cpsr = &proc->cpsr_reg;
	proc->pc   = &proc->pc_reg;
	proc->r15  = proc->pc;

	*proc->cpsr = 0;
	*proc->pc   = 0;

	reg = &proc->r0;
	for(i = 0; i < 8; i++) {
		*reg = &proc->g_regs[i];
		proc->g_regs[i] = 0;
		reg++;
	}

	change_mode(proc, MODE_SVC);

	return proc;
}

void change_mode(ARMProc *proc, int mode) {
	int **reg;
	int i;
	switch(mode) {
		case MODE_USR:
		case MODE_SYS:
			reg = &proc->r8;
			for(i = 8; i < 15; i++) {
				*reg = &proc->s_regs[i - 8];
				proc->s_regs[i - 8] = 0;
				reg++;
			}
		break;
		case MODE_FIQ:
			reg = &proc->r8;
			for(i = 8; i < 15; i++) {
				*reg = &proc->fiq_regs[i - 8];
				proc->fiq_regs[i - 8] = 0;
				reg++;
			}
			proc->spsr = &proc->fiq_regs[7];
		break;
		case MODE_IRQ:
			reg = &proc->r8;
			for(i = 8; i < 13; i++) {
				*reg = &proc->s_regs[i - 8];
				proc->s_regs[i - 8] = 0;
				reg++;
			}
			reg = &proc->r13;
			for(i = 13; i < 15; i++) {
				*reg = &proc->irq_regs[i - 13];
				proc->irq_regs[i - 13] = 0;
				reg++;
			}
			proc->spsr = &proc->irq_regs[3];
		break;
		case MODE_SVC:
			reg = &proc->r8;
			for(i = 8; i < 13; i++) {
				*reg = &proc->s_regs[i - 8];
				proc->s_regs[i - 8] = 0;
				reg++;
			}
			reg = &proc->r13;
			for(i = 13; i < 15; i++) {
				*reg = &proc->svc_regs[i - 13];
				proc->svc_regs[i - 13] = 0;
				reg++;
			}
			proc->spsr = &proc->svc_regs[3];
		break;
		case MODE_ABT:
			reg = &proc->r8;
			for(i = 8; i < 13; i++) {
				*reg = &proc->s_regs[i - 8];
				proc->s_regs[i - 8] = 0;
				reg++;
			}
			reg = &proc->r13;
			for(i = 13; i < 15; i++) {
				*reg = &proc->abt_regs[i - 13];
				proc->abt_regs[i - 13] = 0;
				reg++;
			}
			proc->spsr = &proc->abt_regs[3];
		break;
		case MODE_UND:
			reg = &proc->r8;
			for(i = 8; i < 13; i++) {
				*reg = &proc->s_regs[i - 8];
				proc->s_regs[i - 8] = 0;
				reg++;
			}
			reg = &proc->r13;
			for(i = 13; i < 15; i++) {
				*reg = &proc->und_regs[i - 13];
				proc->und_regs[i - 13] = 0;
				reg++;
			}
			proc->spsr = &proc->und_regs[3];
		break;
		default:
			//Attempt to change to unknown mode
		break;
	}
	proc->lr = proc->r14;
	proc->sp = proc->r13;

	//5 becase mode is of that length
	*proc->cpsr = setbits(*proc->cpsr, mode, CPSR_M, 5);
}

int fetch(ARMProc *proc) {
	int addr = *proc->pc;
	int num;
	int inst = 0;
	int i;
	*proc->pc = *proc->pc + 4;

	inst = read_mem(proc, addr, 4);

	return inst;
}

int read_mem(ARMProc *proc, unsigned int addr, int num_bytes) {
	int i;
	ARMMemEntry *entry;

	for(i = 0; i < proc->memory->size; i++) {
		entry = proc->memory->entries[i];
		if(addr >= entry->location &&
		   addr <  (entry->location + entry->size)) {
			return (*entry->read_memory)(entry, addr, 
							num_bytes);
		}
	}
}

void write_mem(ARMProc * proc, unsigned int addr, int num_bytes, int value) {
	int i;
	ARMMemEntry *entry;

	for(i = 0; i < proc->memory->size; i++) {
		entry = proc->memory->entries[i];
		if(addr >= entry->location &&
		   addr <  (entry->location + entry->size)) {
			(*entry->write_memory)(entry, addr, num_bytes,
							value);
			break;
		}
	}

}

