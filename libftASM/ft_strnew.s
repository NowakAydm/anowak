global	_ft_strnew
extern	_ft_bzero
extern	_malloc
section .text

_ft_strnew:
	mov		rax,	0	
	push	rdi
	cmp		rdi,	0
	je		end

	call	_malloc
	
	mov	rsi,	rdi
	mov	rdi,	rax
	
end:
	pop	rdi
	ret