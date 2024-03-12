#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
 
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
int rand_int(int N)
{
  int val = -1;
  while( val < 0 || val >= N )
    {
      val = (int)(N * (double)rand()/RAND_MAX);
    }
  return val;
}

void allocate_mem(int*** arr, int n)
{
  int i;
  *arr = (int**)malloc(n*sizeof(int*));
  for(i=0; i<n; i++)
    (*arr)[i] = (int*)malloc(n*sizeof(int));
}

void free_mem(int** arr, int n)
{
  int i;
  for(i=0; i<n; i++)
    free(arr[i]);
  free(arr);
}

/* kij */
void mul_kij(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (k=0; k<n; k++) {
    for (i=0; i<n; i++) {
      int x = a[i][k];
      for (j=0; j<n; j++)
	c[i][j] += x * b[k][j];   
    }
  }
}

void block_ijk(int n, int **a, int **b, int**c)
{
  int blockSz = 100; 
  if(n % blockSz != 0){
    printf("Error n mod blockSz != 0");
    return ; 
  } 
  
  int nBlocks = n/blockSz;
  int a_block[blockSz][blockSz];
  int b_block[blockSz][blockSz];
  int block_i, block_j, block_k, iStart,jStart,kStart;
  for (block_i = 0; block_i < nBlocks; block_i++){
    iStart = block_i*blockSz;
    for (block_j = 0; block_j < nBlocks; block_j++){
      jStart = block_j*blockSz;
      for (block_k= 0; block_k < nBlocks; block_k++){
      kStart = block_k*blockSz;
        // fill blocks
        int i,j,k; 

        // a_block = a[i][k]
        for(i = 0; i < blockSz; i++){
          for(k = 0; k < blockSz; k++){
            a_block[i][k] = a[iStart + i][kStart+k];
          }
        }
	      
        // b_block = b[k][j] 
        for(k = 0; k < blockSz; k++){
          for(j = 0; j < blockSz; j++){
            b_block[k][j] = b[kStart + k][jStart+j];
          }
        }

        // loop through block and multiply
         for (i = 0; i < blockSz; i++){
          for (j = 0; j < blockSz; j++){
            int sum = 0; 
            for (k = 0; k < blockSz; k++){
              sum += a_block[i][k]*b_block[k][j];             
            } 
            c[iStart+i][jStart+j] = sum; 
          }  
        }
  }
}
  }
}

/* kji */
void mul_kji(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (k=0; k<n; k++) {
    for (j=0; j<n; j++) {
      int x = b[k][j];
      for (i=0; i<n; i++)
	c[i][j] += x * a[i][k];   
    }
  }
}

/* ijk */
void mul_ijk(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (i=0; i<n; i++)  {
    for (j=0; j<n; j++) {
      int sum = 0;
      for (k=0; k<n; k++) 
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

/* jik */
void mul_jik(int n, int **a, int **b, int **c)
{
  int i, j, k;
  for (j=0; j<n; j++) {
    for (i=0; i<n; i++) {
      int sum = 0;
      for (k=0; k<n; k++)
	sum += a[i][k] * b[k][j];
      c[i][j] = sum;
    }
  }
}

int main()
{
  int i, j, n;
  int **a;
  int **b;
  int **c;
  double time;
  int Nmax = 100; // random numbers in [0, N]

  printf("Enter the dimension of matrices n = ");
  if(scanf("%d", &n) != 1) {
    printf("Error in scanf.\n");
    return -1;
  }

  allocate_mem(&a, n);

  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      a[i][j] = rand_int(Nmax);

  allocate_mem(&b, n);
 
  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      b[i][j] = rand_int(Nmax);

  allocate_mem(&c, n);

  time=get_wall_seconds();
  mul_kij(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kij, time = %f\n",time);
  time=get_wall_seconds();
  mul_ijk(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version ijk, time = %f\n",time);
  time=get_wall_seconds();

  /* for ( i = 0 ; i < n ; i +=10 ) printf("%d\t", c[i][1]);
  printf("\n");
 */
  mul_jik(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version jik, time = %f\n",time);

  time=get_wall_seconds()-time;
  mul_kji(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version kji, time = %f\n",time); 

  time=get_wall_seconds();
  block_ijk(n, a, b, c);
  time=get_wall_seconds()-time;
  printf("Version block_ijk, time = %f\n",time);
  
  /* printf("Product of first col entered matrices:\n");
 
  for ( i = 0 ; i < n ; i +=10 ) printf("%d\t", c[i][1]);
  printf("\n"); */
    

  /*
    printf("Product of entered matrices:\n");
 
    for ( i = 0 ; i < n ; i++ )
    {
    for ( j = 0 ; j < n ; j++ )
    printf("%d\t", c[i][j]);
 
    printf("\n");
    }
  */

  free_mem(a, n);
  free_mem(b, n);
  free_mem(c, n);

  return 0;
}
