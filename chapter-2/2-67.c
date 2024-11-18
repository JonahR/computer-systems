#include <stdio.h>
#include <limits.h>

int bad_int_size_is_32() {
	
	return ((((1 << 30) << 30) << 2) != 0) && ((( 1 << 30) << 30) << 4) == 0;

}

int main() {
	printf("%X\n", bad_int_size_is_32());
}
