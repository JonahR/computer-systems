#include "csapp.h"

int main(int argc, char **argv)
{
  int n, fd;
  rio_t rio;
  char buf[MAXLINE];

  if( argv[1] != NULL) {
    fd = Open(argv[1]);
    Dup2(fd, STDIN_FILENO);
  }

  Rio_readinitb(&rio, STDIN_FILENO);
  while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    Rio_writen(STDOUT_FILENO, buf, n);
}
