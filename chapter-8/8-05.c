#include "csapp.h"

unsigned int snooze(unsigned int secs) {
	int remaining;

	remaining = sleep(secs);
	printf("Slept for %d of %d secs\n", secs - remaining, secs);

	return(0);
}


// int main() {
// 	snooze(3);
// }

