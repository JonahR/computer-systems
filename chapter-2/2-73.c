#include <stdio.h>

int saturating_add(int x, int y) {
	unsigned mask = 0x80000000;
	int sum = x + y;
	int same_sign = !((x & mask) ^ (y & mask));
//	printf("%d\n", same_sign);
	int overflow = (same_sign) && ((x & mask) ^ (sum & mask));
//	printf("%d\n", overflow);
	int overflow_mask = ((overflow << 31) >> 31);
//	printf("overflow_mask: %X\n", overflow_mask);
	int digit_to_remove = overflow && (sum & mask);
	unsigned mask_max = ((0x7FFFFFFF + !!(x & mask)) & overflow_mask);
//	printf("mask_max:%X\n", mask_max);
	int final_sum = (sum & ~overflow_mask) | mask_max;
	printf("final_sum: %d\n", final_sum);
	return final_sum;
}

int main() {
	printf("%d\n", saturating_add(0, 1));
//	printf("%d\n", saturating_add(0, 0));
	printf("%d\n", saturating_add(0, 0));
	printf("%d\n", saturating_add(-1, 0));
	printf("%d\n", saturating_add(24, 80));
	printf("%d\n", saturating_add(2000000000, 2000000000));
	printf("%d\n", saturating_add(-2000000000, -2000000000));
}
