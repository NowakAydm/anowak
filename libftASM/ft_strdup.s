global	_ft_strdup
extern	_ft_strlen
extern	_malloc
	
section .text

_ft_strdup:
	push	rdi

	cmp		rdi,	0
	je		ret_null

	push	rdi
	call	_ft_strlen
	push	rax
	mov		rdi,	rax
	
	inc		rdi
	call	_malloc

	cmp		rax,	0
	je		ret_nomem

	pop		rcx
	pop		rsi
	mov		rdi,	rax
	cld
	rep		movsb

	jmp		end
	
ret_nomem:
	pop		rax
	pop		rdi
	
ret_null:
	mov		rax,	0
	
end:	
	pop		rdi
	ret
	