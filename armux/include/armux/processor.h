#ifndef _PROCESSOR_H
#define _PROCESSOR_H

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

#include <armux/memory.h>

#define CPSR_N  31
#define CPSR_Z  30
#define CPSR_C  29
#define CPSR_V  28
#define CPSR_Q  27
#define CPSR_J  24
#define CPSR_GE 16
#define CPSR_E  9
#define CPSR_A  8
#define CPSR_I  7
#define CPSR_F  6
#define CPSR_T  5
#define CPSR_M  0

#define MODE_USR 0x10
#define MODE_FIQ 0x11
#define MODE_IRQ 0x12
#define MODE_SVC 0x13
#define MODE_ABT 0x17
#define MODE_UND 0x1b
#define MODE_SYS 0x1f

typedef struct {
	int *r0;
	int *r1;
	int *r2;
	int *r3;
	int *r4;
	int *r5;
	int *r6;
	int *r7;
	int *r8;
	int *r9;
	int *r10;
	int *r11;
	int *r12;
	int *r13;
	int *r14;
	int *r15;
	int *pc;
	int *lr;
	int *sp;
	int *cpsr;
	int *spsr;
	int g_regs[8];   //general registers
	int s_regs[7];   //System and user registers
	int svc_regs[3]; //Supervisor registers
	int abt_regs[3]; //Abort registers
	int und_regs[3]; //Undefined registers
	int irq_regs[3]; //Interrupt registers
	int fiq_regs[8]; //Fast Interrupt registers
	int pc_reg;
	int cpsr_reg;
	ARMMem *memory;
} ARMProc;

int  read_status(ARMProc *, int);
void write_status(ARMProc *, int, int);

ARMProc *create_proc();
void change_mode(ARMProc *, int);

int fetch(ARMProc *);
int read_mem(ARMProc *, unsigned int, int);
void write_mem(ARMProc *, unsigned int, int, int);

#endif

