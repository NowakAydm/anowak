global	_ft_puts
section .text

_ft_puts:
	push	rbp
	mov		rbp,	rsp
	
	cmp		rdi,	0
	je		L3

	mov		rcx,	rdi
	mov		r8,		0
L1:
	cmp		[rdi],	byte 0
	je		L2
	inc		r8
	inc		rdi
	jmp		L1

L2:
	mov		rax,	0x2000004
	mov		rdi,	1
	mov		rsi,	rcx
	mov		rdx,	r8
	syscall
	jmp		L4

L3:
	mov		rax,	0x2000004
	mov		rdi,	1
	mov		rsi,	null
	mov		rdx,	6
	syscall
		
L4:	
	push	rcx
	mov		rax,	0x2000004
	mov		rdi,	1
	mov		rsi,	new_line
	mov		rdx,	1
	syscall
	pop		rcx

end:
	mov		rax,	10
	pop		rbp
	ret

new_line:
	db		10

null:
	dw		'(null)'