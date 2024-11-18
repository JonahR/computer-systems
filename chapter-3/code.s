	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 14, 2
	.globl	_sum                            ## -- Begin function sum
	.p2align	4, 0x90
_sum:                                   ## @sum
	.cfi_startproc
## %bb.0:
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset %ebp, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register %ebp
	calll	L0$pb
L0$pb:
	popl	%ecx
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	%eax, _accum-L0$pb(%ecx)
	popl	%ebp
	retl
	.cfi_endproc
                                        ## -- End function
	.globl	_accum                          ## @accum
.zerofill __DATA,__common,_accum,4,2
.subsections_via_symbols
