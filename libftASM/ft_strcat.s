global	_ft_strcat
extern	_ft_strlen
section .text

_ft_strcat:
	push	rdi
	
	cmp		rsi,	0
	je		end

	push	rdi
	call	_ft_strlen
	pop		rdi
	add		rdi,	rax
	mov		rdx,	rdi

	mov		rdi,	rsi
	push	rdi
	call	_ft_strlen
	pop		rdi
	mov		rcx,	rax
	mov		rsi,	rdi
	mov		rdi,	rdx

	cld
	rep		movsb
	
end:
	pop		rdi
	mov		rax,	rdi
	ret
	