global	_ft_bzero
section .text

_ft_bzero:
	push	rdi

	cmp		rsi,	0
	je		end
	
put_zero:	
	mov		[rdi],	byte 0
	inc		rdi
	dec		rsi
	jnz		put_zero
	
end:	
	pop		rdi
	mov		rax,	0
	ret
	