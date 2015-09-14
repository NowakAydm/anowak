global	_ft_isalpha
section .text

_ft_isalpha:
	push	rbp
	mov		rbp,	rsp

	mov		rax,	0
	mov		rsi,	0
	
	cmp		rdi,	65
	jl		end
	cmp		rdi,	90
	jg		not_maj

	mov		rax,	1

not_maj:
	cmp		rdi,	97
	jl		end
	cmp		rdi,	122
	jg		end
	
	mov		rax,	1
	
end:
	pop		rbp
	ret