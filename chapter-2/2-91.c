#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f) {
	// check if "f" is NaN
	// s eeee eeee ffff ffff ffff ffff ffff fff
	// exp = eeee eeee
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	
	if (exp == 0xFF) {
		// if exponent is all 1s, check the frac value
		if (frac != 0) {
			return f;
		}
	}
	
	sign ^= 1;

	return (sign << 31) | (exp << 23) | frac; 
}

int main() {
	for (float_bits i = 0; i <= UINT_MAX; i++) {
		float_bits negate = float_negate(i);
		if (negate ^ (	
