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
	b	irq_exc //Interrupt exception
	b	fiq_exc //Fast interrupt exception

und_exc:

swi_exc:

pfa_exc:

dta_exc:

irq_exc:

fiq_exc:

res_exc:

	b	init

