popl %esp
nop
nop
rrmovl %esp, %eax

// The popl will be in the write back stage when rrmovl is in decode. If the rules were switched the incremented stack pointer would incorrectly be inserted into %eax.
