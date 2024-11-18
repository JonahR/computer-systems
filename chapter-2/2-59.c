#include <stdio.h>

unsigned int yield_word(unsigned int a, unsigned int b) {
	printf("Val of b: %X\n", b);
	unsigned int a_mask = 0x000000FF;
	unsigned int a_masked = a & a_mask;
	unsigned int b_mask = 0xFFFFFF00;
	unsigned int b_masked = b & b_mask;
	printf("Val of b: %X Val of b_mask: %X Val of b_masked: %X\n", b, b_mask, b_masked);
	return a_masked | b_masked;
}

int main() {
	unsigned int x = 0x89ABCDEF;
	unsigned int y = 0x76543210;
	printf("Val of y: %X\n", y);
	unsigned int z;
	z = yield_word(x, y);
	printf("Val of z: %X\n", z);
}
