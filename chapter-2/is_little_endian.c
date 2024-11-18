# include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
	int val = 1;
	byte_pointer b = (byte_pointer) &val;

	if(b[0] || 0) {
		printf("This is little endian");
	}

	int val2 = 16;
	byte_pointer b2 = (byte_pointer) &val;
	if(!(b2[1] || 0)) {
		printf("This is not big endian");
	}
}

int main() {
	is_little_endian();
}

