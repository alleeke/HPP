#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 4

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

pthread_mutex_t m;
double **A,**B,**C,**C2;
int n;

void *thread_func(void *arg){
  int *data = (int*)arg; 
  int i,k,j;
  int startRowInd = data[0], endRowInd = data[1];
  int startColInd = data[2], endColInd = data[3];

 // printf("i: [%d,%d)\n",startRowInd,endRowInd);
 // printf("j: [%d,%d)\n",startColInd,endColInd);

  // Multiply C=A*B
  for (i = startRowInd; i < endRowInd; i++) {
      for (j = startColInd; j < endColInd; j++) {
          double sum = 0;
          for (k = 0; k < n; k++) {
              sum += A[i][k] * B[k][j];
          }
          pthread_mutex_lock(&m);
          C2[i][j] += sum;
          pthread_mutex_unlock(&m);
        }
    }
      
	     

  return NULL; 
}

int main(int argc, char *argv[]) {
  int i, j, k, t;

  if(argc != 2) {
    printf("Please give one argument: the matrix size n\n");
    return -1;
  }

  n = atoi(argv[1]);
  
  //Allocate and fill matrices
  A = (double **)malloc(n*sizeof(double *));
  B = (double **)malloc(n*sizeof(double *));
  C = (double **)malloc(n*sizeof(double *));
  C2 = (double **)malloc(n*sizeof(double *));
  for(i=0;i<n;i++){
    A[i] = (double *)malloc(n*sizeof(double));
    B[i] = (double *)malloc(n*sizeof(double));
    C[i] = (double *)malloc(n*sizeof(double));
    C2[i] = (double *)malloc(n*sizeof(double));
  }

  for (i = 0; i<n; i++)
    for(j=0;j<n;j++){
      A[i][j] = rand() % 5 + 1;
      B[i][j] = rand() % 5 + 1;
      C[i][j] = 0.0;
      C2[i][j] = 0.0;
    }

  printf("Doing (serial) matrix-matrix multiplication...\n");
  double startTime = get_wall_seconds();

  // Multiply C=A*B
   for(i=0; i<n; i++)
    for (j=0; j<n; j++)
      for (k=0; k<n; k++)
	C[i][j] += A[i][k] * B[k][j]; 

  double timeTaken = get_wall_seconds() - startTime;
  printf("Elapsed time: %f wall seconds\n", timeTaken);

  // Correctness check (let this part remain serial)
  printf("Verifying result correctness for a few result matrix elements...\n");
  int nElementsToVerify = 5*n;
  double max_abs_diff = 0;
  for(int el = 0; el < nElementsToVerify; el++) {
    i = rand() % n;
    j = rand() % n;
    double Cij = 0;
    for(k = 0; k < n; k++)
      Cij += A[i][k] * B[k][j];
    double abs_diff = fabs(C[i][j] - Cij);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("max_abs_diff = %g\n", max_abs_diff);
  if(max_abs_diff > 1e-10) {
    for(i = 0; i < 10; i++)
      printf("ERROR: TOO LARGE DIFF. SOMETHING IS WRONG.\n");
    //return -1;
  }
  printf("OK -- result seems correct!\n");

  printf("Doing (parallel) matrix-matrix multiplication...\n");
  startTime = get_wall_seconds();

  pthread_t threads[NUM_THREADS];
  int d[NUM_THREADS][4];

  // Multiply C=A*B
  for(t=0; t < NUM_THREADS; t++){
    d[t][0] = t*(n/NUM_THREADS);
    d[t][1] = (t+1)*(n/NUM_THREADS);
    d[t][2] = 0;
    d[t][3] = n;

    pthread_create(&threads[t], NULL,thread_func, &(d[t]));
  }

  for (t = 0; t < NUM_THREADS; t++){
    pthread_join(threads[t],NULL);
  }

  timeTaken = get_wall_seconds() - startTime;
  printf("Elapsed time: %f wall seconds\n", timeTaken);

  // Correctness check (let this part remain serial)
  printf("Verifying result correctness for a few result matrix elements...\n");
  nElementsToVerify = 5*n;
  max_abs_diff = 0;
  for(int el = 0; el < nElementsToVerify; el++) {
    i = rand() % n;
    j = rand() % n;
    double Cij = 0;
    for(k = 0; k < n; k++)
      Cij += A[i][k] * B[k][j];
    double abs_diff = fabs(C2[i][j] - Cij);
    if(abs_diff > max_abs_diff)
      max_abs_diff = abs_diff;
  }
  printf("max_abs_diff = %g\n", max_abs_diff);
  if(max_abs_diff > 1e-10) {
    for(i = 0; i < 10; i++)
      printf("ERROR: TOO LARGE DIFF. SOMETHING IS WRONG.\n");
    return -1;
  }
  printf("OK -- result seems correct!\n");

  
  // Free memory
  for(i=0;i<n;i++){
    free(A[i]);
    free(B[i]);
    free(C[i]);
    free(C2[i]);
  }
  free(A);
  free(B);
  free(C);
  free(C2);

  return 0;
}
