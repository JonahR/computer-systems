#include "csapp.h"

void echo(int connfd);
void command(void);

int main(int argc, char **argv)
{
  int listenfd, connfd, port, i;
  socketlen_t clientlen = sizeof(struct sockaddr_in);
  struct sockaddr_in clientaddr;
  fd_set read_set, ready_set;
  rio_t *rios[100];

  for (i = 0; i < 100; i++)
    rios[i] = NULL;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  port = atoi(argv[1]);
  listenfd = Open_listenfd(port);

  FD_ZERO(&read_set);
  FD_SET(STDIN_FILENO, &read_set);
  FD_SET(listenfd, &read_set);

  while (1) {
    ready_set = read_set;
    Select(listenfd+1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &ready_set))
      command();
    if (FD_ISSET(listenfd, &ready_set)) {
      connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
      FD_SET(connfd, &read_set);
      Rio_readinitb(rios[i], connfd);
    }
    for (i = 0; i < 100; i++) {
      if (rios[i] == NULL)
	continue;
      if (FD_ISSET(rios[i]->rio_fd, &ready_set))
	  echo(rios[i]);
    }
  }
}

void command(void) {
  char buf[MAXLINE];
  if (!Fgets(buf, MAXLINE, stdin))
    exit(0);
  printf("%s", buf);
}

void echo(rio_t *rio) {
  char buf[MAXLINE];

  if (!Rio_readlineb(rio, buf, MAXLINE)) {
    Close(rio->rio_fd);
    *rio = NULL;
    return;
  }

  printf("%s", buf);
}
  
  
  
