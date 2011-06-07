	.global _start
	.global perro
perro:

_start:
	b perro
	blx r0
	bx r0
	and r0,r0,#5
	and r0,r0,r0
	and r0,r0,r0, LSL #5
	and r0,r0,r0, LSL r0
	and r0,r0,r0, LSR #1
	and r0,r0,r0, LSR r0
	and r0,r0,r0, ASR #4
	and r0,r0,r0, ASR r0
	and r0,r0,r0, ROR #2
	and r0,r0,r0, ROR r0
	and r0,r0,r0, RRX
	adc r0,r0,r0
	add r0,r0,r0
	bic r0,r0,r0
	cmn r0,r0
	cmp r0,r0
	eor r0,r0,r0
	mov r0,r0
	mvn r0,r0	
	orr r0,r0,r0
	rsb r0,r0,r0
	rsc r0,r0,r0
	sbc r0,r0,r0
	sub r0,r0,r0
	teq r0,r0
	tst r0,r0
	clz r0,r0
	ldr r1,[r0]
	ldr r1,[r0,r1]
	ldr r1,[r0,r1,LSL #2]
	ldr r1,[r0,#2]!
	ldr r1,[r0,r2]!
	ldr r1,[r0,r2,LSL #2]!
	ldr r1,[r0],#2
	ldr r1,[r0],r2
	ldr r1,[r0],r2,LSL #3
	ldrb r1,[r0]
	ldrbt r1,[r0]
	ldrd r0,[r1, #1]
	ldrd r0,[r1, r2]
	ldrd r0,[r1, #2]!
	ldrd r0,[r1, r2]!
	ldrd r0,[r1],#2
	ldrd r0,[r1],r2
	ldrex r1,[r0]
	ldrh r1,[r0,#2]
	ldrsb r3,[r8,#3]
	ldrsh r3,[r9,#3]
	ldrt r3,[r5]
	str r2,[r5],#8
	strb r4,[r5,-r4]
	strbt r3,[r4],#5
	strd r8,[r2,#0x2C]
	strex r1,r2,[r3]
	strh r2,[r5],#8
	strt r2,[r4],#3
	swp r0,r1,[r10]
	swpb r0,r1,[r9]
	cdp p5,2,c12,c10,c3,4
	ldc p6,cr1,[r4,#5*4]
	ldc p6,cr1,[r4,#5*4]!
	ldc p6,cr1,[r4],#5*4
	ldc p6,cr1,[r4],{1}
	mcr p14,1,r7,c7,c12,6
	mcrr p14,1,r1,r3,c4
	mrc p15,5,r4,c0,c2,3
	mrrc p14,1,r1,r3,c4
	stc p8,cr4,[r2,#4]!
	mla r0,r1,r2,r3
	mul r0,r1,r2
	smlabb r0,r1,r2,r3
	smlad r0,r1,r2,r3
	smlal r0,r1,r2,r3
	smlalbb r0,r1,r2,r3
	smlald r0,r1,r2,r3
	smlawb r0,r1,r2,r3
	smlsd r0,r1,r2,r3
	smlsld r0,r1,r2,r3
	smmla r0,r1,r2,r3
	smmls r0,r1,r2,r3
	smmul r0,r1,r2
	smuad r0,r1,r2
	smulbb r0,r1,r2
	smull r0,r1,r2,r3
	smulwb r0,r1,r2
	smusd r0,r1,r2
	umaal r0,r1,r2,r3
	umlal r0,r1,r2,r3
	umull r0,r1,r2,r3
	sxtab16 r0,r1,r2
	sxtab r0,r1,r2
	sxtah r0,r1,r2
	sxtb16 r0,r1
	sxtb r0,r1
	sxth r0,r1
	uxtab16 r0,r1,r2
	uxtab r0,r1,r2
	uxtah r0,r1,r2
	uxtb16 r0,r1
	uxtb r0,r1
	uxth r0,r1
	mrs r3, cpsr
	msr cpsr, r3
	msr cpsr, #
	cps #16
	ldmia r0!, {r1,r2,r3}
	ldmib r0!, {r1,r2,r3}
	ldmda r0!, {r1,r2,r3}
	ldmdb r0!, {r1,r2,r3}
	ldmia r4, {r2, r3}^
	ldmia r0!, {r2,r3,r15}^
	setend le
	stmia r0!, {r1,r2,r5}
	stmia r0, {r1,r2,r5}^
	bkpt #12
	swi #13
 
