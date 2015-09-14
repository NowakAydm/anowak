global	_ft_putstr
section .text

_ft_putstr:
	push	rbp
	mov		rbp,	rsp
	
	cmp		rdi,	0
	je		L3

	mov		rcx,	rdi
	mov		r8,	1
L1:
	cmp		[rdi],	byte 0
	je		L2
	inc		r8
	inc		rdi
	jmp		L1

L2:
	dec		r8
	mov		rax,	0x2000004
	mov		rdi,	1
	mov		rsi,	rcx
	mov		rdx,	r8
	syscall
	jmp		end

L3:
	mov		rax,	0x2000004
	mov		rdi,	1
	mov		rsi,	null
	mov		rdx,	6
	syscall

end:
	mov		rax,	10
	pop		rbp
	ret

null:
	dw		'(null)'