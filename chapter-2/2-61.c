#include <stdio.h>

int any_bit_one(int x) {
	unsigned char val = !!x;
	printf("param value = %X, Any bit 0 value = %X\n", x, val);
	return val;
}

int any_bit_zero(int x) {
	unsigned char val = !!~x;
	printf("param value = %X, return val = %X\n", x, val);
	return val;
}

int least_has_1(int x) {
	int mask = 0x000000FF;
	mask = mask & x;
	any_bit_one(mask);
}

void most_has_0(int x) {
	int mask = 0x00FFFFFF;
	mask = mask | x;
	printf("This is the mask: %X\n", mask);
	any_bit_zero(mask);
}

int int_shifts_are_arithmetic() {
	int x = -1;
	printf("Value of -1: %X\n", x);
	x = x >> 1;
	printf("Value of right shift: %X\n", x);
	return !any_bit_zero(x);
}

int main() {
	printf("Right shift are arithmetic: %i\n", int_shifts_are_arithmetic());
}
