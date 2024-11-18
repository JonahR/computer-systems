#include <stdio.h>

int any_odd_one(unsigned x) {
	return !!(x & 0x55555555);
}

int main() {
	printf("0: %X\n", any_odd_one(0));
	printf("0x00000050: %X\n", any_odd_one(0x00000050));
	printf("0x88888888: %X\n", any_odd_one(0x88888888));
	return 0;
}
