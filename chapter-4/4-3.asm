rSum: pushl %ebp // Save previous base pointer
	rrmovl %esp, %ebp // Set the new base pointer
	mrmovl 8(%ebp), %ecx // Get Start
	mrmovl 12(%ebp), %edx // Get Count
	xorl %eax, %eax // Return 0
	andl %edx, %edx // Test Count
	jle End // If Count <= 0, return
	subl $1, %edx // Count - 1
	addl $4, %ecx // Start + 1
	pushl %edx
	pushl %ecx
	call rSum
	mrmovl (%ecx), %esi
	addl %esi, %eax
End: rrmovl %ebp, %esp
	popl %ebp
	ret
	
