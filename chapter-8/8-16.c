#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdlib.h>

int counter = 1;

int main() {
	pid_t pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error: %s\n", strerror(errno));
		exit(0);
	}
	if (pid == 0) {
		counter--;
		exit(0);
	}
	else {
		if (wait(NULL) < 0) {
			fprintf(stderr, "fork error: %s\n", strerror(errno));
		}
		printf("counter = %d\n", ++counter);
	}
	exit(0);
}

// The output is: counter = 2
