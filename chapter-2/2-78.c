#include <stdio.h>
#include <limits.h>

int mul3div4(int x) {
	int mul = (x << 1) + x;
	int neg = INT_MIN & mul;
	neg && (mul = mul + (1 << 2) - 1);
	return mul >> 2;
}

int main() {
	printf("%d\n", mul3div4(5));
	printf("%d\n", mul3div4(-234));
}
