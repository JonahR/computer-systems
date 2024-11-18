#include <stdio.h>


int add_num(int a, int b)
{
	return a + b;
}

int main()
{
	int result;
	
	result = add_num(7, 8);

	printf("The result is: %d\n", result);
	printf("Hello World!\n");
	return 1;
}
