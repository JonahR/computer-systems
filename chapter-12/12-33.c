#include "csapp.h"

char *tfgets(char *str, int len, FILE *stream);
void *sleep_t(void *);
void *fgets_t(void *);

struct fgets_args{
  char *ret;
  char *str;
  int len;
  FILE *stream;
};

int t1_done = 0;
int t2_done = 0;

int main()
{
  char buf[MAXLINE];

  if (tfgets(buf, MAXLINE, stdin) == NULL)
    printf("BOOM!\n");
  else
    printf("%s", buf);

  exit(0);
}

char *tfgets(char *str, int len, FILE *stream) {
  pthread_t thread1, thread2;
  struct fgets_args args;
  void *result;

  args.str = str;
  args.len = len;
  args.stream = stream;
  
  Pthread_create(&thread1, NULL, fgets_t, &args);
  Pthread_create(&thread2, NULL, sleep_t, NULL);

  while(!t1_done && !t2_done) {};
  if(t1_done) {
    return NULL;
  } else {
    return args.ret;
  }
}

void *sleep_t(void *arg) {

  Sleep(5);

  t1_done = 1;
  
  Pthread_exit(NULL);

  return 0;
}

void *fgets_t(void *arg) {
  struct fgets_args *val;

  val = (struct fgets_args *)arg;

  val->ret = fgets(val->str, val->len, val->stream);

  t2_done = 1;

  Pthread_exit(NULL);

  return 0;
}

