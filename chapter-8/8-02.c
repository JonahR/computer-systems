#include "csapp.h"

int main()
{
	int x = 1;

	if (Fork() == 0) {
		printf("printf1: x=%d\n", ++x);
	}

	printf("printf2: x=%d\n", --x);
	exit(0);
}

// The output of the child process is:
// printf1: x=2
// printf2: x=1

// The output of the parent process is:
// printf2: x=0

