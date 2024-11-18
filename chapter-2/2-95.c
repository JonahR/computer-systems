#include <stdio.h>
#include <limits.h>
#include <math.h>

typedef unsigned float_bits;

int float_f2i(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	unsigned bias = 127;
	int E = exp - bias;
	if(E < 0) {
		return 0;
	}
	if(E >= 31) {
		return 0x80000000;
	}
	int normalize = (1 << 23) + frac;
	if (E < 23) {
		normalize >>= 23 - E;
	} else {
		normalize <<= E - 23;
	}
	if (sign) {
		return ~normalize + 1;
	} else {
		return normalize;
	}
	
}

int main() {
	for(float_bits i = 0; i <= UINT_MAX; i++) {
		float f1 = *((float *)&i);
		int i1 = (int) f1;
		int i2 = float_f2i(i);
		if(i1 != i2) {
			printf("cast: %d f2i: %d i:%X\n", i1, i2, i);
		}
	}
}
