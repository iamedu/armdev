#ifndef _ADDRESSING_H
#define _ADDRESSING_H

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

#include <armux/processor.h>
#include <armux/instruction.h>

#define DP_ADDRESSING_NUMBER  10
#define LS_ADDRESSING_NUMBER  6
#define LSM_ADDRESSING_NUMBER 4

static ARMInst **dp_addr_modes;
static ARMInst **ls_addr_modes;
static ARMInst **lsm_addr_modes;

/* Helper Functions */
ARMInst **dp_addressing_dict();
ARMInst **ls_addressing_dict();
ARMInst **lsm_addressing_dict();

typedef struct {
	int shifter_carry_out;
	int shifter_operand;
} DPAddrResult;

typedef struct {
	int start_address;
	int end_address;
} LSMAddrResult;

DPAddrResult *dpaddressingmode1_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode2_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode3_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode4_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode5_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode6_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode7_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode8_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode9_inst(int, ARMProc *);
DPAddrResult *dpaddressingmode10_inst(int, ARMProc *);

int lsaddressingmode1_inst(int, ARMProc *);
int lsaddressingmode2_inst(int, ARMProc *);
int lsaddressingmode3_inst(int, ARMProc *);
int lsaddressingmode4_inst(int, ARMProc *);
int lsaddressingmode5_inst(int, ARMProc *);
int lsaddressingmode6_inst(int, ARMProc *);

LSMAddrResult *lsmaddressingmode1_inst(int, ARMProc *);
LSMAddrResult *lsmaddressingmode2_inst(int, ARMProc *);
LSMAddrResult *lsmaddressingmode3_inst(int, ARMProc *);
LSMAddrResult *lsmaddressingmode4_inst(int, ARMProc *);

#endif

