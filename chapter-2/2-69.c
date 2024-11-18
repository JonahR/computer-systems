#include <stdio.h>

unsigned rotate_left(unsigned z, int n) {
	return (z >> (32 - n)) | (z << n);
}

int main() {
	printf("%X\n", rotate_left(0x12345678, 4));
	printf("%X\n", rotate_left(0x12345678, 20));
	printf("%X\n", rotate_left(0x12345678, 0));
}
