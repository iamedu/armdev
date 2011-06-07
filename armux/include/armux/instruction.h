#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

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

#define INSTRUCTION_NUMBER 64

typedef struct _ARMInst {
	unsigned int bitmask;
	unsigned int testmask;
	void (*execute)(int, ARMProc *);
} ARMInst;

static ARMInst **insts;

/* Helper Functions */
ARMInst *create_inst(int, int, void *);
ARMInst **inst_dict();
int test_inst(ARMInst *, int);
int check_condition(ARMProc *, int);

/* Instruction functions */
//Multiplication instructions
void mla_inst(int, ARMProc *);
void mul_inst(int, ARMProc *);
void smla_inst(int, ARMProc *);
void smlal_inst(int, ARMProc *);
void smlalxy_inst(int, ARMProc *);
void smlawy_inst(int, ARMProc *);
void smull_inst(int, ARMProc *);
void smulwy_inst(int, ARMProc *);
void smulxy_inst(int, ARMProc *);
void umlal_inst(int, ARMProc *);
void umull_inst(int, ARMProc *);
//Miscelaneous instructions
void clz_inst(int, ARMProc *);
void swp_inst(int, ARMProc *);
void swpb_inst(int, ARMProc *);
void mrs_inst(int, ARMProc *);
void msr_inst(int, ARMProc *);
void msri_inst(int, ARMProc *);
//Branch instructions
void bl_inst(int, ARMProc *);
void bx_inst(int, ARMProc *);
void blx1_inst(int, ARMProc *);
void blx2_inst(int, ARMProc *);
//Memory instructions
void ldrt_inst(int, ARMProc *);
void ldr_inst(int, ARMProc *);
void ldrbt_inst(int, ARMProc *);
void ldrb_inst(int, ARMProc *);
void ldrd_inst(int, ARMProc *);
void ldrh_inst(int, ARMProc *);
void ldrsb_inst(int, ARMProc *);
void ldrsh_inst(int, ARMProc *);
void ldm1_inst(int, ARMProc *);
void ldm2_inst(int, ARMProc *);
void strt_inst(int, ARMProc *);
void str_inst(int, ARMProc *);
void strbt_inst(int, ARMProc *);
void strb_inst(int, ARMProc *);
void strd_inst(int, ARMProc *);
void strh_inst(int, ARMProc *);
void stm1_inst(int, ARMProc *);
void stm2_inst(int, ARMProc *);
//Data processing instructions
void and_inst(int, ARMProc *);
void eor_inst(int, ARMProc *);
void sub_inst(int, ARMProc *);
void rsb_inst(int, ARMProc *);
void add_inst(int, ARMProc *);
void adc_inst(int, ARMProc *);
void sbc_inst(int, ARMProc *);
void rsc_inst(int, ARMProc *);
void tst_inst(int, ARMProc *);
void teq_inst(int, ARMProc *);
void cmp_inst(int, ARMProc *);
void cmn_inst(int, ARMProc *);
void orr_inst(int, ARMProc *);
void mov_inst(int, ARMProc *);
void bic_inst(int, ARMProc *);
void mvn_inst(int, ARMProc *);
//Exception generating instructions
void bkpt_inst(int, ARMProc *);
void swi_inst(int, ARMProc *);
//Coprocessor instructions
void cdp_inst(int, ARMProc *);
void mrrc_inst(int, ARMProc *);
void ldc_inst(int, ARMProc *);
void mcr_inst(int, ARMProc *);
void mcrr_inst(int, ARMProc *);
void mrc_inst(int, ARMProc *);
void stc_inst(int, ARMProc *);

#endif

