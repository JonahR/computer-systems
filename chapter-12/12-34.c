/*
  Time it takes to multiply a 2500 x 2500 matrix with a 2500 x 2500 matrix.

  1 thread: 

  2 threads

  4 thread:

  8 threads:

  16 threads:
*/						\

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LINE_MAX 100

void matrix(int m, int n, int p, int *A, int *B, int *AB);
void *thread(void *args);
void tmatrix(int t, int M, int N, int P, int *A, int *B, int *AB);
int addMatrix(int M, int P, int *AB);

struct params {
  int M;
  int N;
  int P;
  int *A;
  int *B;
  int *AB;
};

int main()
{
  int m, n, p;
  struct timeval t1, t2;
  int *A, *B, *AB;
  
  printf("M = ");
  scanf("%d", &m);

  printf("N = ");
  scanf("%d", &n);

  printf("P = ");
  scanf("%d", &p);

  A = (int *)malloc(sizeof(int) * m * n);
  B = (int *)malloc(sizeof(int) * n * p);
  AB = (int *)malloc(sizeof(int) * m * p);
  
  gettimeofday(&t1, NULL);
  matrix(m, n, p, A, B, AB);
  gettimeofday(&t2, NULL);
  printf("time for seq. Seconds: %ld. Milliseconds: %u\n", t2.tv_sec-t1.tv_sec,
	t2.tv_usec-t1.tv_usec);
  
  printf("The sum of the matrix is: %d\n", addMatrix(m, p, AB));
  
  gettimeofday(&t1, NULL);
  tmatrix(2, m, n, p, A, B, AB);
  gettimeofday(&t2, NULL);
  printf("time for thread 2. Seconds: %ld. Milliseconds: %u\n", t2.tv_sec-t1.tv_sec,
	 t2.tv_usec-t1.tv_usec);

  gettimeofday(&t1, NULL);
  tmatrix(4, m, n, p, A, B, AB);
  gettimeofday(&t2, NULL);
  printf("time for thread 4. Seconds: %ld. Milliseconds: %u\n", t2.tv_sec-t1.tv_sec,
	 t2.tv_usec-t1.tv_usec);

  gettimeofday(&t1, NULL);
  tmatrix(8, m, n, p, A, B, AB);
  gettimeofday(&t2, NULL);
  printf("time for thread 8. Seconds: %ld. Milliseconds: %u\n", t2.tv_sec-t1.tv_sec,
	 t2.tv_usec-t1.tv_usec);

  gettimeofday(&t1, NULL);
  tmatrix(16, m, n, p, A, B, AB);
  gettimeofday(&t2, NULL);
  printf("time for thread 16. Seconds: %ld. Milliseconds: %u\n", t2.tv_sec-t1.tv_sec,
	 t2.tv_usec-t1.tv_usec);

  printf("The sum of the matrix is: %d\n", addMatrix(m, p, AB));
    
  free(A);
  free(B);
  free(AB);
  
  return 0;
}  

int addMatrix(int M, int P, int *AB) {
  int i, j, sum;

  sum = 0;
  for(i = 0; i < M; i++) {
    for(j = 0; j < P; j++) {
      sum += AB[i] + j;
    }
  }

  return sum;
}

void matrix(int M, int N, int P, int *A, int *B, int *AB) {
  int m, n, p;
  for(m = 0; m < M; m++) {
    for(p = 0; p < P; p++) {
      AB[(m * P) + p] = 0;
      for(n = 0; n < N; n++) {
	      AB[(m * P) + p] += A[(m * N) + n] * B[(n * P) + p];
      }
    }
  }

  return;
}

void tmatrix(int t, int M, int N, int P, int *A, int *B, int *AB) {
  int i, div, row, rem;
  struct params *ps;
  pthread_t *tids;
  int *start;

  row = M / t;
  rem = M % t;

  tids = (pthread_t *)(calloc(sizeof(pthread_t) * t, 0));
  ps = (struct params *)(malloc(sizeof(struct params) * t));

  start = AB;
  for(i = 0; i < t; i++) {
    // For the last iteration, add the remainder to the # of rows the thread calculates
    if(i == t-1) {
      row += rem;
    }
    ps[i].M = row;
    ps[i].N = N;
    ps[i].P = P;
    ps[i].A = A;
    ps[i].B = B;
    ps[i].AB = start;
    pthread_create(&tids[i], NULL, thread, &ps[i]);

    // calculate where the matrix multiplication results should start populating the final matrix
    start += row * P;
  }

  for(i = 0; i < t; i++){
    pthread_join(tids[i], NULL);
  }
  
  return;
}

void *thread(void *args) {
  struct params p;

  p = *((struct params *)args);

  matrix(p.M, p.N, p.P, p.A, p.B, p.AB);

  return NULL;
}
