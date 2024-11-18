#include <assert.h>
#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

int first_one_finder(unsigned u){
	int val = 32;
	while((u & 0x80000000) == 0) {
		val = val - 1;
		u = u << 1;
	}
	return val;
}

int last_one_finder(unsigned u) {
	int val = 1;
	while((u & 0x1) == 0) {
		val = val + 1;
		u = u >> 1;
	}
	return val;
}

float float_i2f(int i) {
	if (i == 0) {
		return 0;
	}
	if (i == INT_MIN) {
		int sign = 1;
		int exp = 127 + 31;
		unsigned frac = 0;
		unsigned val = (sign << 31) | (exp << 23) | frac;
		return *(float *)&val;

	}
	unsigned u = (unsigned) i;
	int sign = (u >> 31) &0x1;
	if (sign) {
		u = ~u + 1;
	}
	int first_one = first_one_finder(u);
	int last_one = last_one_finder(u);
	int E = (first_one - 1) + 127;
	unsigned frac = ((u << (32 - first_one)) & 0x7fffffff) >> 8;
	
	// Let's do rounding
	if (first_one > 24) {
		int cut_off_one = first_one - 24;
		unsigned cut_off_val = u & (0x1 << (cut_off_one - 1));
		if (cut_off_val != 0) {
			if(cut_off_one == last_one) {
				if(frac & 0x1) {
					frac = frac + 1;
				}
			} else {
				frac = frac + 1;
			}
			// carry over on frac, increase exponent
			if(frac & 0x00800000) {
				//printf("we should carry over");
				E = E + 1;
				frac = frac & 0xFF7FFFFF;
			}
		}
	}
	float_bits f = (sign << 31) | (E << 23) | frac;
	//printf("float_bits: %X\n", f);
	return *(float *)&f;
}

int main() {
	for(int i = INT_MIN; i < INT_MAX; i++) {
		float f1 = float_i2f(i);
		float f2 = (float) i;
		if(f1 != f2) {
			printf("cast: %f f2i: %f i:%X\n", f2, f1, i);
		}
	}
	float f1 = float_i2f(INT_MAX);
	float f2 = (float) INT_MAX;
	if(f1 != f2) {
		printf("cast: %f f2i: %f i:%X\n", f2, f1, INT_MAX);
	}

}
