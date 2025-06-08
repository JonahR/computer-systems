#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv, char **envp) {
  void *file;
  int fd;
  struct stat stat;


  if (argc < 2) {
    printf("mmapcpoy requires an arugment: filename\n");
    exit(1);
  }

  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    fprintf(stderr, "open error: %s\n", strerror(errno));
    exit(1);
  }

  if (fstat(fd, &stat) < 0) {
    fprintf(stderr, "fstat error: %s\n", strerror(errno));
    exit(1);
  }
    
  if ((file = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0)) < 0) {
    fprintf(stderr, "fd error: %s\n", strerror(errno));
    exit(1);
  }
    
  printf("%s", (char *) file);
}




