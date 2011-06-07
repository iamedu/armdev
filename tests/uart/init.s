/*
 * Created by Eduardo Diaz
 *
 */

	.global reset
	.global undef
	.global swi
	.global prefetch
	.global data
	.global irq
	.global fiq

	.global init_all
	.global init

init_all:
reset:
	b	init
undef:
	nop
swi:
	nop
prefetch:
	nop
data:
	nop
	nop
irq:
	nop
fiq:
	nop

init:
	mov	sp,	#500
	b	main

