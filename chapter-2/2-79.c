#include <stdio.h>
#include <limits.h>

int threefourths(int x) {
	printf("x: %X\n", x);
	printf("Answer: %f\n", (0.75 * x));
	int mask = (x & 0x3);
	int remainder = 0;
	(mask & 0x2) && (remainder = mask - 1);

	int neg = INT_MIN & x;
	neg && (remainder = 0);
	neg && (mask = mask & 0x3);
	neg && ( remainder = (mask));

	printf("Value pre remainder: %d\n", (x>>2)+(x>>2)+(x>>2));
	printf("Valie of remainder: %d\n", remainder);
	return (x >> 2) + (x >> 2) + (x >> 2) + remainder;
}

int main() {
	//printf("%d\n", threefourths(60));
	//printf("%d\n", threefourths(61));
	//printf("%d\n", threefourths(62));
	//printf("%d\n", threefourths(63));
	printf("%d\n", threefourths(-60));
	printf("%d\n", threefourths(-61));
	printf("%d\n", threefourths(-62));
	printf("%d\n", threefourths(-63));
}
