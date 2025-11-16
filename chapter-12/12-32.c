#include "csapp.h"

#define MAX_FDS 16

char *tfgets(char *str, int size, FILE *stream);

int main()
{
  char buf[MAXLINE];

  if (tfgets(buf, MAXLINE, stdin) == NULL)
    printf("BOOM!\n");
  else
    printf("%s", buf);

  exit(0);
}

char *tfgets(char *str, int size, FILE *stream) {
  fd_set readfds;
  struct timeval timeout;
  char buf[MAXLINE];
  
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  timeout.tv_sec = 5;
  timeout.tv_usec = 0;
  
  Select(MAX_FDS, &readfds, NULL, NULL, &timeout);

  if(FD_ISSET(STDIN_FILENO, &readfds)) {
    return fgets(buf, MAXLINE, stdin);
  } else {
    return NULL;
  }
}

  
