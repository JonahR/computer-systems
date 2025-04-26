#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
	printf("Caught SIGINFO\n");
}

unsigned int snooze(unsigned int secs) {
	int remaining;

	remaining = sleep(secs);
	printf("Slept for %d of %d secs\n", secs - remaining, secs);

	return(0);
}

int main(int argc, char **argv, char **envp) {
	unsigned int timer;
	pid_t pid;

	if(argc != 2) {
		printf("snooze requires a single arg\n");
		exit(0);
	}
	// Using SIGINFO because SIGINT was not being forwarded by the shell
	if(signal(SIGINFO, handler) == SIG_ERR) { 
		exit(1);
	}

	timer = *argv[1] - 48; // Simple ASCII conversion of char to int
	(void)snooze(timer);
	exit(0);
}

