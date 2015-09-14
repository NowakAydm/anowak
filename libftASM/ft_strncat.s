global	_ft_strncat
extern	_ft_strlen
section .text

_ft_strncat:
	push	rdi
	
	cmp		rsi,	0
	je		end

	push	rdi
	call	_ft_strlen
	pop		rdi
	add		rdi,	rax
	mov		r8,		rdi

	mov		rdi,	rsi
	push	rdi
	call	_ft_strlen
	pop		rdi
	mov		rcx,	rdx
	mov		rsi,	rdi
	mov		rdi,	r8

	cld
	rep		movsb
	
end:
	pop		rdi
	mov		rax,	rdi
	ret
	