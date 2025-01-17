irmovl Stack1, %esp
pushl retrn1
mrmovl Stack2, %esp
ret
halt
retrn1:
irmovl %1, %eax
halt
retrn2:
irmovl %2, %eax
halt
Stack2: 0x200

.pos 0x200
retrn2

// This code should set %eax to 2. The ret instruction should take the value at .pos 0x200 because the mrmovl instruction pushes it to the top of the stack
