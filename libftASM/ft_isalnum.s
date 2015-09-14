global	_ft_isalnum
section .text

_ft_isalnum:
	push	rbp
	mov		rbp,	rsp

	mov		rax,	0

check_if_maj:
	cmp		rdi,	65
	jl		check_if_num
	cmp		rdi,	90
	jg		check_if_min

	mov		rax,	1

check_if_min:
	cmp		rdi,	97
	jl		end
	cmp		rdi,	122
	jg		end
	
	mov		rax,	1

check_if_num:
	cmp		rdi,	48
	jl		end
	cmp		rdi,	57
	jg		end
	
	mov		rax,	1

end:
	pop		rbp
	ret
		