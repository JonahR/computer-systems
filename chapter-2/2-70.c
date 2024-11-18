#include <stdio.h>

int fit_bits(int x, int n) {
	int w = sizeof(int) << 3;
	int offset = w - n;
	return (x << offset >> offset)  == x;
	
}

int main() {
	printf("%X\n", fit_bits(0x0020, 4));
	printf("%X\n", fit_bits(0x0020, 6));
}
