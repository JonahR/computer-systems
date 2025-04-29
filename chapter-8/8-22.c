#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>

int mysystem(char*);

extern char **environ;
/* 
 * main calls /bin/sh -c with the arguements passed in
 */
int main(int argc, char **argv, char **envp) {
	mysystem("ls");
}

int mysystem(char *command) {
	char *argvt[4] = {"sh", "-c", command, NULL};

	if (execve("/bin/sh", argvt, environ) < 0) {
		fprintf(stderr, "execve error: %s\n", strerror(errno));
	}
	exit(errno);
}

