#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv, char **env) {
	printf("Testing if this compiles: %s\n", environ[0]);
	int i;
	
	i = 0;
	while (environ[i] != NULL) {
		printf("Env variable #%d = %s\n", i, environ[i]);
		i = i + 1;
	}


	for(i = 0; i < argc; i++)
		printf("Arg variable #%d = %s\n", i, argv[i]);


	exit(0);
}

