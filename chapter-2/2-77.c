#include <stdio.h>
#include <limits.h>

int divide_power2(int x, int k) {
	printf("Correct answer: %d\n", x / (2 << k));
	int isNeg = INT_MIN & x;
	isNeg && (x = x + (1 << k) - 1);
	return x >> k + 1;
}


int main() {
	printf("%d\n", divide_power2(4543, 4));
	printf("%d\n", divide_power2(0, 8));
	printf("%d\n", divide_power2(-233443, 4));
	printf("%d\n", divide_power2(4543, -3));
	printf("%d\n", divide_power2(4543, 3));
}
