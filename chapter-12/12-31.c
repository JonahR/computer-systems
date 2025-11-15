#include "csapp.h"

void handler(int signal);
char *tfgets(char *str, int size, FILE *stream);

sigjmp_buf env;

int main(int argc, char **argv) {
  char line[1000];

  tfgets(line, 1000, stdin);

  printf("%s", line);

  return 0;
}

char *tfgets(char *str, int size, FILE *stream) {
  char *ret;

  Signal(SIGCHLD, handler);
  if(sigsetjmp(env, 1)) {
    Waitpid(0, NULL, 0);
    return NULL;
  }

  if(Fork() == 0) {
    Sleep(5);
    exit(0);
  }

  fgets(str, size, stream);

  return str;
}

void handler(int signal) {
  siglongjmp(env, 1);
}

  
