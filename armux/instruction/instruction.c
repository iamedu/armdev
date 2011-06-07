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

#include <armux/utils.h>
#include <armux/instruction.h>
#include <armux/processor.h>
#include <stdlib.h>

ARMInst **inst_dict() {
	ARMInst **dict = malloc(sizeof(ARMInst *) * 64);
	dict[0] = create_inst(0xfe000f0, 0x200090, mla_inst);
	dict[1] = create_inst(0xfe000f0, 0x90, mul_inst);
	dict[2] = create_inst(0xff00090, 0x1000080, smla_inst);
	dict[3] = create_inst(0xfe000f0, 0xe00090, smlal_inst);
	dict[4] = create_inst(0xff00090, 0x1400080, smlalxy_inst);
	dict[5] = create_inst(0xff000b0, 0x1200080, smlawy_inst);
	dict[6] = create_inst(0xfe000f0, 0xc00090, smull_inst);
	dict[7] = create_inst(0xff000b0, 0x12000a0, smulwy_inst);
	dict[8] = create_inst(0xff00090, 0x1600080, smulxy_inst);
	dict[9] = create_inst(0xfe000f0, 0xa00090, umlal_inst);
	dict[10] = create_inst(0xfe000f0, 0x800090, umull_inst);
	dict[11] = create_inst(0xff00000, 0x1600000, clz_inst);
	dict[12] = create_inst(0xff000f0, 0x1000090, swp_inst);
	dict[13] = create_inst(0xff000f0, 0x1400090, swpb_inst);
	dict[14] = create_inst(0xfb00000, 0x1000000, mrs_inst);
	dict[15] = create_inst(0xfb000f0, 0x1200000, msr_inst);
	dict[16] = create_inst(0xfb00000, 0x3200000, msri_inst);
	dict[17] = create_inst(0xe000000, 0xa000000, bl_inst);
	dict[18] = create_inst(0xff000f0, 0x1200010, bx_inst);
	dict[19] = create_inst(0xfe000000, 0xfa000000, blx1_inst);
	dict[20] = create_inst(0xff000f0, 0x1200030, blx2_inst);
	dict[21] = create_inst(0xd700000, 0x4300000, ldrt_inst);
	dict[22] = create_inst(0xc500000, 0x4100000, ldr_inst);
	dict[23] = create_inst(0xd700000, 0x4700000, ldrbt_inst);
	dict[24] = create_inst(0xc500000, 0x4500000, ldrb_inst);
	dict[25] = create_inst(0xe1000f0, 0xd0, ldrd_inst);
	dict[26] = create_inst(0xe1000f0, 0x1000b0, ldrh_inst);
	dict[27] = create_inst(0xe1000f0, 0x1000d0, ldrsb_inst);
	dict[28] = create_inst(0xe1000f0, 0x1000f0, ldrsh_inst);
	dict[29] = create_inst(0xe500000, 0x8100000, ldm1_inst);
	dict[30] = create_inst(0xe708000, 0x8500000, ldm2_inst);
	dict[31] = create_inst(0xd700000, 0x4200000, strt_inst);
	dict[32] = create_inst(0xc500000, 0x4000000, str_inst);
	dict[33] = create_inst(0xd700000, 0x4600000, strbt_inst);
	dict[34] = create_inst(0xc500000, 0x4400000, strb_inst);
	dict[35] = create_inst(0xe1000f0, 0xf0, strd_inst);
	dict[36] = create_inst(0xe1000f0, 0xb0, strh_inst);
	dict[37] = create_inst(0xe500000, 0x8000000, stm1_inst);
	dict[38] = create_inst(0xe700000, 0x8400000, stm2_inst);
	dict[39] = create_inst(0xde00000, 0x0, and_inst);
	dict[40] = create_inst(0xde00000, 0x200000, eor_inst);
	dict[41] = create_inst(0xde00000, 0x400000, sub_inst);
	dict[42] = create_inst(0xde00000, 0x600000, rsb_inst);
	dict[43] = create_inst(0xde00000, 0x800000, add_inst);
	dict[44] = create_inst(0xde00000, 0xa00000, adc_inst);
	dict[45] = create_inst(0xde00000, 0xc00000, sbc_inst);
	dict[46] = create_inst(0xde00000, 0xe00000, rsc_inst);
	dict[47] = create_inst(0xdf00000, 0x1100000, tst_inst);
	dict[48] = create_inst(0xdf00000, 0x1300000, teq_inst);
	dict[49] = create_inst(0xdf00000, 0x1500000, cmp_inst);
	dict[50] = create_inst(0xdf00000, 0x1700000, cmn_inst);
	dict[51] = create_inst(0xde00000, 0x1800000, orr_inst);
	dict[52] = create_inst(0xde00000, 0x1a00000, mov_inst);
	dict[53] = create_inst(0xde00000, 0x1c00000, bic_inst);
	dict[54] = create_inst(0xde00000, 0x1e00000, mvn_inst);
	dict[55] = create_inst(0xfff000f0, 0xe1200070, bkpt_inst);
	dict[56] = create_inst(0xf000000, 0xf000000, swi_inst);
	dict[57] = create_inst(0xf000010, 0xe000000, cdp_inst);
	dict[58] = create_inst(0xff00000, 0xc500000, mrrc_inst);
	dict[59] = create_inst(0xe100000, 0xc100000, ldc_inst);
	dict[60] = create_inst(0xf100010, 0xe000010, mcr_inst);
	dict[61] = create_inst(0xff00000, 0xc400000, mcrr_inst);
	dict[62] = create_inst(0xf100010, 0xe100010, mrc_inst);
	dict[63] = create_inst(0xe100000, 0xc000000, stc_inst);
	return dict;
}

ARMInst *create_inst(int testmask, int bitmask, void *func) {
	ARMInst *result;
	result = malloc(sizeof(ARMInst));
	result->bitmask  = bitmask;
	result->testmask = testmask;
	result->execute  = func;
	return result;
}

int test_inst(ARMInst *inst, int inst_val) {
	return (inst->testmask & inst_val) == inst->bitmask;
}

int check_condition(ARMProc *proc, int inst) {
	int cond = getbits(inst, 28, 4);
	switch(cond) {
		case 0:
			return read_status(proc, CPSR_Z) == 1;
		break;
		case 1:
			return read_status(proc, CPSR_Z) == 0;
		break;
		case 2:
			return read_status(proc, CPSR_C) == 1;
		break;
		case 3:
			return read_status(proc, CPSR_C) == 0;
		break;
		case 4:
			return read_status(proc, CPSR_N) == 1;
		break;
		case 5:
			return read_status(proc, CPSR_N) == 0;
		break;
		case 6:
			return read_status(proc, CPSR_V) == 1;
		break;
		case 7:
			return read_status(proc, CPSR_V) == 0;
		break;
		case 8:
			return (read_status(proc, CPSR_C) == 1) &&
			       (read_status(proc, CPSR_Z) == 0);
		break;
		case 9:
			return (read_status(proc, CPSR_C) == 0) ||
			       (read_status(proc, CPSR_Z) == 1);
		break;
		case 10:
			return read_status(proc, CPSR_N) ==
			       read_status(proc, CPSR_V);
		break;
		case 11:
			return read_status(proc, CPSR_N) !=
			       read_status(proc, CPSR_V);
		break;
		case 12:
			return (read_status(proc, CPSR_Z) == 0) &&
			       (read_status(proc, CPSR_N) ==
                               read_status(proc, CPSR_V));
		break;
		case 13:
			return (read_status(proc, CPSR_Z) == 1) ||
			       (read_status(proc, CPSR_N) !=
                               read_status(proc, CPSR_V));
		break;
		case 14:
			return 1;
		break;
	}
	return 0;
}

