global	_ft_isdigit
section .text

_ft_isdigit:
	push	rbp
	mov	rbp,	rsp

	mov	rax,	0
	
	cmp	rdi,	48
	jl	end
	cmp	rdi,	57
	jg	end
	
	mov	rax,	1
	
end:
	pop	rbp
	ret
	