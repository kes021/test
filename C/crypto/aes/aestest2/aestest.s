	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_rol32
	.p2align	4, 0x90
_rol32:                                 ## @rol32
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movl	%esi, %ecx
	roll	%cl, %edi
	movl	%edi, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_tbox_mix_columns
	.p2align	4, 0x90
_tbox_mix_columns:                      ## @tbox_mix_columns
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	pushq	%rax
Lcfi6:
	.cfi_offset %rbx, -56
Lcfi7:
	.cfi_offset %r12, -48
Lcfi8:
	.cfi_offset %r13, -40
Lcfi9:
	.cfi_offset %r14, -32
Lcfi10:
	.cfi_offset %r15, -24
	movq	%rsi, %r14
	movl	%edi, %ebx
	leaq	L_.str(%rip), %rdi
	xorl	%eax, %eax
	movl	%ebx, %esi
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	callq	_puts
	movzbl	%bl, %esi
	movq	%rbx, %r13
	movl	(%r14,%rsi,4), %edx
	leaq	L_.str.2(%rip), %r15
	xorl	%eax, %eax
	movq	%r15, %rdi
                                        ## kill: %ESI<def> %ESI<kill> %RSI<kill>
	callq	_printf
	leaq	L_.str.3(%rip), %rdi
	movl	$-1, %esi
	xorl	%eax, %eax
	callq	_printf
	movq	%r13, %rax
	movzbl	%ah, %ebx  # NOREX
	movl	(%r14,%rbx,4), %edx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	(%r14,%rbx,4), %ebx
	roll	$8, %ebx
	leaq	L_.str.4(%rip), %rdi
	xorl	%eax, %eax
	movl	%ebx, %esi
	callq	_printf
	movl	%r13d, %eax
	shrl	$16, %eax
	movzbl	%al, %r12d
	movl	(%r14,%r12,4), %edx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%r12d, %esi
	callq	_printf
	movl	(%r14,%r12,4), %r12d
	roll	$16, %r12d
	leaq	L_.str.5(%rip), %rdi
	xorl	%eax, %eax
	movl	%r12d, %esi
	callq	_printf
	movq	%r13, %rsi
	shrl	$24, %esi
	movl	(%r14,%rsi,4), %edx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movq	%rsi, %r15
	callq	_printf
	movl	(%r14,%r15,4), %r14d
	roll	$24, %r14d
	leaq	L_.str.6(%rip), %rdi
	xorl	%eax, %eax
	movl	%r14d, %esi
	callq	_printf
	leaq	L_.str.7(%rip), %r15
	movl	$-1, %esi
	xorl	%eax, %eax
	movq	%r15, %rdi
	callq	_printf
	notl	%ebx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%ebx, %esi
	callq	_printf
	xorl	%r12d, %ebx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%ebx, %esi
	callq	_printf
	xorl	%r14d, %ebx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	%ebx, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__literal16,16byte_literals
	.p2align	4
LCPI2_0:
	.long	370507307               ## 0x16157e2b
	.long	2798825000              ## 0xa6d2ae28
	.long	2283141035              ## 0x8815f7ab
	.long	1011863305              ## 0x3c4fcf09
LCPI2_1:
	.long	50462976                ## 0x3020100
	.long	117835012               ## 0x7060504
	.long	185207048               ## 0xb0a0908
	.long	252579084               ## 0xf0e0d0c
LCPI2_2:
	.long	857870592               ## 0x33221100
	.long	2003195204              ## 0x77665544
	.long	3148519816              ## 0xbbaa9988
	.long	4293844428              ## 0xffeeddcc
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi11:
	.cfi_def_cfa_offset 16
Lcfi12:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi13:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$312, %rsp              ## imm = 0x138
Lcfi14:
	.cfi_offset %rbx, -56
Lcfi15:
	.cfi_offset %r12, -48
Lcfi16:
	.cfi_offset %r13, -40
Lcfi17:
	.cfi_offset %r14, -32
Lcfi18:
	.cfi_offset %r15, -24
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movaps	LCPI2_0(%rip), %xmm0    ## xmm0 = [370507307,2798825000,2283141035,1011863305]
	movaps	%xmm0, -352(%rbp)
	leaq	-352(%rbp), %rdi
	leaq	-224(%rbp), %rsi
	callq	_aes128_key_expand
	leaq	L_.str.9(%rip), %rdi
	callq	_puts
	leaq	L_.str.10(%rip), %r14
	leaq	L_.str.13(%rip), %r15
	xorl	%r12d, %r12d
	.p2align	4, 0x90
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
	movq	%r14, %rdi
	movl	%r12d, %esi
	callq	_printf
	movl	-224(%rbp,%r12,4), %ebx
	movzbl	%bl, %esi
	xorl	%eax, %eax
	movq	%r15, %rdi
	callq	_printf
	movzbl	%bh, %esi  # NOREX
	xorl	%eax, %eax
	movq	%r15, %rdi
	callq	_printf
	movl	%ebx, %eax
	shrl	$16, %eax
	movzbl	%al, %esi
	xorl	%eax, %eax
	movq	%r15, %rdi
	callq	_printf
	shrl	$24, %ebx
	xorl	%eax, %eax
	movq	%r15, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	incq	%r12
	cmpq	$44, %r12
	jne	LBB2_1
## BB#2:
	movl	$10, %edi
	callq	_putchar
	movaps	LCPI2_1(%rip), %xmm0    ## xmm0 = [50462976,117835012,185207048,252579084]
	movaps	%xmm0, -352(%rbp)
	leaq	-352(%rbp), %rdi
	leaq	-224(%rbp), %rbx
	movq	%rbx, %rsi
	callq	_aes128_key_expand
	movaps	LCPI2_2(%rip), %xmm0    ## xmm0 = [857870592,2003195204,3148519816,4293844428]
	movaps	%xmm0, -336(%rbp)
	leaq	-336(%rbp), %r14
	leaq	-240(%rbp), %r15
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movq	%r15, %rdx
	callq	_aes128_block_encrypt
	movl	$10, %edi
	callq	_putchar
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%r14, %rdx
	callq	_aes128_block_decrypt
	movl	$10, %edi
	callq	_putchar
	movl	-336(%rbp), %eax
	movb	%al, -256(%rbp)
	movb	%ah, -255(%rbp)  # NOREX
	movl	%eax, %ecx
	movzbl	%al, %esi
	shrl	$16, %eax
	movb	%al, -254(%rbp)
	shrl	$24, %ecx
	movb	%cl, -253(%rbp)
	movl	-332(%rbp), %eax
	movb	%al, -252(%rbp)
	movb	%ah, -251(%rbp)  # NOREX
	movl	%eax, %ecx
	shrl	$16, %ecx
	movb	%cl, -250(%rbp)
	shrl	$24, %eax
	movb	%al, -249(%rbp)
	movl	-328(%rbp), %eax
	movb	%al, -248(%rbp)
	movb	%ah, -247(%rbp)  # NOREX
	movl	%eax, %ecx
	shrl	$16, %ecx
	movb	%cl, -246(%rbp)
	shrl	$24, %eax
	movb	%al, -245(%rbp)
	movl	-324(%rbp), %eax
	movb	%al, -244(%rbp)
	movb	%ah, -243(%rbp)  # NOREX
	movl	%eax, %ecx
	shrl	$16, %ecx
	movb	%cl, -242(%rbp)
	shrl	$24, %eax
	movb	%al, -241(%rbp)
	leaq	L_.str.13(%rip), %r13
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-255(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-254(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-253(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-252(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-251(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-250(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-249(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-248(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-247(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-246(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-245(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-244(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-243(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-242(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-241(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	-240(%rbp), %eax
	movb	%al, -256(%rbp)
	movb	%ah, -255(%rbp)  # NOREX
	movl	%eax, %ecx
	movzbl	%al, %esi
	shrl	$16, %eax
	movb	%al, -254(%rbp)
	shrl	$24, %ecx
	movb	%cl, -253(%rbp)
	movl	-236(%rbp), %eax
	movb	%al, -252(%rbp)
	movb	%ah, -251(%rbp)  # NOREX
	movl	%eax, %ecx
	shrl	$16, %ecx
	movb	%cl, -250(%rbp)
	shrl	$24, %eax
	movb	%al, -249(%rbp)
	movl	-232(%rbp), %ebx
	movb	%bl, -248(%rbp)
	movb	%bh, -247(%rbp)  # NOREX
	movl	%ebx, %eax
	shrl	$16, %eax
	movb	%al, -246(%rbp)
	shrl	$24, %ebx
	movb	%bl, -245(%rbp)
	movl	-228(%rbp), %r12d
	movb	%r12b, -244(%rbp)
	movl	%r12d, %r14d
	shrl	$8, %r14d
	movb	%r14b, -243(%rbp)
	movl	%r12d, %r15d
	shrl	$16, %r15d
	movb	%r15b, -242(%rbp)
	movl	%r12d, %eax
	shrl	$24, %eax
	movl	%eax, -260(%rbp)        ## 4-byte Spill
	movb	%al, -241(%rbp)
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-255(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-254(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-253(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-252(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-251(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-250(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-249(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-248(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-247(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	-246(%rbp), %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movzbl	%r12b, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	%r14b, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	%r15b, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-260(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	leaq	L_.str.14(%rip), %rdi
	callq	_puts
	movl	$99, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$83, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$224, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$140, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$9, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$96, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$225, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$4, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$205, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$112, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$183, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$81, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$186, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$202, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$208, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$231, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	$10, %edi
	callq	_putchar
	movl	$99, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$83, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$224, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$140, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$9, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$96, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$225, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$4, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$205, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$112, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$183, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$81, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$186, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$202, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$208, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$231, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movq	_aes_tbox@GOTPCREL(%rip), %rsi
	movl	$-1931455645, %edi      ## imm = 0x8CE05363
	callq	_tbox_mix_columns
	movl	%eax, %ebx
	movzbl	%bl, %r15d
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r15d, %esi
	callq	_printf
	movzbl	%bh, %esi  # NOREX
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%esi, %r14d
	movl	%r14d, -264(%rbp)       ## 4-byte Spill
	callq	_printf
	movl	%ebx, %eax
	shrl	$16, %eax
	movzbl	%al, %r12d
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, %esi
	callq	_printf
	shrl	$24, %ebx
	movl	%ebx, -260(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$9, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$96, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$225, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$4, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$205, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$112, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$183, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$81, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$186, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$202, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$208, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$231, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	$81879049, %edi         ## imm = 0x4E16009
	movq	_aes_tbox@GOTPCREL(%rip), %rsi
	callq	_tbox_mix_columns
	movl	%eax, %ebx
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r15d, -300(%rbp)       ## 4-byte Spill
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-260(%rbp), %r14d       ## 4-byte Reload
	movl	%r14d, %esi
	callq	_printf
	movzbl	%bl, %esi
	movl	%esi, -272(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	%bh, %esi  # NOREX
	movl	%esi, -268(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	%ebx, %eax
	shrl	$16, %eax
	movzbl	%al, %esi
	movl	%esi, -288(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	shrl	$24, %ebx
	movl	%ebx, -284(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$205, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$112, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$183, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$81, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$186, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$202, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$208, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$231, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	$1370976461, %edi       ## imm = 0x51B770CD
	movq	_aes_tbox@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	callq	_tbox_mix_columns
	movl	%eax, %ebx
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-264(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, -312(%rbp)       ## 4-byte Spill
	movl	%r12d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-272(%rbp), %r14d       ## 4-byte Reload
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-268(%rbp), %r15d       ## 4-byte Reload
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-288(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-284(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	movzbl	%bl, %esi
	movl	%esi, -296(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	%bh, %esi  # NOREX
	movl	%esi, -292(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	%ebx, %eax
	shrl	$16, %eax
	movzbl	%al, %esi
	movl	%esi, -280(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	shrl	$24, %ebx
	movl	%ebx, -276(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$186, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$202, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$208, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$231, %esi
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	$-405747014, %edi       ## imm = 0xE7D0CABA
	movq	_aes_tbox@GOTPCREL(%rip), %rsi
	callq	_tbox_mix_columns
	movl	%eax, %ebx
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-300(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-264(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-260(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-288(%rbp), %r14d       ## 4-byte Reload
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-284(%rbp), %r15d       ## 4-byte Reload
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-296(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-292(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-280(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-276(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	movzbl	%bl, %esi
	movl	%esi, -308(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movzbl	%bh, %esi  # NOREX
	movl	%esi, -304(%rbp)        ## 4-byte Spill
	xorl	%eax, %eax
	movq	%r13, %rdi
	callq	_printf
	movl	%ebx, %eax
	shrl	$16, %eax
	movzbl	%al, %r12d
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, %esi
	callq	_printf
	shrl	$24, %ebx
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movl	$10, %edi
	callq	_putchar
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-300(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-264(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-312(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-260(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-272(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-268(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r14d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r15d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-296(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-292(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-280(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-276(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-308(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	-304(%rbp), %esi        ## 4-byte Reload
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%r12d, %esi
	callq	_printf
	xorl	%eax, %eax
	movq	%r13, %rdi
	movl	%ebx, %esi
	callq	_printf
	movl	$10, %edi
	callq	_putchar
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	cmpq	-48(%rbp), %rax
	jne	LBB2_4
## BB#3:
	xorl	%eax, %eax
	addq	$312, %rsp              ## imm = 0x138
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB2_4:
	callq	___stack_chk_fail
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"tbox_mix_columns (%08x)\n"

L_.str.1:                               ## @.str.1
	.asciz	"Note that words are in the wrong order."

L_.str.2:                               ## @.str.2
	.asciz	"tbox[%02x] = %08x\n"

L_.str.3:                               ## @.str.3
	.asciz	"t1 = %08x\n"

L_.str.4:                               ## @.str.4
	.asciz	"t2 = %08x\n"

L_.str.5:                               ## @.str.5
	.asciz	"t3 = %08x\n"

L_.str.6:                               ## @.str.6
	.asciz	"t4 = %08x\n"

L_.str.7:                               ## @.str.7
	.asciz	"%08x\n"

L_.str.9:                               ## @.str.9
	.asciz	"key schedule:"

L_.str.10:                              ## @.str.10
	.asciz	"w[%2d] =\t"

L_.str.13:                              ## @.str.13
	.asciz	"%02x"

L_.str.14:                              ## @.str.14
	.asciz	"MixColumns test"


.subsections_via_symbols
