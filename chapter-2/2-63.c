#include <stdio.h>
#include <limits.h>

unsigned srl(unsigned x, int k) {
	printf("Param x value: %X\n", x);
	/* Perform shift arithmetically */
	unsigned xsra = (unsigned) x >> k;
	
	int word_size = 8*sizeof(int);
	int difference = word_size - k;
	
	// Stard with a mask equal to 0x11...11
	int mask = -1;

	// Left shift k bits. This is the number of bits we want to 0
	// for the logical right shift. The following steps will move
	// the k 0 bits on the right to the left.
	mask = mask << k;

	// Nor the mask to get the left shift values as 1s
	// Ex. 1111 << 2 => 1100. ~1100 => 0011.
	mask = ~mask;

	// Left shift the 1s, the difference between word size and k
	// to get them to the begging of the word.
	// Ex. difference = 4 - 2 = 2. 0011 << 2 => 1100
	mask = mask << difference;

	// Not the mask in preperation to AND it with xsra to perform
	// the logical right shift
	printf("Vale of mask before final NOT: %x\n", mask);
	mask = ~mask;

	// The mask will now look like 0011. This can be ANDed with xsra
	// such as 1101 to get 0001.
	xsra = xsra & mask;

	return xsra;
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	printf("Logic right shift value of %X is: %X\n", x, xsrl);

	// The mask will be used to keep or zero out right shifted ones
	unsigned mask = 0; 

	// difference is the number of bits not changed by the right shift
	int wordSize = 8*sizeof(int);
	int difference = (wordSize - k);

	// test bit is checking if arithmetic right shift should add 1s or 0s
	// if test bit is 1, we should shift with 1s. 0 we should shift with 0s
	int testBit = 1;
	testBit = testBit << (wordSize - 1);
	printf("The test bit mask is: %X\n", testBit);
	testBit = testBit & x;
	testBit = !!testBit;
	printf("The test bit is: %X\n", testBit);

	// creating mask to AND to xsrl
	unsigned shiftValues = UINT_MAX;
	shiftValues = shiftValues << (difference - 1);
	printf("The shiftValues value is: %X\n", shiftValues);
	mask = mask - testBit;
	printf("Mask after subtracting the testBit: %X\n", mask);
	mask = mask & shiftValues;

	// mask should now either be 000000 or 111000
	printf("Mask value is: %X\n", mask);
	
	xsrl = xsrl | mask;

	return xsrl;
}


int main() {
	printf("sra value of 0xFF123456 and 0: %X\n", sra(0xFF123456, 0));
	printf("sra value of 0x00FFFFFF and 0: %X\n", sra(0x00FFFFFF, 0));
	printf("sra value of 0xFF123456 and 31: %X\n", sra(0xFF123456, 31));
	printf("sra value of 0x00123456 and 31: %X\n", sra(0x00123456, 31));
	printf("sra value of 0xFF123456 and 8: %X\n", sra(0xFF123456, 8));
	printf("sra value of 0x00123456 and 8: %X\n", sra(0x00123456, 8));
}
