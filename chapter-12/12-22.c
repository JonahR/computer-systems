#include "csapp.h"
#define MAX_CONN 64

int echo(int fd);
void command(void);

int main(int argc, char **argv)
{
  int listenfd, connfd, port, maxfd, i;
  socklen_t clientlen = sizeof(struct sockaddr_in);
  struct sockaddr_in clientaddr;
  fd_set read_set, ready_set;
  int fds[MAX_CONN];

  for (i = 0; i < MAX_CONN; i++)
    fds[i] = -1;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  port = atoi(argv[1]);
  maxfd = listenfd = Open_listenfd(port);
  
  FD_ZERO(&read_set);
  FD_SET(STDIN_FILENO, &read_set);
  FD_SET(listenfd, &read_set);

  while (1) {
    printf("ENTERING WHILE LOOP!!!\n");
    ready_set = read_set;
    Select(maxfd+1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &ready_set))
      command();
    if (FD_ISSET(listenfd, &ready_set)) {
      connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
      FD_SET(connfd, &read_set);
      for (i = 0; i < MAX_CONN; i++)
	if (fds[i] == -1) {
	  fds[i] = connfd;
	  break;
	}
      if (i == MAX_CONN){
	printf("Too many connections\n");
	exit(1);
      }
      
      if (connfd > maxfd)
	maxfd = connfd;
      printf("I made a new connection: %d\n", fds[i]);
      fflush(stdout);
    }
    for (i = 0; i < MAX_CONN; i++) {
      if (fds[i] != -1 && FD_ISSET(fds[i], &ready_set))
	if (echo(fds[i]) < 0) {
	  FD_CLR(fds[i], &read_set);
	  Close(fds[i]);
	  fds[i] = -1;
	}
    }
  }
}

void command(void) {
  char buf[MAXLINE];
  if (!Fgets(buf, MAXLINE, stdin))
    exit(0);
  printf("%s", buf);
}

int echo(int fd) {
  char buf[MAXLINE];

  if (rio_readn(fd, buf, MAXLINE) <= 0) {
    return -1;
  }

  printf("%s\n", buf);
  
  return 0;
}
  
  
  
