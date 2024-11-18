#include <stdio.h>

int odd_ones(unsigned x) {
	unsigned y = x >> 16;
	x = x ^ y;
	y = x >> 8;
	x = x ^ y;
	y = x >> 4;
	x = x ^ y;
	y = x >> 2;
	x = x ^ y;
	y = x >> 1;
	x = x ^ y;
	return x & 1;
}

int main() {
	printf("%X\n", odd_ones(0x88888000));
	printf("%X\n", odd_ones(0x0));
	printf("%X\n", odd_ones(0xffffffff));
	printf("%X\n", odd_ones(0xffffefff));
}
