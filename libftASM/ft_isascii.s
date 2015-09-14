global	_ft_isascii
section .text

_ft_isascii:
	push	rbp
	mov	rbp,	rsp

	mov	rax,	0
	
	cmp	rdi,	127
	jg	end
	
	mov	rax,	1
	
end:
	pop	rbp
	ret
	