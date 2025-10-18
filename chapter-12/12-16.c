#include "csapp.h"

void *thread(void *args);


int main(int argc, char **argv)
{
  int i, n;
  pthread_t *tidv;

  if (argc != 2) {
    printf("usage: %s <n>\n", argv[0]);
    exit(0);
  }

  n = atoi(argv[1]);

  tidv = (pthread_t *)Malloc(n * sizeof(pthread_t));
  for (i = 0; i < n; i++) {
    Pthread_create(&tidv[i], NULL, thread, NULL);
  }

  for (i = 0; i < n; i++) {
    Pthread_join(tidv[i], NULL);
  }

  exit(0);
}

void *thread(void *vargp)
{
  printf("Hello, world\n");
  return NULL;
}

/*
  Create N joinable threads given by command line
*/
