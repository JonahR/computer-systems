#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp) {
	if (execve("/bin/ls", argv, envp) < 0) {
		fprintf(stderr, "execve error: %s\n", strerror(errno));
		exit(0);
	}
}

