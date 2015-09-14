global	_ft_isupper
section .text

_ft_isupper:
	mov		rax,	0
	
	cmp		rdi,	65
	jl		end
	cmp		rdi,	90
	jg		end

	mov		rax,	1
	
end:	
	ret
	