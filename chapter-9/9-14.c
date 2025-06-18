#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

extern int errno;

int main() {
  int fd;
  struct stat stat;
  char *bufp;
  
  if((fd = open("hello.txt", O_RDWR)) == -1) {
    fprintf(stderr, "open failed: %s\n", strerror(errno));
    exit(1);
  }

  fstat(fd, &stat);

  if((bufp = mmap(NULL, stat.st_size, PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    fprintf(stderr, "open failed: %s\n", strerror(errno));
    exit(1);
  }

  *bufp = 'J';
  
  return 0;
}
