#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <armux/types.h>
#include <armux/processor.h>

typedef struct ARMInst {
	UWord bitmask;
	UWord expected;
	void (*execute)(ARMProc *, UWord);
	struct ARMInst *next;
} ARMInst;

ARMInst *new_inst(UWord, UWord, void *);
void append(ARMInst *, ARMInst *);
ARMInst *instruction_set();
ARMInst *fetch(ARMInst *, UWord);

//Branch instructions
void bl_inst(ARMProc *, UWord);
void blx_inst(ARMProc *, UWord);
void bx_inst(ARMProc *, UWord);
//End of Branch instructions

//Miscellaneous instructions
void clz_inst(ARMProc *, UWord);
//End of Miscellaneous instructions

//Semaphore intructions
void swp_inst(ARMProc *, UWord);
void swpb_inst(ARMProc *, UWord);
//End of Semaphore intructions

//Multiply instructions
void mla_inst(ARMProc *, UWord);
void mul_inst(ARMProc *, UWord);
void smla_inst(ARMProc *, UWord);
void smlad_inst(ARMProc *, UWord);
void smlal_inst(ARMProc *, UWord);
void smlalxy_inst(ARMProc *, UWord);
void smlald_inst(ARMProc *, UWord);
void smlaw_inst(ARMProc *, UWord);
void smlsd_inst(ARMProc *, UWord);
void smlsld_inst(ARMProc *, UWord);
void smmla_inst(ARMProc *, UWord);
void smmls_inst(ARMProc *, UWord);
void smmul_inst(ARMProc *, UWord);
void smuad_inst(ARMProc *, UWord);
void smul_inst(ARMProc *, UWord);
void smull_inst(ARMProc *, UWord);
void smulw_inst(ARMProc *, UWord);
void smusd_inst(ARMProc *, UWord);
void umaal_inst(ARMProc *, UWord);
void umlal_inst(ARMProc *, UWord);
void umull_inst(ARMProc *, UWord);
//End of Multiply instructions

//Sign/zero extend and Add instructions
void sxtab16_inst(ARMProc *, UWord);
void sxtab_inst(ARMProc *, UWord);
void sxtah_inst(ARMProc *, UWord);
void sxtb16_inst(ARMProc *, UWord);
void sxtb_inst(ARMProc *, UWord);
void sxth_inst(ARMProc *, UWord);
void uxtab16_inst(ARMProc *, UWord);
void uxtab_inst(ARMProc *, UWord);
void uxtah_inst(ARMProc *, UWord);
void uxtb16_inst(ARMProc *, UWord);
void uxtb_inst(ARMProc *, UWord);
void uxth_inst(ARMProc *, UWord);
//End of Sign/zero extend and Add instructions

//Data-processing instructions
void and_inst(ARMProc *, UWord);
void adc_inst(ARMProc *, UWord);
void add_inst(ARMProc *, UWord);
void bic_inst(ARMProc *, UWord);
void cmn_inst(ARMProc *, UWord);
void cmp_inst(ARMProc *, UWord);
void eor_inst(ARMProc *, UWord);
void mov_inst(ARMProc *, UWord);
void mvn_inst(ARMProc *, UWord);
void orr_inst(ARMProc *, UWord);
void rsb_inst(ARMProc *, UWord);
void rsc_inst(ARMProc *, UWord);
void sbc_inst(ARMProc *, UWord);
void sub_inst(ARMProc *, UWord);
void teq_inst(ARMProc *, UWord);
void tst_inst(ARMProc *, UWord);
//End of Data-processing instructions

//Load and store instructions
//LS
void ldr_inst(ARMProc *, UWord);
void ldrb_inst(ARMProc *, UWord);
void ldrbt_inst(ARMProc *, UWord);
void ldrex_inst(ARMProc *, UWord);
void ldrt_inst(ARMProc *, UWord);
void str_inst(ARMProc *, UWord);
void strb_inst(ARMProc *, UWord);
void strbt_inst(ARMProc *, UWord);
void strex_inst(ARMProc *, UWord);
void strt_inst(ARMProc *, UWord);
//MLS
void ldrh_inst(ARMProc *, UWord);
void ldrd_inst(ARMProc *, UWord);
void ldrsb_inst(ARMProc *, UWord);
void ldrsh_inst(ARMProc *, UWord);
void strd_inst(ARMProc *, UWord);
void strh_inst(ARMProc *, UWord);
//End of load and store instructions

//Load and Store Multiple instructions
//LSM
void ldm1_inst(ARMProc *, UWord);
void ldm2_inst(ARMProc *, UWord);
void ldm3_inst(ARMProc *, UWord);
void stm1_inst(ARMProc *, UWord);
void stm2_inst(ARMProc *, UWord);
//End of load and store multiple instructions

//Load and store coprocessor
void mrrc_inst(ARMProc *, UWord);
void cdp_inst(ARMProc *, UWord);
void ldc_inst(ARMProc *, UWord);
void mcr_inst(ARMProc *, UWord);
void mcrr_inst(ARMProc *, UWord);
void mrc_inst(ARMProc *, UWord);
void stc_inst(ARMProc *, UWord);
//End of Load and store coprocessor

//Status register access instructions
void mrs_inst(ARMProc *, UWord);
void msri_inst(ARMProc *, UWord);
void msrr_inst(ARMProc *, UWord);
void cps_inst(ARMProc *, UWord);
void setend_inst(ARMProc *, UWord);
//End of Status register access instructions

//Exception-generating instructions
void bkpt_inst(ARMProc *, UWord);
void swi_inst(ARMProc *, UWord);
//End of Exception-generating instructions

#endif
