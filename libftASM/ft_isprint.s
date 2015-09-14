global	_ft_isprint
section .text

_ft_isprint:
	push	rbp
	mov	rbp,	rsp

	mov	rax,	0
	
	cmp	rdi,	32
	jl	end
	cmp	rdi,	127
	jge	end
	
	mov	rax,	1
	
end:
	pop	rbp
	ret
	