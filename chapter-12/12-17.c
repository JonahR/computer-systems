#include "csapp.h"

void *thread(void *vargp);

int main()
{
  pthread_t tid;

  Pthread_create(&tid, NULL, thread, NULL);
  exit(0);
}

void *thread(void *vargp)
{
  Sleep(1);
  printf("Hello, world\n");
  return NULL;
}

/*
  A. The bug is the main thread exits before the peer thread finishes sleeping.
  When the main thread exits, since the peer thread is no detached, the peer thread
  is terminated. This occurs before printf can print to standard output.

  B. We can use pthread_join. This will ensure the thread runs to completetion.
*/
