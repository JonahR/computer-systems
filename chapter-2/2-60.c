#include <stdio.h>

unsigned replace_byte (unsigned x, int i, unsigned char b) {
	if(i >= 0 && i < sizeof(x)) {
		unsigned mask = 0x000000FF;
		unsigned b_mask = b;
		for (int j = 0; j < i; j++) {
			mask = mask << 8;
			b_mask = b_mask << 8;
		}
		printf("mask val: %X b_mask val: %X\n", mask, b_mask);
		unsigned foil = ~mask;
		printf("foil val: %X\n", foil);
		x = x & foil;
		printf("x & val: %X\n", x);
		x = x | b_mask;
		printf("x | val: %X\n", x);
	}
	return x;
}

int main() {
	printf("%X\n", replace_byte(0x12345678, 2, 0xAB));
	printf("%X\n", replace_byte(0x12345678, 0, 0xAB));
}
