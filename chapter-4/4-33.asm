irmovl $1, %edi
irmovl $5, %esi
subl %esi, %edi
cmovge %eax, %ebx // This fails
rrmovl %ebx, %esi

// The E_dstE signal cannot be used because if a conditional move did fail and
// we were using E_dstE, the rrmovl would move the value of %eax into %esi.
