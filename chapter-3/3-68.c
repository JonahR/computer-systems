#include <stdio.h>

void good_echo() {
	char buffer[8];
	while(fgets(buffer, sizeof buffer, stdin) != NULL) {
		printf("%s", buffer);
	}
}

int main() {
	good_echo();
}

