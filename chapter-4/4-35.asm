irmovl Stack, %esp
irmovl rtptr, %eax
pushl %eax // puts return address on top of stack
xor %eax, %eax
jne Target // This branch is not taken
irmovl $1, %eax
halt
Target: 
ret
irmovl $2, %eax
halt
rtptr:
irmovl $3, %eax
halt
.pos 0x100
Stack

// %eax should contain 1 after completion.
