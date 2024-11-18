#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	int is_NaN = (exp == 0xFF) && (frac != 0);
	if (is_NaN) {
		return f;
	}
	
	return (exp << 23) | frac;
}

float_bits float_twice(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	int is_NaN_or_OO = (exp == 0xFF); 
	if (is_NaN_or_OO) {
		return f;
	}
	else if (exp - 1 == 0xFE) {
		exp = 0xFF;
		frac = 0;
	}
	else if (exp == 0) {
		frac = frac << 1;
	}	
	else {
		exp = exp + 1;
	}

	return (sign << 31) | (exp << 23) | frac;
}

float_bits float_half(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	int is_NaN_or_OO = (exp == 0xFF);
	if (is_NaN_or_OO) {
		return f;
	}
	else if (exp == 0x1) {
		exp = exp >> 1;
		frac = frac >> 1;
	}
	else if (exp == 0) {
		frac = frac >> 1;
	}
	else {
		exp = exp - 1;
	}

	return (sign << 31) | (exp << 23) | frac;
}

	

int main() {
	for (float_bits i = 0x3f800000; i < UINT_MAX; i++) {
		float_bits fb = float_absval(i);
		float f1 = *((float *)&fb);
		float f2 = *((float *)&i);
		float abs_f2 = fabsf(f2);
		if(f1 != f2 && (f1 != NaN && abs_f2 != NaN) {
			printf("f1: %9.6f does not equal abs_f2: %9.6f", f1, abs_f2);
		}
		// if(f1 != -f2) {
			// printf("f1: %2.6f f2: %2.6f", f1, f2);
		// }
	}
}
