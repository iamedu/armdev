#include <aic.h>
#include <devices.h>

	//Global procedure declaration
	.global _start
	.global res_exc
	.global und_exc
	.global swi_exc
	.global pfa_exc
	.global dta_exc
	.global irq_exc
	.global fiq_exc

//Bootloader entry point
_start:
	//Exception vector
	b	res_exc	//Reset exception
	b	und_exc //Undefined exception
	b	swi_exc //Software Interrupt Exception
	b	pfa_exc //Prefetch abort exception
	b	dta_exc //Data abort exception
	nop
	ldr	pc,	[pc, #-0xf20]//Interrupt exception
	ldr	pc,	[pc, #-0xf20]//Fast interrupt exception

und_exc:

swi_exc:

pfa_exc:

dta_exc:

res_exc:

	mrs	r0,	cpsr
	msr	CPSR_c, #0x12|0x80|0x40
	ldr	sp,	=0x300000
	msr	cpsr,	r0
	

	mrs	r0,	cpsr
	bic	r0,	r0,	#0x80
	msr	cpsr,	r0

	ldr	sp,	=0x301000
	b	init

