global	_ft_toupper
section .text

_ft_toupper:
	mov		rax,	rdi
	
	cmp		rdi,	97
	jl		end
	cmp		rdi,	122
	jg		end

	sub		rax,	32
	
end:	
	ret
	