#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
	int left_shift = (3 - bytenum) << 3;
	return (int) word << left_shift >> 24;
}

int main() {
	printf("%X\n", 0xFFFFFFFF + 0x1); 
	printf("%X\n", xbyte(0x82730AB3, 2));
	printf("%X\n", xbyte(0x82730AB3, 1));
	printf("%X\n", xbyte(0x82730AB3, 0));
}
