#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y) {

	// Edge case for 0 - INT_MIN
	
	int edge = (x == 0) && (y == INT_MIN);
	int x_sign = (x >> 31) & 0x1;
	int y_sign = (y >> 31) & 0x1;
	int ans_sign = ((x - y) >> 31) & 0x1;

	return !(((x_sign ^ y_sign) && (x_sign ^ ans_sign))) || edge;
}

int main() {
	printf("%d\n", tsub_ok(0,0));
	printf("%d\n", tsub_ok(2000000000,100000));
	printf("%d\n", tsub_ok(-2000000000,1000000000));
	printf("%d\n", tsub_ok(INT_MIN, 0));
	printf("%d\n", tsub_ok(0, INT_MIN));
}
