#include <armux/types.h>
#include <armux/instruction.h>
#include <stdlib.h>
#include <stdio.h>

ARMInst *new_inst(UWord bitmask, UWord expected, void *func) {
	ARMInst *inst = malloc(sizeof(ARMInst));
	inst->bitmask = bitmask;
	inst->expected = expected;
	inst->execute = func;
	inst->next = NULL;
}

void append(ARMInst *root, ARMInst *node) {
	ARMInst *tmp;
	tmp = root;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = node;
}

ARMInst *instruction_set() {
	ARMInst *root;

	//BL instruction
	root = new_inst(0x0e000000, 0x0a000000, &bl_inst);

	//BLX(2) instruction
	append(root, new_inst(0x0ffffff0, 0x012fff30, &blx_inst));

	//BX instruction
	append(root, new_inst(0x0ffffff0, 0x012fff10, &bx_inst));
	
	//Multiply instructions by Draidens"The Man'"(draiden.wordpress.com)
	
	//MLA instruction
	append(root, new_inst(0x0fe000f0, 0x00200090, &mla_inst));

	//MUL instruction
	append(root, new_inst(0x0fe0f0f0, 0x00000090, &mul_inst));

	//SMLA instruction
	append(root, new_inst(0x0ff00090, 0x01000080, &smla_inst));

	//SMUAD instruction
	append(root, new_inst(0x0ff0f0d0, 0x0700f010, &smuad_inst));

	//SMLAD instruction
	append(root, new_inst(0x0ff000d0, 0x07000010, &smlad_inst));

	//SMLAL instruction
	append(root, new_inst(0x0fe000f0, 0x00e00090, &smlal_inst));

	//SMLALXY instruction
	append(root, new_inst(0x0ff00090, 0x01400080, &smlalxy_inst));

	//SMLALD instruction
	append(root, new_inst(0x0ff000d0, 0x07400010, &smlald_inst));

	//SMLAW instruction
	append(root, new_inst(0x0ff000b0, 0x01200080, &smlaw_inst));

	//SMUSD instruction
	append(root, new_inst(0x0ff0f0d0, 0x0700f050, &smusd_inst));

	//SMLSD instruction
	append(root, new_inst(0x0ff000d0, 0x07000050, &smlsd_inst));

	//SMLSLD instruction
	append(root, new_inst(0x0ff000d0, 0x07400050, &smlsld_inst));

	//SMMUL instruction
	append(root, new_inst(0x0ff0f0d0, 0x0750f010, &smmul_inst));

	//SMMLA instruction
	append(root, new_inst(0x0ff000d0, 0x07500010, &smmla_inst));

	//SMMLS instruction
	append(root, new_inst(0x0ff000d0, 0x075000d0, &smmls_inst));

	//SMUL instruction
	append(root, new_inst(0x0ff0f090, 0x01600080, &smul_inst));

	//SMULL instruction
	append(root, new_inst(0x0fe000f0, 0x00c00090, &smull_inst));

	//SMULW instruction
	append(root, new_inst(0x0ff0f0b0, 0x012000a0, &smulw_inst));

	//UMAAL instruction
	append(root, new_inst(0x0ff000f0, 0x00400090, &umaal_inst));

	//UMLAL instruction
	append(root, new_inst(0x0fe000f0, 0x00a00090, &umlal_inst));

	//UMULL instruction
	append(root, new_inst(0x0fe000f0, 0x00800090, &umull_inst));
	// End of multiply instructions

	//Sign/zero extend and Add instructions by Draidens"The Man'"(draiden.wordpress.com)

	//SXTB16 instruction
	append(root, new_inst(0x0fff03f0, 0x068f0070, &sxtb16_inst));

	//SXTAB16 instruction
	append(root, new_inst(0x0ff003f0, 0x06800070, &sxtab16_inst));

	//SXTB instruction
	append(root, new_inst(0x0fff03f0, 0x06af0070, &sxtb_inst));

	//SXTAB instruction
	append(root, new_inst(0x0ff003f0, 0x06a00070, &sxtab_inst));

	//SXTH instruction
	append(root, new_inst(0x0fff03f0, 0x06bf0070, &sxth_inst));

	//SXTAH instruction
	append(root, new_inst(0x0ff003f0, 0x06b00070, &sxtah_inst));

	//UXTB16 instruction
	append(root, new_inst(0x0fff03f0, 0x06cf0070, &uxtb16_inst));

	//UXTAB16 instruction
	append(root, new_inst(0x0ff003f0, 0x06c00070, &uxtab16_inst));

	//UXTB instruction
	append(root, new_inst(0x0fff03f0, 0x06ef0070, &uxtb_inst));

	//UXTAB instruction
	append(root, new_inst(0x0ff003f0, 0x06e00070, &uxtab_inst));

	//UXTH instruction
	append(root, new_inst(0x0fff03f0, 0x06ff0070, &uxth_inst));

	//UXTAH instruction
	append(root, new_inst(0x0ff003f0, 0x06f00070, &uxtah_inst));
	//End of sign/zero extend and add instructions

	//Load and store instructions by The Man(elman.blominente.com.mx)

	//LDRT
	append(root, new_inst(0x0d700000, 0x04300000, &ldrt_inst));	

	//LDR
	append(root, new_inst(0x0c500000, 0x04100000, &ldr_inst));
	
	//LDRBT
	append(root, new_inst(0x0d700000, 0x04700000, &ldrbt_inst));

	//LDRB
	append(root, new_inst(0x0c500000, 0x04500000, &ldrb_inst));
	
	//LDRD
	append(root, new_inst(0x0e1000f0, 0x000000d0, &ldrd_inst));
	
	//LDREX
	append(root, new_inst(0x0ff00fff, 0x01900f9f, &ldrex_inst));
	
	//LDRH
	append(root, new_inst(0x0e1000f0, 0x001000b0, &ldrh_inst));
	
	//LDRSB
	append(root, new_inst(0x0e1000f0, 0x001000d0, &ldrsb_inst));
	
	//LDRSH
	append(root, new_inst(0x0e1000f0, 0x001000f0, &ldrsh_inst));
	
	//STRT
	append(root, new_inst(0x0d700000, 0x04200000, &strt_inst));
	//STR 
	append(root, new_inst(0x0c500000, 0x04000000, &str_inst));
	
	//STRBT
	append(root, new_inst(0x0c700000, 0x04600000, &strbt_inst));

	//STRB
	append(root, new_inst(0x0c500000, 0x04400000, &strb_inst));
	
	//STRD
	append(root, new_inst(0x0e1000f0, 0x000000f0, &strd_inst));
	
	//STREX
	append(root, new_inst(0x0ff00ff0, 0x01800f90, &strex_inst));
	
	//STRH
	append(root, new_inst(0x0e1000f0, 0x000000b0, &strh_inst));
	
	//End of load and store instructions by The Man(elman.blominente.com.mx)

	//Sign/zero extend and Add instructions by Draidens"The Man'"(draiden.wordpress.com)

	//SXTB16 instruction
	append(root, new_inst(0x0fff03f0, 0x068f0070, &sxtb16_inst));

	//SXTAB16 instruction
	append(root, new_inst(0x0ff003f0, 0x06800070, &sxtab16_inst));

	//SXTB instruction
	append(root, new_inst(0x0fff03f0, 0x06af0070, &sxtb_inst));

	//SXTAB instruction
	append(root, new_inst(0x0ff003f0, 0x06a00070, &sxtab_inst));

	//SXTH instruction
	append(root, new_inst(0x0fff03f0, 0x06bf0070, &sxth_inst));

	//SXTAH instruction
	append(root, new_inst(0x0ff003f0, 0x06b00070, &sxtah_inst));

	//UXTB16 instruction
	append(root, new_inst(0x0fff03f0, 0x06cf0070, &uxtb16_inst));

	//UXTAB16 instruction
	append(root, new_inst(0x0ff003f0, 0x06c00070, &uxtab16_inst));

	//UXTB instruction
	append(root, new_inst(0x0fff03f0, 0x06ef0070, &uxtb_inst));

	//UXTAB instruction
	append(root, new_inst(0x0ff003f0, 0x06e00070, &uxtab_inst));

	//UXTH instruction
	append(root, new_inst(0x0fff03f0, 0x06ff0070, &uxth_inst));

	//UXTAH instruction
	append(root, new_inst(0x0ff003f0, 0x06f00070, &uxtah_inst));
	//End of sign/zero extend and add instructions

	//Data-processing instructions by The Man(elman.blominente.com.mx)
	
	//ADC instruction
	append(root, new_inst(0x0de00000, 0x00a00000, &adc_inst));
	
	//ADD instruction
	append(root, new_inst(0x0de00000, 0x00800000, &add_inst));
	
	//AND instruction
	append(root, new_inst(0x0de00000, 0x00000000, &and_inst));
	
	//BIC instruction
	append(root, new_inst(0x0de00000, 0x01c00000, &bic_inst));

	//CMN instruction
	append(root, new_inst(0x0df0f000, 0x01700000, &cmn_inst));

	//CMP instruction
	append(root, new_inst(0x0df0f000, 0x01500000, &cmp_inst));

	//EOR instruction
	append(root, new_inst(0x0de00000, 0x00200000, &eor_inst));

	//MOV instruction
	append(root, new_inst(0x0de00000, 0x01a00000, &mov_inst));

	//MVN instruction
	append(root, new_inst(0x0de00000, 0x01e00000, &mvn_inst));

	//ORR instruction
	append(root, new_inst(0x0de00000, 0x01800000, &orr_inst));

	//RSB instruction
	append(root, new_inst(0x0de00000, 0x00600000, &rsb_inst));

	//RSC instruction
	append(root, new_inst(0x0de00000, 0x00e00000, &rsc_inst));
	
	//SBC instruction
	append(root, new_inst(0x0de00000, 0x00c00000, &sbc_inst));

	//SUB instruction
	append(root, new_inst(0x0de00000, 0x00400000, &sub_inst));

	//TEQ instruction
	append(root, new_inst(0x0df0f000, 0x01300000, &teq_inst));

	//TST instruction
	append(root, new_inst(0x0df00000, 0x01100000, &tst_inst));
	// End of data-processing

	//Miscellaneous instructions by The Man(elman.blominente.com.mx)
	
	//CLZ
        append(root, new_inst(0x0fff0ff0, 0x016f0f10, &clz_inst));

	//End of miscellaneous instructions by The Man(elman.blominente.com.mx)
	
        
	//Semaphore intructions by The Man(elman.blominente.com.mx)
	
	//SWPB
        append(root, new_inst(0x0ff00ff0, 0x01400090, &swpb_inst));

	//SWP
        append(root, new_inst(0x0ff00ff0, 0x01000090, &swp_inst));

	//End of semaphore intructions by The Man(elman.blominente.com.mx)
	
	//Coprocessor instructions by The Man(elman.blominente.com.mx)
	
	//MRRC
        append(root, new_inst(0x0ff00000, 0x0c500000, &mcrr_inst));

	//CDP
        append(root, new_inst(0x0f000010, 0x0e000000, &cdp_inst));

	//LDC
        append(root, new_inst(0x0e100000, 0x0c100000, &ldc_inst));

	//MCR
        append(root, new_inst(0x0f100010, 0x0e000010, &mcr_inst));

	//MCRR
        append(root, new_inst(0x0ff00000, 0x0c400000, &mcrr_inst));

	//MRC
        append(root, new_inst(0x0f100010, 0x0e100010, &mrc_inst));

	//STC
        append(root, new_inst(0x0e100000, 0x0c000000, &stc_inst));

	//End of coprocessor instructions by The Man(elman.blominente.com.mx)
		

	//Status register access instruction by Draidens"The Man'"(draiden.wordpress.com)
	
	//MRS instruction
	append(root, new_inst(0x0fbf0fff, 0x010f0000, &mrs_inst));

	//MSRI instruction
	append(root, new_inst(0x0fa0f000, 0x0320f000, &msri_inst));

	//MSRR instruction
	append(root, new_inst(0x0fa0fff0, 0x0120f000, &msrr_inst));

	//CPS instruction
	append(root, new_inst(0xfff1fd20, 0xf1000000, &cps_inst));

	//SETEND instruction
	append(root, new_inst(0xfffffdff, 0xf1010000, &setend_inst));
	//End of status register access instructions

	//Load and Store Multiple instructions by Draidens"The Man'"(draiden.wordpress.com)

	//LDM(1) instruction
	append(root, new_inst(0x0e500000, 0x08100000, &ldm1_inst));

	//LDM(2) instruction
	append(root, new_inst(0x0e708000, 0x08500000, &ldm2_inst));

	//LDM(3) instruction
	append(root, new_inst(0x0e508000, 0x08508000, &ldm3_inst));

	//STM(1) instruction
	append(root, new_inst(0x0e500000, 0x08000000, &stm1_inst));

	//STM(2) instruction
	append(root, new_inst(0x0e700000, 0x08400000, &stm2_inst));
	//End of load and Store Multiple instructions

	//Exception-generating instructions by Draidens"The Man'"(draiden.wordpress.com)

	//BKPT instruction
	append(root, new_inst(0xfff000f0, 0xe1200070, &bkpt_inst));

	//SWI instruction
	append(root, new_inst(0x0f000000, 0x0f000000, &swi_inst));
	//End of exception-generating intructions

	return root;
}


ARMInst *fetch(ARMInst *root, UWord inst) {
	ARMInst *tmp;

	tmp = root;
	while(tmp != NULL) {
		if((inst & tmp->bitmask) == tmp->expected)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

