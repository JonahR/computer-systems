# Execution begins.
	.pos 0
init:   irmovl Stack, %esp
	irmovl Stack, %ebp
	call Main
	halt

.align 4
array: .long 0x5
	.long 0x4
	.long 0x3
	.long 0x2
	.long 0x1

Main:   pushl %ebp
	rrmovl %esp, %ebp
	irmovl $5, %eax
	pushl %eax # push the count
	irmovl array, %eax
	pushl %eax  # push the array
	call bubble_p
	rrmovl %ebp, %esp
	popl %ebp
	ret

	# bubble_p(int *array, int count)
bubble_p 
	pushl %ebp
	rrmovl %esp, %ebp
	mrmovl 8(%ebp), %ecx # array[i]
	mrmovl 12(%ebp), %edx # count
	xorl %ebx, %ebx // last
	rrmovl %edx, %ebx
	subl $1, %ebx // last = count -1
	jle done_outer // GOTO if count - 1 <= 0
	xorl %esi, %esi // i
	rrmovl %esi, %eax
	subl %ebx, %eax // i - last
	jge done_inner // GOTO if i >= last
s_outer
s_inner 
	rrmovl %ecx, %edi
	addl $4, %edi // array[i + 1]
	rrmovl %ecx, %eax
	mrmovl (%edi), %eax // Get array[i+1]
	mrmovl (%ecx), %edx // Get array[i]
	rrmovl %eax, %edi
	subl %edx, %edi // array[i+1] - array[i]
	rrmovl %eax, %edi
	cmovl %edx, %eax
	cmovl %edi, %edx
	rmmovl %edx, (%edi) // array[i+1] = array[i]
	rmmovl %eax, (%ecx) // array[i] = t
if_done
	addl $4, %ecx // INC array[i]
	addl $1, %esi // i++
	rrmovl %ebx, %eax
	subl %esi, %eax // last - i
	jl s_inner // GOTO if i < last
done_inner
	subl $1, %ebx // last--
	xor %eax, %eax
	subl %ebx, %eax // last - 0
	jl s_outer // GOTO if last > 0			
done_outer	
	rrmovl %ebp, %esp
	popl %ebp
	ret


.pos 100
Stack	
