	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 14, 2
	.globl	_simple_l                       ## -- Begin function simple_l
	.p2align	4, 0x90
_simple_l:                              ## @simple_l
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rsi, %rax
	addq	(%rdi), %rax
	movq	%rax, (%rdi)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
