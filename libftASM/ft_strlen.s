global	_ft_strlen
section .text

_ft_strlen:
	mov		rax,	0
	cmp		rdi,	0
	je		end
	
	mov		rcx,	0
	not		rcx
	mov		al,		0
	cld
	repne	scasb

	not		rcx
	dec		rcx
	mov		rax,	rcx

end:
	ret
	