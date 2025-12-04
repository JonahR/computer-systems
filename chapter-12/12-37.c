#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXBUF 1024
#define MAXCONNS 128

void *routine(void *arg);

int main() {
  int listenfd, connfd, i, *arg;
  socklen_t clientlen;
  struct sockaddr_in serveraddr, clientaddr;
  pthread_t *thread;
  
  serveraddr.sin_family = AF_INET;
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
    if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0) {
      return -1;
    }
    printf("accepted connection fd: %d\n", connfd);

    thread = (pthread_t *)malloc(sizeof(thread));
    arg = (int *)malloc(sizeof(int));
    *arg = connfd;
    pthread_create(thread, NULL, routine, (void *)arg);  
  }  
  return 0;
}

void *routine(void *arg) {
  int b, connfd;
  char buf[MAXBUF];
  
  pthread_detach(pthread_self());

  connfd = *((int *)arg);
  while ((b = read(connfd, &buf, MAXBUF-1)) > 0) {
    // Stringify the server response
    buf[b] = '\0';
    printf("%s", buf);
  }
  close(connfd);

  return NULL;
}
