#include <strings.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXBUF 1024
#define MAXCONNS 128

int main() {
  int listenfd, connfd, i, b, n;
  socklen_t clientlen;
  struct sockaddr_in serveraddr, clientaddr;
  char buf[MAXBUF];
  fd_set readfds, allfds;
  int conns[MAXCONNS];
  
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

  bzero(&conns, sizeof(int) * MAXCONNS);
  FD_ZERO(&allfds);
  FD_SET(listenfd, &allfds);
  
  while(1) {
    FD_COPY(&allfds, &readfds);

    if ((n = select(FD_SETSIZE, &readfds, NULL, NULL, NULL)) < 0) {
      return -1;
    }
    printf("value of n: %d", n);
    
    if (FD_ISSET(listenfd, &readfds)) {
      clientlen = sizeof(clientaddr);
      if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0) {
	return -1;
      }
      FD_SET(connfd, &allfds);
      for (i = 0; i < MAXCONNS; i++) {
	if (conns[i] == 0) {
	  conns[i] = connfd;
	  break;
	}
      }
      printf("accepted connection fd: %d\n", connfd);
      n--;
    }
      
    for (i = 0; i < MAXCONNS && n > 0; i++) {
      if (FD_ISSET(conns[i], &readfds)) {
	  if ((b = read(conns[i], &buf, MAXBUF-1)) < 0) {
	    return -1;
	  }
	  if (b == 0) { // close the connection
	    close(conns[i]);
	    FD_CLR(conns[i], &allfds);
	    conns[i] = 0;
	    
	  } else {
	  // Stringify the server response
	    buf[b] = '\0';
	    printf("%s", buf);
	  }
	  n--;
	}
      }
  }  
  return 0;
}
