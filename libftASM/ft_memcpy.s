global	_ft_memcpy
section .text

_ft_memcpy:

	mov		rcx,	rdx
	mov		rax,	rdi
	cld
	rep		movsb

	ret
	