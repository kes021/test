	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi2:
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	lea	rax, [rip + L_.str]
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], edi
	mov	qword ptr [rbp - 16], rsi
	mov	dword ptr [rbp - 20], 2147483647
	mov	dword ptr [rbp - 24], 5
	mov	edi, dword ptr [rbp - 24]
	mov	cx, di
	mov	word ptr [rbp - 26], cx
	movsx	esi, word ptr [rbp - 26]
	mov	rdi, rax
	mov	al, 0
	call	_printf
	xor	esi, esi
	mov	dword ptr [rbp - 32], eax ## 4-byte Spill
	mov	eax, esi
	add	rsp, 32
	pop	rbp
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d \n"


.subsections_via_symbols
