// A. 0x30f3fcffffff40630008000000
// irmovl $-4 %ebx
// rmmovl %esi 0x800(%ebx)
// halt

// B.
// 0x200 a06f: pushl %esi
// 0x202 800802000000: call 0x0000000208
// 0x208 30f30a000000: irmovl $10 %ebx
// 0x20E 90: ret

// C.
// 0x300 505407000000: mrmovl $7(%esp), %ebp
// 0x306 10: nop
// 0x307 f0: INS

// D.
// 0x400 6113: subl %ecx, %ebx
// 0x402 730004000000: je 0x400 

// E.
// 0x500 6362: xorl %esi, %edx
// 0x502 a0f0: INS
 
