global	_ft_islower
section .text

_ft_islower:
	mov		rax,	0
	
	cmp		rdi,	97
	jl		end
	cmp		rdi,	122
	jg		end

	mov		rax,	1
	
end:	
	ret
	