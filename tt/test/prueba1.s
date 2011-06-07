	.global _start
_start:
	mov	r0,	#5
	mov	r1,	#10
	add	r0,	r0,	r1
	str	r0,	[r0]
	ldr	r1,	[r0]
	cmn	r0,	r0
