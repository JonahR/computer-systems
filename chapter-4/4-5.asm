// int Sum(int *Start, int Count)
Sum:
	push %ebp
	rrmovl %esp, %ebp
	mrmovl 8(%ebp), %ecx
	mrmovl 12(%ebp), %edx
	xorl %eax, %eax
	andl %edx, %edx
	je End
Loop:
	mrmovl (%ecx), %esi
	rrmovl (%esi), %edi
	irmovl $-1, %ebx	
	xorl %ebx, %edi
	addl $1, %edi
	andl %esi, %esi
	cmovl %edi, %esi
	addl %esi, %eax
	irmovl $4, %ebx
	addl %ebx, %ecx
	irmovl $-1, %ebx
	addl %ebx, %edx
	jne Loop
End:
	rrmovl %ebp, %esp
	popl %ebp
	ret
	
