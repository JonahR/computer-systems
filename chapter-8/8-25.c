#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <signal.h>

#define SIZE 100

char line[SIZE];
typedef void handler_t(int);


handler_t *Signal(int signum, handler_t *handler) {
	struct sigaction action, old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;

	if (sigaction(signum, &action, &old_action) < 0) {
		perror("sigaction");
	}
	return (old_action.sa_handler);
}



void handler1(int sig) {
}

void handler2(int sig) {
	exit(0);
}

char *tfgets(char * restrict str, int size, FILE * restrict stream) {
	pid_t pid;

	Signal(SIGCHLD, handler2);
	Signal(SIGALRM, handler1);
	alarm(5);
	if ((pid = fork()) < 0) {
		perror("fork() failed");
	}
	if (pid == 0) {
		return fgets(str, size, stream);
	}
	pause();
	if (kill(pid, SIGKILL) < 0) {
		perror("kill() failed");	
	}
	return NULL;
}

int main() {
	if (tfgets(line, SIZE, stdin) == NULL) {
		perror("tfget failed");
		exit(1);
	}
	printf("%s", line);
	exit(0);
}
