%define	BUF	8
	
global	_ft_cat
extern	_ft_strnew
extern	_ft_putstr
extern	_free
	
section .text

_ft_cat:

L1:	
	push	rdi
	mov	rdi,	BUF
	call	_ft_strnew
	pop	rdi
	mov	r9,	rdi
	mov	r8,	rax
	
	mov	rdi,	r9
	mov	rsi,	r8
	mov	rdx,	BUF
	mov	rax,	0x2000003
	syscall
	
	jc 	error
	cmp	rax,	0
	je	last

	push	rdi
	mov	rdi,	1
	mov	rsi,	r8
	mov	rdx,	rax
	mov	rax,	0x2000004
	syscall
	jc 	error
	pop	rdi

	push	rdi
	mov	rdi,	rsi
	call	_free
	pop	rdi

	jmp	L1

error:
	push	rdi
	mov	rdi,	rsi
	call	_free
	pop	rdi
	mov	rax,	1
	ret
	
last:

	push	rdi
	mov	rdi,	rsi
	call	_free
	pop	rdi

end:
	mov	rax,	0
	ret
	