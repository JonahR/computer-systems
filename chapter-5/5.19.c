#include <stdio.h>

void *basic_memset(void *s, int c, size_t n) {
	size_t cnt = 0;
	unsigned char *schar = s;
	size_t K = sizeof(unsigned long);

	printf("Size of K: %zu\n", K);
	printf("Address of schar: %p\n", (void*)schar);
	/*
	byte level-writes until the destination address is a multiple of K.
	(K | schar != K) will check if the address stored in schar is a multiple
	of K.
	*/
	while (cnt < n) {
		printf("Address of schar: %p\n", (void*)schar);
		if((size_t) schar % K == 0)
			break;
		*schar++ = (unsigned char) c;
		cnt++;
	}
	printf("This address is aligned: %p\n", (void*)schar);

	/*	
	pack K copies of c into word
	*/
	size_t word_value = 0;	
	size_t *word = &word_value;	
	unsigned char *byte = (unsigned char *)word;
	for (int i = 0; i < K; i++) {
		byte[i] = (unsigned char) c;
	}

	/*
	Word level writes until we reach limit of n
	Note: we must be careful to check that we are able 
	to preform a single word level write.
	*/
	size_t *sword = (size_t *) schar;
	int max_length = n >= K ? n-K : 0;
	while (cnt < max_length) {
		*sword = *word;
		cnt += K;
	}
	
	/*
	Byte level writes until we reach limit of n
	*/
	schar = (unsigned char *) sword;
	while (cnt < n) {
		*schar++ = (unsigned char) c;
		cnt++;
	}

	return s;
}

int main() {
	int n = 1;
	int seq = 8;
	unsigned char bytes[n];
	unsigned char *I = basic_memset(bytes, seq, n);
	for (int i = 0; i < n; i++) {
		printf("Value in %d: %d\n", i, *I);
	}
}

