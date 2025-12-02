#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXBUF 1024

int main() {
  int listenfd, connfd, pid;
  socklen_t clientlen;
  struct sockaddr_in serveraddr, clientaddr;
  char buf[MAXBUF];

  bzero((void *)&serveraddr, sizeof(serveraddr));
  
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = 8080;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);
  
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    return -1;
  }
  if ((bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0) {
    return -1;
  }
  if ((listen(listenfd, 1024)) < 0) {
    return -1;
  }

  while(1) {
    clientlen = sizeof(clientaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0) {
	return -1;
    }
    printf("accepted connection fd: %d\n", connfd);

    if((pid = fork()) < 0) {
      return -1;
    }
    if (pid == 0) {
      bzero((void *)&buf, sizeof(buf));
      while(read(connfd, &buf, MAXBUF) > 0) {
	printf("%s", buf);
	write(connfd, &buf, MAXBUF);
	bzero((void *)&buf, sizeof(buf));
      }
      close(connfd);
      exit(0);
    }
    close(connfd);

    waitpid(0, NULL, WNOHANG);
  }  
  
  return 0;
}
