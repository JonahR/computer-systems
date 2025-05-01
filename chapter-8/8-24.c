#include <sys/errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define N 2

extern const char *const sys_siglist[];

int main() {
	int status, i;
	pid_t pid;

	for (i = 0; i < N; i++) {
		if((pid = fork()) < -1) {
			fprintf(stderr, "fork error: %s\n", strerror(errno));
		}
		if(pid == 0) {
			// Causes a seg fault by writing to random memory below the user stack
			(&i)[1000] = 12;
		}
	}

	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (!WIFEXITED(status))
			printf("child %d terminated by signal %d: %s\n", pid, status, sys_siglist[status]);
	}

	if (errno != ECHILD) {
		printf("waitpid error");
		exit(0);
	}

	exit(0);
}
