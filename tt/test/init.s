	.global	_start


.macro  sum from=0, to=5
.word 0
.if     \to-\from
sum     "(\from+1)",\to
.endif
.endm

_start:
	mov	sp,	#1000
	ldr     lr,    =0x8000
	b	main
