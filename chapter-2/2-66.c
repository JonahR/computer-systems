#include <stdio.h>

int leftmost_one(unsigned x) {
	// Use bit smearing to make all bits to left 1. Than add 1 and shift right.
	x = (x >> 16) | x;
	x = (x >> 8) | x;
	x = (x >> 4) | x;
	x = (x >> 2) | x;
	x = (x >> 1) | x;
	x = x + 1;
	return x >> 1;
}

int main() {
	printf("%X\n", leftmost_one(0xFF00));
	printf("%X\n", leftmost_one(0x6600));
	printf("%X\n", leftmost_one(0x0));
}
