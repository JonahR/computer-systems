#include "csapp.h"
#define N 4

void *thread(void *vargp);

int main()
{
  pthread_t tid[N];
  int a[N];

  for (i = 0; i < N; i++) {
    a[i] = i;
    Pthread_create(&tid[i], NULL, thread, &a[i]);
  }
  for (i = 0; i < N; i++)
    Pthread_join(tid[i], NULL);
  exit(0);
}

void *thread(void *vargp)
{
  int myid = *((int *)vargp);
  printf("Hello from thread %d\n", a[myid]);
  return NULL;
}

/*
  A. Here is an outline of an approach that does not use malloc or free. We can create
  an array of integers, 1-4. And pass the index to the thread.

  B. The advantage is this elimates costly calls to malloc and free, thereby increasing the speed.
  The disadvatage is we most allocate space on the main threads stack for an integer for each thread.
*/
