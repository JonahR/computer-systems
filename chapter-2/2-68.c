#include <stdio.h>

int lower_one_mask(int n) {
	return (1 << (n - 1)) + ((1 << (n - 1)) - 1);
}

int main() {
	printf("%X\n", lower_one_mask(6));
	printf("%X\n", lower_one_mask(17));
	printf("%X\n", lower_one_mask(32));
	printf("%X\n", lower_one_mask(1));
}
