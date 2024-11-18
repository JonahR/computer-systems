# Assumes little endian machine
movl 16(%ebp), %esi // Get y[l]
movl 12(%ebp), %eax // Get x[l]
movl %eax, %edx // Move x into edx reg
sarl $31, %edx // Get x[h]
movl 20(%ebp), %ecx // Get y[h] 
imull %eax, %ecx // x[l] * y[h]
movl %edx, %ebx // x[h] 
imull %esi, %ebx //y[l] * x[h] 
addl %ebx, %ecx // result_h = x[l] * y[h] + x[h] * y[l]
mull %esi // carry = x[l] * y[l]
leal (%ecx, %edx), %edx // result_h += carry[h]  
movl 8(%ebp), %ecx // Get dest
movl %eax, (%ecx) // Set low order bits to carry[low]
movl %edx, 4(%ecx) // Set high order bits to result_h
 

// y[h] y[l]
// x[h] x[l]

// x[l] * y[l] = ans[l] + carry
// x[h] * y[l] = ans[h1] (partial)
// x[l] * y[h] = ans[h2] (partial)
// ans[h1] + ans[h2] + carry = ans[h]
// det = ans[l], ans[h] (little endian)

// visualize via 13 * 5

// y = 13 =   1 | 3
// x = 5 =    0 | 5

// 5 * 3 =  1 | 5 (carry)
// 0 * 3 =  0 | 0 (h1)
// 5 * 10 = 5 | 0 (h2)

// ans[l] = carry[l] = 5
// ans[h] = h1[h] + h2[h] + carry[h] = 0 + 5 + 1 = 6

// ans = 6 | 5 = 65
// 13 * 5 = 65

// Note. This only works because x is an int.
